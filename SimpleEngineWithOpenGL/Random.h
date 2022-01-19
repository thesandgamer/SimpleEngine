#pragma once
#include <random>
#include "Vector2.h"

class Random
{
public:
	void init();

	//Seed the genrator specified int
	//Note: you sould genrally not need to manually this
	static void seed(unsigned int seed);

	//Get a float entre 0 et 1
	static float getFloat();

	//Get a random float dans un range
	static float getFloatRange(float min, float max);

	//Get an int from the specified range
	static int getInRange(int min, int max);

	//Get a random vector given the min max bounds
	static Vector2 getVector(const Vector2& min, const Vector2& max);

private:
	static std::mt19937 sGenerator;
};

