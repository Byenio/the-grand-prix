#pragma once

#include <algorithm>
#include <fstream>
#include <memory>

#include "../utils/functions.hpp"
#include "Track/Track.hpp"

class TrackList
{
  std::vector<std::shared_ptr<Track>> tracks;

public:
  TrackList(const std::string &fileName);
  ~TrackList();

  std::shared_ptr<Track> getTrack(const int id) const;

  int size() const;
};