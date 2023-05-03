#include <stdio.h>
#include <stdlib.h>
#include "NUC100Series.h"
#include "MCU_init.h"
#include "SYS_init.h"
#include "LCD.h"
#include "Draw2D.h"
#include "Seven_Segment.h"
#include "Scankey.h"

#define  DELAY_TIME 500000

unsigned char DrawBuffer[128*8]; // display buffer

unsigned char bmp_mouse[16] = {
	0x00,0x70,0x18,0x7D,0x36,0x34,0x3C,0x3C,0x3C,0x3C,0x34,0x36,0x7D,0x18,0x70,0x00};

unsigned char cover[128*8] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0x60,0x20,0x30,0x10,0x10,0x18,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x18,0x10,0x10,0x30,0x20,0x60,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x70,0x1C,0x06,0x03,0x01,0x00,0x40,0x40,0xC0,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0xC0,0x40,0x40,0x00,0x01,0x03,0x06,0x1C,0x70,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x1F,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x08,0x38,0x28,0x38,0x00,0x00,0xC0,0x40,0xC0,0x00,0x00,0x38,0x28,0x38,0x08,0x08,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x1F,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x3F,0x20,0x20,0x20,0x20,0x20,0x25,0x25,0x25,0x20,0x20,0x20,0x20,0x20,0x2C,0x26,0x3F,0x31,0x3F,0x31,0x3F,0x26,0x2C,0x20,0x20,0x20,0x20,0x20,0x25,0x25,0x25,0x20,0x20,0x20,0x20,0x20,0x3F,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x3C,0xC0,0xF0,0x0E,0x07,0x3C,0xC0,0xF0,0x0F,0x01,0x00,0xFF,0x04,0x04,0x0C,0xF8,0x00,0x60,0x94,0x94,0x94,0xF8,0x00,0x30,0x48,0x84,0x84,0x84,0x00,0x00,0xFF,0x30,0x48,0x84,0x84,0x00,0x10,0x10,0x10,0x00,0x60,0x94,0x94,0x94,0xF8,0x00,0x00,0x10,0x10,0x10,0x00,0x00,0xFC,0x04,0x04,0xFC,0x08,0x04,0x04,0xF8,0x00,0x30,0xCC,0x84,0x84,0x84,0x78,0x00,0x00,0xFF,0x00,0x70,0xDC,0x94,0x94,0x98,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

void displayRound(uint16_t round)
{
	uint8_t digit;
	uint16_t tmp=round;
	digit = round / 1000;
	CloseSevenSegment();
	if(digit!=0) ShowSevenSegment(3,digit);
	CLK_SysTickDelay(5000);
			
	round = round - digit * 1000;
	digit = round / 100;
	CloseSevenSegment();
	if(digit!=0) ShowSevenSegment(2,digit);
	CLK_SysTickDelay(5000);

	round = round - digit * 100;
	digit = round / 10;
	CloseSevenSegment();
	if(digit!=0) ShowSevenSegment(1,digit);
	CLK_SysTickDelay(5000);

	round = round - digit * 10;
	digit = round;
	CloseSevenSegment();
	if(digit!=0) ShowSevenSegment(0,digit);
	CLK_SysTickDelay(5000);
	
	displayRound((tmp*10)%10000);
}

void Display_7seg(uint16_t value)
{
	uint8_t digit;
	digit = value / 1000;
	CloseSevenSegment();
	ShowSevenSegment(3,digit);
	CLK_SysTickDelay(1500);
			
	value = value - digit * 1000;
	digit = value / 100;
	CloseSevenSegment();
	ShowSevenSegment(2,digit);
	CLK_SysTickDelay(1500);

	value = value - digit * 100;
	digit = value / 10;
	CloseSevenSegment();
	ShowSevenSegment(1,digit);
	CLK_SysTickDelay(1500);

	value = value - digit * 10;
	digit = value;
	CloseSevenSegment();
	ShowSevenSegment(0,digit);
	CLK_SysTickDelay(1500);
	CloseSevenSegment();
}

void Display_7(uint8_t digit)
{
	CloseSevenSegment();
	ShowSevenSegment(0,digit);
}

void Buzz(int8_t no)
{
	while(no!=0) {
		PB11=0;
		CLK_SysTickDelay(50000);
		PB11=1;
		CLK_SysTickDelay(50000);
		no--;
	}
}

void Init_Buzz(void)
{
	GPIO_SetMode(PB, BIT11, GPIO_PMD_OUTPUT);
	PB11=1;
}

int main(void)
{
	uint8_t i,j, keyin, life;
	int count;
	long int delay = DELAY_TIME;
	char text[25];
	SYS_Init();
	init_LCD();
	clear_LCD();
	OpenSevenSegment();
	OpenKeyPad();
	GPIO_SetMode(PC, BIT12, GPIO_MODE_OUTPUT);
	Init_Buzz();
	draw_LCD(cover);
	for (i=0;i<4;i++) CLK_SysTickDelay(1000000);
	clear_LCD();
	
	count=0, life=4;
	while(1) {	
		i = rand() % 9 + 1;
		if( count>0 &&(count/10>(count-1)/10)) delay = delay/2;
		draw_Line(24,20,101,20,FG_COLOR, BG_COLOR);  // draw a line
		draw_Line(24,41,101,41,FG_COLOR, BG_COLOR);  // draw a line
		draw_Line(50,0,50,63,FG_COLOR, BG_COLOR);  // draw a line
		draw_Line(76,0,76,63,FG_COLOR, BG_COLOR);  // draw a line
		draw_Line(24,0,101,0,FG_COLOR, BG_COLOR);  // draw a line
		draw_Line(24,63,101,63,FG_COLOR, BG_COLOR);  // draw a line
		draw_Line(24,0,24,63,FG_COLOR, BG_COLOR);  // draw a line
		draw_Line(101,0,101,63,FG_COLOR, BG_COLOR);  // draw a line
		switch(i) {  
			case 1: draw_Bmp16x8(30, 8,FG_COLOR,BG_COLOR, bmp_mouse);
					break;
			case 2: draw_Bmp16x8(56, 8,FG_COLOR,BG_COLOR, bmp_mouse);
					break;
			case 3: draw_Bmp16x8(82, 8,FG_COLOR,BG_COLOR, bmp_mouse);
					break;
			case 4: draw_Bmp16x8(30, 28,FG_COLOR,BG_COLOR, bmp_mouse);
					break;
			case 5: draw_Bmp16x8(56, 28,FG_COLOR,BG_COLOR, bmp_mouse);
					break;
			case 6: draw_Bmp16x8(82, 28,FG_COLOR,BG_COLOR, bmp_mouse);
					break;
			case 7: draw_Bmp16x8(30, 49,FG_COLOR,BG_COLOR, bmp_mouse);
					break;
			case 8: draw_Bmp16x8(56, 49,FG_COLOR,BG_COLOR, bmp_mouse);
					break;
			case 9: draw_Bmp16x8(82, 49,FG_COLOR,BG_COLOR, bmp_mouse);
					break;
			default:break;
		}	
		for(j=0;j<3;j++)
		{
			CLK_SysTickDelay(delay);
			keyin=ScanKey();
			if(keyin==i)
			{
				count++;
				Buzz(1);
				break;
			}
		}
		if(keyin!=i)
			life--;
		switch(life) {
			case 1:
				PC12 = 0;
				PC13 = PC14 = PC15 = 1;
				break;
			case 2:
				PC12 = PC13 = 0;
				PC14 = PC15 = 1;
				break;
			case 3:
				PC12 = PC13 = PC14 = 0;
				PC15 = 1;
				break;
			case 4:
				PC12 = PC13 = PC14 = PC15 = 0;
				break;
			default:
				PC12 = PC13 = PC14 = PC15 = 1;
				break;
		}
		if(life==0) break;
		switch(i) {  
			case 1: draw_Bmp16x8(30, 8,BG_COLOR,FG_COLOR, bmp_mouse);
					break;
			case 2: draw_Bmp16x8(56, 8,BG_COLOR,FG_COLOR, bmp_mouse);
					break;
			case 3: draw_Bmp16x8(82, 8,BG_COLOR,FG_COLOR, bmp_mouse);
					break;
			case 4: draw_Bmp16x8(30, 28,BG_COLOR,FG_COLOR, bmp_mouse);
					break;
			case 5: draw_Bmp16x8(56, 28,BG_COLOR,FG_COLOR, bmp_mouse);
					break;
			case 6: draw_Bmp16x8(82, 28,BG_COLOR,FG_COLOR, bmp_mouse);
					break;
			case 7: draw_Bmp16x8(30, 49,BG_COLOR,FG_COLOR, bmp_mouse);
					break;
			case 8: draw_Bmp16x8(56, 49,BG_COLOR,FG_COLOR, bmp_mouse);
					break;
			case 9: draw_Bmp16x8(82, 49,BG_COLOR,FG_COLOR, bmp_mouse);
					break;
			default:break;
		}
		for(j = 0; j < 125; j++)
			Display_7seg(count);
	}
	PB11=1;
	clear_LCD();
	sprintf(text,"FINAL SCORE: %3d",count);
	printS(1, 30, text);
	return 0;
}