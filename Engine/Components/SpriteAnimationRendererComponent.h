#pragma once
#include "RenderComponent.h"
#include "Resources/Resource.h"

namespace nu {
	class SpriteAnimationRendererComponent : public RendererComponent {
	public:
		CLASS_PROTO(SpriteAnimationRendererComponent)

		void Update(float dt) override;
		void Draw(const Renderer& renderer) override;
		void Read(const json::value_t& value) override;

	private:
		float m_fps = 1.0f;
		bool m_loop = true;

		unsigned int m_frame = 0;
		float m_frameTimer = 0;

		res_t<class TextureFrames> m_textureFrames;
	};
}