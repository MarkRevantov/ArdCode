#define EN1 3
#define EN2 4
#define EN3 5
#define DIR1 6
#define DIR2 7
#define DIR3 8
#define STEP1 9
#define STEP2 10
#define STEP3 11

void motor1(int dir, en, long time_imp) {
  if(micros() > time_imp)
    digitalWrite(EN1, en);
    digitalWrite(DIR1, dir);
    digitalWrite(STEP1, HIGH);
    digitalWrite(STEP1, LOW);

}
void motor2(int dir, en) {
  digitalWrite(EN2, en);
  digitalWrite(STEP2, HIGH);
  digitalWrite(STEP2, LOW);
}
void motor3(int dir, en) {
  digitalWrite(EN3, en);
  digitalWrite(STEP3, HIGH);
  digitalWrite(STEP3, LOW);
}
void turnLeft() {

}

void setup() {
  Serial.begin(9600);

}

void loop() {
 long tim = micros();
 long dt = 800;
  motor1(1,0, tim+dt);
  motor2(1,0, tim+dt);
  motor3(1,0, tim+dt);
  
}
