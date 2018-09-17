int sensorValue;
int digitalValue;
void setup()
{

Serial.begin(9600); // sets the serial port to 9600
pinMode(12, OUTPUT); // connects to RED LED
pinMode(11, OUTPUT); // connects to YELLOW LED
pinMode(10, OUTPUT); // connects to GREEN LED
pinMode(9, OUTPUT); // connects to BLUE LED

}


void loop()

{

sensorValue = analogRead(0); // read analog input pin 0
digitalWrite(12, LOW);
digitalWrite(11, LOW);
digitalWrite(10, LOW);
digitalWrite(9, LOW);
//digitalValue = digitalRead(2); 
if (sensorValue>500)
{

digitalWrite(12, HIGH);
}
else if(sensorValue>300)
{


for (int i=0; i<5; i++){
digitalWrite(12, HIGH);
digitalWrite(11, LOW);
delay(10);
digitalWrite(12, LOW);
digitalWrite(11, HIGH);
delay(10);
}}
else if (sensorValue>200)
{

digitalWrite(11, HIGH);
}
else if(sensorValue>150)
{


for (int i=0; i<5; i++){
digitalWrite(10, HIGH);
digitalWrite(11, LOW);
delay(10);
digitalWrite(10, LOW);
digitalWrite(11, HIGH);
delay(10);
}}
else if (sensorValue>100)
{

digitalWrite(10, HIGH);
}
else if(sensorValue>50)
{

for (int i=0; i<5; i++){
digitalWrite(10, HIGH);
digitalWrite(9, LOW);
delay(10);
digitalWrite(10, LOW);
digitalWrite(9, HIGH);
delay(10);
}}
else{
  digitalWrite(9, HIGH);
}
Serial.println(sensorValue, DEC); // prints the value read
//Serial.println(digitalValue, DEC);

delay(200); // wait 100ms for next reading

}

