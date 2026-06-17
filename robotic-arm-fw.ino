#define LED_PIN 29
#define NUM_LEDS 150
#include <FlexCAN_T4.h>
#include <Servo.h>
#include <FastLED.h>
const int SERVO_PIN = 28;    // PWM pin for servo
const int OPEN_ANGLE = 53;   // fully open
const int CLOSE_ANGLE = 20;  // fully closed
const int trigPin = 25;
const int echoPin = 24;


FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can;
Servo gripperServo;
CRGB leds[NUM_LEDS];

long last;
int activeMotors[6];
int seqOn = 0;
void setup() {
  Serial.begin(115200);  // Start Serial communication
  pinMode(LED_PIN, OUTPUT);
  can.begin();
  can.setBaudRate(500000);
  can.setMaxMB(16);
  can.enableFIFO();
  can.enableFIFOInterrupt();
  can.onReceive(printReceivedMessage);

  gripperServo.attach(SERVO_PIN);
  gripperServo.write(OPEN_ANGLE);  // start closed
  //Serial.println("grip grip");
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  last = millis();
  //Serial.println(last);
  for (int i = 0; i < 6; i++) {
    activeMotors[i] = 0;
  }
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(10);
  setLEDs(CRGB::Green);
}

void loop() {

  can.events();

  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');  // Read until newline
    input.trim();                                 // Remove leading/trailing whitespace

    if (input.length() > 0) {
      processCommand(input);
    //processCommand(input);
  }
}

void processCommand(String input) {
  int ID = (input.substring(0, 2)).toInt();
  int len = input.length();
  String dataStr = input.substring(2, len);

  uint8_t data[8] = { 0 };
  int dataLen = min(dataStr.length() / 2 + dataStr.length() % 2, 8);  // Max 8 bytes, handling odd number of digits
  // parse CAN message from serial input
  for (int i = 0; i < dataLen; i++) {
    int startPos = i * 2;
    String byteStr;

    if (startPos + 1 < dataStr.length()) {
      byteStr = dataStr.substring(startPos, startPos + 2);
    } else if (startPos < dataStr.length()) {
      // Handle odd number of digits by padding with 0
      byteStr = "0" + dataStr.substring(startPos, startPos + 1);
    } else {
      break;
    }

    data[i] = strtoul(byteStr.c_str(), NULL, 16);  // data array for message
  }

  if (ID >= 0x0 && ID <= 0x06) { // if CAN ID is robot motor control 
    if (data[0] == 0xF6) {
      if (data[2] > 0x00) { // 
        if (!activeMotors[ID - 1])  // if motor is off
        {
          activeMotors[ID - 1] = 1; // set motor active
        }
      } else if (data[2] == 0x00) {
        if (activeMotors[ID - 1])  // if motor is on
        {
          activeMotors[ID - 1] = 0; // turn motor off
        }
      }
    }
    int sumMotors = 0;
    for (int i = 0; i < 6; i++) {
      sumMotors += activeMotors[i];
    }
    if (sumMotors > 0 && !seqOn) {
      setLEDs(CRGB::Red);
    } else if (sumMotors == 0 && !seqOn) {
      setLEDs(CRGB::Green);
    }
    // write message to CAN bus
    CAN_message_t msg;
    msg.id = ID;
    msg.len = dataLen;
    memcpy(msg.buf, data, dataLen);
    can.write(msg);
  }
  else if (ID == 0x7) {  // listen for gripper Control Messages
    if (data[0] == 0xFF) {
      // open
      gripperServo.write(OPEN_ANGLE);
      Serial.println("Gripper open");
    } else if (data[0] == 0x00) {
      //close
      gripperServo.write(CLOSE_ANGLE);
      Serial.println("Gripper closed");
    } else {
      // ignore
    }
  } else if (ID == 0x8) { // LED CONTROL
    if (data[0] == 0xFF) {
      // LEDS RED
      setLEDs(CRGB::Red);
      uint8_t response[] = { 0, 1, 0 };
      Serial.print("Response: ");
      Serial.print(ID);
      Serial.print(" ");
      printHexData(response, 3);
      Serial.println();
      seqOn = 1;
    } else if (data[0] == 0x00) {
      // LEDS GREEN
      setLEDs(CRGB::Green);
      uint8_t response[] = { 0, 1, 0 };
      Serial.print("Response: ");
      Serial.print(ID);
      Serial.print(" ");
      printHexData(response, 3);
      Serial.println();
      seqOn = 0;
    }
  } else if (ID == 0x09) {
    if (data[0] == 0x00) {
      readUltraSensor();
    }
  } else {
    // Keep track of active motors for LED functionality
    if (data[0] == 0xF6) {
      if (data[2] > 0x00) {
        if (!activeMotors[ID - 1])  // if motor is off
        {
          activeMotors[ID - 1] = 1;
        }
      } else if (data[2] == 0x00) {
        if (activeMotors[ID - 1])  // if motor is on
        {
          activeMotors[ID - 1] = 0;
        }
      }
    }
    int sumMotors = 0;
    for (int i = 0; i < 6; i++) {
      sumMotors += activeMotors[i];
    }
    if (sumMotors > 0 && !seqOn) {
      setLEDs(CRGB::Red);
    } else if (sumMotors == 0 && !seqOn) {
      setLEDs(CRGB::Green);
    }
    // send message to CAN bus
    CAN_message_t msg;
    msg.id = ID;
    msg.len = dataLen;
    memcpy(msg.buf, data, dataLen);
    can.write(msg);
  }
}


void printReceivedMessage(const CAN_message_t& msg) {
  Serial.print("Response: ");
  Serial.print(msg.id);
  Serial.print(" ");
  printHexData(msg.buf, msg.len);
  Serial.println();
}

void printHexData(const uint8_t* buf, uint8_t len) {
  for (int i = 0; i < len; i++) {
    if (buf[i] < 0x10) {
      Serial.print("0");
    }
    Serial.print(buf[i], HEX);
    Serial.print(" ");
  }
}
void printSentMessage(const char* controller, const CAN_message_t& msg) {
  Serial.print("Sent via ");
  Serial.print(controller);
  Serial.print(" - ID: 0x");
  Serial.print(msg.id, HEX);
  Serial.print(", Data[");
  Serial.print(msg.len);
  Serial.print("]: ");
  printHexData(msg.buf, msg.len);
  Serial.println();
}
void readUltraSensor() {
  long duration;
  float distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send 10us pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo time
  duration = pulseIn(echoPin, HIGH, 30000);  // timeout in 30ms

  // Calculate distance in cm
  distance = duration * 0.0343 / 2.0;

  // Print distance
  if (duration == 0) {
    //Serial.println("No echo received (out of range or sensor error)");
  } else {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }
}
void setLEDs(CRGB color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = color;
  }
  FastLED.show();
  delay(10);
}
