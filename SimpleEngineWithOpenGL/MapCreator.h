#pragma once
#include "Vector2.h"
#include "Actor.h"
#include "Log.h"
#include "Cube.h"

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using std::map;
using std::string;
using std::fstream;
using std::vector;

class MapCreator
{
public:
	MapCreator(Vector3 position, string nameOfLevelToOpen);

private:

	void setupLevelElements();

	string nameOfLevel;

	Vector3 startPos;
	//map<Vector2, Actor*> levelElements;
	vector<Actor*> levelElements;
	

};

