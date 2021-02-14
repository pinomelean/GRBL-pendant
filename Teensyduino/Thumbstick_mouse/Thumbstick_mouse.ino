#include "Mouse.h"
#include "Keyboard.h"
#include "Math.h"

const int stickButton=25; //Thumbstick inputs
const int xAxis=A1;
const int yAxis=A0;
const int clickL=11; //Mouse buttons
const int clickR=10;
int xoff,yoff; //Startup position offset

void mouse();

void setup(){
  pinMode(stickButton,INPUT_PULLUP);
  pinMode(clickL,INPUT_PULLUP);
  pinMode(clickR,INPUT_PULLUP);
  //Set starting position as 0,0
  xoff=analogRead(xAxis);
  yoff=analogRead(yAxis);
  
  Mouse.begin();
}

void loop(){
  delay(10-(millis()%10)); //10ms min loop time
  mouse();
}

void mouse(){
  //Pointer movement
  int range=10; //Maximum movement speed. Default:10
  int dead=15; //Dead zone. Increase to mask drift.
  int x=analogRead(xAxis)-xoff;
  int y=-(analogRead(yAxis)-yoff);
  signed char mx=0,my=0;
  
  if(abs(x)>dead){
    mx=map(abs(x),dead,512,1,range);
    if(x<0)mx=-mx;
  }
  if(abs(y)>dead){
    my=map(abs(y),dead,512,1,range);
    if(y<0)my=-my;
  }
  if(mx!=0||my!=0)Mouse.move(mx,my,0);
  
  //Mouse button control
  //If the mouse left button is pressed:
  if(digitalRead(clickL)==LOW) {
    // if the mouse is not pressed, press it:
    if(!Mouse.isPressed(MOUSE_LEFT))Mouse.press(MOUSE_LEFT);
  }
  //else the mouse button is not pressed:
  else{
    // if the mouse is pressed, release it:
    if(Mouse.isPressed(MOUSE_LEFT))Mouse.release(MOUSE_LEFT);
  }
    //If the mouse right button is pressed:
  if(digitalRead(clickR)==LOW) {
    // if the mouse is not pressed, press it:
    if(!Mouse.isPressed(MOUSE_RIGHT))Mouse.press(MOUSE_RIGHT);
  }
  //else the mouse button is not pressed:
  else{
    // if the mouse is pressed, release it:
    if(Mouse.isPressed(MOUSE_RIGHT))Mouse.release(MOUSE_RIGHT);
  }
}
