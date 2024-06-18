#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include "../utils/functions.hpp"


class Leaderboards{
private:
    int trackSelected;

    std::vector<std::vector<std::string>> timesJapan;
    std::vector<std::vector<std::string>> timesCanada;
    std::vector<std::vector<std::string>> timesSpain;
    std::vector<std::vector<std::string>> timesGB;
    std::vector<std::vector<std::string>> timesHungary;
    std::vector<std::vector<std::string>> timesBelgium;
    std::vector<std::vector<std::string>> timesItaly;
    std::vector<std::vector<std::string>> timesBrazil;
    std::vector<sf::Text> tracks;

    sf::Font font;
public:
    Leaderboards();
    ~Leaderboards();

    void setTracks();
    void setTimes(int trackId, std::vector<std::vector<std::string>> &times);
    void sortTimes(std::vector<std::vector<std::string>> &times);
    void drawTracks(sf::RenderWindow* window);
    int drawTimes(sf::RenderWindow* window);

    void moveRight();
    void moveLeft();

    int trackPressed(){
        return trackSelected;
    }
};