function Start()
    button = Engine.Hierarchy.getObject("Button")
    element = Engine.Input.GetUI("someUI1"):AddListener(OnClick)
    print("gettedUIelement")
    
    print("awaked button")
end

function OnClick()
    print("execute OnClick for someUI1")
    button:Translate(Engine.vec3:new(0,10,0))
end