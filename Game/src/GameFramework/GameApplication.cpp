//
// Created by Tomas Tzorta on 07/12/2023.
//

#include "GameName/GameApplication.h"
#include "Level/MainMenu.h"
#include "LabyrinthFramework/AssetManager.h"
#include "config.h"


labyrinth_engine::Application* GetApplication()
{
    return new labyrinth_engine::GameApplication();
}


namespace labyrinth_engine
{
    GameApplication::GameApplication()
        : Application{600, 900, "Game", sf::Style::Titlebar | sf::Style::Close}
    {
        AssetManager::GetInstance().SetAssetDirectory(GetAssetDirectory());
        const Weak<MainMenu> newWorld = LoadWorld<MainMenu>();
    }
}
