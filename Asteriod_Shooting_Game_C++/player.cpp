#include "player.h"

Player::~Player() { delete strategy; }

Player::Player(const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  frame(FrameFactory::getInstance().getFrame(name)),
  playerWidth( getFrame()->getWidth() ), 
  playerHeight( getFrame()->getHeight() ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")), 
  speedX(Gamedata::getInstance().getXmlInt(name+"/speedX")),
  speedY(Gamedata::getInstance().getXmlInt(name+"/speedY")),
  keyPressedX(false),
  keyPressedY(false),
  laserName(Gamedata::getInstance().getXmlStr(name+"/laserName")),
  lasers(MultiLasers(laserName)),
  laserInterval(Gamedata::getInstance().getXmlInt(name+"/laserInterval")),
  timeSinceLastLaser(0),
  minLaserSpeed(Gamedata::getInstance().getXmlInt(name+"/minLaserSpeed") ),
  strategy( new PerPixelCollisionStrategy )
{ }

Player::Player(const Player & p) :
  Drawable(p),
  frame(p.frame),
  playerWidth(p.playerWidth),
  playerHeight(p.playerHeight),
  worldWidth(p.worldWidth),
  worldHeight(p.worldHeight),
  speedX(p.speedX),
  speedY(p.speedY),
  keyPressedX(p.keyPressedX),
  keyPressedY(p.keyPressedY),
  laserName(p.laserName),
  lasers(p.lasers),
  laserInterval(p.laserInterval),
  timeSinceLastLaser(p.timeSinceLastLaser),
  minLaserSpeed(p.minLaserSpeed),
  strategy(p.strategy)
{ }

void Player::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frame->draw(x, y);
  lasers.draw();
}

void Player::update(Uint32 ticks) { 
  if(keyPressedX == false ){
      velocityX( 0 );
  }
  if(keyPressedY == false ){
      velocityY( 0 );
  }
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);
  if(Y() < 0 ){
    velocityY(speedY);
  }
  if(Y() > worldHeight - playerHeight){
    velocityY(-speedY);
  }
  if(X() < 0){
    velocityX(speedX);
  }
  if(X() > worldWidth - playerWidth){
    velocityX(-speedX);
  }
  keyPressedX = false;
  keyPressedY = false;
  timeSinceLastLaser += ticks;
  lasers.update(ticks);
}

void Player::shoot(bool down){
if(timeSinceLastLaser > laserInterval){
   Vector2f vel = getVelocity();
   if(down) vel = -getVelocity();
   float x = X() + playerWidth/2.8;
   float y = Y();
   vel[1] -= minLaserSpeed;
   lasers.shoot(Vector2f(x,y) , vel);
   timeSinceLastLaser = 0;
  } 
}

void Player::up(){
  keyPressedY = true;
  if( Y() > 0) {
    velocityY(-speedY);
 }
}

void Player::down(){
  keyPressedY = true;
  if( Y() < worldHeight - playerHeight) {
    velocityY(speedY);
  }
}

void Player::left(){
  keyPressedX = true;
  if( X() > 0 ) {
    velocityX(-speedX);
  }
}

void Player::right(){
  keyPressedX = true;
  if( X() < worldWidth - playerWidth ) {
    velocityX(speedX);
  }
}

void Player::stop(){
  velocityX(0);
  velocityY(0);
}
