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
    Bullet(float speed, const nu::Transform& transform) :
        Actor{ transform },
        m_speed{ speed }
    {
    }
    Bullet(float speed, const nu::Transform& transform, const nu::Model& model) :
        Actor{ transform, model },
        m_speed{ speed }
    {
    }

    void Update(float dt) override;
    //void Draw(const class nu::Renderer& renderer) const override;
private:
    int m_ammo = 0;
    float m_speed = 0.0f;
};