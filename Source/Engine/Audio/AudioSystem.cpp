#include "AudioSystem.h"
#include "Core/StringHelper.h"
#include "Core/Logger.h"

#include <SDL3/SDL_error.h>
#include <iostream>
#include <fmod_errors.h>


namespace viper {

    bool AudioSystem::CheckFMODResult(FMOD_RESULT result) {
        if (result != FMOD_OK) {
			Logger::Error("FMOD Error: {}", FMOD_ErrorString(result));
            return false;
        }
        return true;
    }

    bool AudioSystem::Initialize() {
        FMOD_RESULT result = FMOD::System_Create(&m_system);
        if (!CheckFMODResult(result))return false;
        void* extradriverdata = nullptr;
        result = m_system->init(32, FMOD_INIT_NORMAL, extradriverdata);
        if (!CheckFMODResult(result))return false;
        return true;
    }

    void AudioSystem::Shutdown() {
        CheckFMODResult(m_system->release());
    }

    void AudioSystem::Update() {
        CheckFMODResult(m_system->update());
    }

    bool AudioSystem::AddSound(const char* filename, const std::string& name)
    {
        std::string key = name.empty() ? filename : name;
        key = tolower(key);
        if (m_sounds.find(key) != m_sounds.end()) {
			Logger::Error("AudioSystem::AddSound: Sound already exists: {}", key);
            return false;
        }
        FMOD::Sound* sound = nullptr;
        FMOD_RESULT result = m_system->createSound(filename, FMOD_DEFAULT, 0, &sound);
        if (!CheckFMODResult(result)) return false;
        m_sounds[key] = sound;
        return true;
    }
    bool AudioSystem::PlaySound(const std::string& name)
    {
        std::string key = name;
        if (m_sounds.find(key) == m_sounds.end()) {
			Logger::Error("AudioSystem::PlaySound: Sound not found: {}", key);
            return false;
        }
        FMOD_RESULT result = m_system->playSound(m_sounds[name], 0, false, nullptr);
        if (!CheckFMODResult(result)) return false;
        return true;

    }

}