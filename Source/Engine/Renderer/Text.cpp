#include "Text.h"
#include <SDL3_ttf/SDL_ttf.h>
#include "Core/Logger.h"

namespace viper {
	Text::~Text() {
		if (m_texture != nullptr) {
			SDL_DestroyTexture(m_texture);
		}
	}
	bool Text::Create(Renderer& renderer, const std::string& text, const vec3& color) {
		SDL_Color c{ (uint8_t)(color.r * 255), (uint8_t)(color.g * 255), (uint8_t)(color.b * 255), 255 };
		SDL_Surface* surface = TTF_RenderText_Solid(m_font->m_ttfFont, text.c_str(), text.size(), c);
		if (surface == nullptr) {
			Logger::Error("SDL_Init Error: {}", SDL_GetError());
			return false;
		}

		m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
		if (m_texture == nullptr) {
			SDL_DestroySurface(surface);
			Logger::Error("SDL_Init Error: {}", SDL_GetError());
			return false;
		}
		SDL_DestroySurface(surface);

		return true;
	}

	void Text::Draw(Renderer& renderer, float x, float y) {
		float width, height;
		bool success = SDL_GetTextureSize(m_texture, &width, &height);
		assert(success);

		SDL_FRect rect{ x, y, width, height };
		success = SDL_RenderTexture(renderer.m_renderer, m_texture, NULL, &rect);
		assert(success);
	}
}