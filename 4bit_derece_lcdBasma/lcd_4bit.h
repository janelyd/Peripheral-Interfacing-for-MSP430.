// lcd_msp.h
/***
  MSP430 i�in 2x16 LCD K�t�phanesi  ***/
#define delay_us(x)     __delay_cycles(x)
#define delay_ms(x)     __delay_cycles((x * 1000L))
#define LCD_DATA P1OUT
#define LCD_CONTROL     P2OUT
#define EN_ACKAPA()     LCD_EN(1),LCD_EN(0)
#define LCD_RS(x)   ((x)? (LCD_CONTROL |= BIT7) : (LCD_CONTROL &= ~BIT7) )
#define LCD_EN(x)  ((x) ? (LCD_CONTROL |= BIT6) : (LCD_CONTROL &= ~BIT6) )
void lcd_komut(unsigned char);  // LCD ye komut g�ndermeye yarar
void lcd_temizle(void);
// LCD ekran� temizler
void lcd_puts(const char*);
void lcd_goto(char,char);
void lcd_init(void);
void lcd_putch(char);
// LCD ye string ifade yazar
// LCD de sat�r ve sut�n olarak istenilen yere gider
// LCD ba�lang�� ayarlar� yap�l�r
// LCD ye tek karakter yazmak i�in kullan�l�r.
