const int pot1 = A0;
const int pot2 = A1;

const int buzzer1 = 2;
const int buzzer2 = 3;
const int buzzer3 = 4;

const int led1 = 5;
const int led2 = 6;
const int led3 = 7;
const int led4 = 8;
const int led5 = 9;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buzzer1, OUTPUT);
  pinMode(buzzer2, OUTPUT);
  pinMode(buzzer3, OUTPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int pot1Value = analogRead(pot1);
  int pot2Value = analogRead(pot2);

  digitalWrite(buzzer1, LOW);
  digitalWrite(buzzer2, LOW);
  digitalWrite(buzzer3, LOW);

  if (pot1Value >= 0 && pot1Value <= 341) {
    digitalWrite(buzzer1, HIGH);
  } else if (pot1Value > 341 && pot1Value <= 682) {
    digitalWrite(buzzer2, HIGH);
  } else if (pot1Value > 682 && pot1Value <= 1023) {
    digitalWrite(buzzer3, HIGH);
  }

  int newvalue = map(pot2Value, 0, 1023, 100, 5000);

  digitalWrite(led1, HIGH);
  delay(newvalue);
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  delay(newvalue);
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);
  delay(newvalue);
  digitalWrite(led3, LOW);
  digitalWrite(led4, HIGH);
  delay(newvalue);
  digitalWrite(led4, LOW);
  digitalWrite(led5, HIGH);
  delay(newvalue);
  digitalWrite(led5, LOW);

  Serial.print("Pot1 Value: ");
  Serial.print(pot1value);
  Serial.print(", LED Time Delay: ");
  Serial.print(newvalue);
}

// circuit diagram on tinkercad
// https://www.tinkercad.com/things/37jjnaTym3F-smashing-vihelmo-sango?sharecode=MqaS4It_qZ0YrP4NohKtEGBzYApwtFFf66A-e_m2qn4
