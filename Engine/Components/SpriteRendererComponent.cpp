#include "pch.h"
#include "SpriteRendererComponent.h"
#include "../Renderer.h"
#include "../Actor.h"
#include "../ResourceManager.h"
#include "../Engine.h"

namespace nu {
	FACTORY_REGISTER(SpriteRendererComponent)

	void SpriteRendererComponent::Draw(const Renderer& renderer){
		renderer.DrawTexture(*m_texture,
			GetOwner()->GetTransform().position.x,
			GetOwner()->GetTransform().position.y,
			GetOwner()->GetTransform().rotation,
			GetOwner()->GetTransform().scale
		);
	}

	void SpriteRendererComponent::Read(const json::value_t& value) {
		RendererComponent::Read(value);

		std::string textureName;
		JSON_READ_NAME(value, "texture", textureName);
		if (!textureName.empty()) {
			m_texture = Resources().Get<Texture>(textureName, Engine::Get().GetRenderer());
		}
	}
}
