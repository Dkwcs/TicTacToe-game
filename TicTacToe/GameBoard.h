#include <array>

#pragma once
class GameBoard
{
public:
	GameBoard();
	~GameBoard();
	void refreshGameBoard();
	bool trySetBoardValue(int cell, char symbol);
	void clearGameBoard();
	bool checkForWin(char symbol) const;
	bool checkForDraw() const;
private: 
	static const int BOARDSIZE = 9;
	std::array<char, GameBoard::BOARDSIZE> m_boardCells;
};

