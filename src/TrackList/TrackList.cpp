#include "TrackList.hpp"

TrackList::TrackList(std::string &fileName)
{
  std::string line;
  std::ifstream file(fileName);

  while (getline(file, line))
  {
    std::vector<std::string> row = vectorizeLine(line);
    auto track = std::make_shared<Track>(std::stoi(row[0]), row[1]);
    this->trackList.push_back(track);
  }

  file.close();
};

TrackList::~TrackList(){};

std::shared_ptr<Track> TrackList::getTrack(int id)
{
  return this->trackList.at(id);
};

int TrackList::size()
{
  return this->trackList.size();
}