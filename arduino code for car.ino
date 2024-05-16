//Discovery Robot Car
//Project by:
// "BYTE BUSTERS" :
//    -Ebrahim abdalla abdelghany
//    -mohamed erfan
//    -Waleed 3adel
//    -Nema Ahmed Abdelfatah
//    -Nada mahmoud hedaya


#include <AFMotor.h>  
#include <NewPing.h>
#include <Servo.h>
Servo myServo;
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DHT11.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
#define TRIG_PIN A3
#define ECHO_PIN A2 
#define MAX_DISTANCE 200 
#define MAX_SPEED 190 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 20
#define buzz 13
#define r A0
float value =0; 
DHT11 dht11(2);

AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);


boolean goesForward=false;
unsigned long distance = 100;
unsigned long speedSet = 0;
Servo myservo; 
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
void setup() {

  
// setup Buzzer
pinMode(buzz,OUTPUT);

  
 // lcd setup

 
  Serial.begin(9600);
  lcd.init();      
  lcd.init();
  lcd.backlight();
  lcd.print("Hello, world!");
  lcd.clear();
  myservo.attach(10);  
  myservo.write(115); 
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() {



  //Temperature and Humidity

    int temperature = 0;
    int humidity = 0;
    int result = dht11.readTemperatureHumidity(temperature, humidity);
    if (result == 0) {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.print(" °C\tHumidity: ");
        Serial.print(humidity);
        Serial.println(" %");



        lcd.setCursor(0,1);
        lcd.print("T: ");
        lcd.setCursor(2,1);
        lcd.print(temperature);
        lcd.print("C");
        lcd.setCursor(10,1);
        lcd.println("H:");
        lcd.setCursor(12,1);
        lcd.print(humidity);
        lcd.setCursor(14,1);
        lcd.println("%");
    } else {
        // Print error message based on the error code.
        Serial.println(DHT11::getErrorString(result));
    }

        //distance
          lcd.setCursor(0,0);
        lcd.println("d:");
         lcd.setCursor(3,0);
        lcd.println(distance);



    //Buzzer

    if(distance<=10)
    {
      digitalWrite(buzz,HIGH);
    }
    else
      digitalWrite(buzz,LOW);







    //ldr 
    value=analogRead(r);
    value=(value/1023)*5;
    Serial.println(value);
    delay(100);



    if(value>3)
    {
      lcd.setCursor(11,0);
      lcd.print("dark ");
    }
    else
      lcd.setCursor(11,0);
      lcd.print("light");





 int distanceR = 0;
 int distanceL =  0;
 delay(40);
 
 if(distance<=50)
 {
  moveStop();
  delay(100);
  moveBackward();
  delay(300);
  moveStop();
  delay(200);
  distanceR = lookRight();
  delay(200);
  distanceL = lookLeft();
  delay(200);

  if(distanceR>=distanceL)
  {
    turnRight();
    moveStop();
  }else
  {
    turnLeft();
    moveStop();
  }
 }else
 {
  moveForward();
 }
 distance = readPing();
}

int lookRight()
{
    myservo.write(50); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
}

int lookLeft()
{
    myservo.write(170); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
    delay(100);
}

int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  } 
  
void moveForward() {

 if(!goesForward)
  {
    goesForward=true;
    motor1.run(FORWARD);      
    motor2.run(FORWARD);
    motor3.run(FORWARD); 
    motor4.run(FORWARD);     
   for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
   {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
   }
  }
}

void moveBackward() {
    goesForward=false;
    motor1.run(BACKWARD);      
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);  
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
  }
}  

void turnRight() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);     
  delay(500);
  motor1.run(FORWARD);      
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);      
} 
 
void turnLeft() {
  motor1.run(BACKWARD);     
  motor2.run(BACKWARD);  
  motor3.run(FORWARD);
  motor4.run(FORWARD);   
  delay(500);
  motor1.run(FORWARD);     
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}  
