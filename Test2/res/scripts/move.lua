function Awake()
    print("Awake is worked")
    timer = Helpers.Timer:new()
end

function Start() 
    --Helpers.Hierarchy.getObject("object1"):Translate(Helpers.vec3.new(1,1,1))
    print("Start is worked")
end

function Update()
    if(timer:IsStart() == false) then
        timer:StartTimer()
        print("StartTimer")
    end

    delta = timer:GetTimeSec() - timer:GetStart()
    print("Start: ", timer:GetStart())
    print(delta)
    if(delta >= 1) then
        Helpers.Hierarchy.getObject("object1"):Translate(Helpers.vec3.new(5,5,0))
        print("Translated")
        timer:EndTimer()
    end
end