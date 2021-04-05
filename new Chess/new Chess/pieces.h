#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include <windows.h>
#include <iostream>
#include <sstream>
#include <cmath>
#include <math.h>
#include <tuple>
#include <cstdlib>

class pieces
{
public:

	//Info vars
	int toMove = -1;
	int move = 0;

	std::vector<std::string> piece_type;
	std::vector<int> piece_x;
	std::vector<int> piece_y;
	std::vector<int> start_x;
	std::vector<int> start_y;
	std::vector<int> piece_team;
	std::vector<double> piece_id;
	int selected;

	std::vector<int> whiteLegalMovesX;
	std::vector<int> whiteLegalMovesY;
	std::vector<std::string> whiteLegalMovesType;
	std::vector<int> whiteLegalMovesPrevX;
	std::vector<int> whiteLegalMovesPrevY;
	double whiteScore;

	int lastMoveX;
	int lastMoveY;
	std::string lastMoveType;
	int lastMovePrevX;
	int lastMovePrevY;

	std::vector<int> bestMovesX;
	std::vector<int> bestMovesY;
	std::vector <std::string> bestMoveTypes;
	std::vector<int> bestMoveSPrevX;
	std::vector<int> bestMoveSPrevY;
	std::vector<double>bestScores;
	int lines;

	int bestMoveX;
	int bestMoveY;
	std::string bestMoveType;
	int bestMovePrevX;
	int bestMovePrevY;

	std::vector<int> blackLegalMovesX;
	std::vector<int> blackLegalMovesY;
	std::vector<std::string> blackLegalMovesType;
	std::vector<int> blackLegalMovesPrevX;
	std::vector<int> blackLegalMovesPrevY;
	double blackScore;

	double score;

	std::vector<std::vector<std::string>> grid;

	//Piece functions
	void setup();
	void select(int x, int y);
	void release(int x, int y);
	std::string posFen(std::vector<std::vector<std::string>> localGrid, int team);

	//get funcs
	int get_selected();
	bool get_engine();
	bool get_aiWhite();
	bool get_aiBlack();
	std::string get_depth();
	std::vector<std::string> get_type();
	std::vector<int> get_x();
	std::vector<int> get_y();
	std::vector<int> get_team();
	std::vector<std::vector<int>> getBestMove();
	double get_score();
	std::vector<double> get_scores();

	//Legal move functions
	bool legalMoveFunc(int x, int y, std::string type, int team, int startX, int startY, int moveX, int moveY, std::vector<std::string> p_type, std::vector<int> p_x, std::vector<int> p_y, std::vector<int> s_x, std::vector<int> s_y, std::vector<int> p_team, std::vector<std::vector<std::string>> localGrid);
	int moveSquare(int x, int y, int team, std::vector<std::vector<std::string>> localGrid);
	bool inCheck(int team, std::vector<std::string> p_type, std::vector<int> p_x, std::vector<int> p_y, std::vector<int> s_x, std::vector<int> s_y, std::vector<int> p_team, std::vector<std::vector<std::string>> localGrid);
	bool teamCheck(int team);
	void legalMoveList(int team, std::vector<std::string> p_type, std::vector<int> p_x, std::vector<int> p_y, std::vector<int> s_x, std::vector<int> s_y, std::vector<int> p_team);
	bool checkMove(int team, int i, int x, int y, std::vector<std::string> p_type, std::vector<int> p_x, std::vector<int> p_y, std::vector<int> s_x, std::vector<int> s_y, std::vector<int> p_team, std::vector<std::vector<std::string>> localGrid);
	bool isPassant(int x, int y, std::string type, int team, int startX, int startY, int moveX, int moveY);

	//Score calcluation
	double calcScore(std::vector<std::string> p_type, std::vector<int> p_x, std::vector<int> p_y, std::vector<int> s_x, std::vector<int> s_y, std::vector<int> p_team, int team);
	double minimax(int depth, int maxdepth, int team, std::vector<std::string> p_type, std::vector<int> p_x, std::vector<int> p_y, std::vector<int> s_x, std::vector<int> s_y, std::vector<int> p_team, double alpha, double beta);
	double legalCounter(int x, int y, int team, std::vector<int> p_x, std::vector<int> p_y, std::vector<int> s_x, std::vector<int> s_y, std::vector<int> p_team, std::vector<std::string> p_type, std::vector<int> LegalMovesX, std::vector<int> LegalMovesY, std::vector<std::string> LegalMovesType, std::vector<int> LegalMovesPrevX, std::vector<int> LegalMovesPrevY);
	void contanalysis();
	void book(std::string fen);

	std::vector<std::vector<double>> pawnEvalWhite;
	std::vector<std::vector<double>> pawnEvalBlack;

	std::vector<std::vector<double>> knightEval;

	std::vector<std::vector<double>> bishopEvalWhite;
	std::vector<std::vector<double>> bishopEvalBlack;
	
	std::vector<std::vector<double>> rookEvalWhite;
	std::vector<std::vector<double>> rookEvalBlack;

	std::vector<std::vector<double>> evalQueen;

	std::vector<std::vector<double>> kingEvalWhite;
	std::vector<std::vector<double>> kingEvalBlack;

	std::vector<std::vector<double>> KingMate;

	int searchDepth;
	std::string displayDepth;
	bool engineWhite;
	bool engineBlack;
	bool aiWhite;
	bool aiBlack;

	bool breakswitch;
	bool showCont;
	int contDepth;
	std::vector<int> contOrder;

	std::vector<std::string> transPosFen;
	std::vector<double> transPosScore;
	std::vector<int> transPosDepth;
};