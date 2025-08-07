#include "Texture.h"
#include "Renderer.h"
#include "Core/Logger.h"
#include <SDL3_image/SDL_image.h>
#include <iostream>

namespace viper {
    Texture::~Texture()
    {
        if (m_texture) SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
    }

    bool Texture::Load(const std::string& filename, Renderer& renderer)
    {
        SDL_Surface* surface = IMG_Load(filename.c_str());
        if (!surface)
        {
            Logger::Error("SDL_Init Error: {}", SDL_GetError());
            return false;
        }
        m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
        SDL_DestroySurface(surface);
        if (!m_texture)
        {
            Logger::Error("SDL_Init Error: {}", SDL_GetError());
            return false;
        }
        return true;
    }
    vec2 Texture::GetSize()
    {
        float w = 0.0f, h = 0.0f;
        SDL_GetTextureSize(m_texture, &w, &h);
        return vec2(w, h);

    }
}