/****************************************************************************************  
**  This is example LINX firmware for use with the Arduino Uno with the serial 
**  interface enabled.
**
**  For more information see:           www.labviewmakerhub.com/linx
**  For support visit the forums at:    www.labviewmakerhub.com/forums/linx
**  
**  Written By Sam Kristoff
**
**  BSD2 License.
****************************************************************************************/

//Include All Peripheral Libraries Used By LINX
#include <SPI.h>
#include <Wire.h>
#include <EEPROM.h>
#include <Servo.h>
#include <dht.h>

//Include Device Specific Header From Sketch>>Import Library (In This Case LinxChipkitMax32.h)
//Also Include Desired LINX Listener From Sketch>>Import Library (In This Case LinxSerialListener.h)
#include <LinxArduinoMega2560.h>
#include <LinxSerialListener.h>
dht dht;

#define DHT11_PIN 49
//Create A Pointer To The LINX Device Object We Instantiate In Setup()
LinxArduinoMega2560* LinxDevice;

//Initialize LINX Device And Listener
int DHT();
void setup()
{
  //Instantiate The LINX Device
  LinxDevice = new LinxArduinoMega2560();
  
  //The LINXT Listener Is Pre Instantiated, Call Start And Pass A Pointer To The LINX Device And The UART Channel To Listen On
  LinxSerialConnection.Start(LinxDevice, 0); 
  LinxSerialConnection.AttachCustomCommand(0, DHT); 
}

void loop()
{
  //Listen For New Packets From LabVIEW
  LinxSerialConnection.CheckForCommands();
 
}

int DHT(unsigned char numInputBytes, unsigned char* input, unsigned char* numResponseBytes, unsigned char* response)
{
  int chk = dht.read11(DHT11_PIN);
  response[0]=(float)dht.humidity;
  response[1]=(float)dht.temperature;
  *numResponseBytes=2;
   
  //*response=sensor reading; //for single byte data
  //*response=(unsigned char) sensor readings;
  delay(500);//for stability of sensor
  
}
