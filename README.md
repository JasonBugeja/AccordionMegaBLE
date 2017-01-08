AccordionMegaBLE
======================

Arduino Mega based Accordion midi controller using photo-interruptors for bass (left-hand) section mapping using the USB port on the Arduino Mega as class-compliant USB Midi device through mocoLUFA https://github.com/kuwatay/mocolufa and using a commercially available USB Midi to Bluetooth converter to transmit Midi to IOS or OSX devices. Using a commercially available USB midi keyboard for treble (right-hand) section with a powerbank as power supply and a commercially available USB Midi to Bluetooth adaptor or self-powered commercially available BLE mini keyboard.

This Project is an evolution of my other project https://github.com/JasonBugeja/AccordionMega_USB_Keyb which was based on Dmitry Yegorenkov's https://github.com/accordion-mega/AccordionMega.
The idea is to remove the need for routing USB Midi through the Arduino USB host shield by sending the right-hand side midi information directly through a USB to BLE interface to an IOS/OSX device.Eliminating the routing through USB host shield improves latency.  Keep in mind that Midi travels at 31250 bps, that means that if you route it there is an inevitable noticeable lag. 

Having the left and right hand side of the accordion independent creates redundancy in case of failure and eliminates the need for cables across the bellows. The commercially available keyboard on the right-hand side will still benefit through the use of the bellows pressure sensor and if velocity curve cannot be set to "flat" on the device itself, it can still be filtered out through a Midi routing/filtering app such as Midi-Flow on IOS. 

BLE
----
Using any IOS device (iPhone, iPod Touch 6thGen or iPad) multiple BLE transmitters can be used at the same time.  I am currently using two Yamaha UD-BT01 adaptors simultaneously and they work like a charm without any perceivable delay. 

INSTRUCTIONS
------------
"Where am I going to start?"
----------------------------
This breadboard helps you understand better what is going on before starting to build the actual components inside the accordion.
![alt tag](https://github.com/JasonBugeja/AccordionMegaBLE/blob/master/photos/Breadboard.jpg)
![alt tag](https://github.com/JasonBugeja/AccordionMegaBLE/blob/master/photos/Breadboard_Arduino.jpg)

Youtube video of the breadboard https://www.youtube.com/watch?v=EBQ5M6_7AL0

The 'Documents' folder in the zip file contains breadboard prototype schematic and whole accordion schematic done by Dmitry Yegorenkov.

In the 'Photos' folder you can find some high resolution photos of the electronics inside my accordion. 

COMPONENTS:
-----------
* Arduino Mega - For breadboard prototype I have used an Arduino clone in case it gets fried :simple_smile: Inside my accordion I prefer to use a genuine Arduino/Genuino to make sure there are no cost-cutting modifications that would compromise performance.

* resistors - as per schematic. For breadboard use whatever you like as long as resistance matches, for the real thing use low-tolerance high quality resistors. 

* Transistors - I have used C945, you might use an equivalent. Note that transistors have three legs **Emitter**, **Collector**, **Base** - download the data sheet to decipher which is which and where to connect as per schematic. They are not always in the same order eg. the Collector can be the middle leg in one model and left or right on another model - always refer to data sheet and make sure that you are facing the flat side.

* Photo interruptors - I have used HY-301-21 from eBay. Similar models should work as long as specifications are equivalent. Also refer to data sheets because their four legs might be in a different layout. The infrared emitter side is usually marked with a diode sign (Light emitting diode), so you would know where the voltage enters after passing through resistors. When it exits the infra-red diode, it joins all the other exits in the group and goes to the **Collector** of the transistor. The sensor transistor side of the Photo-interruptor is connected to the analog pins of the arduino from the **Collector** side and the **Emitter** to **Ground**.


