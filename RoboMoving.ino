#define EN1 3
#define EN2 4
#define EN3 5
#define DIR1 6
#define DIR2 7
#define DIR3 8
#define STEP1 9
#define STEP2 10
#define STEP3 11
        
//ROBO
//			UP_0
//			./#.#\.
//			|1###2|
//	LEFT_90	|#####|	RIGHT_-90
//			\##3##/
//
//			DOWN_180

unsigned long last_pulse_m1;
unsigned long last_pulse_m2;
unsigned long last_pulse_m3;


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

void setup() {
	Serial.begin(9600);
	
	// Last time pulses for all Motors in microseconds
  last_pulse_m1 = micros();
  last_pulse_m2 = micros();
  last_pulse_m3 = micros();
}

void loop() {
	// Periods of Pulses of Motors. 800 === 1 pulse per 800microseconds / 0.8 milliseconds (
	unsigned long period_m1 = 800;	// Motor1 Pulse
	unsigned long period_m2 = 800;	// Motor2 Pulse
	unsigned long period_m3 = 800;	// Motor3 Pulse

	last_pulse_m1 = motor1(1, 0, last_pulse_m1, period_m1);
	last_pulse_m2 = motor2(1, 0, last_pulse_m2, period_m2);
	last_pulse_m3 = motor3(1, 0, last_pulse_m3, period_m3);
}
