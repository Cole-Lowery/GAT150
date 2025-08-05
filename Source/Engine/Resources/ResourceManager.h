#pragma once 

#include "Core/StringHelper.h"
#include "Resource.h"

#include <map>
#include <string>
#include <memory>
#include <iostream>

namespace viper{
	class ResourceManager {
	public:
		ResourceManager() = default;
		~ResourceManager() = default;
		template<typename T>
		res_t<T> Get(const std::string& name);

	private:
		std::map<std::string, res_t<Resource>> m_Resources;
	};
	template<typename T>
	inline res_t<T> ResourceManager::Get(const std::string& name) {
		std::string key = toLower(name);

		auto iter = m_Resources.find(key);
		if (iter != m_Resources.end()) {
			auto base = iter->second;
			auto derived = std::dynamic_pointer_cast<T>(base);
			if (!derived) {
				throw std::cerr("Resource type mismatch for resource: " + key);
				return res_t<T>();
			}
			return derived;
		}
		return res_t<T>();
	}
}