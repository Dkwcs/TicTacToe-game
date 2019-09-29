
enum class GameMode;
class GameBoard;
class Player;

class TicTacToeGame
{
public:
	TicTacToeGame();
	~TicTacToeGame();
	void start();
private:
	void setGameSettings();
	void makeStep();
	void calculateAIStep();
	void changeCurrentPlayer();
	void setGameModeSettings();
	void setPlayersSettings();
	char getPlayableSymbol();
	void defineFirstStep();
	void printGameResult(bool isWin) const;
	void printSettings() const;
	bool runNewSession();

	std::unique_ptr<GameBoard> m_gameBoard;
	std::shared_ptr<Player> m_firstPlayer;
	std::shared_ptr<Player> m_secondPlayer;
	std::shared_ptr<Player> m_currentPlayer;
	GameMode m_gameMode;
};

