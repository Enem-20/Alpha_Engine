#include "ClassRegistrator.h"
#include "../Engine/src/GameTypes/GameTypes.h"
#include "../Engine/src/Scene/Hierarchy.h"
#include "../Engine/src/Timer.h"
#include "../Engine/src/UI/Button.h"
#include "../Engine/src/Input/Input.h"
#include "../Engine/src/Components/Components.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "glad/glad.h"

#include <typeinfo>

namespace ScriptEngine
{
	static GameObject GetData(std::shared_ptr<GameObject> gameObject)
	{
		return *gameObject;
	}

	void ClassRegistrator::Reg_GLMvec2(sol::table* Lnamespace)
	{
		Lnamespace->new_usertype<glm::vec2>("vec2"
			, sol::constructors<glm::vec2(), glm::vec2(float, float), glm::vec2(glm::vec2)>()

			, sol::meta_function::addition, sol::resolve<glm::vec2(const glm::vec2&, const glm::vec2&)>(glm::operator+)
			, sol::meta_function::subtraction, sol::resolve<glm::vec2(const glm::vec2&, const glm::vec2&)>(glm::operator-)
			, sol::meta_function::multiplication, sol::resolve<glm::vec2(const glm::vec2&, const glm::vec2&)>(glm::operator*)
			//, sol::meta_function::bitwise_xor, sol::resolve<glm::vec2(const glm::vec2&, const float)>(glm::operator^)
			, sol::meta_function::division, sol::resolve<glm::vec2(const glm::vec2&, const glm::vec2&)>(glm::operator/)

			, "x", &glm::vec2::x
			, "y", &glm::vec2::y
			);
	}

	void ClassRegistrator::Reg_GLMivec2(sol::table* Lnamespace)
	{
		Lnamespace->new_usertype<glm::ivec2>("vec2"
			, sol::constructors<glm::ivec2(), glm::ivec2(float, float), glm::ivec2(glm::ivec2)>()

			, sol::meta_function::addition, sol::resolve<glm::ivec2(const glm::ivec2&, const glm::ivec2&)>(glm::operator+)
			, sol::meta_function::subtraction, sol::resolve<glm::ivec2(const glm::ivec2&, const glm::ivec2&)>(glm::operator-)
			, sol::meta_function::multiplication, sol::resolve<glm::ivec2(const glm::ivec2&, const glm::ivec2&)>(glm::operator*)
			//, sol::meta_function::bitwise_xor, sol::resolve<glm::vec2(const glm::vec2&, const float)>(glm::operator^)
			, sol::meta_function::division, sol::resolve<glm::ivec2(const glm::ivec2&, const glm::ivec2&)>(glm::operator/)

			, "x", &glm::ivec2::x
			, "y", &glm::ivec2::y
			);
	}

	void ClassRegistrator::Reg_GLMvec3(sol::table* Lnamespace)
	{
		Lnamespace->new_usertype<glm::vec3>("vec3"
			, sol::constructors<glm::vec3(), glm::vec3(float, float, float), glm::vec3(glm::vec2, float), glm::vec3(float, glm::vec2), glm::vec3(glm::vec3)>()

			, sol::meta_function::addition, sol::resolve<glm::vec3(const glm::vec3&, const glm::vec3&)>(glm::operator+)
			, sol::meta_function::subtraction, sol::resolve<glm::vec3(const glm::vec3&, const glm::vec3&)>(glm::operator-)
			, sol::meta_function::multiplication, sol::resolve<glm::vec3(const glm::vec3&, const glm::vec3&)>(glm::operator*)
			//, sol::meta_function::bitwise_xor, sol::resolve<glm::vec3(const glm::vec3&, const glm::vec3&)>(glm::operator^)
			, sol::meta_function::division, sol::resolve<glm::vec3(const glm::vec3&, const glm::vec3&)>(glm::operator/)

			, "x", &glm::vec3::x
			, "y", &glm::vec3::y
			, "z", &glm::vec3::z
			);
	}

	void ClassRegistrator::Reg_GLMvec4(sol::table* Lnamespace)
	{
		Lnamespace->new_usertype<glm::vec4>("vec4"
			, sol::constructors<glm::vec4(), glm::vec4(float, float, float, float)
			, glm::vec4(glm::vec2, float, float), glm::vec4(float, float, glm::vec2), glm::vec4(float, glm::vec2, float)
			, glm::vec4(glm::vec2, glm::vec2)
			, glm::vec4(glm::vec3, float), glm::vec4(float, glm::vec3)
			, glm::vec4(glm::vec4)>()

			, sol::meta_function::addition, sol::resolve<glm::vec4(const glm::vec4&, const glm::vec4&)>(glm::operator+)
			, sol::meta_function::subtraction, sol::resolve<glm::vec4(const glm::vec4&, const glm::vec4&)>(glm::operator-)
			, sol::meta_function::multiplication, sol::resolve<glm::vec4(const glm::vec4&, const glm::vec4&)>(glm::operator*)
			//, sol::meta_function::bitwise_xor, sol::resolve<glm::vec4(const glm::vec4&, const glm::vec4&)>(glm::operator^)
			, sol::meta_function::division, sol::resolve<glm::vec4(const glm::vec4&, const glm::vec4&)>(glm::operator/)

			, "x", &glm::vec4::x
			, "y", &glm::vec4::y
			, "z", &glm::vec4::z
			, "w", &glm::vec4::w
			);
	}

	void ClassRegistrator::Reg_GLMMat3(sol::table* Lnamespace)
	{
		Lnamespace->new_usertype<glm::mat3>("mat3"
			, sol::constructors<glm::mat3(), glm::mat3(float), glm::mat3(const glm::mat3&), glm::mat3(glm::vec3&, glm::vec3&, glm::vec3&)>()

			, sol::meta_function::addition, sol::resolve<glm::mat3(const glm::mat3&, const glm::mat3&)>(glm::operator+)
			, sol::meta_function::subtraction, sol::resolve<glm::mat3(const glm::mat3&, const glm::mat3&)>(glm::operator-)
			, sol::meta_function::multiplication, sol::resolve<glm::mat3(const glm::mat3&, const glm::mat3&)>(glm::operator*)
			//, sol::meta_function::bitwise_xor, sol::resolve<glm::vec2(const glm::vec2&, const float)>(glm::operator^)
			, sol::meta_function::division, sol::resolve<glm::mat3(const glm::mat3&, const glm::mat3&)>(glm::operator/)
			);
	}

	void ClassRegistrator::Reg_GLMMat4(sol::table* Lnamespace)
	{
		Lnamespace->new_usertype<glm::mat4>("mat4"
			, sol::constructors<glm::mat4(), glm::mat4(float), glm::mat4(const glm::mat4&), glm::mat4(glm::vec4&, glm::vec4&, glm::vec4&, glm::vec4&)>()

			, sol::meta_function::addition, sol::resolve<glm::mat4(const glm::mat4&, const glm::mat4&)>(glm::operator+)
			, sol::meta_function::subtraction, sol::resolve<glm::mat4(const glm::mat4&, const glm::mat4&)>(glm::operator-)
			, sol::meta_function::multiplication, sol::resolve<glm::mat4(const glm::mat4&, const glm::mat4&)>(glm::operator*)
			//, sol::meta_function::bitwise_xor, sol::resolve<glm::vec2(const glm::vec2&, const float)>(glm::operator^)
			, sol::meta_function::division, sol::resolve<glm::mat4(const glm::mat4&, const glm::mat4&)>(glm::operator/)
			);
	}

	void ClassRegistrator::Reg_ShaderProgram(sol::table* same)
	{
		Reg_GLMMat4(same);
		same->new_usertype<RenderEngine::ShaderProgram>("ShaderProgram"
			, sol::constructors<RenderEngine::ShaderProgram(const std::string&, const std::string&)
			, RenderEngine::ShaderProgram(RenderEngine::ShaderProgram&&)>()

			, "isCompiled", &RenderEngine::ShaderProgram::isCompiled
			, "use", &RenderEngine::ShaderProgram::use
			, "setInt", &RenderEngine::ShaderProgram::setMatrix4);
	}

	void ClassRegistrator::Reg_SubTexture2D(sol::table* LTexture2D)
	{
		LTexture2D->new_usertype<RenderEngine::Texture2D::SubTexture2D>("SubTexture2D"
			, sol::constructors<RenderEngine::Texture2D::SubTexture2D(), RenderEngine::Texture2D::SubTexture2D(const glm::vec2, const glm::vec2)>()
			, "leftBottomUV", &RenderEngine::Texture2D::SubTexture2D::leftBottomUV
			, "rightTopUV", &RenderEngine::Texture2D::SubTexture2D::rightTopUV
				);
	}

	void ClassRegistrator::Reg_Texture2D(sol::table* same)
	{
		if (same != nullptr)
		{
			same->new_usertype<RenderEngine::Texture2D>("Texture2D"
				, sol::constructors<RenderEngine::Texture2D(const GLuint, const GLuint
					, const unsigned char*, const unsigned int, const GLenum, const GLenum)

				, RenderEngine::Texture2D(RenderEngine::Texture2D&&)>()

				, "addSubTexture", &RenderEngine::Texture2D::addSubTexture
				, "getSubTexture", &RenderEngine::Texture2D::getSubTexture
				, "getWidth", &RenderEngine::Texture2D::getWidth
				, "getHeight", &RenderEngine::Texture2D::getHeight
				, "bind", &RenderEngine::Texture2D::bind
				);

			Reg_SubTexture2D(same);
		}
	}

	void ClassRegistrator::Reg_Sprite(sol::table* object)
	{
		object->new_usertype<RenderEngine::Sprite>("Sprite"
			, sol::constructors<RenderEngine::Sprite(std::shared_ptr<RenderEngine::Texture2D>,
				std::string,
				std::shared_ptr<RenderEngine::ShaderProgram>,
				const glm::vec2& position,
				const glm::vec3& rotation,
				const glm::vec2& size)>()

			, "render", &RenderEngine::Sprite::render
			, "setPosition", &RenderEngine::Sprite::setPosition
			, "getSize", &RenderEngine::Sprite::getSize
			, "setSize", &RenderEngine::Sprite::setSize
			, "setRotation", &RenderEngine::Sprite::setRotation
			);
	}

	void ClassRegistrator::Reg_UIelement(sol::table* UIElement)
	{
		UIElement->new_usertype<UI::UIelement>("UIelement"
			, "AddListener", &UI::UIelement::AddListener);
	}

	void ClassRegistrator::Reg_Transform(sol::table* Lnamespace)
	{
		Lnamespace->new_usertype<Components::Transform>("Transform"
			, sol::constructors<Components::Transform(std::string, std::shared_ptr<GameObject>), Components::Transform(const Components::Transform&)>()
			, "position", &Components::Transform::position
			, "rotation", &Components::Transform::rotation
			, "scale", &Components::Transform::scale);
	}

	void ClassRegistrator::Reg_GameObject(sol::table* object)
	{
		object->new_usertype<GameObject>("GameObject"
			, sol::constructors<GameObject(std::string), GameObject(const GameObject&)>()

			, "Translate", &GameObject::Translate
			, "Rotate",   &GameObject::Rotate
			, "AddChild", &GameObject::AddChild
			, "GetChild", &GameObject::GetChild

			, "name", &GameObject::name
			);
	}

	void ClassRegistrator::Reg_Timer(sol::table* Lnamespace)
	{
		Lnamespace->new_usertype<Timer>("Timer"
			, "StartTimer", &Timer::StartTimer
			, "EndTimer", &Timer::EndTimer
			, "GetDelta", &Timer::GetDelta
			, "GetTimeSec", &Timer::GetTimeSec
			, "IsStart", &Timer::IsStart
			, "GetStart", &Timer::GetStart
			, "GetEnd", &Timer::GetEnd);
	}

	void ClassRegistrator::Reg_Input(sol::table* Lnamespace)
	{
		Lnamespace->new_usertype<Input>("Input"
			, "GetUI", &Input::GetUI);
	}

	void ClassRegistrator::Reg_Hierarchy(sol::table* hierarchy)
	{
		hierarchy->new_usertype<Hierarchy>("Hierarchy"
			, "getObject", &Hierarchy::getObject);
	}

	int ClassRegistrator::Registration(sol::table* Lnamespace)
	{
		if (!IsReg)
		{
			Reg_GLMvec2(Lnamespace);
			Reg_GLMivec2(Lnamespace);
			Reg_GLMvec3(Lnamespace);
			Reg_GLMvec4(Lnamespace);
			Reg_GLMMat3(Lnamespace);
			Reg_GLMMat4(Lnamespace);

			Reg_Texture2D(Lnamespace);
			Reg_Sprite(Lnamespace);
			Reg_ShaderProgram(Lnamespace);
			Reg_GameObject(Lnamespace);
			Reg_Hierarchy(Lnamespace);
			Reg_Timer(Lnamespace);
			Reg_UIelement(Lnamespace);
			Reg_Input(Lnamespace);
			Reg_Transform(Lnamespace);

			return 0;
		}

		return -1;
	}
}
