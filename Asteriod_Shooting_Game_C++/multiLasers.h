#ifndef MULTILASERS_H
#define MULTILASERS_H

#include <list>
#include "multiLaser.h"
#include <vector>
#include "collisionStrategy.h"

class MultiLasers {
public:
  MultiLasers(const std::string&);
  MultiLasers(const MultiLasers&);
  MultiLasers& operator=(const MultiLasers&);
  virtual ~MultiLasers() { delete strategy; } 
  void draw() const;
  virtual void update(Uint32);
  void shoot(const Vector2f&, const Vector2f&);
  unsigned int laserCount() const { return laserList.size(); }
  unsigned int freeCount() const { return freeList.size(); }
  bool shooting() const { return !laserList.empty(); }
  bool collidWith(const Drawable* d) const;  
private:
  std::string name;
  Vector2f myVelocity;
  Frame* laserFrame;
  mutable std::list<MultiLaser> laserList;
  mutable std::list<MultiLaser> freeList;
  CollisionStrategy * strategy; 
};
#endif
