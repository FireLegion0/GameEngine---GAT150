#pragma once
#include "Framework/Actor.h"

struct BulletDesc : public nu::ActorDesc {
    float speed;
};

class Bullet : public nu::Actor {
public:
    Bullet() = default;
    Bullet(const BulletDesc& BulletDesc) :
        Actor{ BulletDesc },
        m_speed{ BulletDesc.speed }
    {
    }

    CLASS_PROTO(Bullet)

    void Update(float dt) override;

    void Read(const nu::json::value_t& value) override;

private:
    int m_ammo = 0;
    float m_speed = 0.0f;
};