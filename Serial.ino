#include <SoftwareSerial.h>
SoftwareSerial Bluetooth(10, 9); // RX, TX
int Data; // the data received
int a;
void setup() {
  Bluetooth.begin(9600);
  Serial.begin(9600);
  Serial.println("Waiting for command...");

  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
 
}
 
void loop() {
  if (Bluetooth.available()){ //wait for data received
    Data=Bluetooth.read();
    
    if(Data=='2'){  
      Serial.println("GOING FORWARD");
      Bluetooth.println("GOING FORWARD");
      analogWrite(6, 255);
      analogWrite(11,255);
       digitalWrite(2,HIGH);
       digitalWrite(3,LOW);
       digitalWrite(5,HIGH);
       digitalWrite(4,LOW); 
    }
    else if(Data=='0'){
       Serial.println("STOPPING");
       Bluetooth.println("STOPPING");
       digitalWrite(2,LOW);
       digitalWrite(3,LOW);
       digitalWrite(5,LOW);
       digitalWrite(4,LOW);
       
    }
    else if(Data=='1'){  
      Serial.println("GOING BACK");
      Bluetooth.println("GOING BACK");
      analogWrite(6, 255);
      analogWrite(11,255);
      digitalWrite(3,HIGH);
      digitalWrite(2,LOW);
      digitalWrite(4,HIGH);
      digitalWrite(5,LOW); 
    }
    else if(Data=='3'){
       Serial.println("TURNING RIGHT");
       Bluetooth.println("TURNING RIGHT");
       analogWrite(6,255);
       digitalWrite(2,HIGH);
       digitalWrite(3,LOW);
       analogWrite(11, 80);
      digitalWrite(4,HIGH);
      digitalWrite(5,LOW);
    }
    else if(Data=='4'){
       Serial.println("TURNING LEFT");
       Bluetooth.println("TURNING LEFT");
       analogWrite(6, 80);
  analogWrite(11,255);
       digitalWrite(3,HIGH);
       digitalWrite(2,LOW);
       digitalWrite(5,HIGH);
       digitalWrite(4,LOW);
    }
     else if(Data=='5'){
       Serial.println("TURNING 360");
       Bluetooth.println("TURNING 360");
       analogWrite(6, 255);
      analogWrite(11,255);
       digitalWrite(3,HIGH);
       digitalWrite(2,LOW);
       digitalWrite(5,HIGH);
       digitalWrite(4,LOW); 
    }
    else if(Data=='6')
                   {
                   digitalWrite(12,HIGH); 
                          Serial.println("ON");
                          Bluetooth.println("ON");
                       
                    }
   else if (Data=='7')
                        { digitalWrite(12,LOW);
                         
                          Serial.println("Off");
                           Bluetooth.println("OFF");
                        }
                       
    else if(Data=='8'){  
      Serial.println("GOING FORWARD SLOWLY");
      Bluetooth.println("GOING FORWARD SLOWLY");
      analogWrite(6,80);
      analogWrite(11,80);
       digitalWrite(2,HIGH);
       digitalWrite(3,LOW);
       digitalWrite(5,HIGH);
       digitalWrite(4,LOW); 
    }
             else if(Data=='9'){  
      Serial.println("GOING FORWARD MEDIUM");
      Bluetooth.println("GOING FORWARD MEDIUM");
      analogWrite(6, 160);
      analogWrite(11,160);
       digitalWrite(2,HIGH);
       digitalWrite(3,LOW);
       digitalWrite(5,HIGH);
       digitalWrite(4,LOW); 
    }
    
    else{;}
  }
}
