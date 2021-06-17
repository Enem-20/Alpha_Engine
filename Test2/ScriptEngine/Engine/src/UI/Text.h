#pragma once

#include "UIelement.h"
#include "../Renderer/VertexArray.h"
#include "../Renderer/VertexBuffer.h"
#include "../Renderer/VertexBufferLayout.h"
#include "../Renderer/IndexBuffer.h"
#include "../Renderer/ShaderProgram.h"

#include <unordered_map>
#include <memory>

#include <glm/vec2.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace RenderEngine
{
	class Texture2D;
}

namespace UI
{
	class Text : UIelement
	{
	public:
		struct Character
		{
			Character(FT_Face face);

			std::shared_ptr<RenderEngine::Texture2D> texture2D; // ID текстуры глифа
			glm::ivec2 Size; // размер глифа
			glm::ivec2 Bearing; // смещение от линии шрифта до верхнего/левого угла глифа
			unsigned int Advance; // смещение до следующего глифа
		};

		void render() override
		{

		}
		void Update() override
		{

		}
		void loadCharacters();

		Text(std::string path);
		~Text();
	private:
		std::unordered_map<char, Character> Characters;
		FT_Library ft;
		FT_Face face;

		std::shared_ptr<RenderEngine::ShaderProgram> m_shaderProgram;
		glm::vec2 m_position;
		glm::vec3 m_rotation;
		glm::vec2 m_size;
		glm::mat4 model;

		RenderEngine::VertexArray m_vertexArray;
		RenderEngine::VertexBuffer m_vertexCoordsBuffer;
		RenderEngine::VertexBuffer m_textureCoordsBuffer;
		RenderEngine::IndexBuffer m_IndexBuffer;
		int RenderMode;
	};
}