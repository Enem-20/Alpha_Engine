function Awake()
    timer = Engine.Timer:new()
end

function Start() 
end

function Update()
    if(timer:IsStart() == false) then
        timer:StartTimer()
    end

    TranslatePerTime()
end

function TranslatePerTime()
    delta = timer:GetTimeSec() - timer:GetStart()
    if(delta >= 0) then
        Engine.Hierarchy.getObject("object1"):Translate(Engine.vec3.new(10,10,0))
        timer:EndTimer()
    end
end