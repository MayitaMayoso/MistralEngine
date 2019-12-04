#include "..\include\Scenario.h"

Scenario::Scenario(MistralEngine* game)
{
	m_game = game;
}

void Scenario::ReadScenario(string path)
{
	string str;
	string aux;
	string object;
	float x;
	float y;
	float z;

	ifstream file(path);

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
						Character* p = new Character(m_game);
						p->set_position(x, y, z);
					}

					if (object == "Camera")
					{
						Camera* p = new Camera(m_game);
						p->set_position(x, y, z);
					}

					if (object == "Planet")
					{
						Planet* p = new Planet(m_game);
						p->set_position(x, y, z);
					}

					if (object == "Nanosuit")
					{
						Nanosuit* p = new Nanosuit(m_game);
						p->set_position(x, y, z);
					}


				}


				i++;

			}


		}
	}

}
