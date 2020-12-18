#include "Keyboard.h"

const int buttonPin = 3;
const int xAxis=A0;
const int yAxis=A1;
int zx=511,zy=511;
bool jogging;

void jog();

void setup() {
  zx=analogRead(xAxis);
  zy=analogRead(yAxis);
  jogging=false;
  pinMode(buttonPin, INPUT_PULLUP);
  Keyboard.begin();
}

void loop() {
  
  jog();
  
  delay(25);
}

void jog(){
  int threshold=20;
  float jx=0,jy=0,v=0;
  int x=analogRead(xAxis)-zx;
  int y=analogRead(yAxis)-zy;
  v=sqrt(sq(x)+sq(y));
  if(v>threshold){
    jogging=true;
    jx=((float)x/200);
    jy=((float)y/200);
    Keyboard.print("$J=G91 X");
    Keyboard.print(jx);
    Keyboard.print(" Y");
    Keyboard.print(jy);
    Keyboard.print(" F");
    Keyboard.println(v*2+200);
  }
  else{
    if(jogging){
      Keyboard.println("G4P0");
    }
    jogging=false;
  }

  
}
