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
    Astroid(float speed, const nu::Transform& transform) :
        Actor{ transform },
        m_speed{ speed }
    {
    }
    Astroid(float speed, const nu::Transform& transform, const nu::Model& model) :
        Actor{ transform, model },
        m_speed{ speed }
    {
    }

    void Update(float dt) override;
    void OnCollision(Actor* other) override;
private:
    float m_speed = 100.0f;
};