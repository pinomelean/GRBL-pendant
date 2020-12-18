#include "Mouse.h"
#include "Math.h"

const int joystickButton=27;
const int xAxis=A0;
const int yAxis=A1;
int xoff,yoff; //Startup position offset

void mouse();

void setup(){
  pinMode(joystickButton,INPUT);
  Mouse.begin();
  //Set starting position as 0,0
  xoff=analogRead(xAxis)-512;
  yoff=analogRead(yAxis)-512;
}

void loop(){
  mouse();
  delay(5);
}

void mouse(){
  int range=10; //Maximum movement speed. Default:10
  int dead=2; //Dead zone.
  int x=analogRead(xAxis)-xoff;
  int y=analogRead(yAxis)-yoff;
  signed char mx=(abs(x)>dead)?map(x,0,1023,-range,range):0;
  signed char my=(abs(y)>dead)?map(y,0,1023,-range,range):0;
  if(mx!=0||my!=0){
    Mouse.move(mx,my,0);
  }
}
