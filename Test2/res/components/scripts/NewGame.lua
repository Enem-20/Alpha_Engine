function Awake()
    Engine.WindowManager.GetCurrentWindow():GetUI("NewGame"):AddListener(NewGame)
end

function NewGame()
    Engine.ResourceManager.loadScene("res/saves/GameObjects.json")
    print("newGame")
end