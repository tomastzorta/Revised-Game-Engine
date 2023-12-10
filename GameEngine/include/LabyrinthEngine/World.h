//
// Created by Tomas Tzorta on 07/12/2023.
//

#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>
#include "Core.h"

namespace labyrinth_engine
{
    class Actor;
    class Application;

    class World
    {
    public:
        explicit World(Application* a_owningApplication);

        void BeginPlayFramework();
        void WorldTickFramework(float a_deltaTime);
        void Render(sf::RenderWindow& a_window);

        virtual ~World(); //whenever you need something to be inherited you have a virtual destructor to make sure that the destructor of the child class is called first and then the destructor of the parent class is called

        template<typename a_ActorType, typename... arguments>
        Wptr<a_ActorType> SpawnActor(arguments... a_args);

        sf::Vector2u GetWindowSize() const;

        void Clear();


    private:
        void BeginPlay();
        void WorldTick(float a_deltaTime);

        Application* m_owningApplication;
        bool m_bIsPlaying;

        Vec<Sptr<Actor>> m_actors;
        Vec<Sptr<Actor>> m_actorsToAdd; //reason for this is cause we can't add actors to the vector while we are iterating through it
    };

    //Template Functions
    template<typename a_ActorType, typename... arguments>
    Wptr<a_ActorType> World::SpawnActor(arguments... a_args)
    {
        Sptr<a_ActorType> newActor{new a_ActorType(this, a_args...)};
        m_actorsToAdd.push_back(newActor);
        return newActor;
    }

}



#endif //WORLD_H