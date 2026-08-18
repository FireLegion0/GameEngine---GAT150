#pragma once
#include "ColliderComponent.h"

namespace nu {
	class CircleColliderComponent : public ColliderComponent {
	public:
		CLASS_PROTO(CircleColliderComponent)

		bool CheckCol(const ColliderComponent& other) override;
		void Read(const json::value_t& value) override;
		float GetRadius() const { return m_radius; }

	protected:
		float m_radius;
	};
}