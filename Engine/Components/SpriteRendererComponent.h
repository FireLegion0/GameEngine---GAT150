#pragma once
#include "RenderComponent.h"
#include "Resources/Resource.h"
#include "Renderer/Texture.h"
#include "Math/Rect.h"

namespace nu {
	class SpriteRendererComponent : public RendererComponent {
	public:
		CLASS_PROTO(SpriteRendererComponent)

		void Start() override;
		void Draw(const Renderer& renderer) override;

		const Vector2& GetSize() { return m_size; }

		bool GetFlipH() const { return m_flipH; }
		void SetFlipH(bool flipH = true) { m_flipH = flipH; }

		virtual void Read(const json::value_t& value) override;
	protected:
		std::string m_textureName;
		Rect m_sourceRect;
		Vector2 m_size{ 0.0f, 0.0f };
		bool m_flipH = false;

		res_t<Texture> m_texture;
	};
}