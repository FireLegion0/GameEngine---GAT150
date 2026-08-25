#pragma once
#include "Framework/Actor.h"

struct BossDesc : public nu::ActorDesc {
    float speed;
    int health = 3;
};

class Boss : public nu::Actor {
public:
    Boss() = default;
    Boss(const BossDesc& bossDesc) :
        Actor{ bossDesc },
        m_speed{ bossDesc.speed },
        m_health{ bossDesc.health }
    {
    }

    CLASS_PROTO(Boss)

    void Update(float dt) override;
    void OnCollision(Actor* other) override;

    void Read(const nu::json::value_t& value) override;

private:
    int m_ammo = 0;
    int m_health = 3;
    float m_speed = 200.0f;
};