#include <SPI.h>
#include <MFRC522.h>
#include <Keypad.h>

#define RST_PIN         9          
#define SS_PIN          10    

int lock = 8;    

void(* resetFunc) (void) = 0;

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
int pos = 0;  





void setup() 
{
  Serial.begin(9600);   
  SPI.begin();     
  mfrc522.PCD_Init();   
 
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
 
  pinMode(lock,OUTPUT);
}
void loop()
{
 
   
   if ( mfrc522.PICC_IsNewCardPresent()) {
      
  
  mfrc522.PICC_ReadCardSerial();
  
  


//A9 3E D6 2A - Code of the rfid tag

  String card1=String(mfrc522.uid.uidByte[0],HEX)+ String(mfrc522.uid.uidByte[1],HEX)+String(mfrc522.uid.uidByte[2],HEX)+String(mfrc522.uid.uidByte[3],HEX);
  String val = String(169,HEX)+String(62,HEX)+String(214,HEX)+String(42,HEX);
  if(card1 == val)
  {
    Serial.println("ACCESS GRANTED");
    digitalWrite(lock,HIGH);
     
    delay(5000);
    digitalWrite(lock,LOW);
     resetFunc();
    
  }
   else
   {
      digitalWrite(lock,LOW);
      Serial.print("ACCESS DENIED");
   }
    }
}
