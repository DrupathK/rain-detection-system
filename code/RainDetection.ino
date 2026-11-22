
#define GREEN_LED 25
#define RED_LED 26
#define WATER_SENSOR 34
#define BUZZER 27

int previousStatus = -1;

unsigned long previousBeepTime = 0;
bool buzzerState = false;

void setup() {
  Serial.begin(115200);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(WATER_SENSOR, INPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  noTone(BUZZER);

  Serial.println("Rain Detection System Started");
}

void loop() {
  int waterStatus = digitalRead(WATER_SENSOR);

  if (waterStatus == LOW) {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);

    if (millis() - previousBeepTime >= 300) {
      previousBeepTime = millis();
      buzzerState = !buzzerState;

      if (buzzerState) {
        tone(BUZZER, 2000);
      } else {
        noTone(BUZZER);
      }
    }

    if (previousStatus != LOW) {
      Serial.println("WARNING: RAIN DETECTED!");
    }
  }
  else {
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    noTone(BUZZER);

    buzzerState = false;

    if (previousStatus != HIGH) {
      Serial.println("STATUS: NORMAL");
    }
  }

  previousStatus = waterStatus;
  delay(20);
}
