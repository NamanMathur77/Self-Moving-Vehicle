#include<AFMotor.h>
#include<NewPing.h>
#define TRIGGER_PIN 2
#define ECHO_PIN A4
#define MAX_DISTANCE 400
#define led_pin A2
#define ledbacklight A1
AF_DCMotor motor2(2);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
void setup() {
  Serial.begin(9600);
  motor2.setSpeed(200);
  motor2.run(RELEASE);
  pinMode(led_pin, OUTPUT);
  pinMode(ledbacklight, OUTPUT);

}

void loop() {
  int distance;
  distance=sonar.ping_cm();
  Serial.print("initial distance=");
  Serial.print(distance);
  Serial.println();
  if(distance<20 && distance!=0)
  {
    stopit();
    delay(1000);
    digitalWrite(ledbacklight, HIGH);
    for(int i=0; i<=4; i++){
      digitalWrite(led_pin, HIGH);
      delay(500);
      digitalWrite(led_pin, LOW);
      delay(500);
    }
    stopit();
    delay(1000);
    Serial.print("stopping new distance");
    distance=sonar.ping_cm();
    Serial.print(distance);
    Serial.println();
    if(distance<20 && distance!=0)
    {
      digitalWrite(ledbacklight, LOW);
      Serial.println("Moving Backward");
      movebackward();
      delay(500);
      distance=sonar.ping_cm();
      Serial.println("New distance after backward=");
      Serial.print(distance);
      if(distance>20 && distance!=0 && distance<40){
        Serial.println("moving forward");
        moveforward();
        delay(100);
      }
    }
  }
  else
  {
    digitalWrite(led_pin, HIGH);
    digitalWrite(ledbacklight, HIGH);
    delay(200);
    digitalWrite(ledbacklight, LOW);
    delay(200);
    Serial.println("continue moving forward");
    moveforward();
    delay(200);
    
  }

}
void moveforward()
{
  motor2.run(FORWARD);
  for(int i=0; i<200; i++)
  {
    motor2.setSpeed(i);
    delay(10);
  }
}
void stopit()
{
  motor2.run(RELEASE);
}
void movebackward()
{
  motor2.run(BACKWARD);
  for(int i=0; i<200; i++)
  {
    motor2.setSpeed(i);
    delay(10);
  }
}

