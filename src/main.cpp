/*
ATiny85 Pinout

                          +--, ,--+
RESET--5/A0--PCINT5--PB5--|1  U  8|--VCC +
       3/A3--PCINT3--PB3--|2     7|--PB2--PCINT2--2/A1--SCK---SCL
 OC1B--4/A2--PCINT4--PB4--|3     6|--PB1--PCINT1--1-----MISO--D0
                     GND--|4     5|--PB0--PCINT0--0-----MOSI--DI
                          +-------+
*/

#include <Arduino.h>
//define PINs
const int BacklightEnablePin = 0; //pin 5 on Attiny85 chip
const int BacklightPin = 1;       //pin 6 on ATtiny85 chip
const int PotentiometerPin = A1;  //pin 7 on ATtiny85 chip


ISR (PCINT0_vect) {}  // Interrupt Service Routine is calling by external PINs. Which PINs are configured with PCMSK register.


void deepsleep() {
  ADCSRA &=  B01111111; //deactivate ADC with bit 7 in the ADCSRA register = ADEN = ADC Enabled ... to reactivate ADCSRA |= B10000000;
  //ENABLE SLEEP - this enables the sleep mode
  MCUCR |=   B00010000;            //power down mode (SM1=1,SM0=0)     BODS|PUD|SE|SM1|SM0|BODSE|ISC01|ISC00
  MCUCR |=   B00100000;            //enable sleep (SE=1)               BODS|PUD|SE|SM1|SM0|BODSE|ISC01|ISC00
  //disable Brown-Out Detection BOD
  MCUCR |=   B10000100;            //set BODS and BODSE                BODS|PUD|SE|SM1|SM0|BODSE|ISC01|ISC00
  MCUCR = (MCUCR & B11111011) | B10000000; //then clear the BODSE and set the BODS
  __asm__  __volatile__("sleep");  //in line assembler to go to sleep
  // <---- microcontroller now sleep!

  // <---- microcontroller is back after wake up!
  MCUCR &=   B11011111;            //disable sleep (SE=1)              BODS|PUD|SE|SM1|SM0|BODSE|ISC01|ISC00
  ADCSRA |=  B10000000; //reactivate ADC with bit 7 in the ADCSRA register = ADEN = ADC Enabled ... to reactivate ADCSRA |= B10000000;
}


void setup() {
  //energy safing options
  //ADCSRA &= B01111111; //deactivate ADC with bit 7 in the ADCSRA register = ADEN = ADC Enabled ... to reactivate ADCSRA |= B10000000;
  //pinMode(0, OUTPUT);  //set all PINs they are not used as output low
  //pinMode(1, OUTPUT);
  //pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  pinMode(BacklightEnablePin, INPUT_PULLUP);   //signal from computer for backlight enabled (free or high = enabled; low = disabled)
  pinMode(BacklightPin, OUTPUT);               //PWM signal to drive the MOSFED for the LED
  pinMode(PotentiometerPin, INPUT);            //analog input from potentiometer

  PCMSK |= B00000001; // digitalPIN 0                        – | – |PCINT5|PCINT4|PCINT3|PCINT2|PCINT1|PCINT0
  GIFR  |= B00100000; // clear any outstanding interrupts    – |INTF0|PCIF| –| – | – | – | –
  GIMSK |= B00100000; // enable pin change interrupts        – |INT0|PCIE| – | – | – | – | –
}

void loop() {
  int brightness;

  brightness = analogRead(PotentiometerPin);
  //brightness = map(brightness, 0, 1023, 0, 255);
  brightness = brightness >> 2;
  analogWrite(BacklightPin, brightness);
  delay(200);


  if (digitalRead(BacklightEnablePin)==LOW){
    analogWrite(BacklightPin, 0);
    deepsleep();
  }
  

}

