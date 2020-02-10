// Quick sketch to dump parallel PROM chips.
// Copyright 2020, by Renee Harke.
// MIT license, see LICENSE file.

// This works for things like 2716, 2732, 2764, 27128, and 27256 PROM chips.
// Actually I've only tested it on 27128 and 27256 chips, but I see no reason it wouldn't
// work on the others if you get the pin mappings correct.

// Output is given as hex strings rather than raw binary data. I did this so that I could
// just copy and paste it out of the Arduino serial monitor. If you do that and then paste
// into Hex Fiend and save, you'll get the raw data. You could modify this if you have
// other needs...

// How to wire:
//
//  * Wire A0..An to free pins on the Arduino.
//  * Wire D0..D7 to free pins on the Arduino.
//  * Wire Vcc to the Arduino +5V.
//  * Wire GND to the Arduino GND.
//
//  * Other lines may vary slightly. Generally, if there's something a Vpp or PGM line,
//    you want to pull that to 5V. (23xx chips won't have this)
//  * Some of the higher-capacity chips don't have an explicit Vpp or PGM, and enter
//    programming mode by some sort of pulse on another line. Since we're explicitly
//    pulling those lines one way or the other, this should be fine.
//  * Then there will be some CE, CS, and/or OE lines. Usually you want to pull these to
//    GND.
//  * Some chips are active-high, not active-low. I think active-low is usually the most
//    common since the CMOS days, but the older you get, the more likely it is you'll run
//    into an active-high chip.
//  * Best thing is, if you can, look at the schematic of the device hosting the ROM to
//    see how the pins are used.

// Type of chip we're working with. Change for your needs.
#define CHIPTYPE 27256

// Convert chip type into number of bits (address lines) and the resultant size of the ROM.
// CHIPSIZE is 2^CHIPBITS but there aren't enough chip types to not just hardcode for now.
#if CHIPTYPE==2316 || CHIPTYPE==2716
# define CHIPBITS 11
# define CHIPSIZE 2048
#elif CHIPTYPE==2332 || CHIPTYPE==2732
# define CHIPBITS 12
# define CHIPSIZE 4096
#elif CHIPTYPE==2364 || CHIPTYPE==2764
# define CHIPBITS 13
# define CHIPSIZE 8192
#elif CHIPTYPE==27128
# define CHIPBITS 14
# define CHIPSIZE 16384
#elif CHIPTYPE==27256
# define CHIPBITS 15
# define CHIPSIZE 32768
#else
# error Unsupported chip type
#endif

// Pins to use for address and data lines.
// I used an Arduino Mega 2560 and the block of pins down the right-hand side of the board.
static const int ADDR[] = { 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 44 };
static const int DATA[] = { 36, 37, 38, 39, 40, 41, 42, 43 };

void setup() {
  for (int i = 0; i < CHIPBITS; ++i) {
    pinMode(ADDR[i], OUTPUT);
  }
  for (int i = 0; i < 8; ++i) {
    pinMode(DATA[i], INPUT);
  }

  Serial.begin(115200);
  while (!Serial);
  Serial.println("-- Begin --");

  char hexbuf[3] = { 0 };
    
  for (long i = 0; i < CHIPSIZE; ++i) {
    if (i > 0 && i % 64 == 0) {
      Serial.println("");
    }

    for (int j = 0; j < CHIPBITS; ++j) {
      digitalWrite(ADDR[j], bitRead(i, j));
    }
    delayMicroseconds(1);
    
    int data = 0;
    for (int j = 0; j < 8; ++j) {
      bitWrite(data, j, digitalRead(DATA[j]));
    }

    sprintf(hexbuf, "%.2X", data);
    Serial.print(hexbuf);
  }
  Serial.println("");
  Serial.println("-- Complete --");
}

void loop() {
  // Nothing to do here.
}
