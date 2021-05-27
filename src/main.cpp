/* IRremoteESP8266: IRsendDemo - demonstrates sending IR codes with IRsend.
 *
 * Version 1.1 January, 2019
 * Based on Ken Shirriff's IrsendDemo Version 0.1 July, 2009,
 * Copyright 2009 Ken Shirriff, http://arcfn.com
 *
 * An IR LED circuit *MUST* be connected to the ESP8266 on a pin
 * as specified by kIrLed below.
 *
 * TL;DR: The IR LED needs to be driven by a transistor for a good result.
 *
 * Suggested circuit:
 *     https://github.com/crankyoldgit/IRremoteESP8266/wiki#ir-sending
 *
 * Common mistakes & tips:
 *   * Don't just connect the IR LED directly to the pin, it won't
 *     have enough current to drive the IR LED effectively.
 *   * Make sure you have the IR LED polarity correct.
 *     See: https://learn.sparkfun.com/tutorials/polarity/diode-and-led-polarity
 *   * Typical digital camera/phones can be used to see if the IR LED is flashed.
 *     Replace the IR LED with a normal LED if you don't have a digital camera
 *     when debugging.
 *   * Avoid using the following pins unless you really know what you are doing:
 *     * Pin 0/D3: Can interfere with the boot/program mode & support circuits.
 *     * Pin 1/TX/TXD0: Any serial transmissions from the ESP8266 will interfere.
 *     * Pin 3/RX/RXD0: Any serial transmissions to the ESP8266 will interfere.
 *   * ESP-01 modules are tricky. We suggest you use a module with more GPIOs
 *     for your first time. e.g. ESP-12 etc.
 */
#include <M5StickCPlus.h> //0.0.2 https://github.com/m5stack/M5StickC-Plus
#include <Arduino.h> //default
#include <IRremoteESP8266.h> //2.7.18 https://github.com/crankyoldgit/IRremoteESP8266
#include <IRsend.h> //2.7.18 https://github.com/crankyoldgit/IRremoteESP8266

const uint16_t kIrLed = 9;  // ESP32 GPIO pin to use. M5StickC-Plus uses 9 for IR

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

// Example Sony TV captured from IRrecvDumpV2.ino
uint16_t rawData[155] = {2362, 632,  1162, 634,  562, 634,  1162, 632,  564, 636,  1160, 632,  566, 634,  562, 612,  1186, 634,  564, 634,  562, 636,  562, 634,  566, 25856,  2362, 630,  1166, 634,  562, 586,  1212, 634,  562, 628,  1170, 634,  564, 630,  566, 632,  1162, 636,  562, 634,  562, 634,  564, 634,  564, 25852,  2362, 632,  1164, 594,  602, 634,  1164, 636,  562, 634,  1162, 618,  580, 634,  562, 632,  1164, 634,  564, 626,  572, 632,  564, 632,  566, 25850,  2364, 630,  1164, 632,  566, 634,  1162, 634,  564, 634,  1162, 634,  564, 634,  564, 630,  1166, 632,  564, 636,  564, 632,  566, 632,  564, 25854,  2362, 634,  1162, 634,  562, 634,  1162, 634,  562, 634,  1164, 632,  564, 636,  562, 634,  1164, 634,  562, 636,  562, 632,  568, 632,  564, 25854,  2360, 634,  1164, 630,  566, 634,  1162, 632,  566, 632,  1166, 630,  566, 634,  564, 634,  1162, 632,  564, 634,  564, 634,  562, 634,  562};  // SONY A90


void setup() {
  M5.begin();
  irsend.begin();
#if ESP8266
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
#else  // ESP8266
  Serial.begin(115200, SERIAL_8N1);
#endif  // ESP8266
}

void loop() {
  if(digitalRead(M5_BUTTON_HOME) == LOW){
  Serial.println("NEC");
  M5.Lcd.println("Vizio");
  irsend.sendNEC(0x20DF10EF); //VIZIO TV
  delay(500);
  Serial.println("Sony");
  M5.Lcd.println("Sony");
  irsend.sendSony(0xa90, 12, 2);  // 12 bits & 2 repeats
  delay(1000);
//  Serial.println("raw");
//  M5.Lcd.println("raw");
//  irsend.sendRaw(rawData,155,38);
//  delay(2000);
  }
}