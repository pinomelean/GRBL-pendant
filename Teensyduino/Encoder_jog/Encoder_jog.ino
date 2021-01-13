#include "Keyboard.h"
#include <Encoder.h>

float encoder_jog(Encoder &,int buton,float &,char Axis,unsigned int feed);
float jog_encoders(int v);
int Vjog=1000;  //Max jog speed in mm/s

//Encoder pins (at least first one capable of interrupt)
Encoder xEnc(2,1);
const int xButton=12;
Encoder yEnc(0,27);
const int yButton=26;
Encoder zEnc(19,20);
const int zButton=44;

void setup() {
  pinMode(xButton,INPUT_PULLUP);
  pinMode(yButton,INPUT_PULLUP);
  pinMode(zButton,INPUT_PULLUP);
}

void loop() {
  
  jog_encoders(Vjog);
  
  delay(millis()%10);
}

float jog_encoders(int v){
  float dx,dy,dz;
  dx=-encoder_jog(xEnc,xButton,v);
  dy=-encoder_jog(yEnc,yButton,v);
  dz=-encoder_jog(zEnc,zButton,v);
  if(dx||dy||dz){
    Keyboard.print("$J=G91 X");
    Keyboard.print(dx);
    Keyboard.print(" Y");
    Keyboard.print(dy);
    Keyboard.print(" Z");
    Keyboard.print(dz);
    Keyboard.print(" F");
    float d=sqrt(sq(dx)+sq(dy)+sq(dz));
    Keyboard.println(d>=1)?v:v/10);
    return d;
  }
  else{
    return 0;
  }
}


float encoder_jog(Encoder &E,int Button,unsigned int F){
  float d=E.read();
  if(d>=4||d<=-4){
    d=(int)d/4;
    E.write(0);
    //d=((digitalRead(Button)==LOW)?d:d/10);
    return d;
  }
  else{
    return 0;
  }
}
