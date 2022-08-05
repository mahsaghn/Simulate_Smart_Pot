

#include <dht.h>
dht DHT;
#define temp_lowerBound 10
#define temp_upperBound 25

#define hum_lowerBound 10
#define hum_higherBound 25

#define Moisture_PIN A0
#define DHT11_PIN A1
#define Motor_PIN 8
int is_hot=0;
int is_cold=0;

String msg;
int temp;
int humidity;
int moisture;

void get_data();
void send_data();
void check_data();
void start_pump();

void setup()
{
  Serial.begin(9600);
  pinMode(Motor_PIN, OUTPUT);
  digitalWrite(Motor_PIN,LOW);
}

void loop()
{
    get_data();
    check_data();
   while (Serial.available())
  {
    delay(10);
    char c = Serial.read();
    msg +=c;
  }
  if(msg.length()>0)
  {   
    if(msg=="on")
    {
      send_data();
    }
    msg = "";
  }
    delay(500);  
}      
     

void get_data()
{
  int chk = DHT.read11(DHT11_PIN);
  temp=int(DHT.temperature);
  humidity=int(DHT.humidity);
  
  moisture = analogRead(Moisture_PIN)*0.0048828125;   
}

void check_data()
{
  if(temp<temp_lowerBound)
  {
    is_cold=1;
  }
   else if(temp>temp_upperBound)
  {
    is_hot=1;
  }
  else
  {
    is_cold=0;
    is_hot=0;
    }

   if(moisture<2)
   {
    start_pump();
   }
}

void start_pump()
{
  digitalWrite(Motor_PIN,HIGH);
  delay(1000);
  digitalWrite(Motor_PIN,LOW);
 }
 
void send_data()
{      
  Serial.write(lowByte(temp));
 Serial.write(highByte(temp));
   //Serial.println(temp);
   
  Serial.write(lowByte(humidity));
  Serial.write(highByte(humidity));
   //Serial.println(humidity);
   
  Serial.write(lowByte(moisture));
  Serial.write(highByte(moisture));
    //Serial.println(moisture);
    
  //Serial.write(lowByte(is_hot));
 // Serial.write(highByte(is_hot));
    //Serial.println(is_hot);
    
  //Serial.write(lowByte(is_cold));
  //Serial.write(highByte(is_cold));
  //Serial.println(is_cold);
  //Serial.println("////////////////");
}
