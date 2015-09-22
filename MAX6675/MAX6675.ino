
#include <SPI.h>
#define SS_PIN (10)
//#define DEBUG_EN
void setup()
{
    Serial.begin(9600);
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV32);
    pinMode(SS_PIN,OUTPUT);
    digitalWrite(SS_PIN, HIGH);
     
}

void loop()
{
    uint16_t temperature=0;
    uint8_t buffer[2];

    digitalWrite(SS_PIN, LOW);
    buffer[0]=SPI.transfer(0xaa);
    buffer[1]=SPI.transfer(0xaa);
    digitalWrite(SS_PIN, HIGH);

    temperature = (buffer[0]&0x7F);
    temperature = temperature<<8;
    temperature &= 0xff00;
    temperature |= (buffer[1]>>3);
    Serial.println("***************");
#ifdef DEBUG_EN
    Serial.print("B0-B7 ");
    Serial.println(buffer[1],HEX);
    Serial.print("B8-B15 ");
    Serial.println(buffer[0],HEX);
#endif

    if ((buffer[1]&0x04)!=0) {
        Serial.println("!!!!!Thermocouple OPEN!!!!!");
        Serial.println("Following reading may be invalid");
    }
    Serial.print("Ambient Temperature is ");
    Serial.println((float)temperature*1024/32768,DEC);
    Serial.println("***************");
  
    delay(1000);
  
  
}
