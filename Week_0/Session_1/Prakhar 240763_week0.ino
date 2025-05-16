const int p1 = A0;  
const int p2 = A1;  
const int bP[3] = {9, 10,11};  
const int lP[5] = {6, 5, 4, 3, 2};  

int cL = 0;

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(bP[i], OUTPUT);
    digitalWrite(bP[i], LOW);
  }
  for (int i = 0; i < 5; i++) {
    pinMode(lP[i], OUTPUT);
    digitalWrite(lP[i], LOW);
  }
  Serial.begin(9600);
}

void loop(){
	int p1V = analogRead(p1), p2V = analogRead(p2);
  int hbV = p1V<=341?0:p1V<=682?1:2;
  for(int i=0;i<3;i++)
    digitalWrite(bP[i], i==hbV?HIGH:LOW);
  int dT = map(p2V, 0, 1023, 50, 1000);
  for(int i=cL>0?cL:0;i<5;i++){
    cL = (cL+1)%5;
    digitalWrite(lP[i], HIGH);
    delay(dT);
	digitalWrite(lP[i], LOW);  
  }
}

// tindercad link - https://www.tinkercad.com/things/5BqMECcQIqI-240763-week0?sharecode=K4YUM484q-_0O7UPnKUv8Z472QgNJr-Iuq2qLPd8RRI