#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
#define sensor A1
#define led 13
#define motor 8
#define up 7
#define down 6
#define select 5
int menu = 0;
int upStatus;
int downStatus;
int selectStatus;
int selectValue;
//.................................................
void setup() {
  Serial.begin(9600);
  lcd.init();
  pinMode(sensor, INPUT);
  pinMode(led, OUTPUT);
  pinMode(motor, OUTPUT);
  pinMode(up, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  pinMode(select, INPUT_PULLUP);
  gioithieu();
  delay(5000);
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("VUON TU DONG");
  updateMenu();
}
//.................................................
void loop() {
  if (digitalRead(up) == LOW) {
    lcd.clear();
    menu--;
    if (menu < 0) {
      menu = 2;
    }
    updateMenu();
    delay(200);
  }

  if (digitalRead(down) == LOW) {
    lcd.clear();
    menu++;
    if (menu > 2) {
      menu = 0;
    }
    updateMenu();
    delay(200);
  }

  if (digitalRead(select) == LOW) {
    lcd.clear();
    selectValue = 1;
    do {
      if (digitalRead(up) == LOW || digitalRead(down) == LOW) {
        digitalWrite(led, LOW);
        digitalWrite(motor, LOW);
        selectValue = 0;
        lcd.clear();
        updateMenu();
        break;
      }
      updateMenu2();
    } while (digitalRead(select) != LOW && selectValue == 1);
  }
}

void gioithieu() {
  lcd.setCursor(6, 0);
  lcd.print("Nhom 5");
  lcd.setCursor(4, 1);
  lcd.print("VUON TU DONG");
  lcd.setCursor(2, 2);
  lcd.print("Bac");
  lcd.setCursor(12, 2);
  lcd.print("Dat");
  lcd.setCursor(2, 3);
  lcd.print("Hang");
  lcd.setCursor(12, 3);
  lcd.print("Van");
}

void updateMenu() {
  switch (menu) {
    case 0:
      lcd.setCursor(4, 0);
      lcd.print("VUON TU DONG");
      lcd.setCursor(0, 1);
      lcd.print("> Tu dong");
      lcd.setCursor(0, 2);
      lcd.print("  Tuoi 5s");
      lcd.setCursor(0, 3);
      lcd.print("  Tuoi 10s");
      break;
    case 1:
      lcd.setCursor(4, 0);
      lcd.print("VUON TU DONG");
      lcd.setCursor(0, 1);
      lcd.print("  Tu dong");
      lcd.setCursor(0, 2);
      lcd.print("> Tuoi 5s");
      lcd.setCursor(0, 3);
      lcd.print("  Tuoi 10s");
      break;
    case 2:
      lcd.setCursor(4, 0);
      lcd.print("VUON TU DONG");
      lcd.setCursor(0, 1);
      lcd.print("  Tu dong");
      lcd.setCursor(0, 2);
      lcd.print("  Tuoi 5s");
      lcd.setCursor(0, 3);
      lcd.print("> Tuoi 10s");
      break;
    case 3:
      break;
  }
}

void updateMenu2() {
  switch (menu) {
    case 0:
      lcd.setCursor(4, 0);
      lcd.print("TUOI TU DONG");
      tudong();
      break;
    case 1:
      lcd.setCursor(4, 0);
      lcd.print("TUOI 5 GIAY");
      tuoi5giay();
      break;
    case 2:
      lcd.setCursor(4, 0);
      lcd.print("TUOI 10 GIAY");
      tuoi10giay();
      break;
  }
}

void tudong() {
  lcd.setCursor(4, 0);
  lcd.print("TUOI TU DONG");
  lcd.setCursor(4, 1);
  lcd.print("DO AM");
  int value = analogRead(sensor);
  value = 100 - map(value, 0, 1023, 0, 100);
  lcd.setCursor(11, 1);
  lcd.print(value);
  if (value < 100) {
    lcd.setCursor(13, 1);
    lcd.print(' ');
  } else if (value < 10) {
    lcd.setCursor(12, 1);
    lcd.print(' ');
  }
  if (value > 70) {
    Serial.println("Do am binh thuong");
    lcd.setCursor(0, 2);
    lcd.print("    Do am dat ok    ");
    lcd.setCursor(0, 3);
    lcd.print("                   ");
    digitalWrite(led, LOW);
    digitalWrite(motor, LOW);
  }
  else if(value < 50) {
    Serial.println("Dat kho thieu nuoc");
    lcd.setCursor(0, 2);
    lcd.print(" Dat kho thieu nuoc ");
    digitalWrite(led, HIGH);
    digitalWrite(motor, HIGH);
    lcd.setCursor(0, 3);
    lcd.print("   MOTOR dang chay  ");
  }
}
void tuoi10giay() {
  digitalWrite(led, HIGH);
  digitalWrite(motor, HIGH);
  for (int i = 10; i >= 0; i--) {
    if (i == 0) {
      digitalWrite(led, LOW);
      digitalWrite(motor, LOW);
      selectValue = 0;
      lcd.clear();
      updateMenu();
      return 0;
    }
    lcd.setCursor(0, 2);
    lcd.print("Thoi gian con ");
    lcd.setCursor(16, 2);
    lcd.print(i);
    if (i < 10) {
      lcd.setCursor(17, 2);
      lcd.print(' ');
    }
    delay(1000);
  }
}
void tuoi5giay() {
  digitalWrite(led, HIGH);
  digitalWrite(motor, HIGH);
  for (int i = 5; i >= 0; i--) {
    if (i == 0) {
      digitalWrite(led, LOW);
      digitalWrite(motor, LOW);
      selectValue = 0;
      lcd.clear();
      updateMenu();
      return 0;
    }
    lcd.setCursor(0, 2);
    lcd.print("Thoi gian con ");
    lcd.setCursor(16, 2);
    lcd.print(i);
    delay(1000);
  }
}
