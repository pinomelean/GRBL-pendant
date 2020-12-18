#include "Keyboard.h"
#include <Encoder.h>

int encoder_jog(Encoder &,int buton,float &,char Axis,unsigned int feed);
int Vjog=2000;

Encoder xEnc(0,1);
const int xButton=27;

void setup() {
  pinMode(xButton,INPUT_PULLUP);
}

void loop() {
  
  encoder_jog(xEnc,xButton,'X',Vjog);

  delay(100);
}

int encoder_jog(Encoder &E,int Button,char Axis,unsigned int F){
  float d=E.read();
  if(d>=4||d<=-4){
    d=(int)d/4;
    Keyboard.print("$J=G91 ");
    Keyboard.print(Axis);
    if(d<0)Keyboard.print("-");
    d=abs(d);
    Keyboard.print(((digitalRead(Button)==HIGH)?d:d/10));
    Keyboard.print(" F");
    Keyboard.println(((digitalRead(Button)==HIGH)?F:F/10));
    E.write(0);
    return 1;
  }
  else{
    return 0;
  }
}
