# include <Servo.h>
Servo myservo;
#define encodRA 2
#define encodLA 3
#define dr_ar 4
#define dr_av 7
#define dr_vit 5
#define gch_av 12
#define gch_ar 13
#define gch_vit 11
#define left A0
#define cleft A1
#define cright A2
#define right A3
#define xleft A4
#define xright A5
#define TRIGGER_PIN1 8
#define ECHO_PIN1 9

long measure;
float distance_mm;
const unsigned long MEASURE_TIMEOUT = 25000UL;
const float SOUND_SPEED = 340.0 / 1000;
boolean allow_count=false;
boolean allow_turn=true;
int counter=-1;
float motorSpeed=1.60;
float kp=15;
boolean a,b,c,d,f,g;
int turn_count=0;
int consRight=235;
int consLeft =181;
long int previousTime=0;
long int turnTimeCheck=0;
long int StopTimeCheck=-4000;
float RightSpeed=0;
float LeftSpeed=0;
long int Right_ticks=0;
long int Left_ticks=0;
int e=0;
boolean firstStop=true;
void Count_Right();
void Count_Left();
void avant(int a, int b);
void arriere(int a, int b);
void gauche(int a, int b);
void droite(int a, int b);
void gauche_taslih( int a1 , int b1);
void droite_taslih( int a1 , int b1);

void setup() {
  myservo.attach(10);
  myservo.write(90);
  pinMode(encodRA, INPUT);
  pinMode(encodLA, INPUT);
  pinMode(left, INPUT);
  pinMode(cleft, INPUT);
  pinMode(cright, INPUT);
  pinMode(right, INPUT);
  pinMode(TRIGGER_PIN1, OUTPUT);
  pinMode(ECHO_PIN1, INPUT);
  pinMode(6,INPUT);
  digitalWrite(6,LOW);
  digitalWrite(TRIGGER_PIN1, LOW);
  attachInterrupt(0, Count_Right, RISING);
  attachInterrupt(1, Count_Left, RISING);
  Serial.begin(9600);

}
void Count_Right()
{
  Right_ticks++;
}
void Count_Left()
{
  Left_ticks++;
}
void avant ( int a , int b ) 
{ 
  analogWrite(dr_vit, a);
  analogWrite(gch_vit, b);
  digitalWrite(dr_av, HIGH);
  digitalWrite(dr_ar, LOW);
  digitalWrite(gch_av, HIGH);
  digitalWrite(gch_ar, LOW);
}
void arriere ( int a , int b ) 
{
  analogWrite(dr_vit, a-100);
  analogWrite(gch_vit, b-100);
  digitalWrite(dr_av, LOW);
  digitalWrite(dr_ar, HIGH);
  digitalWrite(gch_av, LOW);
  digitalWrite(gch_ar, HIGH);
}
void droite_taslih ( int a1 , int b1,int i ) 
{
  analogWrite(dr_vit, a1);
  analogWrite(gch_vit, b1+i);
  digitalWrite(dr_av, HIGH);
  digitalWrite(dr_ar, LOW);
  digitalWrite(gch_av, HIGH);
  digitalWrite(gch_ar, LOW);
}
void gauche_taslih( int a1 , int b1,int i)
{
  analogWrite(dr_vit, a1+i);
  analogWrite(gch_vit, b1);
  digitalWrite(dr_av, HIGH);
  digitalWrite(dr_ar, LOW);
  digitalWrite(gch_av, HIGH);
  digitalWrite(gch_ar, LOW);
}
void droite()
{
  analogWrite(dr_vit, 0);
  analogWrite(gch_vit, consLeft);
  digitalWrite(dr_av, HIGH);
  digitalWrite(dr_ar, HIGH);
  digitalWrite(gch_av, HIGH);
  digitalWrite(gch_ar, LOW);
}
void gauche()
{
  analogWrite(dr_vit, consRight);
  analogWrite(gch_vit, 0);
  digitalWrite(dr_av, HIGH);
  digitalWrite(dr_ar, LOW);
  digitalWrite(gch_av, HIGH);
  digitalWrite(gch_ar, HIGH);
}

void gauche_arr()
{
  analogWrite(dr_vit, 0);
  analogWrite(gch_vit, consLeft);
  digitalWrite(dr_av, HIGH);
  digitalWrite(dr_ar, HIGH);
  digitalWrite(gch_av, LOW);
  digitalWrite(gch_ar, HIGH);
}
void gauchepro()
{
  analogWrite(dr_vit, consRight);
  analogWrite(gch_vit, consLeft);
  digitalWrite(dr_av, HIGH);
  digitalWrite(dr_ar, LOW);
  digitalWrite(gch_av, LOW);
  digitalWrite(gch_ar, HIGH);
}
void arreter()
{
  digitalWrite(dr_vit, LOW);
  digitalWrite(gch_vit, LOW);
  digitalWrite(dr_av, HIGH);
  digitalWrite(dr_ar, HIGH);
  digitalWrite(gch_av, HIGH);
  digitalWrite(gch_ar, HIGH);
}
void lecture()
{
  /*Lecture capteur*/
  a=digitalRead(left);
  b=digitalRead(cleft);
  c=digitalRead(cright);
  d=digitalRead(right);
  f=digitalRead(xleft);
  g=digitalRead(xright);
  /*Fin lecture capteur*/
}
boolean capteur(){
  int i=0;
  for(int j=0;j<2;j++)
  {
 digitalWrite(TRIGGER_PIN1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN1, LOW);
  measure = pulseIn(ECHO_PIN1, HIGH, MEASURE_TIMEOUT);
   distance_mm = measure / 2.0 * SOUND_SPEED; 
   if (distance_mm>0 && distance_mm<200){
      i++;
    }
   }
    if(i==2) return true;
    else return false;
}
/***********************************************************************************zouz 5tout k7ol*/
void TwoLinesStop(){
if((!f && !g)&&(millis()-StopTimeCheck>4000) && counter<4 ){
   counter++;
   StopTimeCheck=millis();
   if(counter==4){
        Left_ticks=0;
        Right_ticks=0;
      while(Left_ticks<1400)          //9addam
      {
        avant(consRight,consLeft);
        Serial.print(Left_ticks);
      }
        arreter();
        delay(200);
        Left_ticks=0;
        Right_ticks=0;
      while(Left_ticks<1650)          //dour issar bitweli
      {
        gauche_arr();
        Serial.print(Left_ticks);
      }
        arreter();
        delay(200);
        Left_ticks=0;
        Right_ticks=0;
      while(Right_ticks<1650)          //dour issar
      {
        gauche();
        Serial.print(Right_ticks);
      }
        arreter();
        delay(100);
        turnTimeCheck=millis()-1800;
        allow_count=true;
   }
   else if(counter==3){
      allow_turn=true;
      arreter();
      myservo.write(90);
      delay(1000);
   }
   else if(counter<3){
      arreter();
      
      if (counter==1){
        myservo.write(90);
      }
      else if (counter==2){
        myservo.write(160);
      }
      delay(1000);
   }
}
}
/************************************************************************************************suiveur*/
void suiveur() {
  if(turn_count==2)
  {
    allow_turn=false;
  
  if(digitalRead(6))
  {
    arreter();
    delay(5000);   }
  }
 if ((counter==-1)){
  if(capteur()){
  arreter();
  myservo.write(160);
  delay(5000);
  counter++;
  }
}

      lecture();  
      /*zouz 5tout k7ol*/
      TwoLinesStop();
      /*fin zouz 5tout k7ol*/
  /************************************************************************gauche*/
    if (a) {
    if((millis()-turnTimeCheck>2000)&& allow_turn && !d){  
    if(counter==2){
      allow_turn=false;
    }
    Right_ticks=0;
    Left_ticks=0;
    turnTimeCheck=millis();
    while(Right_ticks<1650){
    gauche();
    Serial.print(Right_ticks);
    }
if(allow_count){
  turn_count++;
}

   }
   else if((millis()-turnTimeCheck>2000)&& allow_turn && d && (counter==4)){
    counter++;
    Right_ticks=0;
    Left_ticks=0;
    turnTimeCheck=millis();
    while(Right_ticks<1650){
    gauche();
    Serial.print(Right_ticks);
    }
   }
   else {
    gauchepro();
   }
   }
/*******************************************************************tasli7 gauche*/   
  else if ((!a && !b &&c && !d)||(a&&!b&&c&&d)) {
        int i=0;
        while((!a && !b &&c && !d)||(a&&!b&&c&&d)){
          i++;
          gauche_taslih( consRight , consLeft,i );
          lecture();
          TwoLinesStop();
              if(turn_count==2)
              {
                allow_turn=false;
              
              if(digitalRead(6))
              {
                arreter();
                delay(5000);
               }
              }        
        }
  }

  /*******************************************************************tasli7 droite*/
    else if ((!a&&b&&!c&&!d)||(a&&b&&!c&&d)) {
      int i=0;
      while((!a&&b&&!c&&!d)||(a&&b&&!c&&d)){
        i++;
        droite_taslih( consRight , consLeft,i );
        lecture();
        TwoLinesStop();
            if(turn_count==2)
            {
              allow_turn=false;
            
            if(digitalRead(6))
            {
              arreter();
              delay(5000);
             }
            }       
      }
  }

   /************************************************************************ droite*/
   else if (!a && d) {
    droite();
   }

   /************************************************************************ arriere*/
   else if (!a && !b &&!c && !d){
    arriere(consRight,consLeft);
   }
   /************************************************************************ avant*/
   else {
    /*asservissement*/
         if ((millis()-previousTime) > 20){
              // *********************************3ajla issar
            e=kp*((float)((float)Left_ticks/(float)(millis()-previousTime))-motorSpeed);
              if(e<0){
                consLeft=consLeft-e;  
                if(consLeft>255){consLeft=255;}
                }
              else{
                consLeft=consLeft-e; 
                if(consLeft<0){consLeft=0;}
                }
              // *********************************3ajla imin
              e=kp*((float)((float)Right_ticks/(float)(millis()-previousTime))-motorSpeed);
              if(e<0){
                consRight=consRight-e;  
                if(consRight>255){consRight=255;}
                }
              else{
                consRight=consRight-e; 
                if(consRight<0){consRight=0;}
                }
              Right_ticks=0;
              Left_ticks=0;
              previousTime = millis();
            }
            /*Fin asservissement*/
            avant(consRight, consLeft); 
         }
}
void loop() {
  if(firstStop)
  {
    delay(1000);
    firstStop=false;
    previousTime = millis();
  }
  //while(millis()<47000)
    suiveur(); 
  //  arreter();   
}
