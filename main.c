#include <xc.h>

// Configuration Bits
#pragma config FOSC = INTRC_NOCLKOUT // Oscillator Selection bits
#pragma config WDTE = OFF            // Watchdog Timer Disabled
#pragma config PWRTE = OFF           // Power-up Timer Disabled
#pragma config BOREN = ON            // Brown-out Reset Enabled
#pragma config LVP = OFF             // Low-Voltage Programming Disabled

#define _XTAL_FREQ 8000000 // Define 8 MHz crystal frequency

#define NOTEC3 48
#define NOTECS3 49
#define NOTED3 50
#define NOTEDS3 51
#define NOTEE3 52
#define NOTEF3 53
#define NOTEFS3 54
#define NOTEG3 55
#define NOTEGS3 56
#define NOTEA3 57
#define NOTEAS3 58
#define NOTEB3 59
#define NOTEC4 60
#define NOTECS4 61
#define NOTED4 62
#define NOTEDS4 63
#define NOTEE4 64
#define NOTEF4 65
#define NOTEFS4 66
#define NOTEG4 67
#define NOTEGS4 68
#define NOTEA4 69
#define NOTEAS4 70
#define NOTEB4 71

#define PC3 PORTAbits.RA0
#define PCS3 PORTAbits.RA1
#define PD3 PORTAbits.RA2
#define PDS3 PORTAbits.RA3
#define PE3 PORTAbits.RA4
#define PF3 PORTAbits.RA5
#define PFS3 PORTAbits.RA6
#define PG3 PORTAbits.RA7
#define PGS3 PORTCbits.RC0
#define PA3 PORTCbits.RC1
#define PAS3 PORTCbits.RC2
#define PB3 PORTCbits.RC3
#define PC4 PORTCbits.RC4
#define PCS4 PORTCbits.RC5
#define PD4 PORTDbits.RD0
#define PDS4 PORTDbits.RD1
#define PE4 PORTDbits.RD2
#define PF4 PORTDbits.RD3
#define PFS4 PORTDbits.RD4
#define PG4 PORTDbits.RD5
#define PGS4 PORTDbits.RD6
#define PA4 PORTDbits.RD7
#define PAS4 PORTEbits.RE0
#define PB4 PORTEbits.RE1

// states:
//  0 == scan for note on/off
//  1 == note on, catch next byte as note
//  2 == note off, catch next byte as note
char state = 0;

void __interrupt() intr(void) {
  if (RCIF) {
    RCIF = 0;
    char data = RCREG;

    // first check if we even care
    if (state == 0) {
      if ((data & 0b10010000) == 0b10010000) {
        state = 1;
        return;
      } else if ((data & 0b10000000) == 0b10000000) {
        state = 2;
        return;
      }
    } else if (state == 1) {
      if (data < NOTEC3 || data > NOTEB4) {
        state = 0;
        return;
      }
      // turn on a note
      if (data == NOTEC3) {
        PC3 = 1;
      } else if (data == NOTECS3) {
        PCS3 = 1;
      } else if (data == NOTED3) {
        PD3 = 1;
      } else if (data == NOTEDS3) {
        PDS3 = 1;
      } else if (data == NOTEE3) {
        PE3 = 1;
      } else if (data == NOTEF3) {
        PF3 = 1;
      } else if (data == NOTEFS3) {
        PFS3 = 1;
      } else if (data == NOTEG3) {
        PG3 = 1;
      } else if (data == NOTEGS3) {
        PGS3 = 1;
      } else if (data == NOTEA3) {
        PA3 = 1;
      } else if (data == NOTEAS3) {
        PAS3 = 1;
      } else if (data == NOTEB3) {
        PB3 = 1;
      } else if (data == NOTEC4) {
        PC4 = 1;
      } else if (data == NOTECS4) {
        PCS4 = 1;
      } else if (data == NOTED4) {
        PD4 = 1;
      } else if (data == NOTEDS4) {
        PDS4 = 1;
      } else if (data == NOTEE4) {
        PE4 = 1;
      } else if (data == NOTEF4) {
        PF4 = 1;
      } else if (data == NOTEFS4) {
        PFS4 = 1;
      } else if (data == NOTEG4) {
        PG4 = 1;
      } else if (data == NOTEGS4) {
        PGS4 = 1;
      } else if (data == NOTEA4) {
        PA4 = 1;
      } else if (data == NOTEAS4) {
        PAS4 = 1;
      } else if (data == NOTEB4) {
        PB4 = 1;
      }
    } else if (state == 2) {
      if (data < NOTEC3 || data > NOTEB4) {
        state = 0;
        return;
      }
      // turn off a note
      if (data == NOTEC3) {
        PC3 = 0;
      } else if (data == NOTECS3) {
        PCS3 = 0;
      } else if (data == NOTED3) {
        PD3 = 0;
      } else if (data == NOTEDS3) {
        PDS3 = 0;
      } else if (data == NOTEE3) {
        PE3 = 0;
      } else if (data == NOTEF3) {
        PF3 = 0;
      } else if (data == NOTEFS3) {
        PFS3 = 0;
      } else if (data == NOTEG3) {
        PG3 = 0;
      } else if (data == NOTEGS3) {
        PGS3 = 0;
      } else if (data == NOTEA3) {
        PA3 = 0;
      } else if (data == NOTEAS3) {
        PAS3 = 0;
      } else if (data == NOTEB3) {
        PB3 = 0;
      } else if (data == NOTEC4) {
        PC4 = 0;
      } else if (data == NOTECS4) {
        PCS4 = 0;
      } else if (data == NOTED4) {
        PD4 = 0;
      } else if (data == NOTEDS4) {
        PDS4 = 0;
      } else if (data == NOTEE4) {
        PE4 = 0;
      } else if (data == NOTEF4) {
        PF4 = 0;
      } else if (data == NOTEFS4) {
        PFS4 = 0;
      } else if (data == NOTEG4) {
        PG4 = 0;
      } else if (data == NOTEGS4) {
        PGS4 = 0;
      } else if (data == NOTEA4) {
        PA4 = 0;
      } else if (data == NOTEAS4) {
        PAS4 = 0;
      } else if (data == NOTEB4) {
        PB4 = 0;
      }
    } 
    state = 0;
  }
};

void main(void) {
  OSCCONbits.IRCF = 0b111; // Set internal oscillator to 8 MHz
  OSCCONbits.SCS = 1;      // Select internal oscillator as system clock
  ANSEL = 0;  // Turn all digital I/O pins (disable analog functions)
  ANSELH = 0; // Clear analog high byte

  // setup and clear outputs
  TRISA = 0;
  PORTA = 0;
  TRISC0 = 0;
  TRISC1 = 0;
  TRISC2 = 0;
  TRISC3 = 0;
  TRISC4 = 0;
  TRISC5 = 0;
  PORTC = 0;
  TRISD = 0;
  PORTD = 0;
  TRISE0 = 0;
  TRISE1 = 0;
  PORTE = 0;

  // uart
  BRG16 = 0;
  SPBRGH = 0;
  SPBRG = 3; // 31250bps @ 8MHz
  RCSTAbits.CREN = 1;
  TXSTAbits.SYNC = 0;
  RCSTAbits.SPEN = 1;

  // enable interrupts
  GIE = 1;
  PEIE = 1;
  RCIE = 1;

  while (1)
    ;
}
