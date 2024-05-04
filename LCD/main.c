#include <msp430.h> // MSP430 baþlýk dosyasý
#include "LCD.h" // LCD baþlýk dosyasý
void main(void) {
WDTCTL = WDTPW | WDTHOLD; // Watchdog timeri durdur.
LCD_Ayarla(); // Baþlangýçta LCD ayarlarýný yap.
LCD_Git_XY(1,4); // Kursörü 1.satýr 3.sütuna götür.
LCD_Yazi_Yaz("sagopa kajmer"); // Ekrana Erhan YILMAZ yazdýr.
LCD_Git_XY(2,1); // Kursörü 2.satýr 4.sütuna götür.
LCD_Yazi_Yaz("salako katmer"); // Ekrana LCD DENEME yazdýr.
__bis_SR_register(LPM4_bits); // Denetleyiciyi uyku moduna geçir.
}
