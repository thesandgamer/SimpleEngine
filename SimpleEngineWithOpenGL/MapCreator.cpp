#include "MapCreator.h"

MapCreator::MapCreator(Vector3 position,string nameOfLevelToOpen):startPos(position), nameOfLevel{nameOfLevelToOpen}
{
	nameOfLevel = "Res\\Levels\\" + nameOfLevelToOpen + ".txt";
	setupLevelElements();
}

void MapCreator::setupLevelElements()
{
	string txt ;
	fstream datafileRead;
	datafileRead.open(nameOfLevel, std::ios::in); //On ouvre le fichier pour lire
	if (datafileRead.fail())
	{
		Log::info("Level not found");
		//Log::error(LogCategory::Error, "Level not found");
	}
	if (datafileRead.is_open())
	{
		float ligne = 0;
		while (std::getline(datafileRead, txt)) //txt va être ligne par ligne
		{
			for (float x = 0; x < txt.length(); x += 1) //Pour lire tout les colognes d'une ligne
			{
				std::cout << txt[x];
				if (txt[x] == '\t')
				{
					continue;
				}
				if (txt[x] == 'x' || txt[x] == 'X')
				{
					Actor* cube = new Cube();
					cube->setScale(200.0f); //Set sa scale

					cube->setPosition(Vector3(startPos.x + x*cube->getScale(), startPos.y +ligne * cube->getScale(), startPos.z ));

					levelElements.push_back(cube);
					//levelElements[pos] = cube;
					//levelElements.insert({ pos, cube });
				}


			}
			std::cout << std::endl;
			ligne += 1;

		}		
	}
}
