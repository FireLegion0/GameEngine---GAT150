// Engine.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "Engine.h"

// TODO: This is an example of a library function
//void fnEngine()
//{
//	std::cout << "Hello from Engine!\n";
//}

namespace nu {
	//Engine engine;

	bool Engine::Initialize() {
		m_renderer.Initialize("Game Engine", 1280, 1024);
		m_particleSystem.Initialize();
		m_input.Initialize();
		m_audio.Initialize();
		m_physics.Initialize();

		return true;
	}

	void Engine::Shutdown() {
		m_input.Shutdown();
		m_particleSystem.Shutdown();
		m_renderer.Shutdown();
		m_audio.Shutdown();
		m_physics.Shutdown();
	}

	void Engine::Update() {
		m_time.Tick();
		m_input.Update();
		m_particleSystem.Update(m_time.GetDeltaTime());
		m_audio.Update();
		m_physics.Update(m_time.GetDeltaTime());
	}
}