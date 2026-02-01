#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>

#define WINDOW_HEIGHT 1080
#define WINDOW_WIDTH 1920

#define RESOLUTION sf::Vector2f{ 1920.f, 1080.f }

namespace GameScores {
    inline int westernScore = 0;
    inline int circusScore = 0;
    inline int totalScore = 0;
    inline bool westernCompleted = false;
    inline bool circusCompleted = false;
    inline std::string playerName = "AAA";

    inline void resetScores() {
        westernScore = 0;
        circusScore = 0;
        totalScore = 0;
        westernCompleted = false;
        circusCompleted = false;
        playerName = "AAA";
    }

    inline void updateTotal() {
        totalScore = westernScore + circusScore;
    }

    inline bool bothGamesCompleted() {
        return westernCompleted && circusCompleted;
    }
}

#endif