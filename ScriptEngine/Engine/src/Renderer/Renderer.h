#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"

#include <glm/vec2.hpp>

#include <string>

namespace RenderEngine
{
	class Renderer
	{
	public:
		static void draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const ShaderProgram& shader);
		static void setClearColor(float r, float g, float b, float a);
		static void clear();
		static void setViewport(unsigned int width, unsigned int height, unsigned int leftOffset, unsigned int bottomOffset);
		
		static const std::string getRendererStr();
		static const std::string getVersionStr();

		static glm::dvec2 ViewportSize;
		static glm::ivec2 ViewportOffset;
	};
}