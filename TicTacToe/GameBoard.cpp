#include "GameBoard.h"
#include <iostream>
#include <array>
#include <algorithm>

GameBoard::GameBoard()
{
	clearGameBoard();
}


void GameBoard::refreshGameBoard()
{
	//char* gameBoardTemplate = new char["\n\n" 
	//	+ "\t\t\t %c | %c | %c  \n" 
	//	+ "\t\t\t------------\n" 
	//	+ "\t\t\t %c | %c | %c  \n"
	//	+ "\t\t\t------------\n"
	//	+ "\t\t\t %c | %c | %c  \n"];


	printf("\t\t\t %c | %c | %c  \n", m_boardCells[0],
		m_boardCells[1], m_boardCells[2]);
	printf("\t\t\t------------\n");
	printf("\t\t\t %c | %c | %c  \n", m_boardCells[3],
		m_boardCells[4], m_boardCells[5]);
	printf("\t\t\t------------\n");
	printf("\t\t\t %c | %c | %c  \n\n", m_boardCells[6],
		m_boardCells[7], m_boardCells[8]);
}

bool GameBoard::trySetBoardValue(int cell, char symbol)
{
	if (m_boardCells[cell] == ' ') {
		system("cls");
		m_boardCells[cell] = symbol;
		refreshGameBoard();
		return true;
	}
	return false;
}

void GameBoard::clearGameBoard()
{
	std::fill(m_boardCells.begin(), m_boardCells.end(), ' ');
}


bool GameBoard::checkForWin(char symbol) const
{
	bool isWin = (m_boardCells[0] == symbol && m_boardCells[1] == symbol && m_boardCells[2] == symbol) ||
		(m_boardCells[3] == symbol && m_boardCells[4] == symbol && m_boardCells[5] == symbol) ||
		(m_boardCells[6] == symbol && m_boardCells[7] == symbol && m_boardCells[8] == symbol) ||
		(m_boardCells[0] == symbol && m_boardCells[3] == symbol && m_boardCells[6] == symbol) ||
		(m_boardCells[1] == symbol && m_boardCells[4] == symbol && m_boardCells[7] == symbol) ||
		(m_boardCells[2] == symbol && m_boardCells[5] == symbol && m_boardCells[8] == symbol) ||
		(m_boardCells[0] == symbol && m_boardCells[4] == symbol && m_boardCells[8] == symbol) ||
		(m_boardCells[2] == symbol && m_boardCells[4] == symbol && m_boardCells[6] == symbol);
	return isWin;
}

bool GameBoard::checkForDraw() const
{
	return !std::any_of(m_boardCells.begin(), m_boardCells.end(), [](char cell) {return cell == ' '; });
}


GameBoard::~GameBoard() = default;
