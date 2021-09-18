function Start()
    button = Engine.Hierarchy.getObject("Button")
    button2 = Engine.Hierarchy.getObject("LoadScene")
    Engine.WindowManager:GetCurrentWindow():GetUI("Button"):AddListener(Remove)
    print("gettedUIelement")
    
    print("awaked button")
end

function Remove()
    Engine.Hierarchy.removeObject("Button")
    button = nil
    print("Removed")
end