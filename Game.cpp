#include <iostream>
using namespace std;

#include "Game.hpp"

Game::Game() {
}

Game::Game(std::string title, std::string shortDescription, int popularity) {
    this->title = title;
    this->description = shortDescription;  // FIX: was incorrectly assigning `description` to itself
    this->popularity = popularity;
}

Game::~Game() {

}

std::string Game::getTitle() {
    return title;
}

std::string Game::getShortDescription() {
    return description;
}

int Game::getPopularity() {
    return popularity;
}
