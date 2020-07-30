#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(8, 7); // CE, CSN

#define replicate_button 2
#define record_button 3
#define play_button 4

const byte address[6] = {"00001"};
int pin[5]={0,1,2,3,4};
int map_var[5]={720,720,720,720,720};
 
void setup() {
  // put your setup code here, to run once:
radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  Serial.begin(9600);
  // put your main code here, to run repeatedly:
 /*boolean replicate=digitalRead(replicate_button);
 boolean record=digitalRead(record_button); 
 boolean play=digitalRead(play_button);*/
int x=0;
 if(Serial.available()) x= Serial.read();
 /*int x=0;
 if(replicate==1) x=1;
 if(record == 1) x=2;
 if(play == 1) x=3;*/
 boolean flag=0;
 int temp[5][1000]={0};
 int fingers[5]={0};
 switch(x){
  case 1:
    //replicate module
     //read fingers input (mapped) to fingers array
     for (int i=0;i<5;i++)
      {
        //fingers[i]=map(analogRead[pin[i]],0,1023,0,map_var[i]);
        fingers[i]=map(pin[i],0,1023,0,map_var[i]);
      }
      delay(10);            //check delay here
      flag=0;
    radio.write(&flag, sizeof(flag));
      //write the array to the nrf module
    radio.write(&fingers, sizeof(fingers));
      break;
  case 2:
    
      //record module
      //read fingers input (mapped) to temp 2d array
      for(int n=0;n<1000;n++)
        {
          for(int i=0;i<5;i++)
          {
            temp[n][i]=analogRead(pin[i]);
            delay(15);                              //check delay here
          }
          
        }
      //store the values at temp 
    break;
  case 3: 
  
      //play module
      flag=1;
      radio.write(&flag,sizeof(flag));
      radio.write(&temp,sizeof(flag));
      //write to nrf module
  break;
 }
}
