#include "headsUpDisplay.h"
#include <iostream>
#include <string>
#include <iomanip>
#include "gamedata.h"
#include "aaline.h"

HeadsUpDisplay::HeadsUpDisplay() :
  HUD_WIDTH(Gamedata::getInstance().getXmlInt("hud/HUD_WIDTH")),
  HUD_HEIGHT(Gamedata::getInstance().getXmlInt("hud/HUD_HEIGHT")),
  x(8),
  y(8),
  secondsLocation(10,20),
  fpsLocation(10,40),
  playerMovementLocation(10,60),
  toggleHUDLocation(10,80),
  restartGameLocation(10,100),
  laserListLocation(10,120),
  freeListLocation(10,140),
  shootinginfolocation(10,160),
  playergoal(10,180),
  playergoalextend(10,200)
{}
void HeadsUpDisplay::drawHUD(SDL_Surface * const& screen, const IOManager& io,int seconds,int fps , unsigned int laserCount , unsigned freeCount) const{
 
  const Uint32 RED = SDL_MapRGB(screen->format, 0xff, 0, 0);
  Draw_AALine(screen, x, y+HUD_HEIGHT/2, x+HUD_WIDTH, y+HUD_HEIGHT/2, HUD_HEIGHT, 0xff, 0xff, 0xff, 0xff/2);
    io.printMessageValueAt("Seconds: ", seconds, secondsLocation[0], secondsLocation[1]);
    io.printMessageValueAt("fps: ", fps, fpsLocation[0], fpsLocation[1]);
    io.printMessageAt("Use WASD to control the player.", playerMovementLocation[0], playerMovementLocation[1]);
    io.printMessageAt("Press F1 to toggle HUD.", toggleHUDLocation[0], toggleHUDLocation[1]);
    io.printMessageAt("Press R to restart the game.", restartGameLocation[0], restartGameLocation[1]);
    io.printMessageValueAt("Laser List Count: ", laserCount, laserListLocation[0], laserListLocation[1]);
    io.printMessageValueAt("Free List Count: ", freeCount, freeListLocation[0], freeListLocation[1]);
    io.printMessageAt("Use Space Bar to shoot",shootinginfolocation[0],shootinginfolocation[1]);
    io.printMessageAt("Goal: To Shoot the Asteroid &",playergoal[0],playergoal[1]);
    io.printMessageAt("earn as much points as you can",playergoalextend[0],playergoalextend[1]);
  Draw_AALine(screen, x,y, x+HUD_WIDTH,y, RED);
  Draw_AALine(screen, x,y, x,y+HUD_HEIGHT, RED);
  Draw_AALine(screen, x,y+HUD_HEIGHT, x+HUD_WIDTH,y+HUD_HEIGHT, RED);
  Draw_AALine(screen, x+HUD_WIDTH,y, x+HUD_WIDTH,y+HUD_HEIGHT, RED);
}
