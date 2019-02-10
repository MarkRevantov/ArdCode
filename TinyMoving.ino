#define EN1 3
#define EN2 4
#define EN3 5
#define DIR1 6
#define DIR2 7
#define DIR3 8
#define STEP1 9
#define STEP2 10
#define STEP3 11

#define TRIG 12
#define ECHO 13

// 32 MicroSteps - 600 periods - 9.85 seconds one Turn
#define FULL_TURN 9850000  // 9'850'000 microseconds = 9.85 seconds
#define IDEAL_PERIOD 600
#define DIST_100_TIME 1223000 // 1.223 Seconds on 100 millimeters motors

//TINYROBO
//          UP_0
//          ./#.#\.
//          |#####|
//  LEFT_90 |1###2| RIGHT_-90
//          -------
//
//          DOWN_180 

unsigned long start_time;
unsigned long last_pulse_mL;
unsigned long last_pulse_mR;

// MOTOR Left
unsigned long motorR(int dir, int en, long last_pulse,  unsigned long  period_pulse) {
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

// MOTOR Right
unsigned long motorR(int dir, int en, unsigned long last_pulse,  unsigned long  period_pulse) {
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

// TURN LEFT On angle
void turn_left(int angle, unsigned long period) {
  int dir = 0;
  if (angle < 0) {
    dir = 1;
  }
  unsigned long long start_turn_time = micros();  
  float dt = float(FULL_TURN)*float(angle)/360.0*float(period)/float(IDEAL_PERIOD);

  while (micros() - start_turn_time < long(dt)) {
    last_pulse_m1 = motorL(1, 0, last_pulse_m1, period);
    last_pulse_m2 = motorR(0, 0, last_pulse_m2, period);
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
    last_pulse_m1 = motorL(0, 0, last_pulse_m1, period);
    last_pulse_m2 = motorR(1, 0, last_pulse_m2, period);
  }
}

// GO FORWARD
void go_forward(int distantion, unsigned long period) {
  int dir = 1;
  unsigned long long start_turn_time = micros();  
  float dt = float(DIST_100_TIME)*distantion/0.866/100.0;

  while (micros() - start_turn_time < long(dt)) {
    last_pulse_m1 = motor1(0, 0, last_pulse_m1, period);
    last_pulse_m2 = motor2(0, 0, last_pulse_m2, period);
  }
}

// GO BACK
void go_back(int distantion, unsigned long period) {
  unsigned long long start_turn_time = micros();  
  float dt = float(DIST_100_TIME)*distantion/0.866/100.0;

  while (micros() - start_turn_time < long(dt)) {
    last_pulse_m1 = motor1(1, 0, last_pulse_m1, period);
    last_pulse_m2 = motor2(1, 0, last_pulse_m2, period);
  }
}


// STOP TORMOZI!!!
void stop(long dt) {
  last_pulse_m1 = motor1(0, 1, last_pulse_m1, 600);
  last_pulse_m2 = motor2(0, 1, last_pulse_m2, 600);
  delayMicroseconds(dt);
}

// Get Distance from rangefinder

long long get_distance() {
  digitalWrite(TRIG, LOW); 
  delayMicroseconds(2); 
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  unsigned long long duration = pulseIn(ECHO, HIGH);
  unsigned long distance = long(float(duration)/5.8);
  return distance;
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
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  start_time = micros();
  // Last time pulses for all Motors in microseconds
  last_pulse_mL = micros();
  last_pulse_mR = micros();
}

void loop() {
  Serial.println(long(get_distance()));
}
