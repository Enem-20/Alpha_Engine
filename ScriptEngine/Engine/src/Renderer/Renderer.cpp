#include "Renderer.h"

#include "ShaderProgram.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

#include "../Logging/Clerk.h"

namespace RenderEngine
{
	glm::dvec2 Renderer::ViewportSize;
	glm::ivec2 Renderer::ViewportOffset;
	Renderer::Render_queue Renderer::render_queue;

	void Renderer::draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const ShaderProgram& shader)
	{
#ifdef LOG_INFO
		Clerk::Knowledge(20, __FILE__, "Renderer::draw ", L"using shader...");
#endif
		shader.use();
#ifdef LOG_INFO
		Clerk::Knowledge(24, __FILE__, "Renderer::draw ", L"binding vertex array...");
#endif
		vertexArray.bind();
#ifdef LOG_INFO
		Clerk::Knowledge(28, __FILE__, "Renderer::draw ", L"binding index buffer array...");
#endif
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

	void Renderer::render()
	{
		for (auto& object : render_queue)
		{
			object.second->render();
		}
	}

	void Renderer::add_renderObject(GameObject& gameObject)
	{
		render_queue.emplace(gameObject.name, std::make_shared<GameObject>(gameObject));
	}

	void Renderer::remove_object(const std::string& name)
	{
		if (render_queue.contains(name))
			render_queue.erase(name);
		else
		{
			std::wstring convert(name.begin(), name.end());
#ifdef LOG_ERR
			Clerk::Misstep(65, __FILE__, "removeObject", L"can't remove the " + convert + L". It does not exist");
#endif
		}
	}
}