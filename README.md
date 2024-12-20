This Code is for a ATtiny85 to control the backlight on an LCD screen on a vintage notebook. The LCD backlight was driven by a high voltage fluorescent tube. The tube needs more energy and was dim over the time. You can remove the tube and replace it by a LED string. This LED string will powered by 5 or 12V. To use the old potentiometer to control the brightness of the backlight we use pulse width modulation (PWM) and the ATtiny.

The chip needs the following:
- a logic input to enable/disable the backlight (this is driven by the computer)
- a analog input for the brighness potentiometer
- a PWM output to drive a transitor or MOSFET

You can also use a NE555 as PWM driver. The good thing is, you can drive the NE555 with 12V and drive the LED backlight directly from the chip output. But this chip needs some external components and needs more power consumtion if the backlight is dark as the backlight is in full bright. Example:

I use a 12V LED strip that needs 17,8mA. With the NE555 in full bright the chip an the LED needs 18mA (216mW). With darkes mode the chip an the LED needs 21,1mA (253mW).
Thats a little bit strange and you dont have any engery saving with a dark backlight. It's completely opposit. You need more energy with a dark backlight.
That's the reason that i use the ATtiny85 for this job.


The ATtiny85 needs only for the chip with a 10k Ohm potentiometer a maximum of 2,7mA and in the sleep mode (backlight disabled) 0,57mA. The potentiometer with 10k Ohm eats some current (5V / 10k = 0,5mA). The chip him self needs only 0,13mA in sleep mode. That can be better, but i think i have all options in place.

Wih the same example from above, with a 12V 17,8mA LED strip we have this result:

The chip with the 10k Ohm potentiometer and 5V needs in dark = 2,08mA, in middle = 2,76mA and in full bright 2,16mA.

The LED strip with 12V needs in dark = 0mA, in middle = 8,71mA and in full bright = 17,8mA.

Together we have a power consumtion from dark = 10,4mW, in middle = 118mW and in full bright = 224,4mW.

Thats more the result of a PWM power consumtion that we looking for, and the PWM is more accurat. It starts from zero (all off) up to 100% full bright. We can adjust this as we need in code.


The backlight enable signal can have no potential or high to enable the backlight. If you not connect the pin the backliht is on. Only if the pin is low (ground) the backlight will ne disabled and the chip go in to deep sleep. They will wake up if the signal change to high.

The simple schematic for this project (now with a 1M Ohm potentiometer):
![schematics/Backlight-Schematic.png](https://github.com/Sebastian-gthb/ATtiny85-Backlight-PWM/blob/main/schematics/Backlight-Schematic.png)
