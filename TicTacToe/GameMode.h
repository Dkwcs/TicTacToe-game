#include <assert.h>

#pragma once
enum class GameMode {
	AI = 1,
	Human = 2
};

inline std::string gameModeToString(GameMode mode) {

	switch (mode)
	{
	case GameMode::AI:
		return "AI";
	case GameMode::Human:
		return "Human";
	default:
		assert("Unknown game mode!");
		return "";
	}
}