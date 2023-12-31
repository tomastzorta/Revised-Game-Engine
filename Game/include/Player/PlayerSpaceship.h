//
// Created by Tomas Tzorta on 09/12/2023.
//

#ifndef PLAYER_SPACESHIP_H
#define PLAYER_SPACESHIP_H

#include "Spaceship/Spaceship.h"
#include "LabyrinthFramework/TimeKeeper.h"

namespace labyrinth_engine
{
    class ProjectileLauncher;

    class PlayerSpaceship : public Spaceship
    {
    public:
        PlayerSpaceship(World* a_owningWorld, const std::string& a_path = "ss/Ship/2.png");

        void ActorBeginPlay() override;
        void ActorTick(float a_deltaTime) override; //Override the ActorTick function from the Spaceship class

        void SetPlayerSpeed(const float a_speed) { m_playerSpeed = a_speed; } //Set the player speed
        void Fire() override; //Override the Fire function from the Spaceship class
        void SetProjectileLauncher(Unique<ProjectileLauncher>&& a_projectileLauncher); //Set the projectile launcher
        void DoDamage(float a_damage) override;

        float GetPlayerSpeed() const { return m_playerSpeed; } //Get the player speed

    private:
        void HandlePlayerInput(); //Handle the player input
        void NormalisePlayerInput(); //Normalise the player input
        void HandlePlayerMovementInput(float a_deltaTime); //Handle the player movement input
        void HandlePlayerClampPosition(); //Handle the player clamp position
        void EndPlayerInvinsibilityFrames(); //End the player invincibility frames
        void HandlePlayerInvincibilityFrames(float a_deltaTime); //Handle the player invincibility frames

        float m_playerSpeed; //Player speed
        float m_playerLastTimeFired; //Player last time fired
        float m_playerInvincibilityFrames; //Time where the player is invincible after being respawn
        float m_playerInvincibilityFrameBlinkInterval; //Time interval for the player invincibility blink
        float m_playerInvincibilityFrameBlinkTime; //Time for the player invincibility blink
        float m_playerInvincibilityFrameBlinkReveal; //Time for the player to blink or not blink

        bool m_bIsPlayerInvincible; //Bool to check if the player is invincible

        sf::Vector2f m_playerMoveInput; //Player move input

        TimeKeeper m_playerInvincibilityTimerHandler; //Timer handler for the player invincibility

        Unique<ProjectileLauncher> m_projectileLauncher; //Projectile launcher unique pointer
    };

}



#endif //PLAYER_SPACESHIP_H
