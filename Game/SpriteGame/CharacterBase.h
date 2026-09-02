#pragma once
#include "Framework/Actor.h"

class CharacterBase : public nu::Actor {
public:
	enum class CharState {
		Move,
		Attack,
		Hit,
		Death
	};

	void Read(const nu::json::value_t& value) override;

protected:
	CharState m_state{ CharState::Move };
	float m_stateTimer{ 0.0f };
	float m_health{ 10.0f };
};