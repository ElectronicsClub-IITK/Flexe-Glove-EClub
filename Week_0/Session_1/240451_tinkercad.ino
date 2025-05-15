const int pot1pin = A0;
const int pot2Pin = A1;
const int buzz[] = {2,3,4};
const int led[]={5,6,7,8,9};
int ledIndex = 0;
void setup(){
  for(int i=0;i<3;i++){
    pinMode(buzz[i],OUTPUT);
  }
  
  for(int i=0;i<5;i++){
    pinMode(led[i],OUTPUT);
  }
}

void loop(){
  int val = analogRead(pot1pin);
  if(val>=0 && val<=341){
    digitalWrite(buzz[0], HIGH);
    digitalWrite(buzz[1], LOW);
    digitalWrite(buzz[2], LOW);
  }
  else if(val>=342 && val<=683) {
    digitalWrite(buzz[0], LOW);
    digitalWrite(buzz[1], HIGH);
    digitalWrite(buzz[2], LOW);
  }
  else if(val>=684 && val<=1023){
    digitalWrite(buzz[0], LOW);
    digitalWrite(buzz[1], LOW);
    digitalWrite(buzz[2], HIGH);
  }
  int pot2Val = analogRead(pot2Pin);
  int delayTime = map(pot2Val, 0, 1023, 100, 1000);
  for (int i = 0; i < 5; i++) {
    digitalWrite(led[i], LOW);
  }
  digitalWrite(led[ledIndex], HIGH);
  ledIndex = (ledIndex + 1) % 5;
  delay(delayTime);
}

//  https://www.tinkercad.com/things/6Pmq6vsHjiX-swanky-kasi-bojo?sharecode=ucS9iLVnjoPUTVGFKqTUGPR0GLn8IqLnp8RAPTtCCYM
