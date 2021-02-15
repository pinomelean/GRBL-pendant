#include <Mouse.h>
#include <Keyboard.h>
#include <Math.h>
#include <Button.h> //Change the debouncing delay to 100ms or fewer

//Thumbstick
Button stickButton=25; //Thumbstick inputs
const int xAxis=A1;
const int yAxis=A0;
Button clickL=11; //Mouse buttons
Button clickR=10;
int xoff,yoff; //Startup position offset

void mouse();

void setup(){
  //Thumbstick setup
  stickButton.begin();
  clickL.begin();
  clickR.begin();
  //Set starting position as 0,0
  xoff=analogRead(xAxis);
  yoff=analogRead(yAxis);
  
  Mouse.begin();
}

void loop(){
  delay(10-(millis()%10)); //10ms min loop time
  if(stickButton.read()==Button::RELEASED)mouse();
}

void mouse(){
  //Pointer movement
  int range=10; //Maximum movement speed. Default:10
  int dead=25; //Dead zone. Increase to mask drift.
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
  
  //Mouse buttons control
   if(clickL.pressed())Mouse.press(MOUSE_LEFT);
   if(clickL.released())Mouse.release(MOUSE_LEFT);
   
   if(clickR.pressed())Mouse.press(MOUSE_RIGHT);
   if(clickR.released())Mouse.release(MOUSE_RIGHT);
}
