//
// Created by Tomas Tzorta on 07/12/2023.
//

#include "EntryPoint.h"
#include "LabyrinthEngine/Application.h"

int main()
{
    labyrinth_engine::Application* application = GetApplication();
    application->Run();
    delete application;
}