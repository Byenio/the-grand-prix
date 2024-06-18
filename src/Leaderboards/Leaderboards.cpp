#include "Leaderboards.hpp"

Leaderboards::Leaderboards(){
    font.loadFromFile("assets/fonts/JetBrainsMono.ttf");

    setTracks();
    
    setTimes(0,timesJapan);
    sortTimes(timesJapan);

    setTimes(1,timesCanada);
    sortTimes(timesCanada);
    
    setTimes(2,timesSpain);
    sortTimes(timesSpain);
    
    setTimes(3,timesGB);
    sortTimes(timesGB);
    
    setTimes(4,timesHungary);
    sortTimes(timesHungary);
    
    setTimes(5,timesBelgium);
    sortTimes(timesBelgium);
    
    setTimes(6,timesItaly);
    sortTimes(timesItaly);
    
    setTimes(7,timesBrazil);
    sortTimes(timesBrazil);

    trackSelected = 0;
}

void Leaderboards::setTracks(){
    std::fstream file;
    file.open("config/tracklist");
    if(file.is_open()){
        std::string line;
        int width = 50;

        while (std::getline(file, line))
        {
            std::stringstream ss(line);
            std::string field;

            std::getline(ss, field, ',');
            std::getline(ss, field, ',');

            sf::Text trackText;
            trackText.setFont(font);
            trackText.setString(field);
            trackText.setFillColor(sf::Color::White);
            trackText.setCharacterSize(20);
            trackText.setPosition(width,50);

            tracks.push_back(trackText);

            width+=200;
        }
    }
    file.close();
}

void Leaderboards::setTimes(int trackId, std::vector<std::vector<std::string>> &times){
    std::fstream file;
    std::string fileName = "logs/sessions/" + std::to_string(trackId);
    file.open(fileName);
    if(file.is_open()){
        std::cout<<fileName<<std::endl;
        std::string line;
        while(getline(file, line)){
            times.push_back(fileLineToVector(line,6));
        }
    }
    file.close();
}

void Leaderboards::sortTimes(std::vector<std::vector<std::string>> &times){
        std::sort(times.begin(), times.end(), [](const std::vector<std::string>& a, const std::vector<std::string>& b) {
            return stoi(a[2]) < stoi(b[2]);
        });
}

void Leaderboards::drawTracks(sf::RenderWindow* window){
    for(int i=0; i<static_cast<int>(tracks.size());i++){
        window->draw(tracks[i]);
    }
}

int Leaderboards::drawTimes(sf::RenderWindow* window){
    std::vector<std::vector<std::string>> temp;
    std::cout<<trackSelected<<std::endl;
    switch(trackSelected){
        case 0:
            temp = timesJapan;
            break;
        case 1:
            temp = timesCanada;
            break;
        case 2:
            temp = timesSpain;
            break;
        case 3:
            temp = timesGB;
            break;
        case 4:
            temp = timesHungary;
            break;
        case 5:
            temp = timesBelgium;
            break;
        case 6:
            temp = timesItaly;
            break;
        case 7:
            temp = timesBrazil;
            break;
    }
    if(static_cast<int>(temp.size()) == 0){
        sf::Text text;
        text.setString("Brak czasow");
        text.setCharacterSize(20);
        text.setFont(font);
        text.setFillColor(sf::Color::White);
        text.setPosition(400,300);
        window->draw(text);
        return 0;
    }
    int height = 300;
    for(int i = 0; i < static_cast<int>(temp.size()) && i <10; i++){
        int width = 400;
        for(int j = 2; j < static_cast<int>(temp[i].size()); j++){
            sf::Text text;
            text.setString(formatTime(stoi(temp[i][j])));
            text.setCharacterSize(20);
            text.setFont(font);
            text.setFillColor(sf::Color::White);
            text.setPosition(width,height);
            window->draw(text);
            width+=200;
        }
        height+=40;
    }
    return 0;
}

void Leaderboards::moveRight(){
    if (trackSelected <= static_cast<int>(tracks.size()))
    {
        tracks[trackSelected].setFillColor(sf::Color::White);
        trackSelected++;
        if (trackSelected == static_cast<int>(tracks.size()))
        {
          trackSelected = 0;
        }
        tracks[trackSelected].setFillColor(sf::Color::Blue);
    }
}

void Leaderboards::moveLeft(){
    if (trackSelected >= 0)
    {
        tracks[trackSelected].setFillColor(sf::Color::White);

        trackSelected--;
        if (trackSelected == -1)
        {
        trackSelected = tracks.size()-1;
        }
        tracks[trackSelected].setFillColor(sf::Color::Blue);
    }
}




Leaderboards::~Leaderboards(){}
