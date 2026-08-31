#pragma once

#include "Core/Random.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/MathUtils.h"
#include "Core/StringUtils.h"
#include "Math/Transform.h"
#include "Resources/ResourceManager.h"
#include "Resources/Resource.h"
#include "Renderer/Text.h"
#include "Renderer/Font.h"
#include "Physics/Physics.h"

#include "Renderer/Renderer.h"
#include "Input/Input.h"
#include "Core/GameTime.h"
#include "Renderer/Particle.h"
#include "Audio/Audio.h"
#include "Renderer/Texture.h"
#include "Serialization/Json.h"
#include "Core/Factory.h"

#include "Framework/Actor.h"
#include "Framework/Scene.h"
#include "Framework/Game.h"

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
		Physics& GetPhysics() { return m_physics; }

		Engine(const Engine&) = delete;
		Engine& operator = (const Engine&) = delete;
	private:
		Engine() = default;

		Input m_input;
		Renderer m_renderer;
		Audio m_audio;

		Time m_time;
		ParticleSystem m_particleSystem;
		Physics m_physics;
	};

	extern Engine engine;
}