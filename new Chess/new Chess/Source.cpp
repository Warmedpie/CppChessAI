#include <SFML/Graphics.hpp>
#include "display.h"
#include "board.h"
#include "pieces.h"
#include <thread>

//Variable declarations
int width = 960;
int height = 540;

int main() {
	display* d = new display();
	d->setup();

	board* b = new board();
	b->setup();

	pieces* p = new pieces();
	p->setup();

	sf::RenderWindow window(sf::VideoMode(width, height), "Chess AI", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(30);

	sf::Font font;
	font.loadFromFile("assets/fonts/IHATCS__.ttf");

	sf::Event event;
	while (window.isOpen()) {
		//Event Handler
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::MouseButtonReleased) {
				int x = sf::Mouse::getPosition(window).x;
				int y = sf::Mouse::getPosition(window).y;
				p->release(x, y);
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				int x = sf::Mouse::getPosition(window).x;
				int y = sf::Mouse::getPosition(window).y;
				p->select(x, y);
			}

			if (event.type == sf::Event::KeyPressed) {

			}

			if (event.type == sf::Event::KeyReleased) {

			}

		}
		//Draw
		window.clear(sf::Color(34, 139, 34));

		int mx = sf::Mouse::getPosition(window).x;
		int my = sf::Mouse::getPosition(window).y;

		d->draw(window, mx, my, b->get_x(), b->get_y(), b->get_color(), p->get_x(), p->get_y(), p->get_team(), p->get_type(), p->get_selected(), p->get_score(), p->teamCheck(-1), p->teamCheck(1), p->getBestMove(),p->get_depth(),p->get_engine(),p->get_aiWhite(),p->get_aiBlack(),p->get_scores());
		p->contanalysis();
		window.display();
	}
	return 0;
}