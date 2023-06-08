/*
 * File:   main.c
 * Author: Naveen Reddy
 * 
 * Created on May 13, 2023, 2:26 PM
 */

// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF       // OFF Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF         // OFF Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

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
unsigned char _RL3 = 'C';
unsigned char _RL4 = 'D';
char Numeral = 0;
unsigned char SpChar = 0;
unsigned char units=0;
char hashcntr = 0;
unsigned char tens=0;
unsigned char tens_a = 0;
unsigned char tens_b = 0;
unsigned char tens_c = 0;
unsigned char tens_d = 0;

unsigned char units_a =0;
unsigned char units_b = 0;
unsigned char units_c = 0;
unsigned char units_d = 0;

unsigned char uckeycounter=0;
char ctempkey='n';
int RelayA_Holdtime = 0;
int RelayB_Holdtime = 0;
int RelayC_Holdtime = 0;
int RelayD_Holdtime = 0;
unsigned char TempHt=0;

unsigned char Relay1_flag = 0;
unsigned char Relay2_flag = 0;
unsigned char Relay3_flag = 0;
unsigned char Relay4_flag = 0;

unsigned char Start_timer = 0;
unsigned char Start_Btimer = 0;
unsigned char Start_Ctimer = 0;
unsigned char Start_Dtimer = 0;

unsigned int Seconds=0;
unsigned char Minutes = 0;
unsigned int RL2_Seconds = 0;
unsigned int RL3_Seconds = 0;
unsigned int RL4_Seconds = 0;
char message[20];
//unsigned char RelayA_Minutes = 0;

//extern char Key;
//char UART_get_char()   
//char UART_get_char()  
//void timer_isr()

// Timer 0 ISR//
void __interrupt() Timer0()
{  
    if(INTCONbits.TMR0IF==1) // Timer flag has been triggered due to timer overflow
    {
        TMR0 = 100;     //Load the timer Value
        INTCONbits.TMR0IF=0;       // Clear timer interrupt flag
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

    //----------------------------------------------------------------------//
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
//----------------------------------------------------------------------//
	
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
    
    if (count == 510)   //450
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
        if((Relay3_flag==1)&&(Start_Ctimer ==1))
        {
            RL3_Seconds++;
            if(RL3_Seconds > RelayC_Holdtime*60)
            {
               RELAY3 = 1;
               RelayC_Holdtime = 0;
               Relay3_flag = 0;
               Start_Ctimer = 0;
               RL3_Seconds = 0;
               tens_c = 0;
               units_c = 0;               
            }
        }        
        if((Relay4_flag==1)&&(Start_Dtimer ==1))
        {
            RL4_Seconds++;
            if(RL4_Seconds > RelayD_Holdtime*60)
            {
               RELAY4 = 1;
               RelayD_Holdtime = 0;
               Relay4_flag = 0;
               Start_Dtimer = 0;
               RL4_Seconds = 0;
               tens_d = 0;
               units_d = 0;               
            }
        }        

        if(RED_LED_ON ==1)
        {
           //RED_LED_ON =0;
            //RELAY1 = 0;
        }
        else
        {
            //RED_LED_ON =1;  
            //RELAY1 = 1;
        }        
        GREEN_LED_ON =~GREEN_LED_ON;          
    }
    
    //Tx_timer++;
    //if(Tx_timer>=1000)   //250
    {
        //Tx_timer = 0;
        if(SpChar=='#')
        {
            Tx_timer++;
            if(Tx_timer>500)
            {
                Tx_timer = 0;
                units = 0;
                tens = 0;
                //digit = 0;
                units_a = 0;
                units_b = 0;
                units_c = 0;
                units_d = 0;

                tens_a = 0;
                tens_b = 0;
                tens_c = 0;
                tens_d = 0;

                RelayA_Holdtime = 0;
                RelayB_Holdtime= 0;
                RelayC_Holdtime = 0;
                RelayD_Holdtime= 0;

                RelayID = 'A';  //A
                SpChar = 'n';
            }
            else
            {
                //Tx_timer = 0;
            }
        }
        else
        {
            Tx_timer = 0;
        }

    }
 
    gen_delay++;
    if(gen_delay > 4000)
    {
       gen_delay = 0;
       //RELAY2 = ~RELAY2;
       txflag = 1;   // hscnd will get incremented for every half second    
    }
    
}

void main(void)
{
    unsigned char get_value;   //88/
    char Key = 'n';   //88/
    char temp = 0;
    char digit = 0;
    //unsigned char number = 0;
    
    system_init();
    Initialize_UART();    //Initialize UART module
    //delay(100);
        /*****Port Configuration for Timer ******/
    OPTION_REG = 0b00000101;  // Timer0 with external freq and 64 as prescalar // Also Enables PULL UPs
    //OPTION_REG &= 0x7F;
    
    TMR0 = 100;       // Load the time value for 0.0019968s; delayValue can be between 0-256 only
    INTCONbits.TMR0IE = 1;       //Enable timer interrupt bit in PIE1 register
    //GIE=1;          //Enable Global Interrupt
    //PEIE=1;         //Enable the Peripheral Interrupt
  
    INTCONbits.GIE=1;
    INTCONbits.PEIE=1;
    /***********______***********/ 
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
        else if((Key=='0')||(Key=='1')||(Key=='2')||(Key=='3')||(Key=='4')||(Key=='5')||(Key=='6')||(Key=='7')||(Key=='8')||(Key=='9'))
        {            
          switch (digit) 
          {
                case 0:
                tens  = Key;
                if (tens >= '0' && tens <= '9')
                {
                    tens = tens - '0';    
                }
                //tens = temp<<4;
                digit = 1;
                if(RelayID=='A')
                {
                    tens_a = tens;
                    TempHt = tens_a*10;   //
                }
                if(RelayID=='B')
                {
                    tens_b = tens;                    
                    TempHt = tens_b*10;   //
                }
                if(RelayID=='C')
                {
                    tens_c = tens;                    
                    TempHt = tens_c*10;   //
                }
                if(RelayID=='D')
                {
                    tens_d = tens;                    
                    TempHt = tens_d*10;   //
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
                if(RelayID=='C')
                {
                    units_c = units;
                    RelayC_Holdtime = TempHt + units_c;
                    TempHt = 0;
                }
                if(RelayID=='D')
                {
                    units_d = units;
                    RelayD_Holdtime = TempHt + units_d;
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
                /*
                UART_send_char(0x20);//ASCII value 10 is used for carriage return (to print in new line)
                UART_send_char(_RL1);
                UART_send_char(tens_a);
                UART_send_char(units_a);                        
                UART_send_char(SpChar);
                UART_send_char(0x20);//ASCII value 10 is used for carriage return (to print in new line)
                UART_send_char(RelayA_Holdtime);
                */
                sprintf(message, "%c%c%c%c%c%c%c",0x20,_RL1,tens_a,units_a,SpChar,0x20,RelayA_Holdtime);
                UART_send_string(message);                
            }
            if(( Relay2_flag == 1)&&(Start_Btimer == 1))                    
            {
                /*
                UART_send_char(0x20);//ASCII value 10 is used for carriage return (to print in new line)
                UART_send_char(_RL2);
                UART_send_char(tens_b);
                UART_send_char(units_b);                        
                UART_send_char(SpChar);
                UART_send_char(0x20);//ASCII value 10 is used for carriage return (to print in new line)
                UART_send_char(RelayB_Holdtime); 
                */             
                sprintf(message, "%c%c%c%c%c%c%c",0x20,_RL2,tens_b,units_b,SpChar,0x20,RelayB_Holdtime);
                UART_send_string(message);                
            }
            if(( Relay3_flag == 1)&&(Start_Ctimer == 1))                    
            {
                /*
                UART_send_char(0x20);//ASCII value 10 is used for carriage return (to print in new line)
                UART_send_char(_RL3);
                UART_send_char(tens_c);
                UART_send_char(units_c);                        
                UART_send_char(SpChar);
                UART_send_char(0x20);//ASCII value 10 is used for carriage return (to print in new line)
                UART_send_char(RelayC_Holdtime); 
                */                
                sprintf(message, "%c%c%c%c%c%c%c",0x20,_RL3,tens_c,units_c,SpChar,0x20,RelayC_Holdtime);
                UART_send_string(message);               
            }
            if(( Relay4_flag == 1)&&(Start_Dtimer == 1))                    
            {
                /*
                UART_send_char(0x20);//ASCII value 10 is used for carriage return (to print in new line)
                UART_send_char(_RL4);
                UART_send_char(tens_d);
                UART_send_char(units_d);                        
                UART_send_char(SpChar);
                UART_send_char(0x20);//ASCII value 10 is used for carriage return (to print in new line)
                UART_send_char(RelayD_Holdtime); 
                */                
                sprintf(message, "%c%c%c%c%c%c%c",0x20,_RL4,tens_d,units_d,SpChar,0x20,RelayD_Holdtime);
                UART_send_string(message);            
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
            UART_send_string("RED LED -> ON"); //Send notification to the computer 
            UART_send_char(10);//ASCII value 10 is used for carriage return (to print in new line)
        }
        if (get_value == '0') //If the user sends "0"
        {
           //RB3=0; //Turn off LED
           RED_LED_ON = 1; 
           UART_send_string("RED -> OFF"); //Send notification to the computer      
           UART_send_char(10);//ASCII value 10 is used for carriage return (to print in new line)
        }
        */
    }
}

/*
 *  System Init
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
                 
            //RELAY4 = 1;
            //RELAY3 = 1;             
            //RELAY2 = 1;                       
            break; 
            case 'B':               
                 if((RelayID =='B')&&(SpChar =='*')&&(Start_Btimer==0))
                 {                 
                     if((RelayB_Holdtime>0)&&(RelayB_Holdtime<99))
                     {
                        __delay_ms(1000);
                        RELAY2 = 0;
                        Relay2_flag = 1;
                        Start_Btimer = 1;
                        RL2_Seconds = 0;
                        RelayID = 'C';
                     }
                     else
                     {
                        RelayB_Holdtime = 0;
                        //RELAY1 = 1;  
                     }                         
                 }           
                                             
                 
                //RELAY4 = 1;
                //RELAY3 = 1;             
                //RELAY2 = 1;
                //RELAY1 = 1;             
            break;
 
            case 'C':
                if((RelayID =='C')&&(SpChar =='*')&&(Start_Ctimer==0))
                {                 
                     if((RelayC_Holdtime>0)&&(RelayC_Holdtime<99))
                     {
                        __delay_ms(1000);
                        RELAY3 = 0;
                        Relay3_flag = 1;
                        Start_Ctimer = 1;
                        RL3_Seconds = 0;
                        RelayID = 'D';
                     }
                     else
                     {
                        RelayC_Holdtime = 0;
                        //RELAY1 = 1;  
                     }                         
                 }           

                
                
              
                 //RELAY4 = 1;
                 //RELAY3 = 0;             
                 //RELAY2 = 1;
                 //RELAY1 = 1;              
              break;
            case 'D':
                if((RelayID =='D')&&(SpChar =='*')&&(Start_Dtimer==0))
                {                 
                     if((RelayD_Holdtime>0)&&(RelayD_Holdtime<99))
                     {
                        __delay_ms(1000);
                        RELAY4 = 0;
                        Relay4_flag = 1;
                        Start_Dtimer = 1;
                        RL4_Seconds = 0;
                        RelayID = 'E';
                     }
                     else
                     {
                        RelayD_Holdtime = 0;
                        //RELAY1 = 1;  
                     }                         
                 }           

                 //RELAY4 = 0;
                 //RELAY3 = 1;             
                 //RELAY2 = 1;
                 //RELAY1 = 1;              
              break;            
            default:
             
                 //RELAY4 = 1;
                 //RELAY3 = 1;             
                 //RELAY2 = 1;
                 //RELAY1 = 1;             
                 __delay_ms(1); 
                 
                 if((RelayID =='A')&&(SpChar =='*')&&(Start_timer==0))
                 {  
                     TempHt = tens_a*10;   //
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
                 
                 else if((RelayID =='B')&&(SpChar =='*')&&(Start_Btimer==0))
                 {  
                     TempHt = tens_b*10;   //
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
              else if((RelayID =='C')&&(SpChar =='*')&&(Start_Ctimer==0))
              {  
                    TempHt = tens_c*10;   //
                    RelayC_Holdtime = TempHt + units_c;
                    TempHt = 0;                     
                    if(RelayC_Holdtime>0)
                    {
                        __delay_ms(1000);
                        RELAY3 = 0;
                        Relay3_flag = 1;
                        Start_Ctimer = 1;
                        RL3_Seconds = 0;
                    }
                    else
                    {
                       RelayC_Holdtime = 0;
                       //RELAY1 = 1; 
                    }               
              }
                 
              else if((RelayID =='D')&&(SpChar =='*')&&(Start_Dtimer==0))
              {  
                    TempHt = tens_d*10;   //
                    RelayD_Holdtime = TempHt + units_d;
                    TempHt = 0;                     
                    if(RelayD_Holdtime>0)
                    {
                        __delay_ms(1000);
                        RELAY3 = 0;
                        Relay4_flag = 1;
                        Start_Dtimer = 1;
                        RL4_Seconds = 0;
                    }
                    else
                    {
                       RelayD_Holdtime = 0;
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
    Keypad_PORT  = 0x00;	// Set Keypad port pin values zero
    Keypad_PORT_Direction = 0xF0;	// Last 4 pins input, First 4 pins output
    OPTION_REG = 0x05;
	//OPTION_REG &= 0x7F;
    PORTC  = 0x00;
    TRISC4 = 0;
}

void Initialize_UART(void)
{ 
    //****Setting I/O pins for UART****//
    TRISC6 = 0; // TX Pin set as output
    TRISC7 = 1; // RX Pin set as input
    //________I/O pins set __________// 
    /**Initialize SPBRG register for required 
    baud rate and set BRGH for fast baud_rate**/
    //SPBRG = ((_XTAL_FREQ/16)/Baud_rate) - 1;
    SPBRG = 129;   //
    TXSTAbits.BRGH  = 1;  // for high baud_rate
    //_________End of baud_rate setting_________//
    //****Enable Asynchronous serial port*******//
    TXSTAbits.SYNC  = 0;    // Asynchronous
    RCSTAbits.SPEN  = 1;    // Enable serial port pins
    //_____Asynchronous serial port enabled_______//
    //**Lets prepare for transmission & reception**//
    TXSTAbits.TXEN  = 1;    // enable transmission
    RCSTAbits.CREN  = 1;    // enable reception
    //__UART module up and ready for transmission and reception__//
    //**Select 8-bit mode**//  
    TXSTAbits.TX9   = 0;    // 8-bit reception selected
    RCSTAbits.RX9   = 0;    // 8-bit reception mode selected
    //__8-bit mode selected__//     
}

//**Function to send one byte of date to UART**//

void UART_send_char(char bt)  
{
   //TXREG = bt; //Load the transmitter buffer with the received value
   //while(!TXIF);  // hold the program till TX buffer is free
   
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
    while(!RCIF);  // hold the program till RX buffer is free
    return RCREG; //receive the value and send it to main function
}

//**Function to convert string to byte**//
void UART_send_string(char* st_pt)
{
    while(*st_pt) //if there is a char
        UART_send_char(*st_pt++); //process it as a byte data
}




