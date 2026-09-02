#include "PlayerController.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorRendererComponent.h"
#include "Core/Factory.h"
#include "Framework/scene.h"
#include "Damager.h"
#include "Engine.h"

FACTORY_REGISTER(PlayerController)

void PlayerController::Start(){
	CharacterBase::Start();

	m_physicsComponent = GetComponent<nu::PhysicsComponent>();
	assert(m_physicsComponent);
	m_rendererComponent = GetComponent<nu::SpriteAnimatorRendererComponent>();
	assert(m_rendererComponent);
}

void PlayerController::Update(float dt){
	nu::Vector2 velocity = m_physicsComponent->GetVelocity();

	switch (m_state) {
	case CharacterBase::CharState::Move:
	{
		float dir = 0.0f;
		if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) dir = -1.0f;
		if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) dir = 1.0f;

		if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
			velocity.y = -800.0f;
		}

		if (dir != 0.0f) {
			velocity.x = dir * 100.0f;
			m_rendererComponent->Play("run");
			m_rendererComponent->SetFlipH(dir < 0.0f);
		}
		else {
			m_rendererComponent->Play("idle");
		}


		if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_RSHIFT)) {
			m_state = CharState::Attack;
			m_rendererComponent->Play("attack");
		}
	}
		break;
	case CharacterBase::CharState::Attack:
	{
		if (m_rendererComponent->IsAnimationDone()) {
			m_state = CharState::Move;
			m_rendererComponent->Play("idle");

			auto damager = nu::Factory::Instance().Create<Damager>("DamagerProto");
			damager->SetPosition(GetTransform().position + nu::Vector2{ (m_rendererComponent->GetFlipH() ? -100.0f : 100.0f), 0.0f });
			damager->SetTag("PlayerDamager");
			m_scene->AddActor(std::move(damager));
		}
	}
		break;
	case CharacterBase::CharState::Hit:
		if (m_rendererComponent->IsAnimationDone()) {
			m_state = CharState::Move;
			m_rendererComponent->Play("idle");
		}
		break;
	case CharacterBase::CharState::Death:
		break;
	}
	
	m_physicsComponent->SetVelocity(velocity);
	nu::Engine::Get().GetRenderer().SetCamera(m_physicsComponent->GetPosition());

	CharacterBase::Update(dt);
}

void PlayerController::OnCollision(nu::Actor* other){
	if (nu::EqualsIgnoreCase(other->GetTag(), "EnemyDamager")) {
		m_state = CharState::Hit;
		m_rendererComponent->Play("death");
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

void PlayerController::Read(const nu::json::value_t& value){
	CharacterBase::Read(value);
}
