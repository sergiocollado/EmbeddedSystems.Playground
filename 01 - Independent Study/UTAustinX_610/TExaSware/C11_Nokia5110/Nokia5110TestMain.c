// Nokia5110TestMain.c
// Runs on LM4F120/TM4C123
// Test the functions in Nokia5110.c by printing various
// things to the LCD.
// Daniel Valvano
// September 16, 2013

// Font table, initialization, and other functions based
// off of Nokia_5110_Example from Spark Fun:
// 7-17-2011
// Spark Fun Electronics 2011
// Nathan Seidle
// http://dlnmh9ip6v2uc.cloudfront.net/datasheets/LCD/Monochrome/Nokia_5110_Example.pde

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2013

 Copyright 2013 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// Blue Nokia 5110
// ---------------
// Signal        (Nokia 5110) LaunchPad pin
// Reset         (RST, pin 1) connected to PA7
// SSI0Fss       (CE,  pin 2) connected to PA3
// Data/Command  (DC,  pin 3) connected to PA6
// SSI0Tx        (Din, pin 4) connected to PA5
// SSI0Clk       (Clk, pin 5) connected to PA2
// 3.3V          (Vcc, pin 6) power
// back light    (BL,  pin 7) not connected
// Ground        (Gnd, pin 8) ground

// Red SparkFun Nokia 5110 (LCD-10168)
// -----------------------------------
// Signal        (Nokia 5110) LaunchPad pin
// 3.3V          (VCC, pin 1) power
// Ground        (GND, pin 2) ground
// SSI0Fss       (SCE, pin 3) connected to PA3
// Reset         (RST, pin 4) connected to PA7
// Data/Command  (D/C, pin 5) connected to PA6
// SSI0Tx        (DN,  pin 6) connected to PA5
// SSI0Clk       (SCLK, pin 7) connected to PA2
// back light    (LED, pin 8) not connected

#include "Nokia5110.h"
#include "PLL.h"

//  function delays 3*ulCount cycles
void Delay(unsigned long ulCount){
  do{
    ulCount--;
	}while(ulCount);
}

char troll [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x06,
0x06, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
0x02, 0x02, 0x02, 0x06, 0x06, 0x06, 0x04, 0x04, 0x04, 0x04, 0x0C, 0x0C, 0x0C, 0x08, 0x08, 0x18,
0x10, 0x30, 0x20, 0x40, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x60, 0x70, 0x38, 0x3C, 0x87, 0x81, 0xC0, 0x40,
0xC0, 0x80, 0x80, 0xA0, 0x00, 0x00, 0x30, 0x38, 0x38, 0x3C, 0xBC, 0xBC, 0x3C, 0x2C, 0x2C, 0x6C,
0x48, 0xD8, 0x70, 0x20, 0x00, 0x00, 0x00, 0x00, 0x40, 0xC0, 0xE0, 0x70, 0x70, 0x30, 0x38, 0x38,
0x38, 0x30, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0F, 0x18, 0x30, 0xE0, 0xC0, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0x00, 0x00, 0xFF, 0x18, 0x1C, 0x36, 0xE3, 0x81,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x7F, 0xC0, 0x80, 0x00, 0x1E, 0x77,
0x01, 0x18, 0x18, 0x7E, 0xE6, 0xCC, 0x89, 0x99, 0x11, 0x31, 0xF3, 0x23, 0x63, 0x41, 0x41, 0x40,
0xC0, 0x80, 0x80, 0xB8, 0xF8, 0x08, 0x28, 0x20, 0x20, 0x20, 0x00, 0x00, 0x80, 0x80, 0x87, 0x4C,
0x38, 0x38, 0x30, 0x00, 0x02, 0x06, 0x86, 0x86, 0xC3, 0xFD, 0xF1, 0x81, 0x03, 0x00, 0x00, 0xE0,
0x7F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x01, 0x03, 0x06, 0x18, 0x70, 0xC0, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0D, 0x11, 0x33, 0x7F, 0xC7,
0x86, 0x0C, 0x0C, 0x0C, 0x9C, 0xFC, 0x3F, 0x31, 0x31, 0x31, 0x71, 0x73, 0xF3, 0x7E, 0x72, 0xF2,
0xF2, 0xF2, 0xFE, 0xFE, 0xF2, 0xF2, 0xF2, 0xF2, 0xFF, 0xF9, 0xF1, 0xFF, 0xFC, 0xFD, 0xFF, 0x1F,
0x00, 0x00, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0C, 0x18, 0x10,
0x30, 0x20, 0x60, 0x40, 0xC0, 0x81, 0x83, 0x83, 0x07, 0x04, 0x04, 0x0C, 0x0C, 0x08, 0x08, 0x08,
0x0F, 0x08, 0x08, 0x08, 0x08, 0x0C, 0x0F, 0x08, 0x08, 0x0C, 0x0F, 0x08, 0x0C, 0x0F, 0x0C, 0x04,
0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x7F, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x02, 0x06,
0x04, 0x0C, 0x08, 0x08, 0x08, 0x18, 0x18, 0x10, 0x10, 0x30, 0x20, 0x20, 0x20, 0x60, 0x60, 0x60,
0x60, 0x60, 0x60, 0x60, 0x20, 0x20, 0x30, 0x10, 0x18, 0x0C, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};




char heejoo[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x20,
0x30, 0x30, 0x78, 0x78, 0x7E, 0x54, 0x74, 0x7E, 0x7E, 0x3E, 0x32, 0x16, 0x14, 0x64, 0xFC, 0x78,
0xF8, 0xF8, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x1C, 0x03,
0x01, 0x00, 0x00, 0x00, 0x80, 0xEC, 0xE4, 0xF6, 0xF2, 0xF2, 0xF2, 0xF2, 0xE2, 0xEA, 0xCE, 0x0A,
0x3E, 0xFC, 0xFC, 0xF9, 0x71, 0x61, 0x01, 0x07, 0xFC, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFC, 0xFC,
0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE4, 0xFE, 0xFF, 0xFE, 0xF0,
0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 0x42,
0x42, 0x42, 0x46, 0x7E, 0x32, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x01, 0x0E, 0x18, 0x30, 0x40, 0x80, 0x80, 0x3F, 0x7F, 0xFF, 0xF9, 0xF0, 0xE0, 0xE0, 0xE1,
0xFF, 0xFF, 0x7F, 0x1F, 0x03, 0xFF, 0xFF, 0xFF, 0xBE, 0x9E, 0x7E, 0x3E, 0x1F, 0x00, 0x00, 0x00,
0x00, 0x07, 0x0F, 0x1F, 0x1F, 0x0E, 0x0E, 0x0E, 0x0F, 0x0E, 0x1E, 0x1E, 0x1E, 0x0E, 0x19, 0x3D,
0x3F, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x1F, 0x00, 0x00, 0x00,
0x00, 0x7C, 0x04, 0x06, 0xFE, 0xC6, 0xC4, 0x6C, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x80, 0xC0, 0x60, 0x30, 0x10, 0x10, 0x08, 0x08, 0x08, 0x0C, 0x05, 0xE7, 0xF6, 0xF6, 0xE7,
0x07, 0x07, 0xFF, 0x3D, 0x6D, 0xCC, 0x04, 0x04, 0x04, 0x0F, 0x0F, 0x0F, 0x03, 0x01, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xE0, 0xF8, 0xFC, 0x7C, 0x3E, 0x1E, 0x3E, 0xFC,
0xFC, 0xFC, 0xF0, 0x00, 0x00, 0x07, 0x0F, 0x0F, 0x0F, 0x00, 0xC0, 0xE0, 0xF0, 0xF0, 0xF0, 0xF0,
0xE0, 0xC0, 0x07, 0x04, 0x04, 0xC4, 0x44, 0x64, 0x64, 0x64, 0x64, 0xC4, 0x04, 0x00, 0x04, 0x00,
0x00, 0x00, 0xE0, 0x38, 0x1C, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x0F, 0x1F, 0x1F, 0x1F, 0x1E, 0x1E, 0x1F, 0x3F, 0xFE, 0x1F, 0x1F, 0x1E, 0x1E, 0x1C, 0x20, 0x60,
0xC0, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1F, 0x3F, 0x3F, 0x7C,
0x78, 0x78, 0x78, 0x7F, 0x3F, 0x3F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07,
0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x87, 0xCC, 0x58, 0x58, 0x58, 0xC8, 0x8C,
0x03, 0x00, 0x00, 0x00, 0x3E, 0x67, 0x1F, 0x32, 0x06, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x1E, 0xF0, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x02, 0x02, 0x3E, 0x7C, 0x78, 0x40,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x18, 0x10,
0x10, 0x10, 0x18, 0x1D, 0x07, 0x00, 0x00, 0x00, 
};




//This is awesome in bitmap form
char awesome[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0x70, 0x30, 0x18, 0x1C,
  0x0C, 0x0C, 0x06, 0x06, 0x07, 0x07, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x07,
  0x07, 0x07, 0x0E, 0x06, 0x1C, 0x1C, 0x38, 0x70, 0x70, 0xE0, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xF0, 0x3C, 0xCE, 0x67, 0x33, 0x18, 0x08,
  0x08, 0xC8, 0xF8, 0xF0, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0,
  0x70, 0x38, 0x18, 0x18, 0x08, 0x08, 0x08, 0xF8, 0xF0, 0xF0, 0xE0, 0xC0, 0x00, 0x00, 0x01, 0x07,
  0x0F, 0x3C, 0xF8, 0xE0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0x0F, 0x00, 0x0C, 0x7F,
  0x60, 0x60, 0x60, 0x60, 0x60, 0x61, 0x61, 0x61, 0x61, 0x61, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x7F, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x61, 0x61, 0x61, 0x61, 0x63,
  0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF,
  0xF0, 0x00, 0x00, 0x00, 0x08, 0x08, 0xFC, 0x8C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C,
  0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C,
  0x0C, 0x0C, 0x0C, 0xF8, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0x1F, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x07, 0x0F, 0x3C, 0x70, 0xE0, 0x80, 0x00, 0x07, 0x0C, 0x38, 0x60, 0xC0,
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF0, 0xF0, 0xF8, 0xF8, 0xF8, 0xF8, 0xF0,
  0xF0, 0xE0, 0xC0, 0x80, 0xC0, 0x30, 0x18, 0x0F, 0x00, 0x00, 0x80, 0xC0, 0x70, 0x3C, 0x1F, 0x07,
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x06,
  0x0E, 0x1C, 0x18, 0x38, 0x31, 0x73, 0x62, 0x66, 0x64, 0xC7, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF,
  0xC7, 0xC7, 0xC7, 0x67, 0x63, 0x63, 0x71, 0x30, 0x38, 0x18, 0x1C, 0x0C, 0x06, 0x03, 0x03, 0x01,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
};


// image of a longhorn
const char Longhorn[] = {
  0x08, 0x08, 0x08, 0x08, 0x08, 0x18, 0x18, 0x18, 0x38, 0x30, 0x30, 0x30, 0x70, 0xF0,
  0xE0, 0xC0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xC0, 0xE0, 0xE0, 0xF0, 0x70,
  0x70, 0x30, 0x30, 0x18, 0x18, 0x18, 0x18, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x03, 0x03, 0x03, 0x07, 0x0F, 0x0E, 0x0C, 0x1C, 0x38, 0x38, 0xB8, 0xF8, 0xF0,
  0xF0, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xFC, 0xFC, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8,
  0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF0, 0xE0, 0xE0, 0xF0, 0xF0, 0xF0,
  0xF0, 0x78, 0x38, 0x3C, 0x1C, 0x1F, 0x0F, 0x07, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x0F, 0x0F, 0x0F, 0x0F,
  0x0F, 0x07, 0x07, 0x07, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x0F, 0x1F, 0x1F, 0x1F, 0x1F,
  0x1F, 0x1F, 0x1E, 0x0E, 0x04, 0x00, 0x00, 0x00, 0x0F, 0x05, 0x0B, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x7F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0x7F, 0x3F, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// image of a longhorn loves 319k
const char Longhorn2[] = {
  0x08, 0x08, 0x08, 0x08, 0x08, 0x18, 0x18, 0x18, 0x38, 0x30, 0x30, 0x30, 0x70, 0xF0,
  0xE0, 0xC0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xC0, 0xE0, 0xE0, 0xF0, 0x70,
  0x70, 0x30, 0x30, 0x18, 0x18, 0x18, 0x18, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00,
  0xF0, 0x08, 0x04, 0x24, 0x24, 0xE4, 0x24, 0x24, 0x04, 0x04, 0x04, 0x04, 0x04, 0x08,
  0xF1, 0x03, 0x03, 0x03, 0x07, 0x0F, 0x0E, 0x0C, 0x1C, 0x38, 0x38, 0xB8, 0xF8, 0xF0,
  0xF0, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xFC, 0xFC, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8,
  0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF0, 0xE0, 0xE0, 0xF0, 0xF0, 0xF0,
  0xF0, 0x78, 0x38, 0x3C, 0x1C, 0x1F, 0x0F, 0x07, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x04, 0x04, 0x07, 0x84, 0x44, 0x40, 0x80, 0x40, 0x40, 0x80, 0x00,
  0x00, 0x01, 0x02, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x0F, 0x0F, 0x0F, 0x0F,
  0x0F, 0x07, 0x07, 0x07, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x0F, 0x1F, 0x1F, 0x1F, 0x1F,
  0x1F, 0x1F, 0x1E, 0x0E, 0x04, 0x00, 0x00, 0x00, 0x0F, 0x05, 0x0B, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x84, 0x88, 0x84, 0x02, 0x01, 0x00,
  0x00, 0x80, 0x00, 0x00, 0x01, 0x82, 0x84, 0x84, 0x84, 0x04, 0x04, 0x84, 0x04, 0x04,
  0x84, 0x08, 0x10, 0xE0, 0x00, 0x01, 0x07, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x0F, 0x10, 0x20, 0x40, 0x80, 0x80, 0x80, 0x80, 0x88, 0x88, 0x8A, 0x85, 0x80, 0x80,
  0x89, 0x8F, 0x88, 0x80, 0x80, 0x83, 0x82, 0x82, 0x8F, 0x80, 0x80, 0x8F, 0x82, 0x85,
  0x88, 0x80, 0x80, 0x8F, 0x50, 0x20, 0x00, 0x3C, 0x7F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0x7F, 0x3F, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

int main(void){
  unsigned short count = 0;
  PLL_Init();                           // set system clock to 50 MHz
  Nokia5110_Init();
	for(count=0; count<1; count=count+1){
  //for(count=0; count<5; count=count+1){
    //Nokia5110_DrawFullImage(Longhorn);
	  //Nokia5110_DrawFullImage(awesome);
    //Delay(16666667);                    // delay ~1 sec at 50 MHz
    //Nokia5110_DrawFullImage(Longhorn2);
		Nokia5110_DrawFullImage(heejoo);
    Delay(36666667);                    // delay ~1 sec at 50 MHz
		Nokia5110_DrawFullImage(troll);
    Delay(26666667);
  }
  count = 0;
  Nokia5110_Clear();
//Nokia5110_OutString("************* LCD Test *************Letter: Num:------- ---- ");
	Nokia5110_OutString("*************Glenn Test*************Alpha:  Num:------- ---- ");
  Nokia5110_OutChar(127);               // print UT sign
  while(1){
    Nokia5110_SetCursor(5, 5);          // five leading spaces, bottom row
    Nokia5110_OutChar((count%26)+'A');
    Nokia5110_OutChar(' ');
    Nokia5110_OutUDec(count);
    Delay(8333333);                     // delay ~0.5 sec at 50 MHz
    count = count + 1;
  }
}