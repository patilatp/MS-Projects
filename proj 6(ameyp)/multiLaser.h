#ifndef MULTILASER__H
#define MULTILASER__H

#include "sprite.h"


class MultiLaser : public Sprite{
public:
  MultiLaser(const std::string&, const Vector2f&, const Vector2f&);
  MultiLaser(const MultiLaser&);
  MultiLaser& operator=(const MultiLaser&);
  virtual void update(Uint32 ticks);
  bool goneTooFar() const { return tooFar; }
  void reset();

protected:
  float distance;
  float maxDistance;
  bool tooFar;
};

#endif
