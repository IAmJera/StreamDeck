/*This program is designed to exploit the program using the BadUSB vulnerability. 
Its peculiarity is that it ignores the keyboard layout and enters commands independently of it. 
For using large programs, a memory card slot has been added, on which files with Ducky Script are located.
You can add four times as many buttons at least*/
#include "Keyboard.h"
#include "GyverButton.h"
#include <SPI.h>
#include <string.h>
#include <SD.h>
File script;
boolean first = true;

GButton myButt1;
GButton myButt2;
GButton myButt3;
GButton myButt4;
GButton myButt5;
GButton myButt6;

String DEFAULT_FILE_NAME = "first.txt";
void setup() {
  Serial.begin(9600);
  myButt1.setType(LOW_PULL);
  myButt2.setType(LOW_PULL);
  myButt3.setType(LOW_PULL);
  myButt4.setType(LOW_PULL);
  myButt5.setType(LOW_PULL);
  myButt6.setType(LOW_PULL);
}

void loop() {
  int analog = analogRead(0);
  //Serial.println(analog);  //Uncomment this line to view the analog signal in the port monitor (It is required to specify the signal range for the buttons)
  myButt1.tick(analog < 1030 && analog > 1000);
  myButt2.tick(analog < 750 && analog > 600);
  myButt3.tick(analog < 600 && analog > 410);
  myButt4.tick(analog < 410 && analog > 290);
  myButt5.tick(analog < 290 && analog > 190);
  myButt6.tick(analog < 190 && analog > 80);
  
  // In quotes, you must indicate the name of the text file that is on the memory card and will be played when you click on the corresponding button
  if (myButt1.isClick()) {
    Serial.print("button 1");
    DEFAULT_FILE_NAME = "first.txt";
    startup();
  }
  if (myButt2.isClick()) {
    Serial.print("button 2");
    DEFAULT_FILE_NAME = "second.txt";
    startup();
  }
  if (myButt3.isClick()) {
    Serial.print("button 3");
    DEFAULT_FILE_NAME = "third.txt";
    startup();
  }
  if (myButt4.isClick()) {
    Serial.print("button 4");
    DEFAULT_FILE_NAME = "fourth.txt";
    startup();
  }
  if (myButt5.isClick()) {
    Serial.print("button 5");
    DEFAULT_FILE_NAME = "fifth.txt";
    startup();
  }
  if (myButt6.isClick()) {
    Serial.print("button 6");
    DEFAULT_FILE_NAME = "sixth.txt";
    startup();
  }
}

void startup() {
  if (!SD.begin(10)) {   // Here you can change the port of the memory card module
    return;
  }
  script = SD.open(DEFAULT_FILE_NAME); if (script) {
    Keyboard.begin();
    String line = "";
    while (script.available()) {
      char m = script.read();
      if (m == '\n') {
        Line(line);
        line = "";
      }
      else if ((int) m != 13) {
        line += m;
      }
    }
    Line(line);
    script.close();
  }
  else { }
  Keyboard.end();
}

void Line(String l) {
  int space_1 = l.indexOf(" "); if (space_1 == -1) {
    Press(l);
  }
  else if (l.substring(0, space_1) == "STRING") {
    Keyboard.print(l.substring(space_1 + 1));
  }
  else if (l.substring(0, space_1) == "DELAY") {
    int delaytime = l.substring(space_1 + 1).toInt();
    delay(delaytime);
  }
  else if (l.substring(0, space_1) == "REM") {} else {
    String remain = l;
    while (remain.length() > 0) {
      int latest_space = remain.indexOf(" ");
      if (latest_space == -1) {
        Press(remain);
        remain = "";
      }
      else {
        Press(remain.substring(0, latest_space));
        remain = remain.substring(latest_space + 1);
      }
      delay(5);
    }
  }
  Keyboard.releaseAll();
}

void Press(String b) {
  // Here the correspondence of words in the file to the code of the "Keyboard.h" library is indicatedтщеуз
  if (b.length() == 1) {
    char c = b[0];
    Keyboard.press(c);
  }
  else if (b.equals("ENTER")) Keyboard.press(KEY_RETURN);
  else if (b.equals("CTRL")) Keyboard.press(KEY_LEFT_CTRL);
  else if (b.equals("SHIFT")) Keyboard.press(KEY_LEFT_SHIFT);
  else if (b.equals("ALT")) Keyboard.press(KEY_LEFT_ALT);
  else if (b.equals("GUI")) Keyboard.press(KEY_LEFT_GUI);
  else if (b.equals("NUMLOCK")) Keyboard.press(219);
  else if (b.equals("UP") || b.equals("UPARROW")) Keyboard.press(KEY_UP_ARROW);
  else if (b.equals("DOWN") || b.equals("DOWNARROW")) Keyboard.press(KEY_DOWN_ARROW);
  else if (b.equals("LEFT") || b.equals("LEFTARROW")) Keyboard.press(KEY_LEFT_ARROW);
  else if (b.equals("RIGHT") || b.equals("RIGHTARROW")) Keyboard.press(KEY_RIGHT_ARROW);
  else if (b.equals("DELETE")) Keyboard.press(KEY_DELETE);
  else if (b.equals("PAGEUP")) Keyboard.press(KEY_PAGE_UP);
  else if (b.equals("PAGEDOWN")) Keyboard.press(KEY_PAGE_DOWN);
  else if (b.equals("HOME")) Keyboard.press(KEY_HOME);
  else if (b.equals("ESC")) Keyboard.press(KEY_ESC);
  else if (b.equals("INSERT")) Keyboard.press(KEY_INSERT);
  else if (b.equals("TAB")) Keyboard.press(KEY_TAB);
  else if (b.equals("END")) Keyboard.press(KEY_END);
  else if (b.equals("CAPSLOCK")) Keyboard.press(KEY_CAPS_LOCK);
  else if (b.equals("F1")) Keyboard.press(KEY_F1);
  else if (b.equals("F2")) Keyboard.press(KEY_F2);
  else if (b.equals("F3")) Keyboard.press(KEY_F3);
  else if (b.equals("F4")) Keyboard.press(KEY_F4);
  else if (b.equals("F5")) Keyboard.press(KEY_F5);
  else if (b.equals("F6")) Keyboard.press(KEY_F6);
  else if (b.equals("F7")) Keyboard.press(KEY_F7);
  else if (b.equals("F8")) Keyboard.press(KEY_F8);
  else if (b.equals("F9")) Keyboard.press(KEY_F9);
  else if (b.equals("F10")) Keyboard.press(KEY_F10);
  else if (b.equals("F11")) Keyboard.press(KEY_F11);
  else if (b.equals("F12")) Keyboard.press(KEY_F12);
  else if (b.equals("N9")) {
    Keyboard.press (233);
    Keyboard.release (233);
  }
  else if (b.equals("N8")) {
    Keyboard.press (232);
    Keyboard.release (232);
  }
  else if (b.equals("N7")) {
    Keyboard.press (231);
    Keyboard.release (231);
  }
  else if (b.equals("N6")) {
    Keyboard.press (230);
    Keyboard.release (230);
  }
  else if (b.equals("N5")) {
    Keyboard.press (229);
    Keyboard.release (229);
  }
  else if (b.equals("N4")) {
    Keyboard.press (228);
    Keyboard.release (228);
  }
  else if (b.equals("N3")) {
    Keyboard.press (227);
    Keyboard.release (227);
  }
  else if (b.equals("N2")) {
    Keyboard.press (226);
    Keyboard.release (226);
  }
  else if (b.equals("N1")) {
    Keyboard.press (225);
    Keyboard.release (225);
  }
  else if (b.equals("N0")) {
    Keyboard.press (234);
    Keyboard.release (234);
  }
}
