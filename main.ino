#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <string>
#include <cmath>

using namespace std;

LiquidCrystal_I2C lcd(0x3F, 16, 2);

#define ROW_NUM     4 // four rows
#define COLUMN_NUM  3 // three columns

String all = "", amal = "no", num2 = "";
int num1;

char keys[ROW_NUM][COLUMN_NUM] = {
  {'2', '1', '3'},
  {'5', '4', '6'},
  {'8', '7', '9'},
  {'0', '*', '#'}
};
byte pin_rows[ROW_NUM] = {18, 5, 17, 16}; // GIOP18, GIOP5, GIOP17, GIOP16 connect to the row pins
byte pin_column[COLUMN_NUM] = {2, 4, 15};  // GIOP4, GIOP0, GIOP2 connect to the column pins
Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

void setup() {
  lcd.begin();
	lcd.backlight();
}

void loop() {
  char key = keypad.getKey();
  if (key == '#') {
    all = "";
    num2 = "";
    amal = "no";
    lcd.clear();
  }
  else if (key == '*' && num2 == "") {
    if (all.length() > 0 && all.substring(all.length()-5) == "*****") {
      num1 = all.substring(0, all.length()-5).toInt();
      all = String(num1);
      lcd.clear();
      lcd.print(all);
    }
    else if (all.length() > 0 && all.substring(all.length()-4) == "****") {
      num1 = all.substring(0, all.length()-4).toInt();
      all += "*";
      amal = "^";
      lcd.clear();
      lcd.print(String(num1)+amal);
    }
    else if (all.length() > 0 && all.substring(all.length()-3) == "***") {
      num1 = all.substring(0, all.length()-3).toInt();
      all += "*";
      amal = "-";
      lcd.clear();
      lcd.print(String(num1)+amal);
    }
    else if (all.length() > 0 && all.substring(all.length()-2) == "**") {
      num1 = all.substring(0, all.length()-2).toInt();
      all += "*";
      amal = "+";
      lcd.clear();
      lcd.print(String(num1)+amal);
    }
    else if (all.length() > 0 && all[all.length()-1] == '*') {
      num1 = all.substring(0, all.length()-1).toInt();
      all += "*";
      amal = "/";
      lcd.clear();
      lcd.print(String(num1)+amal);
    }
    else if (all.length() > 0 && all[all.length()-1] != '*') {
      num1 = all.substring(0, all.length()).toInt();
      all += "*";
      amal = "*";
      lcd.print('*');
    }
  }
  else if (key == '*' && num2 != "") {
    if (amal == "*") {
      lcd.print(" :");
      lcd.setCursor(0,1);
      lcd.print(num1*num2.toInt());
    }
    else if (amal == "^") {
      lcd.print(" :");
      lcd.setCursor(0,1);
      lcd.print(pow(num1, num2.toInt()));
    }
    else if (amal == "-") {
      lcd.print(" :");
      lcd.setCursor(0,1);
      lcd.print(num1-num2.toInt());
    }
    else if (amal == "/") {
      lcd.print(" :");
      lcd.setCursor(0,1);
      lcd.print(num1/num2.toInt());
    }
    else if (amal == "+") {
      lcd.print(" :");
      lcd.setCursor(0,1);
      lcd.print(num1+num2.toInt());
    }
  }
  else if (key) {
    if (amal != "no") {
      num2 += key;
    }
    all += key;
    lcd.print(key);
  }
}