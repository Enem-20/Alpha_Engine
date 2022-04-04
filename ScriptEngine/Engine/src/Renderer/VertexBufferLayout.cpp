#include "VertexBufferLayout.h"


VertexBufferLayout::VertexBufferLayout()
	: m_stride(0)
{

}

void VertexBufferLayout::reserveElements(const size_t count)
{
	m_LayoutElements.reserve(count);
}
void VertexBufferLayout::addElementLayoutFloat(const unsigned int count, const bool normalized)
{
	m_LayoutElements.push_back({ static_cast<GLint>(count), GL_FLOAT, normalized });
	m_stride += m_LayoutElements.back().size;
}
