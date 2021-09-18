function Start()
    Engine.Input.AddListener(GetUnit)
    selectedObject = nil
    print("print cell added")
end
    
function GetUnit()
    if(selectedObject == nil) then
        selectedObject = Engine.Hierarchy.getGridObject(GetCell())
    else
        selectedObject = nil
    end
    print("Click is working")
end

function GetCell()
    local cell = Engine.Input:GetCell()
    if(cell.x ~= -9 and cell.y ~= -9) then    
        print(cell.x, ":", cell.y)
    end
    return cell
end