#include <SPI.h>

#include <Keypad.h>

#define RST_PIN         9          
#define SS_PIN          10    

int lock = 8;    
int button = A1;

int pos = 0;  
const byte numRows= 4; 
const byte numCols= 4; 


char keymap[numRows][numCols]= 
{
{'1', '2', '3', 'A'}, 
{'4', '5', '6', 'B'}, 
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};


byte rowPins[numRows] = {0,1,2,3}; 
byte colPins[numCols]= {4,5,6,7}; 

Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

void setup() 
{
  Serial.begin(9600);   
  SPI.begin();     
 
  pinMode(button,INPUT);
  
  pinMode(lock,OUTPUT);
}
void loop()
{
  
 
 
    Serial.println("KEYPAD");
    char num[10];
    char keypressed;
    int i=0;
    int flag=0;
    do
    {
      keypressed = myKeypad.getKey();
      if (keypressed != NO_KEY)
      {
        num[i]=keypressed;
        i++;
      }
    }while(keypressed!='#');
      i--;
      for(int j=0;j<i;j++)
      {
        Serial.println(num[j]);
      }
      if(num[0]=='1'&&i==1)
      {
        Serial.println("ACCESS GRANTED");
        digitalWrite(lock,HIGH);
        delay(5000);
        digitalWrite(lock,LOW);
       }
       else
       {
        Serial.println("ACCESS DENIED");
        digitalWrite(lock,LOW);  
        }
  } 
