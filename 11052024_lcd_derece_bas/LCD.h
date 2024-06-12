//"header guard" olarak bilinen bir tekniktir
#ifndef __LCD_H  //ifadesi, e�er __LCD_H daha �nce yoksa, kodun alt�ndaki b�l�m�n �al��mas�n� sa�lar
#define __LCD_H
#ifdef __cplusplus
extern "C" {
#endif
// LCD ba�lant�s�nda kullan�lacak pinlerin tan�mlamalar�
#define LCD_DATA_PORT P1OUT
#define LCD_DATA_PORT_DIR P1DIR
#define LCD_DATA_PORT_SEL P1SEL
#define LCD_DATA_PORT_SEL2 P1SEL2   //ikinci alternatif fonksiyonu belirtmek i�in

/*Bu tan�mlamalar, LCD ekran�n kontrol sinyallerinin */
/* (RS ve EN) ba�l� oldu�u portu ve bu portun y�n�n� (giri� mi yoksa ��k�� m� oldu�unu) belirler.*/
#define LCD_CONTROL_PORT P2OUT
#define LCD_CONTROL_PORT_DIR P2DIR
#define LCD_CONTROL_PORT_SEL P2SEL
#define LCD_CONTROL_PORT_SEL2 P2SEL2
#define LCD_RS_BIT BIT7
#define LCD_EN_BIT BIT6
// LCD s�rme i�leminde kullan�lan makrolar:

/*LCD ekran�n komutlar�n� veya verilerini almas� i�in EN sinyali kullan�l�r*/
#define EN_AC_KAPA() LCD_EN(1),LCD_EN(0)

/*RS sinyali, LCD ekran�n veri al�p almad���n� belirler*/
#define LCD_RS(x) ( (x) ? (LCD_CONTROL_PORT |= LCD_RS_BIT) : (LCD_CONTROL_PORT &= ~LCD_RS_BIT) )
/*  de�eri do�ruysa (1), RS sinyalini y�ksek seviyeye (veri al�m�) ayarlar; yanl��sa (0), RS sinyalini d���k seviyeye (komut al�m�) ayarlar*/

#define LCD_EN(x) ( (x) ? (LCD_CONTROL_PORT |= LCD_EN_BIT) : (LCD_CONTROL_PORT &= ~LCD_EN_BIT) )
/*x de�eri do�ruysa (1), EN sinyalini y�ksek seviyeye (aktif) ayarlar; yanl��sa (0), EN sinyalini d���k seviyeye (pasif) ayarlar */

// LCD k�t�phanesinde kullan�lan fonksiyon prototipleri
void LCD_Komut_Yaz(unsigned char); // LCD ye komut g�ndermeye yarar
void LCD_Temizle(void); // LCD ekran� temizler
void LCD_Yazi_Yaz(const char*); // LCDye string ifade yazar
void LCD_Git_XY(char,char); // LCDde kurs�r� konumland�r�r
void LCD_Ayarla(void); // LCD ba�lang��ayarlar� yap�l�r
void LCD_Karakter_Yaz(char); // LCDye tek karakter yazmak i�in kullan�l�r
#ifdef __cplusplus
}
#endif
#endif /*__LCD_H */
