#include<LiquidCrystal.h>       //it preposesor deractive for LCD 16X2
LiquidCrystal lcd(2,3,4,5,6,7); //we are  assigning digital pins for lcd

#define echo_s1 A0 // to define global variable for assinging analog pins to A0,A1,A2,A3
#define trigg_s1 A1  
#define echo_s2 A2  
#define trigg_s2 A3 

int relay = 8;  // at pin no 8 of analog pin of ardiuno for interfacing relay chhater
long dis_a=0,dis_b=0; // assing long 
int flag1=0, flag2=0; // assing temp variables for counting human presence
int person = 0; // to initialize person 0 for not get ddefualt values 

//we create function for read values of sound waves of Ultrasonic sensors

void ultra_read(int pi_t,int pi_e,long &ultra_time){
long time;
pinMode(pi_t,OUTPUT);
pinMode(pi_e,INPUT);
digitalWrite(pi_t,LOW);
delayMicroseconds(2);
digitalWrite(pi_t,HIGH);
delayMicroseconds(10);
time=pulseIn (pi_e,HIGH);// it reads a pulse of High or Low
ultra_time =  time / 29 / 2; // by using speed of sound formula 
}

void setup(){
  Serial.begin(9600); // initialize serial communication at 9600 bits per second:
  pinMode(relay, OUTPUT); //
  lcd.begin(16, 2); //
  lcd.setCursor(0, 0);//its print string
  lcd.print("     Welcome    ");
  //delay(1000); // Waiting for a while
  lcd.clear(); 
}

void loop(){ 
   
      ultra_read(trigg_s1,echo_s1,dis_a);
      //delay(30);
      ultra_read(trigg_s2,echo_s2,dis_b);
      //delay(30);
   
      Serial.print("da:");
      Serial.println(dis_a);
      Serial.print("db:");
      Serial.println(dis_b);   

      // we ce

      if(dis_a<90 && flag1==0)
      {
        flag1=1;
        if(flag2==0)
        {
          person = person+1;
        }
      }

      if(dis_b<90 && flag2==0)
      {
        flag2=1;
        if(flag1==1)
        {
          person = person-1;
        }
      }

      if(dis_a>90 && dis_b>90 && flag1==1 && flag2==1)
      {
        flag1=0, flag2=0;
        //delay(1000); 
      }

      lcd.setCursor(0, 0); // its actully is that is lcd setcursur(col,row)
      lcd.print("Have Person: ");
      lcd.print(person);
      lcd.print("  ");
      lcd.setCursor(0,1); 
      lcd.print("Light is :");

    if(person>0)
    {
      digitalWrite(relay,LOW); 
      lcd.print("On ");
    }
    else
    {
      digitalWrite(relay,HIGH); 
      lcd.print("Off");
    }
}
