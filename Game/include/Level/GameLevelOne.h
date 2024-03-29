//
// Created by s5216712 on 11/12/2023.
//

#ifndef GAMELEVELONE_H
#define GAMELEVELONE_H

#include "LabyrinthFramework/World.h"
#include "LabyrinthFramework/TimeKeeper.h"

namespace labyrinth_engine
{
    class PlayerSpaceship;
    class GameHUD;
    class GameLevelOne : public World
    {
    public:
        GameLevelOne(Application* a_application);
    private:
        void BeginPlay() override;
        void InitialiseGameStages() override;
        void PlayerSpaceshipDestroyed(Actor* a_actor);
        void GameOver();
        void GameStagesFinished() override;
        void RestartGame();
        void QuitGame();

        Weak<PlayerSpaceship> m_playerSpaceship;
        Weak<GameHUD> m_GameHUD;
        TimeKeeper m_timerHandler;
    };
}




#endif //GAMELEVELONE_H
