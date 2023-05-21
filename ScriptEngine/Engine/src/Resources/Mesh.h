#pragma once

#ifndef MODEL
#define MODEL

#include "../../internal/Renderer/src/Vulkan/Vertex.h"
#include "ResourceBase.h"

#include <vector>
#include <string>

struct Mesh : ResourceBase{
	Mesh(const std::string& name);
	Mesh(const std::string& name, const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
	Mesh(std::string&& name, std::vector<Vertex>&& vertices, std::vector<uint32_t>&& indices) noexcept;
	Mesh(const Mesh& model);
	Mesh(Mesh&& model) noexcept;

	std::vector<Vertex> vertices{};
	std::vector<uint32_t> indices{};

	inline static const std::string& type = GETTYPE(Mesh);
};

#endif