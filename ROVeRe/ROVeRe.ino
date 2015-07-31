#include <DHT.h>

#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 22  (AM2302)

DHT dht(DHTPIN, DHTTYPE);

char cif (int n)
{
  if (n==0) return '0';
  if (n==1) return '1';
  if (n==2) return '2';
  if (n==3) return '3';
  if (n==4) return '4';
  if (n==5) return '5';
  if (n==6) return '6';
  if (n==7) return '7';
  if (n==8) return '8';
  if (n==9) return '9';
}

void date(int nr)
{
  int og=0,cifra;
  while (nr>0) 
  {
    og=og*10+nr%10;
    nr=nr/10;
  }
  while (og>0)
  {
    cifra=og%10;
    og=og/10;
    Serial.write(cif(cifra));
  }
  Serial.write("!");
}
void transmite(float t)
{
  int a; char i[2];
  a=trunc(t);
  i[1]=cif(a%10);
  i[0]=cif(a/10);
  Serial.write(i[0]);
  Serial.write(i[1]);
  Serial.write(".");
  t=(t-a)*100;
  a=trunc(t);
   i[1]=cif(a%10);
  i[0]=cif(a/10);
  Serial.write(i[0]);
  Serial.write(i[1]);
  Serial.write("!");
}
void fata()
{
         digitalWrite(9,LOW);
         digitalWrite(6,HIGH);
         digitalWrite(10,LOW);
         digitalWrite(11,HIGH);
}
void spate()
       {
          digitalWrite(6,LOW);
          digitalWrite(9,HIGH);
          digitalWrite(11,LOW);
          digitalWrite(10,HIGH);
        }
void stanga()
       {
          digitalWrite(6,LOW);
          digitalWrite(9,HIGH);
          digitalWrite(10,LOW);
          digitalWrite(11,HIGH);
        }
void dreapta()
       {
          digitalWrite(9,LOW);
          digitalWrite(6,HIGH);
          digitalWrite(11,LOW);
          digitalWrite(10,HIGH);
        }
void oprire()
{
    digitalWrite(9,LOW);
    digitalWrite(6,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
   dht.begin();
   pinMode(5,OUTPUT);
   pinMode(6,OUTPUT);
   pinMode(9,OUTPUT);
   pinMode(10,OUTPUT);
   pinMode(11,OUTPUT);
   analogWrite(5,255);
   delay(60000);
   analogWrite(5,67);
}

void loop() {
  if (Serial.available()>0)
  {
    int nr,viteza;
    nr=Serial.read();
    if (nr==49) fata();
    if (nr==50) stanga();
    if (nr==52) dreapta();
    if (nr==51) spate();
    if (nr==53) oprire();
  }
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float p=readPressure(A0);
  float co=analogRead (A1);
  float hic= dht.computeHeatIndex(t,h,false);
  transmite(t);
  transmite(h);
  date(p);
  transmite(hic);
  date(co);
  delay(2000);
}

float readPressure(int pin){  
    int pressureValue = analogRead(pin);
    float pressure=((pressureValue/1024.0)+0.095)/0.000009;
    return pressure;
 }

