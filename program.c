//include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


int sensor = 9;//mic
int buzzer = 10;

 

void setup()
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  lcd.setCursor(0,0);
    lcd.print("Industrial");
   
  lcd.setCursor(0,1);
    lcd.print(" Automation ");
  delay(1000);
  //pinMode(motor, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(sensor, INPUT);// put your setup code here, to run once:
}
 
void loop() {
    int gas=analogRead(sensor);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Sound:");
    lcd.setCursor(0,1);
    lcd.print(ip);
   
    delay(500);
   if(gas>370)
   {
   lcd.setCursor(0,0);
    lcd.print("Noise in  ");
    lcd.setCursor(0,1);
    lcd.print("Danger level");
     delay(500);
     lcd.clear();
   digitalWrite(buzzer, HIGH);
 //  digitalWrite(motor, HIGH);
   lcd.print("      HIGH  ");
    delay(500);
    digitalWrite(buzzer, LOW);
      delay(1000);
    digitalWrite(buzzer, HIGH);
      delay(500);
        digitalWrite(buzzer, LOW);
   }
    if(gas<370)
   {
    digitalWrite(buzzer, LOW);
   //digitalWrite(motor, LOW);
   lcd.print("      LOW  ");
    delay(500);
   
   }
}

            
