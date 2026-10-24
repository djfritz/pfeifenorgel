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

// MIDI parser state
//  status:    last channel status byte seen (running status), 0 == none
//  note:      first data byte (note number) of the current message
//  have_note: 1 == note captured, waiting for velocity
unsigned char status = 0;
unsigned char note = 0;
unsigned char have_note = 0;

void set_note(unsigned char n, unsigned char on) {
  if (n == NOTEC3) {
    PC3 = on;
  } else if (n == NOTECS3) {
    PCS3 = on;
  } else if (n == NOTED3) {
    PD3 = on;
  } else if (n == NOTEDS3) {
    PDS3 = on;
  } else if (n == NOTEE3) {
    PE3 = on;
  } else if (n == NOTEF3) {
    PF3 = on;
  } else if (n == NOTEFS3) {
    PFS3 = on;
  } else if (n == NOTEG3) {
    PG3 = on;
  } else if (n == NOTEGS3) {
    PGS3 = on;
  } else if (n == NOTEA3) {
    PA3 = on;
  } else if (n == NOTEAS3) {
    PAS3 = on;
  } else if (n == NOTEB3) {
    PB3 = on;
  } else if (n == NOTEC4) {
    PC4 = on;
  } else if (n == NOTECS4) {
    PCS4 = on;
  } else if (n == NOTED4) {
    PD4 = on;
  } else if (n == NOTEDS4) {
    PDS4 = on;
  } else if (n == NOTEE4) {
    PE4 = on;
  } else if (n == NOTEF4) {
    PF4 = on;
  } else if (n == NOTEFS4) {
    PFS4 = on;
  } else if (n == NOTEG4) {
    PG4 = on;
  } else if (n == NOTEGS4) {
    PGS4 = on;
  } else if (n == NOTEA4) {
    PA4 = on;
  } else if (n == NOTEAS4) {
    PAS4 = on;
  } else if (n == NOTEB4) {
    PB4 = on;
  }
}

void __interrupt() intr(void) {
  if (RCIF) {
    unsigned char data = RCREG;

    // an overrun stops the receiver until CREN is toggled
    if (OERR) {
      CREN = 0;
      CREN = 1;
    }

    // ignore real-time bytes
    if (data >= 0xF8) {
      return;
    }

    // MSB being set at all means it's a status byte, and 0xF? means it's a
    // system message (which we never care about)
    //
    // either way, if we see a status byte, we clear the note
    if (data & 0x80) {
      status = (data < 0xF0) ? data : 0;
      have_note = 0;
      return;
    }

    // data byte: we only care about note off (0x8n) and note on (0x9n)
    unsigned char type = status & 0xF0;
    if (type != 0x80 && type != 0x90) {
      return;
    }

    // second byte is the note
    if (!have_note) {
      note = data;
      have_note = 1;
      return;
    }

    // third byte is the velocity. Note on with velocity 0 is actually note off... 
    // The organ doesn't have velocity, so it's on or off
    set_note(note, (type == 0x90 && data != 0) ? 1 : 0);
    have_note = 0;
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
