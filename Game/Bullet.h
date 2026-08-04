#pragma once
#include "../Engine/Actor.h"

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

    void Update(float dt) override;
    //void Draw(const class nu::Renderer& renderer) const override;
private:
    int m_ammo = 0;
    float m_speed = 0.0f;
};