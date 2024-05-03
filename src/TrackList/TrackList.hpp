#pragma once

#include "../utils/functions.hpp"
#include "Track/Track.hpp"
#include <algorithm>
#include <fstream>
#include <memory>

class TrackList
{
  std::vector<std::shared_ptr<Track>> trackList;

public:
  TrackList(std::string &fileName);
  ~TrackList();

  std::shared_ptr<Track> getTrack(int id);

  int size();
};