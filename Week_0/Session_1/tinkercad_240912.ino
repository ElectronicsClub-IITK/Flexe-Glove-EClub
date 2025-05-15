const int pot1=A0;
const int pot2=A1;
const int buzzer[3]={1,2,3};
const int LED[5]={4,5,6,7,8};
void setup(){
  for (int i=0;i<3;i++){
    pinMode(buzzer[i],OUTPUT);
    digitalWrite(buzzer[i],LOW);
 }
  for (int i = 0; i < 5; i++) {
    pinMode(LED[i], OUTPUT);
        digitalWrite(LED[i],HIGH);
 }
  Serial.begin(9600);
}
void loop()
{
  int pot1value=analogRead(pot1);
  int pot2value=analogRead(pot2);
  int delay_time=map(pot2value,0,1023,100,10000);
    for (int i=0;i<3;i++){
    pinMode(buzzer[i],OUTPUT);
    digitalWrite(buzzer[i],LOW);
  
  if (pot1value <=341){
         digitalWrite(buzzer[0],HIGH);
  }
  if((pot1value<=682&&pot1value>341)){
        digitalWrite(buzzer[1],HIGH);
  }
  if (pot1value<682){
        digitalWrite(buzzer[2],HIGH);
  }
  for (int i=0;i<5;i++){
    digitalWrite(LED[i], HIGH);
    delay(delay_time);
    digitalWrite(LED[i],LOW);
     
  }
   }
}
//TinkerCad : https://www.tinkercad.com/things/lpaCQnR3RNt
