#include "pieces.h"

void pieces::setup() {
	std::srand(time(NULL));
	this->selected = -1;

	this->engineBlack = false;
	this->engineWhite = false;
	this->breakswitch = true;
	this->showCont = false;

	for (unsigned i = 0; i <= 1; i++) {
		int t;
		if (i == 0)
			t = -1;
		if (i == 1)
			t = 1;

		int y;
		if (t == -1)
			y = 7;
		if (t == 1)
			y = 0;

		this->piece_type.push_back("K");
		this->piece_x.push_back(4);
		this->piece_y.push_back(y);
		this->piece_team.push_back(t);

		this->piece_type.push_back("Q");
		this->piece_x.push_back(3);
		this->piece_y.push_back(y);
		this->piece_team.push_back(t);

		this->piece_type.push_back("B");
		this->piece_x.push_back(2);
		this->piece_y.push_back(y);
		this->piece_team.push_back(t);
		this->piece_type.push_back("B");
		this->piece_x.push_back(5);
		this->piece_y.push_back(y);
		this->piece_team.push_back(t);

		this->piece_type.push_back("N");
		this->piece_x.push_back(1);
		this->piece_y.push_back(y);
		this->piece_team.push_back(t);
		this->piece_type.push_back("N");
		this->piece_x.push_back(6);
		this->piece_y.push_back(y);
		this->piece_team.push_back(t);

		this->piece_type.push_back("R");
		this->piece_x.push_back(0);
		this->piece_y.push_back(y);
		this->piece_team.push_back(t);
		this->piece_type.push_back("R");
		this->piece_x.push_back(7);
		this->piece_y.push_back(y);
		this->piece_team.push_back(t);

		if (t == -1)
			y = 6;
		if (t == 1)
			y = 1;

		for (unsigned x = 0; x <= 7; x++) {
			this->piece_type.push_back("P");
			this->piece_x.push_back(x);
			this->piece_y.push_back(y);
			this->piece_team.push_back(t);
		}
	}

	for (unsigned i = 0; i < this->piece_type.size(); i++) {
		start_x.push_back(piece_x[i]);
		start_y.push_back(piece_y[i]);
	}

	for (unsigned x = 0; x <= 7; x++) {
		std::vector<std::string> a;
		this->grid.push_back(a);
		for (unsigned y = 0; y <= 7; y++) {
			this->grid[x].push_back("  ");
		}
	}

	for (unsigned i = 0; i < this->piece_type.size(); i++) {
		std::string b;
		if (this->piece_team[i] == 1) {
			b = "+";
		}
		if (this->piece_team[i] == -1) {
			b = "-";
		}
		this->grid[piece_x[i]][piece_y[i]] = b + this->piece_type[i];
	}

	/*for (unsigned y = 0; y <= 7; y++) {
		for (unsigned x = 0; x <= 7; x++) {
			std::cout << "[" + this->grid[x][y] + "]";
		}
		std::cout << "" << std::endl;
		std::cout << "" << std::endl;
	} */

	this->searchDepth = 4;
	this->displayDepth = "-1";

	if (this->toMove == 1 && this->engineBlack)
		this->score = minimax(this->searchDepth - 1, this->searchDepth - 1, this->toMove, this->piece_type, this->piece_x, this->piece_y, this->start_x, this->start_y, this->piece_team, -99, 99);
	if (this->toMove == -1 && this->engineWhite)
		this->score = minimax(this->searchDepth - 1, this->searchDepth - 1, this->toMove, this->piece_type, this->piece_x, this->piece_y, this->start_x, this->start_y, this->piece_team, -99, 99);
}

std::vector<int> pieces::get_x() {

	return this->piece_x;
}

std::vector<int> pieces::get_y() {

	return this->piece_y;
}

std::vector<int> pieces::get_team() {

	return this->piece_team;
}

std::vector<std::string> pieces::get_type() {

	return this->piece_type;
}

int pieces::get_selected() {

	return this->selected;
}

std::string pieces::get_depth() {
	if (this->showCont)
		return std::to_string(this->contDepth);
	if (this->displayDepth == "-1")
		return std::to_string(this->searchDepth);
	return this->displayDepth;
}

void pieces::select(int x, int y) {
	for (unsigned ux = 0; ux <= 7; ux++) {
		for (unsigned uy = 0; uy <= 7; uy++) {
			if (x > 25 + ux * 50 && x < 75 + ux * 50) {
				x = ux;
			}
			if (y > 25 + uy * 50 && y < 75 + uy * 50) {
				y = uy;
			}

		}
	}
	for (unsigned i = 0; i < this->piece_type.size(); i++) {
		if (this->piece_x[i] == x && this->piece_y[i] == y) {
			this->selected = i;
		}

	}
}

void pieces::release(int x, int y) {
	if (x < 450 && y < 450) {

		if (this->selected != -1) {
			for (unsigned ux = 0; ux <= 7; ux++) {
				for (unsigned uy = 0; uy <= 7; uy++) {
					if (x > 25 + ux * 50 && x < 75 + ux * 50) {
						x = ux;
					}
					if (y > 25 + uy * 50 && y < 75 + uy * 50) {
						y = uy;
					}

				}
			}

			if (x < 8 && x >= 0 && y < 8 && y >= 0) {
				bool legalMove = legalMoveFunc(this->piece_x[this->selected], this->piece_y[this->selected], this->piece_type[this->selected], this->piece_team[this->selected], this->start_x[this->selected], this->start_y[this->selected], x, y, this->piece_type, this->piece_x, this->piece_y, this->start_x, this->start_y, this->piece_team, this->grid);
				int a = moveSquare(x, y, this->piece_team[this->selected], this->grid);

				//Make the move to see if the player is in check after the move is made
				bool check = checkMove(this->piece_team[this->selected], this->selected, x, y, this->piece_type, this->piece_x, this->piece_y, this->start_x, this->start_y, this->piece_team, this->grid);

				bool passant = isPassant(this->piece_x[this->selected], this->piece_y[this->selected], this->piece_type[this->selected], this->piece_team[this->selected], this->start_x[this->selected], this->start_y[this->selected], x, y);
				if (passant) {
					legalMove = true;
				}
				if (legalMove && a != -1 && !check && this->piece_team[this->selected] == this->toMove) {
					this->grid[this->piece_x[this->selected]][this->piece_y[this->selected]] = "  ";

					if (this->piece_type[this->selected] == "K") {
						if (x - this->piece_x[this->selected] == 2) {

							for (unsigned u = 0; u < piece_team.size(); u++) {
								if (piece_x[u] == 7 && piece_y[u] == y) {
									this->grid[7][y] = "  ";
									std::string b;
									if (this->piece_team[u] == 1) {
										b = "+";
									}
									if (this->piece_team[u] == -1) {
										b = "-";
									}
									this->piece_x[u] = 5;

									this->grid[piece_x[u]][piece_y[u]] = b + this->piece_type[u];
								}
							}

						}

						if (x - this->piece_x[this->selected] == -2) {

							for (unsigned u = 0; u < piece_team.size(); u++) {
								if (piece_x[u] == 0 && piece_y[u] == y) {
									this->grid[0][y] = "  ";

									std::string b;
									if (this->piece_team[u] == 1) {
										b = "+";
									}
									if (this->piece_team[u] == -1) {
										b = "-";
									}
									this->piece_x[u] = 3;

									this->grid[piece_x[u]][piece_y[u]] = b + this->piece_type[u];
								}
							}

						}
					}
					int prevX = this->piece_x[this->selected];
					int prevY = this->piece_y[this->selected];

					this->piece_x[this->selected] = x;
					this->piece_y[this->selected] = y;

					if (this->piece_type[this->selected] == "P") {
						if (this->piece_y[this->selected] == 0 || this->piece_y[this->selected] == 7) {
							this->piece_type[this->selected] = "Q";
						}
					}

					std::string b;
					if (this->piece_team[this->selected] == 1) {
						b = "+";
					}
					if (this->piece_team[this->selected] == -1) {
						b = "-";
					}
					this->grid[piece_x[this->selected]][piece_y[this->selected]] = b + this->piece_type[this->selected];

					//Remove a captured piece
					if (a == 2) {
						for (unsigned o = 0; o < this->piece_team.size(); o++) {
							if (this->piece_x[o] == x && this->piece_y[o] == y && this->piece_team[o] != this->piece_team[this->selected]) {
								this->piece_x.erase(this->piece_x.begin() + o);
								this->piece_y.erase(this->piece_y.begin() + o);
								this->piece_team.erase(this->piece_team.begin() + o);
								this->piece_type.erase(this->piece_type.begin() + o);
								this->start_x.erase(this->start_x.begin() + o);
								this->start_y.erase(this->start_y.begin() + o);
							}
						}
					}
					if (passant) {
						for (unsigned o = 0; o < this->piece_team.size(); o++) {
							if (this->piece_x[o] == x && this->piece_y[o] == y + this->piece_team[o] && this->piece_team[o] != this->piece_team[this->selected]) {
								this->piece_x.erase(this->piece_x.begin() + o);
								this->piece_y.erase(this->piece_y.begin() + o);
								this->piece_team.erase(this->piece_team.begin() + o);
								this->piece_type.erase(this->piece_type.begin() + o);
								this->start_x.erase(this->start_x.begin() + o);
								this->start_y.erase(this->start_y.begin() + o);
							}
						}
					}

					this->toMove *= -1;
					this->move++;
					this->lastMoveX = x;
					this->lastMoveY = y;
					this->lastMoveType = this->piece_type[this->selected];
					this->lastMovePrevX = prevX;
					this->lastMovePrevY = prevY;

					if (this->toMove == 1 && this->engineBlack)
						this->score = minimax(this->searchDepth - 1, this->searchDepth - 1, this->toMove, this->piece_type, this->piece_x, this->piece_y, this->start_x, this->start_y, this->piece_team, -99, 99);
					if (this->toMove == -1 && this->engineWhite)
						this->score = minimax(this->searchDepth - 1, this->searchDepth - 1, this->toMove, this->piece_type, this->piece_x, this->piece_y, this->start_x, this->start_y, this->piece_team, -99, 99);
				}

			}
			this->selected = -1;
			/*
			std::cout << "-------------------------------" << std::endl;
			std::cout << "" << std::endl;
			std::cout << "-------------------------------" << std::endl;
			for (unsigned y = 0; y <= 7; y++) {
				for (unsigned x = 0; x <= 7; x++) {
					std::cout << "[" + this->grid[x][y] + "]";
				}
				std::cout << "" << std::endl;
				std::cout << "" << std::endl;
			} */

		}
	}

	if (x > 715 && x < 715 + 170) {
		if (y > 295 && y < 295 + 32) {
			if (x < 715 + (170 / 2)) {
				this->searchDepth++;
			}
			if (x > 715 + (170 / 2)) {
				this->searchDepth -= 1;
				std::cout << this->searchDepth;
				if (this->searchDepth < 1)
					this->searchDepth = 1;

			}
		}
		if (y > 395 && y < 395 + 32) {
			std::string fen = posFen(this->grid,this->toMove);

			const char* output = fen.c_str();
			const size_t len = strlen(output) + 1;
			HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
			memcpy(GlobalLock(hMem), output, len);
			GlobalUnlock(hMem);
			OpenClipboard(0);
			EmptyClipboard();
			SetClipboardData(CF_TEXT, hMem);
			CloseClipboard();
		}
	}
	if (x > 515 && x < 515 + 170) {

		if (y > 245 && y < 245 + 32) {
			this->contDepth = 1;
			this->showCont = !this->showCont;
			if (this->showCont == true)
				this->breakswitch = false;

			if (this->showCont == false)
				this->breakswitch = true;
			contanalysis();
		}

		if (y > 295 && y < 295 + 32) {
			this->engineWhite = !this->engineWhite;
			if (this->toMove == -1 && this->engineWhite)
				this->score = minimax(this->searchDepth - 1, this->searchDepth - 1, this->toMove, this->piece_type, this->piece_x, this->piece_y, this->start_x, this->start_y, this->piece_team, -99, 99);
		}

		if (y > 345 && y < 345 + 32) {
			this->engineBlack = !this->engineBlack;
			if (this->toMove == 1 && this->engineBlack)
				this->score = minimax(this->searchDepth - 1, this->searchDepth - 1, this->toMove, this->piece_type, this->piece_x, this->piece_y, this->start_x, this->start_y, this->piece_team, -99, 99);
		}

		if (y > 395 && y < 395 + 32) {
			std::string fen = sf::Clipboard::getString();

			int px = 0;
			int py = 0;

			this->piece_x.clear();
			this->piece_y.clear();
			this->piece_team.clear();
			this->piece_type.clear();

			int n = fen.length();
			char char_array[100];

			for (int i = 0; i < n; i++) {
				char_array[i] = fen[i];
			}

			for (int i = 0; i < n; i++) {
				char ch = char_array[i];
				if (ch == *"p") {
					this->piece_type.push_back("P");
					this->piece_x.push_back(px);
					this->piece_y.push_back(py);
					this->piece_team.push_back(1);
					px += 1;
				}
				if (ch == *"n") {
					this->piece_type.push_back("N");
					this->piece_x.push_back(px);
					this->piece_y.push_back(py);
					this->piece_team.push_back(1);
					px += 1;
				}
				if (ch == *"k") {
					this->piece_type.push_back("K");
					this->piece_x.push_back(px);
					this->piece_y.push_back(py);
					this->piece_team.push_back(1);
					px += 1;
				}
				if (ch == *"b") {
					this->piece_type.push_back("B");
					this->piece_x.push_back(px);
					this->piece_y.push_back(py);
					this->piece_team.push_back(1);
					px += 1;
				}
				if (ch == *"r") {
					this->piece_type.push_back("R");
					this->piece_x.push_back(px);
					this->piece_y.push_back(py);
					this->piece_team.push_back(1);
					px += 1;
				}
				if (ch == *"q") {
					this->piece_type.push_back("Q");
					this->piece_x.push_back(px);
					this->piece_y.push_back(py);
					this->piece_team.push_back(1);
					px += 1;
				}

				if (ch == *"P") {
					this->piece_type.push_back("P");
					this->piece_x.push_back(px);
					this->piece_y.push_back(py);
					this->piece_team.push_back(-1);
					px += 1;
				}
				if (ch == *"N") {
					this->piece_type.push_back("N");
					this->piece_x.push_back(px);
					this->piece_y.push_back(py);
					this->piece_team.push_back(-1);
					px += 1;
				}
				if (ch == *"K") {
					this->piece_type.push_back("K");
					this->piece_x.push_back(px);
					this->piece_y.push_back(py);
					this->piece_team.push_back(-1);
					px += 1;
				}
				if (ch == *"B") {
					this->piece_type.push_back("B");
					this->piece_x.push_back(px);
					this->piece_y.push_back(py);
					this->piece_team.push_back(-1);
					px += 1;
				}
				if (ch == *"R") {
					this->piece_type.push_back("R");
					this->piece_x.push_back(px);
					this->piece_y.push_back(py);
					this->piece_team.push_back(-1);
					px += 1;
				}
				if (ch == *"Q") {
					this->piece_type.push_back("Q");
					this->piece_x.push_back(px);
					this->piece_y.push_back(py);
					this->piece_team.push_back(-1);
					px += 1;
				}
				if (isdigit(ch)) {
					px += std::stoi(&ch);
				}
				if (ch == *"/") {
					py += 1;
					px = 0;
				}
				if (ch == *" ") {
					if (char_array[i + 1] == *"w")
						this->toMove = -1;
					if (char_array[i + 1] == *"b")
						this->toMove = 1;

					break;
				}
			}

			this->grid.clear();

			for (unsigned x = 0; x <= 7; x++) {
				std::vector<std::string> a;
				this->grid.push_back(a);
				for (unsigned y = 0; y <= 7; y++) {
					this->grid[x].push_back("  ");
				}
			}

			for (unsigned i = 0; i < this->piece_type.size(); i++) {
				std::string b;
				if (this->piece_team[i] == 1) {
					b = "+";
				}
				if (this->piece_team[i] == -1) {
					b = "-";
				}
				this->grid[piece_x[i]][piece_y[i]] = b + this->piece_type[i];
			}

			for (unsigned y = 0; y <= 7; y++) {
				for (unsigned x = 0; x <= 7; x++) {
					std::cout << "[" + this->grid[x][y] + "]";
				}
				std::cout << "" << std::endl;
				std::cout << "" << std::endl;
			}

		}
	}
}

bool pieces::isPassant(int x, int y, std::string type, int team, int startX, int startY, int moveX, int moveY) {
	if (type == "P") {
		if (std::abs(moveX - x) == 1 && moveY - y == team) {
			if (this->grid[moveX][y] != "  ") {
				int ts;
				if (team == 1)
					ts = 6;
				if (team == -1)
					ts = 1;
				if (this->lastMoveX == moveX && this->lastMoveY == y && this->lastMovePrevY == ts) {
					if (this->lastMoveType == "P") {
						return true;
					}
				}

			}
		}
	}
	return false;
}

bool pieces::legalMoveFunc(int x, int y, std::string type, int team, int startX, int startY, int moveX, int moveY, std::vector<std::string> p_type, std::vector<int> p_x, std::vector<int> p_y, std::vector<int> s_x, std::vector<int> s_y, std::vector<int> p_team, std::vector<std::vector<std::string>> localGrid) {
	if (type == "P") {
		if (moveX == x) { //move forwards
			if (localGrid[x][moveY] == "  ") {
				if (x == startX && y == startY) {
					if (moveY == startY + (team * 2) && localGrid[x][moveY - team] == "  ") {
						return true;
					}
				}

				if (moveY == y + team) {
					return true;
				}

			}
		}
		else if (std::abs(moveX - x) == 1 && moveY - y == team) {
			if (localGrid[moveX][moveY] != "  ") {
				return true;
			}
		}
	}

	if (type == "N") {
		int sX = std::abs(moveX - x);
		int sY = std::abs(moveY - y);

		if (sX == 2 && sY == 1) {
			return true;
		}

		if (sY == 2 && sX == 1) {
			return true;
		}

	}

	if (type == "R") {
		if (moveX == x || moveY == y) {
			if (moveX == x) {
				int d = moveY - y;

				if (d > 0)
					d = 1;
				else if (d < 0)
					d = -1;

				int Cy = moveY - d;
				while (Cy != y) {
					if (localGrid[x][Cy] != "  ") {
						return false;
					}
					Cy -= d;
				}
			}
			if (moveY == y) {
				int d = moveX - x;

				if (d > 0)
					d = 1;
				else if (d < 0)
					d = -1;

				int Cx = moveX - d;
				while (Cx != x) {
					if (localGrid[Cx][y] != "  ") {
						return false;
					}
					Cx -= d;
				}
			}

			return true;
		}
	}

	if (type == "B") {
		int sX = moveX - x;
		int sY = moveY - y;

		if (std::abs(sX) == std::abs(sY)) {
			int Dx = sX;
			int Dy = sY;

			if (Dx > 0)
				Dx = 1;
			else if (Dx < 0)
				Dx = -1;
			if (Dy > 0)
				Dy = 1;
			else if (Dy < 0)
				Dy = -1;

			int Cx = x + Dx;
			int Cy = y + Dy;

			while (Cx != moveX) {
				if (localGrid[Cx][Cy] != "  ") {

					return false;
				}
				Cx += Dx;
				Cy += Dy;
			}

			return true;
		}
	}
	if (type == "Q") {
		if (moveX == x || moveY == y) {
			if (moveX == x) {
				int d = moveY - y;

				if (d > 0)
					d = 1;
				else if (d < 0)
					d = -1;

				int Cy = moveY - d;
				while (Cy != y) {
					if (localGrid[x][Cy] != "  ") {
						return false;
					}
					Cy -= d;
				}
			}
			if (moveY == y) {
				int d = moveX - x;

				if (d > 0)
					d = 1;
				else if (d < 0)
					d = -1;

				int Cx = moveX - d;
				while (Cx != x) {
					if (localGrid[Cx][y] != "  ") {
						return false;
					}
					Cx -= d;
				}
			}

			return true;
		}
		int sX = moveX - x;
		int sY = moveY - y;

		if (std::abs(sX) == std::abs(sY)) {
			int Dx = sX;
			int Dy = sY;

			if (Dx > 0)
				Dx = 1;
			else if (Dx < 0)
				Dx = -1;
			if (Dy > 0)
				Dy = 1;
			else if (Dy < 0)
				Dy = -1;

			int Cx = x + Dx;
			int Cy = y + Dy;

			while (Cx != moveX) {
				if (localGrid[Cx][Cy] != "  ") {

					return false;
				}
				Cx += Dx;
				Cy += Dy;
			}

			return true;
		}
	}

	if (type == "K") {
		int sX = moveX - x;
		int sY = moveY - y;

		if (x == startX && y == startY) {
			if (std::abs(sX) == 2 && sY == 0) {
				int rX;
				int Cx;
				int d;
				if (sX == -2) {
					rX = 0;
					Cx = 1;
					d = 1;
				}
				if (sX == 2) {
					rX = 7;
					Cx = 6;
					d = -1;
				}

				while (Cx != x) {
					if (localGrid[Cx][y] != "  ") {
						return false;
					}
					Cx += d;
				}
				std::string b;
				if (team == 1) {
					b = "+";
				}
				if (team == -1) {
					b = "-";
				}
				if (localGrid[rX][y] == b + "R") {
					return true;
				}
			}
		}

		if (std::abs(sX) > 1 || std::abs(sY) > 1) {
			return false;
		}
		if (std::abs(sX) <= 1 && std::abs(sY) <= 1) {
			return true;
		}
		return true;
	}
	return false;
}

int pieces::moveSquare(int x, int y, int team, std::vector<std::vector<std::string>> localGrid) {
	if (localGrid[x][y] == "  ")
		return 1;
	else {
		std::string b;
		if (team == 1) {
			b = "+";
		}
		if (team == -1) {
			b = "-";
		}
		std::string c = localGrid[x][y];
		std::string s(1, c.at(0));
		if (s != b) {
			return 2;
		}
	}
	return -1;
}

bool pieces::inCheck(int team, std::vector<std::string> p_type, std::vector<int> p_x, std::vector<int> p_y, std::vector<int> s_x, std::vector<int> s_y, std::vector<int> p_team, std::vector<std::vector<std::string>> localGrid) {
	int kingX;
	int kingY;

	for (unsigned u = 0; u < p_team.size(); u++) {
		if (p_type[u] == "K" && p_team[u] == team) {
			kingX = p_x[u];
			kingY = p_y[u];
		}
	}

	for (unsigned u = 0; u < p_team.size(); u++) {
		if (p_team[u] != team) {
			std::string t = p_type[u];
			int x = p_x[u];
			int y = p_y[u];

			if (t == "P") {
				if (std::abs(kingX - x) == 1 && y == kingY + team) {
					return true;
				}
			}

			if (t == "N") {
				if (std::abs(kingX - x) == 2 && std::abs(kingY - y) == 1) {
					return true;
				}
				if (std::abs(kingX - x) == 1 && std::abs(kingY - y) == 2) {
					return true;
				}
			}

			if (t == "R") {
				if (kingX == x || kingY == y) {
					if (kingX == x) {
						int Dy = y - kingY;
						if (Dy > 0)
							Dy = 1;
						if (Dy < 0)
							Dy = -1;

						int Cy = y - Dy;
						bool a = true;
						while (Cy != kingY - Dy) {
							for (unsigned e = 0; e < p_team.size(); e++) {
								if (p_x[e] == x && p_y[e] == Cy) {
									if (kingY == Cy && p_team[e] == team && a) {
										return true;

									}
									else if (p_team[e] != team) {
										a = false;
									}
									else if (kingY != Cy) {
										a = false;
									}
								}
							}
							Cy -= Dy;
						}
					}

					if (kingY == y) {
						int Dx = x - kingX;
						if (Dx > 0)
							Dx = 1;
						if (Dx < 0)
							Dx = -1;

						int Cx = x - Dx;
						bool a = true;
						while (Cx != kingX - Dx) {
							for (unsigned e = 0; e < p_team.size(); e++) {
								if (p_y[e] == y && p_x[e] == Cx) {
									if (kingX == Cx && p_team[e] == team && a) {
										return true;
									}
									else if (p_team[e] != team) {
										a = false;
									}
									else if (kingX != Cx) {
										a = false;
									}
								}
							}
							Cx -= Dx;
						}
					}

				}
			}

			if (t == "B") {
				int sX = x - kingX;
				int sY = y - kingY;

				if (std::abs(sX) == std::abs(sY)) {
					int Dx = sX;
					int Dy = sY;

					if (Dx > 0)
						Dx = 1;
					else if (Dx < 0)
						Dx = -1;
					if (Dy > 0)
						Dy = 1;
					else if (Dy < 0)
						Dy = -1;

					int Cx = x - Dx;
					int Cy = y - Dy;
					bool a = true;

					while (Cy != kingY - Dy) {
						for (unsigned e = 0; e < p_team.size(); e++) {
							if (p_x[e] == Cx && p_y[e] == Cy) {
								if (Cy == kingY && a) {
									return true;
								}
								else {
									a = false;
								}
							}
						}
						Cy -= Dy;
						Cx -= Dx;
					}

				}
			}

			if (t == "K") {
				int sX = x - kingX;
				int sY = y - kingY;

				if (std::abs(sX) <= 1 && std::abs(sY) <= 1)
					return true;
			}

			if (t == "Q") {
				int sX = x - kingX;
				int sY = y - kingY;

				if (std::abs(sX) == std::abs(sY)) {
					int Dx = sX;
					int Dy = sY;

					if (Dx > 0)
						Dx = 1;
					else if (Dx < 0)
						Dx = -1;
					if (Dy > 0)
						Dy = 1;
					else if (Dy < 0)
						Dy = -1;

					int Cx = x - Dx;
					int Cy = y - Dy;
					bool a = true;
					while (Cy != kingY - Dy) {
						for (unsigned e = 0; e < p_team.size(); e++) {
							if (p_x[e] == Cx && p_y[e] == Cy) {
								if (Cy == kingY && a) {
									return true;
								}
								else {
									a = false;
								}
							}
						}
						Cy -= Dy;
						Cx -= Dx;
					}

				}
				if (kingX == x || kingY == y) {
					if (kingX == x) {
						int Dy = y - kingY;
						if (Dy > 0)
							Dy = 1;
						if (Dy < 0)
							Dy = -1;

						int Cy = y - Dy;
						bool a = true;
						while (Cy != kingY - Dy) {
							for (unsigned e = 0; e < p_team.size(); e++) {
								if (p_x[e] == x && p_y[e] == Cy) {
									if (kingY == Cy && p_team[e] == team && a) {
										return true;
									}
									else if (p_team[e] != team) {
										a = false;
									}
									else if (kingY != Cy) {
										a = false;
									}
								}
							}
							Cy -= Dy;
						}
					}

					if (kingY == y) {
						int Dx = x - kingX;
						if (Dx > 0)
							Dx = 1;
						if (Dx < 0)
							Dx = -1;

						int Cx = x - Dx;
						bool a = true;
						while (Cx != kingX - Dx) {
							for (unsigned e = 0; e < p_team.size(); e++) {
								if (p_y[e] == y && p_x[e] == Cx) {
									if (kingX == Cx && p_team[e] == team && a) {
										return true;
									}
									else if (p_team[e] != team) {
										a = false;
									}
									else if (kingX != Cx) {
										a = false;
									}
								}
							}
							Cx -= Dx;
						}
					}

				}

			}
		}
	}

	return false;
}

void pieces::legalMoveList(int team, std::vector<std::string> p_type, std::vector<int> p_x, std::vector<int> p_y, std::vector<int> s_x, std::vector<int> s_y, std::vector<int> p_team) {

	std::vector<std::vector<std::string>> localGrid;

	for (unsigned x = 0; x <= 7; x++) {
		std::vector<std::string> a;
		localGrid.push_back(a);
		for (unsigned y = 0; y <= 7; y++) {
			localGrid[x].push_back("  ");
		}
	}

	for (unsigned i = 0; i < p_team.size(); i++) {
		std::string b;
		if (p_team[i] == 1) {
			b = "+";
		}
		if (p_team[i] == -1) {
			b = "-";
		}
		localGrid[p_x[i]][p_y[i]] = b + p_type[i];
	}

	std::vector<int> LegalMovesX;
	std::vector<std::string> LegalMovesType;
	std::vector<int> LegalMovesY;
	std::vector<int> LegalMovesPrevX;
	std::vector<int> LegalMovesPrevY;

	for (unsigned j = 0; j < p_team.size(); j++) {
		if (p_team[j] == team) {
			int x;
			int y;
			if (p_type[j] == "P") {

				x = p_x[j];
				y = p_y[j] + p_team[j] * 2;

				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					if (legalMoveFunc(p_x[j], p_y[j], p_type[j], p_team[j], s_x[j], s_y[j], x, y, p_type, p_x, p_x, s_x, s_x, p_team, localGrid)) {
						if (moveSquare(x, y, team, localGrid) != -1) {
							bool check = checkMove(team, j, x, y, p_type, p_x, p_y, s_x, s_y, p_team, localGrid);
							if (!check) {
								LegalMovesX.push_back(x);
								LegalMovesY.push_back(y);
								LegalMovesType.push_back(p_type[j]);
								LegalMovesPrevX.push_back(p_x[j]);
								LegalMovesPrevY.push_back(p_y[j]);
							}
						}
					}
				}

				for (unsigned Cx = 0; Cx <= 2; Cx++) {
					x = p_x[j] + Cx - 1;
					y = p_y[j] + p_team[j];

					if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
						if (legalMoveFunc(p_x[j], p_y[j], p_type[j], p_team[j], s_x[j], s_y[j], x, y, p_type, p_x, p_x, s_x, s_x, p_team, localGrid) || isPassant(p_x[j], p_y[j], p_type[j], p_team[j], s_x[j], s_y[j], x, y)) {
							if (moveSquare(x, y, team, localGrid) != -1) {
								bool check = checkMove(team, j, x, y, p_type, p_x, p_y, s_x, s_y, p_team, localGrid);
								if (!check) {
									LegalMovesX.push_back(x);
									LegalMovesY.push_back(y);
									LegalMovesType.push_back(p_type[j]);
									LegalMovesPrevX.push_back(p_x[j]);
									LegalMovesPrevY.push_back(p_y[j]);
								}
							}
						}
					}
				}
			}

			if (p_type[j] == "N") {
				std::vector<int> Cx;
				std::vector<int> Cy;

				x = p_x[j] + 1;
				y = p_y[j] + 2;
				Cx.push_back(x);
				Cy.push_back(y);

				x = p_x[j] + 2;
				y = p_y[j] + 1;
				Cx.push_back(x);
				Cy.push_back(y);

				x = p_x[j] - 1;
				y = p_y[j] + 2;
				Cx.push_back(x);
				Cy.push_back(y);

				x = p_x[j] + 2;
				y = p_y[j] - 1;
				Cx.push_back(x);
				Cy.push_back(y);

				x = p_x[j] + 1;
				y = p_y[j] - 2;
				Cx.push_back(x);
				Cy.push_back(y);

				x = p_x[j] - 2;
				y = p_y[j] + 1;
				Cx.push_back(x);
				Cy.push_back(y);

				x = p_x[j] - 1;
				y = p_y[j] - 2;
				Cx.push_back(x);
				Cy.push_back(y);

				x = p_x[j] - 2;
				y = p_y[j] - 1;
				Cx.push_back(x);
				Cy.push_back(y);

				for (unsigned u = 0; u < Cx.size(); u++) {
					x = Cx[u];
					y = Cy[u];

					if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
						if (legalMoveFunc(p_x[j], p_y[j], p_type[j], p_team[j], s_x[j], s_y[j], x, y, p_type, p_x, p_x, s_x, s_x, p_team, localGrid)) {
							if (moveSquare(x, y, team, localGrid) != -1) {
								bool check = checkMove(team, j, x, y, p_type, p_x, p_y, s_x, s_y, p_team, localGrid);
								if (!check) {
									LegalMovesX.push_back(x);
									LegalMovesY.push_back(y);
									LegalMovesType.push_back(p_type[j]);
									LegalMovesPrevX.push_back(p_x[j]);
									LegalMovesPrevY.push_back(p_y[j]);
								}
							}
						}
					}

				}

			}

			if (p_type[j] == "R") {
				std::vector<int> Cx;
				std::vector<int> Cy;
				for (unsigned Cs = 0; Cs <= 7; Cs++) {
					Cx.push_back(p_x[j]);
					Cy.push_back(Cs);

					Cx.push_back(Cs);
					Cy.push_back(p_y[j]);
				}

				for (unsigned u = 0; u < Cx.size(); u++) {
					x = Cx[u];
					y = Cy[u];

					if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
						if (legalMoveFunc(p_x[j], p_y[j], p_type[j], p_team[j], s_x[j], s_y[j], x, y, p_type, p_x, p_x, s_x, s_x, p_team, localGrid)) {
							if (moveSquare(x, y, team, localGrid) != -1) {
								bool check = checkMove(team, j, x, y, p_type, p_x, p_y, s_x, s_y, p_team, localGrid);
								if (!check) {
									LegalMovesX.push_back(x);
									LegalMovesY.push_back(y);
									LegalMovesType.push_back(p_type[j]);
									LegalMovesPrevX.push_back(p_x[j]);
									LegalMovesPrevY.push_back(p_y[j]);
								}
							}
						}
					}

				}

			}

			if (p_type[j] == "B") {
				std::vector<int> Cx;
				std::vector<int> Cy;
				for (unsigned u = 0; u < 14; u++) {
					Cx.push_back(p_x[j] + u - 7);
					Cy.push_back(p_y[j] + u - 7);

					Cx.push_back(p_x[j] - (u - 7));
					Cy.push_back(p_y[j] + u - 7);
				}

				for (unsigned u = 0; u < Cx.size(); u++) {
					x = Cx[u];
					y = Cy[u];

					if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
						if (legalMoveFunc(p_x[j], p_y[j], p_type[j], p_team[j], s_x[j], s_y[j], x, y, p_type, p_x, p_x, s_x, s_x, p_team, localGrid)) {
							if (moveSquare(x, y, team, localGrid) != -1) {
								bool check = checkMove(team, j, x, y, p_type, p_x, p_y, s_x, s_y, p_team, localGrid);
								if (!check) {
									LegalMovesX.push_back(x);
									LegalMovesY.push_back(y);
									LegalMovesType.push_back(p_type[j]);
									LegalMovesPrevX.push_back(p_x[j]);
									LegalMovesPrevY.push_back(p_y[j]);
								}
							}
						}
					}

				}

			}

			if (p_type[j] == "Q") {
				std::vector<int> Cx;
				std::vector<int> Cy;
				for (unsigned u = 0; u < 14; u++) {
					Cx.push_back(p_x[j] + u - 7);
					Cy.push_back(p_y[j] + u - 7);

					Cx.push_back(p_x[j] - (u - 7));
					Cy.push_back(p_y[j] + u - 7);

					Cx.push_back(p_x[j]);
					Cy.push_back(p_y[j] + u - 7);

					Cx.push_back(p_x[j] + u - 7);
					Cy.push_back(p_y[j]);

				}

				for (unsigned u = 0; u < Cx.size(); u++) {
					x = Cx[u];
					y = Cy[u];

					if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
						if (legalMoveFunc(p_x[j], p_y[j], p_type[j], p_team[j], s_x[j], s_y[j], x, y, p_type, p_x, p_x, s_x, s_x, p_team, localGrid)) {
							if (moveSquare(x, y, team, localGrid) != -1) {
								bool check = checkMove(team, j, x, y, p_type, p_x, p_y, s_x, s_y, p_team, localGrid);
								if (!check) {
									LegalMovesX.push_back(x);
									LegalMovesY.push_back(y);
									LegalMovesType.push_back(p_type[j]);
									LegalMovesPrevX.push_back(p_x[j]);
									LegalMovesPrevY.push_back(p_y[j]);
								}
							}
						}
					}

				}

			}

			if (p_type[j] == "K") {
				std::vector<int> Cx;
				std::vector<int> Cy;
				for (unsigned ux = 0; ux <= 4; ux++) {
					for (unsigned uy = 0; uy <= 2; uy++) {
						Cx.push_back(p_x[j] + (ux - 2));
						Cy.push_back(p_y[j] + (uy - 1));
					}
				}

				for (unsigned u = 0; u < Cx.size(); u++) {
					x = Cx[u];
					y = Cy[u];

					if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
						if (legalMoveFunc(p_x[j], p_y[j], p_type[j], p_team[j], s_x[j], s_y[j], x, y, p_type, p_x, p_x, s_x, s_x, p_team, localGrid)) {
							if (moveSquare(x, y, team, localGrid) != -1) {
								bool check = checkMove(team, j, x, y, p_type, p_x, p_y, s_x, s_y, p_team, localGrid);
								if (!check) {
									LegalMovesX.push_back(x);
									LegalMovesY.push_back(y);
									LegalMovesType.push_back(p_type[j]);
									LegalMovesPrevX.push_back(p_x[j]);
									LegalMovesPrevY.push_back(p_y[j]);
								}
							}
						}
					}

				}

			}

		}
	}

	if (team == 1) {
		this->blackLegalMovesX = LegalMovesX;
		this->blackLegalMovesY = LegalMovesY;
		this->blackLegalMovesType = LegalMovesType;
		this->blackLegalMovesPrevX = LegalMovesPrevX;
		this->blackLegalMovesPrevY = LegalMovesPrevY;
	}

	if (team == -1) {
		this->whiteLegalMovesX = LegalMovesX;
		this->whiteLegalMovesY = LegalMovesY;
		this->whiteLegalMovesType = LegalMovesType;
		this->whiteLegalMovesPrevX = LegalMovesPrevX;
		this->whiteLegalMovesPrevY = LegalMovesPrevY;
	}

}

bool pieces::checkMove(int team, int i, int x, int y, std::vector<std::string> p_type, std::vector<int> p_x, std::vector<int> p_y, std::vector<int> s_x, std::vector<int> s_y, std::vector<int> p_team, std::vector<std::vector<std::string>> localGrid) {

	p_x[i] = x;
	p_y[i] = y;

	std::string t = p_type[i];

	for (unsigned o = 0; o < p_team.size(); o++) {
		if (p_x[o] == x && p_y[o] == y && p_team[o] != team) {
			p_x.erase(p_x.begin() + o);
			p_y.erase(p_y.begin() + o);
			p_team.erase(p_team.begin() + o);
			p_type.erase(p_type.begin() + o);
			s_x.erase(s_x.begin() + o);
			s_y.erase(s_y.begin() + o);
		}
	}

	localGrid.clear();

	for (unsigned x = 0; x <= 7; x++) {
		std::vector<std::string> a;
		localGrid.push_back(a);
		for (unsigned y = 0; y <= 7; y++) {
			localGrid[x].push_back("  ");
		}
	}

	for (unsigned i = 0; i < p_team.size(); i++) {
		std::string b;
		if (p_team[i] == 1) {
			b = "+";
		}
		if (p_team[i] == -1) {
			b = "-";
		}
		localGrid[p_x[i]][p_y[i]] = b + p_type[i];
	}

	// Check for check
	bool check = inCheck(team, p_type, p_x, p_y, s_x, s_y, p_team, localGrid);

	return check;
}

double pieces::calcScore(std::vector<std::string> p_type, std::vector<int> p_x, std::vector<int> p_y, std::vector<int> s_x, std::vector<int> s_y, std::vector<int> p_team, int team) {
	double whiteScore = 0;
	double blackScore = 0;

	std::vector<int> W_LegalMovesX;
	std::vector<std::string> W_LegalMovesType;
	std::vector<int> W_LegalMovesY;
	std::vector<int> W_LegalMovesPrevX;
	std::vector<int> W_LegalMovesPrevY;

	std::vector<int> B_LegalMovesX;
	std::vector<std::string> B_LegalMovesType;
	std::vector<int> B_LegalMovesY;
	std::vector<int> B_LegalMovesPrevX;
	std::vector<int> B_LegalMovesPrevY;

	legalMoveList(team, p_type, p_x, p_y, s_x, s_y, p_team);

	B_LegalMovesX = this->blackLegalMovesX;
	B_LegalMovesType = this->blackLegalMovesType;
	B_LegalMovesY = this->blackLegalMovesY;
	B_LegalMovesPrevX = this->blackLegalMovesPrevX;
	B_LegalMovesPrevY = this->blackLegalMovesPrevY;

	W_LegalMovesX = this->whiteLegalMovesX;
	W_LegalMovesType = this->whiteLegalMovesType;
	W_LegalMovesY = this->whiteLegalMovesY;
	W_LegalMovesPrevX = this->whiteLegalMovesPrevX;
	W_LegalMovesPrevY = this->whiteLegalMovesPrevY;

	for (unsigned i = 0; i < p_team.size(); i++) {
		double s = 0;
		if (p_type[i] == "P") {
			s = 1;
		}
		if (p_type[i] == "N") {
			s = 3;
			if (p_y[i] == 0 || p_y[i] == 7) {
				s -= 0.5;
			}
			if (p_x[i] == 0 || p_x[i] == 7) {
				s -= 0.75;
			}
		}
		if (p_type[i] == "B") {
			s = 3;
			if (p_y[i] == 0 || p_y[i] == 7) {
				s -= 0.35;
			}
		}
		if (p_type[i] == "R") {
			s = 5;
			if (p_y[i] == 0 || p_y[i] == 7) {
				s -= 0.1;
			}
		}
		if (p_type[i] == "Q") {
			s = 9;
			if (this->move <= 5) {
				if (s_y[i] != p_y[i]) {
					s -= 3;
				}
			}
		}
		if (p_type[i] == "K") {
			if (s_y[i] != p_y[i]) {
				s = -1;
			}
			if (s_x[i] != p_x[i]) {
				if (p_x[i] == 2)
					s += 0.25;
				else if (p_x[i] == 6)
					s += 0.7;
				else
					s -= 0.5;
			}
		}
		if (p_x[i] == s_x[i] && p_y[i] == s_y[i]) {
			s = s * .85;
		}
		if (p_team[i] == 1)
		s *= legalCounter(p_x[i], p_y[i], p_team[i], p_x, p_y, s_x, s_y, p_team, p_type, B_LegalMovesX, B_LegalMovesY, B_LegalMovesType, B_LegalMovesPrevX, B_LegalMovesPrevY);
		if (p_team[i] == -1)
			s *= legalCounter(p_x[i], p_y[i], p_team[i], p_x, p_y, s_x, s_y, p_team, p_type, W_LegalMovesX, W_LegalMovesY, W_LegalMovesType, W_LegalMovesPrevX, W_LegalMovesPrevY);
		if (p_team[i] == -1) {
			whiteScore += s;
		}
		if (p_team[i] == 1) {
			blackScore += s;
		}
	}

	return whiteScore - blackScore;
}

double pieces::get_score() {

	return this->score;
}

bool pieces::get_engine() {
	bool a;
	if (this->toMove == -1)
		a = this->engineWhite;
	if (this->toMove == 1)
		a = this->engineBlack;
	if (this->showCont)
		a = true;

	return a;
}

double pieces::minimax(int depth, int maxdepth, int team, std::vector<std::string> p_type, std::vector<int> p_x, std::vector<int> p_y, std::vector<int> s_x, std::vector<int> s_y, std::vector<int> p_team, double alpha, double beta) {
	if (depth == maxdepth) {
		this->transPosFen.clear();
		this->transPosScore.clear();

		if (this->move <= 9) {
			this->displayDepth = "-1";

			book(posFen(this->grid, this->toMove));

			if (this->displayDepth == "Book")
				return 0;
		}

	}
	bool max;
	bool min;
	double score;

	std::vector<int> LegalMovesX;
	std::vector<std::string> LegalMovesType;
	std::vector<int> LegalMovesY;
	std::vector<int> LegalMovesPrevX;
	std::vector<int> LegalMovesPrevY;
	legalMoveList(team, p_type, p_x, p_y, s_x, s_y, p_team);
	if (team == 1) {
		max = false;
		min = true;
		score = 99;

		LegalMovesX = this->blackLegalMovesX;
		LegalMovesType = this->blackLegalMovesType;
		LegalMovesY = this->blackLegalMovesY;
		LegalMovesPrevX = this->blackLegalMovesPrevX;
		LegalMovesPrevY = this->blackLegalMovesPrevY;

	}

	if (team == -1) {
		max = true;
		min = false;
		score = -99;

		LegalMovesX = this->whiteLegalMovesX;
		LegalMovesType = this->whiteLegalMovesType;
		LegalMovesY = this->whiteLegalMovesY;
		LegalMovesPrevX = this->whiteLegalMovesPrevX;
		LegalMovesPrevY = this->whiteLegalMovesPrevY;

	}

	std::vector<std::vector<std::string>> localGrid;

	for (unsigned x = 0; x <= 7; x++) {
		std::vector<std::string> a;
		localGrid.push_back(a);
		for (unsigned y = 0; y <= 7; y++) {
			localGrid[x].push_back("  ");
		}
	}

	for (unsigned i = 0; i < p_team.size(); i++) {
		std::string b;
		if (p_team[i] == 1) {
			b = "+";
		}
		if (p_team[i] == -1) {
			b = "-";
		}
		localGrid[p_x[i]][p_y[i]] = b + p_type[i];
	}

	//Check for mate and stalemate
	if (LegalMovesX.size() == 0) {
		bool a = inCheck(team, p_type, p_x, p_y, s_x, s_y, p_team, localGrid);

		if (!a) {
			score = 0;
		}
		else {
			if (min)
				score += (depth - maxdepth);
			if (max)
				score -= (depth - maxdepth);
			std::cout << score << std::endl;
			std::cout << depth << "/" << maxdepth << std::endl;
		}
		return score;
	}

	int restoreX;
	int restoreY;
	int restoreTeam;
	std::string restoreType;
	int restoreSX;
	int restoreSY;

	std::vector<std::string> localP_type;
	std::vector<int> localP_x;
	std::vector<int> localP_y;
	std::vector<int> localS_x;
	std::vector<int> localS_y;
	std::vector<int> localP_team;

	int c;
	bool a = false;

	std::vector<double> scores;
	std::vector<int> moves;

	//move ordering
	std::vector<int> ordering;
	if (this->breakswitch || depth != maxdepth || maxdepth == 1) {
		for (unsigned i = 0; i < LegalMovesX.size(); i++) {
			int score = 0;
			int capture = 0;
			int piece;

			localP_type = p_type;
			localP_x = p_x;
			localP_y = p_y;
			localS_x = s_x;
			localS_y = s_y;
			localP_team = p_team;

			for (unsigned u = 0; u < localP_x.size(); u++) {
				if (localP_x[u] == LegalMovesPrevX[i] && localP_y[u] == LegalMovesPrevY[i]) {
					piece = u;
					break;
				}

			}
			for (unsigned u = 0; u < localP_x.size(); u++) {
				if (localP_x[u] == LegalMovesX[i] && localP_y[u] == LegalMovesY[i]) {
					if (localP_type[u] == "P") {
						capture = 1;
					}
					if (localP_type[u] == "N") {
						capture = 3;
					}
					if (localP_type[u] == "B") {
						capture = 3;
					}
					if (localP_type[u] == "R") {
						capture = 5;
					}
					if (localP_type[u] == "Q") {
						capture = 9;
					}
					break;
				}

			}
			localP_x[piece] = LegalMovesX[i];
			localP_y[piece] = LegalMovesY[i];

			if (LegalMovesType[i] == "P" && LegalMovesX[i] == 4)
				score += 1;
			if (LegalMovesType[i] == "P" && LegalMovesX[i] == 3)
				score += 1;
			if (LegalMovesType[i] == "P" && std::abs(LegalMovesY[i] - LegalMovesPrevY[i]) == 1 && LegalMovesPrevY[i] == 1)
				score -= 1;
			if (LegalMovesType[i] == "P" && std::abs(LegalMovesY[i] - LegalMovesPrevY[i]) == 1 && LegalMovesPrevY[i] == 7)
				score -= 1;
			if (LegalMovesType[i] == "P" && LegalMovesX[i] < 3)
				score -= 1;
			if (LegalMovesType[i] == "P" && LegalMovesX[i] > 4)
				score -= 1;

			score += capture;

			ordering.push_back(score);
		}
	}

	if (!this->breakswitch && depth == maxdepth && maxdepth != 1) {
		int sc = 1000;
		for (unsigned i = 0; i < LegalMovesX.size(); i++) {
			ordering.push_back(0);
		}
		for (unsigned i = 0; i < this->contOrder.size(); i++) {
			ordering[this->contOrder[i]] = sc;
			sc -= 1;
		}
	}
	for (unsigned u = 0; u < ordering.size(); u++) {
		for (unsigned e = 0; e < ordering.size() - 1; e++) {
			if (ordering[e] > ordering[e + 1]) {
				double s1 = ordering[e];
				ordering[e] = ordering[e + 1];
				ordering[e + 1] = s1;

				int x1 = LegalMovesX[e];
				LegalMovesX[e] = LegalMovesX[e + 1];
				LegalMovesX[e + 1] = x1;

				int y1 = LegalMovesY[e];
				LegalMovesY[e] = LegalMovesY[e + 1];
				LegalMovesY[e + 1] = y1;

				int px1 = LegalMovesPrevX[e];
				LegalMovesPrevX[e] = LegalMovesPrevX[e + 1];
				LegalMovesPrevX[e + 1] = px1;

				int py1 = LegalMovesPrevY[e];
				LegalMovesPrevY[e] = LegalMovesPrevY[e + 1];
				LegalMovesPrevY[e + 1] = py1;

				std::string t1 = LegalMovesType[e];
				LegalMovesType[e] = LegalMovesType[e + 1];
				LegalMovesType[e + 1] = t1;
			}
		}
	}
	
	std::reverse(LegalMovesX.begin(), LegalMovesX.end());
	std::reverse(LegalMovesY.begin(), LegalMovesY.end());
	std::reverse(LegalMovesPrevX.begin(), LegalMovesPrevX.end());
	std::reverse(LegalMovesPrevY.begin(), LegalMovesPrevY.end());
	std::reverse(LegalMovesType.begin(), LegalMovesType.end());

	for (unsigned i = 0; i < LegalMovesX.size(); i++) {

		//Set up the local enviroment
		localP_type = p_type;
		localP_x = p_x;
		localP_y = p_y;
		localS_x = s_x;
		localS_y = s_y;
		localP_team = p_team;

		//Find the piece
		int piece;
		int capture = -1;
		for (unsigned u = 0; u < localP_x.size(); u++) {
			if (localP_x[u] == LegalMovesPrevX[i] && localP_y[u] == LegalMovesPrevY[i]) {
				piece = u;
				break;
			}
			
		}

		for (unsigned u = 0; u < localP_x.size(); u++) {
			if (localP_x[u] == LegalMovesX[i] && localP_y[u] == LegalMovesY[i]) {
				capture = u;
				break;
			}

		}


		//make a move
		localP_x[piece] = LegalMovesX[i];
		localP_y[piece] = LegalMovesY[i];

		if (localP_type[piece] == "K") {
			if (std::abs(LegalMovesX[i] - LegalMovesPrevX[i]) == 2) {
				int rX = -1;
				if (LegalMovesX[i] == 2) {
					for (unsigned u = 0; u < localP_x.size(); u++) {
						if (localP_x[u] == 0 && localP_y[u] == LegalMovesY[i]) {
							rX = u;
							break;
						}
					}
					localP_x[rX] = 3;

				}
				if (LegalMovesX[i] == 6) {
					int rX = -1;
					for (unsigned u = 0; u < localP_x.size(); u++) {
						if (localP_x[u] == 7 && localP_y[u] == LegalMovesY[i]) {
							rX = u;
							break;
						}
					}
					localP_x[rX] = 5;
				}
			}
		}

		if (localP_type[piece] == "P") {
			if (localP_y[piece] == 0 || localP_y[piece] == 7) {
				localP_type[piece] = "Q";
			}
		}


		if (capture != -1) {
			localP_type.erase(localP_type.begin() + capture);
			localP_x.erase(localP_x.begin() + capture);
			localP_y.erase(localP_y.begin() + capture);
			localS_x.erase(localS_x.begin() + capture);
			localS_y.erase(localS_y.begin() + capture);
			localP_team.erase(localP_team.begin() + capture);
		}

		localGrid.clear();

		for (unsigned x = 0; x <= 7; x++) {
			std::vector<std::string> a;
			localGrid.push_back(a);
			for (unsigned y = 0; y <= 7; y++) {
				localGrid[x].push_back("  ");
			}
		}

		for (unsigned i = 0; i < localP_team.size(); i++) {
			std::string b;
			if (localP_team[i] == 1) {
				b = "+";
			}
			if (localP_team[i] == -1) {
				b = "-";
			}
			localGrid[localP_x[i]][localP_y[i]] = b + localP_type[i];
		}

		//0 depth behavior
		double s;
		if (depth == 0) {
			s = calcScore(localP_type, localP_x, localP_y, localS_x, localS_y, localP_team, team);
			scores.push_back(s);
			moves.push_back(i);
		}
		//depth > 0 behavior
		if (depth > 0) {

			std::string localFen = posFen(localGrid, team);
			bool q1 = false;
			if (maxdepth - depth > 3 && depth >= 1) {
				for (unsigned q = 0; q < this->transPosFen.size(); q++) {
					if (this->transPosFen[q] == localFen) {
						s = this->transPosScore[q];
						q1 = true;
						std::cout << "I just saved a lot of time!" << std::endl;
					}
				}
			}
			if (!q1) {
				s = minimax(depth - 1, maxdepth, team * -1, localP_type, localP_x, localP_y, localS_x, localS_y, localP_team, alpha, beta);
				this->transPosFen.push_back(localFen);
				this->transPosScore.push_back(s);
			}
			scores.push_back(s);
			moves.push_back(i);
		}
		if (max) {
			if (s > alpha)
				alpha = s;
		}
		if (min) {
			if (s < beta)
				beta = s;
		}
		if (beta <= alpha) {
			break;
		}

	}

	for (unsigned u = 0; u < scores.size(); u++) {
		for (unsigned e = 0; e < scores.size() - 1; e++) {
			if (scores[e] > scores[e + 1]) {
				double s1 = scores[e];
				scores[e] = scores[e + 1];
				scores[e + 1] = s1;

				int m1 = moves[e];
				moves[e] = moves[e + 1];
				moves[e + 1] = m1;
			}
		}
	}

	if (max) {
		std::reverse(scores.begin(), scores.end());
		std::reverse(moves.begin(), moves.end());
	}
	if (!this->breakswitch) {
		this->contOrder = moves;
	}
	score = scores[0];
	if (depth == maxdepth) {
		bestMoveX = LegalMovesX[moves[0]];
		bestMoveY = LegalMovesY[moves[0]];
		bestMoveType = LegalMovesType[moves[0]];
		bestMovePrevX = LegalMovesPrevX[moves[0]];
		bestMovePrevY = LegalMovesPrevY[moves[0]];
	}

	return score;
}

std::vector<int> pieces::getBestMove() {
	std::vector<int> a;
	a.push_back(this->bestMoveX);
	a.push_back(this->bestMoveY);
	a.push_back(this->bestMovePrevX);
	a.push_back(this->bestMovePrevY);
	if (this->bestMoveType == "P")
		a.push_back(0);
	if (this->bestMoveType == "N")
		a.push_back(1);
	if (this->bestMoveType == "B")
		a.push_back(2);
	if (this->bestMoveType == "R")
		a.push_back(3);
	if (this->bestMoveType == "Q")
		a.push_back(4);
	if (this->bestMoveType == "K")
		a.push_back(5);

	return a;
}
bool pieces::teamCheck(int team) {

	return inCheck(team, this->piece_type, this->piece_x, this->piece_y, this->start_x, this->start_y, this->piece_team, this->grid);
}

double pieces::legalCounter(int x, int y, int team, std::vector<int> p_x, std::vector<int> p_y, std::vector<int> s_x, std::vector<int> s_y, std::vector<int> p_team, std::vector<std::string> p_type, std::vector<int> LegalMovesX, std::vector<int> LegalMovesY, std::vector<std::string> LegalMovesType, std::vector<int> LegalMovesPrevX, std::vector<int> LegalMovesPrevY) {
	int c = 0;

	for (unsigned i = 0; i < LegalMovesX.size(); i++) {
		if (LegalMovesPrevX[i] == x && LegalMovesPrevY[i] == y) {
			c++;
		}
	}
	return 1 + (0.002 * c);
}

void pieces::contanalysis() {
	if (!this->breakswitch) {
		this->score = minimax(this->contDepth - 1, this->contDepth - 1, this->toMove, this->piece_type, this->piece_x, this->piece_y, this->start_x, this->start_y, this->piece_team, -99, 99);

		if (std::abs(this->score) == 99) {
			this->breakswitch = true;
		}

		this->contDepth++;
	}
}

std::string pieces::posFen(std::vector<std::vector<std::string>> localGrid, int team) {
	std::string fen;
	int z = 0;
	for (unsigned y = 0; y <= 7; y++) {
		for (unsigned x = 0; x <= 7; x++) {
			std::string q;
			if (localGrid[x][y] == "  ") {
				z++;
			}
			if (localGrid[x][y] == "+P") {
				if (z != 0)
					q = std::to_string(z) + "p";
				else
					q = "p";
				z = 0;
			}
			if (localGrid[x][y] == "+N") {
				if (z != 0)
					q = std::to_string(z) + "n";
				else
					q = "n";
				z = 0;
			}
			if (localGrid[x][y] == "+B") {
				if (z != 0)
					q = std::to_string(z) + "b";
				else
					q = "b";
				z = 0;
			}
			if (localGrid[x][y] == "+R") {
				if (z != 0)
					q = std::to_string(z) + "r";
				else
					q = "r";
				z = 0;
			}
			if (localGrid[x][y] == "+Q") {
				if (z != 0)
					q = std::to_string(z) + "q";
				else
					q = "q";
				z = 0;
			}
			if (localGrid[x][y] == "+K") {
				if (z != 0)
					q = std::to_string(z) + "k";
				else
					q = "k";
				z = 0;
			}

			if (localGrid[x][y] == "-P") {
				if (z != 0)
					q = std::to_string(z) + "P";
				else
					q = "P";
				z = 0;
			}
			if (localGrid[x][y] == "-N") {
				if (z != 0)
					q = std::to_string(z) + "N";
				else
					q = "N";
				z = 0;
			}
			if (localGrid[x][y] == "-B") {
				if (z != 0)
					q = std::to_string(z) + "B";
				else
					q = "B";
				z = 0;
			}
			if (localGrid[x][y] == "-R") {
				if (z != 0)
					q = std::to_string(z) + "R";
				else
					q = "R";
				z = 0;
			}
			if (localGrid[x][y] == "-Q") {
				if (z != 0)
					q = std::to_string(z) + "Q";
				else
					q = "Q";
				z = 0;
			}
			if (localGrid[x][y] == "-K") {
				if (z != 0)
					q = std::to_string(z) + "K";
				else
					q = "K";
				z = 0;
			}

			fen = fen + q;
		}
		if (z != 0)
			fen += std::to_string(z);
		z = 0;
		fen += "/";
	}
	if (team == -1)
		fen += " w";
	if (team == 1)
		fen += " b";

	return fen;
}
void pieces::book(std::string fen) {
	//WHITES BOOK
	if (this->toMove == -1) {
		if (fen == "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR/ w") {
			int x = std::rand() % 100;

			if (x <= 50) { //e4
				bestMoveX = 4;
				bestMoveY = 4;
				bestMoveType = "P";
				bestMovePrevX = 4;
				bestMovePrevY = 6;

				this->displayDepth = "Book";
				return;
			}
			if (x > 50) { //d4
				bestMoveX = 3;
				bestMoveY = 4;
				bestMoveType = "P";
				bestMovePrevX = 3;
				bestMovePrevY = 6;

				this->displayDepth = "Book";
				return;
			}
		}
		if (fen == "rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR/ w") { //e4 e5 nf3
			bestMoveX = 5;
			bestMoveY = 5;
			bestMoveType = "N";
			bestMovePrevX = 6;
			bestMovePrevY = 7;

			this->displayDepth = "Book";
			return;
		}

		if (fen == "r1bqkbnr/pppp1ppp/2n5/4p3/4P3/5N2/PPPP1PPP/RNBQKB1R/ w") {
			int x = std::rand() % 100;

			if (x <= 50) { //Italian
				bestMoveX = 2;
				bestMoveY = 4;
				bestMoveType = "B";
				bestMovePrevX = 5;
				bestMovePrevY = 7;

				this->displayDepth = "Book";
				return;
			}
			if (x > 50) { //Ruy lopez
				bestMoveX = 1;
				bestMoveY = 3;
				bestMoveType = "B";
				bestMovePrevX = 5;
				bestMovePrevY = 7;

				this->displayDepth = "Book";
				return;
			}
		}
		if (fen == "r1bqkbnr/1ppp1ppp/p1n5/1B2p3/4P3/5N2/PPPP1PPP/RNBQK2R/ w") { //Ruy Lopez a3
			int x = std::rand() % 100;

			if (x <= 50) { //Exchange variation
				bestMoveX = 2;
				bestMoveY = 2;
				bestMoveType = "B";
				bestMovePrevX = 1;
				bestMovePrevY = 3;

				this->displayDepth = "Book";
				return;
			}
			if (x > 50) { //Ba4
				bestMoveX = 0;
				bestMoveY = 4;
				bestMoveType = "B";
				bestMovePrevX = 1;
				bestMovePrevY = 3;

				this->displayDepth = "Book";
				return;
			}
		}
		if (fen == "r1bqkbnr/1pp2ppp/p1p5/4p3/4P3/5N2/PPPP1PPP/RNBQK2R/ w") { //Ruy lopez exchange 0-0
			bestMoveX = 4;
			bestMoveY = 7;
			bestMoveType = "K";
			bestMovePrevX = 6;
			bestMovePrevY = 7;

			this->displayDepth = "Book";
			return;
		}
		if (fen == "rnbqkbnr/pppp1ppp/4p3/8/4P3/8/PPPP1PPP/RNBQKBNR/ w") { //French d4
			bestMoveX = 3;
			bestMoveY = 4;
			bestMoveType = "P";
			bestMovePrevX = 3;
			bestMovePrevY = 6;

			this->displayDepth = "Book";
			return;
		}
		if (fen == "rnbqkbnr/ppp2ppp/4p3/3p4/3PP3/8/PPP2PPP/RNBQKBNR/ w") { //French Defense d4 d5
			int x = std::rand() % 100;

			if (x <= 50) { //Advance Variation
				bestMoveX = 4;
				bestMoveY = 3;
				bestMoveType = "P";
				bestMovePrevX = 4;
				bestMovePrevY = 4;

				this->displayDepth = "Book";
				return;
			}
			if (x > 50) { //Nc3
				bestMoveX = 2;
				bestMoveY = 5;
				bestMoveType = "N";
				bestMovePrevX = 1;
				bestMovePrevY = 7;

				this->displayDepth = "Book";
				return;
			}
		}
		if (fen == "rnbqkbnr/pp3ppp/4p3/2ppP3/3P4/8/PPP2PPP/RNBQKBNR/ w") {//French advance c5 c3
			bestMoveX = 2;
			bestMoveY = 5;
			bestMoveType = "P";
			bestMovePrevX = 2;
			bestMovePrevY = 6;

			this->displayDepth = "Book";
			return;
		}
		if (fen == "r1bqkbnr/pp3ppp/2n1p3/2ppP3/3P4/2P5/PP3PPP/RNBQKBNR/ w") {//French advance paulsen attack
			bestMoveX = 5;
			bestMoveY = 5;
			bestMoveType = "N";
			bestMovePrevX = 6;
			bestMovePrevY = 7;

			this->displayDepth = "Book";
			return;
		}
		if (fen == "r1b1kbnr/pp3ppp/1qn1p3/2ppP3/3P4/2P2N2/PP3PPP/RNBQKB1R/ w") {//French advance paulsen attack Qb6 Be2
			bestMoveX = 4;
			bestMoveY = 6;
			bestMoveType = "B";
			bestMovePrevX = 5;
			bestMovePrevY = 7;

			this->displayDepth = "Book";
			return;
		}
		if (fen == "rnbqkbnr/ppp1pppp/8/3p4/3P4/8/PPP1PPPP/RNBQKBNR/ w") { //d4 d5
			int x = std::rand() % 100;

			if (x < 33) { //Nf3
				bestMoveX = 5;
				bestMoveY = 5;
				bestMoveType = "N";
				bestMovePrevX = 6;
				bestMovePrevY = 7;

				this->displayDepth = "Book";
				return;
			}
			if (x >= 33 && x < 67) { //Queens Gambit
				bestMoveX = 2;
				bestMoveY = 4;
				bestMoveType = "P";
				bestMovePrevX = 2;
				bestMovePrevY = 6;

				this->displayDepth = "Book";
				return;
			}
			if (x > 67) { //LONDON
				bestMoveX = 5;
				bestMoveY = 4;
				bestMoveType = "B";
				bestMovePrevX = 2;
				bestMovePrevY = 7;

				this->displayDepth = "Book";
				return;
			}
		}
		if (fen == "rnbqkbnr/ppp2ppp/4p3/3p4/2PP4/8/PP2PPPP/RNBQKBNR/ w") { //Queens Gambit Declined Nc3
			bestMoveX = 2;
			bestMoveY = 5;
			bestMoveType = "N";
			bestMovePrevX = 1;
			bestMovePrevY = 7;

			this->displayDepth = "Book";
			return;
		}
		if (fen == "rnbqkb1r/ppp2ppp/4pn2/3p4/2PP4/2N5/PP2PPPP/R1BQKBNR/ w") {//Queens Gambit Declined Nc3 Nf6 Nf3
			bestMoveX = 5;
			bestMoveY = 5;
			bestMoveType = "N";
			bestMovePrevX = 6;
			bestMovePrevY = 7;

			this->displayDepth = "Book";
			return;
		}
		if (fen == "rn1qkbnr/ppp1pppp/8/3p1b2/3P1B2/8/PPP1PPPP/RN1QKBNR/ w" || fen == "rnbqkb1r/ppp1pppp/5n2/3p4/3P1B2/8/PPP1PPPP/RN1QKBNR/ w") { //LONDON e3
			bestMoveX = 4;
			bestMoveY = 5;
			bestMoveType = "P";
			bestMovePrevX = 4;
			bestMovePrevY = 6;

			this->displayDepth = "Book";
			return;
		}
		if (fen == "rn1qkb1r/ppp1pppp/5n2/3p1b2/3P1B2/4P3/PPP2PPP/RN1QKBNR/ w") {//LONDON e3
			int x = std::rand() % 100;
			if (x <= 50) { //c4
				bestMoveX = 2;
				bestMoveY = 4;
				bestMoveType = "P";
				bestMovePrevX = 2;
				bestMovePrevY = 6;

				this->displayDepth = "Book";
				return;
			}
			if (x > 50) { //Nf3
				bestMoveX = 5;
				bestMoveY = 5;
				bestMoveType = "N";
				bestMovePrevX = 6;
				bestMovePrevY = 7;

				this->displayDepth = "Book";
				return;
			}
		}
		if (fen == "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR/ w") { //Sicilian Defense
			int x = std::rand() % 100;
			if (x < 33) { //c3
				bestMoveX = 2;
				bestMoveY = 5;
				bestMoveType = "P";
				bestMovePrevX = 2;
				bestMovePrevY = 6;

				this->displayDepth = "Book";
				return;
			}
			if (x > 33 && x <= 67) { //Nf3
				bestMoveX = 5;
				bestMoveY = 5;
				bestMoveType = "N";
				bestMovePrevX = 6;
				bestMovePrevY = 7;

				this->displayDepth = "Book";
				return;
			}
			if (x > 67) { //Nc3
				bestMoveX = 2;
				bestMoveY = 5;
				bestMoveType = "N";
				bestMovePrevX = 1;
				bestMovePrevY = 7;

				this->displayDepth = "Book";
				return;
			}
		}
		if (fen == "rnbqkbnr/pp1p1ppp/4p3/2p5/4P3/2N5/PPPP1PPP/R1BQKBNR/ w" || fen == "r1bqkbnr/pp1ppppp/2n5/2p5/4P3/2N5/PPPP1PPP/R1BQKBNR/ w") {//Sicilian Defense Nc3 (e6 or Nc6) Nf3
			bestMoveX = 5;
			bestMoveY = 5;
			bestMoveType = "N";
			bestMovePrevX = 6;
			bestMovePrevY = 7;

			this->displayDepth = "Book";
			return;
		}
		if (fen == "r1bqkbnr/pp1ppppp/2n5/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R/ w" || fen == "rnbqkbnr/pp1p1ppp/4p3/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R/ w") {//Sicilian Defense Nf3 (e6 or Nc6) Nc3
			bestMoveX = 2;
			bestMoveY = 5;
			bestMoveType = "N";
			bestMovePrevX = 1;
			bestMovePrevY = 7;

			this->displayDepth = "Book";
			return;
		}
		if (fen == "r1bqkbnr/pp1p1ppp/2n1p3/2p5/4P3/2N2N2/PPPP1PPP/R1BQKB1R/ w") {//Sicilian Defense Nf3 and Nc3 e6 and Nc6 Bb5
			bestMoveX = 1;
			bestMoveY = 3;
			bestMoveType = "B";
			bestMovePrevX = 5;
			bestMovePrevY = 7;

			this->displayDepth = "Book";
			return;
		}
		if (fen == "rnbqkbnr/pp1p1ppp/4p3/2p5/4P3/2P5/PP1P1PPP/RNBQKBNR/ w" || fen == "r1bqkbnr/pp1ppppp/2n5/2p5/4P3/2P5/PP1P1PPP/RNBQKBNR/ w") { //Sicilian Defense c3 (Nc6 or e3)
			int x = std::rand() % 100;
			if (x <= 50) { //d4
				bestMoveX = 3;
				bestMoveY = 4;
				bestMoveType = "P";
				bestMovePrevX = 3;
				bestMovePrevY = 6;

				this->displayDepth = "Book";
				return;
			}
			if (x > 50) { // Nf3
				bestMoveX = 5;
				bestMoveY = 5;
				bestMoveType = "N";
				bestMovePrevX = 6;
				bestMovePrevY = 7;

				this->displayDepth = "Book";
				return;
			}
		}
		if (fen == "rnbqkbnr/pp2pppp/8/2pp4/4P3/2P5/PP1P1PPP/RNBQKBNR/ w") { //Sicilian Defense c3 d5 exd5
			bestMoveX = 3;
			bestMoveY = 3;
			bestMoveType = "P";
			bestMovePrevX = 4;
			bestMovePrevY = 4;

			this->displayDepth = "Book";
			return;
		}
		if (fen == "rnb1kbnr/pp2pppp/8/2pq4/8/2P5/PP1P1PPP/RNBQKBNR/ w") {//Sicilian Defense c3 d5 exd5 Qxd5
			int x = std::rand() % 100;
			if (x <= 50) { //d4
				bestMoveX = 3;
				bestMoveY = 4;
				bestMoveType = "P";
				bestMovePrevX = 3;
				bestMovePrevY = 6;

				this->displayDepth = "Book";
				return;
			}
			if (x > 50) { // Nf3
				bestMoveX = 5;
				bestMoveY = 5;
				bestMoveType = "N";
				bestMovePrevX = 6;
				bestMovePrevY = 7;

				this->displayDepth = "Book";
				return;
			}
		}
		if (fen == "r1bqkbnr/pp1ppppp/2n5/8/3pP3/2P5/PP3PPP/RNBQKBNR/ w") {//Sicilian Defense c3 Nc6 d4 cxd4 cxd4
			bestMoveX = 3;
			bestMoveY = 4;
			bestMoveType = "P";
			bestMovePrevX = 2;
			bestMovePrevY = 5;

			this->displayDepth = "Book";
			return;
		}
		if (fen == "rnbqkb1r/pppppppp/5n2/8/3P4/8/PPP1PPPP/RNBQKBNR/ w") {//Indian Game c4
			bestMoveX = 2;
			bestMoveY = 4;
			bestMoveType = "P";
			bestMovePrevX = 2;
			bestMovePrevY = 6;

			this->displayDepth = "Book";
			return;
		}
		if (fen == "rnbqkb1r/pppppp1p/5np1/8/2PP4/8/PP2PPPP/RNBQKBNR/ w" || fen == "rnbqkb1r/pppp1ppp/4pn2/8/2PP4/8/PP2PPPP/RNBQKBNR/ w") {//kings indian or east indian
			int x = std::rand() % 100;
			if (x <= 50) { // Nf3
				bestMoveX = 5;
				bestMoveY = 5;
				bestMoveType = "N";
				bestMovePrevX = 6;
				bestMovePrevY = 7;

				this->displayDepth = "Book";
				return;
			}
			if (x > 50) {
				bestMoveX = 2;
				bestMoveY = 5;
				bestMoveType = "N";
				bestMovePrevX = 1;
				bestMovePrevY = 7;

				this->displayDepth = "Book";
				return;
			}
		}
	}

	//BLACKS BOOK
	if (this->toMove == 1) {
		if (fen == "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR/ b") { //e4
			int x = std::rand() % 100;
			if (x <= 50) { //e5
				bestMoveX = 4;
				bestMoveY = 3;
				bestMoveType = "P";
				bestMovePrevX = 4;
				bestMovePrevY = 1;

				this->displayDepth = "Book";
				return;
			}
			if (x > 50) { //c5
				bestMoveX = 2;
				bestMoveY = 3;
				bestMoveType = "P";
				bestMovePrevX = 2;
				bestMovePrevY = 1;

				this->displayDepth = "Book";
				return;
			}
		}

		if (fen == "r1bqkbnr/pppp1ppp/2n5/1B2p3/4P3/5N2/PPPP1PPP/RNBQK2R/ b") { //Ruy lopez a3
			bestMoveX = 0;
			bestMoveY = 2;
			bestMoveType = "P";
			bestMovePrevX = 0;
			bestMovePrevY = 1;

			this->displayDepth = "Book";
			return;
		}
		if (fen == "rnbqkbnr/pppp1ppp/8/4p3/4P3/5N2/PPPP1PPP/RNBQKB1R/ b") { //e4 e5 nf3 nc3
			bestMoveX = 2;
			bestMoveY = 2;
			bestMoveType = "N";
			bestMovePrevX = 1;
			bestMovePrevY = 0;

			this->displayDepth = "Book";
			return;
		}
		if (fen == "r1bqkbnr/1ppp1ppp/p1B5/4p3/4P3/5N2/PPPP1PPP/RNBQK2R/ b") { //Ruy Exchange dxc6
			bestMoveX = 2;
			bestMoveY = 2;
			bestMoveType = "P";
			bestMovePrevX = 3;
			bestMovePrevY = 1;

			this->displayDepth = "Book";
			return;
		}
		if (fen == "rnbqkbnr/pppppppp/8/8/3P4/8/PPP1PPPP/RNBQKBNR/ b") { //d4 d5
			bestMoveX = 3;
			bestMoveY = 3;
			bestMoveType = "P";
			bestMovePrevX = 3;
			bestMovePrevY = 1;

			this->displayDepth = "Book";
			return;
		}
		if (fen == "rnbqkbnr/ppp1pppp/8/3p4/2PP4/8/PP2PPPP/RNBQKBNR/ b") { //Queens Gambit
			bestMoveX = 4;
			bestMoveY = 2;
			bestMoveType = "P";
			bestMovePrevX = 4;
			bestMovePrevY = 1;

			this->displayDepth = "Book";
			return;
		}
		if (fen == "rnbqkbnr/ppp2ppp/4p3/3p4/2PP4/2N5/PP2PPPP/R1BQKBNR/ b") { //Queens Gambit Declined Nc3 Nf6
			bestMoveX = 5;
			bestMoveY = 2;
			bestMoveType = "N";
			bestMovePrevX = 6;
			bestMovePrevY = 0;

			this->displayDepth = "Book";
			return;
		}
		if (fen == "rnbqkbnr/ppp1pppp/8/3p4/3P1B2/8/PPP1PPPP/RN1QKBNR/ b") { //LONDON
			int x = std::rand() % 100;

			if (x <= 50) { //Nf6
				bestMoveX = 5;
				bestMoveY = 2;
				bestMoveType = "N";
				bestMovePrevX = 6;
				bestMovePrevY = 0;

				this->displayDepth = "Book";
				return;
			}
			if (x > 50) { //Bf5
				bestMoveX = 5;
				bestMoveY = 3;
				bestMoveType = "B";
				bestMovePrevX = 2;
				bestMovePrevY = 0;

				this->displayDepth = "Book";
				return;
			}
		}
		if (fen == "rn1qkbnr/ppp1pppp/8/3p1b2/3P1B2/4P3/PPP2PPP/RN1QKBNR/ b") { //London Bf5 e3
			bestMoveX = 5;
			bestMoveY = 2;
			bestMoveType = "N";
			bestMovePrevX = 6;
			bestMovePrevY = 0;

			this->displayDepth = "Book";
			return;
		}
		if (fen == "rnbqkb1r/ppp1pppp/5n2/3p4/3P1B2/4P3/PPP2PPP/RN1QKBNR/ b") { //London Nf6 e3
			bestMoveX = 5;
			bestMoveY = 3;
			bestMoveType = "B";
			bestMovePrevX = 2;
			bestMovePrevY = 0;

			this->displayDepth = "Book";
			return;
		}
		if (fen == "rn1qkb1r/ppp1pppp/5n2/3p1b2/3P1B2/4PN2/PPP2PPP/RN1QKB1R/ b" || fen == "rn1qkb1r/ppp1pppp/5n2/3p1b2/2PP1B2/4P3/PP3PPP/RN1QKBNR/ b") { //LONDON e6
			bestMoveX = 4;
			bestMoveY = 2;
			bestMoveType = "P";
			bestMovePrevX = 4;
			bestMovePrevY = 1;

			this->displayDepth = "Book";
			return;
		}
		if (fen == "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R/ b" || fen == "rnbqkbnr/pp1ppppp/8/2p5/4P3/2N5/PPPP1PPP/R1BQKBNR/ b") { //Sicilian Nf3 or Nc3
			int x = std::rand() % 100;
			if (x <= 50) { //Nc6
				bestMoveX = 2;
				bestMoveY = 2;
				bestMoveType = "N";
				bestMovePrevX = 1;
				bestMovePrevY = 0;

				this->displayDepth = "Book";
				return;
			}
			if (x > 50) { //e6
				bestMoveX = 4;
				bestMoveY = 2;
				bestMoveType = "P";
				bestMovePrevX = 4;
				bestMovePrevY = 1;

				this->displayDepth = "Book";
				return;
			}
		}
		if (fen == "rnbqkbnr/pp1p1ppp/4p3/2p5/4P3/2N2N2/PPPP1PPP/R1BQKB1R/ b") {//Sicilian Nf3 and Nc3 e6 Nc6
			bestMoveX = 2;
			bestMoveY = 2;
			bestMoveType = "N";
			bestMovePrevX = 1;
			bestMovePrevY = 0;

			this->displayDepth = "Book";
			return;
		}
		if (fen == "r1bqkbnr/pp1ppppp/2n5/2p5/4P3/2N2N2/PPPP1PPP/R1BQKB1R/ b") {//Sicilian Nf3 and Nc3 Nc6 e6
			bestMoveX = 4;
			bestMoveY = 2;
			bestMoveType = "P";
			bestMovePrevX = 4;
			bestMovePrevY = 1;

			this->displayDepth = "Book";
			return;
		}
		if (fen == "rnbqkbnr/pp1ppppp/8/2p5/4P3/2P5/PP1P1PPP/RNBQKBNR/ b") { //Sicilian c3
			int x = std::rand() % 100;
			if (x <= 50) { //d5
				bestMoveX = 3;
				bestMoveY = 3;
				bestMoveType = "P";
				bestMovePrevX = 3;
				bestMovePrevY = 1;

				this->displayDepth = "Book";
				return;
			}
			if (x > 50) { //e6
				bestMoveX = 4;
				bestMoveY = 2;
				bestMoveType = "P";
				bestMovePrevX = 4;
				bestMovePrevY = 1;

				this->displayDepth = "Book";
				return;
			}
		}
		if (fen == "rnbqkbnr/pp2pppp/8/2pP4/8/2P5/PP1P1PPP/RNBQKBNR/ b") { //Sicilian c3 d5 exd5 Qxd5
			bestMoveX = 3;
			bestMoveY = 3;
			bestMoveType = "Q";
			bestMovePrevX = 3;
			bestMovePrevY = 0;

			this->displayDepth = "Book";
			return;
		}
		if (fen == "r1bqkbnr/pp1ppppp/2n5/2p5/3PP3/2P5/PP3PPP/RNBQKBNR/ b") {//Sicilian c3 Nc6 d4 cxd4
			bestMoveX = 3;
			bestMoveY = 4;
			bestMoveType = "P";
			bestMovePrevX = 2;
			bestMovePrevY = 3;

			this->displayDepth = "Book";
			return;
		}
		if (fen == "rnbqkbnr/ppp1pppp/8/3p4/3P4/5N2/PPP1PPPP/RNBQKB1R/ b") {//Queen pawn with Nf3
			bestMoveX = 5;
			bestMoveY = 2;
			bestMoveType = "N";
			bestMovePrevX = 6;
			bestMovePrevY = 0;

			this->displayDepth = "Book";
			return;
		}
	}
	return;
}