/*******************************************************************************
 MIDI accordion for Mega
 Jason Bugeja 2014
 based on a projects by
 * AccordionMega
 * Dimon Yegorenkov 2011
 *
 * USB-MIDI to Legacy Serial MIDI converter
 * Copyright 2012-2013 Yuuichi Akagawa
 *
 * Idea from LPK25 USB-MIDI to Serial MIDI converter
 *   by Collin Cunningham - makezine.com, narbotic.com
 *
 * for use with USB Host Shield 2.0 from Circuitsathome.com
 * https://github.com/felis/USB_Host_Shield_2.0
 *
 * This is sample program. Do not expect perfect behavior.
 *******************************************************************************
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 *******************************************************************************/

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <WProgram.h>                                                         //++
//#include <LiquidCrystal.h>                                                  //++
                                                                              //++
// this part is needed for reading BMP085 sensor                              //++
#include <Wire.h>                                                             //++
#define BMP085_ADDRESS 0x77  // I2C address of BMP085                         //++
const unsigned char OSS = 0; //oversampling for measurement                   //++
//const unsigned char pressure_waittime[4] = { 5, 8, 14, 26 };                //++
                                                                              //++
//#define MIDI_PORT Serial                                                    //++
HardwareSerial & MIDI_PORT = Serial;                                          //++
HardwareSerial & BT_CC_PORT = Serial2;                                        //++
HardwareSerial & BT_MENU_PORT = Serial3;                                      //++
                                                                              //++
boolean RIGHT_VEL_ON = false;                                                 //++
boolean RIGHT_EXPR_OFF = false;                                               //++
boolean LEFT_EXPR_OFF = false;                                                //++
boolean SETUP_MODE = true;  //<---turn to "true" to enable Bass_Setup         //++
boolean PAGETURN_MODE = true;                                                 //++

int reg_blue = 0;                                                             //++
int blueCtrl = 0;                                                             //++
                                                                              //++
char mode_switch = 0;                                                         //++
//as taken from the BMP085 datasheet                                          //++
int ac1;                                                                      //++
int ac2;                                                                      //++ 
int ac3;                                                                      //++ 
unsigned int ac4;                                                             //++
unsigned int ac5;                                                             //++
unsigned int ac6;                                                             //++
int b1;                                                                       //++
int b2;                                                                       //++
int mb;                                                                       //++
int mc;                                                                       //++
int md;                                                                       //++
/* b5 is calculated in bmp085GetTemperature(...), this variable is also used  //++ 
in bmp085GetPressure(...) so ...Temperature(...) must be called               //++
before ...Pressure(...).*/                                                    //++
long b5;                                                                      //++
// Use these for altitude conversions                                         //++
const float p0 = 101325;     // Pressure at sea level (Pa)                    //++
float altitude;                                                               //++
                                                                              //++
#include <avr/pgmspace.h>                                                     //++
                                                                              //++
//  these pins do not have to be configured one by one,                       //++ 
//  numbers just for reference, that's 8 bits for PortF, 8 bits for PortK     //++
//  and they are read as a byte and byte later.                               //++
                                                                              //++
char bass_row_pins[] = { 4, 5};                                               //++
char chord_row_pins[] = { 6, 7};                                              //++
                                                                              //++
byte reg_values = 0;                                                          //++
                                                                              //++
// array to store up/down status of left keys                                 //++ 
int BassKeysStatus[] = {                                                      //++ 
  B0000000,                                                                   //++
  B0000000                                                                    //++
};                                                                            //++
                                                                              //++
// array to store up/down status of right keys                                //++
int ChordKeysStatus[] = {                                                     //++ 
  B0000000,                                                                   //++
  B0000000                                                                    //++
};                                                                            //++
                                                                              //++
// storing in program memory to save RAM                                      //++ 
const prog_char bass_notes_midi_numbers[][8] = {                              //++
 //F2,E2,D#2,D2,C#,C2,B2,A#2 - pin9                                           //++
  {41,40,39, 38,37,36,47,46},                                                 //++
  //       A2,G#2,G2,F#2 ----- pin10                                          //++
  {0,0,0,0,45,44, 43,42}                                                      //++
  };                                                                          //++
                                                                              //++  
const prog_char chord_notes_midi_numbers[][8] = {                             //++
 //F4,E4,D#4,D4,C#4,C4,B3,A#3 - pin11                                         //++
  {65,64,63, 62,61, 60,59,58},                                                //++
         //A3,G#3,G3,F#3 -----  pin12                                         //++
  {0,0,0,0,57,56, 55,54}                                                      //++
  };                                                                          //++
                                                                              //++
char notes_to_play;                                                           //++
char bt_c_buffer[3];                                                          //++
byte bt_m_choice;                                                             //++
int bt_m_counter = 0;                                                         //++
int bt_m_counter2 = 0;                                                        //++
int bass_setup_i = 0;                                                         //++
int transposer = 0; 
byte octave_higher = 0x0C;
byte program_change = 0x00;                                                   //++
                                                                              //++
byte ledPin = 13;                                                             //++
byte midi_channel1 = 2;                                                       //++
byte midi_channel2 = 1;                                                       //++
byte chan_1 = 0xB0;                                                           //++
byte chan_2 = 0xB1;                                                           //++
byte chan_3 = 0xB2;                                                           //++  
                                                                              //++
byte ch_1_NoteOn  = 0x90;                                                     //++
byte ch_1_NoteOff = 0x80;                                                     //++
byte ch_2_NoteOn  = 0x91;                                                     //++
byte ch_2_NoteOff = 0x81;                                                     //++
byte ch_3_NoteOn  = 0x92;                                                     //++
byte ch_3_NoteOff = 0x82;                                                     //++
                                                                              //++
byte cc_descriptor = 0x0B;                                                    //++
                                                                              //++
//function noteOn variables:                                                  //++
int pitch;                                                                    //++
char midi_cmd;                                                                //++
char midi_vel;                                                                //++
//int lastUpdate = 0;                                                         //++
byte curr_velocity = 127;                                                     //++
byte velocity = 127;                                                          //++
boolean velocity_active = false;                                              //++
byte pressure_low_limit = 7;                                                  //++
int time = micros();                                                          //++
int temperature = 0;                                                          //++
long pressure = 0;                                                            //++
long zero_pressure = 0;                                                       //++
int delta_pressure=0;                                                         //++
int pressure_counter = 0;                                                     //++
int pressure_loops = 2;                                                       //++
long min_pressure=480;   //480;                                               //++
long max_pressure=440;   //440;                                               //++

int maxvel = 100;     // maximum velocity for left chords and bass - not to trigger fortissimo sample layers
   unsigned long t1;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//************************PageFlip********************************
//====================================================== variables
// The switches MUST be on Arduino pin 2 and 3 respectively
int ch15PitchBnd = 2;
int ch16PitchBnd = 3;
volatile int ch15PitchBnd_transition = 0;
volatile int ch16PitchBnd_transition = 0;

/////////////////////////////////////////////////////////////////////////////
#include <Usb.h>                                                           //
#include <usbh_midi.h>                                                     //
                                                                           //
//////////////////////////////                                             //
// MIDI Pin assign          //                                             //
// 2 : GND                  //                                             //
// 4 : +5V(Vcc) with 220ohm //                                             //
// 5 : TX                   //                                             //
//////////////////////////////                                             //
                                                                           //
USB  Usb;                                                                  //
USBH_MIDI  Midi(&Usb);                                                     //
                                                                           //
void MIDI_poll();                                                          //
void doDelay(unsigned long t1, unsigned long t2, unsigned long delayTime); //
/////////////////////////////////////////////////////////////////////////////

 //************************PageFlipFlag****************************
 // All this does is set a flag on a switch transition.
 // The loop function looks for the flag.
void ch15PitchBnd_switch_transition(void)
   {
     ch15PitchBnd_transition = 1;
   }
void ch16PitchBnd_switch_transition(void)
   {
     ch16PitchBnd_transition = 1;
   }

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void setup(){

    MIDI_PORT.begin(31250);  // start midi port
//  MIDI_PORT.begin(115200);  // start Serial Monitor
  BT_CC_PORT.begin(115200);  // start bluetooth midi port
  BT_MENU_PORT.begin(115200);  // start bluetooth midi port  
  Wire.begin();
  bmp085Calibration();
  getZero();

  // PortK as left input and turn on pullup resistors
  DDRK = B00000000;
  PORTK = B11111111; 
//----------------------------------------------------------------------------------
  //*******************PageTurnerSetup*************
  // This will call switch_transition if the switch goes up or down
  attachInterrupt(0,ch15PitchBnd_switch_transition,CHANGE);
  attachInterrupt(1,ch16PitchBnd_switch_transition,CHANGE);  
  // pinMode(toggleSwitch, INPUT);
  pinMode(ch15PitchBnd, INPUT);
  pinMode(ch16PitchBnd, INPUT);
  // pinMode(midiOut, OUTPUT);
  //***********************************************
  //RESETTING ALL CHANNELS TO 127 Expression - in case of switching off and on again 
  //                              to change bellows mode in Bass Setup
  noteOn(chan_1,cc_descriptor,127);
  noteOn(chan_2,cc_descriptor,127);
  noteOn(chan_3,cc_descriptor,127);
  noteOn(0xC0,0x00,program_change); // Initialising program change on external sound generator
  
 //////////////////////////////////
//Workaround for non UHS2.0 Shield //
  pinMode(7,OUTPUT);               //
  digitalWrite(7,HIGH);            //
                                   //
  if (Usb.Init() == -1) {          //
    while(1); //halt               //
  }//if (Usb.Init() == -1...       //
  delay( 200 );                    //
//////////////////////////////////
} // End of Setup

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void loop(){
//****************************************************************************************************** 
BassSide_poll();  // NEEDS TO BE FIRST BECAUSE OF BASS SETUP MODE

if (!SETUP_MODE){ 
    BlueCC_poll();
    PageTurn_poll();
//******************************************************************************************************
// BT_Menu_poll();

  ////////////////////////////////////////////////////
                                                    //
                                                    //
  Usb.Task();                                       //
  // t1 = micros();                                 //
  if( Usb.getUsbTaskState() == USB_STATE_RUNNING )  //
  {                                                 //
    MIDI_poll();                                    //
  }                                                 //
  //delay(1ms)                                      //
  doDelay(t1, micros(), 1000);                      //  
                                                    //    
                                                    //
  ////////////////////////////////////////////////////
   } //End of "if not setup mode" statement 
}

///////////////////////////////////////////////////////////////////
/////////////////// - F U N C T I O N S - /////////////////////////
/////////////////////////////////////////////////////////////////// 

////////////////////////////////////////////////////////////////////////////
// Poll USB MIDI Controller and send to serial MIDI                       //
void MIDI_poll()                                                          //
{                                                                         //
    byte outBuf[ 3 ];                                                     //
    uint8_t size;                                                         //
                                                                          //
    do {                                                                  //
      if( (size=Midi.RcvData(outBuf)) > 0 ){                              //
        //MIDI Output
        if ((outBuf[0]==0x90)|(outBuf[0]==0x80)){        //               
          outBuf[1]=(outBuf[1]+octave_higher)+transposer;                 //
            if(!RIGHT_VEL_ON){                                            //
              outBuf[2]=100;  // to disable velocity less than 127 not    //
                              // trigger Fortissimo sample layer          //
            }                                                             //
//        midi_vel = outBuf[2]; 
        }                                                                 //
        MIDI_PORT.write(outBuf, size);                                    //
        BT_CC_PORT.write(outBuf, size);                                   //
      }                                                                   //
    }while(size>0);                                                       //
}                                                                         //
// Delay time (max 16383 us)                                              //
void doDelay(unsigned long t1, unsigned long t2, unsigned long delayTime) //
{                                                                         //
    unsigned long t3;                                                     //
                                                                          //
    if( t1 > t2 ){                                                        //
      t3 = (4294967295 - t1 + t2);                                        //
    }else{                                                                //
      t3 = t2 - t1;                                                       //
    }                                                                     //
                                                                          //
    if( t3 < delayTime ){                                                 //
      delayMicroseconds(delayTime - t3);                                  //
    }                                                                     //
}                                                                         //
////////////////////////////////////////////////////////////////////////////

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void BassSide_poll( void ){
 if (!SETUP_MODE){ 
   
   temperature = bmp085GetTemperature(bmp085ReadUT());
   pressure = bmp085GetPressure(bmp085ReadUP());   
   getDeltaPressure();

    // setting up minimal pressure to start a sound
    if (delta_pressure < pressure_low_limit){ //setting controller to zero once it got to zero   
      if (curr_velocity>0){
        if (!RIGHT_EXPR_OFF){
	  noteOn(chan_1,cc_descriptor,0);
        }
        if (!LEFT_EXPR_OFF){ 
          noteOn(chan_2,cc_descriptor,0);
	  noteOn(chan_3,cc_descriptor,0);
        }
	curr_velocity = 0; 
      }
    }
    else if (delta_pressure >= pressure_low_limit) { 

        velocity = delta_pressure;
        
      if (curr_velocity != velocity) {
        if (!RIGHT_EXPR_OFF){        
          noteOn(chan_1,cc_descriptor,velocity);
        }
        if (!LEFT_EXPR_OFF){   
          noteOn(chan_2,cc_descriptor,velocity);
          noteOn(chan_3,cc_descriptor,velocity);
       
        }
        curr_velocity = velocity;
      }            
    }
    
  } //<--END of if not SETUP_MODE statement
  
  else {
    curr_velocity = 127;
  }

  scan_keys(bass_row_pins, sizeof(bass_row_pins), BassKeysStatus, true); 
  scan_keys(chord_row_pins, sizeof(chord_row_pins), ChordKeysStatus, false);   
}
//******************* End of BassSidePoll Function *************************

void scan_keys(char *row_pins, int size, int *KeysStatus, boolean bass) {  
  for (int i=0; i<size;i++){    
    digitalWrite(row_pins[i], HIGH);
    delayMicroseconds(500);     
    reg_values = ~PINK;
    digitalWrite(row_pins[i], LOW);
    // checking for activity
    // nested if to save time if nothing happens
    if (reg_values != KeysStatus[i]){
      if (reg_values > KeysStatus[i]){             
          check_key(reg_values ^ KeysStatus[i],i,true,bass);  //sending modified bits only
      }
      else {
	check_key(reg_values ^ KeysStatus[i],i,false,bass); //sending modified bits only
      }           
    }        
  }
 
}

void check_key(int reg, int group, boolean up, boolean bass){
   // saving 4 iterations, dividing byte by 2
   if (reg & 0xF0) {
     for(int i=0; i<4; i++){
       if ((reg >> 4+i) & 1){
	 if (bass) {
	   midi_note(group,i+4,up,bass);
	 }
	 else {
	   midi_note(group,i+4,up,bass);
	 }
       }
     }
   }
   else if (reg & 0x0F) { 
    for(int i=0; i<4; i++){
       if ((reg >> i) & 1){
	 if (bass) {
	   midi_note(group,i,up,bass);
	 }
	 else{
	   midi_note(group,i,up,bass); 
	 }
       }
     }     
   }
}


void midi_note(int group, int position, boolean on, boolean bass){

  if (bass){
    pitch = bass_notes_midi_numbers[group][position];
  }
  else{
    pitch = chord_notes_midi_numbers[group][position];
  }

  if (on & bass){
/************ Bass note gets on *************/
    midi_cmd = ch_3_NoteOn;    
    BassKeysStatus[group] |= (1 << position);  //setting bit value
  }
  else if (~on & bass) {
/************ Bass note gets off ************/
    midi_cmd = ch_3_NoteOff;
    BassKeysStatus[group] &= ~(1 << position);  //setting bit value
  }
  else if(on & ~bass) {
/************ Chord note gets on ************/
    midi_cmd = ch_2_NoteOn;
    ChordKeysStatus[group] |= (1 << position);  //setting bit value
  }
  else if(~on & ~bass) {
/*********** Chord note gets off ************/
    midi_cmd = ch_2_NoteOff;;
    ChordKeysStatus[group] &= ~(1 << position);  //setting bit value
  }
    
  //MIDI output
  if (bass){
      notes_to_play = bass_notes_midi_numbers[group][position];
  }
  else{
      notes_to_play = chord_notes_midi_numbers[group][position];
  }
  
  for (int i=0; i<sizeof(notes_to_play);i++){
    if (notes_to_play){
      if (!SETUP_MODE) {
      byte outBuf[ 3 ];  
        outBuf[0] = midi_cmd;
        outBuf[1] = (notes_to_play+transposer);
        outBuf[2] = maxvel;      //maxvel 127 instead of midi_vel channel volume 0x07 / expression 0x0B used instead    
      MIDI_PORT.write(outBuf[0]);
      MIDI_PORT.write(outBuf[1]);
      MIDI_PORT.write(outBuf[2]);

       BT_CC_PORT.write(outBuf[0]);
       BT_CC_PORT.write(outBuf[1]);
       BT_CC_PORT.write(outBuf[2]);    
    
     }
     else
        mode_switch = notes_to_play;
        getBassSetup();
        bass_setup_i++;
          if (bass_setup_i > 2){
            SETUP_MODE = false;
          }
      } 
  }
}

void getZero(){

    zero_pressure = 0; 
    for (int i=0; i<32; i++){
      temperature = bmp085GetTemperature(bmp085ReadUT());
      zero_pressure += bmp085GetPressure(bmp085ReadUP());
      delayMicroseconds(500);    
    }
    zero_pressure = zero_pressure/32;
 
}

void getDeltaPressure(){
          if (pressure <= zero_pressure){ 
            delta_pressure = int(float((pow((zero_pressure - pressure),1.4)+280)/45)); 
            if (delta_pressure>127){
              delta_pressure = 127;
            }     
          }
      else if (pressure > zero_pressure){
             delta_pressure = int(float((pow((pressure - zero_pressure),1.4)+280)/40));         
             if (delta_pressure>127){
               delta_pressure = 127;
             }     
           }  
}

void PageTurn_poll(){ //This function is used to control the page turner
  // There's nothing to do if the transition flag is not set
  if(!ch15PitchBnd_transition && !ch16PitchBnd_transition)return; 
  ch15PitchBnd_transition = 0;
  // If toggleswitch is now high, the switch is now UP otherwise it is now DOWN
  if(digitalRead(ch15PitchBnd)) {
      if (!PAGETURN_MODE){
      program_change--;
         if (program_change < 0){
          program_change++;
        }     
      noteOn(0xC0,0x00,program_change);   
      }
      else {
      //  Ch5, Patch 0, Piano
      noteOn(0xEF,0x00,0x7F);
      }
      } 
  else {
      if (!PAGETURN_MODE){
      // do nothing
      }
      else {
      noteOn(0xEF,0x00,0x40);
      }
     } 
  // if(!ch15PitchBnd_transition)return;
  ch16PitchBnd_transition = 0; 
  if(digitalRead(ch16PitchBnd)) {
      if (!PAGETURN_MODE){
      program_change++;
        if (program_change > 127){
          program_change = 0;
        } 
      noteOn(0xC0,0x00,program_change);          
      }
      else {
      //  Ch5, Patch 0, Piano
      noteOn(0xEE,0x00,0x7F);
      }
    } 
  else {
      if (!PAGETURN_MODE){
      //do nothing
      }
      else {    
      noteOn(0xEE,0x00,0x40);
      } 
     }        
  } // EndOf PageTurn_poll
  
void noteOn(int midi_cmd, int pitch, int midi_vel){
  
      MIDI_PORT.write(midi_cmd);
      MIDI_PORT.write(pitch);
      MIDI_PORT.write(midi_vel);

      BT_CC_PORT.write(midi_cmd);
      BT_CC_PORT.write(pitch);
      BT_CC_PORT.write(midi_vel);
      
}


