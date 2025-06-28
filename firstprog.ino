#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

// ------------------- PIN DEFINITIONS -------------------
#define SS_PIN         10
#define RST_PIN        9
#define SERVO_PIN      5
#define IR_SENSOR_PIN  8
#define TRIG_PIN       7
#define ECHO_PIN       6
#define GREEN_LED      2
#define RED_LED        3
#define BLUE_LED       4

// ------------------- CONFIGURABLE CONSTANTS -------------------
#define GATE_OPEN_TIME     3000   // Gate open duration in ms
#define DETECTION_DISTANCE 15     // cm, for ultrasonic sensor

MFRC522 rfid(SS_PIN, RST_PIN);
Servo gateServo;

String validTags[] = {
  // ADD YOUR VALID RFID TAGS HERE for example
  "F9 AA 43 02",
  "63 BA B5 31",
};

void setup() {
  Serial.begin(9600);
  while (!Serial);

  SPI.begin();
  rfid.PCD_Init();

  byte v = rfid.PCD_ReadRegister(rfid.VersionReg);
  if (v == 0x00 || v == 0xFF) {
    Serial.println("WARNING: RFID reader not detected!");
  } else {
    Serial.print("RFID Reader Version: 0x");
    Serial.println(v, HEX);
  }

  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  digitalWrite(BLUE_LED, HIGH); // Standby mode ON

  gateServo.attach(SERVO_PIN);
  gateServo.write(0); // Gate closed

  Serial.println("RFID FASTag System Initialized...");
}

void loop() {
  if (digitalRead(IR_SENSOR_PIN) == HIGH) {
    Serial.println("Vehicle detected! Waiting for FASTag...");
    int distance = measureDistance();

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance <= DETECTION_DISTANCE) {
      readRFID();
    }
  }

  delay(200); // Polling delay
}

// ------------------- FUNCTION DEFINITIONS -------------------

int measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2;
  return distance;
}

void readRFID() {
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  String uidStr = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10) uidStr += "0";
    uidStr += String(rfid.uid.uidByte[i], HEX);
    if (i < rfid.uid.size - 1) uidStr += " ";
  }
  uidStr.toUpperCase();

  Serial.print("RFID UID: ");
  Serial.println(uidStr);

  bool valid = false;
  for (int i = 0; i < sizeof(validTags) / sizeof(validTags[0]); i++) {
    if (uidStr == validTags[i]) {
      valid = true;
      break;
    }
  }

  if (valid) {
    grantAccess();
  } else {
    denyAccess();
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

void grantAccess() {
  Serial.println("Access Granted. Opening Gate...");
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);

  openGate();
  delay(GATE_OPEN_TIME);
  closeGate();

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, HIGH);
  Serial.println("Gate Closed.");
}

void denyAccess() {
  Serial.println("Access Denied.");
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(RED_LED, HIGH);
  delay(2000);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BLUE_LED, HIGH);
}

void openGate() {
  gateServo.write(90);
}

void closeGate() {
  gateServo.write(0);
}

