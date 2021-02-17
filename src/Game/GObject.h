#pragma once

#include "../Renderer/Sprite.h"
#include "../Renderer/ShaderProgram.h"
//#include "../Components/Component.h"

#include <vector>

class GObject
{
public:
	GObject();
	virtual ~GObject();
	void Translate(const glm::vec3 position);

	void Rotate(const float rotation);

	virtual void render();
	//virtual void update() = 0;

	virtual void SetSprite(const std::string& spriteName,
		const std::string& textureName,
		const std::string& shaderName,
		const unsigned int spriteWidth,
		const unsigned int spriteHeight,
		const std::string& subTextureName = "default");
	virtual std::shared_ptr<Renderer::Sprite> GetSprite();

	//template<class Ty_Component>
	//void AddComponent(Figure* gObject = nullptr, Ty_Component new_component = nullptr);
	//template<class Ty_Component>
	//Component* GetComponent() const;
	////void RemoveComponent(Ty_Component remove_component);

	glm::vec3 position;

	glm::ivec2 cellposition;

	//std::vector<Component*> components;
protected:
	glm::mat4 model;
	std::shared_ptr<Renderer::Sprite> sprite;
	std::shared_ptr<Renderer::ShaderProgram> m_ShaderProgram;
};

//template<class Ty_Component>
//void GObject::AddComponent(Figure* gObject, Ty_Component new_component)
//{
//	if (gObject == nullptr)
//	{
//		gObject = this;
//	}
//	if (new_component == nullptr)
//	{
//		Component* buf_component = new_component;
//		buf_component->gObject = gObject;
//		components.push_back(buf_component);
//		return;
//	}
//	Component* buf_component = static_cast<Component*>(new_component);
//	components.push_back(buf_component);
//}
//template<class Ty_Component>
//Component* GObject::GetComponent() const
//{
//	for (auto it : components)
//	{
//		if (typeid(it).name() == typeid(Ty_Component).name())
//		{
//			return it;
//		}
//	}
//
//	return nullptr;
//}