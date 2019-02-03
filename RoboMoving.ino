#define EN1 3
#define EN2 4
#define EN3 5
#define DIR1 6
#define DIR2 7
#define DIR3 8
#define STEP1 9
#define STEP2 10
#define STEP3 11

// 32 MicroSteps - 600 periods - 9.85 seconds one Turn
#define FULL_TURN 9850000  // 9'850'000 microseconds = 9.85 seconds
#define IDEAL_PERIOD 600
#define DIST_100_TIME 1223000 // 1.223 Seconds on 100 millimeters motors

//ROBO
//      UP_0
//      ./#.#\.
//      |1###2|
//  LEFT_90 |#####| RIGHT_-90
//      \##3##/
//
//      DOWN_180 

unsigned long start_time;
unsigned long last_pulse_m1;
unsigned long last_pulse_m2;
unsigned long last_pulse_m3;

// MOTOR1
unsigned long motor1(int dir, int en, long last_pulse,  unsigned long  period_pulse) {
  if (micros() - last_pulse >= period_pulse) {
    digitalWrite(EN1, en);
    digitalWrite(DIR1, dir);
    digitalWrite(STEP1, HIGH);
    digitalWrite(STEP1, LOW);
    // New Last Pulse
    last_pulse = micros();
    return last_pulse;
  } else {
    // There are no Changes
    return last_pulse;
  }
}
// MOTOR2
unsigned long motor2(int dir, int en, unsigned long last_pulse,  unsigned long  period_pulse) {
  if (micros() - last_pulse >= period_pulse) {
    digitalWrite(EN2, en);
    digitalWrite(DIR2, dir);
    digitalWrite(STEP2, HIGH);
    digitalWrite(STEP2, LOW);
    // New Last Pulse
    last_pulse = micros();
    return last_pulse;
  } else {
    // There are no Changes
    return last_pulse;
  }
}
// MOTOR3
unsigned long motor3(int dir, int en, unsigned long last_pulse,  unsigned long  period_pulse) {
  if (micros() - last_pulse >= period_pulse) {
    digitalWrite(EN3, en);
    digitalWrite(DIR3, dir);
    digitalWrite(STEP3, HIGH);
    digitalWrite(STEP3, LOW);
    // New Last Pulse
    last_pulse = micros();
    return last_pulse; 
  } else {
    // There are no Changes
    return last_pulse;
  }
}
// TURN LEFT On angle
void turn_left(int angle, unsigned long period) {
  int dir = 0;
  if (angle < 0) {
    dir = 1;
  }
  unsigned long long start_turn_time = micros();  
  float dt = float(FULL_TURN)*float(angle)/360.0*float(period)/float(IDEAL_PERIOD);

  while (micros() - start_turn_time < long(dt)) {
    last_pulse_m1 = motor1(dir, 0, last_pulse_m1, period);
    last_pulse_m2 = motor2(dir, 0, last_pulse_m2, period);
    last_pulse_m3 = motor3(dir, 0, last_pulse_m3, period);
  }
}
// TURN RIGHT On angle
void turn_right(int angle, unsigned long period) {
  int dir = 1;
  if (angle < 0) {
    dir = 0;
  }
  unsigned long long start_turn_time = micros();  
  float dt = float(FULL_TURN)*float(angle)/360.0*float(period)/float(IDEAL_PERIOD);

  while (micros() - start_turn_time < long(dt)) {
    last_pulse_m1 = motor1(dir, 0, last_pulse_m1, period);
    last_pulse_m2 = motor2(dir, 0, last_pulse_m2, period);
    last_pulse_m3 = motor3(dir, 0, last_pulse_m3, period);
  }
}
// GO FORWARD
void go_forward(int distantion, unsigned long period) {
  int dir = 1;
  unsigned long long start_turn_time = micros();  
  float dt = float(DIST_100_TIME)*distantion/0.866/100.0;

  while (micros() - start_turn_time < long(dt)) {
    last_pulse_m1 = motor1(1, 0, last_pulse_m1, period);
    last_pulse_m2 = motor2(0, 0, last_pulse_m2, period);
    last_pulse_m3 = motor3(dir, 1, last_pulse_m3, 0);
  }
}
// GO BACK
void go_back(int distantion, unsigned long period) {
  unsigned long long start_turn_time = micros();  
  float dt = float(DIST_100_TIME)*distantion/0.866/100.0;

  while (micros() - start_turn_time < long(dt)) {
    last_pulse_m1 = motor1(0, 0, last_pulse_m1, period);
    last_pulse_m2 = motor2(1, 0, last_pulse_m2, period);
    last_pulse_m3 = motor3(dir, 1, last_pulse_m3, 0);
  }
}
// GO LEFT
void go_left(int distantion, unsigned long period) {
  unsigned long long start_turn_time = micros();  
  float dt = float(DIST_100_TIME)*distantion/100.0;

  while (micros() - start_turn_time < long(dt)) {
    last_pulse_m1 = motor1(0, 0, last_pulse_m1, period*2);
    last_pulse_m2 = motor2(0, 0, last_pulse_m2, period*2);
    last_pulse_m3 = motor3(1, 1, last_pulse_m3, period);
  }
}
// GO RIGHT
void go_right(int distantion, unsigned long period) {
  unsigned long long start_turn_time = micros();  
  float dt = float(DIST_100_TIME)*distantion/100.0;

  while (micros() - start_turn_time < long(dt)) {
    last_pulse_m1 = motor1(1, 0, last_pulse_m1, period*2);
    last_pulse_m2 = motor2(1, 0, last_pulse_m2, period*2);
    last_pulse_m3 = motor3(0, 1, last_pulse_m3, period);
  }
}
void setup() {
  Serial.begin(9600);

  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(EN3, OUTPUT);
  pinMode(STEP1, OUTPUT);
  pinMode(STEP2, OUTPUT);
  pinMode(STEP3, OUTPUT);
  pinMode(DIR1, OUTPUT);
  pinMode(DIR2, OUTPUT);
  pinMode(DIR3, OUTPUT);

  start_time = micros();
  // Last time pulses for all Motors in microseconds
  last_pulse_m1 = micros();
  last_pulse_m2 = micros();
  last_pulse_m3 = micros();
}

void loop() {
  unsigned long period = 600;
  go_forward(300, period);
  go_right(300, period);
  go_back(300, period);
  go_left(300, period);
}
