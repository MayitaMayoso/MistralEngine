#include "MistralEngine.h"
#include "Scenario.h"
#include "GameObjects.h"
#include "Entity.h"

Scenario::Scenario(MistralEngine* g)
{
	game = g;
}

void Scenario::ReadScenario(string path)
{
	string str;
	string aux;
	string object;
	float x;
	float y;
	float z;

	name = path;

	ifstream file( "_resources/Scenarios/" + path);

	if (file.is_open())
	{

		while (std::getline(file, str))
		{
			std::istringstream is(str);
			int i = 0;
			while (getline(is, aux, '/'))
			{
				if (i == 0)
					object = aux;


				if (i == 1)
					x = std::stof(aux);
				if (i == 2)
					y = std::stof(aux);
				if (i == 3)
				{
					z = std::stof(aux);

					if (object == "Character")
					{
						Character* p = new Character(game);
						p->set_position(x, y, z);
					}

					if (object == "Skybox")
					{
						Skybox* p = new Skybox(game);
						p->set_position(x, y, z);
					}

					if (object == "Nanosuit")
					{
						Nanosuit* p = new Nanosuit(game);
						p->set_position(x, y, z);
					}

					if (object == "Universe")
					{
						Universe* p = new Universe(game);
						p->set_position(x, y, z);
					}

					if (object == "Planet")
					{
						Planet* p = new Planet(game);
						p->set_position(x, y, z);
					}


				}


				i++;

			}


		}
	}

}

void Scenario::ChangeScenario(string path) {
	room2change = true;
	nextRoom = path;
}

void Scenario::CheckAndChangeScenario() {
	if (room2change) {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glutSwapBuffers();

		for (Entity* e : game->EntitiesList) {
			e->Destroy();
			delete e;
		}

		game->EntitiesList.clear();

		room2change = false;

		ReadScenario(nextRoom);
	}
}