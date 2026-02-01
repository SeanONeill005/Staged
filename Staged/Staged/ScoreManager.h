#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

struct ScoreEntry {
    std::string name;
    int westernScore;
    int circusScore;
    int totalScore;
};

class ScoreManager {
public:
    static ScoreManager& getInstance() {
        static ScoreManager instance;
        return instance;
    }

    void saveScore(const std::string& name, int westernScore, int circusScore) {
        std::ofstream file("scores.csv", std::ios::app);
        if (file.is_open()) {
            int total = westernScore + circusScore;
            file << name << "," << westernScore << "," << circusScore << "," << total << "\n";
            file.close();
        }
    }

    std::vector<ScoreEntry> loadScores() {
        std::vector<ScoreEntry> scores;
        std::ifstream file("scores.csv");

        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                std::stringstream ss(line);
                std::string name;
                std::string western, circus, total;

                if (std::getline(ss, name, ',') &&
                    std::getline(ss, western, ',') &&
                    std::getline(ss, circus, ',') &&
                    std::getline(ss, total, ',')) {

                    ScoreEntry entry;
                    entry.name = name;
                    entry.westernScore = std::stoi(western);
                    entry.circusScore = std::stoi(circus);
                    entry.totalScore = std::stoi(total);
                    scores.push_back(entry);
                }
            }
            file.close();
        }
        return scores;
    }

    int getBestWesternScore() {
        auto scores = loadScores();
        if (scores.empty()) return 0;

        auto maxIt = std::max_element(scores.begin(), scores.end(),
            [](const ScoreEntry& a, const ScoreEntry& b) {
                return a.westernScore < b.westernScore;
            });
        return maxIt->westernScore;
    }

    int getBestCircusScore() {
        auto scores = loadScores();
        if (scores.empty()) return 0;

        auto maxIt = std::max_element(scores.begin(), scores.end(),
            [](const ScoreEntry& a, const ScoreEntry& b) {
                return a.circusScore < b.circusScore;
            });
        return maxIt->circusScore;
    }

    int getBestTotalScore() {
        auto scores = loadScores();
        if (scores.empty()) return 0;

        auto maxIt = std::max_element(scores.begin(), scores.end(),
            [](const ScoreEntry& a, const ScoreEntry& b) {
                return a.totalScore < b.totalScore;
            });
        return maxIt->totalScore;
    }

private:
    ScoreManager() = default;
};
