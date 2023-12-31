//
// Created by Tomas Tzorta on 28/12/2023.
//

#include "LabyrinthFramework/AudioManager.h"

#include <iostream>

#include "LabyrinthFramework/AssetManager.h"

namespace labyrinth_engine
{

    Unique<AudioManager> AudioManager::audioManager{nullptr};

    AudioManager::AudioManager()
        : m_sfx{}
        , m_sfxPlayer{}
        , m_globalVolume{}
        , m_sfxVolume{}
    {

    }

    void AudioManager::LoadSFX(const std::string& a_audioName, const std::string& a_audioPath)
    {
        AssetManager& assetManager = AssetManager::GetInstance();
        m_sfx[a_audioName] = assetManager.LoadSoundBuffer(a_audioPath);
        m_sfxPlayer[a_audioName].setBuffer(*m_sfx[a_audioName]);
    }

    void AudioManager::PlaySFX(const std::string& a_audioName)
    {
        auto itteration = m_sfxPlayer.find(a_audioName);
        if (itteration != m_sfxPlayer.end())
        {
            itteration->second.play();
        }
    }

    void AudioManager::StopSFX(const std::string& a_audioName)
    {
        auto itteration = m_sfxPlayer.find(a_audioName);
        if (itteration != m_sfxPlayer.end())
        {
            itteration->second.stop();

        }
    }

    void AudioManager::SetSFXLoop(const std::string& a_audioName, bool a_bLoop)
    {
        auto itteration = m_sfxPlayer.find(a_audioName);
        if (itteration != m_sfxPlayer.end())
        {
            itteration->second.setLoop(a_bLoop);
        }
    }

    void AudioManager::SetGlobalVolume(float a_volume)
    {
        m_globalVolume = a_volume;
        for (auto& i : m_sfxPlayer)
        {
            i.second.setVolume(m_globalVolume);
        }
    }

    void AudioManager::SetSFXVolume(const std::string& a_audioName, float a_volume)
    {
        auto itteration = m_sfxPlayer.find(a_audioName);
        if (itteration != m_sfxPlayer.end())
        {
            itteration->second.setVolume(a_volume);
        }
    }

    AudioManager& AudioManager::GetInstance()
    {
        if (audioManager == nullptr)
        {
            audioManager = std::move(Unique<AudioManager>{new AudioManager{}});
        }
        return *audioManager;
    }
}
