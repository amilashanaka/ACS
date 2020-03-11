// demo: CAN-BUS Shield, send data
#include <mcp_can.h>
#include <SPI.h>

// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 10;

MCP_CAN CAN(SPI_CS_PIN);  // Set CS pin
// PORT INPUT
//int TRIM_PORT_UP = 31;
//int TRIM_PORT_DOWN = 33;
//int TRIM_STB_UP = 35;
//int TRIM_STB_DOWN = 37;
//int STEERING_PORT = 39;
//int STEERING_STB = 41;

//int buttonState_TPU =0;
//int buttonState_TPD =0;
//int buttonState_TSU =0;
//int buttonState_TSD =0;
//int buttonState_SP =0;
//int buttonState_SS =0;

//int sensorValue1 = 126;
//int sensorValue2 = 126;
//int sensorValue3 = 128;
//
//int increment_speed = 2;

// BUTTON CMD
int FU_NFU_ST = 22;
int PORT_STB = 24;
int TRIM_UP = 26;
int TRIM_DOWN = 28;
int ALARM_ATK = 30;
int FU_NFU_TRIM = 32;
int TAKE_CMND = 34;
int MAN_AUTO = 36;

int buttonState_FNS =0;
int buttonState_PS =0;
int buttonState_TU =0;
int buttonState_TD =0;
int buttonState_AA =0;
int buttonState_FNT =0;
int buttonState_TC =0;
int buttonState_MA =0;

void setup()
{
//  pinMode(TRIM_PORT_UP, INPUT);
//  pinMode(TRIM_PORT_DOWN, INPUT);
//  pinMode(TRIM_STB_UP, INPUT);
//  pinMode(TRIM_STB_DOWN, INPUT);
//  pinMode(STEERING_PORT, INPUT);
//  pinMode(STEERING_STB, INPUT);
  
  pinMode(FU_NFU_ST,INPUT);
  pinMode(PORT_STB,INPUT);
  pinMode(TRIM_UP,INPUT);
  pinMode(TRIM_DOWN,INPUT);
  pinMode(ALARM_ATK,INPUT);
  pinMode(FU_NFU_TRIM,INPUT);
  pinMode(TAKE_CMND,INPUT);
  pinMode(MAN_AUTO,INPUT);
  Serial.begin(115200);

START_INIT:

  if (CAN_OK == CAN.begin(CAN_100KBPS))                  // init can bus : baudrate = 100k
  {
    Serial.println("CAN BUS Shield init ok!");
  }
  else
  {
    Serial.println("CAN BUS Shield init fail");
    Serial.println("Init CAN BUS Shield again");
    delay(100);
    goto START_INIT;
  }
}

unsigned char stmp0[2] = {0, 0};
unsigned char stmp1[4] = {0, 192, 0, 16};
unsigned char stmp2[2] = {0, 2};
unsigned char stmp3[2] = {0, 20};
//unsigned char stmp4[8] = {5, 0, 5, 128, 6, 126, 6, 126}; // 5,unknown,5,wheel,6,stb_trim,6,port_trim
unsigned char stmp5[4] = {5, 31, 5, 237};
unsigned char stmp6[2] = {8, 40};
unsigned char cmd0[1] = {0};
unsigned char cmd1[1] = {1};

void loop()
//NFU CTRL
{
//  buttonState_TPU = digitalRead(TRIM_PORT_UP);
//    if ( buttonState_TPU == LOW ) {
//    sensorValue1 = sensorValue1 + increment_speed;
//    }
//  buttonState_TPD = digitalRead(TRIM_PORT_DOWN);
//    if ( buttonState_TPD == LOW ) {
//    sensorValue1 = sensorValue1 - increment_speed;
//    }
//    if ( sensorValue2 == 255 ) {
//    sensorValue1 = 255;
//    }
//    if ( sensorValue2 == 0 ) {
//    sensorValue1 = 0;
//    }
//    
//  buttonState_TSU = digitalRead(TRIM_STB_UP);
//    if ( buttonState_TSU == LOW ) {
//    sensorValue2 = sensorValue2 + increment_speed;
//    }
//  buttonState_TSD = digitalRead(TRIM_STB_DOWN);
//    if ( buttonState_TSD == LOW ) {
//    sensorValue2 = sensorValue2 - increment_speed;
//    }
//    if ( sensorValue3 == 255 ) {
//    sensorValue2 = 255;
//    }
//    if ( sensorValue3 == 0 ) {
//    sensorValue2 = 0;
//    }
//    
//   buttonState_SP = digitalRead(STEERING_PORT);
//    if ( buttonState_SP == LOW ) {
//    sensorValue3 = sensorValue3 + increment_speed;
//    }
//  buttonState_SS = digitalRead(STEERING_STB);
//    if ( buttonState_SS == LOW ) {
//    sensorValue3 = sensorValue3 - increment_speed;
//    }
//    if ( sensorValue2 == 255 ) {
//    sensorValue3 = 255;
//    }
//    if ( sensorValue2 == 0 ) {
//    sensorValue3 = 0;
//    } 
  // print out the value you read:
//  Serial.print(sensorValue1);
//  Serial.print(",");
//  Serial.print(sensorValue2);
//  Serial.print(",");
//  Serial.println(sensorValue3);
//  Serial.println(",");
//  Serial.println(sensorValue3);
//  Serial.println(",");
 
 //BUTTON CTRL
 
  
  buttonState_FNS = digitalRead(FU_NFU_ST);
  if (buttonState_FNS == LOW) {     
  CAN.sendMsgBuf(0x120, 0, 1, cmd0);
  Serial.println("FU_NFU_ST");  
  } 
  delay(20);
  buttonState_PS = digitalRead(PORT_STB);
  if (buttonState_PS == LOW) {     
  CAN.sendMsgBuf(0x121, 0, 1, cmd0); 
  Serial.println("PORT_STB");  
  } 
  delay(20);
  buttonState_TU = digitalRead(TRIM_UP);
  if (buttonState_TU == LOW) {     
  CAN.sendMsgBuf(0x129, 0, 1, cmd0); 
  Serial.println("TRIM_UP");  
  }
  delay(20); 
  buttonState_TD = digitalRead(TRIM_DOWN);
  if (buttonState_TD == LOW) {     
  CAN.sendMsgBuf(0x12A, 0, 1, cmd0); 
  Serial.println("TRIM_DOWN");  
  } 
  delay(20);
  buttonState_AA = digitalRead(ALARM_ATK);
  if (buttonState_AA == LOW) {     
  CAN.sendMsgBuf(0x128, 0, 1, cmd0);
  Serial.println("ALARM_ATK");  
  } 
  delay(20);
  buttonState_FNT = digitalRead(FU_NFU_TRIM);
  if (buttonState_FNT == LOW) {     
  CAN.sendMsgBuf(0x122, 0, 1, cmd0);
  Serial.println("FU_NFU_TRIM");  
  } 
  delay(20);
  buttonState_TC = digitalRead(TAKE_CMND);
  if (buttonState_TC == LOW) {     
  CAN.sendMsgBuf(0x126, 0, 1, cmd0);
  //CAN.sendMsgBuf(0x050, 0, 1, cmd1);
  Serial.println("TAKE_CMND");
  } 
  delay(20);
  buttonState_MA = digitalRead(MAN_AUTO);
  if (buttonState_MA == LOW) {     
  CAN.sendMsgBuf(0x126, 0, 1, cmd1); 
  Serial.println("MAN_AUTO");  
  }
  delay(20); 
  
 
  // send data:  id = 0x00, standrad flame, data len = 8, stmp: data buf
 //unsigned char stmp4[8] = {5, 128, 5, sensorValue3, 6, sensorValue2, 6, sensorValue1};
//  unsigned char stmp5[4] = {6, sensorValue1, 6, sensorValue2};
//  unsigned char stmp6[2] = {8, sensorValue1};
    
  CAN.sendMsgBuf(0x006, 0, 2, stmp0);
  
  CAN.sendMsgBuf(0x011, 0, 4, stmp1);
  
  CAN.sendMsgBuf(0x182, 0, 2, stmp2);
 
  CAN.sendMsgBuf(0x183, 0, 2, stmp3);
 
  //CAN.sendMsgBuf(0x010, 0, 8, stmp4); // rudder value
                        // send data per 100ms
  CAN.sendMsgBuf(0x005, 0, 4, stmp5);
                        // send data per 100ms
  CAN.sendMsgBuf(0x002, 0, 2, stmp6);
  delay(150);                       // send data per 100ms
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
