function Awake()
    white_moves = 0
    black_moves = 0
    GameObjects = {}
    rank = 
    {
        ["pawn"] = pawn,
        ["bishop"] = bishop, 
        ["knight"] = knight, 
        ["castle"] = castle, 
        ["queen"] = queen, 
        ["king"] = king
    }
    fraction = {["white"] = white, ["black"] = black}
    --item = {object, moves}
    queueMove = {[false] = "white", [true] = "black"}
    current = false
    q = {}
    enemies = {}
end

function Start()
    for i = 1, 8 do
        GameObjects["pawn_white" .. tostring(i)] = {[1] = Engine.Hierarchy.getObject("pawn_white" .. tostring(i)), [2] = 0}
        GameObjects["pawn_black" .. tostring(i)] = {[1] = Engine.Hierarchy.getObject("pawn_black" .. tostring(i)), [2] = 0}
    end
    for i = 1, 2 do
        GameObjects["bishop_white" .. tostring(i)] = {[1] = Engine.Hierarchy.getObject("bishop_white" .. tostring(i)), [2] = 0}
        GameObjects["bishop_black" .. tostring(i)] = {[1] = Engine.Hierarchy.getObject("bishop_black" .. tostring(i)), [2] = 0}

        GameObjects["knight_white" .. tostring(i)] = {[1] = Engine.Hierarchy.getObject("knight_white" .. tostring(i)), [2] = 0}
        GameObjects["knight_black" .. tostring(i)] = {[1] = Engine.Hierarchy.getObject("knight_black" .. tostring(i)), [2] = 0}

        GameObjects["castle_white" .. tostring(i)] = {[1] = Engine.Hierarchy.getObject("castle_white" .. tostring(i)), [2] = 0}
        GameObjects["castle_black" .. tostring(i)] = {[1] = Engine.Hierarchy.getObject("castle_black" .. tostring(i)), [2] = 0}
    end

    GameObjects["queen_white"] = {[1] = Engine.Hierarchy.getObject("queen_white"), [2] = 0}
    GameObjects["queen_black"] = {[1] = Engine.Hierarchy.getObject("queen_black"), [2] = 0}
    GameObjects["king_white"] = {[1] = Engine.Hierarchy.getObject("king_white"), [2] = 0}
    GameObjects["king_black"] = {[1] = Engine.Hierarchy.getObject("king_black"), [2] = 0}

    print(#GameObjects)
    for _, obj in pairs(GameObjects) do
        Engine.Hierarchy.addGridObject(obj[1].name)
        obj[1].onGrid = true
    end
    Engine.Input.AddListener(GetUnit)
    selectedObject = nil
    previousCell = Engine.ivec2:new(-9,-9)
    --Engine.Hierarchy.addPoolObject(Engine.Hierarchy.getObject("Allowed_cell"))
    Allowed_cell = Engine.Hierarchy.getObject("Allowed_cell")
    print("print cell added")
end
    
function GetUnit()
print("get unit function")
    local cell = GetCell()

    if selectedObject == nil then
        selectedObject = Engine.Hierarchy.getGridObject(cell)
        if Engine.StringFuncs.Find(selectedObject.name, queueMove[current]) then
            previousCell = cell
            chooseRank(cell)
        else
            selectedObject = nil
            print(#q)
            for i = 1, #q do
                Engine.Hierarchy.removeObject(q[i].name)
                q[i] = nil
                print("removed")
            end
            for i = 1, #enemies do
                Engine.Hierarchy.removeObject(enemies[i][2].name)
                Engine.Hierarchy.addGridObject(enemies[i][1].name)
                enemies[i] = nil
                --print("removed")
            end
            print("unselected")
            previousCell = Engine.ivec2:new(-9,-9)
        end
    elseif (previousCell.x == cell.x) and (previousCell.y == cell.y) then
        selectedObject = nil
        print(#q)
        for i = 1, #q do
            Engine.Hierarchy.removeObject(q[i].name)
            q[i] = nil
            print("removed")
        end
        for i = 1, #enemies do
            Engine.Hierarchy.removeObject(enemies[i][2].name)
            Engine.Hierarchy.addGridObject(enemies[i][1].name)
            enemies[i] = nil
            --print("removed")
        end
        print("unselected")
        previousCell = Engine.ivec2:new(-9,-9)
    else
        local isAllowedBreak = false
        for i = 1, #q do
            posCellQ = Engine.Input.GetVectorCell(q[i]:GetTransform():GetPosition())
            if(cell.x == posCellQ.x) and (cell.y == posCellQ.y) then
                selectedObject:Teleport(Engine.Casts.CellToScreen(cell, Engine.ivec2:new(8,8)))
                print("allowed_cell detected")
                isAllowedBreak = true
                break
            end
        end
        if not isAllowedBreak then
            print(#enemies, "   before first remove")
            for i = 1, #enemies do
                posCellQ = Engine.Input.GetVectorCell(enemies[i][2]:GetTransform():GetPosition())
                if(cell.x == posCellQ.x) and (cell.y == posCellQ.y) then
                    Engine.Hierarchy.removeObject(enemies[i][2].name)
                    Engine.Hierarchy.removeObject(enemies[i][1].name)
                    selectedObject:Teleport(Engine.Casts.CellToScreen(cell, Engine.ivec2:new(8,8)))
                    print("enemies detected")
                    enemies[i] = nil
                    isAllowedBreak = true
                    break
                end
            end
        end

        if (not isAllowedBreak) then
            selectedObject = Engine.Hierarchy.getGridObject(cell)
            previousCell = cell 
            for i = 1, #q do
                Engine.Hierarchy.removeObject(q[i].name)
                q[i] = nil
            end
            for i = 1, #enemies do
                if(enemies[i] ~= nil) then
                    Engine.Hierarchy.removeObject(enemies[i][2].name)
                    Engine.Hierarchy.addGridObject(enemies[i][1].name)
                    enemies[i] = nil
                end
                --print("removed")
            end
            print("changed")
            chooseRank(cell)
        else
            GameObjects[selectedObject.name][2] = GameObjects[selectedObject.name][2] + 1
            selectedObject = nil
            previousCell = Engine.ivec2:new(-9,-9)
            for i = 1, #q do
                Engine.Hierarchy.removeObject(q[i].name)
            end
            print(#enemies, "   before last remove")
            for i = 1, #enemies do
                if enemies[i] ~= nil then
                    Engine.Hierarchy.removeObject(enemies[i][2].name)
                    Engine.Hierarchy.addGridObject(enemies[i][1].name)
                end
                --print("removed")
            end
            q = {}
            enemies = {}
            current = not current
        end
    end
    
    print("Click is working")
end

function GetCell()
    local cell = Engine.Input:GetCell()
    if(cell.x ~= -9) and (cell.y ~= -9) then    
        print(cell.x, ":", cell.y)
    end
    return cell
end

function pawn(cell)
    local check
    local check2

    local attack
    local attack2
    local fraction = nil
    local fraction2 = nil
    if not current then
        check = Engine.ivec2:new(cell.x, cell.y + 1)
        check2 = Engine.ivec2:new(cell.x, cell.y + 2)
        attack = Engine.ivec2:new(cell.x - 1, cell.y + 1)
        local buf = Engine.Hierarchy.getGridObject(attack) 
        if (buf ~= nil) and Engine.StringFuncs.Find(buf.name, "white") then
            fraction = "white"
            print("attack fraction white")
        elseif (buf ~= nil) and Engine.StringFuncs.Find(buf.name, "black") then
            fraction = "black"
            print("attack fraction black")
        end
        attack2 = Engine.ivec2:new(cell.x + 1, cell.y + 1)
        buf = Engine.Hierarchy.getGridObject(attack2)
        if (buf ~= nil) and Engine.StringFuncs.Find(buf.name, "white") then
            fraction2 = "white"
            print("attack2 fraction white")
        elseif (buf ~= nil) and Engine.StringFuncs.Find(buf.name, "black") then
            fraction2 = "black"
            print("attack2 fraction black")
        end
    else
        check = Engine.ivec2:new(cell.x, cell.y - 1)
        check2 = Engine.ivec2:new(cell.x, cell.y - 2)
        attack = Engine.ivec2:new(cell.x - 1, cell.y - 1)
        local buf = Engine.Hierarchy.getGridObject(attack) 
        if (buf ~= nil) and Engine.StringFuncs.Find(buf.name, "white") then
            fraction = "white"
            print("attack fraction white")
        elseif (buf ~= nil) and Engine.StringFuncs.Find(buf.name, "black") then
            fraction = "black"
            print("attack fraction black")
        end
        attack2 = Engine.ivec2:new(cell.x + 1, cell.y - 1)
        buf = Engine.Hierarchy.getGridObject(attack2)
        if (buf ~= nil) and Engine.StringFuncs.Find(buf.name, "white") then
            fraction2 = "white"
            print("attack2 fraction white")
        elseif (buf ~= nil) and Engine.StringFuncs.Find(buf.name, "black") then
            fraction2 = "black"
            print("attack2 fraction black")
        end
    end

    if Engine.Hierarchy.getGridObject(check) == nil then
        print("it is white pawn!")
        if(GameObjects[selectedObject.name][2] ~= 0) then
            q[1] = Engine.Hierarchy.addObject(Allowed_cell)
            q[1]:Teleport(Engine.Casts.CellToScreen(check, Engine.ivec2:new(8,8)))
            print("added allowed_cell")
            Engine.Hierarchy.addGridObject(q[1].name)
        else
            q[1] = Engine.Hierarchy.addObject(Allowed_cell)
            q[1]:Teleport(Engine.Casts.CellToScreen(check, Engine.ivec2:new(8,8)))
            Engine.Hierarchy.addGridObject(q[1].name)
            print("added allowed_cell")
            if Engine.Hierarchy.getGridObject(check2) == nil then
                q[2] = Engine.Hierarchy.addObject(Allowed_cell)
                q[2]:Teleport(Engine.Casts.CellToScreen(check2, Engine.ivec2:new(8,8)))
                Engine.Hierarchy.addGridObject(q[2].name)
                print("added allowed_cell")
            end
        end
    end

    if (fraction ~= nil) and (fraction ~= queueMove[current]) then
        enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(attack), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
        enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(attack, Engine.ivec2:new(8,8)))
        print("added allowed_cell")
        Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)
    end
    if (fraction2 ~= nil) and (fraction2 ~= queueMove[current]) then
        enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(attack2), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
        enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(attack2, Engine.ivec2:new(8,8)))
        print("added allowed_cell")
        Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)
    end
end

function bishop(cell)   
    local qu = dequeue.new()
    parents = {}
    local cur = Engine.ivec2:new(cell.x - 1, cell.y + 1)
    if(Engine.Hierarchy.getGridObject(cur) == nil) and checkBorders(cur) then
        parents[cur] = cell
        qu:push_right(cur)
        q[#q + 1] = Engine.Hierarchy.addObject(Allowed_cell)
        q[#q]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(q[#q].name)
    elseif (Engine.Hierarchy.getGridObject(cur) ~= nil) and checkBorders(cur) and not Engine.StringFuncs.Find(Engine.Hierarchy.getGridObject(cur).name, queueMove[current]) then
        enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(cur), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
        enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)
    end
    cur = Engine.ivec2:new(cell.x + 1, cell.y + 1)
    if(Engine.Hierarchy.getGridObject(cur) == nil) and checkBorders(cur) then
        parents[cur] = cell
        qu:push_right(cur)
        q[#q + 1] = Engine.Hierarchy.addObject(Allowed_cell)
        q[#q]:Teleport(Engine.Casts.CellToScreen(cur), Engine.ivec2:new(8,8))
        Engine.Hierarchy.addGridObject(q[#q].name)
    elseif (Engine.Hierarchy.getGridObject(cur) ~= nil) and checkBorders(cur) and not Engine.StringFuncs.Find(Engine.Hierarchy.getGridObject(cur).name, queueMove[current]) then
        enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(cur), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
        enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)
    end
    cur = Engine.ivec2:new(cell.x - 1, cell.y - 1)
    if(Engine.Hierarchy.getGridObject(cur) == nil) and checkBorders(cur) then
        parents[cur] = cell
        qu:push_right(cur)
        q[#q + 1] = Engine.Hierarchy.addObject(Allowed_cell)
        q[#q]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(q[#q].name)
    elseif (Engine.Hierarchy.getGridObject(cur) ~= nil) and checkBorders(cur) and not Engine.StringFuncs.Find(Engine.Hierarchy.getGridObject(cur).name, queueMove[current]) then
        enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(cur), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
        enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)
    end
    cur = Engine.ivec2:new(cell.x + 1, cell.y - 1)
    if(Engine.Hierarchy.getGridObject(cur) == nil) and checkBorders(cur) then
        parents[cur] = cell
        qu:push_right(cur)
        q[#q + 1] = Engine.Hierarchy.addObject(Allowed_cell)
        q[#q]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(q[#q].name)
    elseif (Engine.Hierarchy.getGridObject(cur) ~= nil) and checkBorders(cur)  and not Engine.StringFuncs.Find(Engine.Hierarchy.getGridObject(cur).name, queueMove[current]) then
        enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(cur), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
        enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)
    end

    --local visited = {cell = true}
    
    print("queue created")

    while not qu:is_empty() do
        local currentQ = qu:peek_left() + GetDirection(qu:peek_left())
        print(currentQ.x, ":", currentQ.y)
        print("bishop get current")
        --local direction = GetDirection(current)
        if(Engine.Hierarchy.getGridObject(currentQ) == nil) and checkBorders(currentQ) then
            qu:push_right(currentQ)
            q[#q + 1] = Engine.Hierarchy.addObject(Allowed_cell)
            q[#q]:Teleport(Engine.Casts.CellToScreen(currentQ, Engine.ivec2:new(8,8)))
            Engine.Hierarchy.addGridObject(q[#q].name)
            parents[currentQ] = qu:peek_left()
        elseif (Engine.Hierarchy.getGridObject(currentQ) ~= nil) and checkBorders(currentQ) and not Engine.StringFuncs.Find(Engine.Hierarchy.getGridObject(currentQ).name, queueMove[current]) then
            print("add enemy")
            enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(currentQ), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
            enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(currentQ, Engine.ivec2:new(8,8)))
            Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)   
        end
        qu:pop_left()
    end  
end

function knight(cell)
    local cur = Engine.ivec2:new(cell.x - 2, cell.y + 1)
    if(Engine.Hierarchy.getGridObject(cur) == nil) and checkBorders(cur) then
        q[#q + 1] = Engine.Hierarchy.addObject(Allowed_cell)
        q[#q]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(q[#q].name)
    elseif(Engine.Hierarchy.getGridObject(cur) ~= nil) and checkBorders(cur) and not Engine.StringFuncs.Find(Engine.Hierarchy.getGridObject(cur).name, queueMove[current]) then
        enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(cur), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
        enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)
    end
    cur = Engine.ivec2:new(cell.x - 1, cell.y + 2)
    if(Engine.Hierarchy.getGridObject(cur) == nil) and checkBorders(cur) then
        q[#q + 1] = Engine.Hierarchy.addObject(Allowed_cell)
        q[#q]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(q[#q].name)
    elseif(Engine.Hierarchy.getGridObject(cur) ~= nil) and checkBorders(cur) and not Engine.StringFuncs.Find(Engine.Hierarchy.getGridObject(cur).name, queueMove[current]) then
        enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(cur), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
        enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)
    end
    cur = Engine.ivec2:new(cell.x + 1, cell.y + 2)
    if(Engine.Hierarchy.getGridObject(cur) == nil) and checkBorders(cur) then
        q[#q + 1] = Engine.Hierarchy.addObject(Allowed_cell)
        q[#q]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(q[#q].name)
    elseif(Engine.Hierarchy.getGridObject(cur) ~= nil) and checkBorders(cur) and not Engine.StringFuncs.Find(Engine.Hierarchy.getGridObject(cur).name, queueMove[current]) then
        enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(cur), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
        enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)
    end
    cur = Engine.ivec2:new(cell.x + 2, cell.y + 1)
    if(Engine.Hierarchy.getGridObject(cur) == nil) and checkBorders(cur) then
        q[#q + 1] = Engine.Hierarchy.addObject(Allowed_cell)
        q[#q]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(q[#q].name)
    elseif(Engine.Hierarchy.getGridObject(cur) ~= nil) and checkBorders(cur) and not Engine.StringFuncs.Find(Engine.Hierarchy.getGridObject(cur).name, queueMove[current]) then
        enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(cur), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
        enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)
    end

    cur = Engine.ivec2:new(cell.x + 2, cell.y - 1)
    if(Engine.Hierarchy.getGridObject(cur) == nil) and checkBorders(cur) then
        q[#q + 1] = Engine.Hierarchy.addObject(Allowed_cell)
        q[#q]:Teleport(Engine.Casts.CellToScreen(cur), Engine.ivec2:new(8,8))
        Engine.Hierarchy.addGridObject(q[#q].name)
    elseif(Engine.Hierarchy.getGridObject(cur) ~= nil) and checkBorders(cur) and not Engine.StringFuncs.Find(Engine.Hierarchy.getGridObject(cur).name, queueMove[current]) then
        enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(cur), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
        enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)
    end
    cur = Engine.ivec2:new(cell.x + 1, cell.y - 2)
    if(Engine.Hierarchy.getGridObject(cur) == nil) and checkBorders(cur) then
        q[#q + 1] = Engine.Hierarchy.addObject(Allowed_cell)
        q[#q]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(q[#q].name)
    elseif(Engine.Hierarchy.getGridObject(cur) ~= nil) and checkBorders(cur) and not Engine.StringFuncs.Find(Engine.Hierarchy.getGridObject(cur).name, queueMove[current]) then
        enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(cur), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
        enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)
    end
    cur = Engine.ivec2:new(cell.x - 1, cell.y - 2)
    if(Engine.Hierarchy.getGridObject(cur) == nil) and checkBorders(cur) then
        q[#q + 1] = Engine.Hierarchy.addObject(Allowed_cell)
        q[#q]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(q[#q].name)
    elseif(Engine.Hierarchy.getGridObject(cur) ~= nil) and checkBorders(cur) and not Engine.StringFuncs.Find(Engine.Hierarchy.getGridObject(cur).name, queueMove[current]) then
        enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(cur), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
        enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)
    end
    cur = Engine.ivec2:new(cell.x - 2, cell.y - 1)
    if(Engine.Hierarchy.getGridObject(cur) == nil) and checkBorders(cur) then
        q[#q + 1] = Engine.Hierarchy.addObject(Allowed_cell)
        q[#q]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(q[#q].name)
    elseif(Engine.Hierarchy.getGridObject(cur) ~= nil) and checkBorders(cur) and not Engine.StringFuncs.Find(Engine.Hierarchy.getGridObject(cur).name, queueMove[current]) then
        enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(cur), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
        enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)
    end
end

function castle(cell)   
    local qu = dequeue.new()
    parents = {}
    local cur = Engine.ivec2:new(cell.x - 1, cell.y)
    if(Engine.Hierarchy.getGridObject(cur) == nil) and checkBorders(cur) then
        parents[cur] = cell
        qu:push_right(cur)
        q[#q + 1] = Engine.Hierarchy.addObject(Allowed_cell)
        q[#q]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(q[#q].name)
    elseif (Engine.Hierarchy.getGridObject(cur) ~= nil) and checkBorders(cur) and not Engine.StringFuncs.Find(Engine.Hierarchy.getGridObject(cur).name, queueMove[current]) then
        enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(cur), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
        enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)
    end
    cur = Engine.ivec2:new(cell.x, cell.y + 1)
    if(Engine.Hierarchy.getGridObject(cur) == nil) and checkBorders(cur) then
        parents[cur] = cell
        qu:push_right(cur)
        q[#q + 1] = Engine.Hierarchy.addObject(Allowed_cell)
        q[#q]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(q[#q].name)
    elseif (Engine.Hierarchy.getGridObject(cur) ~= nil) and checkBorders(cur) and not Engine.StringFuncs.Find(Engine.Hierarchy.getGridObject(cur).name, queueMove[current]) then
        enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(cur), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
        enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)
    end
    cur = Engine.ivec2:new(cell.x + 1, cell.y)
    if(Engine.Hierarchy.getGridObject(cur) == nil) and checkBorders(cur) then
        parents[cur] = cell
        qu:push_right(cur)
        q[#q + 1] = Engine.Hierarchy.addObject(Allowed_cell)
        q[#q]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(q[#q].name)
    elseif (Engine.Hierarchy.getGridObject(cur) ~= nil) and checkBorders(cur) and not Engine.StringFuncs.Find(Engine.Hierarchy.getGridObject(cur).name, queueMove[current]) then
        enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(cur), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
        enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)
    end
    cur = Engine.ivec2:new(cell.x, cell.y - 1)
    if(Engine.Hierarchy.getGridObject(cur) == nil) and checkBorders(cur) then
        parents[cur] = cell
        qu:push_right(cur)
        q[#q + 1] = Engine.Hierarchy.addObject(Allowed_cell)
        q[#q]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(q[#q].name)
    elseif (Engine.Hierarchy.getGridObject(cur) ~= nil) and checkBorders(cur)  and not Engine.StringFuncs.Find(Engine.Hierarchy.getGridObject(cur).name, queueMove[current]) then
        enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(cur), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
        enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)
    end

    --local visited = {cell = true}
    
    print("queue created")

    while not qu:is_empty() do
        local currentQ = qu:peek_left() + GetDirection(qu:peek_left())
        print(currentQ.x, ":", currentQ.y)
        print("bishop get current")
        --local direction = GetDirection(current)
        if(Engine.Hierarchy.getGridObject(currentQ) == nil) and checkBorders(currentQ) then
            qu:push_right(currentQ)
            q[#q + 1] = Engine.Hierarchy.addObject(Allowed_cell)
            q[#q]:Teleport(Engine.Casts.CellToScreen(currentQ, Engine.ivec2:new(8,8)))
            Engine.Hierarchy.addGridObject(q[#q].name)
            parents[currentQ] = qu:peek_left()
        elseif (Engine.Hierarchy.getGridObject(currentQ) ~= nil) and checkBorders(currentQ) and not Engine.StringFuncs.Find(Engine.Hierarchy.getGridObject(currentQ).name, queueMove[current]) then
            print("add enemy")
            enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(currentQ), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
            enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(currentQ, Engine.ivec2:new(8,8)))
            Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)   
        end
        qu:pop_left()
    end  
end

function queen(cell)
    local qu = dequeue.new()
    parents = {}
    local cur = Engine.ivec2:new(cell.x - 1, cell.y)
    if(Engine.Hierarchy.getGridObject(cur) == nil) and checkBorders(cur) then
        parents[cur] = cell
        qu:push_right(cur)
        q[#q + 1] = Engine.Hierarchy.addObject(Allowed_cell)
        q[#q]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(q[#q].name)
    elseif (Engine.Hierarchy.getGridObject(cur) ~= nil) and checkBorders(cur) and not Engine.StringFuncs.Find(Engine.Hierarchy.getGridObject(cur).name, queueMove[current]) then
        enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(cur), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
        enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)
    end
    cur = Engine.ivec2:new(cell.x, cell.y + 1)
    if(Engine.Hierarchy.getGridObject(cur) == nil) and checkBorders(cur) then
        parents[cur] = cell
        qu:push_right(cur)
        q[#q + 1] = Engine.Hierarchy.addObject(Allowed_cell)
        q[#q]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(q[#q].name)
    elseif (Engine.Hierarchy.getGridObject(cur) ~= nil) and checkBorders(cur) and not Engine.StringFuncs.Find(Engine.Hierarchy.getGridObject(cur).name, queueMove[current]) then
        enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(cur), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
        enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)
    end
    cur = Engine.ivec2:new(cell.x + 1, cell.y)
    if(Engine.Hierarchy.getGridObject(cur) == nil) and checkBorders(cur) then
        parents[cur] = cell
        qu:push_right(cur)
        q[#q + 1] = Engine.Hierarchy.addObject(Allowed_cell)
        q[#q]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(q[#q].name)
    elseif (Engine.Hierarchy.getGridObject(cur) ~= nil) and checkBorders(cur) and not Engine.StringFuncs.Find(Engine.Hierarchy.getGridObject(cur).name, queueMove[current]) then
        enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(cur), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
        enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)
    end
    cur = Engine.ivec2:new(cell.x, cell.y - 1)
    if(Engine.Hierarchy.getGridObject(cur) == nil) and checkBorders(cur) then
        parents[cur] = cell
        qu:push_right(cur)
        q[#q + 1] = Engine.Hierarchy.addObject(Allowed_cell)
        q[#q]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(q[#q].name)
    elseif (Engine.Hierarchy.getGridObject(cur) ~= nil) and checkBorders(cur)  and not Engine.StringFuncs.Find(Engine.Hierarchy.getGridObject(cur).name, queueMove[current]) then
        enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(cur), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
        enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)
    end
    cur = Engine.ivec2:new(cell.x - 1, cell.y + 1)
    if(Engine.Hierarchy.getGridObject(cur) == nil) and checkBorders(cur) then
        parents[cur] = cell
        qu:push_right(cur)
        q[#q + 1] = Engine.Hierarchy.addObject(Allowed_cell)
        q[#q]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(q[#q].name)
    elseif (Engine.Hierarchy.getGridObject(cur) ~= nil) and checkBorders(cur) and not Engine.StringFuncs.Find(Engine.Hierarchy.getGridObject(cur).name, queueMove[current]) then
        enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(cur), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
        enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)
    end
    cur = Engine.ivec2:new(cell.x + 1, cell.y + 1)
    if(Engine.Hierarchy.getGridObject(cur) == nil) and checkBorders(cur) then
        parents[cur] = cell
        qu:push_right(cur)
        q[#q + 1] = Engine.Hierarchy.addObject(Allowed_cell)
        q[#q]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(q[#q].name)
    elseif (Engine.Hierarchy.getGridObject(cur) ~= nil) and checkBorders(cur) and not Engine.StringFuncs.Find(Engine.Hierarchy.getGridObject(cur).name, queueMove[current]) then
        enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(cur), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
        enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)
    end
    cur = Engine.ivec2:new(cell.x - 1, cell.y - 1)
    if(Engine.Hierarchy.getGridObject(cur) == nil) and checkBorders(cur) then
        parents[cur] = cell
        qu:push_right(cur)
        q[#q + 1] = Engine.Hierarchy.addObject(Allowed_cell)
        q[#q]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(q[#q].name)
    elseif (Engine.Hierarchy.getGridObject(cur) ~= nil) and checkBorders(cur) and not Engine.StringFuncs.Find(Engine.Hierarchy.getGridObject(cur).name, queueMove[current]) then
        enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(cur), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
        enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)
    end
    cur = Engine.ivec2:new(cell.x + 1, cell.y - 1)
    if(Engine.Hierarchy.getGridObject(cur) == nil) and checkBorders(cur) then
        parents[cur] = cell
        qu:push_right(cur)
        q[#q + 1] = Engine.Hierarchy.addObject(Allowed_cell)
        q[#q]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(q[#q].name)
    elseif (Engine.Hierarchy.getGridObject(cur) ~= nil) and checkBorders(cur)  and not Engine.StringFuncs.Find(Engine.Hierarchy.getGridObject(cur).name, queueMove[current]) then
        enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(cur), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
        enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)
    end

    --local visited = {cell = true}
    
    print("queue created")

    while not qu:is_empty() do
        local currentQ = qu:peek_left() + GetDirection(qu:peek_left())
        print(currentQ.x, ":", currentQ.y)
        print("bishop get current")
        --local direction = GetDirection(current)
        if(Engine.Hierarchy.getGridObject(currentQ) == nil) and checkBorders(currentQ) then
            qu:push_right(currentQ)
            q[#q + 1] = Engine.Hierarchy.addObject(Allowed_cell)
            q[#q]:Teleport(Engine.Casts.CellToScreen(currentQ, Engine.ivec2:new(8,8)))
            Engine.Hierarchy.addGridObject(q[#q].name)
            parents[currentQ] = qu:peek_left()
        elseif (Engine.Hierarchy.getGridObject(currentQ) ~= nil) and checkBorders(currentQ) and not Engine.StringFuncs.Find(Engine.Hierarchy.getGridObject(currentQ).name, queueMove[current]) then
            print("add enemy")
            enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(currentQ), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
            enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(currentQ, Engine.ivec2:new(8,8)))
            Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)   
        end
        qu:pop_left()
    end 
end

function king(cell)
    local cur = Engine.ivec2:new(cell.x - 1, cell.y)
    if(Engine.Hierarchy.getGridObject(cur) == nil) and checkBorders(cur) then
        q[#q + 1] = Engine.Hierarchy.addObject(Allowed_cell)
        q[#q]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(q[#q].name)
    elseif (Engine.Hierarchy.getGridObject(cur) ~= nil) and checkBorders(cur) and not Engine.StringFuncs.Find(Engine.Hierarchy.getGridObject(cur).name, queueMove[current]) then
        enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(cur), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
        enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)
    end
    cur = Engine.ivec2:new(cell.x, cell.y + 1)
    if(Engine.Hierarchy.getGridObject(cur) == nil) and checkBorders(cur) then
        q[#q + 1] = Engine.Hierarchy.addObject(Allowed_cell)
        q[#q]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(q[#q].name)
    elseif (Engine.Hierarchy.getGridObject(cur) ~= nil) and checkBorders(cur) and not Engine.StringFuncs.Find(Engine.Hierarchy.getGridObject(cur).name, queueMove[current]) then
        enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(cur), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
        enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)
    end
    cur = Engine.ivec2:new(cell.x + 1, cell.y)
    if(Engine.Hierarchy.getGridObject(cur) == nil) and checkBorders(cur) then
        q[#q + 1] = Engine.Hierarchy.addObject(Allowed_cell)
        q[#q]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(q[#q].name)
    elseif (Engine.Hierarchy.getGridObject(cur) ~= nil) and checkBorders(cur) and not Engine.StringFuncs.Find(Engine.Hierarchy.getGridObject(cur).name, queueMove[current]) then
        enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(cur), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
        enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)
    end
    cur = Engine.ivec2:new(cell.x, cell.y - 1)
    if(Engine.Hierarchy.getGridObject(cur) == nil) and checkBorders(cur) then
        q[#q + 1] = Engine.Hierarchy.addObject(Allowed_cell)
        q[#q]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(q[#q].name)
    elseif (Engine.Hierarchy.getGridObject(cur) ~= nil) and checkBorders(cur)  and not Engine.StringFuncs.Find(Engine.Hierarchy.getGridObject(cur).name, queueMove[current]) then
        enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(cur), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
        enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)
    end
    cur = Engine.ivec2:new(cell.x - 1, cell.y + 1)
    if(Engine.Hierarchy.getGridObject(cur) == nil) and checkBorders(cur) then
        q[#q + 1] = Engine.Hierarchy.addObject(Allowed_cell)
        q[#q]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(q[#q].name)
    elseif (Engine.Hierarchy.getGridObject(cur) ~= nil) and checkBorders(cur) and not Engine.StringFuncs.Find(Engine.Hierarchy.getGridObject(cur).name, queueMove[current]) then
        enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(cur), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
        enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)
    end
    cur = Engine.ivec2:new(cell.x + 1, cell.y + 1)
    if(Engine.Hierarchy.getGridObject(cur) == nil) and checkBorders(cur) then
        q[#q + 1] = Engine.Hierarchy.addObject(Allowed_cell)
        q[#q]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(q[#q].name)
    elseif (Engine.Hierarchy.getGridObject(cur) ~= nil) and checkBorders(cur) and not Engine.StringFuncs.Find(Engine.Hierarchy.getGridObject(cur).name, queueMove[current]) then
        enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(cur), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
        enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)
    end
    cur = Engine.ivec2:new(cell.x - 1, cell.y - 1)
    if(Engine.Hierarchy.getGridObject(cur) == nil) and checkBorders(cur) then
        q[#q + 1] = Engine.Hierarchy.addObject(Allowed_cell)
        q[#q]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(q[#q].name)
    elseif (Engine.Hierarchy.getGridObject(cur) ~= nil) and checkBorders(cur) and not Engine.StringFuncs.Find(Engine.Hierarchy.getGridObject(cur).name, queueMove[current]) then
        enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(cur), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
        enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)
    end
    cur = Engine.ivec2:new(cell.x + 1, cell.y - 1)
    if(Engine.Hierarchy.getGridObject(cur) == nil) and checkBorders(cur) then
        q[#q + 1] = Engine.Hierarchy.addObject(Allowed_cell)
        q[#q]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(q[#q].name)
    elseif (Engine.Hierarchy.getGridObject(cur) ~= nil) and checkBorders(cur)  and not Engine.StringFuncs.Find(Engine.Hierarchy.getGridObject(cur).name, queueMove[current]) then
        enemies[#enemies + 1] = {[1] = Engine.Hierarchy.getGridObject(cur), [2] = Engine.Hierarchy.addObject(Allowed_cell)}
        enemies[#enemies][2]:Teleport(Engine.Casts.CellToScreen(cur, Engine.ivec2:new(8,8)))
        Engine.Hierarchy.addGridObject(enemies[#enemies][2].name)
    end
end

function chooseRank(cell)
    print(selectedObject.name)
    if Engine.StringFuncs.Find(selectedObject.name, "pawn") then 
        pawn(cell)  
    elseif Engine.StringFuncs.Find(selectedObject.name, "bishop") then
        bishop(cell)
    elseif Engine.StringFuncs.Find(selectedObject.name, "castle") then
        castle(cell)
    elseif Engine.StringFuncs.Find(selectedObject.name, "queen") then
        queen(cell)
    elseif Engine.StringFuncs.Find(selectedObject.name, "king") then
        king(cell)
    elseif Engine.StringFuncs.Find(selectedObject.name, "knight") then
        knight(cell)
    end
end

function checkBorders(cell)
    if (cell.x > -1) and (cell.y > -1) and (cell.x < 8) and (cell.y < 8) then
        return true
    end
    return false
end

function GetDirection(cell)
    local buf = parents[cell]
    return Engine.ivec2:new(cell.x - buf.x, cell.y - buf.y)  
end