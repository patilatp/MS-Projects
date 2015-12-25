#include <iostream>
#include "multiLasers.h"
#include "gamedata.h"
#include "frameFactory.h"

MultiLasers::MultiLasers( const std::string& name) :
  name(name),
  myVelocity( Gamedata::getInstance().getXmlInt(name+"/speed/x"),
    	      Gamedata::getInstance().getXmlInt(name+"/speed/y")),
  laserFrame(FrameFactory::getInstance().getFrame(name)),
  laserList(),
  freeList(),
  strategy(new PerPixelCollisionStrategy())
{ }

MultiLasers::MultiLasers(const MultiLasers& b) :
  name(b.name),
  myVelocity(b.myVelocity),
  laserFrame(b.laserFrame),
  laserList(b.laserList),
  freeList(b.freeList),
  strategy(b.strategy)
{}

MultiLasers& MultiLasers::operator=(const MultiLasers& rhs) {
  name = rhs.name;
  myVelocity = rhs.myVelocity;
  laserFrame = rhs.laserFrame;
  laserList = rhs.laserList;
  freeList = rhs.freeList;
  strategy = rhs.strategy;
  return *this;
}

bool MultiLasers::collidWith(const Drawable* obj) const {
  std::list<MultiLaser>::iterator ptr = laserList.begin();
  while(ptr != laserList.end()){
    if(strategy->execute(*ptr, *obj)){
      freeList.push_back(*ptr);
      ptr = laserList.erase(ptr);
      return true;
    }
    ++ptr;
  }
  return false;
}


void MultiLasers::shoot(const Vector2f& pos, const Vector2f& objVel){
  if(freeList.empty()){
    MultiLaser b(name, pos, objVel);
    laserList.push_back(b);
  }
  else{
    MultiLaser b = freeList.front();
    freeList.pop_front();
    b.reset();
    b.setVelocity(objVel);
    b.setPosition(pos);
    laserList.push_back(b);
  }
}

void MultiLasers::draw() const { 
  std::list<MultiLaser>::const_iterator ptr = laserList.begin();
  while(ptr != laserList.end()){
    ptr->draw();
    ++ptr;
  }
}

void MultiLasers::update(Uint32 ticks) {
  std::list<MultiLaser>::iterator ptr = laserList.begin();
  while(ptr != laserList.end()){
    ptr->update(ticks);
    if(ptr->goneTooFar()){
      freeList.push_back(*ptr);
      ptr = laserList.erase(ptr);
    }
    else ++ptr;
  }
}
