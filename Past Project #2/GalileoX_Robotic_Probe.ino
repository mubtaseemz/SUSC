#define SensorPin A2          //pH meter Analog output to Arduino Analog Input 0
#define Offset 0.00         //deviation compensate
#define LED 13
#define samplingInterval 20
#define printInterval 800
#define ArrayLenth  40  //times of collection
#include <LiquidCrystal.h>       
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //Digital pins to which you connect the LCD
const int inPin = 1;  
int pHArray[ArrayLenth];   //Store the average value of the sensor feedback
int pHArrayIndex=0;    
int ledR = 10;
int ledB = 9;
int ledY = 8;

void setup(void)
{
  lcd.begin(16,2);
  pinMode(ledR, OUTPUT);   
  pinMode(ledB, OUTPUT);
  pinMode(ledY, OUTPUT);
  Serial.begin(9600);  
  Serial.println("pH meter experiment!"); //Test the serial monitor
}
void loop(void)
{
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue,voltage;
  int valueTemp = analogRead(inPin); // read the value from the sensor
  lcd.setCursor(0,1);
  float millivolts = (valueTemp / 1024.0) * 5000;
  float farenheit = millivolts / 10;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(farenheit);
  lcd.print("F");
  lcd.setCursor(0,1);
  lcd.print(((farenheit-32)*5) / 9); //turning the farenheit into celsius
  lcd.print("C  ");
  lcd.print("pH:");
  lcd.print(pHValue);
  delay(1000);
 
  if(millis()-samplingTime > samplingInterval)
  {
    pHArray[pHArrayIndex++]=analogRead(SensorPin);
    if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
    voltage = avergearray(pHArray, ArrayLenth)*5.0/1024;
    pHValue = 3.5*voltage+Offset;
    samplingTime=millis();
  }
  if(millis() - printTime > printInterval)   //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
  {
 
      Serial.print("  pH value: ");
  Serial.println(pHValue,2);
      digitalWrite(LED,digitalRead(LED)^1);
      printTime=millis();
  }
  if (pHValue > 8.5) {
  digitalWrite(ledR, HIGH);
  digitalWrite(ledY, LOW);
  digitalWrite(ledB, LOW);
 }  
  if (pHValue < 6.0) {
  digitalWrite(ledY, HIGH);
  digitalWrite(ledR, LOW);
  digitalWrite(ledB, LOW);
 }
  if (pHValue <= 8.5 && pHValue >= 6.0){
  digitalWrite(ledB, HIGH);
  digitalWrite(ledY, LOW);
  digitalWrite(ledR, LOW);
 }
}
double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
  Serial.println("Error number for the array to avraging!/n");
  return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
  for(i=0;i<number;i++){
    amount+=arr[i];
  }
  avg = amount/number;
  return avg;
  }else{
  if(arr[0]<arr[1]){
    min = arr[0];max=arr[1];
  }
  else{
    min=arr[1];max=arr[0];
  }
  for(i=2;i<number;i++){
    if(arr[i]<min){
      amount+=min;      //arr<min
      min=arr[i];
    }else {
      if(arr[i]>max){
        amount+=max;  //arr>max
        max=arr[i];
      }else{
        amount+=arr[i]; //min<=arr<=max
      }
    }//if
  }//for
  avg = (double)amount/(number-2);
  }//if
  return avg;
 
}

