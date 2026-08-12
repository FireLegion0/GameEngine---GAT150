#include "Player.h"
#include "Bullet.h"
#include "Assets.h"
#include "../Engine/Texture.h"
#include "../Engine/Renderer.h"
#include "../Engine/Engine.h"
#include "SpaceGame.h"

using namespace nu;

void Player::Update(float dt) {
	float thrust = 0.0f;
	if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = m_speed;
	if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -m_speed;

	float rotate = 0.0f;
	if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -100.0f;
	if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = 100.0f;

	SetRotation(m_transform.rotation + rotate * dt);

	nu::Vector2 velocity{ 1, 0 };
	velocity = velocity.Rotate(m_transform.rotation * nu::DegToRad) * thrust;
	AddVelocity(velocity * dt);

	if (thrust) {
		nu::Particle particle;
		nu::Vector2 offset{ -20.0f, 0.0f };
		offset = offset.Rotate(m_transform.rotation * nu::DegToRad);
		particle.position = m_transform.position + offset;
		nu::Color colors[3] = { {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f} };
		particle.color = colors[nu::RandomInt(3)];
		particle.lifespan = nu::RandomFloat(0.5f, 1.5f);
		particle.velocity = nu::Vector2{ nu::RandomFloat(-30.0f, -100.0f),0.0f}.Rotate((m_transform.rotation + nu::RandomInt(-30, 30)) * nu::DegToRad); //{ nu::RandomFloat(-200.0f, 200.0f), nu::RandomFloat(-200.0f, 200.0f) };

		nu::Engine::Get().GetPS().AddParticle(particle);
	}

	if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {

		nu::Engine::Get().GetAudio().PlaySound("shoot"); //For Later

		BulletDesc desc;
		desc.name = "Bullet";
		desc.tag = "PlayBullet";
		//desc.model = assets::bulletModel;
		desc.texture = Resources().Get<Texture>("textures/bullet.png", Engine::Get().GetRenderer());
		desc.transform = m_transform;
		desc.transform.scale = 1;
		desc.speed = 1250.0f;
		desc.lifespan = 1.0f;

			//Bullet* bullet = new Bullet{ desc };
			m_scene->AddActor(std::move(std::make_unique<Bullet>(desc)));

			desc.transform.rotation += 20.0f;
			//bullet = new Bullet{ desc };
			m_scene->AddActor(std::move(std::make_unique<Bullet>(desc)));

			desc.transform.rotation += 20.0f;
			//bullet = new Bullet{ desc };
			m_scene->AddActor(std::move(std::make_unique<Bullet>(desc)));

			desc.transform.rotation -= 60.0f;
			//bullet = new Bullet{ desc };
			m_scene->AddActor(std::move(std::make_unique<Bullet>(desc)));

			desc.transform.rotation -= 20.0f;
			//bullet = new Bullet{ desc };
			m_scene->AddActor(std::move(std::make_unique<Bullet>(desc)));
	}

	if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_X)) {
		nu::Engine::Get().GetTime().SetTimeScale(0.5f);
	}
	else {
		nu::Engine::Get().GetTime().SetTimeScale(1.0f);
	}

	Actor::Update(dt);
}

void Player::OnCollision(Actor* other) {
	if (other->GetTag() == "Enemy" || other->GetTag() == "Astroid") {
		nu::Engine::Get().GetAudio().PlaySound("explode");
		SetDestroyed(true);
		other->SetDestroyed(true);
		((SpaceGame*)m_scene->GetGame())->OnPlayerDeath();
	}
}

void Player::Read(const nu::json::value_t& value) {
	Actor::Read(value);

	JSON_READ_NAME(value, "speed", m_speed);
}