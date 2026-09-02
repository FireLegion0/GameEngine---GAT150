#pragma once
#include "Framework/Actor.h"

class Damager : public nu::Actor {
public:
	CLASS_PROTO(Damager);

	void Read(const nu::json::value_t& value) override;

	float GetDamage() { return m_damage; }
	void SetDamage(float damage) { m_damage = damage; }

protected:
	float m_damage{ 1.0f };
};