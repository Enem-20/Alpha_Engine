#pragma once

#include "GObject.h"

class AllowedCell : public GObject
{
public:
	AllowedCell();

	void SetSprite(const std::string& spriteName,
		const std::string& textureName,
		const std::string& shaderName,
		const unsigned int spriteWidth,
		const unsigned int spriteHeight,
		const std::string& subTextureName = "default") override;
};