int forward = 12; // D6
int backward = 5; // D1
int left  = 14; // D5
int right = 4; // D2

int extend = 13; // D7 
int retract = 2; // D4

void setup() {
  pinMode(forward, INPUT_PULLUP);
  pinMode(backward, INPUT_PULLUP);
  pinMode(left, INPUT_PULLUP);  
  pinMode(right, INPUT_PULLUP);

  pinMode(extend, INPUT_PULLUP);
  pinMode(retract, INPUT_PULLUP);

  Serial.begin(9600);
  delay(10);
}

void loop() {
  char b[6];
  b[0] = (digitalRead(forward)) ? '1' : '0';
  b[1] = (digitalRead(backward)) ? '1' : '0';
  b[2] = (digitalRead(left)) ? '1' : '0';
  b[3] = (digitalRead(right)) ? '1' : '0';
  b[4] = (digitalRead(extend)) ? '1' : '0';
  b[5] = (digitalRead(retract)) ? '1' : '0';
  Serial.println(b);
}
