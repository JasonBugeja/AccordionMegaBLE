AccordionMega_USB_Keyb
======================

Arduino Mega based Accordion midi controller using photointerruptors for bass (left-hand) section mapping using the USB port on the Arduino Mega as class-compliant USB Midi device through MocoLufa and using a commercially available USB Midi to Bluetooth converter to transmit Midi to IOS or OSX devices. Using a commercially available USB midi keyboard for treble (right-hand) section with a powerbank as power supply and a commercially available USB Midi to Bluetooth adaptor or self-powered commercially available BLE mini keyboard.

Thanks to Dmitry Yegorenkov https://github.com/accordion-mega/AccordionMega/wiki/Accordion-Mega-story I have packed up courage to start my mission to convert an acoustic accordion (Hohner Concerto III in my case) into a digital midi controller.  The project took me the whole year 2014 (in my free time) to complete. 

I have updated Dmitry's code to the new Arduino IDE and decided to combine with Yuuichi Akagawa's https://github.com/YuuichiAkagawa/USBH_MIDI/blob/master/examples/USB_MIDI_converter/USB_MIDI_converter.ino
so that apart from being cost effective, it will have touch sensitivity on the right-hand keyboard and less time-consuming to build. Using an off-the-shelf midi keyboard, first Akai LPK25 and then Samson Graphite M32 to have more keys available, costs approx £50 more but saves you 34 or 41 opto-interrupters and their mapping!  The bass section is relatively easier to map since all bass combinations use only 24 pallets. 

Bass side pallets with opto-interruptors:

![alt tag](https://github.com/JasonBugeja/AccordionMega_USB_Keyb/blob/master/photos/OptoInterruptorsPallets.jpg)

Bass side bellows side showing counterpart opto-interruptor circuits, Arduino-Mega and USB host shield.

![alt tag](https://github.com/JasonBugeja/AccordionMega_USB_Keyb/blob/master/photos/ArduinoSide.jpg)

First working project using Akai LPK25 controller keyboard:

![alt tag](https://github.com/JasonBugeja/AccordionMega_USB_Keyb/blob/master/photos/TransformedHohner.jpg)

Final working project using Samson Graphite M32 USB controller keyboard:

![alt tag](https://github.com/JasonBugeja/AccordionMega_USB_Keyb/blob/master/photos/AccordionReady.jpg)

First Youtube video showing first prototype - warning! looks very primitive, made several people laugh :)

https://www.youtube.com/watch?v=Fmhv2PbcJrA

Myself playing using the final working project:

https://www.youtube.com/watch?v=ATPYN1C5aeo
