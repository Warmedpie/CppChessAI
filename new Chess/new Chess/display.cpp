#include "display.h"

void display::setup() {

	sf::Texture resourceb0;
	resourceb0.loadFromFile("assets/GUI/button_0.png");
	resourceb0.setSmooth(true);
	this->b0T = resourceb0;

	sf::Sprite spriteb0;
	spriteb0.setTexture(this->b0T);
	this->b0 = spriteb0;

	sf::Texture resourceb1;
	resourceb1.loadFromFile("assets/GUI/button_1.png");
	resourceb1.setSmooth(true);
	this->b1T = resourceb1;

	sf::Sprite spriteb1;
	spriteb1.setTexture(this->b1T);
	this->b1 = spriteb1;

	sf::Texture resourceD;
	resourceD.loadFromFile("assets/GUI/depth.png");
	resourceD.setSmooth(true);
	this->depth_buttonT = resourceD;

	sf::Sprite spriteD;
	spriteD.setTexture(this->depth_buttonT);
	this->depth_buttonS = spriteD;

	this->depth_buttonS.setPosition(715, 245);

	sf::Texture resource;
	resource.loadFromFile("assets/White/king.png");
	resource.setSmooth(true);
	this->piece_t["-1K"] = resource;

	sf::Sprite sprite1;
	sprite1.setTexture(piece_t["-1K"]);
	this->piece_s["-1K"] = sprite1;

	resource.loadFromFile("assets/White/queen.png");
	resource.setSmooth(true);
	this->piece_t["-1Q"] = resource;

	sf::Sprite sprite2;
	sprite2.setTexture(piece_t["-1Q"]);
	this->piece_s["-1Q"] = sprite2;

	resource.loadFromFile("assets/White/knight.png");
	resource.setSmooth(true);
	this->piece_t["-1N"] = resource;

	sf::Sprite sprite3;
	sprite3.setTexture(piece_t["-1N"]);
	this->piece_s["-1N"] = sprite3;

	resource.loadFromFile("assets/White/bishop.png");
	resource.setSmooth(true);
	this->piece_t["-1B"] = resource;

	sf::Sprite sprite4;
	sprite4.setTexture(piece_t["-1B"]);
	this->piece_s["-1B"] = sprite4;

	resource.loadFromFile("assets/White/rook.png");
	resource.setSmooth(true);
	this->piece_t["-1R"] = resource;

	sf::Sprite sprite5;
	sprite5.setTexture(piece_t["-1R"]);
	this->piece_s["-1R"] = sprite5;

	resource.loadFromFile("assets/White/pawn.png");
	resource.setSmooth(true);
	this->piece_t["-1P"] = resource;

	sf::Sprite sprite6;
	sprite6.setTexture(piece_t["-1P"]);
	this->piece_s["-1P"] = sprite6;

	resource.loadFromFile("assets/Brown/king.png");
	resource.setSmooth(true);
	this->piece_t["1K"] = resource;

	sf::Sprite sprite7;
	sprite7.setTexture(piece_t["1K"]);
	this->piece_s["1K"] = sprite7;

	resource.loadFromFile("assets/Brown/queen.png");
	resource.setSmooth(true);
	this->piece_t["1Q"] = resource;

	sf::Sprite sprite8;
	sprite8.setTexture(piece_t["1Q"]);
	this->piece_s["1Q"] = sprite8;

	resource.loadFromFile("assets/Brown/knight.png");
	resource.setSmooth(true);
	this->piece_t["1N"] = resource;

	sf::Sprite sprite9;
	sprite9.setTexture(piece_t["1N"]);
	this->piece_s["1N"] = sprite9;

	resource.loadFromFile("assets/Brown/bishop.png");
	resource.setSmooth(true);
	this->piece_t["1B"] = resource;

	sf::Sprite sprite10;
	sprite10.setTexture(piece_t["1B"]);
	this->piece_s["1B"] = sprite10;

	resource.loadFromFile("assets/Brown/rook.png");
	resource.setSmooth(true);
	this->piece_t["1R"] = resource;

	sf::Sprite sprite11;
	sprite11.setTexture(piece_t["1R"]);
	this->piece_s["1R"] = sprite11;

	resource.loadFromFile("assets/Brown/pawn.png");
	resource.setSmooth(true);
	this->piece_t["1P"] = resource;

	sf::Sprite sprite12;
	sprite12.setTexture(piece_t["1P"]);
	this->piece_s["1P"] = sprite12;
}

void display::draw(sf::RenderWindow &window, int mx, int my, std::vector<int> b_x, std::vector<int> b_y, std::vector<sf::Color> b_color, std::vector<int> p_x, std::vector<int> p_y, std::vector<int> p_team, std::vector<std::string> p_type, int p_selected, double score, bool checkWhite, bool checkBlack, std::vector<std::vector<int>> bestMove, std::string depth, bool engine, bool aiw, bool aib, std::vector<double> scores) {
	sf::RectangleShape rectangle(sf::Vector2f(50, 50));

	sf::RectangleShape back(sf::Vector2f(450, 450));
	back.setFillColor(sf::Color(160, 82, 45));
	window.draw(back);

	for (unsigned i = 0; i < b_x.size(); i++) {
		rectangle.setPosition(25 + b_x[i] * 50, 25 + b_y[i] * 50);
		rectangle.setFillColor(b_color[i]);


		window.draw(rectangle);
	}

	for (unsigned i = 0; i < p_type.size(); i++) {
		std::string key = std::to_string(p_team[i]) + p_type[i];
		this->piece_s[key].setPosition(25 + p_x[i] * 50, 25 + p_y[i] * 50);

		if (checkWhite && p_team[i] == -1 && p_type[i] == "K") {
			sf::RectangleShape rect(sf::Vector2f(50, 50));
			rect.setPosition(25 + p_x[i] * 50, 25 + p_y[i] * 50);
			rect.setFillColor(sf::Color(200, 0, 0, 150));


			window.draw(rect);
		}

		if (checkBlack && p_team[i] == 1 && p_type[i] == "K") {
			sf::RectangleShape rect(sf::Vector2f(50, 50));
			rect.setPosition(25 + p_x[i] * 50, 25 + p_y[i] * 50);
			rect.setFillColor(sf::Color(200, 0, 0, 150));


			window.draw(rect);
		}

		if (i == p_selected) {
			this->piece_s[key].setPosition(mx - 25, my - 25);
		}
		window.draw(piece_s[key]);
	}

	sf::Font font;
	font.loadFromFile("assets/fonts/IHATCS__.ttf");

	sf::Text displayScore;
	displayScore.setFillColor(sf::Color::White);
	displayScore.setOutlineColor(sf::Color::Black);
	displayScore.setOutlineThickness(2);
	displayScore.setFont(font);
	displayScore.setCharacterSize(24);
	displayScore.setPosition(525, 50);
	std::string scoreT;
	if (engine) {
		if (std::abs(score) < 990)
			scoreT = "Score: " + std::to_string(score) + "@: " + depth + " search depth.";
		else {
			std::string c = "-";
			if (score > 0)
				c = "+";

			int mScore = 999 - std::abs(score);
			std::vector<int> ms;
			ms.push_back(0);
			ms.push_back(1);
			ms.push_back(1);
			ms.push_back(2);
			ms.push_back(2);
			ms.push_back(3);
			ms.push_back(3);
			ms.push_back(4);
			ms.push_back(4);
			ms.push_back(5);
			ms.push_back(5);
			scoreT = "Score: " + c + "M" + std::to_string(ms[mScore]);
		}
	}
	else {
		scoreT = "Engine is disabled";
	}
	displayScore.setString(scoreT);

	window.draw(displayScore);

	double x = score;

	if (x > 5)
		x = 5;
	if (x < -5)
		x = -5;
	double y = 1.25 / 2 * (0.7*x*x) / ((x*x) + 5) + 0.5;
	if (std::abs(score) >= 90) {
		y = 1;
	}
	double wp;
	double bp;

	if (x >= 0) {
		wp = y;
		bp = 1 - y;
	}
	else {
		wp = 1 - y;
		bp = y;
	}


	sf::RectangleShape displayWhite(sf::Vector2f(35, 400 * wp));
	sf::RectangleShape displayBlack(sf::Vector2f(35, 400 * bp));

	displayWhite.setFillColor(sf::Color(255, 255, 255));
	displayBlack.setFillColor(sf::Color(0, 0, 0));

	displayWhite.setPosition(465, 25);
	displayBlack.setPosition(465, 25 + (400 * wp));

	window.draw(displayWhite);
	window.draw(displayBlack);

	if (engine) {
		sf::RectangleShape bestMovePrev(sf::Vector2f(50, 50));
		bestMovePrev.setPosition(25 + bestMove[2][0] * 50, 25 + bestMove[3][0] * 50);
		bestMovePrev.setFillColor(sf::Color(10, 5, 200, 150));


		window.draw(bestMovePrev);

		sf::RectangleShape bestMoveNew(sf::Vector2f(50, 50));
		bestMoveNew.setPosition(25 + bestMove[0][0] * 50, 25 + bestMove[1][0] * 50);
		bestMoveNew.setFillColor(sf::Color(10, 5, 200, 150));


		window.draw(bestMoveNew);

		sf::Text line;
		line.setFillColor(sf::Color::White);
		line.setOutlineColor(sf::Color::Black);
		line.setOutlineThickness(2);
		line.setFont(font);
		line.setCharacterSize(18);
		for (unsigned i = 0; i < bestMove[0].size(); i++) {
			line.setPosition(525, 80 + (20 * i));
			std::string lineT;
			std::vector<int> lineA;
			lineA.push_back(bestMove[0][i]);
			lineA.push_back(bestMove[1][i]);
			lineA.push_back(bestMove[2][i]);
			lineA.push_back(bestMove[3][i]);
			lineA.push_back(bestMove[4][i]);
			std::string sign = "+";
			if (scores[i] < 0)
				sign = "";
			if (std::abs(scores[i]) < 990)
				lineT = move(lineA) + " " + sign + std::to_string(scores[i]);
			else {
				std::string c = "-";
				if (score > 0)
					c = "+";

				int mScore = 999 - std::abs(scores[i]);
				std::vector<int> ms;
				ms.push_back(0);
				ms.push_back(1);
				ms.push_back(1);
				ms.push_back(2);
				ms.push_back(2);
				ms.push_back(3);
				ms.push_back(3);
				ms.push_back(4);
				ms.push_back(4);
				ms.push_back(5);
				ms.push_back(5);
				lineT = move(lineA) + " " + c + "M" + std::to_string(ms[mScore]);
			}
			line.setString(lineT);
			window.draw(line);
		}
	}

	//Buttons

	sf::RectangleShape analysisR(sf::Vector2f(170, 32));
	analysisR.setPosition(515, 245);
	analysisR.setFillColor(sf::Color(10, 5, 200, 150));


	sf::Text analysis;
	analysis.setFillColor(sf::Color::White);
	analysis.setOutlineColor(sf::Color::Black);
	analysis.setOutlineThickness(1);
	analysis.setFont(font);
	analysis.setCharacterSize(18);
	analysis.setPosition(525, 250);
	analysis.setString("Continuous Analysis");

	window.draw(analysisR);
	window.draw(analysis);

	sf::RectangleShape engineWhiteRECT(sf::Vector2f(170, 32));
	engineWhiteRECT.setPosition(515, 295);
	engineWhiteRECT.setFillColor(sf::Color(10, 5, 200, 150));


	sf::Text engineWhite;
	engineWhite.setFillColor(sf::Color::White);
	engineWhite.setOutlineColor(sf::Color::Black);
	engineWhite.setOutlineThickness(1);
	engineWhite.setFont(font);
	engineWhite.setCharacterSize(18);
	engineWhite.setPosition(525, 300);
	engineWhite.setString("Toggle engine white");

	window.draw(engineWhiteRECT);
	window.draw(engineWhite);

	sf::RectangleShape engineBlackRECT(sf::Vector2f(170, 32));
	engineBlackRECT.setPosition(515,345);
	engineBlackRECT.setFillColor(sf::Color(10, 5, 200, 150));


	sf::Text engineBlack;
	engineBlack.setFillColor(sf::Color::White);
	engineBlack.setOutlineColor(sf::Color::Black);
	engineBlack.setOutlineThickness(1);
	engineBlack.setFont(font);
	engineBlack.setCharacterSize(18);
	engineBlack.setPosition(525, 350);
	engineBlack.setString("Toggle engine black");

	window.draw(engineBlackRECT);
	window.draw(engineBlack);

	sf::RectangleShape fenRECT(sf::Vector2f(170, 32));
	fenRECT.setPosition(515, 395);
	fenRECT.setFillColor(sf::Color(10, 5, 200, 150));


	sf::Text fen;
	fen.setFillColor(sf::Color::White);
	fen.setOutlineColor(sf::Color::Black);
	fen.setOutlineThickness(1);
	fen.setFont(font);
	fen.setCharacterSize(18);
	fen.setPosition(525, 400);
	fen.setString("Fen from clipboard");

	window.draw(fenRECT);
	window.draw(fen);

	sf::RectangleShape fenPRECT(sf::Vector2f(170, 32));
	fenPRECT.setPosition(715, 395);
	fenPRECT.setFillColor(sf::Color(10, 5, 200, 150));


	sf::Text fenP;
	fenP.setFillColor(sf::Color::White);
	fenP.setOutlineColor(sf::Color::Black);
	fenP.setOutlineThickness(1);
	fenP.setFont(font);
	fenP.setCharacterSize(18);
	fenP.setPosition(725, 400);
	fenP.setString("Fen from position");

	window.draw(fenPRECT);
	window.draw(fenP);


	sf::Text depthT;
	depthT.setFillColor(sf::Color::White);
	depthT.setOutlineColor(sf::Color::Black);
	depthT.setOutlineThickness(1);
	depthT.setFont(font);
	depthT.setCharacterSize(18);
	depthT.setPosition(725 + 65, 270);
	depthT.setString(depth);

	window.draw(depth_buttonS);
	window.draw(depthT);

	if (!aiw) {
		b0.setPosition(725, 295);
		window.draw(b0);
	}
	else {
		b1.setPosition(725, 295);
		window.draw(b1);
	}
	if (!aib) {
		b0.setPosition(725, 345);
		window.draw(b0);
	}
	else {
		b1.setPosition(725, 345);
		window.draw(b1);
	}
}

std::string display::move(std::vector<int> move) {
	int x = move[0];
	int px = move[2];
	int y = move[1];
	std::string t;
	if (move[4] == 0)
		t = "P";
	if (move[4] == 1)
		t = "N";
	if (move[4] == 2)
		t = "B";
	if (move[4] == 3)
		t = "R";
	if (move[4] == 4)
		t = "Q";
	if (move[4] == 5)
		t = "K";

	std::vector<std::string> file;
	file.push_back("a");
	file.push_back("b");
	file.push_back("c");
	file.push_back("d");
	file.push_back("e");
	file.push_back("f");
	file.push_back("g");
	file.push_back("h");

	std::vector<std::string> rank;
	rank.push_back("8");
	rank.push_back("7");
	rank.push_back("6");
	rank.push_back("5");
	rank.push_back("4");
	rank.push_back("3");
	rank.push_back("2");
	rank.push_back("1");

	std::string notation;

	if (t != "P")
		notation = t + file[x] + rank[y];

	if (t == "P" && px == x)
		notation = file[x] + rank[y];

	if (t == "P" && px != x)
		notation = file[x] + "x" + rank[y];

	if (t == "P") {
		if (y == 0 || y == 7)
			notation += "=Q";
	}
	return notation;
}