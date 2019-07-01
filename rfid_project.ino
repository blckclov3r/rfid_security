/*
 *    instagram.com/blckclov3r
 *    blckclov3r@gmail.com
 *    facebook.com/blckclov3r
 */
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <LiquidCrystal.h>

const uint8_t rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int static count = 0;
const int BUZZER = 8; //buzzer pin

Servo myServo; //define servo name
constexpr uint8_t RST_PIN = 9;          // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = 10;         // Configurable, see typical pin layout above
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

const int redPin = A1;
const int greenPin = A2;
const int bluePin = A3;
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin(); 
  lcd.begin(16,2);
  mfrc522.PCD_Init(); 

  pinMode(BUZZER,OUTPUT);
  noTone(BUZZER);
  setupColor(0,255,0);
  lcd.setCursor(1,0);
  lcd.print("RFID Controller");
  lcd.setCursor(2,1);
  lcd.print("+- SYSTEM -+");
  delay(1500);
  lcd.clear();

  
  lcd.setCursor(2,0);
  lcd.print("Instr. Eng'r");
  lcd.setCursor(0,1);
  lcd.print("Wilmer B Fuentes");
  delay(2000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Behind The Scene");
  lcd.setCursor(2,1);
  lcd.print("    Aljun    ");
  delay(1500);
  lcd.clear();
  
  myServo.attach(A0); //servo pin
  myServo.write(0); //servo start position
  Serial.println("\t+----------------------------+");
  Serial.println("\t|   RFID Controller System   |");
  Serial.println("\t+----------------------------+\n");
  Serial.println("\tLet me scan your card to Identify: \n");
  
}

void loop() 
{
  setupColor(0,0,255);
  lcd.setCursor(0,0);
  lcd.print("   Please Scan  ");
  lcd.setCursor(0,1);
  lcd.print("    To Verify   ");
  // Look for new cards
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
  Serial.print("\tUID tag :");
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
  Serial.print("\tMessage : ");
  content.toUpperCase();
  
  if (content.substring(1) == "C4 D7 41 79" || content.substring(1) == "B4 34 27 FD"){
    count = 0;
    while(content.substring(1) == "B4 34 27 FD"){
       lcd.clear();
       Serial.println("\n");
       Serial.println("\t+--------------------------+");
       Serial.println("\t|  Login as Administrator  |");
       Serial.println("\t+--------------------------+\n");
       setupColor(255,255,255);
       tone(BUZZER,700);
       delay(300);
       noTone(BUZZER);
       lcd.setCursor(0,0);
       lcd.print("    Access as");
       lcd.setCursor(0,1);
       lcd.print("  Administrator");
       myServo.write(90);
       delay(5050);
       break;
    }
    while(content.substring(1) == "C4 D7 41 79"){
    lcd.clear();
    setupColor(0,255,0);
    tone(BUZZER, 500);
    delay(300);
    noTone(BUZZER);
    lcd.setCursor(1,0);
    lcd.print("Authorization");
    lcd.setCursor(2,1);
    lcd.print("A C C E S S");
    Serial.println(" ACCESS GRANTED!");
    myServo.write(90);
    delay(5050);
    break;
    }
    myServo.write(0);
    lcd.clear();
  }
 
  else{
    count+=1;
    myServo.write(0);
    lcd.clear();
    setupColor(255,0,0);
    lcd.setCursor(3,0);
    lcd.print("A C C E S S");
    lcd.setCursor(3,1);
    lcd.print("D E N I E D");
    Serial.print(" ACCESS DENIED!\n");
    tone(BUZZER,200);
    delay(800);
    noTone(BUZZER);
    lcd.clear();
    if(count == 2){
       lcd.clear();
       setupColor(255,255,255);
       Serial.println("\n\t+-- W A R N I N G --+\n");
       lcd.setCursor(2,0);
       lcd.print("W A R N I N G");
       lcd.setCursor(0,1);
       lcd.print("Unregistered UID");
       delay(1000);
       myServo.write(0);
       lcd.clear();
    }
    if(count == 3){ 
        lcd.clear();
        setupColor(255,255,255);
        lcd.setCursor(0,0);
        lcd.print("Failed to Verify");
        lcd.setCursor(0,1);
        lcd.print("try again, later");
        Serial.println("\t+-- Unregistered UID --+");
        Serial.println("\t+-- 10sec. countdown --+\n");
        noTone(BUZZER);
        delay(1000);
        for(int i=0;i<5;i++){
           setupColor(255,0,0);
           tone(BUZZER,200);
           delay(1000);
           setupColor(255,255,255);
           noTone(BUZZER);
           delay(1000);
        }//eo for
    }//eo if count == 3
    myServo.write(0);
    lcd.clear();
  

   if(count == 5){
      lcd.clear();
      setupColor(0,255,0);
      Serial.println();
      Serial.println("\t+-------------------------------------+");
      Serial.println("\t|  Need help?, ask the administrator  |");
      Serial.println("\t+-------------------------------------+\n");
      lcd.setCursor(2,0);
      lcd.print("Want a help?");
      lcd.setCursor(3,1);
      lcd.print("Ask, Aljun");
      delay(2500);
      myServo.write(0);
      lcd.clear();
  }
  if(count == 6){
      lcd.clear();
      setupColor(0,0,255);
      Serial.println();
      Serial.println("\t+-------------------------------------+");
      Serial.println("\t|        Need help?, ask Aljun        |");
      Serial.println("\t+-------------------------------------+\n");
      lcd.setCursor(0,0);
      lcd.print("Unidentified UID");
      lcd.setCursor(0,1);
      lcd.print("Please try again");
      noTone(BUZZER);
      delay(1000);
      for(int i=0;i<5;i++){
           setupColor(255,0,0);
           tone(BUZZER,200);
           delay(1000);
           setupColor(0,0,255);
           noTone(BUZZER);
           delay(1000);
      }
      myServo.write(0);
      lcd.clear();
      count = 0;
    }
  }
     myServo.write(0);
} 
void setupColor(int red,int green,int blue){
   analogWrite(redPin,red);
   analogWrite(greenPin,green);
   analogWrite(bluePin,blue);
}
