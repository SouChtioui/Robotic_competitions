#include "ThingSpeak.h"
#include "secrets.h"
#include <WiFi.h>
#include <Robojax_L298N_DC_motor.h>
/*
#define SECRET_SSID "Souhail"
#define SECRET_PASS "12344321"
#define SECRET_CH_ID 971745
#define SECRET_WRITE_APIKEY "5MBTFD2U5AZVUD87"
*/
#define SECRET_SSID "CME"
#define SECRET_PASS "cme_lma2020"
#define SECRET_CH_ID 971654
#define SECRET_WRITE_APIKEY "E5UMJ64D27IDUZJ7"

#define mission_one_code 6191
#define mission_two_code 6192
#define mission_three_code 6193
//*******************************************************************************MOTORS***************************************************

// motor 1 settings
#define CHA 0
#define ENA 19 // this pin must be PWM enabled pin if Arduino board is used
#define IN1 5
#define IN2 18

// motor 2 settings
#define IN3 2
#define IN4 15
#define ENB 4// this pin must be PWM enabled pin if Arduino board is used
#define CHB 1

const int CCW = 2; // do not change
const int CW  = 1; // do not change

#define motor1 1 // do not change
#define motor2 2 // do not change

// for two motors without debug information // Watch video instruciton for this line: https://youtu.be/2JTMqURJTwg
Robojax_L298N_DC_motor robot(IN1, IN2, ENA, CHA,  IN3, IN4, ENB, CHB);

//************************************************************************Capteurs ligne***************************************************

#define left  26
#define cleft 27
#define cright 14
#define right 12
#define xleft 23
#define xright 13

#define RL 25
#define RC 35
#define RR 34

#define TRIGGER_PIN1 33
#define ECHO_PIN1 32
int L,C,R;
long measure;
float distance_mm;
const unsigned long MEASURE_TIMEOUT = 25000UL;
const float SOUND_SPEED = 340.0 / 1000;

boolean a,b,c,d,f,g;

int consRight=80;
int consLeft =80;


boolean firstStop=true;

void avant(int a, int b);
void arriere(int a, int b);
void gauche(int a, int b);
void droite(int a, int b);
void gauche_taslih( int a1 , int b1);
void droite_taslih( int a1 , int b1);
void suiveur2();
boolean free_to_go=false;
long int time_stamp=0;
long int code_time_stamp=0;
char servo_state='D';
int up_number=0;
int mission_number=0;
char mission_state='S';
int suiveur_number=1;
char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

// Initialize our values
int mission_code = 0;
String my_code="";
//*******************************************************functions
void send_to_server();
void ligne_horizontale();
void servo_count();
/************************************************************ Setup starts here ****************************************************/
/************************************************************ Setup starts here ****************************************************/
/************************************************************ Setup starts here ****************************************************/
void setup() {
  pinMode(left, INPUT);
  pinMode(cleft, INPUT);
  pinMode(cright, INPUT);
  pinMode(right, INPUT);
  pinMode(xright, INPUT);
  pinMode(xleft, INPUT);
  pinMode(RL, INPUT);
  pinMode(RC, INPUT);
  pinMode(RR, INPUT);
  pinMode(TRIGGER_PIN1,OUTPUT);
  pinMode(ECHO_PIN1,INPUT);
  robot.begin();

  Serial.begin(115200);  //Initialize serial

  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}
/************************************************************ functions starts here ****************************************************/
/************************************************************ functions starts here ****************************************************/
/************************************************************ functions starts here ****************************************************/
void avant ( int a , int b ) 
{ 
  robot.rotate(motor1, a, CW);//run motor1 at 60% speed in CW direction
  robot.rotate(motor2, b, CW);//run motor1 at 60% speed in CW direction
}
void arriere ( int a , int b ) 
{
  robot.rotate(motor1, a, CCW);//run motor1 at 60% speed in CW direction
  robot.rotate(motor2, b, CCW);//run motor1 at 60% speed in CW direction
}
void droite_taslih ( int a1 , int b1,int i ) 
{
  robot.rotate(motor1, a1, CW);//run motor1 at 60% speed in CW direction
  robot.rotate(motor2, b1+i, CW);//run motor1 at 60% speed in CW direction
  
}
void gauche_taslih( int a1 , int b1,int i)
{
  robot.rotate(motor1, a1+i, CW);//run motor1 at 60% speed in CW direction
  robot.rotate(motor2, b1, CW);//run motor1 at 60% speed in CW direction
}
void droite()
{
  robot.rotate(motor1, consRight, CCW);//run motor1 at 60% speed in CW direction
  robot.rotate(motor2, consLeft, CW);//run motor1 at 60% speed in CW direction
 
}
void gauche()
{
  robot.rotate(motor1,consRight, CW);//run motor1 at 60% speed in CW direction
  robot.rotate(motor2,consLeft, CCW);//run motor1 at 60% speed in CW direction

}


void arreter()
{
  robot.brake(1);
  robot.brake(2);  
 

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
boolean capteur(int distance){
  int i=0;
  for(int j=0;j<2;j++)
  {
 digitalWrite(TRIGGER_PIN1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN1, LOW);
  measure = pulseIn(ECHO_PIN1, HIGH, MEASURE_TIMEOUT);
   distance_mm = measure / 2.0 * SOUND_SPEED; 
   if (distance_mm>0 && distance_mm<distance){
      i++;
    }
   }
    if(i==2) return true;
    else return false;
}


/************************************************************************************************suiveur*/
void suiveur_IR() {
  lecture();
  //*********************5edmit l code*****************/
  if(mission_number==1){
  if(f && (millis()-code_time_stamp>500)){ //xleft
    my_code=my_code+'1';
    code_time_stamp=millis();
  }
  else if(g && (millis()-code_time_stamp>500)){ //xright
    my_code=my_code+'0';
    code_time_stamp=millis();
  }
  }
  else if(mission_number==2){
  if(!f && (millis()-code_time_stamp>500)){ //xleft
    my_code=my_code+'1';
    code_time_stamp=millis();
  }
  else if(!g && (millis()-code_time_stamp>500)){ //xright
    my_code=my_code+'0';
    code_time_stamp=millis();
  }
  }
  //*********************5edmit l code*****************/
  /*4 k7ol*/
  if (a && b && c && d){ 
    ligne_horizontale();
  }
  /*fin 4 k7ol*/
  /************************************************************************gauche*/
  else if (a && !d) {
gauche() ; 
   }
/*******************************************************************tasli7 gauche*/   
  else if ((!a && !b &&c && !d)||(a&&!b&&c&&d)) {
        int i=0;
        while((!a && !b &&c && !d)||(a&&!b&&c&&d)){
          i++;
          if(i>40)
          {
            i=40;
          }
          gauche_taslih( consRight , consLeft,i );
          lecture();
            //*********************5edmit l code*****************/
            if(mission_number==1){
            if(f && (millis()-code_time_stamp>500)){ //xleft
              my_code=my_code+'1';
              code_time_stamp=millis();
            }
            else if(g && (millis()-code_time_stamp>500)){ //xright
              my_code=my_code+'0';
              code_time_stamp=millis();
            }
            }
            else if(mission_number==2){
            if(!f && (millis()-code_time_stamp>500)){ //xleft
              my_code=my_code+'1';
              code_time_stamp=millis();
            }
            else if(!g && (millis()-code_time_stamp>500)){ //xright
              my_code=my_code+'0';
              code_time_stamp=millis();
            }
            }
            //*********************5edmit l code*****************/
          /*4 k7ol*/
          if (a && b && c && d){ 
            ligne_horizontale();
          }
          /*fin 4 k7ol*/
             
        }
  }

  /*******************************************************************tasli7 droite*/
    else if ((!a&&b&&!c&&!d)||(a&&b&&!c&&d)) {
      int i=0;
      while((!a&&b&&!c&&!d)||(a&&b&&!c&&d)){
        i++;
          if(i>40)
          {
            i=40;
          }
        droite_taslih( consRight , consLeft,i );
        lecture();
            //*********************5edmit l code*****************/
            if(mission_number==1){
            if(f && (millis()-code_time_stamp>500)){ //xleft
              my_code=my_code+'1';
              code_time_stamp=millis();
            }
            else if(g && (millis()-code_time_stamp>500)){ //xright
              my_code=my_code+'0';
              code_time_stamp=millis();
            }
            }
            else if(mission_number==2){
            if(!f && (millis()-code_time_stamp>500)){ //xleft
              my_code=my_code+'1';
              code_time_stamp=millis();
            }
            else if(!g && (millis()-code_time_stamp>500)){ //xright
              my_code=my_code+'0';
              code_time_stamp=millis();
            }
            }
            //*********************5edmit l code*****************/
        /*4 k7ol*/
        if (a && b && c && d){ 
          ligne_horizontale();
        }
        /*fin 4 k7ol*/  
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
   else
   avant(consRight, consLeft); 
}
void suiveur2(){
  C=analogRead(RC);
  L=analogRead(RL);
  R=analogRead(RR);
  if(C>R && C>L){
    avant(60,60);
  }
  else if(R>C && R>L){
    droite();
  }
  else if(L>C && L>L){
    gauche();
  }
}
void send_to_server(int field_number){
    // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }

  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
  // pieces of information in a channel.  Here, we write to field 1.
  if(field_number==1){
  int x = ThingSpeak.writeField(myChannelNumber, 1, mission_code, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  }
  else if(field_number==2){
  int x = ThingSpeak.writeField(myChannelNumber, 2, my_code, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  }
  delay(15000); // Wait 15 seconds to update the channel again
}
void servo_count(){
    arreter();
    while(!free_to_go){
      if(servo_state=='U'){
        if(millis()-time_stamp>5000){
          free_to_go=true;
        }
        else if(capteur(500)){
          servo_state='D';
        }        
      }
      else if(servo_state=='D'){
        if(!capteur(500)){
          servo_state='U';
          up_number++;
          time_stamp=millis();
        }
      }
    }
    mission_state='F';
    my_code=String(up_number);
}
void ligne_horizontale(){
  arreter() ; 
  if(mission_number<4){
  if(mission_state=='S'){
    mission_number++;  
    if(mission_number==1)
    {
      mission_code=mission_one_code;
    }
    else if(mission_number==2)
    {
      mission_code=mission_two_code;
    }
    else if(mission_number==3)
    {
      mission_code=mission_three_code;
    }
    my_code="The Code is ";
    send_to_server(1);
    mission_state=='F';
  }
  else if(mission_state=='F'){
    send_to_server(2);  
    mission_state=='S';
  }
  }
  else if(mission_number==4)
  {
    my_code="Dark tunnel";
    send_to_server(2);
  }
  avant(consRight, consLeft);
  delay(1000);
}

/************************************************************ loop starts here ****************************************************/
/************************************************************ loop starts here ****************************************************/
/************************************************************ loop starts here ****************************************************/
void loop() {
  if(firstStop)
  {
    delay(2000);
    firstStop=false;
  }

  suiveur_IR();
  
}
