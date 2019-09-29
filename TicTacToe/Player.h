#pragma once
#include <string>
#include <assert.h>

enum class PlayerType {
	AI,
	Human
};

inline std::string playerTypeToString(PlayerType type) {

	switch (type)
	{
	case PlayerType::AI:
		return "AI";
	case PlayerType::Human:
		return "Human";
	default:
		assert("Unknown player type!");
		return "";
	}
}

class Player
{
private:
	PlayerType m_playerType;
	std::string m_playerName;
	char m_playableSymbol;
public:
	const char getPlayerSymbol() const;
	const std::string& getPlayerName() const;
	const PlayerType getPlayerType() const;
	Player(PlayerType playerType, std::string playerName, char playableSymbol);
	~Player();
};

