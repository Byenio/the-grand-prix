#include "TrackList.hpp"

TrackList::TrackList(const std::string &fileName)
{
  std::ifstream file(fileName);

  if (!file.is_open())
  {
    throw std::runtime_error("Failed to open file: " + fileName);
  }

  std::string line;

  while (getline(file, line))
  {
    std::vector<std::string> row = vectorizeLine(line);
    auto track = std::make_shared<Track>(std::stoi(row[0]), row[1]);
    this->tracks.push_back(track);
  }

  file.close();
};

TrackList::~TrackList(){};

std::shared_ptr<Track> TrackList::getTrack(const int id) const
{
  auto it = std::find_if(tracks.begin(), tracks.end(),
                         [id](const std::shared_ptr<Track> &ptr) { return ptr->getId() == id; });

  if (it != tracks.end())
  {
    return *it;
  }

  return nullptr;
};

int TrackList::size() const
{
  return this->tracks.size();
}