#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
/*#include<Servo.h>
Servo myservo1
Servo myservo2
Servo myservo3
Servo myservo4
Servo myservo5*/

RF24 radio(8, 7); // CE, CSN

const byte address[6] = "00001";
 int fingers[5]={0};

void setup() {
  // put your setup code here, to run once:
/*myservo1.attach(3);
myservo2.attach(5);
myservo3.attach(6);
myservo4.attach(9);
myservo5.attach(10);*/
boolean flag=0;
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}
void loop() {
  if (radio.available()) {
    boolean text;
    radio.read(&text, sizeof(text));
    Serial.println(text);
    switch(text)
     { case 0:
        int fingers[5]={};
        radio.read(&fingers,sizeof(fingers));
        for(int i=0;i<5;i++)
          {
            Serial.println(fingers[i]);
            Serial.println("\n");
          }
        /*myservo1.write(finger[1]);
        myservo2.write(finger[2]);
        myservo3.write(finger[3]);
        myservo4.write(finger[4]);
        myservo5.write(finger[5]);*/

        break;
      case 1:
        int temp[5][1000]={0};
        radio.read(&temp,sizeof(temp));
        for(int n=0;n<1000;n++)
          {
            /*myservo1.write(temp[1][n]);
            myservo2.write(temp[2][n]);
            myservo3.write(temp[3][n]);
            myservo4.write(temp[4][n]);
            myservo5.write(temp[5][n] );*/
            for(int i=0;i<5;i++)
          {
            Serial.println(temp[i][n]);
            Serial.println("\n");
          } 
          }
          break;
          
  }}

}
