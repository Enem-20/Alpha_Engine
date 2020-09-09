#include "AnimatedSprite.h"
#include "Texture2D.h"
#include <iostream>

namespace Renderer
{
	AnimatedSprite::AnimatedSprite(std::shared_ptr<Texture2D> Texture,
		std::string initialSubTexture,
		std::shared_ptr<ShaderProgram> shaderProgram,
		const glm::vec2& position,
		const glm::vec2& size,
		const float rotation)
		: Sprite (std::move(Texture), std::move(initialSubTexture), std::move(shaderProgram), position, size, rotation)
	{
		m_CurrentAnimationDurations = m_statesMap.end();

	}

	void AnimatedSprite::insertState(std::string state, std::vector<std::pair<std::string, uint64_t>> subTexturesDuration)
	{
		m_statesMap.emplace(std::move(state), std::move(subTexturesDuration));
	}
	

	void AnimatedSprite::render() const
	{
		if (m_dirty)
		{
			auto subTexture = m_Texture->getSubTexture(m_CurrentAnimationDurations->second[m_currentFrame].first);

			GLfloat textureCoords[] =
			{
				//u  v
				subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
				subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
				subTexture.rightTopUV.x, subTexture.rightTopUV.y,

				subTexture.rightTopUV.x, subTexture.rightTopUV.y,
				subTexture.rightTopUV.x, subTexture.leftBottomUV.y,
				subTexture.leftBottomUV.x, subTexture.leftBottomUV.y
			};

			glBindBuffer(GL_ARRAY_BUFFER, m_textureCoordsVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(textureCoords), &textureCoords);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			m_dirty = false;
		}

		Sprite::render();
	}
	
	
	void AnimatedSprite::setState(const std::string& newState)
	{
		auto it = m_statesMap.find(newState);

		if (it == m_statesMap.end())
		{
			std::cout << "Can't find animation state: " << newState << std::endl;
			return;
		}

		if (it != m_CurrentAnimationDurations)
		{
			m_currentAnimationTime = 0;
			m_currentFrame = 0;
			m_CurrentAnimationDurations = it;
			m_dirty = true;
		}
	}
	
	void AnimatedSprite::Update(const uint64_t deltaTime) 
	{
		if (m_CurrentAnimationDurations != m_statesMap.end())
		{
			m_currentAnimationTime += deltaTime;

			while (m_currentAnimationTime >= m_CurrentAnimationDurations->second[m_currentFrame].second)
			{
				m_currentAnimationTime -= m_CurrentAnimationDurations->second[m_currentFrame].second;
				++m_currentFrame;
				m_dirty = true;
				if (m_currentFrame == m_CurrentAnimationDurations->second.size())
				{
					m_currentFrame = 0;
				}
			}
		}
	}

}