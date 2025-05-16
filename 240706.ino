 
const int POT1_PIN = A0;    
const int POT2_PIN = A1;    
const int BUZZER_PINS[3] = { 2, 3, 4 };
const int LED_PINS[5] = { 5, 6, 7, 8, 9 };

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(BUZZER_PINS[i], OUTPUT);
    digitalWrite(BUZZER_PINS[i], LOW);  
  }
  for (int i = 0; i < 5; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], LOW);     
  }
}

void loop() {
  int pot1Val = analogRead(POT1_PIN);   
  int pot2Val = analogRead(POT2_PIN);   

  
  if (pot1Val <= 341) {
    activateOnlyBuzzer(0);
  }
  else if (pot1Val <= 682) {
    activateOnlyBuzzer(1);
  }
  else {
    activateOnlyBuzzer(2);
  }

  
  int seqDelay = map(pot2Val, 0, 1023, 100, 1000);

   
  for (int i = 0; i < 5; i++) {
    
    for (int j = 0; j < 5; j++) {
      digitalWrite(LED_PINS[j], LOW);
    }
    
    digitalWrite(LED_PINS[i], HIGH);
    delay(seqDelay);
  }
}

 
void activateOnlyBuzzer(int index) {
  for (int i = 0; i < 3; i++) {
    digitalWrite(BUZZER_PINS[i], (i == index) ? HIGH : LOW);
  }
}

// https://www.tinkercad.com/things/i9jBhM07m6d/editel?sharecode=l3AqX_FD0uke1oF0fKv6O1fx5a-FbJ-76f2hC6qTECw