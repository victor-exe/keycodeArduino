// Use this example with the Adafruit Keypad products.
// You'll need to know the Product ID for your keypad.
// Here's a summary:
//   * PID3844 4x4 Matrix Keypad
//   * PID3845 3x4 Matrix Keypad
//   * PID1824 3x4 Phone-style Matrix Keypad
//   * PID1332 Membrane 1x4 Keypad
//   * PID419  Membrane 3x4 Matrix Keypad

#include "Adafruit_Keypad.h"
#include <Servo.h>
//sg90 9g twerpro
//zrx 345 keypad adafruit library

Servo myservo;

// define your specific keypad here via PID
#define KEYPAD_PID3844
// define your pins here
// can ignore ones that don't apply
#define R1    2
#define R2    3
#define R3    4
#define R4    5
#define C1    6
#define C2    7
#define C3    8
#define C4    9

#define greenLED 11
#define yellowLED 12
#define redLED 13


// leave this import after the above configuration
#include "keypad_config.h"

//initialize an instance of class NewKeypad
Adafruit_Keypad customKeypad = Adafruit_Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  
  Serial.begin(9600);
  customKeypad.begin();
  myservo.attach(10);
  myservo.write(0);
}

int greenLight = 0;
char keyPressed = 'x';
int pos = 0;

char letterA = '1', letterB = '2', letterC = '3', letterD = '4';

void loop() {
  // put your main code here, to run repeatedly:
  customKeypad.tick();

  while(customKeypad.available()){
    keypadEvent e = customKeypad.read();
    Serial.print((char)e.bit.KEY);
    Serial.println(" pressed");
    if(e.bit.EVENT == KEY_JUST_PRESSED){
      tone(12, 1000, 100);
      if(e.bit.KEY == letterA && keyPressed == 'x'){
        keyPressed = letterA;
      }
      else if(e.bit.KEY == letterB && keyPressed == letterA){
        keyPressed = letterB;
      }
      else if(e.bit.KEY == letterC && keyPressed == letterB){
        keyPressed = letterC;
      }
      else if(e.bit.KEY == letterD){
        if(keyPressed == letterC){
          keyPressed = 'x';
          digitalWrite(greenLED, HIGH);
          delay(400);
          digitalWrite(greenLED, LOW);
          for(int i = 0; i < 3; i++){
              digitalWrite(greenLED, HIGH);
              delay(70);
              digitalWrite(greenLED, LOW);
              delay(70);
          }
            for(int i = 0; i < 3; i++){
              tone(12, 1000);
              delay(50);
              noTone(12);
              delay(50);
            }
            myservo.write(90);
            delay(4000);
            for(int i = 0; i < 3; i++){
              tone(12, 1000);
              delay(50);
              noTone(12);
              delay(50);
            }
            myservo.write(0); 
          }
        else{
          for(int i = 0; i < 3; i++){
            digitalWrite(redLED, HIGH);
            delay(20);
            digitalWrite(redLED, LOW);
            delay(20);
            keyPressed = 'x';
          }
        }
      }

      else if(e.bit.KEY == '*'){
        delay(2000);
        if(e.bit.KEY == '*'){
          for(int i = 0; i < 3; i++){
            tone(12, 700);
            delay(50);
            noTone(12);
            delay(50);
          }
          letterA = e.bit.KEY;
          delay(50);
          letterB = e.bit.KEY;
          delay(50);
          letterC = e.bit.KEY;
          delay(50);
          letterD = e.bit.KEY;
        }
      }
    }
    else if(e.bit.EVENT == KEY_JUST_RELEASED) Serial.println(" released");
  }

  delay(10);
}
