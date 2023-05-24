#include "Mesh.h"

#include "ResourceManager.h"

Mesh::Mesh(const std::string& name, const std::string& path) 
	: ResourceBase(name)
	, path(path)
{
	ResourceManager::addResource<Mesh>(this);
}

Mesh::Mesh(const std::string& name, const std::string& path, const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
	: vertices(vertices)
	, indices(indices)
	, path(path)
	, ResourceBase(name)
{
	ResourceManager::addResource<Mesh>(this);
}

Mesh::Mesh(std::string&& name, std::string&& path, std::vector<Vertex>&& vertices, std::vector<uint32_t>&& indices) noexcept
	: vertices(std::move(vertices))
	, indices(std::move(indices))
	, path(std::move(path))
	, ResourceBase(std::move(name))
{
	ResourceManager::addResource<Mesh>(this);
}

Mesh::Mesh(const Mesh& model) 
	: vertices(model.vertices)
	, indices(model.indices)
	, path(model.path)
	, ResourceBase(model.name)
{
	ResourceManager::addResource<Mesh>(this);
}

Mesh::Mesh(Mesh&& model) noexcept
	: vertices(std::move(model.vertices))
	, indices(std::move(model.indices))
	, path(std::move(model.path))
	, ResourceBase(std::move(model.name))
{
	ResourceManager::addResource<Mesh>(this);
}