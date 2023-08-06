#include <avr/io.h>
#define F_CPU 8000000UL
#include "util/delay.h"

#define ctrl PORTC
#define RS 0
#define RW 1
#define EN 2

#define Dataout PORTD

void LCD_cmd(unsigned char Command);
void LCD_init(void);
void LCD_data(unsigned char Data);
unsigned char i;
unsigned char j;

int main(void)
{
	char string[] ="Hello Mayank";
	char string1[] ="Welcome";
	DDRD=0xFF;
	DDRC =0xFF;
	LCD_init();
	while(string[i]!='\0')
	{
		LCD_data(string[i]);
		i++;
	}
	LCD_cmd(0xC0);
	while(string1[j]!='\0')
	{
		LCD_data(string1[j]);
		j++;
	}
}

void LCD_init(void)
{
	LCD_cmd(0x38); // 8bit mode
	LCD_cmd(0x06); // Entry mode
	LCD_cmd(0x01);  // Clear Display
	LCD_cmd(0x80); // 1st row and 1st position
	LCD_cmd(0x0E); // Display on cursor on
}

void LCD_cmd(unsigned char Command)
{
	Dataout = Command;
	ctrl = (0<<RS)|(0<<RW)|(1<<EN); // RS=0 for instruction/command
	_delay_ms(1);
	ctrl = (0<<RS)| (0<< RW)|(0<<EN);
	_delay_ms(50);
}

void LCD_data(unsigned char Data)
{
	Dataout = Data;
	ctrl= (1<<RS)| (0<<RW)| (1<<EN);  // RS=1 for data
	_delay_ms(1);
	ctrl = (1<<RS | (0<<RW)|(0<<EN));
	_delay_ms(50);
}