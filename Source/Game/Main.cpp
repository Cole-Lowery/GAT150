#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Transform.h"
#include "Core/Random.h"
#include "Core/Time.h"
#include "Core/File.h"
#include "Framework/Actor.h"
#include "Audio/AudioSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Input/InputSystem.h"
#include "Framework/Scene.h"
#include "Engine.h"
#include "Resources/ResourceManager.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "Renderer/Texture.h"
#include "Core/Logger.h"

#include "Game/Player.h"
#include "Game/SpaceGame.h"

#include <iostream>
#include <vector>
#include <memory>

int main(int argc, char* argv[]) {
    viper::Logger::SetEnabledLevels;

    viper::file::SetCurrentDirectory("Assets");

    // Intialize engine
    viper::GetEngine().Initialize();

    //Initialize game
    std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
    game->Initialize();

    // Create stars
    std::vector<viper::vec2> stars;
    for (int i = 0; i < 100; i++) {
        stars.push_back(viper::vec2{ viper::random::getReal() * 1280, viper::random::getReal() * 1024 });
    }

    //auto texture = viper::ResourceManager::Instance().Get<viper::Texture>("maple.jpg", viper::GetEngine().GetRenderer());

    SDL_Event e;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) { quit = true; }

        // Update input system
        viper::GetEngine().Update();
        game->Update(viper::GetEngine().GetTime().GetDeltaTime());

        // Clear the renderer
        viper::vec3 color{ 0, 0, 0 };

        viper::GetEngine().GetRenderer().SetColor(color.r, color.g, color.b);
        viper::GetEngine().GetRenderer().Clear();

        game->Draw(viper::GetEngine().GetRenderer());

        // Draw stars
        viper::vec2 speed{ -140.0f, 0.0f };
        float length = speed.Length();



        for (auto& star : stars) {
            star += speed * viper::GetEngine().GetTime().GetDeltaTime();

            if (star[0] > 1280) star[0] = 0;
            if (star[0] < 0) star[0] = 1280;

            viper::GetEngine().GetRenderer().SetColor((uint8_t)viper::random::getInt(256), viper::random::getInt(256), viper::random::getInt(256));
            viper::GetEngine().GetRenderer().DrawPoint(star.x, star.y);
        }

        viper::GetEngine().GetRenderer().Present();
    }

    game->Shutdown();
    game.release();
    viper::GetEngine().Shutdown();

    return 0;
}