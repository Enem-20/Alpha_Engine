#include "Mesh.h"

#include "ResourceManager.h"

Mesh::Mesh(const std::string& name) : ResourceBase(name) 
{
	ResourceManager::addResource<Mesh>(this);
}

Mesh::Mesh(const std::string& name, const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
	: vertices(vertices)
	, indices(indices)
	, ResourceBase(name)
{
	ResourceManager::addResource<Mesh>(this);
}

Mesh::Mesh(std::string&& name, std::vector<Vertex>&& vertices, std::vector<uint32_t>&& indices) noexcept
	: vertices(std::move(vertices))
	, indices(std::move(indices))
	, ResourceBase(std::move(name))
{
	ResourceManager::addResource<Mesh>(this);
}

Mesh::Mesh(const Mesh& model) 
	: vertices(model.vertices)
	, indices(model.indices)
	, ResourceBase(model.name)
{
	ResourceManager::addResource<Mesh>(this);
}

Mesh::Mesh(Mesh&& model) noexcept
	: vertices(std::move(model.vertices))
	, indices(std::move(model.indices))
	, ResourceBase(std::move(model.name))
{
	ResourceManager::addResource<Mesh>(this);
}