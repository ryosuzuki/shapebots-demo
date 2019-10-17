int currentPos = 0;
int targetPos = 0;
int a1 = 5;  // D1
int a2 = 4;  // D2
int buttonUp = 12; // D6
int buttonDown = 13; // D7
int limitSwitch = 0; // D3
int maxLength = 1000;

void setup() {
  pinMode (a1, OUTPUT);
  pinMode (a2, OUTPUT);
  pinMode(buttonUp, INPUT_PULLUP);
  pinMode(buttonDown, INPUT_PULLUP);
  pinMode(limitSwitch, INPUT_PULLUP);
  
  Serial.begin (9600);
  delay(10);
  off();
  initialize();
}

void loop() {
  
  if (digitalRead(limitSwitch) == 0) {
    currentPos = 0;
  }

  if (digitalRead(buttonUp) == 0) {
    if (currentPos >= maxLength) {
      off();
    } else {
      up();
      currentPos = currentPos + 1;
    }
    Serial.println(currentPos);
  } else {
    off();
  }

  if (digitalRead(buttonDown) == 0) {
    if (currentPos <= 0) {
      off();
    } else {
      down();
      currentPos = currentPos - 1;
    }
    Serial.println(currentPos);    
  } else {
    off();
  }

  delay(1);
}

void initialize() {
  while (true) {
    down();
    delay(1);
    if (digitalRead(limitSwitch) == 0) {
      pause();
      delay(100);
      currentPos = 0;
      off();
      break;
    }
  }
}


void off() {
  digitalWrite(a1, LOW);
  digitalWrite(a2, LOW);
}

void up() {
  digitalWrite(a1, LOW);
  digitalWrite(a2, HIGH);
}

void down() {
  digitalWrite(a1, HIGH);
  digitalWrite(a2, LOW);
}

void pause() {
  digitalWrite(a1, HIGH);
  digitalWrite(a2, HIGH);
}
