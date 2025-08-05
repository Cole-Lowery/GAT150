#pragma once
#include <string>

namespace viper {
	public:
		Font() = default;
		~Font();

		bool Load(const std::string& name, float fontSize);
	private:

		friend class Text;

		TTF_Font* m_ttfFont{ nullptr };
};
}
