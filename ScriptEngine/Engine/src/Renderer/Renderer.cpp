#include "Renderer.h"

#include "ShaderProgram.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

namespace RenderEngine
{
	glm::dvec2 Renderer::ViewportSize;
	glm::ivec2 Renderer::ViewportOffset;

	void Renderer::draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const ShaderProgram& shader)
	{
		shader.use();
		vertexArray.bind();
		indexBuffer.bind();

		glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::setClearColor(float r, float g, float b, float a)
	{
		glClearColor(r,g,b,a);
	}

	void Renderer::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::setViewport(unsigned int width, unsigned int height, unsigned int leftOffset = 0, unsigned int bottomOffset = 0)
	{
		ViewportSize = glm::dvec2(width, height);
		ViewportOffset = glm::ivec2(leftOffset, bottomOffset);
		glViewport(leftOffset, bottomOffset, width, height);
	}

	const std::string Renderer::getRendererStr()
	{
		return (char*)glGetString(GL_RENDERER);
	}
	const std::string Renderer::getVersionStr()
	{
		return (char*)glGetString(GL_VERSION);
	}
}