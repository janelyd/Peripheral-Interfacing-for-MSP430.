#include <msp430.h> // MSP430 ba�l�k dosyas�
#include "LCD.h" // LCD ba�l�k dosyas�
void main(void) {
WDTCTL = WDTPW | WDTHOLD; // Watchdog timeri durdur.
LCD_Ayarla(); // Ba�lang��ta LCD ayarlar�n� yap.
LCD_Git_XY(1,4); // Kurs�r� 1.sat�r 3.s�tuna g�t�r.
LCD_Yazi_Yaz("sagopa kajmer"); // Ekrana Erhan YILMAZ yazd�r.
LCD_Git_XY(2,1); // Kurs�r� 2.sat�r 4.s�tuna g�t�r.
LCD_Yazi_Yaz("salako katmer"); // Ekrana LCD DENEME yazd�r.
__bis_SR_register(LPM4_bits); // Denetleyiciyi uyku moduna ge�ir.
}
