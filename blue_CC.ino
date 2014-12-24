void BlueCC_poll(){
    if (BT_CC_PORT.available() > 0)//there's something in the buffer
    {
        BT_CC_PORT.readBytes(bt_c_buffer, 3);//receive it
        noteOn(bt_c_buffer[0],bt_c_buffer[1],bt_c_buffer[2]); 
        delayMicroseconds(500);         
    }  
} 
    
 
