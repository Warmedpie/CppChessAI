#include "board.h"

void board::setup() {
	int c = -1;

	for (unsigned x = 0; x < 8; x++) {
		c *= -1;
		for (unsigned y = 0; y < 8; y++) {
			c *= -1;
			if (c == 1)
				this->color.push_back(sf::Color(222, 184, 135));
			if (c == -1)
				this->color.push_back(sf::Color(255, 248, 220));

			this->x.push_back(x);
			this->y.push_back(y);
		}

	}
}

std::vector<int> board::get_x() {

	return this->x;
}

std::vector<int> board::get_y() {

	return this->y;
}

std::vector<sf::Color> board::get_color() {

	return this->color;
}