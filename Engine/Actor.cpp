#include "pch.h"
#include "Actor.h"
#include "Renderer.h"
#include "Texture.h"
#include "MathUtils.h"

namespace nu {
	void Actor::Update(float dt) {
        //lifespan
        if (m_lifespan > 0.0f) {
            m_lifespan -= dt;
            m_destroyed = (m_lifespan <= 0.0f);
        }

        //physics
        m_transform.position += (m_velocity * dt);
        m_velocity *= 1.0f / ((1.0f) + m_damping * dt);

        m_transform.position.x = Wrap(0.0f, 1280.0f, m_transform.position.x);
        m_transform.position.y = Wrap(0.0f, 1024.0f, m_transform.position.y);
    }

	void Actor::Draw(const Renderer& renderer) const {
        if(m_model){
            renderer.DrawModel(*m_model, m_transform);
        }
        if (m_texture) {
            renderer.DrawTexture(*m_texture,
                m_transform.position.x,
                m_transform.position.y,
                m_transform.rotation,
                m_transform.scale);
        }
    }

    float Actor::GetRadius() const {
        if (m_model) {
            return m_model->GetRadius() * m_transform.scale * 0.7f;
        }
        if (m_texture) {
            return (m_texture->GetSize().Length() * 0.5f) * 0.5f;
        }
        return 0.0f;
    }

	void Actor::Read(const json::value_t& value) {
		Object::Read(value);

        if (JSON_HAS_NAME(value, "transform")) {
            m_transform.Read(JSON_GET_NAME(value, "transform"));
        }

        JSON_READ_NAME(value, "tag", m_tag);
        JSON_READ_NAME(value, "lifespan", m_lifespan);
        JSON_READ_NAME(value, "velocity", m_velocity);
        JSON_READ_NAME(value, "damping", m_damping);
	}
}