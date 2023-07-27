figureTypesWithCount = {
    ["Pawn"] = 8,
    ["Knight"] = 2,
    ["Bishop"] = 2,
    ["Castle"] = 2,
    ["Queen"] = 1,
    ["King"] = 1
}

faction = {
    "White",
    "Black"
}

figuresFullInfo = {
    --[===[
        [<name>] = {
            ["player"] = <player>,
            ["faction"] = <faction>,
            ["type"] = <figureType>,
            ["cellPosition"] = <cellPosition>,
            ["NDCPosition"] = <NDCPosition>,
            ["GameObject"] = <GameObject>
        }
    --]===]
}

figuresPool = {}

movementDirections = {}

currentPlayer = {
    "Player1", "Player2",
}

function swap(first, second)
    local buf = first
    first = second
    second = buf;
end

function getCurrentPlayer()
    return currentPlayer[1]
end

function changePlayer() 
    swap(currentPlayer[1], currentPlayer[2])
end

currentFaction = {
    "White", "Black"
}

function getCurrentFaction()
    return currentFaction[1]
end

function changeFaction()
    swap(currentFaction[1], currentFaction[2])
end

function Awake()
    local file = io.open("state.txt", 'r')
    currentPlayer[1] = file:read()
    local currentPlayerNumber = currentPlayer[1]:sub(-1)

    if currentPlayerNumber == 1 then
        currentPlayer[2] = "Player2"
    elseif currentPlayerNumber == 2 then
        currentPlayer[2] = "Player1"
    end

    currentFaction[1] = file:read()
    if currentFaction[1] == "White" then
        currentFaction[2] = "Black"
    else
        currentFaction[2] = "White"
    end

    file.close()
    --currentFaction[1] = 
end

function Start()
    FiguresCreation()
    FiguresMovementCreation()
    SetFiguresToStartState({"White", "Black"})
end

function FiguresCreation()
    print("FiguresWatcher Start executed")

    print("loop starting")
    for i = 1, #faction, 1
    do
        print("faction for loop")
        for k,v in pairs(figureTypesWithCount)
        do
            print("types for loop")
            for j = 1, v, 1
            do
                print("counts for loop")
                print("faction: ", faction[i])
                local currentName = faction[i] .. k .. tostring(j)
                print("currentName: " .. currentName)
                local cachedFigure = Engine.ResourceManager.getGameObject(currentName)
                print("cachedFigure was got")
                print("faction: " .. faction[i])
                if cachedFigure ~= nil then
                    figuresPool[currentName] = {[k] = cachedFigure}
                    local cachedFigurePos = cachedFigure:getTransform(cachedFigure.name):getPosition()
                    cachedFigure:Teleport(Engine.vec3.new(cachedFigurePos.x, cachedFigurePos.y, 2.0))
                else
                    print("loading new one for: " .. currentName)
                    local figure = Engine.GameObject.new(currentName)
                    print(currentName .. " was created")
                    local transformInitializer = Engine.Transform.new(currentName, Engine.vec3:new(0.0, 0.0, 10.0), Engine.vec3:new(0.0,0.0,0.0), Engine.vec3:new(0.125, 0.125, 0.0001))
                    print("transform for " .. currentName .. " was created")
                    local texture = Engine.ResourceManager.getTexture(faction[i] .. k)
                    if texture == nil then
                        texture = Engine.Texture2D.new(faction[i] .. k, "res/textures/" .. faction[i] .. k .. ".png")
                    end
                    print("texture for " .. currentName .. " was created")
                    local mesh = Engine.ResourceManager.getMesh("SpriteMesh")
                    if mesh == nil then
                        mesh = Engine.Mesh.new("SpriteMesh", "res/models/SpriteMesh.obj")
                    end
                    print("mesh for " .. currentName .. " was created")
                    print(mesh.name)
                    print("texture width: " .. tostring(texture:getWidth()))
                    print("texture height: " .. tostring(texture:getHeight()))
                    print(texture.name)
                    local sprite = Engine.Sprite.new(currentName .. "Sprite", texture.name, "TestShaderProgram", mesh.name, texture:getWidth(), texture:getHeight(), "default")
                    print("sprite for " .. currentName .. " was created")
                    local collider = Engine.ResourceManager.getCollider2D(currentName)
                    if collider == nil then
                        collider = Engine.Collider2D.new(currentName, transformInitializer)
                    end
                    print(collider.name)
                    print("collider for " .. currentName .. " was created")
                    local script = Engine.ResourceManager.getLuaScript(k)
                    if script == nil then
                        --script = Engine.LuaScript.new(k, "res/FiguresMovement/" .. k .. ".lua")
                    end

                    print("script for " .. currentName .. " was created")

                    --figure:addLuaScript(script)
                    figure:addSprite(sprite)
                    print(collider)
                    figure:addCollider2D(collider)
                    figure:addTransform(transformInitializer)
                    print("gameObject was created")
                    figuresPool[currentName] = {[k] = figure}
                    --figuresFullInfo[currentName]["player"] = (k == "White") and 
                    print(currentName .. " initialization complete")
                end
                
            end
        end
    end
end

function unionValuesFromTables(table1, table2)
    print("union")
    local newTable = {}

    for k,v in pairs(table1) do newTable[k] = v end
    for k,v in pairs(table2) do newTable[k] = v end
    return newTable
end

function FiguresMovementCreation()
    print("FiguresMovementCreation is started")
    directionsByType = {
        ["Pawn"] = {Engine.vec3.new(0.0, 1.0, 0.0)},
        ["Castle"] = {Engine.vec3.new(0.0, 1.0, 0.0), Engine.vec3.new(0.0, -1.0, 0.0), Engine.vec3.new(1.0, 0.0, 0.0), Engine.vec3.new(-1.0, 0.0, 0.0)},
        ["Bishop"] = {Engine.vec3.new(1.0, 1.0, 0.0), Engine.vec3.new(-1.0, -1.0, 0.0), Engine.vec3.new(1.0, -1.0, 0.0), Engine.vec3.new(-1.0, 1.0, 0.0)},
    } 
    directionsByType["Queen"] = unionValuesFromTables(directionsByType["Castle"], directionsByType["Bishop"])
    directionsByType["King"] = unionValuesFromTables(directionsByType["Castle"], directionsByType["Bishop"])
    directionsByType["Knight"] = directionsByType["Bishop"]


    movementAmountModifiers = {
        ["Pawn"] = {Engine.vec3.new(1.0,1.0,1.0)},
        ["Castle"] = {Engine.vec3.new(7.0, 7.0, 1.0)},
        ["Knight"] = {Engine.vec3.new(1.0, 2.0, 1.0), Engine.vec3.new(2.0, 1.0, 1.0)}
    }
    movementAmountModifiers["Bishop"] = movementAmountModifiers["Castle"]
    movementAmountModifiers["Queen"] = movementAmountModifiers["Castle"]
    movementAmountModifiers["King"] = movementAmountModifiers["Castle"]
    

    print(directionsByType)
    print(movementAmountModifiers)
    print("movement completed")
end

local columnStartPositions = {
    ["Pawn"] = {1, 2, 3, 4, 5, 6, 7, 8},
    ["Knight"] = {2, 7},
    ["Castle"] = {1, 8},
    ["Bishop"] = {3, 6},
    ["Queen"] = {4},
    ["King"] = {5},
}

local lineStartPositions ={
    ["Pawn"] = {
        ["Player1"] = 2,
        ["Player2"] = 7
    },
    ["Another"] = {
        ["Player1"] = 1,
        ["Player2"] = 8
    }

}

function SetFiguresToStartState(playerFactions) 
    print("setting positions was started")
    local currentPlayerNumber = 1
    for _,v in pairs(playerFactions) do
        print("player faction " .. playerFactions[currentPlayerNumber])
        for k1, v1 in pairs(columnStartPositions) do
            print("columnStartPosition for: " .. "[" .. k1 .. "] = " .. tostring(v1[1]))
            for i = 1, #v1, 1 do
                print("faction: " .. v)
                local columnStartPosition = columnStartPositions[k1][i]
                print("ColumnPosition: " .. tostring(columnStartPosition))
                local lineStartPosition = 0.0
                if k1 == "Pawn" then
                    print("figure type: " .. k1)
                    lineStartPosition = lineStartPositions[k1]["Player" .. tostring(currentPlayerNumber)]
                else
                    print("figure type: " .. k1)
                    lineStartPosition = lineStartPositions["Another"]["Player" .. tostring(currentPlayerNumber)]
                end
                print(tostring(lineStartPosition))
                local position2 = fromCelltoNDC(Engine.vec2.new(columnStartPosition, lineStartPosition))
                figuresPool[v .. k1 .. tostring(i)][k1]:Teleport(Engine.vec3.new(position2, 10.0))
            end
        end
        currentPlayerNumber = currentPlayerNumber + 1
    end
    print("figures on they own positions")
end

local ndcRange = Engine.vec2.new(-1.0, 1.0)
local cellCenteredRange = Engine.vec2.new(0.5, 8.5)

function fromNDCtoCell(vector)
    print("vector.x: " .. vector.x)
    print("vector.y: " .. vector.y)
    local x = (math.floor(Engine.Casts.castValueToNewRange(vector.x, ndcRange, cellCenteredRange) + 0.5) * 5) / 5.0
    local y = (math.floor(Engine.Casts.castValueToNewRange(vector.y, ndcRange, cellCenteredRange) + 0.5) * 5) / 5.0
    --local x = Engine.Casts.castValueToNewRange(vector.x, ndcRange, cellCenteredRange)
    --local y = Engine.Casts.castValueToNewRange(vector.y, ndcRange, cellCenteredRange)
    return Engine.vec2.new(x, y)
end

function fromCelltoNDC(vector)
    local vec = Engine.vec2.new(Engine.Casts.castValueToNewRange(vector.x, cellCenteredRange, ndcRange), 
    Engine.Casts.castValueToNewRange(vector.y, cellCenteredRange, ndcRange))

    print("new NDC vec: " .. "(" .. vec.x .. "; " .. vec.y .. ")")
    return vec 
end

function saveCurrentState()
    local file, err = io.open("state.txt", 'w')

    if file then
        file:write(currentPlayer[1])
        file:write(currentFaction[1])

        file.close()
    end
end