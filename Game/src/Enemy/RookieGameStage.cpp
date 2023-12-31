//
// Created by Tomas Tzorta on 16/12/2023.
//

#include "Enemy/RookieGameStage.h"
#include "LabyrinthFramework/World.h"
#include "Enemy/RookieEnemy.h"

namespace labyrinth_engine
{
    RookieGameStage::RookieGameStage(World* a_world)
        : GameStage{a_world}
        , m_enemySpawnInterval{1.5f}
        , m_enemySwitchInterval{5.0f}
        , m_spawnLocationDistanceFromEdge{100.0f}
        , m_enemyLeftSpawnLocation{0.0f, 0.0f}
        , m_enemyRightSpawnLocation{0.0f, 0.0f}
        , m_enemySpawnLocation{0.0f, 0.0f}
        , m_enemyRows{2}
        , m_enemySpawnCount{0}
        , m_rookieCountPerRow{5}
        , m_currentRowRookieCount{0}
    {

    }

    void RookieGameStage::StartStage()
    {
        auto windowSize = GetWorld()->GetWindowSize();
        m_enemyLeftSpawnLocation = sf::Vector2f{m_spawnLocationDistanceFromEdge, -100.0f}; //spawning this much away fromthe left edge and also beyond the top edge
        m_enemyRightSpawnLocation = sf::Vector2f{windowSize.x - m_spawnLocationDistanceFromEdge, -100.0f}; //spawning this much away from the right edge and also beyond the top edge

        SwitchEnemyRows();
    }

    void RookieGameStage::StageEnded()
    {
        TimeManager::GetInstance().RemoveTimer(m_switchTimerHandler); //clear the switch timer handler
        TimeManager::GetInstance().RemoveTimer(m_spawnTimerHandler); //clear the spawn timer handler
    }

    void RookieGameStage::SpawnEnemies()
    {
        Weak<RookieEnemy> newRookie = GetWorld()->SpawnActor<RookieEnemy>(); //spawn a new rookie enemy
        newRookie.lock()->SetActorLocation(m_enemySpawnLocation); //set the position of the rookie enemy to the enemy spawn location
        ++m_currentRowRookieCount; //increment the current row rookie enemy count
        if (m_currentRowRookieCount == m_rookieCountPerRow) //if the current row rookie enemy count is equal to the rookie count per row
        {
            TimeManager::GetInstance().RemoveTimer(m_spawnTimerHandler); //clear the spawn timer handler
            m_switchTimerHandler = TimeManager::GetInstance().SetTimer(GetWeakReference(), &RookieGameStage::SwitchEnemyRows, m_enemySwitchInterval, false); //set the switch timer handler
            m_currentRowRookieCount = 0; //reset the current row rookie count
        }
    }

    void RookieGameStage::SwitchEnemyRows()
    {
        if (m_enemySpawnCount == m_enemyRows)
        {
            EndStage();
            return;
        }

        if (m_enemySpawnLocation == m_enemyLeftSpawnLocation) //if the enemy spawn location is the left spawn location
        {
            m_enemySpawnLocation = m_enemyRightSpawnLocation; //set the enemy spawn location to the right spawn location
        }
        else
        {
            m_enemySpawnLocation = m_enemyLeftSpawnLocation; //set the enemy spawn location to the left spawn location
        }

        m_spawnTimerHandler = TimeManager::GetInstance().SetTimer(GetWeakReference(), &RookieGameStage::SpawnEnemies, m_enemySpawnInterval, true); //this is why we store game stage as shared in order to use it as a weak reference
        ++m_enemySpawnCount;
    }
}
