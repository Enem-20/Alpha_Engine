#include "ClassRegistrator.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>

#include <typeinfo>

namespace ScriptEngine
{
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

	int ClassRegistrator::Registration(sol::table* Lnamespace)
	{
		if (!IsReg)
		{
			Reg_GLMvec2(Lnamespace);
			Reg_GLMvec3(Lnamespace);
			Reg_GLMMat3(Lnamespace);
			
			return 0;
		}

		return -1;
	}
}
