//
// Created by Tomas Tzorta on 16/12/2023.
//

#ifndef UFOGAMESTAGE_H
#define UFOGAMESTAGE_H

#include "Gameplay/GameStage.h"
#include <SFML/Graphics.hpp>
#include "LabyrinthFramework/TimeManager.h"

namespace labyrinth_engine
{
    class UFOGameStage : public GameStage
    {
    public:
        /* Constructors and Destructors */
        UFOGameStage(World* a_world);
        /* End of Constructors and Destructors */

        /* Class Functions */

        // Void Functions

        // Boolean Functions

        // Virtual Functions
        void StartStage() override;

        /* End of Class Functions */

        /* Override Functions */
        /* End of Override Functions */

        /* Setters and Getters */

        // Setters

        // Getters

        /* End of Setters and getters */

    protected:

    private:
        void StageEnded() override;
        sf::Vector2f GetRandomSpawnLocation();
        void SpawnEnemies();

        float m_enemySpawnInterval;
        int m_enemySpawnAmount;
        int m_enemyCurrentSpawnAmount;
        float m_ufoSpeed;

        TimerHandler m_enemySpawnTimer;
    };
}

#endif //UFOGAMESTAGE_H
