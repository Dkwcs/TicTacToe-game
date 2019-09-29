#include "Player.h"
#include <string>


const char Player::getPlayerSymbol() const
{
	return m_playableSymbol;
}

const std::string& Player::getPlayerName() const
{
	return m_playerName;
}

const PlayerType Player::getPlayerType() const
{
	return m_playerType;
}


Player::Player(PlayerType playerType, std::string playernName, char playableSymbol)
	: m_playerType{ playerType }, m_playerName{ std::move(playernName) }, m_playableSymbol{ playableSymbol }
{
}


Player::~Player() = default;

