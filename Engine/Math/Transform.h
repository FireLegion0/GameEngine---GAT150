#pragma once
#include "Vector2.h"
#include "Serialization/Json.h"

namespace nu {
	struct Transform {
		Vector2 position{ 0.0f, 0.0f };
		float rotation{ 0.0f };
		float scale{ 1.0f };

		void Read(const json::value_t& value) {
			JSON_READ_REQ(value, position);
			JSON_READ_REQ(value, rotation);
			JSON_READ_REQ(value, scale);
		}

	};
}