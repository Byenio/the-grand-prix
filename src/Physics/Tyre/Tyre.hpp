#pragma once

class Tyre
{
  int width;
  float grip;

public:
  Tyre(int width, float grip);
  ~Tyre();

  int getWidth();
  float getGrip();
};