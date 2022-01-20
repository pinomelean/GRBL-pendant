
/*  PENDANT LAYOUT WITH PIN CONNECTIONS
      ________________________________
    /   ______     ______     ______   \
   /   |      |   |      |   |      |   \
  /    |   9  |   |  24  |   |  23  |    \
 |     |______|   |______|   |______|     |
 |   ________                  ________   |
 |  |        |    ________    |        |  |
 |  |  11   /   /          \   \   22  |  |
 |  |_____ /   |         >  |   \ _____|  |
 |   _____     |     25  A1 |     _____   |
 |  |      \   |   v A0     |   /      |  |
 |  |  10   \   \ ________ /   /   42  |  |
 |  |________|                |________|  |
 |      ____        ____        ____      |
 |    /  12  \    /  26  \    /  44  \    |
 |   (  2  1  )  (  0 27  )  ( 19  20 )   |
 |    \ ____ /    \_____ /    \ ____ /    |
 |     ______      ______      ______     |
 |    |  5   |    |  7   |    |  21  |    |
 |    |______|    |______|    |______|    |
 |   ___      ____        ____      ___   |
 |  |   |   /  8   \    /  40  \   |   |  |
 |  | 6 |  (  3  4  )  ( 18  41 )  | 41|  |
 |  |___|   \ ____ /    \ ____ /   |___|  |
 |     ______        __        ______     |
 |    |      |     / 29 \     |      |    |
 |    | 13  /     ( ____ )     \  33 |    |
 |    |___ /   __   ____   __   \ ___|    |
 |           /   | |    | |   \           |
 |          ( 15 | | 32 | | 28 )          |
 |     ___   \ __| |____| |__ /   ___     |
 |    |    \        ____        /    |    |
  \   | 14  \     (  17  )     /  16 |   /
   \  |______|     \ __ /     |______|  /
    \ ________________________________ /

 25 - thumbstick push button
 A1, and A0 - thumbstick axes
 12, 26, 44, 8, and 40 - encoder push buttons
 2, 1; 0, 27; 19, 20; 3, 4; and 18, 41; - encoder quadrature outputs
*/
 
#include <Keyboard.h>
#include <Encoder.h>
#include <Mouse.h>
#include <math.h>
#include <Button.h> //Change the debouncing delay to 100ms or fewer


//Thumbstick
Button stickButton=25; //Thumbstick inputs
const int xAxis=A1;
const int yAxis=A0;
Button clickL=11; //Mouse buttons
Button clickR=10;
int xoff,yoff; //Startup position offset

void mouse();

//Jogging encoders
int encoder_jog(Encoder &,Button Push,float &,char Axis,unsigned int Feed); 
int Vjog=1500;  //Maximum jogging speed at 1mm/detent
Encoder xEnc(2,1); 
Button xButton=12;
Encoder yEnc(0,27); 
Button yButton=26;
Encoder zEnc(19,20); 
Button zButton=44;
bool enc[3]={0,0,0}; //Flag vector to chech for encoder rotation
 

void setup() {
  //Thumbstick setup
  stickButton.begin();
  clickL.begin();
  clickR.begin();
  //Set starting position as 0,0
  xoff=analogRead(xAxis);
  yoff=analogRead(yAxis);
  
  Mouse.begin();
  //Encoder setup
  xButton.begin();
  yButton.begin();
  zButton.begin();
} 
 
void loop() { 
  delay(10-(millis()%10)); //10ms min loop time

  //Thumbstick mouse
  if(stickButton.read()==Button::RELEASED)mouse();
  
  //Jogging encoders 
  if((millis()%100<=10)){ //executes every 100ms
    enc[0]+=encoder_jog(xEnc,xButton,'X',Vjog);
    if(xButton.pressed())enc[0]=0; //Pulses are counted starting when pushed in
    //If he encoder is pushed and released without turning, the axis is zeroed
    if(xButton.released()&&enc[0]==0)Keyboard.println("G10 L20 P0 X0"); 
    enc[1]+=encoder_jog(yEnc,yButton,'Y',Vjog);
    if(yButton.pressed())enc[1]=0;
    if(yButton.released()&&enc[1]==0)Keyboard.println("G10 L20 P0 Y0");
    enc[2]+=encoder_jog(zEnc,zButton,'Z',Vjog);
    if(zButton.pressed())enc[2]=0;
    if(zButton.released()&&enc[2]==0)Keyboard.println("G10 L20 P0 Z0");
  }
  
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

int encoder_jog(Encoder &E,Button Push,char Axis,unsigned int Feed){ 
  float d=E.read(); 
  if(d>=4||d<=-4){  //Each detent generates 4 pulses
    d=(int)d/4; //Pulses reduced to only 1 per detent
    Keyboard.print("$J=G91 "); 
    Keyboard.print(Axis); 
    if(d<0)Keyboard.print("-"); 
    d=abs(d); 
    //If the encoder is pushed in, both the distance and speed are reduced to 1/10 for precise positioning
    Keyboard.print(((Push.read()==Button::PRESSED)?d/10:d)); 
    Keyboard.print(" F"); 
    Keyboard.println(((Push.read()==Button::PRESSED)?Feed/10:Feed)); 
    E.write(0); 
    return 1; 
  } 
  else{ 
    return 0; 
  } 
} 
