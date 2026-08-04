#pragma once
#include "Vector2.h"
#include <string>

struct SDL_Texture;

namespace nu
{
	class Texture
	{
	public:
		Texture() = default;
		~Texture();

		bool Load(const std::string& filename, class Renderer& renderer);

		nu::Vector2 GetSize();

		friend class Renderer;

	private:
		SDL_Texture* m_texture{ nullptr };
	};
}