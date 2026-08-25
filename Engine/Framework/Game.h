#pragma once


namespace nu {
	class Scene;
	
	class Game {
	public:
		Game() = default;
		Game(Scene* scene) :
			m_scene{ scene }
		{ }

		virtual bool Initialize() { return true; }
		virtual void Shutdown() {}

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer);

		void SetScene(Scene* scene) { m_scene = scene; }

	protected:
		Scene* m_scene = nullptr;
	};
}