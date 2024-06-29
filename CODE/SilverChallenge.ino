#include<NewPing.h>
#define TRIGGER_PIN 13
#define ECHO_PIN 12
#define MAX_DISTANCE 20
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
const int pin = 4;
int cm, l, r, flag = 0, d = 0;
static int c = 0;
int c1 = c;
unsigned long x = millis();
unsigned long xU = millis();
long interval = 500;
void setup()
{
pinMode(A0, INPUT);
pinMode(A1, INPUT);
for (int i = 5; i <= 8; i++) pinMode(i, OUTPUT);
Serial.begin(9600);
}
void loop()
{
if (Serial.read() == 'a' || flag == 1) flag = 1;
if (flag == 1) run_buggy();
if (flag == -1) stop_buggy();
}
void run_buggy()
{
receiver();
l = digitalRead(A0);
r = digitalRead(A1);
if (l == 1 && r == 1) forward();
if (l == 0 && r == 1) left();
if (l == 1 && r == 0) right();
if (l == 0 && r == 0) {
unsigned long y = millis();
if ((y - x) > interval) {
c++;
x = millis();
}
if (c1 != c) {
c1 = c;
Serial.print("Group 6: Count = "); Serial.println(c);
}
switch (c) {
case 1:
{
forward(); break;
}
case 3:
{
right(); delay(150); break;
}
//case 5:
//{
//right(); delay(200); break;
//}
case 6:
{
stop_buggy();
Serial.println("Group 6: Buggy Parked!");
flag = -1; break;
}
default: forward();
}
}
unsigned long yU = millis();
if ((yU - xU) > interval) {
xU = yU;
ultrasonic();
}
}
void ultrasonic()
{
delay(50);
cm = sonar.ping_cm();
Serial.print("Group 6: Distance = "); Serial.print(cm);
Serial.println(" cm");
if ((cm > 0) && (cm < 20)) { stop_buggy(); delay(2000); }
}
void receiver()
{
if (digitalRead(pin) == HIGH) {
d = pulseIn(pin, HIGH);
if (d > 1500 && d < 2000) {
Serial.println("Group 6: Gantry 1 Crossed");
Serial.print("Group 6: Ping: d = "); Serial.println(d);
stop_buggy(); 
delay(1000);
}
if (d > 2500 && d < 3000) {
Serial.println("Group 6: Gantry 2 Crossed");
Serial.print("Group 6: Ping: d = "); Serial.println(d);
stop_buggy(); delay(1000);
}
if (d > 500 && d < 1000) {
Serial.println("Group 6: Gantry 3 Crossed");
Serial.print("Group 6: Ping: d = "); Serial.println(d);
stop_buggy(); delay(1000);
}
if (d > 3500 && d < 4000) {
Serial.println("Group 6: Gantry 3 Crossed");
Serial.print("Group 6: Ping: d = "); Serial.println(d);
stop_buggy(); delay(1000);
}
}
}
void stop_buggy()
{
digitalWrite(5, LOW);
digitalWrite(6, LOW);
digitalWrite(7, LOW);
digitalWrite(8, LOW);
}
void forward()
{
digitalWrite(5, HIGH);
digitalWrite(6, LOW);
digitalWrite(7, LOW);
digitalWrite(8, HIGH);
}
void right()
{
digitalWrite(5, HIGH);
digitalWrite(6, LOW);
digitalWrite(7, LOW);
digitalWrite(8, LOW);
}
void left()
{
digitalWrite(5, LOW);
digitalWrite(6, LOW);
digitalWrite(7, LOW);
digitalWrite(8, HIGH);
}
