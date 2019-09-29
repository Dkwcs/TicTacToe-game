#include <iostream>
#include "TicTacToeGame.h"
#include "GameMode.h"
#include "Player.h"
#include "GameBoard.h"
#include <time.h>
#include <cctype>
#include "Utility.h"
#include <string>
#include "Resources.h"

TicTacToeGame::TicTacToeGame()
	: m_gameBoard{ std::make_unique<GameBoard>() }
{
}

void TicTacToeGame::start()
{
		while (true)
		{
			setGameSettings();
			system("cls");
			m_gameBoard->clearGameBoard();
			m_gameBoard->refreshGameBoard();

			bool isWin = runNewSession();
			printGameResult(isWin);
			char userAnswer;
			std::cout << "Do you want to play again? y/n" << std::endl;
			std::cin >> userAnswer;
			if (userAnswer != 'y')
			{
				break;
			}
		}
}


void TicTacToeGame::setGameSettings()
{
	setGameModeSettings();
	setPlayersSettings();
	defineFirstStep();
}

void TicTacToeGame::makeStep()
{
	if (m_gameMode == GameMode::AI && m_currentPlayer->getPlayerType() == PlayerType::AI)
	{
		std::srand(time(0));
		calculateAIStep();
	}
	else
	{
		std::string inputFieldIndex;
		bool isCellCorrect = false;
		std::cout << "Turn is player " << m_currentPlayer->getPlayerName() << std::endl;
		do {

			std::cout << "Choose number of field to fill " << std::endl;

			std::cin >> inputFieldIndex;
			int fieldIndex = isNumber(inputFieldIndex) ? std::stoi(inputFieldIndex) : -1;
			if (fieldIndex >= Resources::LowerBoardRange && fieldIndex <= Resources::UpperBoardRange)
			{

				if (!m_gameBoard->trySetBoardValue(fieldIndex - 1, m_currentPlayer->getPlayerSymbol()))
				{
					isCellCorrect = false;
					std::cout << "This cell is busy. Select another cell " << std::endl;
				}
				else
				{
					isCellCorrect = true;
				}
			}
			else
			{
				std::cout << "Incorrect number of field. Try again " << std::endl;
			}
		} while (!isCellCorrect);
	}

}

void TicTacToeGame::calculateAIStep()
{
	
	bool isCellCorrect = false;
	do {
		int cellIndex = (std::rand() % Resources::UpperBoardRange) + Resources::LowerBoardRange;
		isCellCorrect = m_gameBoard->trySetBoardValue(cellIndex - 1, m_currentPlayer->getPlayerSymbol());
	} while (!isCellCorrect);

}

void TicTacToeGame::changeCurrentPlayer()
{
	m_currentPlayer =  m_currentPlayer == m_firstPlayer ? m_secondPlayer : m_firstPlayer;
}

void TicTacToeGame::setGameModeSettings()
{
	std::string inputGameModeIndex;
	int gameModeIndex;
	bool isGameModeCorrect = false;
	do
	{
		std::cout << "Choose game mode - AI or Human? Set 1 or 2" << std::endl;
		std::cin >> inputGameModeIndex;
		gameModeIndex = isNumber(inputGameModeIndex) ? std::stoi(inputGameModeIndex) : -1;
		isGameModeCorrect = gameModeIndex == 1 || gameModeIndex == 2;
		if (!isGameModeCorrect)
		{
			std::cout << "Inccorect game mode" << std::endl;
		}

	} while (!isGameModeCorrect);

	m_gameMode = static_cast<GameMode>(gameModeIndex);
}

void TicTacToeGame::setPlayersSettings()
{
	std::string playerName;
	std::cout << "Set your name. Player - " << Resources::First_Player_Id << std::endl;
	std::cin >> playerName;
	char playableSymbol = getPlayableSymbol();
	m_firstPlayer = std::make_shared<Player>(PlayerType::Human, playerName, playableSymbol);
	playableSymbol = playableSymbol == Resources::Symbol_X ? Resources::Symbol_0 : Resources::Symbol_X;
	if (m_gameMode == GameMode::Human)
	{
		bool isPlayerNameCorrect = true;
		do {
			std::cout << "Set your name. Player - " << Resources::Second_Player_Id << std::endl;
			std::cin >> playerName;
			if (playerName == m_firstPlayer->getPlayerName()) {
				isPlayerNameCorrect = false;
				std::cout << "That name match with first player. Please input another name " << 2 << std::endl;
			}
			else {
				isPlayerNameCorrect = true;
			}
		} while (!isPlayerNameCorrect);

		m_secondPlayer = std::make_shared<Player>(PlayerType::Human, playerName, playableSymbol);
	}
	else {
		m_secondPlayer = std::make_shared<Player>(PlayerType::AI, Resources::AI_NAME, playableSymbol);
	}
}

char TicTacToeGame::getPlayableSymbol()
{
	std::string inputPlayableSymbol;
	char playableSymbol;
	bool isCorrectPlayableSymbol = false;
	do
	{
		std::cout << "Set playable symbol for first player? Set X or 0" << std::endl;
		std::cin >> inputPlayableSymbol;
		playableSymbol = toupper(inputPlayableSymbol[0]);
		isCorrectPlayableSymbol = inputPlayableSymbol.length() == 1 && (playableSymbol == Resources::Symbol_X || playableSymbol == Resources::Symbol_0);
		if (!isCorrectPlayableSymbol)
		{
			std::cout << "This symbol is not correct" << std::endl;
		}
	} while (!isCorrectPlayableSymbol);

	return playableSymbol;

}

void TicTacToeGame::defineFirstStep()
{
	std::string inputCurrentPlayerId;
	int currentPlayerId;
	std::cout << "Whose step is first? Set 1 or 2" << std::endl;
	std::cin >> inputCurrentPlayerId;
	currentPlayerId = isNumber(inputCurrentPlayerId) ? std::stoi(inputCurrentPlayerId) : Resources::Second_Player_Id;
	m_currentPlayer = currentPlayerId == Resources::First_Player_Id ? m_firstPlayer : m_secondPlayer;
}

void TicTacToeGame::printGameResult(bool isWin) const
{
	if (isWin && m_currentPlayer)
	{
		std::cout << "Player - " << m_currentPlayer->getPlayerName() << " won!" << std::endl;
	}
	else
	{
		std::cout << "It's draw! " << std::endl;
	}
}

void TicTacToeGame::printSettings() const
{
	std::cout << "Your mode is " << gameModeToString(m_gameMode) << std::endl;
	std::cout << "Player Type - " << playerTypeToString(m_firstPlayer->getPlayerType()) << " Name - " << m_firstPlayer->getPlayerName() << " Symbol - " << m_firstPlayer->getPlayerSymbol() << std::endl;
	std::cout << "Player Type - " << playerTypeToString(m_secondPlayer->getPlayerType()) << " Name - " << m_secondPlayer->getPlayerName() << " Symbol - " << m_secondPlayer->getPlayerSymbol() << std::endl;
}

bool TicTacToeGame::runNewSession()
{
	bool isWin = false;
	bool isGameEnd = false;
	do
	{
		printSettings();
		makeStep();
		isWin = m_gameBoard->checkForWin(m_currentPlayer->getPlayerSymbol());
		isGameEnd = isWin || m_gameBoard->checkForDraw();
		if (!isGameEnd) 
		{
			changeCurrentPlayer();
		}
	} while (!isGameEnd);
	return isWin;
}


TicTacToeGame::~TicTacToeGame() = default;
