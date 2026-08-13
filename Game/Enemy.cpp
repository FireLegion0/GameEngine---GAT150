#include "Enemy.h"
#include "Player.h"
#include "../Engine/Renderer.h"
#include "../Engine/Engine.h"
#include "SpaceGame.h"

#include <iostream>

void Enemy::Update(float dt) {
	Player* player = m_scene->GetActorByName<Player>("PlayerProto");
	if (player) {
		nu::Vector2 direction = player->GetTransform().position - m_transform.position;
		float rotation = direction.Angle();
		SetRotation(rotation * nu::RadToDeg);

		nu::Vector2 forward{ 1, 0 };
		forward = forward.Rotate(m_transform.rotation * nu::DegToRad);
		AddVelocity(forward * m_speed * dt);
	}

	nu::Particle particle;
	nu::Vector2 offset{ -20.0f, 0.0f };
	offset = offset.Rotate(m_transform.rotation * nu::DegToRad);
	particle.position = m_transform.position + offset;
	particle.color = { 1.0f, 0.0f, 0.0f };
	particle.lifespan = nu::RandomFloat(0.5f, 1.5f);
	particle.velocity = nu::Vector2{ nu::RandomFloat(-30.0f, -100.0f),0.0f }.Rotate((m_transform.rotation + nu::RandomInt(-30, 30)) * nu::DegToRad); //{ nu::RandomFloat(-200.0f, 200.0f), nu::RandomFloat(-200.0f, 200.0f) };

	nu::Engine::Get().GetPS().AddParticle(particle);

	Actor::Update(dt);
}


void Enemy::OnCollision(Actor* other) {
	//std::cout << other->GetName() << std::endl;

	if (other->GetTag() == "PlayBullet") {
		SetDestroyed(true);
		other->SetDestroyed(true);

		((SpaceGame*)m_scene->GetGame())->AddPoints(100);
		nu::Engine::Get().GetAudio().PlaySound("explode");

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

void Enemy::Read(const nu::json::value_t& value) {
	Actor::Read(value);

	JSON_READ_NAME(value, "speed", m_speed);
}