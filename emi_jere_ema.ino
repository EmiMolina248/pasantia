 /*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>
//#include <Keyboard.h>

Servo myservo;  // create servo object to control a servo
int sensorValue,regulaUmbral, servoValue,cont, prom, optionUmbral,segs;
 
const int BUTTON_PIN = 7;
const int led = 8;
const int largoArray = 10;// variable que contiene el largo del array del sensor
int arraySensor[largoArray]; 
int arrayRegulador[largoArray];
int currentState;// the current reading from the input pin


int promValues(int b){
  int sum  = 0;
  for(int i= 1;i<largoArray ;i++){
   arraySensor[i-1] = arraySensor[i]; //funcion para sacar el promedio de los valores del sensor guardados en el array
   sum += arraySensor[i-1];
   }
  arraySensor[9] = b;
  sum += b ; 
  return sum/largoArray ;
}

           

int getUmbral(int p,int o, int um){
  
  if(currentState == LOW){
    if (optionUmbral == 3){
        optionUmbral=1;
    }
    else if(currentState == LOW){
      optionUmbral++;
    }
  }
  switch(o){
  case 1:
    return 250;
   break; 
  case 2:
    return 100 + um;
  break; 
  case 3:
     return p*1.25;
     break;
  }
}


  
void setup() {
  pinMode(led, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
  myservo.write(0);
  //Keyboard.begin();

}



void loop() {
  regulaUmbral = analogRead(A2);
  sensorValue = analogRead(A3);
  currentState = digitalRead(BUTTON_PIN);
  if(cont % 2 == 0 ){
   prom = promValues(sensorValue);
   if (cont >= 800){
    cont=0;
   }
  }
  cont++; 
  if(sensorValue > getUmbral(prom, optionUmbral,regulaUmbral) ){
   segs++;
   digitalWrite(led, HIGH);
   if( segs % 5 == 0){
      Serial.println("keyboard,");
   }
   //Keyboard.press(' ');
   if(segs>=180){ 
    myservo.write(0);
    segs=0;
   }
   else{
    myservo.write(segs);
   }
  }
    else{
      segs = 0;
      digitalWrite(led, LOW);
      myservo.write(0);
    }
  Serial.println(String(sensorValue) +","+ String(prom)+ ", "+ String(getUmbral(prom,optionUmbral,regulaUmbral)) + ", " +String(segs)+ "," +String(optionUmbral));
  delay(100);        
                             
}



String arrayMessage(){
  String mess = "{";
  for(int i = 0; i<largoArray ;i++){      // funcion para mostrar los elementos del array
    mess += String(arraySensor[i])+ ", ";
  } 
    mess += "}";
    return mess;
} 
