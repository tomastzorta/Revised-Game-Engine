//
// Created by Tomas Tzorta on 10/12/2023.
//

#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include <box2d/b2_world.h>

#include "Core.h"


//Physics System is a singleton

namespace labyrinth_engine
{
    class Actor;
}

namespace labyrinth_engine
{
    class PhysicsContactListner : public b2ContactListener
    {
        void BeginContact(b2Contact* contact) override;
        void EndContact(b2Contact* contact) override;
    };

    class PhysicsSystem
    {
    public:
        static PhysicsSystem& GetInstance();
        void Update(float a_deltaTime);
        b2Body* AddListener(Actor* a_actor); //add actor to physics world
        void RemoveListener(b2Body* a_body); //remove actor from physics world

        //getters
        float GetPhysicsScale() const { return m_physicsScale; }

        static void Clear();



    protected:
        PhysicsSystem();
    private:
        void CalculateListenersToRemove();
        static Unique<PhysicsSystem> physicsSystem;
        b2World m_physicsWorld;
        float m_physicsScale;
        int m_velocityIterations;
        int m_positionIterations;

        PhysicsContactListner m_contactListner;

        Set<b2Body*> m_listenersToRemove;

    };
}



#endif //PHYSICSSYSTEM_H
