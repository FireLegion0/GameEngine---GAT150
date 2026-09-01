#include "pch.h"
#include "SpriteAnimationRendererComponent.h"
#include "Renderer/textureFrames.h"
#include "Math/MathUtils.h"
#include "Math/Transform.h"
#include "Framework/Actor.h"
#include "Engine.h"

namespace nu {
	FACTORY_REGISTER(SpriteAnimationRendererComponent)



	void SpriteAnimationRendererComponent::Start(){
		if (!m_textureFramesName.empty()) {
			m_textureFrames = Resources().Get<TextureFrames>(m_textureFramesName, Engine::Get().GetRenderer());
			if (m_textureFrames) {
				m_sourceRect = m_textureFrames->GetFrameRect(0);
				m_size = Vector2{ m_sourceRect.w, m_sourceRect.h };
				m_texture = m_textureFrames->GetTexture();
			}
			if (!m_textureFrames) {
				std::cerr << "Texture Frames Not Loaded." << m_textureFramesName << " (Read)" << std::endl;
				return;
			}
		}
	}

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

		m_sourceRect = m_textureFrames->GetFrameRect(m_frame);
	}

	void SpriteAnimationRendererComponent::Read(const json::value_t& value){
		RendererComponent::Read(value);

		JSON_READ_NAME_REQ(value, "fps", m_fps);
		JSON_READ_NAME(value, "loop", m_loop);

		std::string textureFrames;
		JSON_READ_NAME_REQ(value, "textureFrames", m_textureFramesName);
	}
}
