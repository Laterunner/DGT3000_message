/*
   To be used with arduino micro (32u4).
   A DGT3000 chess clock was modified with a KY025 Reed Sswitch, placed parallel to the built in Reed Contact.
   Now moves are counted and send as messages via USB each time the Lever is pressed by a Player.
   These messages are further processed and trigger events in a python program running an the connected computer.
   Bouncing is avoided by the circuit of the KY025.
   THe Message is displayed on a 2004 LCD screen.
   A passive buzzer KY06  is used to produce a short beep (30 msecs) each time the lever is pressed.
   August 2021, Marius Bartsch

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/KeyboardMessage
*/

#include <Wire.h> // Wire Bibliothek einbinden
#include <LiquidCrystal_I2C.h> // Vorher hinzugefügte LiquidCrystal_I2C Bibliothek einbinden
LiquidCrystal_I2C lcd(0x27, 20, 4);

#include <Keyboard.h>
// prints characters of american keyboard layout. If Computer uses s German keyboard care for y,x, :, ä,ö etc!

const int buttonPin = 4;          // input pin for pushbutton
int previousButtonState = HIGH;   // for checking the state of a pushButton
int counter = 0;                  // button push counter
int chess_move = 0;


void setup() {
  // make the pushButton pin an input
  pinMode(buttonPin, INPUT);

  lcd.init(); //Im Setup wird der LCD gestartet
  lcd.backlight(); //Hintergrundbeleuchtung einschalten (lcd.noBacklight(); schaltet die Beleuchtung aus).

  // initialize control over the keyboard:
  Keyboard.begin();
  //delay(2000);
}


void loop() {

  lcd.setCursor(0, 0);//Hier wird die Position des ersten Zeichens festgelegt. In diesem Fall bedeutet (0,0) das erste Zeichen in der ersten Zeile.
  lcd.print("Hi Chessfriends!");

  if (counter  < 2) {
    lcd.setCursor(0, 1);// In diesem Fall bedeutet (0,1) das erste Zeichen in der zweiten Zeile.
    lcd.print("Press lever to start");
  }

  // read the pushbutton:
  int buttonState = digitalRead(buttonPin);
  // if the button state has changed,
  if (buttonState != previousButtonState) {
    chess_move = counter / 2;
    lcd.setCursor(0, 1);
    lcd.clear();
    if (counter > 0 && counter % 2 == 0) {
      Keyboard.println("Black to move");
      lcd.setCursor(0, 2);
      lcd.print("Black to move ");
      lcd.print(counter / 2);
      lcd.print(" ...");
    }
    if (counter > 0 && counter % 2 == 1) {
      Keyboard.println("White to move");
      lcd.setCursor(0, 2);
      lcd.print("White to move ");
      lcd.print(counter / 2 + 1);
      lcd.print(" ...");
    }
    counter++;
    tone(5, 852, 30);
    //noTone(5);
  }
  // save the current button state for comparison next time:
  previousButtonState = buttonState;
}
