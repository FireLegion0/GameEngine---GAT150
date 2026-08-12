#pragma once
#include "Object.h"
#include "Singleton.h"

#include <memory>
#include <map>

namespace nu {
	class ICreator {
	public:
		virtual ~ICreator() = default;
		virtual std::unique_ptr<Object> Create() = 0;
	};

	template <typename T>
		requires std::derived_from<T, Object>
	class Creator : public ICreator {
	public:
		std::unique_ptr<Object> Create() override {
			return std::make_unique<T>();
		}
	};

	class Factory : public Singleton<Factory> {
	public:
		template <typename T>
			requires std::derived_from<T, Object>
		void Register(const std::string& name);

		template <typename T = class Object>
			requires std::derived_from<T, Object>
		std::unique_ptr<T> Create(const std::string& name);

	private:
		std::map<std::string, std::unique_ptr<ICreator>> m_registry;
	};

	template <typename T>
		requires std::derived_from<T, Object>
	inline void Factory::Register(const std::string& name) {
		std::string lowerName = ToLower(name);

		if (m_registry.contains(lowerName)) {
			std::cerr << "Object already registered: " << name << std::endl;
			return;
		}
		m_registry[lowerName] = std::make_unique<Creator<T>>();
	}

	template <typename T>
		requires std::derived_from<T, Object>
	inline std::unique_ptr<T> Factory::Create(const std::string& name) {
		std::string lowerName = ToLower(name);

		if (!m_registry.contains(lowerName)) {
			std::cerr << "Object not registered: " << name << std::endl;
			return std::unique_ptr<T>();
		}

		auto iter = m_registry.find(lowerName);

		//auto creator = m_registry[lowerName];
		auto object = iter->second->Create();

		T* derived = dynamic_cast<T*>(object.get());
		if (derived) {
			object.release();
			return std::unique_ptr<T>(derived);
		}
		else {
			std::cerr << "Object not derived from type: " << name << std::endl;
		}

		return std::unique_ptr<T>();
	}
}