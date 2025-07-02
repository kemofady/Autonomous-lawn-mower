#include <SoftwareSerial.h>

// #define BT_RX_PIN 0
// #define BT_TX_PIN 1
// SoftwareSerial bluetoothSerial(BT_RX_PIN, BT_TX_PIN);

#define RIGHT_DIR_PIN1 10
#define RIGHT_DIR_PIN2 12
#define RIGHT_PWM_PIN 11

#define LEFT_DIR_PIN1 8
#define LEFT_DIR_PIN2 7
#define LEFT_PWM_PIN 9

#define FRONT_LED_PIN 5
#define RIGHT_LED_PIN 3
#define LEFT_LED_PIN 2
#define BACK_LED_PIN 4

#define CUTTER_MOTOR_PIN 6
#define SERIAL_TEST_PIN 7
#define SW A7
#define LDR_PIN A0

int i, j;

enum MotorState {
  IDLE,
  STOPPING_PWM,
  OPENING_RELAYS,
  CLOSING_RELAYS,
  APPLYING_SPEED
};

MotorState motorState = IDLE;
unsigned long motorStateStartTime = 0;

int left_pwm = 0;
int right_pwm = 0;
int targetLeft = 0;
int targetRight = 0;
bool needRelayChange = false;

int prevLeftDir = 0;
int prevRightDir = 0;

String inputString = "";
bool stringComplete = false;
bool cutterRunning = false;

void setup() {
  Serial.begin(9600);
  // bluetoothSerial.begin(9600);

  pinMode(RIGHT_DIR_PIN1, OUTPUT);
  pinMode(RIGHT_DIR_PIN2, OUTPUT);
  pinMode(RIGHT_PWM_PIN, OUTPUT);
  pinMode(LEFT_DIR_PIN1, OUTPUT);
  pinMode(LEFT_DIR_PIN2, OUTPUT);
  pinMode(LEFT_PWM_PIN, OUTPUT);

  pinMode(FRONT_LED_PIN, OUTPUT);
  pinMode(RIGHT_LED_PIN, OUTPUT);
  pinMode(LEFT_LED_PIN, OUTPUT);
  pinMode(BACK_LED_PIN, OUTPUT);
  pinMode(SW, INPUT);
  pinMode(CUTTER_MOTOR_PIN, OUTPUT);
  pinMode(SERIAL_TEST_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT);

  for (i = 1; i <= 255; i++) {
    analogWrite(FRONT_LED_PIN, i);
    delay(1);
  }
  for (i = 255; i >= 0; i--) {
    analogWrite(FRONT_LED_PIN, i);
    delay(1);
  }
}

void loop() {
  digitalWrite(LEFT_LED_PIN, HIGH);

  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      stringComplete = true;
    } else {
      inputString += inChar;
    }
  }

  digitalWrite(RIGHT_LED_PIN, HIGH);

  if (stringComplete) {
    parseCommand(inputString);
    inputString = "";
    stringComplete = false;
  }

  updateMotorState();
  updateSensorsAndLEDs();
}

void parseCommand(String cmd) {
  int lIndex = cmd.indexOf('L');
  int rIndex = cmd.indexOf('R');
  if (lIndex == -1 || rIndex == -1 || rIndex < lIndex) return;

  float leftVal = cmd.substring(lIndex + 1, rIndex).toFloat();
  float rightVal = cmd.substring(rIndex + 1).toFloat();
  
  Serial.print("Parsed Left: "); Serial.println(leftVal);
  Serial.print("Parsed Right: "); Serial.println(rightVal);

  int newLeftPWM = constrain(abs(leftVal) * 255 / 5.0, 0, 255);
  int newRightPWM = constrain(abs(rightVal) * 255 / 5.0, 0, 255);
  int newLeftDir = (leftVal > 0) ? 1 : (leftVal < 0) ? -1 : 0;
  int newRightDir = (rightVal > 0) ? 1 : (rightVal < 0) ? -1 : 0;

  if (newLeftPWM != left_pwm || newRightPWM != right_pwm ||
      newLeftDir != prevLeftDir || newRightDir != prevRightDir) {

    targetLeft = newLeftPWM * newLeftDir;
    targetRight = newRightPWM * newRightDir;
    needRelayChange = (newLeftDir != prevLeftDir) || (newRightDir != prevRightDir);
    Serial.print("targetLeft: ");
    Serial.println(targetLeft);
    Serial.print("targetRight: ");
    Serial.println(targetRight);

    if (newLeftPWM == 0 && newRightPWM == 0) motorState = STOPPING_PWM;
    else if (needRelayChange) motorState = STOPPING_PWM;
    else motorState = APPLYING_SPEED;

    prevLeftDir = newLeftDir;
    prevRightDir = newRightDir;
    motorStateStartTime = millis();
  }
}

void updateMotorState() {
  unsigned long currentTime = millis();
  unsigned long elapsed = currentTime - motorStateStartTime;

  switch (motorState) {
    case STOPPING_PWM:
      analogWrite(LEFT_PWM_PIN, 0);
      analogWrite(RIGHT_PWM_PIN, 0);
      motorState = needRelayChange ? OPENING_RELAYS : APPLYING_SPEED;
      motorStateStartTime = currentTime;
      break;

    case OPENING_RELAYS:
      digitalWrite(LEFT_DIR_PIN1, LOW);
      digitalWrite(LEFT_DIR_PIN2, LOW);
      digitalWrite(RIGHT_DIR_PIN1, LOW);
      digitalWrite(RIGHT_DIR_PIN2, LOW);
      motorState = CLOSING_RELAYS;
      motorStateStartTime = currentTime;
      break;

    case CLOSING_RELAYS:
      if (elapsed >= 100) {
        if (targetLeft > 0) {
          digitalWrite(LEFT_DIR_PIN1, HIGH);
          digitalWrite(LEFT_DIR_PIN2, LOW);
        } else if (targetLeft < 0) {
          digitalWrite(LEFT_DIR_PIN1, LOW);
          digitalWrite(LEFT_DIR_PIN2, HIGH);
        }

        if (targetRight > 0) {
          digitalWrite(RIGHT_DIR_PIN1, HIGH);
          digitalWrite(RIGHT_DIR_PIN2, LOW);
        } else if (targetRight < 0) {
          digitalWrite(RIGHT_DIR_PIN1, LOW);
          digitalWrite(RIGHT_DIR_PIN2, HIGH);
        }

        motorState = APPLYING_SPEED;
        motorStateStartTime = currentTime;
      }
      break;

    case APPLYING_SPEED:
      Serial.print("APPLYING SPEED -> Left: ");
      Serial.print(abs(targetLeft));
      Serial.print(" | Right: ");
      Serial.println(abs(targetRight));
      analogWrite(LEFT_PWM_PIN, abs(targetLeft));
      analogWrite(RIGHT_PWM_PIN, abs(targetRight));
      left_pwm = abs(targetLeft);
      right_pwm = abs(targetRight);
      motorState = IDLE;
      break;

    case IDLE:
    default:
      break;
  }
}

void updateSensorsAndLEDs() {
  if (targetLeft > 20 && targetRight > 20 && digitalRead(FRONT_LED_PIN) == LOW) {
    for (i = 1; i <= 255; i++) {
      analogWrite(FRONT_LED_PIN, i);
      delay(1);
    }
  } else if (targetLeft > 20 && targetRight > 20) {
    digitalWrite(FRONT_LED_PIN, HIGH);
    analogWrite(CUTTER_MOTOR_PIN, 150);
  } else { 
    digitalWrite(FRONT_LED_PIN, LOW);
  }
}
