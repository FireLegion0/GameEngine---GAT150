#include "Player.h"
#include "Bullet.h"
#include "Assets.h"
#include "Renderer/Texture.h"
#include "Renderer/Renderer.h"
#include "Components/PhysicsComponent.h"
#include "Engine.h"
#include "SpaceGame.h"

using namespace nu;

FACTORY_REGISTER(Player)

void Player::Update(float dt) {
	float thrust = 0.0f;
	if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = m_speed;
	if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -m_speed;

	float rotate = 0.0f;
	if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -100.0f;
	if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = 100.0f;

	nu::PhysicsComponent* physComp = GetComponent<nu::PhysicsComponent>();
	if (physComp) {
		nu::Vector2 forward{ 1, 0 };
		nu::Vector2 force = forward.Rotate(m_transform.rotation * nu::DegToRad) * thrust;

		physComp->ApplyForce(force);
		physComp->ApplyTorque(rotate);

		nu::Vector2 position = physComp->GetPosition();
		//position.x = Wrap(0.0f, 1280.0f, position.x);
		//position.y = Wrap(0.0f, 1024.0f, position.y);
		//physComp->SetPosition(position);

		nu::Engine::Get().GetRenderer().SetCamera(position);
	}

	SetRotation(m_transform.rotation + rotate * dt);

	nu::Vector2 velocity{ 1, 0 };
	velocity = velocity.Rotate(m_transform.rotation * nu::DegToRad) * thrust;
	//AddVelocity(velocity * dt);

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

		auto bullet = nu::Factory::Instance().Create<Bullet>("BulletProto");
		bullet->SetTransform(m_transform);
		bullet->SetScale(1.25f);
		bullet->SetTag("PlayBullet");

		m_scene->AddActor(std::move(bullet));
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
	bool inv = true;
	if (inv) {
		return;
	}

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