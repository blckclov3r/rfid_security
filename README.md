# RFID Security
* Simple local rfid security project

# Hardware
 * Arduino Uno
 * LCD 16X2
 * Arduino MFRC522 RFID
 * Buzzer
 * Led
 * Servo sg90
 
# Circuit Diagram
![rfid_controller_system_with_lcd16x2_bb](https://user-images.githubusercontent.com/43292234/60394368-f88ac180-9ad7-11e9-8d98-694e792bd008.jpg)

# Source code pin
 * LCD 16X2 
   * VSS pin to GROUND
   * VCC/VDD pin to +5v
   * VO/VEE pin to Centre of potentiometer
   * LCD RS pin to digital pin 2
   * LCD Enable pin to digital pin 3
   * LCD D4 pin to digital pin 4
   * LCD D5 pin to digital pin 5
   * LCD D6 pin to digital pin 6
   * LCD D7 pin to digital pin 7
   * LCD R/W pin to GND

 * MFRC522 RFID
   * RST pin to 9
   * SDA pin to 10
   * MOSI pin to 11
   * MISO pin to 12                                         
   * SCK pin to 13
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
 * BUZZER 
   * pin to 8
   * pin to GND

 * LED 
   * redLed to A5
   * greenLed to A4
   * blueLed to A3

 * SERVO SG90
   * pin to A0
  
# Library  
 * Download the RFID library <a href="https://github.com/miguelbalboa/rfid">here</a> created by miguelbalboa
 * Unzip the RFID library
 * Install the RFID library in your Arduino IDE
 * Restart your Arduino IDE
 
