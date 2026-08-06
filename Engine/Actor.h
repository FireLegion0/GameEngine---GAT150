#pragma once
#include "Transform.h"
#include "Model.h"
#include "Resource.h"
#include <string>
#include <memory>

namespace nu {

    class Scene;
    class Texture;

    struct ActorDesc {
        std::string name;
        std::string tag;

        Transform transform;
        Vector2 velocity{ 0.0f, 0.0f };
        float damping{ 0.0f };
        float lifespan{ 0 };
        bool destroyed{ false };

        res_t<Model> model;
		res_t<Texture> texture;
    };

    class Actor {
    public:
        Actor() = default;
        Actor(const ActorDesc& actorDesc) :
            m_name{actorDesc.name},
            m_tag{actorDesc.tag},
            m_transform{ actorDesc.transform },
            m_velocity{ actorDesc.velocity },
            m_damping{ actorDesc.damping },
            m_lifespan{ actorDesc.lifespan },
            m_model{ actorDesc.model },
            m_texture{ actorDesc.texture }
        { }

        virtual void Update(float dt);
        virtual void Draw(const class Renderer& renderer) const; 

        virtual void OnCollision(Actor* other) {}

        const Transform& GetTransform() const { return m_transform; }
        void SetPosition(const Vector2& position) { m_transform.position = position; }
        void SetRotation(float rotation) { m_transform.rotation = rotation; }
        void SetScale(float scale) { m_transform.scale = scale; }

        const Vector2& GetVelocity() const { return m_velocity; }
        void SetVelocity(const Vector2& velocity) { m_velocity = velocity; }
        void AddVelocity(const Vector2& velocity) { m_velocity += velocity; }

        const std::string& GetName() const { return m_name; }
        const std::string& GetTag() const { return m_tag; }

        Scene* GetScene() { return m_scene; }

        float GetRadius() const;

        void SetDestroyed(bool destroy) { m_destroyed = true; };
        bool GetDestroyed() const { return m_destroyed; }

        friend Scene;

    protected:
        std::string m_name;
        std::string m_tag;

        Transform m_transform;
        Vector2 m_velocity{ 0.0f, 0.0f };
        float m_damping{ 0.0f };
        float m_lifespan{ 0 };
        bool m_destroyed{ false };

        res_t<Model> m_model;
        res_t<Texture> m_texture;

        Scene* m_scene{ nullptr };
    };
}