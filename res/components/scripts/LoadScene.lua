function Awake()
    Engine.WindowManager.GetCurrentWindow():GetUI("LoadScene"):AddListener(Load)
end

function Load()
    Engine.Hierarchy.removeObject("LoadScene")
    
    Engine.ResourceManager.loadScene("res/scene.json")
    print("loaded")
end