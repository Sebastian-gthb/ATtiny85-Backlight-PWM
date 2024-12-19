This Code is for a ATtiny85 to control the backlight on an LCD screen on a vintage notebook. The LCD backlight was driven by a high voltage fluorescent tube. The tube needs more energy and was dim over the time. You can remove the tube and replace it by a LED string. This LED string will powered by 5 or 12V. To use the old potentiometer to control the brightness of the backlight we use pulse width modulation (PWM) and the ATtiny.

The chip needs the following:
- a logic input to enable/disable the backlight (this is driven by the computer)
- a analog input for the brighness potentiometer
- a PWM output to drive a transitor or MOSFET

You can also use a NE555 as PWM driver. The good thing is, you can drive the NE555 with 12V and drive the LED backlight directly from the chip output. But this chip needs some external components and needs more power consumtion if the backlight is dark as the backlight is in full bright. Thats a little bit strange and you dont have any engery saving with a dark backlight. It's completely opposit. You need more energy with a dark backlight.
That's the reason that i use the ATtiny85 for this job.

The ATtiny85 needs only for the chip with a 10k Ohm potentiometer a maximum of 2,7mA and in the sleep mode (backlight disabled) 0,9mA. It can be better, but thats the first version. After enhancement of the sleep mode (adding deactivating ADC and disabling brown-out detection in sleep mode) the chip needs only 0,13mA and with the 10k Ohm potentiometer 0,57mA. Thats a little bit better.
