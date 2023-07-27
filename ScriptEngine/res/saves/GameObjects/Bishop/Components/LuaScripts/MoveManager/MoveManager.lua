local figuresWatcher = require("FiguresWatcher.Components.LuaScripts.FiguresWatcher.FiguresWatcher")

function Pawn(movementEndPoints)
    print("pawn movement creation")
    if (movementEndPoints[1]) then
        print("getting cell position of gameObject")
        local startCellPosVec2 = fromNDCtoCell(selectedGameObject:getTransform(selectedGameObject.name):getPosition())
        print("start from: " .. tostring(startCellPosVec2.x) .. " " .. tostring(startCellPosVec2.y))
        local whereWeShouldMove = Engine.vec3.new(startCellPosVec2.x, startCellPosVec2.y, 1.0) + (movementEndPoints[1] * playerMoveModifier[currentPlayer[1]])
        print("whereWeShouldMove: (" .. tostring(whereWeShouldMove.x)  .. "; " .. tostring(whereWeShouldMove.y) .. ")")

        print("if cell")
        if isCellFree(whereWeShouldMove) then
            print(selectedGameObject)
            if isntFirstMove[selectedGameObject.name] == nil then
                print("is first move")
                print("mult")
                local whereWeShouldMove2 = whereWeShouldMove + Engine.vec3.new(0.0, 1.0, 0.0)
                if isCellFree(whereWeShouldMove2) then
                    print("should move to: " .. tostring(whereWeShouldMove2.x) .. tostring(whereWeShouldMove2.y))
                    allowedCellCreation("AllowedCell2", whereWeShouldMove2)
                end
            end
            local cellName = "AllowedCell1"
            print("should move to: " .. tostring(whereWeShouldMove.x) .. tostring(whereWeShouldMove.y))
            print("allowedCellCreation")
            allowedCellCreation(cellName, whereWeShouldMove)
        else
            print("cell (" .. tostring(whereWeShouldMove.x) .. "; " .. tostring(whereWeShouldMove.y) .. ") isn't free")
        end
    end

end

toPossibleMovementCreation = {
    ["Pawn"] = Pawn
}

movements = {
    -- [name] = object
}

isntFirstMove = {
    -- [name] = true/false
}

print("check before Awake")

function Awake()
    selectedGameObject = nil
    Engine.Input.addOnClickListener("MouseCallback", MouseCallback)
    print("Awake completed")
end

print("Before Start")

function Start()
    print("start check")
    if (Engine.ResourceManager.getTexture("AllowedCell") == nil) then
        allowedCellTexture = Engine.Texture2D.new("AllowedCell", "res/textures/AllowedCell.png")
        print("start completed check")
    else
        allowedCellTexture = Engine.ResourceManager.getTexture("AllowedCell")
    end
end

function Update()
    -- print("Update was executed")
    if (selectedGameObject ~= nil) then
    end
end

print("check before mousecallback")

function deleteMoves()
    for k,v in pairs(movements) do
        print(k)
        print(movements[k])
        Engine.ResourceManager.removeGameObject(k)
        movements[k] = nil
    end
    for k,v in pairs(currentMoves) do
        currentMoves[k] = nil
    end
end

function MouseCallback()
    print("MouseCallback was executed")
    local ndcMousePosition = Engine.Input.getNDCMousePosition()
    print("got ndcMousePosition")

    print(selectedGameObject)
    print("selecting gameObject...")
    print(ndcMousePosition.x, ndcMousePosition.y)
    local cellMousePos = fromNDCtoCell(ndcMousePosition)
    print("cell mouse pos: " .. tostring(cellMousePos.x) .. " " .. tostring(cellMousePos.y))
    local start = Engine.vec3.new(ndcMousePosition, 0.0)
    local finish = Engine.vec3.new(ndcMousePosition, 8000.0)
    print("start and finish initialized")
    local selectedCollider = Engine.Raycast.new():closestBodyHit(Engine.vec3:new(ndcMousePosition, 0.0),
        Engine.vec3.new(ndcMousePosition, 8000.0))
    if selectedCollider ~= nil then
        print("check for move click")
        if movements[selectedCollider:getGameObject().name] then
            local position = selectedCollider:getGameObject():getTransform(selectedCollider:getGameObject().name):getPosition()
            print("teleporting selected gameObject to " .. tostring(fromNDCtoCell(position).x) .. " " .. tostring(fromNDCtoCell(position).y))
            selectedGameObject:Teleport(position)
            isntFirstMove[selectedGameObject.name] = true
            deleteMoves()
            selectedGameObject = nil
            selectedCollider = nil
            return
        end
        deleteMoves()
        selectedGameObject = nil

        selectedGameObject = selectedCollider:getGameObject()
        print("gameObject selected: " .. selectedGameObject.name)

        print("getting selected position...")
        local selectedObjectPos = selectedGameObject:getTransform(selectedGameObject.name):getPosition()
        print("selected object pos: " .. tostring(selectedObjectPos.x) .. " " .. tostring(selectedObjectPos.y))
        print("getting selected position in in vec2...")
        local cellSelectedObjectPos = fromNDCtoCell(selectedObjectPos)
        print(selectedGameObject)
        print("getting objectType")
        local objectType = ""
        print(selectedGameObject.name)
        print(figuresPool[selectedGameObject.name])
        for k, v in pairs(figuresPool[selectedGameObject.name]) do
            print(k)
            objectType = k
        end

        print("Object type: " .. objectType)

        local directions = directionsByType[objectType]
        local movementAmounts = movementAmountModifiers[objectType]

        print("directions and amounts were got")
        print(movementAmounts[1])
        local movementEndPoints = {}
        for i = 1, #directions, 1 do
            for j = 1, #movementAmounts, 1 do
                print("i+j: " .. tostring(i+j))
                print("direction: " .. tostring(directions[i].x) .. " " .. tostring(directions[i].y))
                print("movementAmount: " .. tostring(directions[i].x) .. " " .. tostring(directions[i].y))
                movementEndPoints[i+j-1] = directions[i] * movementAmounts[j]

                print("movementEndPoint: " .. tostring(movementEndPoints[i+j-1].x) .. " " .. tostring(movementEndPoints[i+j-1].y))
            end
        end
        print("to possible movement creation")
        toPossibleMovementCreation[objectType](movementEndPoints)
    else
        deleteMoves()
        selectedGameObject = nil
        print("selection emptied")
    end
end

currentMoves = {
    -- [vec3] = <AllowedCellName>
}

playerMoveModifier = {
    ["Player1"] = Engine.vec3.new(1.0, 1.0, 1.0),
    ["Player2"] = Engine.vec3.new(-1.0, -1.0, 1.0)
}

function allowedCellCreation(cellName, cellPosition)
    print("creating allowed cell: " .. cellName)
    currentMoves[cellPosition] = Engine.GameObject.new(cellName)
    print("new was gameObject created")
    local NDCpositionVec3 = Engine.vec3.new(fromCelltoNDC(cellPosition), 1.0)
    print("ndc pos")
    local transform = Engine.Transform.new(cellName, NDCpositionVec3, Engine.vec3.new(0.0, 0.0, 0.0),
        Engine.vec3.new(0.125, 0.125, 0.0001))
    print("transform was created")
    local cellCollider2D = Engine.Collider2D.new(cellName, transform)
    print("collider was created")
    print(allowedCellTexture.name)
    local cellSprite = Engine.Sprite.new("Sprite" .. cellName, allowedCellTexture.name, "TestShaderProgram",
        "SpriteMesh", allowedCellTexture:getWidth(), allowedCellTexture:getHeight(), "default")
    print("sprite was created")
    currentMoves[cellPosition]:addTransform(transform)
    currentMoves[cellPosition]:addCollider2D(cellCollider2D)
    currentMoves[cellPosition]:addSprite(cellSprite)
    movements[cellName] = currentMoves[cellPosition]
end

function allowedCellSpriteCreation()

end

function isCellFree(cell)
    local raycaster = Engine.Raycast.new()
    print("raycast created")
    local raycastCheck = fromCelltoNDC(cell)
    print("raycastCheck: " .. tostring(raycastCheck.x) .. " " .. tostring(raycastCheck.y))
    local collider = raycaster:closestBodyHit(Engine.vec3.new(fromCelltoNDC(cell), 0.0),
    Engine.vec3.new(fromCelltoNDC(cell), 1000.0))
    print("check if cell free in position: (" .. tostring(cell.x) .. "; " .. tostring(cell.y) .. ")")
    if collider ~= nil then
        print("collider in this place: " .. collider.name)
    end
    return (collider == nil) and true or false
end
