#pragma once

#include "Random.h"
#include "Vector2.h"
#include "Vector3.h"
#include "MathUtils.h"
#include "Transform.h"
#include "Text.h"
#include "Font.h"

#include "Renderer.h"
#include "Input.h"
#include "GameTime.h"
#include "Particle.h"
#include "Audio.h"
#include "Texture.h"

#include "Actor.h"
#include "Scene.h"
#include "Game.h"

#define ENGINE Engine::Get()

namespace nu {
	class Engine {
	public:
		static Engine& Get() { static Engine engine; return engine; }

		bool Initialize();
		void Shutdown();

		void Update();

		Input& GetInput() { return m_input; }
		Renderer& GetRenderer() { return m_renderer; }
		Time& GetTime() { return m_time; }
		ParticleSystem& GetPS() { return m_particleSystem; }
		Audio& GetAudio() { return m_audio; }

		Engine(const Engine&) = delete;
		Engine& operator = (const Engine&) = delete;
	private:
		Engine() = default;

		Input m_input;
		Renderer m_renderer;
		Audio m_audio;

		Time m_time;
		ParticleSystem m_particleSystem;
	};

	extern Engine engine;
}