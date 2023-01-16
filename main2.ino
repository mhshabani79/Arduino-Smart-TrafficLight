//#include <LiquidCrystal.h>
#include <Keypad.h>
#include <string.h>
#include <stdio.h>
#include <LiquidCrystal.h>


const int rs = 9, en = 8, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int timer=17;
int state=1;
int crowd1, crowd2, crowd3;
int serin=0;

void setup() {
  Serial.begin(9600); 
  lcd.begin(16, 2);
  lcd.print("A:");
  lcd.setCursor(0, 1);
  lcd.print("B:");
}

void loop() 
{
  if (Serial.available() > 0)
    serin = Serial.read();
  if( serin==1 || serin==2 || serin==3)
    state = serin;
    
  if(state == 1)
  {
    timer--;
    if(timer==0)
      timer = 16;  
  }
  else if(state == 2)
  {
    
    crowd1 = analogRead(A0);
    crowd2 = analogRead(A1);
    crowd3 = analogRead(A2);
    if( (crowd1>crowd3 || crowd2>crowd3) && timer==11 )
      timer = timer;
    else if( (crowd3>crowd1 && crowd3>crowd2) && timer==4 )
      timer = timer;
    else
      {
        timer--;
        if(timer==0)
          timer = 16;
      }
  }
  else if(state == 3)
  {
    if(serin==33)
    {
      if(timer>=10)
        timer=10;
      else if(timer<8)
        timer=3;
    serin=0;
    }
    timer--;
    if(timer==0)
      timer = 16;
  }
  
  delay(100);
  show();
}



void show(void)
{
  if(timer>=10)
  {
      lcd.setCursor(2, 0);
      lcd.print("Green- ");
      lcd.print(timer-9);
      lcd.setCursor(2, 1);
      lcd.print("Red-   ");
      lcd.print(timer-9); 
  }
  else if( timer<10 && timer>=8)
  {
      lcd.setCursor(2, 0);
      lcd.print("Yellow-");
      lcd.print(timer-7);
      lcd.setCursor(2, 1);
      lcd.print("Yellow-");
      lcd.print(timer-7);  
  }
  else if( timer<8 && timer>2 )
  {
      lcd.setCursor(2, 0);
      lcd.print("Red-   ");
      lcd.print(timer-2);
      lcd.setCursor(2, 1);
      lcd.print("Green- ");
      lcd.print(timer-2);  
  }
    else if( timer<=2)
  {
      lcd.setCursor(2, 0);
      lcd.print("Yellow-");
      lcd.print(timer);
      lcd.setCursor(2, 1);
      lcd.print("Yellow-");
      lcd.print(timer); 
}
}
