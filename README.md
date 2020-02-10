# dumprom

A quick Arduino sketch to dump parallel PROM chips.

## Summary

This is for dumping things like 2716, 2732, 2764, 27128, and 27256 PROM chips.

## Requirements

* An Arduino with enough pins. I used a Mega 2560 because it's loaded with pins. You basically need 8 pins for the address lines, and then however many pins for the data lines, depending on what size of ROM you're dumping.

## How

Easiest solution is to stick the PROM in a solderless breadboard, then wire to your Arduino roughly as follows:

* Wire A0..An to free pins on the Arduino.
* Wire D0..D7 to free pins on the Arduino.
* Wire Vcc to the Arduino +5V.
* Wire GND to the Arduino GND.
* Other lines may vary slightly. Generally, if there's something a Vpp or PGM line, you want to pull that to 5V. (23xx chips won't have this)
* Some of the higher-capacity chips don't have an explicit Vpp or PGM, and enter programming mode by some sort of pulse on another line. Since we're explicitly pulling those lines one way or the other, this should be fine.
* Then there will be some CE, CS, and/or OE lines. Usually you want to pull these to GND.
* Some chips are active-high, not active-low. I think active-low is usually the most common since the CMOS days, but the older you get, the more likely it is you'll run into an active-high chip.
* Best thing is, if you can, look at the schematic of the device hosting the ROM to see how the pins are used.

Based on what pins you used, modify the array of pin numbers in the source code before you run it. Also, modify CHIPTYPE depending on what type of chip you have.

## Why?

I wanted to dump the ROMs from my Apple IIe and some of its peripherals. I was also able to dump ROMs from some of my Laser 128 collection.
