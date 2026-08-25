#include "pch.h"
#include "TextureFrames.h"
#include "Serialization/Json.h"
#include "Texture.h"

namespace nu {
	bool TextureFrames::Load(const std::string& filename, class Renderer& renderer) {
		json::document_t doc;

		json::Load(filename, doc);

		if (!json::Load(filename, doc)) {
			std::cerr << "Could not load Texture Frames: " << filename << std::endl;
			return false;
		}

		std::string texture_name;
		JSON_READ_REQ(doc, texture_name);
		if (texture_name.empty()) {
			std::cerr << "texture_name cannot be empty." << std::endl;
			return false;
		}

		m_texture = Resources().Get<Texture>(texture_name, renderer);
		if (!m_texture) {
			std::cerr << "Could not load Texture Frame texture: " << texture_name << std::endl;
			return false;
		}

		JSON_READ_NAME(doc, "cols", m_numCols);
		JSON_READ_NAME(doc, "rows", m_numRows);
		JSON_READ_NAME(doc, "start_frame", m_startFrame);
		JSON_READ_NAME(doc, "total_frames", m_totalFrame);

		if (m_numCols <= 0 || m_numRows <= 0) {
			std::cerr << "Cols/Rows cannot be 0: " << m_numCols << "/" << m_numRows << std::endl;
			return false;
		}

		Vector2 textureSize = m_texture->GetSize();
		m_frameSize = textureSize / Vector2{ m_numCols, m_numRows };

		return true;
	}

	Rect TextureFrames::GetFrameRect(unsigned int frame) const {
		if (frame >= m_totalFrame) {
			std::cerr << "Frame" << frame << "out of range : " << std::endl;
			frame = 0;
		}

		int currentFrame = m_startFrame + frame;

		int col = currentFrame % m_numCols;
		int row = currentFrame / m_numCols;

		float x = col * m_frameSize.x;
		float y = row * m_frameSize.y;

		return Rect {
			x,
			y,
			m_frameSize.x,
			m_frameSize.y
		};
	}
}