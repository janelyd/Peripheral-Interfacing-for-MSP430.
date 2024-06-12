#include <msp430.h>
#include "lcd_4bit.h" //LCD kütüphanesi eklenecek.
void main( void )
{
WDTCTL = WDTPW + WDTHOLD;
BCSCTL1 = CALBC1_1MHZ;
DCOCTL  = CALDCO_1MHZ;
__delay_cycles(1000);
lcd_init();
lcd_goto(1,2);
lcd_puts("EEM306");
delay_ms(1000);
lcd_goto(2,1);
// Satýr ve sutun ayarlanýyor
lcd_puts("Mikroislemciler Dersi");
__bis_SR_register(LPM4_bits + GIE);
}
