#pragma once

#ifndef API
#define API

#define GL_CLAMP_TO_EDGE 0x812F
#define GL_DYNAMIC_DRAW 0x88E8

#include "ExportProperty.h"

#include "glfw/glfw3.h"

#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
//#include <glad/glad.h>

#include <rapidjson/document.h>

#include <map>



class DLLEXPORT StringFuncs
{
public:
	static std::string Match(const std::string& str1, const std::string& str2);
	static bool Find(const std::string& str1, const std::string& str2);
};
class DLLEXPORT Casts
{
public:
	static glm::vec3 CellToScreen(const glm::ivec2& ivec2, const glm::ivec2& cellSize);
};

class DLLEXPORT Input
{
public:
	static glm::ivec2 GetCellReal();
	static glm::ivec2 GetCell(const glm::vec2& objPos);
	static void AddListener(const sol::function& func);
};

class DLLEXPORT GLPref
{
public:
	static void glfwError(int id, const char* description);
	static void SwapBuffers();
	static void PollEvents();
	static bool isNeedClose();

	static int init();
};

class GameObject;

namespace Components
{
	class DLLEXPORT Component
	{
	public:
		Component(std::string name = "", std::shared_ptr<GameObject> gameObject = nullptr);
		Component(std::string&& name, GameObject&& gameObject) noexcept;

		~Component();
		//Component(std::string&& name, std::shared_ptr<GameObject>&& gameObject)
		//	: name(name)
		//	, gameObject(gameObject)
		//{}
		GameObject& GetGameObject() const;
	};

	class DLLEXPORT Transform : Component
	{
	public:
		Transform(std::string name = "", std::shared_ptr<GameObject> gameObject = nullptr);
		Transform(Transform&& transform) noexcept;
		Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, std::string name = "", std::shared_ptr<GameObject> gameObject = nullptr);

		Transform(const Transform& _transform);

		void Teleport(const glm::vec3& position);
		void Translate(const glm::vec3& position);
		void Rotate(const glm::vec3& rotation);
		void Scale(const glm::vec3& scale);
		void transform();
		const glm::mat4& GetModel() const;

		glm::vec2 GetVec2Position();
		glm::vec3 GetPosition() const;
		glm::vec3 GetRotation() const;
		glm::vec3 GetScale() const;
	};

	class LuaScript : public Component
	{
	public:
		LuaScript(sol::protected_function& Awake, sol::protected_function& Start, sol::protected_function& Update, sol::protected_function& FixedUpdate, sol::protected_function& LastUpdate);
		LuaScript(std::string name, std::string path, std::shared_ptr<GameObject> gameObject = nullptr);
		LuaScript(LuaScript&& script) noexcept;
		LuaScript(const LuaScript& script);
		void SetAwake(const sol::protected_function& Awake);
		void SetStart(const sol::protected_function& Start);
		void SetUpdate(const sol::protected_function& Update);
		void SetFixedUpdate(const sol::protected_function& FixedUpdate);
		void SetLastUpdate(const sol::protected_function& LastUpdate);

		void LoadScript();

		void Awake() const;
		void Start() const;
		void Update() const;
		void FixedUpdate() const;
		void LastUpdate()const;
	};
}

namespace UI
{
	class DLLEXPORT UIelement : public Components::Component
	{
	public:
		UIelement(std::string name, std::shared_ptr<GameObject> gameObject);

		virtual void AddListener(const sol::protected_function& func);

		void executeOnClicks();
		//void setParamCollider();
		//virtual void OnExecute() = 0;

		virtual void Awake() = 0;
		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;

		virtual void translate(const glm::vec2& newPos) = 0;
	};
	class Button : public UIelement
	{
	public:
		~Button();

		Button(std::string name = "", std::shared_ptr<GameObject> gameObject = nullptr);

		enum class States { Idle, Down, Stay, Up };

		void Awake() override;
		void Start() override;
		void Update() override;
		void FixedUpdate() override;

		void translate(const glm::vec2& newPos) override;
	};
}

class DLLEXPORT Hierarchy
{
public:
	static void removeObjectReal(const std::string& name);
	static void addObject(const GameObject& obj);
	//static void addObj(const std::string& name);
	static void removeObject(const std::string& name);
	static std::shared_ptr<GameObject> getObject(const std::string& name);
	static GameObject& getOriginalObject(std::string name);
	static void ExecuteEvent();
	static void Clear();

	static void addGridObject(const std::string& objName);
	static void removeGridObject(const glm::ivec2& cell);
	static std::shared_ptr<GameObject> getGridObject(const glm::ivec2& cell);
	static void addPoolObject(std::shared_ptr<GameObject> obj);
	static std::shared_ptr<GameObject> getPoolObject(const std::string& name);
	static void removePoolObject(const std::string& name);
	static GameObject& addFromScriptObject(const GameObject& obj);
	static std::unordered_map<std::string, std::shared_ptr<GameObject>> GetSceneObjects();
};

class DLLEXPORT Window
{
public:
	Window();
	~Window();
	Window(GLFWwindow* window);
	Window(std::string name, int width, int height);
	//GLFWwindow* GetRaw();
	//void SetWindow(GLFWwindow* window);
	//std::shared_ptr<Window> CreateWindow(const std::string& name, const unsigned int& width, const unsigned int& height);
	//void Awake();
	////void Start();
	//void Update();
	//void FixedUpdate();
	//std::shared_ptr<UI::Button>& AddUI(const UI::Button& ui);
	std::shared_ptr<UI::UIelement> GetUI(const std::string& name) const;
	//void RemoveUI(const std::string name);
};

class DLLEXPORT WindowManager
{
public:
	//static int init(std::string name, int width = 1080, int height = 1080);
	static void ShutDown();

	//static std::shared_ptr<Window> GetWindow(std::string name);
	//static std::shared_ptr<Window> AddWindow(std::string name, int width = 1080, int height = 1080);
	static Window& GetCurrentWindow();
	static void Start();
	static void Update();
};

class DLLEXPORT Timer
{
public:
	Timer();
	int GetTimeSec() const;
	int GetDeltaUpdateSec() const;
	int GetDelta() const;
	int GetStart() const;
	int GetEnd() const;
	void StartUpdateTimer();
	void EndUpdateTimer();
	void StartTimer();
	void EndTimer();
	bool IsStart() const;
};

namespace RenderEngine
{
	class DLLEXPORT ShaderProgram
	{
	public:
		ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
		~ShaderProgram();

		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&);
		ShaderProgram& operator=(const ShaderProgram&) = delete;
		ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;
		ShaderProgram(ShaderProgram&& shaderProgram) noexcept;

		bool isCompiled() const;
		void use() const;
		void setInt(const std::string& name, const GLint value);
		void setMatrix4(const std::string& name, const glm::mat4& matrix);
	};

	class DLLEXPORT Texture2D
	{
	public:
		struct SubTexture2D
		{
			SubTexture2D(const SubTexture2D& sub);

			SubTexture2D(SubTexture2D&& sub) noexcept;

			SubTexture2D(const glm::vec2 _leftBottomUV, const glm::vec2 _rightTopUV);
			SubTexture2D();

			const glm::vec2& getLeftBottomUV() const;
			const glm::vec2& getRightTopUV() const;

			const SubTexture2D& operator=(const SubTexture2D& second);
		};
		Texture2D() = delete;
		Texture2D(const GLuint width, const GLuint height,
			const unsigned char* data, const unsigned int channels = 4,
			const GLenum filter = GL_LINEAR, const GLenum wrapMode = GL_CLAMP_TO_EDGE);
		//Texture2D() = default;
		Texture2D(Texture2D& texture2d);
		Texture2D& operator=(const Texture2D&) = delete;
		Texture2D& operator=(Texture2D&& texture2d) noexcept;
		Texture2D(Texture2D&& texture2d) noexcept;
		~Texture2D();

		void addSubTexture(std::string name, const glm::vec2& leftBottomUV, const glm::vec2& rightTopUV);
		const SubTexture2D& getSubTexture(const std::string& name) const;
		unsigned int getWidth() const;
		unsigned int getHeight() const;

		void bind() const;
	};

	class DLLEXPORT Sprite
	{
	public:
		std::string name;
		Sprite(std::shared_ptr<Texture2D> Texture,
			std::string initialSubTexture,
			std::shared_ptr<ShaderProgram> shaderProgram,
			const glm::vec2& position = glm::vec2(0.f, 0.f),
			const glm::vec3& rotation = glm::vec3(1.f),
			const glm::vec2& size = glm::vec2(1.f),
			const int RenderMode = GL_DYNAMIC_DRAW);
		virtual ~Sprite();

		Sprite() = delete;
		Sprite(const Sprite& sprite);
		Sprite& operator=(const Sprite&) = delete;
		Sprite(Sprite&& sprite) noexcept;

		void Translate(glm::vec3 position);
		void Rotate(glm::vec3 rotation);
		void Scale(glm::vec3 scale);
		virtual void render(const glm::mat4& model) const;
		virtual void InstanceRender(glm::mat4 model) const;
		void setPosition(const glm::vec2& position);
		glm::vec2 getSize() const;
		glm::vec3 getRotation() const;
		void setSize(const glm::vec2& size);
		void setRotation(const glm::vec3& rotation);
		int GetRenderMode() const;
	};

	class AnimatedSprite : public Sprite
	{
	public:
		AnimatedSprite(std::shared_ptr<Texture2D> Texture,
			std::string initialSubTexture,
			std::shared_ptr<ShaderProgram> shaderProgram,
			const glm::vec2& position = glm::vec2(0.f),
			const glm::vec3& rotation = glm::vec3(0.f),
			const glm::vec2& size = glm::vec2(1.f));
		void insertState(std::string state, std::vector<std::pair<std::string, uint64_t>> subTexturesDuration);
		void render(const glm::mat4& model) const override;
		void Update(const uint64_t deltaTime);
		void setState(const std::string& newState);
	};
}

class DLLEXPORT GameObject
{
public:
	static GameObject& toNull(GameObject& gameObject);
	static GameObject SetNull();
	static GameObject Null;
public:
	GameObject(const GameObject& gameObject);
	//GameObject(GameObject&&) = default;
	GameObject(std::string name = "",
		std::shared_ptr<Components::Transform> transform = nullptr,
		std::shared_ptr<RenderEngine::Sprite> sprite = nullptr,
		std::unordered_map<std::string, std::shared_ptr<Components::LuaScript>> scripts = std::unordered_map<std::string, std::shared_ptr<Components::LuaScript>>(),
		std::unordered_map<std::string, std::shared_ptr<UI::Button>> buttons = std::unordered_map<std::string, std::shared_ptr<UI::Button>>(),
		int render_priority = 0);
	void operator=(const GameObject& gameObject);
	GameObject(GameObject&&) = delete;
	virtual ~GameObject();
	void Translate(const glm::vec3& position);
	void Teleport(const glm::vec3& position);
	void Rotate(glm::vec3 rotation);
	void Scale(glm::vec3 scale);
	void Update();

	const bool& isGrided() const;
	const std::string& Name() const;
	Components::Transform& GetTransform();
	void SetOnGrid(const bool& onGridNew);
	virtual void render();
	std::unordered_map<std::string, std::shared_ptr<Components::LuaScript>> GetScripts() const;
	const int& GetRenderPriority() const;

	std::shared_ptr<GameObject> testShared(GameObject gameObject);

	void AddChild(const GameObject& gameObject);
	GameObject& GetChild(int i) const;

	virtual std::shared_ptr<RenderEngine::Sprite> GetSprite() const;
};


class DLLEXPORT ResourceManager
{
public:
	struct m_Components
	{
		std::unordered_map<std::string, std::shared_ptr<Components::LuaScript>> scripts;
		std::unordered_map<std::string, std::shared_ptr<UI::Button>> buttons;
	};
	static void SetExecutablePath(const std::string& executablePath);
	static void UnloadAllResources();

	ResourceManager() = delete;
	~ResourceManager() = delete;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;
	ResourceManager(ResourceManager&&) = delete;

	static void SetLuaState(std::shared_ptr<sol::state> L);
	static std::shared_ptr<RenderEngine::ShaderProgram> loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
	static std::shared_ptr<RenderEngine::ShaderProgram> getShaderProgram(const std::string& shaderName);

	static std::shared_ptr<RenderEngine::Texture2D> loadTexture(const std::string& textureName, const std::string& texturePath);
	static std::shared_ptr<RenderEngine::Texture2D> getTexture(const std::string& textureName);

	static std::shared_ptr<RenderEngine::Sprite> loadSprite(const std::string& spriteName,
		const std::string& textureName,
		const std::string& shaderName,
		const unsigned int spriteWidth,
		const unsigned int spriteHeight,
		const int RenderMode,
		const std::string& subTextureName = "default");
	static std::shared_ptr<RenderEngine::Sprite> getSprite(const std::string& spriteName);

	static std::shared_ptr<RenderEngine::AnimatedSprite> loadAnimatedSprite(const std::string& spriteName,
		const std::string& textureName,
		const std::string& shaderName,
		const unsigned int spriteWidth,
		const unsigned int spriteHeight,
		const std::string& subTextureName = "default");
	static std::shared_ptr<RenderEngine::AnimatedSprite> getAnimatedSprite(const std::string& spriteName);


	static std::shared_ptr<RenderEngine::Texture2D> loadTextureAtlas(std::string textureName,
		std::string texturePath,
		std::vector<std::string> subTextures,
		const unsigned int subTextureWidth,
		const unsigned int subTextureHeight);
	static std::string GetLuaScriptPath(const std::string& relativePath);

	static rapidjson::Document documentParse(const std::string& relativePath);

	static bool loadJSONScene(const std::string& relativePath);
	static bool loadSave(const std::string relativePath);
	static void loadSaveReal(const std::string& relativePath);
	static void loadExecute();
	[[nodiscard]] static bool loadJSONGameOjects(const std::string& relativePath);
	static bool loadJSONSprites(const std::string& relativePath);
	static bool loadJSONTextureAtlasses(const std::string& relativePath);
	static bool loadJSONTextures(const std::string& relativePath);
	static bool loadJSONShaders(const std::string& relativePath);
	static m_Components loadJSONComponents(const rapidjson::Value& it);

	static std::string GetPath();
};

#endif