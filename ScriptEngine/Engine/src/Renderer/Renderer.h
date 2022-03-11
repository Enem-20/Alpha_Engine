#pragma once

#include <glm/vec2.hpp>

#include <string>
#include <list>
#include <map>

namespace RenderEngine
{
	class IndexBuffer;
	class VertexArray;
	class ShaderProgram;

	class Renderer
	{
	public:
		static void draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const ShaderProgram& shader);
		static void setClearColor(float r, float g, float b, float a);
		static void clear();
		static void setViewport(unsigned int width, unsigned int height, unsigned int leftOffset, unsigned int bottomOffset);
		static void render();
		
		static void add_renderObject(GameObject& gameObject);
		static void remove_object(const std::string& name);

		static const std::string getRendererStr();
		static const std::string getVersionStr();

		static glm::dvec2 ViewportSize;
		static glm::ivec2 ViewportOffset;
	private:
		typedef std::map<std::string, std::shared_ptr<GameObject>> Render_queue;
		static Render_queue render_queue;
	};
}