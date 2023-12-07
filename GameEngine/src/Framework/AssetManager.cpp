//
// Created by NAT20 on 07/12/2023.
//

#include "Framework/AssetManager.h"

namespace Framework
{
    Uptr<AssetManager> AssetManager::assetManager{nullptr}; // singleton

    AssetManager& AssetManager::Get()
    {
        if (!assetManager)
        {
            assetManager = Uptr<AssetManager>{new AssetManager};
        }
        return *assetManager;
    }

    Sptr<sf::Texture> AssetManager::LoadTexture(const std::string& filename)
    {
        const auto pairFound = m_mLoadedTextures.find(filename); // check if texture is already loaded
        if (pairFound != m_mLoadedTextures.end()) // if texture is already loaded
        {
            return pairFound->second; // return texture
        }

        Sptr<sf::Texture> newTexture{new sf::Texture}; // load texture
        if (newTexture->loadFromFile(filename)) // if texture is loaded
        {
            m_mLoadedTextures.insert({filename, newTexture}); // insert texture into map
            return newTexture; // return texture
        }

        return Sptr<sf::Texture> {nullptr}; // return nullptr if texture is not loaded
    }

    void AssetManager::Clear()
    {
        for (auto iterator = m_mLoadedTextures.begin(); iterator != m_mLoadedTextures.end();)
        {
            if (iterator->second.use_count() == 1)
            {
                GE_LOG("Cleaning up texture: %s", iterator->first.c_str());
                iterator = m_mLoadedTextures.erase(iterator);
            }
            else
            {
                ++iterator;
            }
        }
    }

    AssetManager::AssetManager()
    {

    }
}