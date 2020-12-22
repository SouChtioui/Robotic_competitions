
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 12
int frequency = 0;
boolean red=false;
void setup() {
  // put your setup code here, to run once:
  pinMode(9,OUTPUT);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

    digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  digitalWrite(9,LOW);
   Serial.begin(9600);
}


int rouge()
 {int red,green,blue;
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequency = map(frequency, 25,72,255,0);
  red=frequency;
  // Printing the value on the serial monitor
  /*Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(10);*/
// Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequency = map(frequency, 30,90,255,0);
  green =frequency;
  // Printing the value on the serial monitor
  /*Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(10);*/
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequency = map(frequency, 25,70,255,0);
  blue=frequency;
  // Printing the value on the serial monitor
  /*Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");
  delay(10);*/
 if((red>green)&&(red>blue)&&(green<0)&&(blue<0))
  return(1);
 else return(0);
 }

void loop() {  
  int i=0;
    for(int j=0;j<2;j++)
    {
      if(rouge()==1)
      {
      i++;
      }
    }
    if (i==2)
    {
       digitalWrite(9,HIGH);
       Serial.println("a7mer");
    }
  /*else{ 
    digitalWrite(9,LOW);
    Serial.println("mahouch a7mer");
  }*/
}
