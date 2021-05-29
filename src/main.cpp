#include <M5StickCPlus.h> //0.0.2 https://github.com/m5stack/M5StickC-Plus
#include <Arduino.h> //default
#include <IRremoteESP8266.h> //2.7.18 https://github.com/crankyoldgit/IRremoteESP8266
#include <IRsend.h> //2.7.18 https://github.com/crankyoldgit/IRremoteESP8266
#include <logo.h> 

static int menupos = 1;
const uint16_t kIrLed = 9;  // ESP32 GPIO pin to use. M5StickC-Plus uses 9 for IR
IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

// Example Sony TV captured from IRrecvDumpV2.ino
//uint16_t rawData[155] = {2362, 632,  1162, 634,  562, 634,  1162, 632,  564, 636,  1160, 632,  566, 634,  562, 612,  1186, 634,  564, 634,  562, 636,  562, 634,  566, 25856,  2362, 630,  1166, 634,  562, 586,  1212, 634,  562, 628,  1170, 634,  564, 630,  566, 632,  1162, 636,  562, 634,  562, 634,  564, 634,  564, 25852,  2362, 632,  1164, 594,  602, 634,  1164, 636,  562, 634,  1162, 618,  580, 634,  562, 632,  1164, 634,  564, 626,  572, 632,  564, 632,  566, 25850,  2364, 630,  1164, 632,  566, 634,  1162, 634,  564, 634,  1162, 634,  564, 634,  564, 630,  1166, 632,  564, 636,  564, 632,  566, 632,  564, 25854,  2362, 634,  1162, 634,  562, 634,  1162, 634,  562, 634,  1164, 632,  564, 636,  562, 634,  1164, 634,  562, 636,  562, 632,  568, 632,  564, 25854,  2360, 634,  1164, 630,  566, 634,  1162, 632,  566, 632,  1166, 630,  566, 634,  564, 634,  1162, 632,  564, 634,  564, 634,  562, 634,  562};  // SONY A90

void handleScreen(){
M5.Lcd.pushImage(0, 0, imgWidth, imgHeight, img);
M5.Lcd.setCursor(40, 10);
M5.Lcd.setTextSize(2); //Every newline is 16 px
M5.Lcd.setTextColor(WHITE);
M5.Lcd.setTextColor(RED);
M5.Lcd.println("M5 IR");
M5.Lcd.setTextColor(WHITE);
}

void clearcircles(){
  M5.Lcd.drawCircle(12,48,6,BLACK); //#1
  M5.Lcd.drawCircle(12,48+32,6,BLACK); //#2
  M5.Lcd.drawCircle(12,48+64,6,BLACK); //#3
}

// Display the menu options
void setMenu(){
  M5.Lcd.println("");
  M5.Lcd.println("  Power\n");
  M5.Lcd.println("  Vol Up\n");
  M5.Lcd.println("  Vol Down");
}

void selector(){
  switch (menupos)
  {
  case 1: //power
    M5.Lcd.drawCircle(12,48,6,CYAN);
    break;
  
  case 2: //vol up
    clearcircles();
    M5.Lcd.drawCircle(12,48+32,6,CYAN);
    break;
  
  case 3: //vol down
    clearcircles();
    M5.Lcd.drawCircle(12,48+64,6,CYAN);
    break;
  
  default:
    break;
  }
}

void setup() {
  M5.begin();
  M5.IMU.Init();
  pinMode(M5_LED, OUTPUT); //give power to LED
  digitalWrite(M5_LED, HIGH); //Turn the LED itself off
  M5.Axp.ScreenBreath(8); //low power display dimming
  irsend.begin();
  digitalWrite(9, HIGH); //fix for IR LED staying on. force it to be off
  Serial.begin(115200, SERIAL_8N1);
  M5.Lcd.fillScreen(0x8631); //set the bg color to match the image's background for *transparent* text
  handleScreen();
  setMenu();
  clearcircles();
  selector();
  //M5.Lcd.drawCircle(12,48,6,CYAN); //#1
  //M5.Lcd.drawCircle(12,48+32,6,CYAN); //#2
  //M5.Lcd.drawCircle(12,48+64,6,CYAN); //#3
}

void loop() {
  if(digitalRead(M5_BUTTON_HOME) == LOW){
    menupos++;
    if(menupos>3){
      menupos = 1;
      clearcircles();
    }
    selector();
    Serial.println(menupos);
    delay(250);
  }
}