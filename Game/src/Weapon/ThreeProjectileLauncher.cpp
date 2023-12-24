//
// Created by Tomas Tzorta on 18/12/2023.
//

#include "Weapon/ThreeProjectileLauncher.h"

namespace labyrinth_engine
{
    ThreeProjectileLauncher::ThreeProjectileLauncher(Actor* a_owner, float a_cooldown, const sf::Vector2f& a_offset)
        : ProjectileLauncher{a_owner}
        , launcherLeft{a_owner, a_cooldown, a_offset, -30.0f, "PNG/Lasers/laserRed01.png"}
        , launcherCenter{a_owner, a_cooldown, a_offset, 0.0f, "PNG/Lasers/laserRed01.png"}
        , launcherRight{a_owner, a_cooldown, a_offset, 30.0f, "PNG/Lasers/laserRed01.png"}
        , launcherMaxLeft{a_owner, a_cooldown, a_offset, 15.0f, "PNG/Lasers/laserRed01.png"}
        , launcherMaxRight{a_owner, a_cooldown, a_offset, -15.0f, "PNG/Lasers/laserRed01.png"}
    {
    }

    void ThreeProjectileLauncher::IncreaseLauncherLevel(int a_increaseAmount)
    {
        ProjectileLauncher::IncreaseLauncherLevel(a_increaseAmount);
        launcherLeft.IncreaseLauncherLevel(a_increaseAmount);
        launcherCenter.IncreaseLauncherLevel(a_increaseAmount);
        launcherRight.IncreaseLauncherLevel(a_increaseAmount);

        launcherMaxLeft.IncreaseLauncherLevel(a_increaseAmount);
        launcherMaxRight.IncreaseLauncherLevel(a_increaseAmount);
    }

    void ThreeProjectileLauncher::OnFire()
    {
        launcherLeft.Fire();
        launcherCenter.Fire();
        launcherRight.Fire();

        if (GetCurrentLauncherLevel() == GetMaxLauncherLevel())
        {
            launcherMaxLeft.Fire();
            launcherMaxRight.Fire();
        }
    }
}