
#include <HID-Project.h>
#include <HID-Settings.h>

#define NO_OF_SENSORS 8
#define GND 21
// int pins[]={19,18,15,14,16,10,9,8};
int possible[]={1,2,3,4,5,1,2,3,4,5,1,2,3,4,5};
int pins[]={16,10,9,19,15,16,17,18};
bool readpin(int pin){
    digitalWrite(GND,HIGH);
    // delay(10);
    
    digitalWrite(GND,LOW);
    // delay(10);
 
    return !digitalRead(pin);
}
int currentState, previousState;
int currentValue = 0;
int relative;


void setup() {
  
    for (int i=0;i<NO_OF_SENSORS;i++){
    pinMode(pins[i],INPUT);
  }
  pinMode(GND,OUTPUT);
  // put your setup code here, to run once:
  Serial.begin(9600);
  Consumer.begin();
}

void loop() {
  // Convert to current state
  int output[6]={false};
  for (int j=0;j<5;j++){
  for (int i=0;i<NO_OF_SENSORS; i++){
    if (readpin(pins[i])){
      output[i]=true;
      currentState=i+1;
    }
    
    
  }
  delay(1);
  }
  
// for (int i=0;i<5;i++){
//   Serial.print(output[i]);
// }

// Serial.print(" ");

  // handle relativity
  // Serial.print(currentState);
  // Serial.print(" ");
  if (currentState != previousState){
    int mid=NO_OF_SENSORS+previousState-1;
    for (int i=mid-((NO_OF_SENSORS-1)/2);i<mid;i++){
        Serial.print(possible[i]);
        if (possible[i]==currentState){
          currentValue-=mid-i;
          Consumer.write(MEDIA_VOLUME_DOWN);
          delay(5);
        }
    }
    Serial.print(" ");


  Serial.print(previousState);
    Serial.print(" ");
    for (int i=mid+1;i<mid+((NO_OF_SENSORS-1)/2)+1;i++){
      Serial.print(possible[i]);
        if (possible[i]==currentState){
          currentValue+=i-mid;
          Consumer.write(MEDIA_VOLUME_UP);
          delay(5);
        }
    }
  
  Serial.print(" ");
  Serial.println(currentValue);
  }

  previousState =currentState;
}