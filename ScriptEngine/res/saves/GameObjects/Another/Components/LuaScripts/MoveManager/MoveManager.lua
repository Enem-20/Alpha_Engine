function Awake()
    selectedGameObject = nil
    Engine.Input.addOnClickListener("MouseCallback", MouseCallback)
    print("Awake completed")
end

function Start()
end

function Update()
    --print("Update was executed")
    if(selectedGameObject ~= nil) then
        print("printing selected gameObject...")
        print("Selected gameObject: ", selectedGameObject:Name())
        selectedGameObject = nil
    end
end

function MouseCallback()
    print("MouseCallback was executed")
    local ndcMousePosition = Engine.Input.getNDCMousePosition()
    print("got ndcMousePosition")
    
    print(selectedGameObject)
    if selectedGameObject == nil then
        print("selecting gameObject...")
        print(ndcMousePosition.x, ndcMousePosition.y)
        local start = Engine.vec3:new(ndcMousePosition, 0.0)
        local finish = Engine.vec3:new(ndcMousePosition, 8000.0)
        print("start and finish initialized")
        selectedGameObject = Engine.Raycast:new():closestBodyHit(Engine.vec3:new(ndcMousePosition, 0.0), Engine.vec3:new(ndcMousePosition, 8000.0)):getGameObject()
        print("gameObject was selected")
    end
end