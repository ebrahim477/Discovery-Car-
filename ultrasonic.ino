#include <LiquidCrystal.h>
#define r A0
#define buzz 13
#define trigPin 8
#define echoPin 9
#include <DHT11.h>
float value =0; 
DHT11 dht11(A1);
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

int pos = 0;  

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
         
      // setup Buzzer
      pinMode(buzz,OUTPUT);

  lcd.begin(20, 4);

  lcd.setCursor(0, 1);
  delay(400);
  lcd.clear();
  delay(1000);
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance < 24) {  // This is where the LED On/Off happens
    

  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Hurdle Detected");
  Serial.println(" Hurdle Detected");
 
  delay(400);
  lcd.clear();
  
  delay(200);
}
 
  lcd.setCursor(1, 0);
  lcd.print("Distance= ");
 
  lcd.print(distance);
  lcd.print("cm");
  
    Serial.print(distance);
    Serial.println(" cm");

  delay(500);
    int temperature = 0;
    int humidity = 0;

    // Attempt to read the temperature and humidity values from the DHT11 sensor.
    int result = dht11.readTemperatureHumidity(temperature, humidity);

    // Check the results of the readings.
    // If the reading is successful, print the temperature and humidity values.
    // If there are errors, print the appropriate error messages.
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
   
         //ldr 
    value=analogRead(r);
    value=(value/1023)*5;
    Serial.println(value);
    delay(100);

if(value>3)
   {
     lcd.setCursor(15,3);
     lcd.print("dark ");
   }
    else
     lcd.setCursor(15,3);
      lcd.print("light");

   





  
}
