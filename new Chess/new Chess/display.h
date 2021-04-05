#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include <iostream>
#include <sstream>

class display
{
public:
	std::map<std::string, sf::Sprite> piece_s;
	std::map<std::string, sf::Texture> piece_t;

	sf::Sprite depth_buttonS;
	sf::Texture depth_buttonT;

	sf::Sprite b0;
	sf::Texture b0T;
	sf::Sprite b1;
	sf::Texture b1T;

	void setup();
	void draw(sf::RenderWindow &window, int mx, int my, std::vector<int> b_x, std::vector<int> b_y, std::vector<sf::Color> b_color, std::vector<int> p_x, std::vector<int> p_y, std::vector<int> p_team, std::vector<std::string> p_type, int p_selected, double score, bool checkWhite, bool checkBlack, std::vector<std::vector<int>> bestMove, std::string depth, bool engine, bool aiw, bool aib, std::vector<double> scores);
	std::string move(std::vector<int> move);
};

