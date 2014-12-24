/***************************************************************************************
Currently unused function - was used instead of bassSetup to set registrations on GM/GS
compatible sound generators. 
****************************************************************************************/
void getRegistration(){

    switch (mode_switch) {
  case 36: 
          //0xB0 - 0x00 - 0x98
          // MSB 98 Ch1
          noteOn(chan_1,0x00,0x98);
          // LSB 0 Ch1
          noteOn(chan_1,0x20,0x00);   
          // Channel 0 (hex = 0xC0) is PIANO 00 (0 on patch map) hex = 0x00
          noteOn(0xC0,0x00,0x19); 
          delay( 5 );
     // MSB 98 Ch2
    noteOn(chan_2,0x00,0x98);
    // LSB 0 Ch2
    noteOn(chan_2,0x20,0x00);  
  delay( 5 );
    // Channel 2 instrument Steel Guitar 0x19
    noteOn(0xC1,0x00,0x19);
  delay( 5 );
  /*
    // MSB 98 Ch2
    noteOn(chan_3,0x00,0x98);
    // LSB 0 Ch1
    noteOn(chan_3,0x20,0x00);    
  */  
    // Channel 3 Acoustic Bass
    noteOn(0xC2,0x00,0x20);         
    break;
  case 40:    
          //0xB0 - 0x00 - 0x98
          // MSB 98 Ch1
          noteOn(chan_1,0x00,0x98);
          // LSB 0 Ch1
          noteOn(chan_1,0x20,0x00);   
          // Channel 0 (hex = 0xC0) is PIANO 00 (0 on patch map) hex = 0x00
          noteOn(0xC0,0x00,0x17); 
          delay( 5 );
    // MSB 98 Ch2
    noteOn(chan_2,0x00,0x98);
    // LSB 0 Ch2
    noteOn(chan_2,0x20,0x00);  
  delay( 5 );
    // Channel 2 instrument Steel Guitar 0x19
    noteOn(0xC1,0x00,0x19);
  delay( 5 );
  /*
    // MSB 98 Ch2
    noteOn(chan_3,0x00,0x98);
    // LSB 0 Ch1
    noteOn(chan_3,0x20,0x00);    
  */  
    // Channel 3 Acoustic Bass
    noteOn(0xC2,0x00,0x20);
    break;
    /*
  case 3:   
          //0xB0 - 0x00 - 0x98
          // MSB 98 Ch1
          noteOn(chan_1,0x00,0x98);
          // LSB 0 Ch1
          noteOn(chan_1,0x20,0x00);   
          // Channel 0 (hex = 0xC0) is PIANO 00 (0 on patch map) hex = 0x00
          noteOn(0xC0,0x00,0x21); 
          delay( 5 ); //to give time for midi 
    break;
    */
  delay(1);        // delay in between reads for stability    
    }
}
 

