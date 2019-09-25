#include "GraphicsEngine/Application.h"

#include "Tasks/Task01.h"
#include "Tasks/Task04.h"
#include "Tasks/Task05_01.h"
#include "Tasks/Task08.h"
#include "pylos_game/pylos_game.h"

using namespace graphics_engine;

// The application's entry point
int main(int argc, char ** argv)
{
	// Remember argc, argv
	{
		Application & app = Application::Instance();
		app.argc = argc;
		app.argv = argv;
	}

//    Task * pTask = new Task01();
//    Task * pTask = new Task04();
    Task * pTask = new pylos_game_space::PylosTask();
    //Task * pTask = new Task05_01();
    //Task * pTask = new Task08();
	{
		GraphicsEngine & engine = GraphicsEngine::Instance();

		engine.Init();
        pTask->Init();

		while (engine.IsRunning())
		{
            pTask->Update();
			engine.Render();
		}

        delete pTask;
		engine.Deinit();
    }
	
    return 0;
}
