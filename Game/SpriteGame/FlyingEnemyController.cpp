#include "FlyingEnemyController.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorRendererComponent.h"
#include "Core/Factory.h"
#include "Framework/Scene.h"
#include "Damager.h"
#include "Engine.h"

FACTORY_REGISTER(FlyingEnemyController)

void FlyingEnemyController::Start() {
	CharacterBase::Start();

	m_physicsComponent = GetComponent<nu::PhysicsComponent>();
	assert(m_physicsComponent);
	m_rendererComponent = GetComponent<nu::SpriteAnimatorRendererComponent>();
	assert(m_rendererComponent);
}

void FlyingEnemyController::Update(float dt) {
	nu::Vector2 velocity = m_physicsComponent->GetVelocity();

	switch (m_state) {
	case CharacterBase::CharState::Move:
	{
		m_hasAttacked = false;
		auto player = m_scene->GetActorByName<Actor>("PlayerProto");
		if (player) {
			nu::Vector2 position = GetTransform().position;
			nu::Vector2 playerPosition = player->GetTransform().position;

			nu::Vector2 direction = playerPosition - position;

			m_rendererComponent->SetFlipH(direction.x < 0.0f);

			if (direction.Length() < 50.0f) {
				m_state = CharState::Attack;
				m_rendererComponent->Play("attack");
			}

			m_physicsComponent->ApplyForce(direction.Normalized() * 800.0f);
		}
	}
		break;
	case CharacterBase::CharState::Attack:
	{
		if (m_hasAttacked == false && m_rendererComponent->GetFrame() == 3) {
			auto damager = nu::Factory::Instance().Create<Damager>("DamagerProto");
			damager->SetDamage(1.0f);
			damager->SetPosition(GetTransform().position);
			damager->SetTag("EnemyDamager");
			damager->SetScale(1.5f);
			m_scene->AddActor(std::move(damager));
			m_hasAttacked = true;
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
			Damager* damager = dynamic_cast<Damager*>(m_scene->GetActorByName("EnemyDamager"));
			if (damager) {
				m_health -= damager->GetDamage();
			}
			if (m_health <= 0.0f) {
				m_destroyed = true;
			}
		}
	}
		break;
	case CharacterBase::CharState::Death:
	{

	}
		break;
	}

	CharacterBase::Update(dt);
}

void FlyingEnemyController::OnCollision(nu::Actor* other) {
	if (nu::EqualsIgnoreCase(other->GetTag(), "PlayerDamager")) {
		m_state = CharState::Hit;
		m_rendererComponent->Play("hit");
		Damager* damager = dynamic_cast<Damager*>(other);
		if (damager) {
			m_health -= damager->GetDamage();
		}
		if (m_health <= 0.0f) {
			m_destroyed = true;
		}

		other->SetDestroyed(true);
	}
}

void FlyingEnemyController::Read(const nu::json::value_t& value) {
	CharacterBase::Read(value);
}
