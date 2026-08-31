#include "Bullet.h"
#include "Math/MathUtils.h"
#include "Core/Factory.h"
#include "Components/PhysicsComponent.h"

FACTORY_REGISTER(Bullet)

void Bullet::Update(float dt) {
	nu::Vector2 forward{ 1.0f, 0.0f };
	nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::DegToRad) * m_speed;

	//SetVelocity(velocity);

	nu::PhysicsComponent* physComp = GetComponent<nu::PhysicsComponent>();
	if (physComp) {
		nu::Vector2 forward{ 1, 0 };
		nu::Vector2 force = forward.Rotate(m_transform.rotation * nu::DegToRad) * m_speed;
		physComp->SetVelocity(velocity);
	}

	Actor::Update(dt);
}
void Bullet::Read(const nu::json::value_t& value) {
	Actor::Read(value);

	JSON_READ_NAME(value, "speed", m_speed);
}