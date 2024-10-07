int IN1 = 5;
int IN2 = 6;
int IN3 = 7;
int IN4 = 8;
int ENA = 9;
int ENB = 10;
#define SERIAL_BAUD 9600
String lastMessage;
// char readBuffer[64];
// char writeBuffer[64];

void setup() {
  for (int i = 5; i < 11; i++) {
    pinMode(i, OUTPUT);
  }
  Serial.begin(SERIAL_BAUD);
}

// Wheel controls =============================
void leftForward() {
  digitalWrite(IN2, LOW);
  digitalWrite(IN1, HIGH);
  analogWrite(ENA, 200);
}

void leftBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 200);
}

void rightForward() {
  digitalWrite(IN4, LOW);
  digitalWrite(IN3, HIGH);
  analogWrite(ENB, 200);
}

void rightBackward() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, 200);
}
// ============================================

// Direction controls =========================
void goForward() {
  stop();
  leftForward();
  rightForward();
}

void goBack() {
  stop();
  leftBackward();
  rightBackward();
}

void goLeft() {
  stop();
  rightForward();
}

void goRight() {
  stop();
  leftForward();
}

void stop() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

// ============================================

/*
Split string by delimiter and get the index
*/
String getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void runTrolley(String direction) {
  if (direction == "forward") {
    goForward();
    Serial.println("going forward");
  } else if (direction == "backward") {
    goBack();
    Serial.println("going backwards");
  } else if (direction == "left") {
    goLeft();
    Serial.println("going left");
  } else if (direction == "right") {
    goRight();
    Serial.println("going right");
  } else if (direction == "stop") {
    stop();
    Serial.println("stopping");
  } else {
    Serial.println("WHYYYYYYY ARE YOU HERREEEE: GO AWAYYYY");
  }
}

void loop() {

  if (Serial.available() > 0) {
    // int availableBytes = Serial.available();
    // for (int i=0; i<availableBytes; i++ ){
    //   readBuffer[i] = Serial.read();
    // }
    // sprintf(readBuffer, Serial.readUntil('\n'));
    String message = Serial.readStringUntil('\n');
    // String value = getValue(message, ' ', 1);
    // // sprintf(writeBuffer, "Received: %s\n", message);
    // runTrolley(value);
    // Serial.println(value);



    // String message = "";  // to store any string messages like "State changed"
    // while (Serial.available() > 0) {
    //   char c = Serial.read();
    //   if (c == '\n')
    //     break;       // Stop reading the message at a newline
    //   message += c;  // Accumulate message characters
    // }

    // 3. Read message
    String command1 = getValue(message, ' ', 0);
    if (command1 == "[DIRECTION]") {
      String direction = getValue(message, ' ', 1);
      lastMessage = direction;
      runTrolley(direction);
    }
  } else {
    runTrolley(lastMessage);
  }
}

// // rotate CW
// digitalWrite(IN1, LOW);
// digitalWrite(IN2, HIGH);
// analogWrite(ENA, 200);
// digitalWrite(IN3, LOW);
// digitalWrite(IN4, HIGH);
// analogWrite(ENB, 200);
// delay(1000);
// // pause for 1S
// analogWrite(ENA, 0);
// analogWrite(ENB, 0);
// delay(1000);
// // rotate CCW
// digitalWrite(IN1, HIGH);
// digitalWrite(IN2, LOW);
// analogWrite(ENA, 100);
// digitalWrite(IN3, HIGH);
// digitalWrite(IN4, LOW);
// analogWrite(ENB, 100);
// delay(1000);
// // pause for 1S
// analogWrite(ENA, 0);
// analogWrite(ENB, 0);
// delay(1000);
// }