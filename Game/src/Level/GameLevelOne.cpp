//
// Created by s5216712 on 11/12/2023.
//

#include "Level/GameLevelOne.h"

#include "Enemy/RookieGameStage.h"
#include "Enemy/CopyCatGameStage.h"
#include "Enemy/EnforcerGameStage.h"
#include "Enemy/DancerGameStage.h"
#include "Gameplay/WaitStage.h"
#include "Enemy/MadMaxGameStage.h"

#include "LabyrinthFramework/Actor.h"
#include "LabyrinthFramework/TimeKeeper.h"
#include "GameName/GameApplication.h"
#include "Player/PlayerManager.h"
#include "Player/PlayerSpaceship.h"
#include "UI/GameHUD.h"


namespace labyrinth_engine
{
    GameLevelOne::GameLevelOne(Application* a_application)
        : World{a_application}
    {
        AudioManager::GetInstance().LoadSFX("Shoot", "Bonus/blaster.mp3");
        AudioManager::GetInstance().LoadSFX("PlayerShoot", "Bonus/sfx_laser2.ogg");
        AudioManager::GetInstance().LoadSFX("BG", "Bonus/background.mp3");
        AudioManager::GetInstance().LoadSFX("Explosion", "Bonus/explosion.wav");
        AudioManager::GetInstance().LoadSFX("PowerUp", "Bonus/sfx_zap.ogg");
        AudioManager::GetInstance().LoadSFX("Game Over", "ss/Sound/5.wav");
        AudioManager::GetInstance().SetSFXVolume("Shoot", 5.0f);
        AudioManager::GetInstance().SetSFXVolume("BG", 10.0f);
        AudioManager::GetInstance().SetSFXVolume("Explosion", 40.0f);
        AudioManager::GetInstance().SetSFXVolume("PowerUp", 70.0f);
        AudioManager::GetInstance().SetSFXVolume("PlayerShoot", 50.0f);
    }

    void GameLevelOne::BeginPlay()
    {
        Player& player = PlayerManager::GetInstance().AddPlayer();
        m_playerSpaceship = player.SpawnPlayerSpaceship(this);
        m_playerSpaceship.lock()->OnActorDestroy.Bind(GetWeakReference(), &GameLevelOne::PlayerSpaceshipDestroyed);
        m_GameHUD = InstantiateHUD<GameHUD>();
        AudioManager::GetInstance().PlaySFX("BG");
        AudioManager::GetInstance().SetSFXLoop("BG", true);

    }

    void GameLevelOne::InitialiseGameStages()
    {

        AddGameStage(Shared<WaitStage>{new WaitStage{this, 2.0f}});
        AddGameStage(Shared<RookieGameStage>{new RookieGameStage{this}});

        AddGameStage(Shared<WaitStage>{new WaitStage{this, 5.0f}});
        AddGameStage(Shared<CopyCatGameStage>{new CopyCatGameStage{this}});

        AddGameStage(Shared<WaitStage>{new WaitStage{this, 8.0f}});
        AddGameStage(Shared<EnforcerGameStage>{new EnforcerGameStage{this}});

        AddGameStage(Shared<WaitStage>{new WaitStage{this, 11.0f}});
        AddGameStage(Shared<DancerGameStage>{new DancerGameStage{this}});

        AddGameStage(Shared<WaitStage>{new WaitStage{this, 15.0f}});
        AddGameStage(Shared<MadMaxGameStage>{new MadMaxGameStage{this}});
    }

    void GameLevelOne::PlayerSpaceshipDestroyed(Actor* a_actor)
    {
        m_playerSpaceship = PlayerManager::GetInstance().GetPlayer()->SpawnPlayerSpaceship(this);

        if (!m_playerSpaceship.expired())
        {
            m_playerSpaceship.lock()->OnActorDestroy.Bind(GetWeakReference(), &GameLevelOne::PlayerSpaceshipDestroyed);
        }
        else
        {
            GameOver();
        }

    }

    void GameLevelOne::GameOver()
    {
        AudioManager::GetInstance().StopSFX("BG");
        AudioManager::GetInstance().PlaySFX("Game Over");
        LE_LOG("GAME OVER! YOU LOSE!");
    }
}
