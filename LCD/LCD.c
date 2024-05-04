#include <msp430.h>
#include "LCD.h"

//PRINTF GIBI
// LCD'ye karakter yazan fonksiyon
    void LCD_Karakter_Yaz(char veri) {
        unsigned char bSayac;
        LCD_RS(1); // LCD ekranýn veri yazma moduna geçtiðini belirtir
        for(bSayac = 0; bSayac < 40; bSayac++);
        /*bekleme süresi, LCD ekranýn komutlarý veya verileri iþlemesi için gerekli olan zaman kadar beklemek için kullanýlmýþ olabilir.*/
        LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((veri) & 0xF0); // düþük dört bit korunur ve yüksek dört bitler yeni veriyle güncellenir
        /*veri & 0xF0, karakterin yüksek dört bitlerini alýr*/

        EN_AC_KAPA(); //LCD ekranýn veriyi kabul etmesi için gerekli iþlemi gerçekleþtirir

        LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (veri << 4 & 0xF0);
        /*düþük dört bit korunur ve yeni verinin düþük dört biti, karakterin düþük dört bitiyle güncellenir*/
        /*veri << 4 & 0xF0, karakterin düþük dört bitlerini alýr ve bunlarý sola 4 bit kaydýrýr*/

        EN_AC_KAPA(); //LCD ekranýn veriyi kabul etmesi için gerekli iþlemi gerçekleþtirir
    }

    // SCANF GIBI
// LCD'ye komut yazan fonksiyon
void LCD_Komut_Yaz(unsigned char komut) {
    unsigned char bSayac;
    LCD_RS(0); //RS sinyali düþük seviyede ise, LCD ekran komut alýr
    for(bSayac = 0; bSayac < 40; bSayac++); // Bekleme süresi
    LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((komut) & 0xF0); //LCD ekranýn veri portuna yüksek dört bitlik kýsmý yazmak için bir iþlem yapýlýr
    /*Önce LCD_DATA_PORT'un düþük dört biti temizlenir ve sonra komut deðiþkeninin yüksek dört biti LCD_DATA_PORT'un yüksek dört bitine kopyalanýr*/
    EN_AC_KAPA();
    LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (komut << 4 & 0xF0);
    EN_AC_KAPA();
}

// LCD ekraný temizleyip kursor pozisyonunu baþa getiren fonksiyon
void LCD_Temizle(void) {
    LCD_Komut_Yaz(0x01);
    //LCD_Komut_Yaz fonksiyonu çaðrýlýr ve parametre olarak 0x01 gönderilir
    //0x01, LCD ekranýnda "clear display" iþlemini gerçekleþtiren bir komut kodudur. Bu komut, ekraný temizler ve kursor pozisyonunu baþa getirir
    __delay_cycles(1000); // ekranýn temizlenmesi ve kursorun baþa getirilmesi için gerekli olan zaman
}

// LCD'ye yazý yazdýran fonksiyon
void LCD_Yazi_Yaz(const char* yazi) { //yazi dizisinin her bir karakteri kontrol edilir
    while (*yazi) {
        LCD_Karakter_Yaz(*yazi++); //LCD_Karakter_Yaz fonksiyonu çaðrýlýr ve yazi dizisinin mevcut karakteri (*yazi) gönderilir
    }  //Daha sonra, yazi dizisinin bir sonraki karakterine geçmek için yazi iþaretçisi artýrýlýr
}

// LCD kursörünü istenilen yere götüren fonksiyon
void LCD_Git_XY(char x, char y) {
    if (x == 1)
        LCD_Komut_Yaz(0x80 + ((y - 1) % 16)); //x deðeri 1 ise, bu komutla birinci satýra geçilir
    //LCD ekranýn ilk satýrýnda 0x80 adresinden baþlayarak her sütunun adresi y parametresine baðlý olarak belirlenir
    else
        LCD_Komut_Yaz(0xC0 + ((y - 1) % 16)); //(y - 1) % 16 iþlemiyle sütun numarasý 0 ile 15 arasýnda bir deðere dönüþtürülür
    //xC0 adresinden baþlayarak her sütunun adresi y parametresine baðlý olarak belirlenir
}

// LCD baþlangýç ayarlarýný yapan fonksiyon
void LCD_Ayarla() {
    unsigned int bSayac1, bSayac2;
    LCD_DATA_PORT_DIR |= BIT4 + BIT5 + BIT6 + BIT7;
    //LCD veri portunun yüksek dört biti için çýkýþ modu ayarlanýr
    //LCD_DATA_PORT_DIR deðiþkeninin yüksek dört bitine karþýlýk gelen bitler 1 olarak ayarlanýr, diðer bitler ise deðiþtirilmez

    LCD_DATA_PORT_SEL &= ~(BIT4 + BIT5 + BIT6 + BIT7);
    //Bu satýrda, LCD veri portunun yüksek dört biti için GPIO (Genel Amaçlý Giriþ/Çýkýþ) modu seçilir
    //LCD_DATA_PORT_SEL deðiþkeninin yüksek dört bitine karþýlýk gelen bitler 0 olarak ayarlanýr, diðer bitler ise deðiþtirilmez

    LCD_DATA_PORT_SEL2 &= ~(BIT4 + BIT5 + BIT6 + BIT7);
    LCD_CONTROL_PORT_DIR |= LCD_EN_BIT + LCD_RS_BIT;
    //LCD kontrol pini için çýkýþ modu ayarlanýr
    //LCD_CONTROL_PORT_DIR deðiþkeninin ilgili bitleri 1 olarak ayarlanýr
    LCD_CONTROL_PORT_SEL &= ~(LCD_EN_BIT + LCD_RS_BIT);
    //LCD kontrol pini için GPIO (Genel Amaçlý Giriþ/Çýkýþ) modu seçilir.
    //LCD_CONTROL_PORT_SEL deðiþkeninin ilgili bitleri 0 olarak ayarlanýr
    LCD_CONTROL_PORT_SEL2 &= ~(LCD_EN_BIT + LCD_RS_BIT);
    LCD_DATA_PORT = 0x0F;
    //LCD veri portuna 0x0F deðeri yazýlýr
    //Bu, veri yolu için baþlangýç ayarýdýr
    LCD_CONTROL_PORT = 0x00;
    //LCD kontrol portuna 0x00 deðeri yazýlýr. Bu, kontrol pinlerinin baþlangýç durumunu temsil eder
    for (bSayac1 = 0; bSayac1 < 1000; bSayac1++) //, LCD ekranýn baþlatýlmasý için gerekli olan zaman kadar bekleme
        for (bSayac2 = 0; bSayac2 < 500; bSayac2++);
    LCD_RS(0);
    LCD_EN(0); // RS ve EN sinyalleri sýfýr seviyesine getirilir. LCD ekranýn komut kabul moduna geçmesini saðlar
    for (bSayac1 = 0; bSayac1 < 20000; bSayac1++); // LCD ekranýn baþlatýlmasý ve ayarlarýnýn uygulanmasý için gerekli olan zaman
    LCD_Komut_Yaz(0x28); // 0x28 deðeri, 4-bit veri yolu ve çift satýr modunu belirtir
    LCD_Komut_Yaz(0x0C); // Ýmleç Gizleniyor
    LCD_Komut_Yaz(0x06); // 0x06 deðeri, saða doðru yazma modunu belirtir
    LCD_Komut_Yaz(0x80); // LCD Birinci Satýr Konumunda
    LCD_Temizle();       // Ekran temizlenir ve kursorun baþlangýç konumuna getirilir
}
