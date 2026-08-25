#pragma once
#include "RenderComponent.h"
#include "Resources/Resource.h"
#include "Renderer/Texture.h"

namespace nu {
	class SpriteRendererComponent : public RendererComponent {
	public:
		CLASS_PROTO(SpriteRendererComponent)

		void Draw(const Renderer& renderer) override;

		virtual void Read(const json::value_t& value) override;
	protected:
		res_t<Texture> m_texture;

	};
}