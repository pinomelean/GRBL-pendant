#include "Keyboard.h"

//Thumbstick inputs
const int stickButton=25;
const int xAxis=A2;
const int yAxis=A0;
int xoff,yoff; //Startup position offset
bool jogging;

float jog(int f);

void setup() {
  //Set starting thumbstick position as 0,0
  xoff=analogRead(xAxis);
  yoff=analogRead(yAxis);
  jogging=false;
  pinMode(stickButton, INPUT_PULLUP);
  
  Keyboard.begin();
}

void loop() {
  delay(10-(millis()%10)); //10ms min loop time
  if((millis()%100<=10))jog(2000);
}

float jog(int f){
  int dead=5; //Stick dead zone
  int stepFactor=15; //Set according to machine (default 15)
  //smaller factor => choppier movement
  //bigger factor => response delay (stopping)
  float x=analogRead(xAxis)-xoff;
  float y=analogRead(yAxis)-yoff;
  float d=sqrt(sq(x)+sq(y));
  if((d>=dead)&&(digitalRead(stickButton)==LOW)){
    jogging=true;
    float jx=(abs(x)>dead)?x/(f/stepFactor):0;
    float jy=(abs(y)>dead)?y/(f/stepFactor):0;
    Keyboard.print("$J=G91 X");
    Keyboard.print(jx);
    Keyboard.print(" Y");
    Keyboard.print(jy);
    Keyboard.print(" F");
    Keyboard.println(map(d/20,0,512/20,100,f));
    return d;
  }
  else{
    if(jogging){
      Keyboard.println("G4P0");
    }
    jogging=false;
    return 0;
  }

  
}
