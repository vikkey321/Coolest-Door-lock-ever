#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
 

#define RINGPIN 6

#define SS_PIN 10
#define RST_PIN 9


Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
MFRC522 mfrc522(SS_PIN, RST_PIN);  


uint8_t NUMPIXELS = 10;      // total number of LED's in the ring display
int ot = 1;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, RINGPIN, NEO_RGB + NEO_KHZ800);  // an instance for the LED ring display

void setup() {
  // put your setup code here, to run once:
  myservo.attach(5);
  strip.begin();
  pinMode(7, OUTPUT);
  Serial.begin(9600);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Please Scan Your Card...");
  Serial.println();
  clearled();
  //servocheck();
  myservo.write(90);
}



void loop() {

  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  content.toUpperCase();
  if (content.substring(1) == "86 AB 84 A5") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Card Identified");
    digitalWrite(7, HIGH);
    delay(200);
    digitalWrite(7, LOW);
    delay(200);
    digitalWrite(7, HIGH);
    delay(200);
    digitalWrite(7, LOW);
    Serial.println();
    granted();

    myservo.write(179);
    for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
      strip.setPixelColor(i, strip.Color(255, 0, 0));
      strip.setPixelColor(NUMPIXELS - i, strip.Color(255, 0, 0));
      strip.show();
      delay(35);
    }
    delay(3000);

    
    for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
      strip.setPixelColor(i, strip.Color(0, 0, 0));
      strip.setPixelColor(NUMPIXELS - i, strip.Color(0, 0, 0));
      strip.show();
      delay(50);
    }
    myservo.write(90);
    
  }
 
  else   {
   Serial.println("Card Not Identified");
   digitalWrite(7, HIGH);
   delay(200);
   digitalWrite(7, LOW);
   delay(200);
   digitalWrite(7, HIGH);
   delay(200);
   digitalWrite(7, LOW);
   delay(200);
   digitalWrite(7, HIGH);
   delay(200);
   digitalWrite(7, LOW);
   denied();
   delay(2000);
  }


}
void granted(){
  for(int m=0;m<=2;m++){
 for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(255, 0, 0));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(255, 0, 0));
    strip.show();
    delay(35);
  }
for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(0, 0, 0));
    strip.show();
    delay(50);
  }
   for (int i = NUMPIXELS / 2; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(255, 0, 0));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(255, 0, 0));
    strip.show();
    delay(35);
  }
for (int i = NUMPIXELS / 2 ; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(0, 0, 0));
    strip.show();
    delay(50);
  }
  }

  
  }

void denied(){
  for(int m=0;m<=2;m++){
 for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(0, 255, 0));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(0, 255, 0));
    strip.show();
    delay(35);
  }
for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(0, 0, 0));
    strip.show();
    delay(50);
  }
   for (int i = NUMPIXELS / 2; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(0, 255, 0));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(0, 255, 0));
    strip.show();
    delay(35);
  }
for (int i = NUMPIXELS / 2 ; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(0, 0, 0));
    strip.show();
    delay(50);
  }
  }
  for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(0, 255, 0));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(0, 255, 0));
    strip.show();
    delay(35);
  }
  delay(1000);
for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(0, 0, 0));
    strip.show();
    delay(50);
  }

  }
void clearled()
{
  for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(0, 0, 0));
    strip.show();
    delay(50);
  }
  }

  
