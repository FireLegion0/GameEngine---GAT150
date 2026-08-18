#pragma once
#include "Component.h"

namespace nu {
	class ColliderComponent : public Component {
	public:
		virtual bool CheckCol(const ColliderComponent& other) = 0;
	};
}