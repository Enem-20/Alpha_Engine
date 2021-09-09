function Start()
    button = Engine.Hierarchy.getObject("Button")
    button2 = Engine.Hierarchy.getObject("Button2")
    Engine.WindowManager:GetCurrentWindow():GetUI("Button2"):AddListener(OnClick)
    print("gettedUIelement2")
    
    print("awaked button2")
end

function OnClick()
    print("execute OnClick for Button2")
    button2:Translate(Engine.vec3:new(10,0,0))
    if(button ~= nil) then
        button:Translate(Engine.vec3:new(10,0,0))
    end
    
end