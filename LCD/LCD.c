#include <msp430.h>
#include "LCD.h"

//PRINTF GIBI
// LCD'ye karakter yazan fonksiyon
    void LCD_Karakter_Yaz(char veri) {
        unsigned char bSayac;
        LCD_RS(1); // LCD ekran�n veri yazma moduna ge�ti�ini belirtir
        for(bSayac = 0; bSayac < 40; bSayac++);
        /*bekleme s�resi, LCD ekran�n komutlar� veya verileri i�lemesi i�in gerekli olan zaman kadar beklemek i�in kullan�lm�� olabilir.*/
        LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((veri) & 0xF0); // d���k d�rt bit korunur ve y�ksek d�rt bitler yeni veriyle g�ncellenir
        /*veri & 0xF0, karakterin y�ksek d�rt bitlerini al�r*/

        EN_AC_KAPA(); //LCD ekran�n veriyi kabul etmesi i�in gerekli i�lemi ger�ekle�tirir

        LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (veri << 4 & 0xF0);
        /*d���k d�rt bit korunur ve yeni verinin d���k d�rt biti, karakterin d���k d�rt bitiyle g�ncellenir*/
        /*veri << 4 & 0xF0, karakterin d���k d�rt bitlerini al�r ve bunlar� sola 4 bit kayd�r�r*/

        EN_AC_KAPA(); //LCD ekran�n veriyi kabul etmesi i�in gerekli i�lemi ger�ekle�tirir
    }

    // SCANF GIBI
// LCD'ye komut yazan fonksiyon
void LCD_Komut_Yaz(unsigned char komut) {
    unsigned char bSayac;
    LCD_RS(0); //RS sinyali d���k seviyede ise, LCD ekran komut al�r
    for(bSayac = 0; bSayac < 40; bSayac++); // Bekleme s�resi
    LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((komut) & 0xF0); //LCD ekran�n veri portuna y�ksek d�rt bitlik k�sm� yazmak i�in bir i�lem yap�l�r
    /*�nce LCD_DATA_PORT'un d���k d�rt biti temizlenir ve sonra komut de�i�keninin y�ksek d�rt biti LCD_DATA_PORT'un y�ksek d�rt bitine kopyalan�r*/
    EN_AC_KAPA();
    LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (komut << 4 & 0xF0);
    EN_AC_KAPA();
}

// LCD ekran� temizleyip kursor pozisyonunu ba�a getiren fonksiyon
void LCD_Temizle(void) {
    LCD_Komut_Yaz(0x01);
    //LCD_Komut_Yaz fonksiyonu �a�r�l�r ve parametre olarak 0x01 g�nderilir
    //0x01, LCD ekran�nda "clear display" i�lemini ger�ekle�tiren bir komut kodudur. Bu komut, ekran� temizler ve kursor pozisyonunu ba�a getirir
    __delay_cycles(1000); // ekran�n temizlenmesi ve kursorun ba�a getirilmesi i�in gerekli olan zaman
}

// LCD'ye yaz� yazd�ran fonksiyon
void LCD_Yazi_Yaz(const char* yazi) { //yazi dizisinin her bir karakteri kontrol edilir
    while (*yazi) {
        LCD_Karakter_Yaz(*yazi++); //LCD_Karakter_Yaz fonksiyonu �a�r�l�r ve yazi dizisinin mevcut karakteri (*yazi) g�nderilir
    }  //Daha sonra, yazi dizisinin bir sonraki karakterine ge�mek i�in yazi i�aret�isi art�r�l�r
}

// LCD kurs�r�n� istenilen yere g�t�ren fonksiyon
void LCD_Git_XY(char x, char y) {
    if (x == 1)
        LCD_Komut_Yaz(0x80 + ((y - 1) % 16)); //x de�eri 1 ise, bu komutla birinci sat�ra ge�ilir
    //LCD ekran�n ilk sat�r�nda 0x80 adresinden ba�layarak her s�tunun adresi y parametresine ba�l� olarak belirlenir
    else
        LCD_Komut_Yaz(0xC0 + ((y - 1) % 16)); //(y - 1) % 16 i�lemiyle s�tun numaras� 0 ile 15 aras�nda bir de�ere d�n��t�r�l�r
    //xC0 adresinden ba�layarak her s�tunun adresi y parametresine ba�l� olarak belirlenir
}

// LCD ba�lang�� ayarlar�n� yapan fonksiyon
void LCD_Ayarla() {
    unsigned int bSayac1, bSayac2;
    LCD_DATA_PORT_DIR |= BIT4 + BIT5 + BIT6 + BIT7;
    //LCD veri portunun y�ksek d�rt biti i�in ��k�� modu ayarlan�r
    //LCD_DATA_PORT_DIR de�i�keninin y�ksek d�rt bitine kar��l�k gelen bitler 1 olarak ayarlan�r, di�er bitler ise de�i�tirilmez

    LCD_DATA_PORT_SEL &= ~(BIT4 + BIT5 + BIT6 + BIT7);
    //Bu sat�rda, LCD veri portunun y�ksek d�rt biti i�in GPIO (Genel Ama�l� Giri�/��k��) modu se�ilir
    //LCD_DATA_PORT_SEL de�i�keninin y�ksek d�rt bitine kar��l�k gelen bitler 0 olarak ayarlan�r, di�er bitler ise de�i�tirilmez

    LCD_DATA_PORT_SEL2 &= ~(BIT4 + BIT5 + BIT6 + BIT7);
    LCD_CONTROL_PORT_DIR |= LCD_EN_BIT + LCD_RS_BIT;
    //LCD kontrol pini i�in ��k�� modu ayarlan�r
    //LCD_CONTROL_PORT_DIR de�i�keninin ilgili bitleri 1 olarak ayarlan�r
    LCD_CONTROL_PORT_SEL &= ~(LCD_EN_BIT + LCD_RS_BIT);
    //LCD kontrol pini i�in GPIO (Genel Ama�l� Giri�/��k��) modu se�ilir.
    //LCD_CONTROL_PORT_SEL de�i�keninin ilgili bitleri 0 olarak ayarlan�r
    LCD_CONTROL_PORT_SEL2 &= ~(LCD_EN_BIT + LCD_RS_BIT);
    LCD_DATA_PORT = 0x0F;
    //LCD veri portuna 0x0F de�eri yaz�l�r
    //Bu, veri yolu i�in ba�lang�� ayar�d�r
    LCD_CONTROL_PORT = 0x00;
    //LCD kontrol portuna 0x00 de�eri yaz�l�r. Bu, kontrol pinlerinin ba�lang�� durumunu temsil eder
    for (bSayac1 = 0; bSayac1 < 1000; bSayac1++) //, LCD ekran�n ba�lat�lmas� i�in gerekli olan zaman kadar bekleme
        for (bSayac2 = 0; bSayac2 < 500; bSayac2++);
    LCD_RS(0);
    LCD_EN(0); // RS ve EN sinyalleri s�f�r seviyesine getirilir. LCD ekran�n komut kabul moduna ge�mesini sa�lar
    for (bSayac1 = 0; bSayac1 < 20000; bSayac1++); // LCD ekran�n ba�lat�lmas� ve ayarlar�n�n uygulanmas� i�in gerekli olan zaman
    LCD_Komut_Yaz(0x28); // 0x28 de�eri, 4-bit veri yolu ve �ift sat�r modunu belirtir
    LCD_Komut_Yaz(0x0C); // �mle� Gizleniyor
    LCD_Komut_Yaz(0x06); // 0x06 de�eri, sa�a do�ru yazma modunu belirtir
    LCD_Komut_Yaz(0x80); // LCD Birinci Sat�r Konumunda
    LCD_Temizle();       // Ekran temizlenir ve kursorun ba�lang�� konumuna getirilir
}
