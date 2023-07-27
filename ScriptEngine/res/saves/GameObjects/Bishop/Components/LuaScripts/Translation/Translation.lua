function Awake()
	print("Awake")
	timer = Engine.Timer:new()
end

function Start()
	print("start executed")
	translateVector = Engine.vec3.new(0.001, 0.001, 0.0)
	print("translateVector was initialized")
	gameObject = Engine.ResourceManager.getGameObject("Bishop")
	gameObject:Teleport(Engine.vec3.new(-0.375, 0.875, 10.0))
end

function Update()
	if(timer:IsStart() == false) then
		timer:StartTimer()
	end

	TranslatePerTime()
end

function TranslatePerTime()
--	delta = timer:GetTimeSec() - timer:GetStart()
--	if(delta >= 0) then
--		gameObject:Translate(translateVector)
--		timer:EndTimer()
--	end
end