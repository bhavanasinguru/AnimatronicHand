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
  Serial.println("green");
  radio.openWritingPipe(address2);
  radio.openReadingPipe(1, address1);
  radio.setPALevel(RF24_PA_MIN);
}
void loop()
{
  int flag=3;
  radio.startListening();
      while(!radio.available());
      radio.read(&flag,sizeof(flag));
      Serial.print("flag : ");
      Serial.println(flag);
      radio.stopListening();
    
  switch (flag)
  {
    case 0:
      {radio.write(&flag,sizeof(flag));
        radio.startListening();
        while(radio.available())
          {int text[3]={};
            radio.read(&text,sizeof(text));
            for(int i=0;i<(0.5*sizeof(text));i++ )Serial.println(text[i]);
          }
        break;
      }
    case 1:
      {radio.write(&flag,sizeof(flag));
        radio.startListening();
        if(radio.available())
          {int text[4]={};
            radio.read(&text,sizeof(text));
            for(int i=0;i<(0.5*sizeof(text));i++ )Serial.println(text[i]);
          }
        break;
      }
  }
  
}
