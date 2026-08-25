#include "pch.h"
#include "SpriteAnimationRendererComponent.h"
#include "Renderer/TextureFrames.h"
#include "Math/MathUtils.h"
#include "Engine.h"

namespace nu {
	FACTORY_REGISTER(SpriteAnimationRendererComponent)

	void SpriteAnimationRendererComponent::Update(float dt){
		if (!m_textureFrames) {
			std::cerr << "Texture Frames Not Found. (Update)" << std::endl;
			return;
		}

		m_frameTimer += dt;
		float frameTime = 1.0f/m_fps;

		while (m_frameTimer >= frameTime) {
			m_frame++;
			if (m_loop) {
				m_frame = m_frame % m_textureFrames->GetTotalFrames();
			}
			else {
				m_frame = Clamp(0u, m_textureFrames->GetTotalFrames() - 1, m_frame);

				if (m_frame >= m_textureFrames->GetTotalFrames() - 1) {
					m_frame = m_textureFrames->GetTotalFrames() - 1;
				}
			}

			m_frameTimer -= frameTime;
		}
	}

	void SpriteAnimationRendererComponent::Draw(const Renderer& renderer){
		if (!m_textureFrames) {
			std::cerr << "Texture Frames Not Found. (Draw)" << std::endl;
			return;
		}

		auto transform = GetOwner()->GetTransform();

		Rect rect = m_textureFrames->GetFrameRect(m_frame);
		renderer.DrawTexture(
			*m_textureFrames->GetTexture(),
			rect,
			transform.position.x, 
			transform.position.y,
			transform.rotation,
			transform.scale);
	}

	void SpriteAnimationRendererComponent::Read(const json::value_t& value){
		RendererComponent::Read(value);

		JSON_READ_NAME_REQ(value, "fps", m_fps);
		JSON_READ_NAME(value, "loop", m_loop);

		std::string textureFrames;
		JSON_READ_REQ(value, textureFrames);

		if (!textureFrames.empty()) {
			m_textureFrames = Resources().Get<TextureFrames>(textureFrames, Engine::Get().GetRenderer());
			if (!m_textureFrames) {
				std::cerr << "Texture Frames Not Loaded." << textureFrames << " (Read)" << std::endl;
				return;
			}
		}
	}
}
