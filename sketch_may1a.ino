int segmentPins[] = {14, 15, 16, 17, 21, 19, 20};

int digits[10][7] = {
  {LOW, LOW, LOW, LOW, LOW, LOW, LOW},  
  {LOW, LOW, HIGH, LOW, LOW, HIGH, LOW},     
  {LOW, HIGH, HIGH, HIGH, HIGH, LOW, HIGH},  
  {LOW, LOW, LOW, HIGH, LOW, LOW, LOW},  
  {LOW, LOW, HIGH, HIGH, HIGH, HIGH, HIGH},   
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH},  
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH},  
  {HIGH, HIGH, HIGH, LOW, LOW, HIGH, LOW},    
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH},
  {HIGH, HIGH, HIGH, HIGH, LOW, HIGH, HIGH}  
};

int button1 = 2;  
int button2 = 3;  
int button3 = 4;  

int green1 = 5;
int red1 = 6;
int green2 = 7;
int red2 = 8;
int green3 = 9;
int red3 = 10;

int stepPin = 11;
int dirPin = 12;

int currentFloor = 1; 

int targetSteps1 = 2200;  
int targetSteps2 = 2200;     
int targetSteps3 = 2200;     

int targetSpeed1 = 1000;   
int targetDirection1 = 1; 

int targetSpeed2 = 1000;  
int targetDirection2 = 0; 

int targetSpeed3 = 1000; 
int targetDirection3 = -1; 


unsigned long lastPressTime = 0;
unsigned long debounceDelay = 200; 

void setup() {
  pinMode(button1, INPUT_PULLUP);  
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);

  pinMode(green1, OUTPUT);
  pinMode(red1, OUTPUT);
  pinMode(green2, OUTPUT);
  pinMode(red2, OUTPUT);
  pinMode(green3, OUTPUT);
  pinMode(red3, OUTPUT);

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }

  displayNumber(currentFloor);  
}

void loop() {
  if (millis() - lastPressTime > debounceDelay) {  
    if (digitalRead(button1) == LOW && currentFloor != 1) {  
      moveToFloor(1, targetSteps1, targetSpeed1, targetDirection1); 
    } 
    else if (digitalRead(button2) == LOW && currentFloor != 2) {  
      moveToFloor(2, targetSteps2, targetSpeed2, targetDirection2); 
    } 
    else if (digitalRead(button3) == LOW && currentFloor != 3) {  
      moveToFloor(3, targetSteps3, targetSpeed3, targetDirection3); 
    }
  }

  delay(50); 
}

void displayNumber(int num) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], digits[num][i]);
  }
}

void moveToFloor(int targetFloor, int steps, int speed, int direction) {
  if ((currentFloor == 1 && targetFloor == 3) || (currentFloor == 3 && targetFloor == 1)) {
    steps *= 2; 
  }

  if (currentFloor == 3 && targetFloor == 2) {
    direction = 1;  
  }

  digitalWrite(dirPin, direction == 1 ? HIGH : LOW); 
  steps = abs(steps); 

  for (int i = 0; i < steps; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(speed); 
    digitalWrite(stepPin, LOW);
    delayMicroseconds(speed);  
  }

  currentFloor = targetFloor;
  displayNumber(currentFloor);  
  updateLamps(currentFloor); 
  lastPressTime = millis();  
}

void updateLamps(int floor) {
  digitalWrite(green1, floor == 1 ? HIGH : LOW);
  digitalWrite(red1, floor != 1 ? HIGH : LOW);

  digitalWrite(green2, floor == 2 ? HIGH : LOW);
  digitalWrite(red2, floor != 2 ? HIGH : LOW);

  digitalWrite(green3, floor == 3 ? HIGH : LOW);
  digitalWrite(red3, floor != 3 ? HIGH : LOW);
}