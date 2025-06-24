/*
 * gc9a01a.c
 *
 *  Created on: Jun 13, 2025
 *      Author: Hwabok
 */


#include "gc9a01a.h"
#include "cmsis_os.h"

#define LCD_CS_0	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET)
#define LCD_CS_1  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET)
#define LCD_DC_0   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET)
#define LCD_DC_1  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET)
#define LCD_RST_0  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET)
#define LCD_RST_1 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET)

HAL_StatusTypeDef SPI_Write(uint8_t* pbuff, uint16_t size);
HAL_StatusTypeDef SPI_Read(uint8_t* pbuff, uint16_t size);

//===============================================================
//write parameter

void  Write_Cmd_Data (unsigned char CMDP)
{
    LCD_CS_0;
   	LCD_DC_1;

   	SPI_Write(&CMDP, 1);

   	LCD_CS_1;
}

//=============================================================
//write command

void Write_Cmd(unsigned char CMD)
{
    LCD_CS_0;
   	LCD_DC_0;

   	SPI_Write(&CMD, 1);

   	LCD_CS_1;
}

//==============================================================
//write  data word

void  Write_Data_U16(unsigned int y)
{
	unsigned char m,n;
	m=y>>8;
	n=y;
	Write_Data(m,n);
}


//===================================================================
//write data byte

void Write_Data(unsigned char DH,unsigned char DL)
{
    LCD_CS_0;
   	LCD_DC_1;

   	SPI_Write(&DH, 1);
   	SPI_Write(&DL, 1);

   	LCD_CS_1;
}


void Write_Bytes(unsigned char * pbuff, unsigned short size)
{
    LCD_CS_0;
   	LCD_DC_1;

   	SPI_Write(pbuff, size);

   	LCD_CS_1;
}


HAL_StatusTypeDef SPI_Write(uint8_t* pbuff, uint16_t size)
{
	//DMA, use HAL_SPI_Transmit_DMA() function
    HAL_StatusTypeDef status =  HAL_SPI_Transmit_DMA(&hspi2, pbuff, size);
    //HAL_StatusTypeDef status = HAL_SPI_Transmit(&hspi2, pbuff, size, 1000);
    while(HAL_SPI_GetState(&hspi2) != HAL_SPI_STATE_READY){;}
    return status;

    //no DMA, use HAL_SPI_Transmit() function
    //return HAL_SPI_Transmit(&hspi2, pbuff, size, 100);
}

HAL_StatusTypeDef SPI_Read(uint8_t* pbuff, uint16_t size)
{
	//DMA, use HAL_SPI_Receive_DMA() function
   HAL_StatusTypeDef status = HAL_SPI_Receive_DMA(&hspi2, pbuff, size);
   while(HAL_SPI_GetState(&hspi2) != HAL_SPI_STATE_READY){;}
   return status;

   //no DMA, use HAL_SPI_Receive() function
//   return HAL_SPI_Receive(&hspi2, pbuff, size, 100);
}


//=============================================================
//LCD Initial

void GC9A01_Initial(void)
{
  	LCD_CS_1;
  	osDelay(5);
	//'osDelay(5);
	LCD_RST_0;
	osDelay(10);
	LCD_RST_1;
	osDelay(120);


 //************* Start Initial Sequence **********//
	Write_Cmd(0xEF);

	Write_Cmd(0xEB);
	Write_Cmd_Data(0x14);

    Write_Cmd(0xFE);
	Write_Cmd(0xEF);

	Write_Cmd(0xEB);
	Write_Cmd_Data(0x14);

	Write_Cmd(0x84);
	Write_Cmd_Data(0x40);

	Write_Cmd(0x85);
	Write_Cmd_Data(0xFF);

	Write_Cmd(0x86);
	Write_Cmd_Data(0xFF);

	Write_Cmd(0x87);
	Write_Cmd_Data(0xFF);

	Write_Cmd(0x88);
	Write_Cmd_Data(0x0A);

	Write_Cmd(0x89);
	Write_Cmd_Data(0x21);

	Write_Cmd(0x8A);
	Write_Cmd_Data(0x00);

	Write_Cmd(0x8B);
	Write_Cmd_Data(0x80);

	Write_Cmd(0x8C);
	Write_Cmd_Data(0x01);

	Write_Cmd(0x8D);
	Write_Cmd_Data(0x01);

	Write_Cmd(0x8E);
	Write_Cmd_Data(0xFF);

	Write_Cmd(0x8F);
	Write_Cmd_Data(0xFF);


	Write_Cmd(0xB6);
	Write_Cmd_Data(0x00);
	Write_Cmd_Data(0x00); //0x00

	Write_Cmd(0x36);

	if(USE_HORIZONTAL==0)Write_Cmd_Data(0x18);
	else if(USE_HORIZONTAL==1)Write_Cmd_Data(0x28);
	else if(USE_HORIZONTAL==2)Write_Cmd_Data(0x48);
	else Write_Cmd_Data(0x88);



	Write_Cmd(0x3A);
	Write_Cmd_Data(0x05);


	Write_Cmd(0x90);
	Write_Cmd_Data(0x08);
	Write_Cmd_Data(0x08);
	Write_Cmd_Data(0x08);
	Write_Cmd_Data(0x08);

	Write_Cmd(0xBD);
	Write_Cmd_Data(0x06);

	Write_Cmd(0xBC);
	Write_Cmd_Data(0x00);

	Write_Cmd(0xFF);
	Write_Cmd_Data(0x60);
	Write_Cmd_Data(0x01);
	Write_Cmd_Data(0x04);

	Write_Cmd(0xC3);
	Write_Cmd_Data(0x13);
	Write_Cmd(0xC4);
	Write_Cmd_Data(0x13);

	Write_Cmd(0xC9);
	Write_Cmd_Data(0x22);

	Write_Cmd(0xBE);
	Write_Cmd_Data(0x11);

	Write_Cmd(0xE1);
	Write_Cmd_Data(0x10);
	Write_Cmd_Data(0x0E);

	Write_Cmd(0xDF);
	Write_Cmd_Data(0x21);
	Write_Cmd_Data(0x0c);
	Write_Cmd_Data(0x02);

	Write_Cmd(0xF0);
    Write_Cmd_Data(0x45);
    Write_Cmd_Data(0x09);
 	Write_Cmd_Data(0x08);
  	Write_Cmd_Data(0x08);
 	Write_Cmd_Data(0x26);
 	Write_Cmd_Data(0x2A);

 	Write_Cmd(0xF1);
 	Write_Cmd_Data(0x43);
 	Write_Cmd_Data(0x70);
 	Write_Cmd_Data(0x72);
 	Write_Cmd_Data(0x36);
 	Write_Cmd_Data(0x37);
 	Write_Cmd_Data(0x6F);


 	Write_Cmd(0xF2);
 	Write_Cmd_Data(0x45);
 	Write_Cmd_Data(0x09);
 	Write_Cmd_Data(0x08);
 	Write_Cmd_Data(0x08);
 	Write_Cmd_Data(0x26);
 	Write_Cmd_Data(0x2A);

 	Write_Cmd(0xF3);
 	Write_Cmd_Data(0x43);
 	Write_Cmd_Data(0x70);
 	Write_Cmd_Data(0x72);
 	Write_Cmd_Data(0x36);
 	Write_Cmd_Data(0x37);
 	Write_Cmd_Data(0x6F);

	Write_Cmd(0xED);
	Write_Cmd_Data(0x1B);
	Write_Cmd_Data(0x0B);

	Write_Cmd(0xAE);
	Write_Cmd_Data(0x77);

	Write_Cmd(0xCD);
	Write_Cmd_Data(0x63);


	Write_Cmd(0x70);
	Write_Cmd_Data(0x07);
	Write_Cmd_Data(0x07);
	Write_Cmd_Data(0x04);
	Write_Cmd_Data(0x0E);
	Write_Cmd_Data(0x0F);
	Write_Cmd_Data(0x09);
	Write_Cmd_Data(0x07);
	Write_Cmd_Data(0x08);
	Write_Cmd_Data(0x03);

	Write_Cmd(0xE8);
	Write_Cmd_Data(0x34);

	Write_Cmd(0x62);
	Write_Cmd_Data(0x18);
	Write_Cmd_Data(0x0D);
	Write_Cmd_Data(0x71);
	Write_Cmd_Data(0xED);
	Write_Cmd_Data(0x70);
	Write_Cmd_Data(0x70);
	Write_Cmd_Data(0x18);
	Write_Cmd_Data(0x0F);
	Write_Cmd_Data(0x71);
	Write_Cmd_Data(0xEF);
	Write_Cmd_Data(0x70);
	Write_Cmd_Data(0x70);

	Write_Cmd(0x63);
	Write_Cmd_Data(0x18);
	Write_Cmd_Data(0x11);
	Write_Cmd_Data(0x71);
	Write_Cmd_Data(0xF1);
	Write_Cmd_Data(0x70);
	Write_Cmd_Data(0x70);
	Write_Cmd_Data(0x18);
	Write_Cmd_Data(0x13);
	Write_Cmd_Data(0x71);
	Write_Cmd_Data(0xF3);
	Write_Cmd_Data(0x70);
	Write_Cmd_Data(0x70);

	Write_Cmd(0x64);
	Write_Cmd_Data(0x28);
	Write_Cmd_Data(0x29);
	Write_Cmd_Data(0xF1);
	Write_Cmd_Data(0x01);
	Write_Cmd_Data(0xF1);
	Write_Cmd_Data(0x00);
	Write_Cmd_Data(0x07);

	Write_Cmd(0x66);
	Write_Cmd_Data(0x3C);
	Write_Cmd_Data(0x00);
	Write_Cmd_Data(0xCD);
	Write_Cmd_Data(0x67);
	Write_Cmd_Data(0x45);
	Write_Cmd_Data(0x45);
	Write_Cmd_Data(0x10);
	Write_Cmd_Data(0x00);
	Write_Cmd_Data(0x00);
	Write_Cmd_Data(0x00);

	Write_Cmd(0x67);
	Write_Cmd_Data(0x00);
	Write_Cmd_Data(0x3C);
	Write_Cmd_Data(0x00);
	Write_Cmd_Data(0x00);
	Write_Cmd_Data(0x00);
	Write_Cmd_Data(0x01);
	Write_Cmd_Data(0x54);
	Write_Cmd_Data(0x10);
	Write_Cmd_Data(0x32);
	Write_Cmd_Data(0x98);

	Write_Cmd(0x74);
	Write_Cmd_Data(0x10);
	Write_Cmd_Data(0x85);
	Write_Cmd_Data(0x80);
	Write_Cmd_Data(0x00);
	Write_Cmd_Data(0x00);
	Write_Cmd_Data(0x4E);
	Write_Cmd_Data(0x00);

    Write_Cmd(0x98);
	Write_Cmd_Data(0x3e);
	Write_Cmd_Data(0x07);

	Write_Cmd(0x35);
	Write_Cmd(0x21);

	Write_Cmd(0x11);
	osDelay(120);
	Write_Cmd(0x29);
	osDelay(20);
}




//===============================================================
//clear screen
//point to point clear , slowly
void ClearScreen(unsigned int bColor)
{
 unsigned int i,j;

 LCD_SetPos(0,0,GC9A01_TFTWIDTH,GC9A01_TFTHEIGHT);//240x240

 LCD_DC_1;
 LCD_CS_0;

 for (i=0;i<GC9A01_TFTWIDTH;i++)
 {
	 for (j=0;j<GC9A01_TFTHEIGHT;j++)
		 Write_Data_U16(bColor);
 }

 LCD_CS_1;

}

//===============================================================
//clear screen2
//Use DMA，faster
void ClearScreen2(unsigned int bColor)
{
	ClearWindow(0,0,GC9A01_TFTWIDTH-1,GC9A01_TFTHEIGHT-1,bColor);
}

volatile uint8_t dma_busy = 0;

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi) {
    if (hspi->Instance == SPI2) {
        dma_busy = 0;
    }
}

void ClearWindow(unsigned int startX, unsigned int startY, unsigned int endX, unsigned int endY, unsigned int bColor)
{
 unsigned int i;

 //Exchange high 8bit and low 8bit of bColor for DMA batch transmit
 unsigned char hb = (bColor&0xFFFF) >> 8;
 unsigned char lb = bColor & 0xFF;
 unsigned short tempColor = lb * 256 + hb;

 unsigned int totalSize = (endX-startX) * (endY - startY) * 2; // total clear window data size
 unsigned int bufSize = 512;  // define bufSize, need less than DMA transmit size

 unsigned int loopNum = (totalSize - (totalSize % bufSize)) / bufSize; // transmit loop times
 unsigned int modNum = totalSize % bufSize;  // remainder data bytes


 //use a tempBuf to initial bColor data, bufSize < DMA transmit size
 static unsigned short tempBuf[512];
 unsigned char * ptempBuf;

 //init tempBuf data to tempColor( Exchange high 8bit and low 8bit of bColor )
 for(i=0; i<bufSize; i++){
	 tempBuf[i] = tempColor;
 }

 // Clear window size: from (startX, startY) to (endX, endY)
 LCD_SetPos(startX,startY,endX-1,endY-1);// (endX-startX) * (endY - startY)

 // transmit bufSize byte one time, loopNum loops
 ptempBuf = (unsigned char *)tempBuf;
 for(i=0; i<loopNum; i++){
	 dma_busy = 1;
	 Write_Bytes(ptempBuf, bufSize);
	 while(dma_busy);
 }

 // transmit remainder data, modNum bytes
 Write_Bytes(ptempBuf, modNum);

}


//===============================================================
 void LCD_SetPos(unsigned int Xstart,unsigned int Ystart,unsigned int Xend,unsigned int Yend)
{
	Write_Cmd(0x2a);
	Write_Cmd_Data(Xstart>>8);
	Write_Cmd_Data(Xstart& 0xff);
 	Write_Cmd_Data(Xend>>8);
	Write_Cmd_Data(Xend& 0xff);

	Write_Cmd(0x2b);
	Write_Cmd_Data(Ystart>>8);
	Write_Cmd_Data(Ystart);
	Write_Cmd_Data(Yend>>8);
	Write_Cmd_Data(Yend);

  	Write_Cmd(0x2c);//LCD_WriteCMD(GRAMWR);
}

static void Gc9a01a_WriteChar(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor) {
	 uint32_t i, b, j;

	 LCD_SetPos(x,y, x+font.width-1, y+font.height-1);
	 for(i = 0; i < font.height; i++) {
		 b = font.data[(ch - 32) * font.height + i];
		 for(j = 0; j < font.width; j++) {
			 if((b << j) & 0x8000)  {
				 Write_Data(color >> 8, color & 0xFF);
			 } else {
				 Write_Data(bgcolor >> 8, bgcolor & 0xFF);
			 }
		 }
	 }
}

void Gc9a01a_WriteString(uint16_t x, uint16_t y, const char* str, FontDef font, uint16_t color, uint16_t bgcolor) {

    while(*str) {
        if(x + font.width >= GC9A01_TFTWIDTH) {
            x = 0;
            y += font.height;
            if(y + font.height >= GC9A01_TFTHEIGHT) {
                break;
            }

            if(*str == ' ') {
                // skip spaces in the beginning of the new line
                str++;
                continue;
            }
        }

        Gc9a01a_WriteChar(x, y, *str, font, color, bgcolor);
        x += font.width;
        str++;
    }

}



 void LCD_DrawPoint(unsigned int x,unsigned int y,unsigned int color)
 {
 	LCD_SetPos(x,y,x,y);
 	Write_Data_U16(color);
 }


 void LCD_DrawLine(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int color)
 {
 	unsigned int t;
 	int xerr=0,yerr=0,delta_x,delta_y,distance;
 	int incx,incy,uRow,uCol;
 	delta_x=x2-x1;
 	delta_y=y2-y1;
 	uRow=x1;
 	uCol=y1;
 	if(delta_x>0)incx=1;
 	else if (delta_x==0)incx=0;
 	else {incx=-1;delta_x=-delta_x;}
 	if(delta_y>0)incy=1;
 	else if (delta_y==0)incy=0;
 	else {incy=-1;delta_y=-delta_x;}
 	if(delta_x>delta_y)distance=delta_x;
 	else distance=delta_y;
 	for(t=0;t<distance+1;t++)
 	{
 		LCD_DrawPoint(uRow,uCol,color);
 		xerr+=delta_x;
 		yerr+=delta_y;
 		if(xerr>distance)
 		{
 			xerr-=distance;
 			uRow+=incx;
 		}
 		if(yerr>distance)
 		{
 			yerr-=distance;
 			uCol+=incy;
 		}
 	}
 }


 void LCD_DrawRectangle(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2,unsigned int color)
 {
 	LCD_DrawLine(x1,y1,x2,y1,color);
 	LCD_DrawLine(x1,y1,x1,y2,color);
 	LCD_DrawLine(x1,y2,x2,y2,color);
 	LCD_DrawLine(x2,y1,x2,y2,color);
 }


 void Draw_Circle(unsigned int x0,unsigned int y0,unsigned char r,unsigned int color)
 {
 	int a,b;
 	a=0;b=r;
 	while(a<=b)
 	{
 		LCD_DrawPoint(x0-b,y0-a,color);             //3
 		LCD_DrawPoint(x0+b,y0-a,color);             //0
 		LCD_DrawPoint(x0-a,y0+b,color);             //1
 		LCD_DrawPoint(x0-a,y0-b,color);             //2
 		LCD_DrawPoint(x0+b,y0+a,color);             //4
 		LCD_DrawPoint(x0+a,y0-b,color);             //5
 		LCD_DrawPoint(x0+a,y0+b,color);             //6
 		LCD_DrawPoint(x0-b,y0+a,color);             //7
 		a++;
 		if((a*a+b*b)>(r*r))
 		{
 			b--;
 		}
 	}
 }

 void GC9A01A_FillScreen_NoDMA(uint16_t color)
 {
     uint32_t totalPixels = GC9A01_TFTWIDTH * GC9A01_TFTHEIGHT;

     // 컬러 셋용 준비 (높은 바이트 + 낮은 바이트)
     uint8_t hi = color >> 8;
     uint8_t lo = color & 0xFF;

     // 주소 범위 지정
     LCD_SetPos(0, 0, GC9A01_TFTWIDTH - 1, GC9A01_TFTHEIGHT - 1);

     // DC=1: 데이터 모드, CS=0: 선택
     LCD_DC_1;
     LCD_CS_0;

     // 모든 픽셀을 루프로 채움
     for (uint32_t i = 0; i < totalPixels; i++) {
         Write_Data(hi, lo);
     }

     LCD_CS_1;
 }


 //============================================================
 //show gray

 void DispRGBGray(void)
 {

 	unsigned int  A,B,C;
     unsigned int  i,j,k,DH;

     LCD_SetPos(0,0,GC9A01_TFTWIDTH-1,GC9A01_TFTHEIGHT-1);//240x240

 	for(k=0;k<60;k++)
 	{
     	A=0;
     	B=0;
     	C=0;
 		for(i=0;i<16;i++)
 		{
     		for(j=0;j<15;j++)
     		{
      			DH=(A<<11)+(B<<5)+C;
      			Write_Data_U16(DH);
     		}
     		A=A+2;
    			B=B+4;
     		C=C+2;
   		}
 	}

 	for(k=0;k<60;k++)
 	{
     	A=0;
     	B=0;
     	C=0;
 		for(i=0;i<16;i++)
 		{
     		for(j=0;j<15;j++)
     		{
      			DH=(A<<11)+B+C;
      			Write_Data_U16(DH);
     		}
     		A=A+2;
   		}
 	}

 	for(k=0;k<60;k++)
 	{
     	A=0;
     	B=0;
     	C=0;
 		for(i=0;i<16;i++)
 		{
     		for(j=0;j<15;j++)
     		{
      			DH=A+(B<<5)+C;
      			Write_Data_U16(DH);
     		}
     		B=B+4;
   		}
 	}

 	for(k=0;k<60;k++)
 	{
     	A=0;
     	B=0;
     	C=0;
 		for(i=0;i<16;i++)
 		{
     		for(j=0;j<15;j++)
     		{
      			DH=A+B+C;
      			Write_Data_U16(DH);
     		}
     		C=C+2;
   		}
 	}
 }

