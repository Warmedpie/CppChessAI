#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include <iostream>
#include <sstream>
class board
{
public:
	std::vector<int> x;
	std::vector<int> y;
	std::vector<sf::Color> color;

	void setup();
	std::vector<int> get_x();
	std::vector<int> get_y();
	std::vector<sf::Color> get_color();
};

