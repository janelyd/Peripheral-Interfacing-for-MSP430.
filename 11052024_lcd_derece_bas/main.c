#include <msp430.h> // MSP430 ba�l�k dosyas�
#include "LCD.h" // LCD ba�l�k dosyas�

unsigned int adc_value = 0; // ADC de�erini saklamak i�in de�i�ken
int pot_value = 0;          // Potansiyometre de�erini saklamak i�in de�i�ken
float derece;
unsigned char dizi[2];

int i;


void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Watchdog timer'� durdur
    BCSCTL1 = CALBC1_1MHZ;      // DCO'yu 1MHz'e ayarla
    DCOCTL = CALDCO_1MHZ;
    LCD_Ayarla(); // Ba�lang��ta LCD ayarlar�n� yap.
    LCD_Git_XY(1,4); // Kurs�r� 1.sat�r 3.s�tuna g�t�r.
    LCD_Yazi_Yaz("sicaklik="); // Ekrana Erhan YILMAZ yazd�r.



    P1SEL |= BIT0;              // A0 pini olarak ayarla
    P1DIR |= BIT1+ BIT2;              // P1.1'i ��k�� olarak ayarla

    // ADC ayarlar�
    ADC10CTL1 = INCH_0;         // A0 pini i�in ADC kanal�n� se�
    ADC10CTL0 = SREF_0 + ADC10SHT_2 + ADC10ON; // Referans seviyesi, �rnekleme s�resi ve ADC'yi etkinle�tir
    ADC10AE0 |= BIT0;           // A0 pini i�in analog giri� etkinle�tir

    while(1){
        ADC10CTL0 &= ~ENC;      // D�n���m bitini s�f�rla
        while (ADC10CTL1 & BUSY); // E�er ADC me�gulse bekle
        ADC10CTL0 |= ENC + ADC10SC; // D�n���m� ba�lat
        while (ADC10CTL1 & BUSY); // D�n���m tamamlanana kadar bekle

        adc_value = ADC10MEM;   // ADC sonucunu oku

        // ADC de�erini 0-40 aras�nda bir say�ya d�n��t�r
        pot_value =(unsigned int)(adc_value);
        derece = (pot_value*3.3)/1023;
        derece = derece/0.0322;
        int derece_int = (int)derece; // Dereceyi int t�r�ne d�n��t�r
        int x = 1;

        for(i=0;i<=1;i++){
            dizi[i] = ((derece_int/x)%10)+48;
            x=x*10;
       }
        LCD_Git_XY(2,1); // Kurs�r� 2.sat�r 4.s�tuna g�t�r.
             LCD_Yazi_Yaz("derece="); // Ekrana LCD DENEME yazd�r.
        for(i=0;i<=1;i++){

            LCD_Karakter_Yaz(dizi[1-i]);
            }

        if (derece < 28) {
                    P1OUT |= BIT1; // P1.1'i y�ksek seviyeye ayarla
                    P1OUT &= ~BIT2; // P1.2'yi d���k seviyeye ayarla
                    }
        else if(derece > 28 && derece < 34) {
                    P1OUT &= ~BIT1; // P1.1'i d���k seviyeye ayarla
                    P1OUT |= BIT2; // P1.2'yi y�ksek seviyeye ayarla
                }
        else {
                    P1OUT &= ~(BIT1 + BIT2); // Hem P1.1 hem de P1.2'yi d���k seviyeye ayarla
                }

        // pot_value de�i�kenini kullanarak yapmak istedi�iniz i�lemi ger�ekle�tirin

        __delay_cycles(250); // Bekleme s�resi
    }

}
