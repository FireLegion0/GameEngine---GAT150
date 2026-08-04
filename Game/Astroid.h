#pragma once
#include "../Engine/Actor.h"

struct AstroidDesc : public nu::ActorDesc {
	float speed;
};

class Astroid : public nu::Actor {
public:
	Astroid() = default;
    Astroid(const AstroidDesc& astroidDesc) :
        Actor{ astroidDesc },
        m_speed{ astroidDesc.speed }
    {
    }

    void Update(float dt) override;
    void OnCollision(Actor* other) override;
private:
    float m_speed = 100.0f;
};