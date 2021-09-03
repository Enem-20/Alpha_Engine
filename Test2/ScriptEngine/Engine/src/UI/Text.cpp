#include "Text.h"
#include "../Renderer/Texture2D.h"
#include "../Resources/ResourceManager.h"

#include <iostream>

namespace UI
{
	Text::Text(std::string path)
	{
		strText = "same";
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		for (GLubyte c = 0; c < 128; c++)
		{
			if (FT_Init_FreeType(&ft))
			{
				std::cerr << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
			}

			if (FT_New_Face(ft, path.c_str(), 0, &face))
			{
				std::cerr << "ERROR::FREETYPE: Failed to load font" << std::endl;
			}

			FT_Set_Pixel_Sizes(face, 0, 48);

			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cerr << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}

			//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			Character character(face);

			Characters.emplace(c, character);
		}
	}

	Text::Character::Character(FT_Face face)
	{
		sprite = std::make_shared<RenderEngine::Sprite>(std::make_shared<RenderEngine::Texture2D>(face->glyph->bitmap.width, face->glyph->bitmap.rows, face->glyph->bitmap.buffer, 1, GL_NEAREST, GL_CLAMP_TO_EDGE),
			"", ResourceManager::getShaderProgram("TextShader"));

		Size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
		Bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
		Advance = face->glyph->advance.x;
	}

	void Text::loadCharacters()
	{


		//Characters.emplace(character);
	}

	Text::~Text()
	{
		FT_Done_Face(face);
		FT_Done_FreeType(ft);
	}

	std::string Text::GetStr()
	{
		return strText;
	}
	void Text::SetStr(std::string newStrText)
	{
		strText = newStrText;
	}
}