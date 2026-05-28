#ifndef GAME_HPP
#define GAME_HPP

#include <string>

class Game {
private: 
    std::string title;
    std::string description;
    int popularity;

public:
    Game();
    Game(std::string title, std::string shortDescription, int popularity);
    ~Game();

    std::string getTitle();
    std::string getShortDescription();
    int getPopularity();
};

#endif