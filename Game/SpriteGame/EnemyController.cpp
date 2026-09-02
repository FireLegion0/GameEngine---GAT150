#include "EnemyController.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorRendererComponent.h"
#include "Core/Factory.h"
#include "Framework/Scene.h"
#include "Damager.h"
#include "Engine.h"

FACTORY_REGISTER(EnemyController)

void EnemyController::Start() {
	CharacterBase::Start();

	m_physicsComponent = GetComponent<nu::PhysicsComponent>();
	assert(m_physicsComponent);
	m_rendererComponent = GetComponent<nu::SpriteAnimatorRendererComponent>();
	assert(m_rendererComponent);
}

void EnemyController::Update(float dt) {
	nu::Vector2 velocity = m_physicsComponent->GetVelocity();
	switch (m_state) {
	case CharacterBase::CharState::Move:
	{

		float dir = 0.0f;
		auto player = m_scene->GetActorByName("PlayerProto");
		if (player) {
			nu::Vector2 position = GetTransform().position;
			nu::Vector2 playerPosition = player->GetTransform().position;

			if (playerPosition.x < position.x) {
				dir = -1.0f;
			}
			else if (playerPosition.x > position.x) {
				dir = 1.0f;
			}
		}

		if (dir != 0.0f) {
			velocity.x = dir * 50.0f;
			m_rendererComponent->Play("run");
			m_rendererComponent->SetFlipH(dir < 0.0f);
		}
		else {
			m_rendererComponent->Play("idle");
		}

	}
	break;
	case CharacterBase::CharState::Attack:
	{

		if (m_rendererComponent->GetFrame() == 3) {
			auto damager = nu::Factory::Instance().Create<Actor>("DamagerProto");
			damager->SetPosition(GetTransform().position);
			damager->SetTag("EnemyDamager");
			m_scene->AddActor(std::move(damager));
		}
		if (m_rendererComponent->IsAnimationDone()) {
			m_state = CharState::Move;
			m_rendererComponent->Play("idle");
		}

	}
	break;
	case CharacterBase::CharState::Hit:
	{
		if (m_rendererComponent->IsAnimationDone()) {
			m_state = CharState::Move;
			m_rendererComponent->Play("idle");
		}
	}
		break;
	case CharacterBase::CharState::Death:
		break;
	}

	

	m_physicsComponent->SetVelocity(velocity);

	CharacterBase::Update(dt);
}

void EnemyController::OnCollision(nu::Actor* other) {
	if (nu::EqualsIgnoreCase(other->GetTag(), "PlayerDamager")) {
		m_state = CharState::Hit;
		m_rendererComponent->Play("hit");
		Damager* damager = dynamic_cast<Damager*>(other);
		if(damager) {
			m_health -= damager->GetDamage();
		}
		if (m_health <= 0.0f) {
			m_destroyed = true;
		}

		other->SetDestroyed(true);
	}
}

void EnemyController::Read(const nu::json::value_t& value) {
	CharacterBase::Read(value);
}
