//#pragma once
//
//#include "UIelement.h"
//#include "../Renderer/VertexArray.h"
//#include "../Renderer/VertexBuffer.h"
//#include "../Renderer/VertexBufferLayout.h"
//#include "../Renderer/IndexBuffer.h"
//#include "../Renderer/ShaderProgram.h"
//
//#include <unordered_map>
//#include <memory>
//
//#include <glm/vec2.hpp>
//#include <ft2build.h>
//#include FT_FREETYPE_H
//
//namespace RenderEngine
//{
//	class Texture2D;
//}
//
//namespace UI
//{
//	class Text : UIelement
//	{
//	public:
//		struct Character
//		{
//			Character(FT_Face face);
//
//			//std::shared_ptr<RenderEngine::Texture2D> texture2D; // ID текстуры глифа
//			std::shared_ptr<RenderEngine::Sprite> sprite;	
//			glm::ivec2 Size; // размер глифа
//			glm::ivec2 Bearing; // смещение от линии шрифта до верхнего/левого угла глифа
//			unsigned int Advance; // смещение до следующего глифа
//		};
//
//		void render(glm::mat4 model) override
//		{
//			float scale = 5;
//			float x = 0;
//			float y = 20;
//			std::string::const_iterator c;
//			for (c = strText.begin(); c != strText.end(); c++)
//			{
//				Character ch = Characters.find(*c)->second;
//
//				GLfloat xpos = x + ch.Bearing.x * scale;
//				GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
//
//				GLfloat w = ch.Size.x * scale;
//				GLfloat h = ch.Size.y * scale;
//				// Update VBO for each character
//				GLfloat vertices[6][4] = {
//					{ xpos, ypos + h, 0.0, 0.0 },
//					{ xpos, ypos, 0.0, 1.0 },
//					{ xpos + w, ypos, 1.0, 1.0 },
//					{ xpos, ypos + h, 0.0, 0.0 },
//					{ xpos + w, ypos, 1.0, 1.0 },
//					{ xpos + w, ypos + h, 1.0, 0.0 }
//				};
//
//				auto chara = Characters.find(*c);
//
//				chara->second.sprite->render(model);
//
//				x += (ch.Advance >> 6) * scale;
//			}
//		}
//		void Update() override
//		{
//
//		}
//		void loadCharacters();
//
//		std::string GetStr();
//		void SetStr(std::string newStrText);
//		Text(std::string path);
//		~Text();
//	private:
//		std::string strText;
//		std::unordered_map<char, Character> Characters;
//		FT_Library ft;
//		FT_Face face;
//	};
//}