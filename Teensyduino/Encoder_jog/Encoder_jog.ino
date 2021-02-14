#include <Keyboard.h>
#include <Encoder.h>
#include <Button.h> 

//Jogging encoders
int encoder_jog(Encoder &,Button Push,float &,char Axis,unsigned int Feed); 
int Vjog=1000;  //Maximum jogging speed at 1mm/detent
Encoder xEnc(2,1); 
Button xButton=12;
Encoder yEnc(0,27); 
Button yButton=26;
Encoder zEnc(19,20); 
Button zButton=44;
bool enc[3]={0,0,0}; //Flag vector to chech for encoder rotation
 
void setup() {
  //Encoder setup
  xButton.begin();
  yButton.begin();
  zButton.begin();
} 
 
void loop() { 
  
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
 
  delay(10-(millis()%10)); //10ms min loop time 
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
