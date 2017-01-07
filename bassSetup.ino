/******************************************** BASS NOTES **************************************************
MIDI №        37	44	39	46	41	36	43	38	45	40	47	42
Root Note      D♭	A♭	E♭	B♭	F	C	G	D	A	E	B	F#  
***********************************************************************************************************/
void getBassSetup(){  
      switch (mode_switch) {
//********************************************************************
  case 36: // C - Left & Right Expression ON
          frontSw_switch = 1;
          // DO NOTHING
    break;
    
  case 43: // G - Left Fixed & Right Expression ON
          LEFT_EXPR_OFF = true;
    break;  
    
  case 38: // D - Left Expression & Right Velocity
          RIGHT_EXPR_OFF = true;
          RIGHT_VEL_ON = true;
    break;

  case 45: // A - Left Fixed & Right Velocity
          RIGHT_EXPR_OFF = true;
          LEFT_EXPR_OFF = true;
          RIGHT_VEL_ON = true;
    break;
/**************** REGISTRATION ********************/    
  case 40: // E  - pushbutton switches on PROGRAM CHANGE mode
          frontSw_switch = 2;

          /*
          // Channel 0 (hex = 0xC0) is Bassoon 00 (0 on patch map) hex = 0x00
          noteOn(0xC0,0x00,program_change); 
      // ONLY IF SAME SOUNDFONT    
      delay( 5 );
        // Channel 2 instrument Guitar 0x19
        noteOn(0xC1,0x00,0x19);
      delay( 5 );
        // Channel 3 Acoustic Bass
    noteOn(0xC2,0x00,0x20);    
    //Setting up Channel 2 and 3 volume
    noteOn(chan_2,0x07,70);
    noteOn(chan_3,0x07,60); */ 

delayMicroseconds(500);    
    break;
    
  case 47: // B  - pushbutton switches on PAGE TURN mode
         // Channel 0 (hex = 0xC0) is Soprano 00 (0 on patch map) hex = 0x00
          noteOn(0xC0,0x00,0x01); 
      /* ONLY IF SAME SOUNDFONT   
      delay( 5 );
        // Channel 2 instrument steel Guitar 0x19
        noteOn(0xC1,0x00,0x19);
      delay( 5 );
        // Channel 3 Acoustic Bass
    noteOn(0xC2,0x00,0x20);  

    //Setting up Channel 2 and 3 volume
    noteOn(chan_2,0x07,70);
    noteOn(chan_3,0x07,60);   
    */   
delayMicroseconds(500);
    break;
    

  case 42: // F#
          //0xB0 - 0x00 - 0x98
          // MSB 98 Ch1
          noteOn(chan_1,0x00,0x98);
          // LSB 0 Ch1
          noteOn(chan_1,0x20,0x01);   
          // Channel 0 (hex = 0xC0) is PIANO 00 (0 on patch map) hex = 0x00
          noteOn(0xC0,0x00,0x15); 
          delay( 5 );
         // MSB 98 Ch2
        noteOn(chan_2,0x00,0x98);
        // LSB 0 Ch2
        noteOn(chan_2,0x20,0x00);  
      delay( 5 );
        // Channel 2 instrument Strat Rear 0x1B
        noteOn(0xC1,0x00,0x1B);
      delay( 5 );
      /*
        // MSB 98 Ch2
        noteOn(chan_3,0x00,0x98);
        // LSB 0 Ch1
        noteOn(chan_3,0x20,0x00);    
      */  
        // Channel 3 Acoustic Bass
    noteOn(0xC2,0x00,0x20);  
    //Setting up Channel 2 and 3 volume
    noteOn(chan_2,0x07,70);
    noteOn(chan_3,0x07,60);   
    break;

  case 37: 
          //0xB0 - 0x00 - 0x98
          // MSB 98 Ch1
          noteOn(chan_1,0x00,0x98);
          // LSB 0 Ch1
          noteOn(chan_1,0x20,0x01);   
          // Channel 0 (hex = 0xC0) is PIANO 00 (0 on patch map) hex = 0x00
          noteOn(0xC0,0x00,0x17); //Bandoneon
          delay( 5 );
         // MSB 98 Ch2
        noteOn(chan_2,0x00,0x98);
        // LSB 0 Ch2
        noteOn(chan_2,0x20,0x00);  
      delay( 5 );
        // Channel 2 instrument Strat Rear 0x1B
        noteOn(0xC1,0x00,0x1B);
      delay( 5 );
      /*
        // MSB 98 Ch2
        noteOn(chan_3,0x00,0x98);
        // LSB 0 Ch1
        noteOn(chan_3,0x20,0x00);    
      */  
        // Channel 3 Acoustic Bass
    noteOn(0xC2,0x00,0x20);  
    //Setting up Channel 2 and 3 volume
    noteOn(chan_2,0x07,70);
    noteOn(chan_3,0x07,60);   
    break;   
/***************** TRANSPOSER ********************/
//  case 37: // D♭ - TR -5
//          transposer = -5;
//    break; 

  case 44: // A♭ - TR -4
          transposer = -4;
    break; 
    
  case 39: // E♭ - TR -2
          transposer = -2;
    break;
    
  case 46: // C - TR +1
          transposer = 1;
    break;  
    
  case 41: // B♭ - TR +3
          transposer = 3;
    break;  
    
  delayMicroseconds(500);  
    
    }   
  }

