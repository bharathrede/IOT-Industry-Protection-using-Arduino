SoftwareSerial wifi(2,3); // RX, TX
String apiKey = "UPY099IS3UF0TQ0O";     //5N648YQF26XV4ENY

const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int  light = 6; //lightogic ckt
const int  motor = 5;//fan
const int fire = 4;//fire
const int buzzer = 13;

int fire_data;
int ldr ;
int gas ;
int tmp;
int celsius ;
int cnt = 0;
int i;

String fire_web;
String light_web;
String temp_web;
String gas_web;


void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  
  lcd.setCursor(0, 0);
  lcd.print("  IOT Based    ");
  lcd.setCursor(0, 1);
  lcd.print("Industrial Autn");

  delay(2000);
  pinMode(motor, OUTPUT);
  pinMode(light, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(fire, INPUT);// put your setup code here, to run once:

 digitalWrite(buzzer, LOW);
 digitalWrite(motor, LOW);
  lcd.setCursor(0, 0);
  lcd.print("WiFi module     ");
  lcd.setCursor(0, 1);
  lcd.print("Initilizing.... ");
   delay(1000);
  wifi.begin(115200);
  wifi.println("AT+RST");
  delay(4000);
  wifi.println("AT+CWMODE=3");
  delay(4000);
  wifi.print("AT+CWJAP=");
  wifi.write('"');
  wifi.print("a");
  wifi.write('"');
  wifi.write(',');
  wifi.write('"');
  wifi.print("1234567890");
  wifi.write('"');
  wifi.println();
  delay(3000);
  lcd.setCursor(0, 0);
  lcd.print("WiFi module     ");
  lcd.setCursor(0, 1);
  lcd.print("Initilized..... ");
  delay(1000);
  lcd.clear();
}





void loop()
{
  lcd.clear();

  fire_data = digitalRead(fire);


  ldr = analogRead(A1);
  ldr = ldr / 2;

  gas = analogRead(A2);
  gas = gas / 2;


  tmp = analogRead(A0);
  
  celsius =  tmp  / 2;
  //celsius=int(celsius);


  lcd.setCursor(0, 0);
  lcd.print("fire:");
  lcd.setCursor(5, 0);
  lcd.print(fire_data);


  //ldr,light
  lcd.setCursor(0, 1);
  lcd.print("LDR:");
  lcd.setCursor(4, 1);
  lcd.print(ldr);
  lcd.setCursor(9, 1);
  lcd.print("Lt:");
  lcd.setCursor(11, 1);
  lcd.print("     ");


  delay(2000);
  lcd.clear();
  //gas,temp
  lcd.setCursor(0, 0);
  lcd.print("GAS:");
  lcd.setCursor(4, 0);
  lcd.print(gas);
  lcd.setCursor(8, 0);
  lcd.print("T:");
  lcd.setCursor(10, 0);
  lcd.print(celsius);


  delay(2000);
  lcd.clear();


  //-------------------------fire------------------------------------
  if  (fire_data == 1) //fire
  {
    digitalWrite(buzzer, HIGH);//ON
    lcd.setCursor(0, 0);
    lcd.print("fire:");
    lcd.setCursor(5, 0);
    lcd.print(fire_data);
    delay(2000);
    fire_web = "1";
    digitalWrite(buzzer, LOW);//off
    lcd.clear();
  }

  else
  {
    digitalWrite(buzzer, LOW);//off
    lcd.setCursor(0, 0);
    lcd.print("fire:");
    lcd.setCursor(5, 0);
    lcd.print(fire_data);
    delay(500);
    fire_web = "0";
    lcd.clear();

  }

  //------------------------------------------temp--------------------
  if ( celsius > 55 ) //on
  {

    buzzer_Sound(2);
    lcd.setCursor(0, 2);
    lcd.print("GAS:");
    lcd.setCursor(4, 2);
    lcd.print(gas);
    lcd.setCursor(8, 2);
    lcd.print("T:");
    lcd.setCursor(10, 2);
    lcd.print(celsius);
    delay(1000);

    temp_web = "1";
    lcd.clear();
  }
  else
  {
    lcd.setCursor(0, 2);
    lcd.print("GAS:");
    lcd.setCursor(4, 2);
    lcd.print(gas);
    lcd.setCursor(8, 2);
    lcd.print("T:");
    lcd.setCursor(10, 2);
    lcd.print(celsius);
    delay(1000);
    temp_web = "0";
    lcd.clear();
  }

  //------------------------------------------gas--------------------
  if ( gas > 100 ) //on
  {
   digitalWrite(motor, HIGH);
    buzzer_Sound(2);
    lcd.setCursor(0, 2);
    lcd.print("GAS:");
    lcd.setCursor(4, 2);
    lcd.print(gas);
    lcd.setCursor(8, 2);
    lcd.print("T:");
    lcd.setCursor(10, 2);
    lcd.print(celsius);
    delay(1000);
   digitalWrite(motor, LOW);
    gas_web = "1";
    lcd.clear();
  }
  else
  {
    lcd.setCursor(0, 2);
    lcd.print("GAS:");
    lcd.setCursor(4, 2);
    lcd.print(gas);
    lcd.setCursor(8, 2);
    lcd.print("T:");
    lcd.setCursor(10, 2);
    lcd.print(celsius);
    delay(1000);
    gas_web = "0";
    lcd.clear();
  }





  //--------------------------------ldr,light---------------------------------------

  if (ldr < 100) //night
  {
    digitalWrite(light, HIGH);//oN
    lcd.setCursor(0, 1);
    lcd.print("LDR:");
    lcd.setCursor(4, 1);
    lcd.print(ldr);
    lcd.setCursor(9, 1);
    lcd.print("Lt:");
    lcd.setCursor(12, 1);
    lcd.print("Nig");

    delay(800);
    lcd.clear();

  }
  else
  {
    digitalWrite(light, LOW);//off
    lcd.setCursor(0, 1);
    lcd.print("LDR:");
    lcd.setCursor(4, 1);
    lcd.print(ldr);
    lcd.setCursor(9, 1);
    lcd.print("Lt:");
    lcd.setCursor(12, 1);
    lcd.print("Mor");

    delay(800);
    lcd.clear();


  }



  sendwifi_Data();

  Serial.println("SENT@");
  lcd.setCursor(15, 2);
  lcd.print("*");
  delay(1000);
  lcd.clear();

}






void sendwifi_Data(){
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "184.106.153.149"; // api.thingspeak.com
  cmd += "\",80";
  wifi.println(cmd);
  delay(1000);

 
  getStr += String(fire_data);
  getStr +="&field2=";
  getStr += String(celsius);
  getStr +="&field3=";
  getStr += String(gas);
  getStr +="&field4=";
  getStr += String(ldr );

  getStr += "\r\n\r\n";

  // send data length
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  wifi.println(cmd);
  delay(1000);
  wifi.println(getStr);
  delay(500);
}


void buzzer_Sound(unsigned char Ntimes)
{
  unsigned char b;
  for (b = 0; b < Ntimes; b++)
  {
    digitalWrite(buzzer, HIGH);
    delay(600);
    digitalWrite(buzzer, LOW);
    delay(300);
  }
}
