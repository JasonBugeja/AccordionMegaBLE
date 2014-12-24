AccordionMega_USB_Keyb
======================

Arduino Mega based Accordion midi controller using photointerruptors for bass (left-hand) section mapping and USB midi keyboard for treble (right-hand) section through USB host shield. 

Thanks to Dmitry Yegorenkov https://github.com/accordion-mega/AccordionMega/wiki/Accordion-Mega-story I have packed up courage to start my mission to convert an acoustic accordion (Hohner Concerto III in my case) into a digital midi controller.  The project took me the whole year 2014 (in my free time) to complete. 

I have updated Dmitry's code to the new Arduino IDE and decided to combine with Yuuichi Akagawa's https://github.com/YuuichiAkagawa/USBH_MIDI/blob/master/examples/USB_MIDI_converter/USB_MIDI_converter.ino
so that apart from being cost effective, it will have touch sensitivity on the right-hand keyboard and less time-consuming to build. Using an off-the-shelf midi keyboard, first Akai LPK25 and then Samson Graphite M32 to have more keys available, costs approx £50 more but saves you 34 or 41 opto-interrupters and their mapping!  The bass section is relatively easier to map since all bass combinations use only 24 pallets. 

				<p class="MsoNormal" style="text-align: center">
				<img alt="OptoInterruptors" src="photos/ArduinoSide.jpg" width="350" height="280" /></p>
