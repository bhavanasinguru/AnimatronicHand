#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(8, 7); // CE, CSN
const byte address1[6] = {"00001"};
const byte address2[6] = {"00002"};
void setup() {
  pinMode(10,OUTPUT);
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address1);
  radio.openReadingPipe(1,address2);
  radio.setPALevel(RF24_PA_MIN);
}
void loop() {
  radio.stopListening();
while(!Serial.available());
char  x=Serial.read();
switch(x){
  case 'a':
  {int flag =0;
  radio.write(&flag,sizeof(flag));
  radio.startListening();
  while(!radio.available());
  radio.stopListening();
  const int text[] = {1,2,3};
  Serial.println(sizeof(text));
  radio.write(&text, sizeof(text)); 
  
  Serial.print("transmitted :   ");
  
  Serial.print("  ,   ");
  for(int i=0;i<3;i++){Serial.println(text[i]);}
  break;
  }

  case 'b':
  {int flag =1;
  radio.write(&flag,sizeof(flag));
  radio.startListening();
  while(!radio.available());
  radio.stopListening();
  const int ext[5] = {5,6,7,8};
  Serial.println(sizeof(ext));
  radio.write(&ext, sizeof(ext)); 
  
  Serial.print("transmitted :   ");
  
  Serial.print("  ,   ");
  for(int i=0;i<4;i++){Serial.println(ext[i]);}
 break;}
  }
  }
