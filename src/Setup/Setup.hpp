#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Setup{
private:
    sf::Text tracks[11];
    sf::Text cars[10];
    sf::Font font;

    int selectedTrack;
    int selectedCar;

public:
    Setup(float width, float height);
    void draw(sf::RenderWindow& window);
    ~Setup();

    int getSelectedTrack(){
        return selectedTrack;
    }
    int getSelectedCar(){
        return selectedCar;
    }

    void moveUpTrack();
    void moveDownTrack();

    void moveUpCar();
    void moveDownCar();
};

