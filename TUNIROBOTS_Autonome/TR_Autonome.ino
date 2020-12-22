#include <Servo.h>
Servo myservopincedr, myservopincegch, myservosekkadr, myservosekkagch,  myservopann ;
int encodRA = 2;
int encodRB = 3;
int encodLA = 19;
int encodLB = 18;
int gch_ar = 23;
int gch_av = 22;
int gch_vit = 5;
int dr_av = 25;
int dr_ar = 24;
int dr_vit = 4;
int d=170;
int l=132;
int a=170;
int b=132;  
float e=0;
float R = 30;
float encoder_ticks = 4800;//1633.25;////// 
float precision = 4;////
long int previousTime;
long int previousTime2;
float distR;
float previousDistR;
float vitR;
int encoderRPos;
int lastEncoderRPos;
boolean encoderRA_set;
boolean encoderRB_set;
float distL;
float previousDistL;
float vitL;
int encoderLPos;
int lastEncoderLPos;
boolean encoderLA_set;
boolean encoderLB_set;
float distance_tick = (2 * PI*R) / (encoder_ticks*precision);

void go_left(float target_distance);
void go_right(float target_distance);
void go_backward(float target_distance);
void go_forward(float target_distance);
void Count_ChannelA_R();
void Count_ChannelB_R();
void Count_ChannelA_L();
void Count_ChannelB_L();

  void setup() {
  //target_tick = (target_deg*encoder_ticks*precision)/360;
  myservopincedr.attach(8); 
  myservopincegch.attach(9);
  myservosekkadr.attach(12);
  myservosekkagch.attach(11);
  myservopann.attach(10);
  myservopincedr.write(50); 
  myservopincegch.write(10);
  myservosekkadr.write(165);
  myservosekkagch.write(5);
  myservopann.write(160);
  delay(200);
  distR = 0;
  previousDistR=0;
  vitR = 0;
  encoderRPos = 0;
  lastEncoderRPos = 0;
  encoderRA_set = false;
  encoderRB_set = false;
  previousTime=0;
  previousTime2=0;
  distL = 0;
  previousDistL=0;
  vitL = 0;
  encoderLPos = 0;
  lastEncoderLPos = 0;
  encoderLA_set = false;
  encoderLB_set = false;
  pinMode(encodRA, INPUT);
  pinMode(encodRB, INPUT);
  pinMode(encodLA, INPUT);
  pinMode(encodLB, INPUT);
  digitalWrite(encodRA, HIGH);
  digitalWrite(encodRB, HIGH);
  digitalWrite(encodLB, HIGH);
  digitalWrite(encodLA, HIGH);
  attachInterrupt(0, Count_ChannelA_R, CHANGE);
  attachInterrupt(1, Count_ChannelB_R, CHANGE);
  attachInterrupt(4, Count_ChannelA_L, CHANGE);
  attachInterrupt(5, Count_ChannelB_L, CHANGE);
  Serial.begin(9600);
}

//****************************************************************************************************Strategy_1
void loop(){
//***********************************************************************************************task_1
  go_forward(89.53);
  myservopincedr.write(10);
  myservopincegch.write(45);
  delay(1000);
  myservosekkadr.write(50);
  myservosekkagch.write(110);
  delay(1000);
  
//***********************************************************************************************task_2
  go_forward(274.88);
  myservosekkadr.write(120);
  myservosekkagch.write(35);
  delay(500);
  myservopincedr.write(50);
  myservopincegch.write(10);
  delay(1000);
  
//***********************************************************************************************task_3
  go_backward(330);
  myservosekkadr.write(165);
  myservosekkagch.write(10);
  delay(500);
  myservopincedr.write(10);
  myservopincegch.write(45);
  delay(500);
  
//***********************************************************************************************task_4
  go_left(92.3);
  go_backward(98.5);
  myservopann.write(45);
  delay(1000);
  myservopann.write(150);
  delay(500);
  
//***********************************************************************************************task_5
  go_backward(100);
  myservopann.write(45);
  delay(1000);
  myservopann.write(150);
  delay(500);
  
//***********************************************************************************************task_6
  go_forward(176);
  go_right(92);
  go_forward(242);
  go_right(92);
  go_forward(145);
  go_backward(84.5);
  go_left(92.3);
  go_forward(185);
  while (true){
    digitalWrite(dr_av, HIGH);
    digitalWrite(dr_ar, HIGH);
    digitalWrite(gch_av, HIGH);
    digitalWrite(gch_ar, HIGH);
  }
}

//***********************************************************************************************functions
//***********************************************************************************************functions
//***********************************************************************************************functions
void go_forward(float target_distance){
  while(distL<target_distance){
     if ((millis()-previousTime) > 20){
        previousTime = millis();
        Serial.println(distL);
        Serial.println(distR);
        vitL=distL-previousDistL;
        vitR=distR-previousDistR;
        previousDistL=distL;
        previousDistR=distR;
        if(vitL>vitR){
          e=220*(vitL-vitR); 
          if(a<200){
            a=a+e;  
          }
          else{
            b=b-e; 
          }
        }
        else{
          e=213*(vitR-vitL);
             if(b<200){
            b=b+e;  
          }
          else{
            a=a-e;
          } 
        }
      }
      analogWrite(dr_vit, a);
      analogWrite(gch_vit, b);
      digitalWrite(dr_av, HIGH);
      digitalWrite(dr_ar, LOW);
      digitalWrite(gch_av, HIGH);
      digitalWrite(gch_ar, LOW);
  }
  digitalWrite(dr_av, HIGH);
  digitalWrite(dr_ar, HIGH);
  digitalWrite(gch_av, HIGH);
  digitalWrite(gch_ar, HIGH);
  distL=0;
  distR=0;
  previousDistL=0;
  previousDistR=0;
  previousTime=millis();
  a=d;
  b=l;
}

void go_backward(float target_distance){
  while((-distL)<target_distance){
     if ((millis()-previousTime) > 20){
        previousTime = millis();
        Serial.println(distL);
        Serial.println(distR);
        vitL=(-distL)-(-previousDistL);
        vitR=(-distR)-(-previousDistR);
        previousDistL=distL;
        previousDistR=distR;
        if(vitL>vitR){
          e=220*(vitL-vitR); 
          if(a<200){
            a=a+e;  
          }
          else{
            b=b-e; 
          }
        }
        else{
          e=213*(vitR-vitL);
             if(b<200){
            b=b+e;  
          }
          else{
            a=a-e;
          } 
        }
    }
    analogWrite(dr_vit, a);
    analogWrite(gch_vit, b);
    digitalWrite(dr_ar, HIGH);
    digitalWrite(dr_av, LOW);
    digitalWrite(gch_ar, HIGH);
    digitalWrite(gch_av, LOW);
  }
  digitalWrite(dr_av, HIGH);
  digitalWrite(dr_ar, HIGH);
  digitalWrite(gch_av, HIGH);
  digitalWrite(gch_ar, HIGH);
  distL=0;
  distR=0;
  previousDistL=0;
  previousDistR=0;
  previousTime=millis();
}

void go_left(float target_distance){
  while((-distR)<target_distance){
    Serial.println(distL);
    Serial.println(distR);
    analogWrite(dr_vit, 170);
    analogWrite(gch_vit, 0);
    digitalWrite(dr_ar, HIGH);
    digitalWrite(dr_av, LOW);
    digitalWrite(gch_av, HIGH);
    digitalWrite(gch_ar, HIGH);
  }
  digitalWrite(dr_av, HIGH);
  digitalWrite(dr_ar, HIGH);
  digitalWrite(gch_av, HIGH);
  digitalWrite(gch_ar, HIGH);
  distL=0;
  distR=0;
  previousDistL=0;
  previousDistR=0;
  previousTime=millis();
  a=d;
  b=l;
}

void go_right(float target_distance){
  while((-distL)<target_distance){ 
    Serial.println(distL);
    Serial.println(distR);
    analogWrite(gch_vit, 170);
    digitalWrite(dr_ar, HIGH);
    digitalWrite(dr_av, HIGH);
    digitalWrite(gch_av, LOW);
    digitalWrite(gch_ar, HIGH);
  }
  digitalWrite(dr_av, HIGH);
  digitalWrite(dr_ar, HIGH);
  digitalWrite(gch_av, HIGH);
  digitalWrite(gch_ar, HIGH);
  distL=0;
  distR=0;
  previousDistL=0;
  previousDistR=0;
  previousTime=millis();
  a=d;
  b=l; 
}

void Count_ChannelA_R() {
  encoderRA_set = digitalRead(encodRA) == HIGH;
  encoderRPos += (encoderRA_set == encoderRB_set) ? -1 : +1;
  distR += (encoderRA_set == encoderRB_set) ? -distance_tick : +distance_tick;
}

void Count_ChannelB_R() {
  encoderRB_set = digitalRead(encodRB) == HIGH;
  encoderRPos += (encoderRA_set != encoderRB_set) ? -1 : +1;
  distR += (encoderRA_set != encoderRB_set) ? -distance_tick : +distance_tick;
}

void Count_ChannelA_L() {
  encoderLA_set = digitalRead(encodLA) == HIGH;
  encoderLPos += (encoderLA_set != encoderLB_set) ? -1 : +1;
  distL += (encoderLA_set != encoderLB_set) ? -distance_tick : +distance_tick;
}

void Count_ChannelB_L() {
  encoderLB_set = digitalRead(encodLB) == HIGH;
  encoderLPos += (encoderLA_set == encoderLB_set) ? -1 : +1;
  distL += (encoderLA_set == encoderLB_set) ? -distance_tick : +distance_tick;
}
