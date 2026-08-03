#include "pch.h"
#include "Renderer.h"
#include "Transform.h"
#include "Model.h"
#include "MathUtils.h"

#include <iostream>
#include "input.h"

namespace nu {
	bool Renderer::Initialize(const char* name, int width, int height) {
		m_width = width;
		m_height = height;

        SDL_Init(SDL_INIT_VIDEO);

		if (!TTF_Init()) {
			std::cerr << "TTF_Init Error: " << SDL_GetError() << std::endl;
			return false;
		}

        m_window = SDL_CreateWindow(name, width, height, 0);
        if (m_window == nullptr) {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return false;
        }

        m_renderer = SDL_CreateRenderer(m_window, NULL);
        if (m_renderer == nullptr) {
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return false;
        }

		SDL_SetRenderVSync(m_renderer, 1);

		return true;
	}

	void Renderer::Shutdown() {
		TTF_Quit();
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}

	void Renderer::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const {
		SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
	}

	void Renderer::SetColor(float r, float g, float b, float a) const {
		SDL_SetRenderDrawColorFloat(m_renderer, r, g, b, a);
	}

	void Renderer::Clear() {
		SDL_RenderClear(m_renderer);
	}

	void Renderer::Present() {
		SDL_RenderPresent(m_renderer);
	}

	void Renderer::DrawPoint(float x, float y) const {
		SDL_RenderPoint(m_renderer, x, y);
	}

	void Renderer::DrawFillRect(float x, float y, float w, float h) const {
		SDL_FRect rect = { x, y, w, h };
		SDL_RenderFillRect(m_renderer, &rect);
	}

	void Renderer::DrawRect(float x, float y, float w, float h) const {
		SDL_FRect rect = { x, y, w, h };
		SDL_RenderRect(m_renderer, &rect);
	}

	void Renderer::DrawLine(float x1, float y1, float x2, float y2) const {
		SDL_RenderLine(m_renderer, x1, y1, x2, y2);
	}

	void Renderer::DrawModel(const Model& model, const Transform& transform) const {
		for (auto mesh : model.GetMeshes()) {
			SetColor(mesh.GetColor().r, mesh.GetColor().g, mesh.GetColor().b, 1.0f);

			auto& points = mesh.GetPoints();
			for (int i = 0; i + 1 < mesh.GetPoints().size(); i++) {
				Vector2 v1 = points[i];
				Vector2 v2 = points[i + 1];

				v1 *= transform.scale;
				v2 *= transform.scale;

				v1 = v1.Rotate(transform.rotation * DegToRad);
				v2 = v2.Rotate(transform.rotation * DegToRad);

				v1 += transform.position;
				v2 += transform.position;

				DrawLine(v1.x, v1.y, v2.x, v2.y);
			}
		}
	}
}