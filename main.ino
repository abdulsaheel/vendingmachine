/*
* File: main.c
* Author: Naveen Reddy
*
* Created on May 13, 2023, 2:26 PM
*/
// PIC16F877A Configuration Bit Settings
// 'C' source line config statements
// CONFIG
#pragma config FOSC = HS // Oscillator Selection bits (HS
oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT
disabled)
#pragma config PWRTE = OFF // Power-up Timer Enable bit
(PWRT disabled)
#pragma config BOREN = OFF // OFF Brown-out Reset Enable
bit (BOR enabled)
#pragma config LVP = OFF // OFF Low-Voltage (SingleSupply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has
PGM function; low-voltage programming enabled)
#pragma config CPD = OFF // Data EEPROM Memory Code
Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF // Flash Program Memory Write
Enable bits (Write protection off; all program memory may be
written to by EECON control)
#pragma config CP = OFF // Flash Program Memory Code
Protection bit (Code protection off)
#include <xc.h>
#include <stdio.h>
#include <string.h>
#include "lcd.h"
#include "Keypad.h"
/*
Hardware related definition
*/
//#define _XTAL_FREQ 20000000 //Crystal Frequency, used in delay
#define Baud_rate 9600
#define STARTED_A "MACHINE A Started"
#define STOPPED_A "MACHINE A Stopped"
#define STOPPED_B "MACHINE B Stopped"
#define STARTED_B "MACHINE B Started"



/*
Other Specific definition
*/
void system_init(void);
void Initialize_UART(void);
void UART_send_char(char bt);
void UART_send_string(char* st_pt);
void Operate_Relay(void);
//void timer_isr(void);
char UART_get_char(void);
char get_num(char ch);
int count = 0;
unsigned char txflag = 0;
unsigned int Tx_timer = 0;
long gen_delay=0;
///extern unsigned char ucNKP;
unsigned char RelayID ='A';
unsigned char _RL1 = 'A';
unsigned char _RL2 = 'B';
char Numeral = 0;
unsigned char SpChar = 0;
unsigned char units=0;
char hashcntr = 0;
unsigned char tens=0;
unsigned char tens_a = 0;
unsigned char tens_b = 0;
unsigned char units_a =0;
unsigned char units_b = 0;
unsigned char uckeycounter=0;
char ctempkey='n';
int RelayA_Holdtime = 0;
int RelayB_Holdtime = 0;
unsigned char TempHt=0;
unsigned char Relay1_flag = 0;
unsigned char Relay2_flag = 0;
unsigned char Start_timer = 0;
unsigned char Start_Btimer = 0;
unsigned int Seconds=0;
unsigned char Minutes = 0;
unsigned int RL2_Seconds = 0;
unsigned char RelayA_Minutes = 0;
//extern char Key;
//char UART_get_char()
//char UART_get_char()
//void timer_isr()
// Timer 0 ISR//
void __interrupt() Timer0()
{
 if(INTCONbits.TMR0IF==1) // Timer flag has been triggered due
to timer overflow
 {
 TMR0 = 100; //Load the timer Value
 INTCONbits.TMR0IF=0; // Clear timer interrupt flag
 count++;
 }
 //-------------------KEY SCANNER------------------------------------------//


 X_1 = 1; X_2 = 0; X_3 = 1; X_4 = 1;

if (Y_1 == 0)
 {
 uckeycounter++;
 if(uckeycounter > 60)
 {
 uckeycounter = 0;
 if (Y_1 == 0)
 ctempkey = '4';
 }
 }
if (Y_2 == 0)
 {
 uckeycounter++;
 if(uckeycounter > 60)
 {
 uckeycounter = 0;
 if (Y_2 == 0)
 {
 ctempkey = '5';
 }
 }
 }
if (Y_3 == 0)
 {
 uckeycounter++;
 if(uckeycounter > 60)
 {
 uckeycounter = 0;
 if (Y_3 == 0)
 ctempkey = '6';
 }
 }
if (Y_4 == 0)
 {
 uckeycounter++;
 if(uckeycounter > 60)
 {
 uckeycounter = 0;
 if (Y_4 == 0)
 ctempkey = 'B';
 }
 }

//---------------------------------------------------------------
-------//
X_1 = 0; X_2 = 1; X_3 = 1; X_4 = 1;
if (Y_1 == 0)
 {
 uckeycounter++;

 if(uckeycounter > 60)
 {
 uckeycounter = 0;
 if (Y_1 == 0)
 ctempkey = '1';
 }
 }
if (Y_2 == 0)
 {
 uckeycounter++;
 if(uckeycounter > 60)
 {
 uckeycounter = 0;
 if (Y_2 == 0)
 ctempkey = '2';
 }
 }
if (Y_3 == 0)
 {
 uckeycounter++;
 if(uckeycounter > 60)
 {
 uckeycounter = 0;
 if (Y_3 == 0)
 ctempkey = '3';
 }
 }
if (Y_4 == 0)
 {
 uckeycounter++;
 if(uckeycounter > 60)
 {
 uckeycounter = 0;
 if (Y_4 == 0)
 ctempkey = 'A';
 }
 }
//---------------------------------------------------------------
-------//
X_1 = 1; X_2 = 1; X_3 = 0; X_4 = 1;
if (Y_1 == 0)
 {
 uckeycounter++;
 if(uckeycounter > 60)
 {
 uckeycounter = 0;
 if (Y_1 == 0)
 ctempkey = '7';
 }
 }

if(Y_2 == 0)
 {
 uckeycounter++;
 if(uckeycounter > 60)
 {
 uckeycounter = 0;
 if (Y_2 == 0)
 ctempkey = '8';
 }
 }
if (Y_3 == 0)
 {
 uckeycounter++;
 if(uckeycounter > 60)
 {
 uckeycounter = 0;
 if (Y_3 == 0)
 ctempkey = '9';
 }
 }
if (Y_4 == 0)
 {
 uckeycounter++;
 if(uckeycounter > 60)
 {
 uckeycounter = 0;
 if (Y_4 == 0)
 ctempkey = 'C';
 }
 }
X_1 = 1; X_2 = 1; X_3 = 1; X_4 = 0;
if (Y_1 == 0)
 {
 uckeycounter++;
 if(uckeycounter > 60)
 {
 uckeycounter = 0;
 if (Y_1 == 0)
 ctempkey = '*';
 }
 }
if (Y_2 == 0)
 {
 uckeycounter++;
 if(uckeycounter > 60)
 {
 uckeycounter = 0;
 if (Y_2 == 0)
 ctempkey = '0';
 }
 }

if (Y_3 == 0)
 {
 uckeycounter++;
 if(uckeycounter > 60)
 {
 uckeycounter = 0;
 if (Y_3 == 0)
 ctempkey = '#';
 }
 }
if (Y_4 == 0)
 {
 uckeycounter++;
 if(uckeycounter > 60)
 {
 uckeycounter = 0;
 if (Y_4 == 0)
 ctempkey = 'D';
 }
 }
//return 'n';
 //Key = ctempkey;
//-------------------KEY SCANNER------------------------------------------//

 if (count == 510) //450
 {
 count=0;
 if((Relay1_flag==1)&&(Start_timer ==1))
 {
 Seconds++; //Increment seconds
 if(Seconds > RelayA_Holdtime*60)
 {
 RELAY1 = 1;
 RelayA_Holdtime = 0;
 Relay1_flag = 0;
 Start_timer = 0;
 Seconds = 0;
 tens_a = 0;
 units_a = 0;
 }
 }
 if((Relay2_flag==1)&&(Start_Btimer ==1))
 {
 RL2_Seconds++;
 if(RL2_Seconds > RelayB_Holdtime*60)
 {
 RELAY2 = 1;
 RelayB_Holdtime = 0;
 Relay2_flag = 0;
 Start_Btimer = 0;

 RL2_Seconds = 0;
 tens_b = 0;
 units_b = 0;
 }
 }
 GREEN_LED_ON =~GREEN_LED_ON;
 }

 Tx_timer++;
 if(Tx_timer>=1000) //250
 {
 Tx_timer = 0;
 }
 gen_delay++;
 if(gen_delay > 4000)
 {
 gen_delay = 0;
 //RELAY2 = ~RELAY2;
 txflag = 1; // hscnd will get incremented for every half second
 }

 if(SpChar=='#')
 {
 hashcntr++;
 if(hashcntr>3)
 {
 hashcntr = 0;
 units = 0;
 tens = 0;
 //digit = 0;
 units_a = 0;
 units_b = 0;
 tens_a = 0;
 tens_b = 0;
 RelayA_Holdtime = 0;
 RelayB_Holdtime= 0;
 RelayID = 'A';
 SpChar = 'n';
 }
 }
}
void main(void)
{
 unsigned char get_value; //88/
 char Key = 'n'; //88/
 char temp = 0;
 char digit = 0;
 //unsigned char number = 0;


 system_init();
 Initialize_UART(); //Initialize UART module
 //delay(100);
 /*****Port Configuration for Timer ******/
 OPTION_REG = 0b00000101; // Timer0 with external freq and 64 as prescalar // Also Enables PULL UPs
 //OPTION_REG &= 0x7F;

 TMR0 = 100; // Load the time value for 2ms; delayValue
can be between 0-256 only
 INTCONbits.TMR0IE = 1; //Enable timer interrupt bit in
PIE1 register

 INTCONbits.GIE=1;
 INTCONbits.PEIE=1;

 RELAY1 = 1;
 RELAY2 = 1;
 RELAY3 = 1;
 RELAY4 = 1;

 while(1)
 {
 //Key = switch_press_scan();
 Key = ctempkey;
 if((Key=='A')||(Key=='B')||(Key=='C')||(Key=='D'))
 {
 RelayID = Key;
 Key = 'n';
 digit = 0;
 }
 else
if((Key=='0')||(Key=='1')||(Key=='2')||(Key=='3')||(Key=='4')||(Key=='5')||(Key=='6')||(Key=='7')||(Key=='8')||(Key=='9'))
 {
 switch (digit)
 {
 case 0:
 tens = Key;
 if (tens >= '0' && tens <= '9')
 {
 tens = tens - '0';
 }
 //tens = temp<<4;
 digit = 1;
 if(RelayID=='A')
 {
 tens_a = tens;
 TempHt = tens_a*10; //
 }
 if(RelayID=='B')
 {

 tens_b = tens;
 TempHt = tens_b*10; //
 }
 break;
 case 1:
 units = Key;
 if (units >= '0' && units <= '9')
 {
 units = units - '0';
 }
 if(RelayID=='A')
 {
 units_a = units;
 RelayA_Holdtime = TempHt + units_a;
 TempHt = 0;
 }
 if(RelayID=='B')
 {
 units_b = units;
 RelayB_Holdtime = TempHt + units_b;
 TempHt = 0;
 }
 break;
 default:
 Key = 'n';
 tens = 0;
 units = 0;
 }
 }
 else if((Key=='*')||(Key=='#'))
 {
 SpChar = Key;
 Key = 'n';
 }
 else
 {
 temp = 0;
 }
 if(txflag ==1)
 {
 if((Relay1_flag==1)&&(Start_timer==1))
 {
 UART_send_char(0x20);//ASCII value 10 is used for carriage return (to print in new line)
//  UART_send_char(_RL1);
//  UART_send_char(tens_a);
//   UART_send_char(units_a);
//  UART_send_char(SpChar);
//  UART_send_char(0x20);//ASCII value 10 is used for carriage return (to print in new line)
//  UART_send_char(RelayA_Holdtime);
  Serial.println(STARTED_A);

 }
  else{
  Serial.println(ENDED_A)
   }
 if(( Relay2_flag == 1)&&(Start_Btimer == 1))
 {
//  UART_send_char(0x20);//ASCII value 10 is used for carriage return (to print in new line)
//  UART_send_char(_RL2);
//  UART_send_char(tens_b);
//  UART_send_char(units_b);
//  UART_send_char(SpChar);
//  UART_send_char(0x20);//ASCII value 10 is used for
// carriage return (to print in new line)
//  UART_send_char(RelayB_Holdtime);
  Serial.println(STARTED_B);
 }
  else{
   Serial.println(ENDED_B)
  }
 txflag = 0;
 }
 __delay_ms(500);
 Operate_Relay();

 /*
 get_value = UART_get_char();
 if (get_value == '1') //If the user sends "1"
 {
 ///RB3=1; //Turn on LED
 RED_LED_ON = 0;
 UART_send_string("RED LED -> ON"); //Send
notification to the computer
 UART_send_char(10);//ASCII value 10 is used for
carriage return (to print in new line)
 }
 if (get_value == '0') //If the user sends "0"
 {
 //RB3=0; //Turn off LED
 RED_LED_ON = 1;
 UART_send_string("RED -> OFF"); //Send notification to
the computer
 UART_send_char(10);//ASCII value 10 is used for
carriage return (to print in new line)
 }
 */
 }
}
/*
* System Init
*/
void Operate_Relay(void)
{
 switch (RelayID)
 {
 case 'A':

 if((RelayID =='A')&&(SpChar =='*')&&(Start_timer==0))
 {

if((RelayA_Holdtime>0)&&(RelayA_Holdtime<99))
 {
 __delay_ms(1000);
 RELAY1 = 0;
 Relay1_flag = 1;
 Start_timer = 1;
 Seconds = 0;
 RelayID = 'B';
 }
 else
 {
 RelayA_Holdtime = 0;
 //RELAY1 = 1;
 }
 }

 RELAY4 = 1;
 RELAY3 = 1;
 //RELAY2 = 1;
 break;
 case 'B':
 if((RelayID =='B')&&(SpChar
=='*')&&(Start_Btimer==0))
 {

if((RelayB_Holdtime>0)&&(RelayB_Holdtime<99))
 {
 __delay_ms(1000);
 RELAY2 = 0;
 Relay2_flag = 1;
 Start_Btimer = 1;
 RL2_Seconds = 0;
 RelayID = 'E';
 }
 else
 {
 RelayB_Holdtime = 0;
 //RELAY1 = 1;
 }
 }


 RELAY4 = 1;
 RELAY3 = 1;
 //RELAY2 = 1;
 //RELAY1 = 1;
 break;
 case 'C':


 RELAY4 = 1;
 //RELAY3 = 0;
 RELAY2 = 1;
 RELAY1 = 1;
 break;
 case 'D':

 //RELAY4 = 0;
 RELAY3 = 1;
 RELAY2 = 1;
 RELAY1 = 1;
 break;
 default:

 RELAY4 = 1;
 RELAY3 = 1;
 //RELAY2 = 1;
 //RELAY1 = 1;
 __delay_ms(1);

 if((RelayID =='A')&&(SpChar
=='*')&&(Start_timer==0))
 {
 TempHt = tens_a*10; //
 RelayA_Holdtime = TempHt + units_a;
 TempHt = 0;

 if(RelayA_Holdtime>0)
 {
 __delay_ms(1000);
 RELAY1 = 0;
 Relay1_flag = 1;
 Start_timer = 1;
 Seconds = 0;
 }
 else
 {
 RelayA_Holdtime = 0;
 //RELAY1 = 1;
 }

 }

 else if((RelayID =='B')&&(SpChar
=='*')&&(Start_Btimer==0))
 {
 TempHt = tens_b*10; //
 RelayB_Holdtime = TempHt + units_b;
 TempHt = 0;

 if(RelayB_Holdtime>0)

 {
 __delay_ms(1000);
 RELAY2 = 0;
 Relay2_flag = 1;
 Start_Btimer = 1;
 RL2_Seconds = 0;
 }
 else
 {
 RelayB_Holdtime = 0;
 //RELAY1 = 1;
 }
 }
 }
}
void system_init(void)
{
 TRISD = 0x40;
 PORTD = 0X00;
 //InitKeypad();
 Keypad_PORT = 0x00; // Set Keypad port pin values zero
 Keypad_PORT_Direction = 0xF0; // Last 4 pins input, First
4 pins output
 OPTION_REG = 0x05;
//OPTION_REG &= 0x7F;
 PORTC = 0x00;
 TRISC4 = 0;
}
void Initialize_UART(void)
{
 //****Setting I/O pins for UART****//
 TRISC6 = 0; // TX Pin set as output
 TRISC7 = 1; // RX Pin set as input

 /**Initialize SPBRG register for required
 baud rate and set BRGH for fast baud_rate**/
 //SPBRG = ((_XTAL_FREQ/16)/Baud_rate) - 1;
 SPBRG = 129; //
 TXSTAbits.BRGH = 1; // for high baud_rate

 //****Enable Asynchronous serial port*******//
 TXSTAbits.SYNC = 0; // Asynchronous
 RCSTAbits.SPEN = 1; // Enable serial port pins

 //**Lets prepare for transmission & reception**//
 TXSTAbits.TXEN = 1; // enable transmission
 RCSTAbits.CREN = 1; // enable reception

 //**Select 8-bit mode**//
 TXSTAbits.TX9 = 0; // 8-bit reception selected

 RCSTAbits.RX9 = 0; // 8-bit reception mode selected

}
//**Function to send one byte of date to UART**//
void UART_send_char(char bt)
{
 //TXREG = bt; //Load the transmitter buffer with the received
value
 //while(!TXIF); // hold the program till TX buffer is free

//TXEN = 1;
while (!TXSTAbits.TRMT);
 TXREG = bt;
}
//**Function to get one byte of date from UART**//
char UART_get_char()
{
 if(RCSTAbits.OERR) // check for Error
 {
 RCSTAbits.CREN = 0; //If error -> Reset
 RCSTAbits.CREN = 1; //If error -> Reset
 }
 while(!RCIF); // hold the program till RX buffer is free
 return RCREG; //receive the value and send it to main
function
}
//**Function to convert string to byte**//
void UART_send_string(char* st_pt)
{
 while(*st_pt) //if there is a char
 UART_send_char(*st_pt++); //process it as a byte data
}
