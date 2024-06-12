#include <msp430.h>

unsigned int adc_value = 0; // ADC deðerini saklamak için deðiþken
int pot_value = 0;          // Potansiyometre deðerini saklamak için deðiþken
float derece;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Watchdog timer'ý durdur
    BCSCTL1 = CALBC1_1MHZ;      // DCO'yu 1MHz'e ayarla
    DCOCTL = CALDCO_1MHZ;

    P1SEL |= BIT0;              // A0 pini olarak ayarla
    P1DIR |= BIT1+ BIT2;              // P1.1'i çýkýþ olarak ayarla

    // ADC ayarlarý
    ADC10CTL1 = INCH_0;         // A0 pini için ADC kanalýný seç
    ADC10CTL0 = SREF_0 + ADC10SHT_2 + ADC10ON; // Referans seviyesi, örnekleme süresi ve ADC'yi etkinleþtir
    ADC10AE0 |= BIT0;           // A0 pini için analog giriþ etkinleþtir

    while(1){
        ADC10CTL0 &= ~ENC;      // Dönüþüm bitini sýfýrla
        while (ADC10CTL1 & BUSY); // Eðer ADC meþgulse bekle
        ADC10CTL0 |= ENC + ADC10SC; // Dönüþümü baþlat
        while (ADC10CTL1 & BUSY); // Dönüþüm tamamlanana kadar bekle

        adc_value = ADC10MEM;   // ADC sonucunu oku

        // ADC deðerini 0-40 arasýnda bir sayýya dönüþtür
        pot_value =(unsigned int)(adc_value);
        derece = (pot_value*3.3)/1023;
        derece = derece/0.0322;

        if (derece < 28) {
                    P1OUT |= BIT1; // P1.1'i yüksek seviyeye ayarla
                    P1OUT &= ~BIT2; // P1.2'yi düþük seviyeye ayarla
                    }
        else if(derece > 28 && derece < 34) {
                    P1OUT &= ~BIT1; // P1.1'i düþük seviyeye ayarla
                    P1OUT |= BIT2; // P1.2'yi yüksek seviyeye ayarla
                }
        else {
                    P1OUT &= ~(BIT1 + BIT2); // Hem P1.1 hem de P1.2'yi düþük seviyeye ayarla
                }

        // pot_value deðiþkenini kullanarak yapmak istediðiniz iþlemi gerçekleþtirin

        __delay_cycles(250); // Bekleme süresi
    }
}
