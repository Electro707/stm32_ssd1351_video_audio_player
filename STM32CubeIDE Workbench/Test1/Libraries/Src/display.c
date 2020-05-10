#include "display.h"

volatile uint8_t color_byte[2],color_fill_byte[2];


void OLED_Driver_Write_Command(volatile uint8_t cmd)  {

  OLED_CS_0;
  OLED_DC_0;
  SPI_Write_Byte(cmd);

}

void OLED_Driver_Write_Data(volatile uint8_t dat) {

  OLED_CS_0;
  OLED_DC_1;
  SPI_Write_Byte(dat);

}

void OLED_Driver_Set_Color(volatile uint16_t color)  {

  color_byte[0] = (uint8_t)(color >> 8);
  color_byte[1] = (uint8_t)(color & 0x00ff);

}

void OLED_Driver_Set_FillColor(volatile uint16_t color)  {
  color_fill_byte[0] = (uint8_t)(color >> 8);
  color_fill_byte[1] = (uint8_t)(color & 0x00ff);
}

void OLED_Driver_RAM_Address(void)  {

  OLED_Driver_Write_Command(0x15);
  OLED_Driver_Write_Data(0x00);
  OLED_Driver_Write_Data(0x7f);
  OLED_CS_1;

  OLED_Driver_Write_Command(0x75);
  OLED_Driver_Write_Data(0x00);
  OLED_Driver_Write_Data(0x7f);
  OLED_CS_1;
}

void OLED_Driver_CUSTOM_RAM_Address(volatile uint8_t s_row, volatile uint8_t e_row, volatile uint8_t s_col, volatile uint8_t e_col)  {

  OLED_Driver_Write_Command(0x15);
  OLED_Driver_Write_Data(s_col);
  OLED_Driver_Write_Data(e_col);
  OLED_CS_1;

  OLED_Driver_Write_Command(0x75);
  OLED_Driver_Write_Data(s_row);
  OLED_Driver_Write_Data(e_row);
  OLED_CS_1;
}

void OLED_Driver_Clear_Screen(void)  {

  int i,j;

  uint8_t clear_byte[] = {0x00, 0x00};
  OLED_Driver_RAM_Address();
  OLED_Driver_Write_Command(0x5C);
  for(i=0;i<128;i++)  {
    for(j=0;j<128;j++)  {
      OLED_Driver_Write_Data(clear_byte[0]);
      OLED_Driver_Write_Data(clear_byte[1]);
    }
  }
  OLED_CS_1;
}


void OLED_Driver_Fill_Color(volatile uint16_t color)  {

  volatile uint16_t i,j;
  OLED_Driver_RAM_Address();
  OLED_Driver_Write_Command(0x5C);
  OLED_Driver_Set_FillColor(color);
  for(i = 0; i < 128; i++)  {
    for(j = 0; j < 128; j++)  {
      OLED_Driver_Write_Data(color_fill_byte[0]);
      OLED_Driver_Write_Data(color_fill_byte[1]);

    }
  }
  OLED_CS_1;
}

void OLED_Driver_Set_Coordinate(uint16_t x, uint16_t y)  {

  if ((x >= SSD1351_WIDTH) || (y >= SSD1351_HEIGHT))
    return;
  //Set x and y coordinate
  OLED_Driver_Write_Command(SSD1351_CMD_SETCOLUMN);
  OLED_Driver_Write_Data(x);
  OLED_Driver_Write_Data(SSD1351_WIDTH-1);
  OLED_CS_1;

  OLED_Driver_Write_Command(SSD1351_CMD_SETROW);
  OLED_Driver_Write_Data(y);
  OLED_Driver_Write_Data(SSD1351_HEIGHT-1);
  OLED_CS_1;

  OLED_Driver_Write_Command(SSD1351_CMD_WRITERAM);
  //OLED_CS_1;
}

void OLED_Driver_Set_Address(volatile uint8_t column, volatile uint8_t row)  {

  OLED_Driver_Write_Command(SSD1351_CMD_SETCOLUMN);
  OLED_Driver_Write_Data(column);  //X start
  OLED_Driver_Write_Data(column); //X end
  OLED_CS_1;

  OLED_Driver_Write_Command(SSD1351_CMD_SETROW);
  OLED_Driver_Write_Data(row);  //Y start
  OLED_Driver_Write_Data(row+7);  //Y end
  OLED_CS_1;

  OLED_Driver_Write_Command(SSD1351_CMD_WRITERAM);
  //OLED_CS_1;
}

/*
void OLED_Driver_Write_text(uint8_t dat) {

  uint8_t i;

  for(i=0;i<8;i++)  {
    if (dat & 0x01) {
      OLED_Driver_Write_Data(color_byte[0]);
      OLED_Driver_Write_Data(color_byte[1]);

    }
    else  {
      OLED_Driver_Write_Data(0x00);
      OLED_Driver_Write_Data(0x00);
    }
    dat >>= 1;
  }
}*/

void  OLED_Driver_Invert(uint8_t v) {

  if (v)
    OLED_Driver_Write_Command(SSD1351_CMD_INVERTDISPLAY);
  else
    OLED_Driver_Write_Command(SSD1351_CMD_NORMALDISPLAY);
  OLED_CS_1;
}

void OLED_Driver_Draw_Pixel(int16_t x, int16_t y)
{
  // Bounds check.
  if ((x >= SSD1351_WIDTH) || (y >= SSD1351_HEIGHT)) return;
  if ((x < 0) || (y < 0)) return;

  OLED_Driver_Set_Address(x, y);

  // transfer data
  OLED_Driver_Write_Data(color_byte[0]);
  OLED_Driver_Write_Data(color_byte[1]);

  OLED_CS_1;
}

void OLED_Driver_Device_Init(void) {

  OLED_DC_0;
  OLED_CS_1;


  OLED_RST_0;
  delayMs(500);
  OLED_RST_1;
  delayMs(500);


  OLED_Driver_Write_Command(0xfd);  // command lock
  OLED_Driver_Write_Data(0x12);
  OLED_CS_1;

  OLED_Driver_Write_Command(0xfd);  // command lock
  OLED_Driver_Write_Data(0xB1);
  OLED_CS_1;

  OLED_Driver_Write_Command(0xae);  // display off
  OLED_CS_1;

  OLED_Driver_Write_Command(0xa4);  // Normal Display mode
  OLED_CS_1;

  OLED_Driver_Write_Command(0x15);  //set column address
  OLED_Driver_Write_Data(0x00); //column address start 00
  OLED_Driver_Write_Data(0x7f); //column address end 127
  OLED_CS_1;

  OLED_Driver_Write_Command(0x75);  //set row address
  OLED_Driver_Write_Data(0x00); //row address start 00
  OLED_Driver_Write_Data(0x7f); //row address end 127
  OLED_CS_1;

  OLED_Driver_Write_Command(0xB3);
  //OLED_Driver_Write_Data(0xF1);
  OLED_Driver_Write_Data(0xF0);
  OLED_CS_1;

  OLED_Driver_Write_Command(0xCA);
  OLED_Driver_Write_Data(0x7F);
  OLED_CS_1;

  OLED_Driver_Write_Command(0xa0);  //set re-map & data format
  OLED_Driver_Write_Data(0x74); //Horizontal address increment
//  OLED_Driver_Write_Data(0b10110100); //Horizontal address increment
  OLED_CS_1;
            //74
  OLED_Driver_Write_Command(0xa1);  //set display start line
  OLED_Driver_Write_Data(0x00); //start 00 line
  OLED_CS_1;

  OLED_Driver_Write_Command(0xa2);  //set display offset
  OLED_Driver_Write_Data(0x00);
  OLED_CS_1;

  OLED_Driver_Write_Command(0xAB);
  OLED_Driver_Write_Data(0x01);
  OLED_CS_1;

  OLED_Driver_Write_Command(0xB4);
  OLED_Driver_Write_Data(0xA0);
  OLED_Driver_Write_Data(0xB5);
  OLED_Driver_Write_Data(0x55);
  OLED_CS_1;

  OLED_Driver_Write_Command(0xC1);
  OLED_Driver_Write_Data(0xC8);
  OLED_Driver_Write_Data(0x80);
  OLED_Driver_Write_Data(0xC0);
  OLED_CS_1;

  OLED_Driver_Write_Command(0xC7);
  OLED_Driver_Write_Data(0x0F);
  //OLED_Driver_Write_Data(0x05);
  OLED_CS_1;

  OLED_Driver_Write_Command(0xB1);
  OLED_Driver_Write_Data(0x32);
  OLED_CS_1;

  OLED_Driver_Write_Command(0xB2);
  OLED_Driver_Write_Data(0xA4);
  OLED_Driver_Write_Data(0x00);
  OLED_Driver_Write_Data(0x00);
  OLED_CS_1;

  OLED_Driver_Write_Command(0xBB);
  OLED_Driver_Write_Data(0x17);
  OLED_CS_1;

  OLED_Driver_Write_Command(0xb5); // Set GPIO 0 to 1  turn on DC/DC
  OLED_Driver_Write_Data(0x0b);
  OLED_CS_1;

  OLED_Driver_Write_Command(0xB6);
  OLED_Driver_Write_Data(0x01);
  OLED_CS_1;

  OLED_Driver_Write_Command(0xBE);
  OLED_Driver_Write_Data(0x05);
  OLED_CS_1;

  OLED_Driver_Write_Command(0xA6);
  OLED_CS_1;

  OLED_Driver_Clear_Screen();
  OLED_Driver_Write_Command(0xaf);   //display on
  OLED_CS_1;
}



// Draw a horizontal line ignoring any screen rotation.
void OLED_Driver_Draw_FastHLine(int16_t x, int16_t y, int16_t length) {
  // Bounds check
  if ((x >= SSD1351_WIDTH) || (y >= SSD1351_HEIGHT))
    return;

  // X bounds check
  if (x+length > SSD1351_WIDTH) {
    length = SSD1351_WIDTH - x - 1;
  }

  if (length < 0)
    return;

  // set location
  OLED_Driver_Write_Command(SSD1351_CMD_SETCOLUMN);
  OLED_Driver_Write_Data(x);
  OLED_Driver_Write_Data(x+length-1);
  OLED_CS_1;

  OLED_Driver_Write_Command(SSD1351_CMD_SETROW);
  OLED_Driver_Write_Data(y);
  OLED_Driver_Write_Data(y);
  OLED_CS_1;

  // fill!
  OLED_Driver_Write_Command(SSD1351_CMD_WRITERAM);

  for (uint16_t i=0; i < length; i++)  {
    OLED_Driver_Write_Data(color_byte[0]);
    OLED_Driver_Write_Data(color_byte[1]);
  }
  OLED_CS_1;
}

  // Draw a vertical line ignoring any screen rotation.
void OLED_Driver_Draw_FastVLine(int16_t x, int16_t y, int16_t length)  {
  // Bounds check

  uint16_t i;

  if ((x >= SSD1351_WIDTH) || (y >= SSD1351_HEIGHT))
    return;
  // X bounds check
  if (y+length > SSD1351_HEIGHT) {
    length = SSD1351_HEIGHT - y - 1;
  }
  if (length < 0)
    return;

  // set location
  OLED_Driver_Write_Command(SSD1351_CMD_SETCOLUMN);
  OLED_Driver_Write_Data(x);
  OLED_Driver_Write_Data(x);
  OLED_CS_1;

  OLED_Driver_Write_Command(SSD1351_CMD_SETROW);
  OLED_Driver_Write_Data(y);
  OLED_Driver_Write_Data(y+length-1);
  OLED_CS_1;

  // fill!
  OLED_Driver_Write_Command(SSD1351_CMD_WRITERAM);

  for (i = 0; i < length; i++)  {
    OLED_Driver_Write_Data(color_byte[0]);
    OLED_Driver_Write_Data(color_byte[1]);
  }
  OLED_CS_1;
}

/*
void OLED_Driver_Display_Interface(void) {

  uint16_t i,j,color;

  OLED_Driver_Set_Coordinate(0,1);
  for(i = 0 ; i < 8 ; i++)  {
    for(j = 0; j < 128; j++) {
      if((interface_1[(i*128+j)/8]>>((i*128+j)%8))&0x01)
        color = GREEN+((i*128+j)<<11);
      else
        color = BLACK;

      OLED_Driver_Set_Color(color);
      OLED_Driver_Write_Data(color_byte[0]);
      OLED_Driver_Write_Data(color_byte[1]);
    }
  }
  OLED_CS_1;

  OLED_Driver_Set_Coordinate(0,20);
  for(i = 0 ; i < 22 ; i++) {
    for(j = 0; j < 128; j++)  {
      if((interface_2[(i*128+j)/8]>>((i*128+j)%8))&0x01)
        color = MAGENTA;
      else
        color = BLACK;

      OLED_Driver_Set_Color(color);
      OLED_Driver_Write_Data(color_byte[0]);
      OLED_Driver_Write_Data(color_byte[1]);
    }
  }
  OLED_CS_1;

  OLED_Driver_Set_Coordinate(0,60);
  for(i = 0 ; i < 18 ; i++) {
    for(j = 0; j < 128; j++)  {
      if((interface_4[(i*128+j)/8]>>((i*128+j)%8))&0x01)
        color = GREEN;
      else
        color = BLACK;

      OLED_Driver_Set_Color(color);
      OLED_Driver_Write_Data(color_byte[0]);
      OLED_Driver_Write_Data(color_byte[1]);
    }
  }
  OLED_CS_1;

  OLED_Driver_Write_Command(SSD1351_CMD_SETCOLUMN);
  OLED_Driver_Write_Data(80);  //X start
  OLED_Driver_Write_Data(80+8*5-1); //X end
  OLED_CS_1;

  OLED_Driver_Write_Command(SSD1351_CMD_SETROW);
  OLED_Driver_Write_Data(90);  //Y start
  OLED_Driver_Write_Data(90+16-1);  //Y end
  OLED_CS_1;

  OLED_Driver_Write_Command(SSD1351_CMD_WRITERAM);

  for(i = 0 ; i < 16 ; i++) {
    for(j = 0; j < 8*5; j++)  {
      if((interface_text1[(i*8*5+j)/8]>>((i*8*5+j)%8))&0x01)
        color = BLUE+0x0f00+i*128+j*32;
      else
        color = BLACK;

      OLED_Driver_Set_Color(color);
      OLED_Driver_Write_Data(color_byte[0]);
      OLED_Driver_Write_Data(color_byte[1]);
    }
  }
  OLED_CS_1;

  OLED_Driver_Write_Command(SSD1351_CMD_SETCOLUMN);
  OLED_Driver_Write_Data(0);  //X start
  OLED_Driver_Write_Data(0+8*9-1); //X end
  OLED_CS_1;

  OLED_Driver_Write_Command(SSD1351_CMD_SETROW);
  OLED_Driver_Write_Data(90);  //Y start
  OLED_Driver_Write_Data(90+16-1);  //Y end
  OLED_CS_1;

  OLED_Driver_Write_Command(SSD1351_CMD_WRITERAM);

  for(i = 0 ; i < 16 ; i++) {
    for(j = 0; j < 8*9; j++)  {
      if((interface_text2[(i*8*9+j)/8]>>((i*8*9+j)%8))&0x01)
        color = BLUE+0xf000+i*128;
      else
        color = BLACK;

      OLED_Driver_Set_Color(color);
      OLED_Driver_Write_Data(color_byte[0]);
      OLED_Driver_Write_Data(color_byte[1]);
    }
  }
  OLED_CS_1;

  OLED_Driver_Set_Coordinate(0,118);
  for(i = 0 ; i < 9 ; i++) {
    for(j = 0; j < 128; j++)  {
      if((interface_3[(i*128+j)/8]>>((i*128+j)%8))&0x01)
        color = RED+(i*128+j);
      else
        color = BLACK;

      OLED_Driver_Set_Color(color);
      OLED_Driver_Write_Data(color_byte[0]);
      OLED_Driver_Write_Data(color_byte[1]);
    }
  }
  OLED_CS_1;



  Set_Coordinate(0,15);
  for(i = 0 ; i < 22 ; i++)  {
    for(j = 0; j < 128; j++) {
      if((interface_2[(i*128+j)/8]>>((i*128+j)%8))&0x01)  {
        if((i*128+j)<128*12)
          color = GREEN+((i*128+j)<<11);
        else if((i*128+j)<128*40)
          color = CYAN;
        else
          color = RED+(i*128+j)-128*40;
      }
      else  {
        color = BLACK;
      }
      Set_Color(color);
      OLED_Driver_Write_Data(color_byte[0]);
      OLED_Driver_Write_Data(color_byte[1]);
    }
  }

} */




