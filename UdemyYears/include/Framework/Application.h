//
// Created by NAT20 on 07/12/2023. By holding CTRL + K -> O you switch between .h and .cpp files.
//

#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/Graphics.hpp>

namespace Framework
{
    class Application
    {
    public:
        Application();
        void Run();

    private:
        static void Tick(float a_deltaTime);
        void Render();

        sf::RenderWindow m_window;
        float m_targetFrameRate;
        sf::Clock m_tick;
    };
}

#endif //APPLICATION_H
