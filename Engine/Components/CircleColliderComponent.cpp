#include "pch.h"
#include "CircleColliderComponent.h"
#include "Core/Factory.h"
#include "Framework/Actor.h"

namespace nu {
    FACTORY_REGISTER(CircleColliderComponent)

    bool CircleColliderComponent::CheckCol(const ColliderComponent& other) {
        const CircleColliderComponent* circleCollider = dynamic_cast<const CircleColliderComponent*>(&other);
        if (!circleCollider) return false;

        float dist = GetOwner()->GetTransform().position.Distance(other.GetOwner()->GetTransform().position);

        return dist <= m_radius + circleCollider->GetRadius();
    }

    void CircleColliderComponent::Read(const json::value_t& value) {
        ColliderComponent::Read(value);

        JSON_READ_NAME(value, "radius", m_radius);
    }
}
