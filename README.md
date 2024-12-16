This Code is for a ATtiny85 to control the backlight on an LCD screen on a vintage notebook. The LCD backlight was driven by a high voltage fluorescent tube. The tube needs more energy and was dim over the time. You can remove the tube and replace it by a LED string. This LED string will powered by 5 or 12V. To use the old potentiometer to control the brightness of the backlight we use pulse width modulation (PWM) and the ATtiny.

The chip needs the following:
- a logic input to enable/disable the backlight (this is driven by the computer)
- a analog input for the brighness potentiometer
- a PWM output to drive a transitor or MOSFET

