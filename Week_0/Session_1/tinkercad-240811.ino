
const int POT1_PIN = A0;    // first potentiometer
const int POT2_PIN = A1;    // second potentiometer
const int BUZZER1_PIN = 2;  // buzzer 1
const int BUZZER2_PIN = 3;  // buzzer 2
const int BUZZER3_PIN = 4;  // buzzer 3

const int LED_PINS[] = {5, 6, 7, 8, 9}; //leds
const int NUM_LEDS = 5;                 

int currentLed = 0;      
unsigned long lastLedChange = 0; 

void setup() {
  
  pinMode(BUZZER1_PIN, OUTPUT);
  pinMode(BUZZER2_PIN, OUTPUT);
  pinMode(BUZZER3_PIN, OUTPUT);
  
  
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }
  
  //buzzrs off initially
  digitalWrite(BUZZER1_PIN, LOW);
  digitalWrite(BUZZER2_PIN, LOW);
  digitalWrite(BUZZER3_PIN, LOW);
  
 //leds off
  allLedsOff();
}

void loop() {
 
  int pot1Value = analogRead(POT1_PIN);
  int pot2Value = analogRead(POT2_PIN);
  
  
  controlBuzzers(pot1Value);
  
 
  controlLeds(pot2Value);
}

void controlBuzzers(int value) {
  
  digitalWrite(BUZZER1_PIN, LOW);
  digitalWrite(BUZZER2_PIN, LOW);
  digitalWrite(BUZZER3_PIN, LOW);
  
  // determine which buzzer to activate based on value ranges
  if (value >= 0 && value <= 341) {
    digitalWrite(BUZZER1_PIN, HIGH);
  } else if (value > 341 && value <= 682) {
    digitalWrite(BUZZER2_PIN, HIGH);
  } else if (value > 682) {
    digitalWrite(BUZZER3_PIN, HIGH);
  }
}

void controlLeds(int speedValue) {
  // potentiometer value to delay (20ms to 1000ms)
  int ledDelay = map(speedValue, 0, 1023, 20, 1000);
  
 
  if (millis() - lastLedChange >= ledDelay) {
    
    digitalWrite(LED_PINS[currentLed], LOW);
    
    
    currentLed = (currentLed + 1) % NUM_LEDS;
    
 
    digitalWrite(LED_PINS[currentLed], HIGH);
    
    
    lastLedChange = millis();
  }
}

void allLedsOff() {
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(LED_PINS[i], LOW);
  }
}

//link to the circuit
//https://www.tinkercad.com/things/fOmIjSsSOwG/editel?returnTo=%2Fdashboard&sharecode=Ibei_9HUpPTVl8LpDKUZ_Z7GnWfjshEHt8htfR5VKZY