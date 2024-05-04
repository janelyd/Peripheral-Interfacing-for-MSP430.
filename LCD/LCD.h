//"header guard" olarak bilinen bir tekniktir
#ifndef __LCD_H  //ifadesi, eðer __LCD_H daha önce yoksa, kodun altýndaki bölümün çalýþmasýný saðlar
#define __LCD_H
#ifdef __cplusplus
extern "C" {
#endif
// LCD baðlantýsýnda kullanýlacak pinlerin tanýmlamalarý
#define LCD_DATA_PORT P1OUT
#define LCD_DATA_PORT_DIR P1DIR
#define LCD_DATA_PORT_SEL P1SEL
#define LCD_DATA_PORT_SEL2 P1SEL2   //ikinci alternatif fonksiyonu belirtmek için

/*Bu tanýmlamalar, LCD ekranýn kontrol sinyallerinin */
/* (RS ve EN) baðlý olduðu portu ve bu portun yönünü (giriþ mi yoksa çýkýþ mý olduðunu) belirler.*/
#define LCD_CONTROL_PORT P2OUT
#define LCD_CONTROL_PORT_DIR P2DIR
#define LCD_CONTROL_PORT_SEL P2SEL
#define LCD_CONTROL_PORT_SEL2 P2SEL2
#define LCD_RS_BIT BIT7
#define LCD_EN_BIT BIT6
// LCD sürme iþleminde kullanýlan makrolar:

/*LCD ekranýn komutlarýný veya verilerini almasý için EN sinyali kullanýlýr*/
#define EN_AC_KAPA() LCD_EN(1),LCD_EN(0)

/*RS sinyali, LCD ekranýn veri alýp almadýðýný belirler*/
#define LCD_RS(x) ( (x) ? (LCD_CONTROL_PORT |= LCD_RS_BIT) : (LCD_CONTROL_PORT &= ~LCD_RS_BIT) )
/*  deðeri doðruysa (1), RS sinyalini yüksek seviyeye (veri alýmý) ayarlar; yanlýþsa (0), RS sinyalini düþük seviyeye (komut alýmý) ayarlar*/

#define LCD_EN(x) ( (x) ? (LCD_CONTROL_PORT |= LCD_EN_BIT) : (LCD_CONTROL_PORT &= ~LCD_EN_BIT) )
/*x deðeri doðruysa (1), EN sinyalini yüksek seviyeye (aktif) ayarlar; yanlýþsa (0), EN sinyalini düþük seviyeye (pasif) ayarlar */

// LCD kütüphanesinde kullanýlan fonksiyon prototipleri
void LCD_Komut_Yaz(unsigned char); // LCD ye komut göndermeye yarar
void LCD_Temizle(void); // LCD ekraný temizler
void LCD_Yazi_Yaz(const char*); // LCDye string ifade yazar
void LCD_Git_XY(char,char); // LCDde kursörü konumlandýrýr
void LCD_Ayarla(void); // LCD baþlangýçayarlarý yapýlýr
void LCD_Karakter_Yaz(char); // LCDye tek karakter yazmak için kullanýlýr
#ifdef __cplusplus
}
#endif
#endif /*__LCD_H */
