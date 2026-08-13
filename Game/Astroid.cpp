#include "Astroid.h"
#include "../Engine/Renderer.h"
#include "../Engine/Engine.h"
#include "SpaceGame.h"

#include <iostream>

void Astroid::Update(float dt) {
	Actor::Update(dt);
}

void Astroid::OnCollision(Actor* other) {
	//std::cout << other->GetName() << std::endl;

	if (other->GetTag() == "PlayBullet") {
		SetDestroyed(true);
		other->SetDestroyed(true);

		((SpaceGame*)m_scene->GetGame())->AddPoints(1000);

		for (int i = 0; i < 100; i++)
		{
			nu::Particle particle;
			particle.position = m_transform.position;
			particle.color = { 1.0f, 1.0f, 1.0f };
			particle.lifespan = nu::RandomFloat(0.5f, 2.0f);
			particle.velocity = { nu::RandomFloat(-600.0f, 600.0f), nu::RandomFloat(-600.0f, 600.0f) };

			nu::Engine::Get().GetPS().AddParticle(particle);
		}
	}
}

void Astroid::Read(const nu::json::value_t& value) {
	Actor::Read(value);

	JSON_READ_NAME(value, "speed", m_speed);
}