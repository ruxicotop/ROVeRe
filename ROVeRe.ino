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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
   dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) return;
  transmite(t);
  transmite(h);
  delay(2000);
}
