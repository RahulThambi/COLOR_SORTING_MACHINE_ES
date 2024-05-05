#include <Arduino_BuiltIn.h>

#include <Servo.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

Servo pickServo;
Servo dropServo;

#define S0 4 
#define S1 13
#define S2 7
#define S3 2
#define sensorOut 8    
const int ledPin = 12; 
const int ldrPin = A0; 
int frequency = 0;
int color=0;
int buzzer=11; //buzz
int a=1;

int detectColor()
 {
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;
  Serial.print("Red = ");
  Serial.print(frequency);//printing RED color frequency
  Serial.print("   ");
  delay(50);
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;
  Serial.print("Blue = ");
  Serial.print(frequency);
  Serial.println("   ");
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;
  Serial.print("Green = ");
  Serial.print(frequency);
  Serial.print("   ");
  delay(50);
  delay(50);
if( R>210 & R<220 & G>248 & G<255 & B<205 & B>195)
  {
    color = 1; 
    Serial.print("Detected Color is = ");
    Serial.println("RED");
  }

  else if(R>210 & R<220 & G<250 & G>235 & B<205 & B>195 )
  {
    color = 2; 
    Serial.print("Detected Color is = ");
    Serial.println("YELLOW");
  }
  else if(R>220 & R<230 & G<260 & G>250 & B<205 & B>195)
  {
    color = 4;
    Serial.println("NOTA");
  }
  else
  {
    color=3;
    Serial.println("PURPLE");

  }


  return color;  
}
void setup() 
{
  lcd.init(); // initialize the lcd
  lcd.backlight();
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  digitalWrite(S0, LOW);
  digitalWrite(S1, HIGH);
  pickServo.attach(10);
  dropServo.attach(9);
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT); //buzz
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT); 
  pinMode(ldrPin, INPUT); 
}

void loop() 
{
//   int ldrStatus = analogRead(ldrPin);
// if (ldrStatus <= 12) 
// {
// digitalWrite(ledPin, HIGH); 
// Serial.print("Darkness over here,turn on the LED :");
// Serial.println(ldrStatus);
// } 
// else
//  {
// digitalWrite(ledPin, LOW); 
// Serial.print("There is sufficient light , turn off the LED : ");
// Serial.println(ldrStatus);
//}
  pickServo.write(115);
  delay(600);
  for(int i = 115; i > 50; i--)
  {
    pickServo.write(i);
    delay(2);
  }
  delay(500);
  color = detectColor();
  delay(1000);  

  switch (color)
  {
    case 1:
      digitalWrite(6,HIGH);
      delay(300);
      lcd.clear();                 // clear display
      lcd.setCursor(0, 0);         // move cursor to   (0, 0)
      lcd.print("Colour is:");        // print message at (0, 0)
      lcd.setCursor(2, 1);         // move cursor to   (2, 1)
      lcd.print("RED"); // print message at (2, 1)
      delay(2000);                 // display the above for two seconds

      digitalWrite(6,LOW);
      dropServo.write(170);
    break;

    case 2:
    
    digitalWrite(3,HIGH);//yellow
    delay(300);
    lcd.clear();                 // clear display
    lcd.setCursor(0, 0);         // move cursor to   (0, 0)
    lcd.print("Colour is:");        // print message at (0, 0)
    lcd.setCursor(2, 1);         // move cursor to   (2, 1)
    lcd.print("YELLOW"); // print message at (2, 1)
    delay(2000);                 // display the above for two seconds
    digitalWrite(3,LOW);
    dropServo.write(180);
    break;

    case 3:
     digitalWrite(5,HIGH);
    delay(300);
      lcd.clear();                 // clear display
      lcd.setCursor(0, 0);         // move cursor to   (0, 0)
      lcd.print("Colour is:");        // print message at (0, 0)
      lcd.setCursor(2, 1);         // move cursor to   (2, 1)
      lcd.print("PURPLE"); // print message at (2, 1)
      delay(2000);                 // display the above for two seconds
    digitalWrite(5,LOW);
    dropServo.write(110);
    break;

    case 4:
    //NOTA
      lcd.clear();                 // clear display
      lcd.setCursor(0, 0);         // move cursor to   (0, 0)
      lcd.print("NOTA");        // print message at (0, 0)
      delay(2000);                 // display the above for two seconds
    delay(300);
    dropServo.write(80);
    tone(buzzer,1000,500);
    delay(500);
    break;

    //     case 5:
    //  digitalWrite(5,HIGH);
    // delay(300);
    //   lcd.clear();                 // clear display
    //   lcd.setCursor(0, 0);         // move cursor to   (0, 0)
    //   lcd.print("Colour is:");        // print message at (0, 0)
    //   lcd.setCursor(2, 1);         // move cursor to   (2, 1)
    //   lcd.print("PURPLE"); // print message at (2, 1)
    //   delay(2000);                 // display the above for two seconds
    // digitalWrite(5,LOW);
    // dropServo.write(110);
    // break;


    case 0:
    break;
  }
  delay(500);
  for(int i = 65; i > 29; i--) 
  {
    pickServo.write(i);
    delay(2);
  } 
  delay(300);
  for(int i = 29; i < 115; i++)
  {
    pickServo.write(i);
    delay(2);
  }
  color=0;
}

