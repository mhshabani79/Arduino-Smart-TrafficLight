//#include <LiquidCrystal.h>
#include <Keypad.h>
#include <string.h>
#include <stdio.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20,16,2);

//const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const byte ROWS = 4; 
const byte COLS = 3;

char hexaKeys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {7, 6, 5, 4}; 
byte colPins[COLS] = {A0, A1, A2};

char inkey;
char pass[5];
char master[5]="2021";
int ledg = 12, ledr = 13, change_button = 11;
int change_en=0;
int state=1;
int i=0;
Keypad keypad34 = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
void setup() {
  pinMode(ledg, OUTPUT);
  pinMode(ledr, OUTPUT);
  pinMode(change_button, INPUT);
  pinMode(10, INPUT);
  pinMode(9, INPUT);
  pinMode(8, INPUT);
  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), police, RISING);
  Serial.begin(9600);
  lcd.init();  
  //lcd.begin(16, 2);
  lcd.print("State : ");
  lcd.setCursor(8, 0);
  lcd.print(state);
}

void loop() 
{
  change_en = 0;
  if(digitalRead(change_button))
    inputkey();

  if(change_en)
  {
    state = digitalRead(10) + digitalRead(9)*2 + digitalRead(8)*3;
    lcd.setCursor(8, 0);
    lcd.print(state);
    Serial.write(state); 
  }

}

void inputkey(void)
{
    lcd.setCursor(0, 1);
   for(i=0; i<4; i++)
   {
        
       inkey = keypad34.waitForKey();
       if(inkey == '#')
       {
            lcd.setCursor(0, 1);
            lcd.print("Cancelling...");
            delay(50);
            lcd.setCursor(0, 1);
            lcd.print("                ");
            return;
       }
       else if(inkey == '*')
       {
         digitalWrite(ledg, 1);
         digitalWrite(ledr, 1);
         delay(50);
         digitalWrite(ledg, 0);
         digitalWrite(ledr, 0);
    
         lcd.setCursor(0, 1);
         lcd.print("Enter Master Pas");
         delay(100);
         lcd.setCursor(0, 1);
         lcd.print("                ");
    
         lcd.setCursor(0, 1);
    
        for(i=0; i<4; i++)
        {
         inkey = keypad34.waitForKey();
         if(inkey == '#')
         {
            lcd.setCursor(0, 1);
            lcd.print("Cancelling...");
            delay(100);
            lcd.setCursor(0, 1);
            lcd.print("                ");
            return;
         }
         else pass[i] = inkey;
         lcd.print(pass[i]);
        }
    
        if(!strcmp(pass, master))
        {
          lcd.setCursor(0, 1);
          lcd.print("Enter New Pass");
          delay(100);
          lcd.setCursor(0, 1);
          lcd.print("                ");
          lcd.setCursor(0, 1);
    
          for(i=0; i<4; i++)
          {
          inkey = keypad34.waitForKey();
          if(inkey == '#')
          {
            lcd.setCursor(0, 1);
            lcd.print("Cancelling...");
            delay(50);
            lcd.setCursor(0, 1);
            lcd.print("                ");
            return;
          }
          else pass[i] = inkey;
          lcd.print(pass[i]);
          if(i==3)
          {
            digitalWrite(ledg, 1);
            digitalWrite(ledr, 1);
            delay(50);
            digitalWrite(ledg, 0);
            digitalWrite(ledr, 0);
            delay(50);
            digitalWrite(ledg, 1);
            digitalWrite(ledr, 1);
            delay(50);
            digitalWrite(ledg, 0);
            digitalWrite(ledr, 0);
            delay(50);
            digitalWrite(ledg, 1);
            digitalWrite(ledr, 1);
            delay(50);
            digitalWrite(ledg, 0);
            digitalWrite(ledr, 0); 
          }
          else
          {
            digitalWrite(ledr, 1);
            delay(50);
            digitalWrite(ledr, 0);  
          }
          }
        strcpy(master, pass);
        lcd.setCursor(0, 1);
        lcd.print("Password Changed");
        delay(50);
        lcd.setCursor(0, 1);
        lcd.print("                ");
        return;
        }
        else
        {
         lcd.setCursor(0, 1);
         lcd.print("Wrong Password");
         delay(50);
         lcd.setCursor(0, 1);
        lcd.print("                ");
         return; 
        }   
       }
       else
       {
       pass[i] = inkey;
       lcd.print("*");
       }
  }
  if(!strcmp(master, pass))
  {
        lcd.setCursor(0, 1);
        lcd.print("Ready for change");
        digitalWrite(ledg, 1);
        delay(50);
        digitalWrite(ledg, 0);
        delay(50); 
        digitalWrite(ledg, 1);
        delay(50);
        digitalWrite(ledg, 0);
        delay(50); 
        digitalWrite(ledg, 1);
        delay(50);
        digitalWrite(ledg, 0);
        delay(50);
        lcd.setCursor(0, 1);
        lcd.print("                 ");
        change_en = 1;
        return;
  }
  else
  {
        lcd.setCursor(0, 1);
        lcd.print("Invalid Password");
        digitalWrite(ledr, 1);
        delay(50);
        digitalWrite(ledr, 0);
        delay(50) ;
        digitalWrite(ledr, 1);
        delay(50);
        digitalWrite(ledr, 0); 
        delay(50);
        digitalWrite(ledr, 1);
        delay(50);
        digitalWrite(ledr, 0);
        delay(50);
        lcd.setCursor(0, 1);
        lcd.print("                 ");
        change_en = 0;
        return;
  }
}

void police(void)
{
  if(state == 3)
  {
    Serial.write(33);
  }
}
