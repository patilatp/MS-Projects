#ifndef PlAYER__H
#define PlAYER__H

#include <string>
#include "sprite.h"
#include "gamedata.h"
#include "frameFactory.h"
#include "multiLasers.h"
#include "collisionStrategy.h"

class Player : public Drawable {
public:
  Player(const std::string& name);
  Player(const Player&);
  MultiLasers* getLasers() {
    return &lasers;
  }
  bool collidWith(const Drawable* d) const {
    return lasers.collidWith(d);
  } 
  bool playerCollidWith(const Drawable* d) const {
    return strategy->execute(*this, *d);
  }
  virtual ~Player();
  virtual void draw() const;
  virtual void update(Uint32 ticks);
  
  virtual const Frame* getFrame() const { 
    return frame; 
  }
  virtual void shoot(bool down);
  void stop();
  void right();
  void left();
  void up();
  void down();
  unsigned int getLaserListSize() const { return lasers.laserCount(); }
  unsigned int getFreeListSize() const { return lasers.freeCount(); }
  
private:
  Player& operator=(const Player&);
protected:
  const Frame * frame;
  int playerWidth;
  int playerHeight;
  int worldWidth;
  int worldHeight;
  const int speedX;
  const int speedY;
  bool keyPressedX;
  bool keyPressedY;
  std::string laserName;
  MultiLasers lasers;
  float laserInterval;
  float timeSinceLastLaser;
  float minLaserSpeed;
  CollisionStrategy * strategy;
};
#endif

