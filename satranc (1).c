#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
// Struct tanımları
typedef struct {
    int sah;
    int vezir;
    int kaleL;
    int kaleR;
    int atL;
    int atR;
    int filL;
    int filR;
    int piyon[8]; 
} beyaz;

typedef struct {
    int sah;
    int vezir;
    int kaleL;
    int kaleR;
    int atL;
    int atR;
    int filL;
    int filR;
    int piyon[8]; 
} siyah;
char tahta[64]; 

char tahta[64];

void baslat_beyaz(beyaz *b) {
    b->sah = 5;
    b->vezir = 4;
    b->kaleL = 1;
    b->kaleR = 8;
    b->atL = 2;
    b->atR = 7;
    b->filL = 3;
    b->filR = 6;
    for (int i = 0; i < 8; i++) {
        b->piyon[i] = 9 + i;
    }
}


void baslat_siyah(siyah *s) {
    s->sah = 61;
    s->vezir = 60;
    s->kaleL = 57;
    s->kaleR = 64;
    s->atL = 58;
    s->atR = 63;
    s->filL = 59;
    s->filR = 62;
    for (int i = 0; i < 8; i++) {
        s->piyon[i] = 49 + i;
    }
}




void tahta_baslat() {
    for (int i = 0; i < 64; i++) {
        tahta[i] = '.'; 
    }
}


void tahta_goster() {
    for (int i = 0; i < 64; i++) {
        printf("%c ", tahta[i]);
        if ((i + 1) % 8 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}


void tahta_guncelle(beyaz *b, siyah *s) {
    
    tahta_baslat(); 
    
    
    tahta[b->sah - 1] = 'S';
    tahta[b->vezir - 1] = 'V';
    tahta[b->kaleL - 1] = 'K';
    tahta[b->kaleR - 1] = 'K';
    tahta[b->atL - 1] = 'A';
    tahta[b->atR - 1] = 'A';
    tahta[b->filL - 1] = 'F';
    tahta[b->filR - 1] = 'F';
    for (int i = 0; i < 8; i++) {
        tahta[b->piyon[i] - 1] = 'P';
    }


    tahta[s->sah - 1] = 's';
    tahta[s->vezir - 1] = 'v';
    tahta[s->kaleL - 1] = 'k';
    tahta[s->kaleR - 1] = 'k';
    tahta[s->atL - 1] = 'a';
    tahta[s->atR - 1] = 'a';
    tahta[s->filL - 1] = 'f';
    tahta[s->filR - 1] = 'f';
    for (int i = 0; i < 8; i++) {
        tahta[s->piyon[i] - 1] = 'p';
    }

    
    tahta_goster();
}



//!şah
void kontrolSiyahSah(int deger, int *p, siyah *s1) {
    int sahKonumu = s1->sah; 
    int satir = sahKonumu / 8; 
    int sutun = sahKonumu % 8; 

    
    int yonler[] = { -9, -8, -7, -1, 1, 7, 8, 9 };

    
    for (int i = 0; i < 8; i++) {
        int yeniKonum = sahKonumu + yonler[i];
        int yeniSatir = yeniKonum / 8;
        int yeniSutun = yeniKonum % 8;

        // Tahta sınırlarını kontrol et
        if (yeniKonum < 0 || yeniKonum >= 64) continue;

        // Eğer yeni konum aynı satır veya bir sonraki/önceki satırda değilse sınırı aşmıştır
        if (abs(yeniSatir - satir) > 1 || abs(yeniSutun - sutun) > 1) continue;

        
        if (yeniKonum == deger) {
            *p = 2; 
            return; 
        }
    }
}

void kontrolBeyazSah(int deger, int *p, beyaz *b1) {
    int sahKonumu = b1->sah; 
    int satir = sahKonumu / 8; 
    int sutun = sahKonumu % 8; 

    
    int yonler[] = { -9, -8, -7, -1, 1, 7, 8, 9 };

    
    for (int i = 0; i < 8; i++) {
        int yeniKonum = sahKonumu + yonler[i];
        int yeniSatir = yeniKonum / 8;
        int yeniSutun = yeniKonum % 8;

        // Tahta sınırlarını kontrol et
        if (yeniKonum < 0 || yeniKonum >= 64) continue;

        // Eğer yeni konum aynı satır veya bir sonraki/önceki satırda değilse sınırı aşmıştır
        if (abs(yeniSatir - satir) > 1 || abs(yeniSutun - sutun) > 1) continue;

        
        if (yeniKonum == deger) {
            *p = 1; 
            return; 
        }
    }
}


//!vezir
void kontrolVezir(int deger, int *p, beyaz *b1) {
    int vezirKonumu = b1->vezir; 
    int satir = vezirKonumu / 8; 
    int sutun = vezirKonumu % 8;
    
    int yonler[] = { -8, 8, -1, 1, -9, -7, 7, 9 }; 

    // Her yön için hareket kontrolü
    for (int i = 0; i < 8; i++) {
        int yeniKonum = vezirKonumu;
        int yeniSatir = satir;
        int yeniSutun = sutun;

        // Sınırları aşmadan hareketleri kontrol et
        while (1) {
            yeniKonum += yonler[i];
            yeniSatir = yeniKonum / 8;
            yeniSutun = yeniKonum % 8;

            // Tahta sınırlarını kontrol et
            if (yeniKonum < 0 || yeniKonum >= 64) break;

            
            if (i < 4) { // Dikey veya yatay hareketler
                if ((i == 2 || i == 3) && yeniSatir != satir) break; // Yatay sınır kontrolü
                if ((i == 0 || i == 1) && yeniSutun != sutun) break; // Dikey sınır kontrolü
            } else { // çapraz hareketler
                if (abs(yeniSatir - satir) != abs(yeniSutun - sutun)) break;
            }

            
            if (yeniKonum == deger) {
                *p = 1; 
                return; 
            }
        }
    }
}

void kontrolVezirSiyah(int deger, int *p, siyah *b1) {
    int vezirKonumu = b1->vezir; 
    int satir = vezirKonumu / 8; 
    int sutun = vezirKonumu % 8; 

    
    int yonler[] = { -8, 8, -1, 1, -9, -7, 7, 9 }; 

    
    for (int i = 0; i < 8; i++) {
        int yeniKonum = vezirKonumu;
        int yeniSatir = satir;
        int yeniSutun = sutun;

        
        while (1) {
            yeniKonum += yonler[i];
            yeniSatir = yeniKonum / 8;
            yeniSutun = yeniKonum % 8;

            // Tahta sınırlarını kontrol et
            if (yeniKonum < 0 || yeniKonum >= 64) break;

            // Satır veya sütun sınırlarının dışına taşmasını engelle
            if (i < 4) { // Dikey veya yatay hareketler
                if ((i == 2 || i == 3) && yeniSatir != satir) break; // Yatay sınır kontrolü
                if ((i == 0 || i == 1) && yeniSutun != sutun) break; // Dikey sınır kontrolü
            } else { // çapraz hareketler
                if (abs(yeniSatir - satir) != abs(yeniSutun - sutun)) {break;}
            }

            
            if (yeniKonum == deger) {
                *p = 2;
                return ;
            }
        }
    }
}

//!filler
void kontrolFR(int deger, int *p, beyaz *b1) {
    int filKonumu = b1->filR; 
    int satir = filKonumu / 8; 
    int sutun = filKonumu % 8; 

    
    int yonler[] = { -9, -7, 7, 9 }; 

    // Her yön için hareket kontrolü
    for (int i = 0; i < 4; i++) {
        int yeniKonum = filKonumu;
        int yeniSatir = satir;
        int yeniSutun = sutun;

        // Sınırları aşmadan çapraz hareketleri kontrol et
        while (1) {
            yeniKonum += yonler[i];
            yeniSatir = yeniKonum / 8;
            yeniSutun = yeniKonum % 8;

            // Tahta sınırlarını kontrol et
            if (yeniKonum < 0 || yeniKonum >= 64) break;

            // Farklı satırlara veya sütunlara geçişi kontrol et
            if (abs(yeniSatir - satir) != abs(yeniSutun - sutun)) break;

            
            if (yeniKonum == deger) {
                *p = 1; 
                return; 
            }
        }
    }
}

void kontrolFilSiyahR(int deger, int *p, siyah *b1) {
    int filKonumu = b1->filR; 
    int satir = filKonumu / 8; 
    int sutun = filKonumu % 8; 


    int yonler[] = { -9, -7, 7, 9 };

    // Her yön için hareket kontrolü
    for (int i = 0; i < 4; i++) {
        int yeniKonum = filKonumu;
        int yeniSatir = satir;
        int yeniSutun = sutun;

        // Sınırları aşmadan çapraz hareketleri kontrol et
        while (1) {
            yeniKonum += yonler[i];
            yeniSatir = yeniKonum / 8;
            yeniSutun = yeniKonum % 8;

            // Tahta sınırlarını kontrol et
            if (yeniKonum < 0 || yeniKonum >= 64) break;

            // Farklı satırlara veya sütunlara geçişi kontrol et
            if (abs(yeniSatir - satir) != abs(yeniSutun - sutun)) break;

            
            if (yeniKonum == deger) {
                *p = 2; 
                return; 
            }
        }
    }
}

void kontrolFL(int deger, int *p, beyaz *b1) {
    int filKonumu = b1->filL; 
    int satir = filKonumu / 8; 
    int sutun = filKonumu % 8; 

    // Filin hareket edebileceği dört yön 
    int yonler[] = { -9, -7, 7, 9 }; 

    // Her yön için hareket kontrolü
    for (int i = 0; i < 4; i++) {
        int yeniKonum = filKonumu;
        int yeniSatir = satir;
        int yeniSutun = sutun;

        // Sınırları aşmadan diyagonal hareketleri kontrol et
        while (1) {
            yeniKonum += yonler[i];
            yeniSatir = yeniKonum / 8;
            yeniSutun = yeniKonum % 8;

            // Tahta sınırlarını kontrol et
            if (yeniKonum < 0 || yeniKonum >= 64) break;

            // Farklı satırlara veya sütunlara geçişi kontrol et
            if (abs(yeniSatir - satir) != abs(yeniSutun - sutun)) break;

            
            if (yeniKonum == deger) {
                *p = 1; 
                return; 
            }
        }
    }
}
void kontrol_filsiyah_sol(int yenikonum,siyah*s1){
    if (yenikonum==s1->atL){yenikonum=-1;}
    if (yenikonum==s1->atR){yenikonum=-1;}
    if (yenikonum==s1->kaleL){yenikonum=-1;}
    if (yenikonum==s1->kaleR){yenikonum=-1;}
    if (yenikonum==s1->vezir){yenikonum=-1;}
    if (yenikonum==s1->sah){yenikonum=-1;}
    if (yenikonum==s1->filR){yenikonum=-1;}
    for (int i = 0; i < 8; i++)
{
    if (yenikonum==s1->piyon[i]){yenikonum=-1;}
}

}

void kontrolFilSiyahSol(int deger, int *p, siyah *b1) {
    int filKonumu = b1->filL; 
    int satir = filKonumu / 8; 
    int sutun = filKonumu % 8; 

    
    int yonler[] = { -9, -7, 7, 9 }; 

    
    for (int i = 0; i < 4; i++) {
        int yeniKonum = filKonumu;
        int yeniSatir = satir;
        int yeniSutun = sutun;

        // Sınırları aşmadan diyagonal hareketleri kontrol et
        while (1) {
            yeniKonum += yonler[i];
            yeniSatir = yeniKonum / 8;
            yeniSutun = yeniKonum % 8;
            kontrol_filsiyah_sol(yeniKonum,b1);
            // Tahta sınırlarını kontrol et
            if (yeniKonum < 0 || yeniKonum >= 64||yeniKonum==-1) break;

            // Farklı satırlara veya sütunlara geçişi kontrol et
            if (abs(yeniSatir - satir) != abs(yeniSutun - sutun)) break;

            
            if (yeniKonum == deger) {
                *p = 2; 
                return; 
            }
        }
    }
}

//!atlar
void kontrolAR(int deger, int *p, beyaz *b1) {
    int atKonumu = b1->atR; 
    int bol = atKonumu % 8;

    
    int hamleler[] = { -17, -15, -10, -6, 6, 10, 15, 17 };

    
    for (int i = 0; i < 8; i++) {
        int yeniKonum = atKonumu + hamleler[i];

        // Tahta sınırlarını kontrol et
        if (yeniKonum < 0 || yeniKonum >= 64) continue;

        // Tahtadaki sütun sınırlarını kontrol et
        int yeniBol = yeniKonum % 8;
        if ((bol == 0 && (yeniBol == 6 || yeniBol == 7)) ||
            (bol == 1 && (yeniBol == 5 || yeniBol == 6 || yeniBol == 7)) ||
            (bol == 2 && (yeniBol >= 0 && yeniBol <= 7)) ||
            (bol == 3 && (yeniBol >= 0 && yeniBol <= 7)) ||
            (bol == 4 && (yeniBol >= 0 && yeniBol <= 7)) ||
            (bol == 5 && (yeniBol >= 0 && yeniBol <= 7)) ||
            (bol == 6 && (yeniBol == 0 || yeniBol == 1)) ||
            (bol == 7 && (yeniBol == 0))) {
            
            
            if (yeniKonum == deger) {
                *p = 1; 
                return; 
            }
        }
    }
}
void kontrolAL(int deger, int *p, beyaz *b1) {
    int atKonumu = b1->atL;
    int bol = atKonumu % 8;

    
    int hamleler[] = { -17, -15, -10, -6, 6, 10, 15, 17 };

    
    for (int i = 0; i < 8; i++) {
        int yeniKonum = atKonumu + hamleler[i];

        // Tahta sınırlarını kontrol et
        if (yeniKonum < 0 || yeniKonum >= 64) continue;

        // Tahtadaki sütun sınırlarını kontrol et
        int yeniBol = yeniKonum % 8;
        if ((bol == 0 && (yeniBol == 6 || yeniBol == 7)) ||
            (bol == 1 && (yeniBol == 5 || yeniBol == 6 || yeniBol == 7)) ||
            (bol == 2 && (yeniBol >= 0 && yeniBol <= 7)) ||
            (bol == 3 && (yeniBol >= 0 && yeniBol <= 7)) ||
            (bol == 4 && (yeniBol >= 0 && yeniBol <= 7)) ||
            (bol == 5 && (yeniBol >= 0 && yeniBol <= 7)) ||
            (bol == 6 && (yeniBol == 0 || yeniBol == 1)) ||
            (bol == 7 && (yeniBol == 0))) {
            
            
            if (yeniKonum == deger) {
                *p = 1; 
                return; 
            }
        }
    }
}
void kontrolSiyahAL(int deger, int *p, siyah *s1) {
    int atKonumu = s1->atL; 
    int bol = atKonumu % 8;

    
    int hamleler[] = { -17, -15, -10, -6, 6, 10, 15, 17 };

    
    for (int i = 0; i < 8; i++) {
        int yeniKonum = atKonumu + hamleler[i];

        // Tahta sınırlarını kontrol et
        if (yeniKonum < 0 || yeniKonum >= 64) continue;

        // Tahtadaki sütun sınırlarını kontrol et
        int yeniBol = yeniKonum % 8;
        if ((bol == 0 && (yeniBol == 6 || yeniBol == 7)) ||
            (bol == 1 && (yeniBol == 5 || yeniBol == 6 || yeniBol == 7)) ||
            (bol == 2 && (yeniBol >= 0 && yeniBol <= 7)) ||
            (bol == 3 && (yeniBol >= 0 && yeniBol <= 7)) ||
            (bol == 4 && (yeniBol >= 0 && yeniBol <= 7)) ||
            (bol == 5 && (yeniBol >= 0 && yeniBol <= 7)) ||
            (bol == 6 && (yeniBol == 0 || yeniBol == 1)) ||
            (bol == 7 && (yeniBol == 0))) {
            
            
            if (yeniKonum == deger) {
                *p = 2; 
                return; 
            }
        }
    }
}
void kontrolSiyahAR(int deger, int *p, siyah *s1) {
    int atKonumu = s1->atR; 
    int bol = atKonumu % 8;

    
    int hamleler[] = { -17, -15, -10, -6, 6, 10, 15, 17 };

    
    for (int i = 0; i < 8; i++) {
        int yeniKonum = atKonumu + hamleler[i];

        // Tahta sınırlarını kontrol et
        if (yeniKonum < 0 || yeniKonum >= 64) continue;

        // Tahtadaki sütun sınırlarını kontrol et
        int yeniBol = yeniKonum % 8;
        if ((bol == 0 && (yeniBol == 6 || yeniBol == 7)) ||
            (bol == 1 && (yeniBol == 5 || yeniBol == 6 || yeniBol == 7)) ||
            (bol == 2 && (yeniBol >= 0 && yeniBol <= 7)) ||
            (bol == 3 && (yeniBol >= 0 && yeniBol <= 7)) ||
            (bol == 4 && (yeniBol >= 0 && yeniBol <= 7)) ||
            (bol == 5 && (yeniBol >= 0 && yeniBol <= 7)) ||
            (bol == 6 && (yeniBol == 0 || yeniBol == 1)) ||
            (bol == 7 && (yeniBol == 0))) {
        
            
            if (yeniKonum == deger) {
                *p = 2; 
                return; 
            }
        
        }
    }
}
//! kontrolcü
void kontrol_siyahat_left(int deger,int*p,siyah*s1,beyaz*b1){
if (deger==s1->atR){*p=1;}
if (deger==s1->kaleL){*p=1;}
if (deger==s1->kaleR){*p=1;}    
if (deger==s1->filL){*p=1;}
if (deger==s1->filR){*p=1;}
if (deger==s1->sah){*p=1;}
if (deger==s1->vezir){*p=1;}
for (int i = 0; i < 8; i++)
{
    if (deger==s1->piyon[i]){*p=0;}
}


}
void kontrol_siyahat_right(int deger,int*p,siyah*s1,beyaz*b1){
if (deger==s1->atL){*p=1;}
if (deger==s1->kaleL){*p=1;}
if (deger==s1->kaleR){*p=1;}    
if (deger==s1->filL){*p=1;}
if (deger==s1->filR){*p=1;}
if (deger==s1->sah){*p=1;}
if (deger==s1->vezir){*p=1;}
for (int i = 0; i < 8; i++)
{
    if (deger==s1->piyon[i]){*p=1;}
}


}

void kontrol_beyazat_left(int deger,int*p,siyah*s1,beyaz*b1){
if (deger==b1->atR){*p=0;}
if (deger==b1->kaleL){*p=0;}
if (deger==b1->kaleR){*p=0;}    
if (deger==b1->filL){*p=0;}
if (deger==b1->filR){*p=0;}
if (deger==b1->sah){*p=0;}
if (deger==b1->vezir){*p=0;}
for (int i = 0; i < 8; i++)
{
    if (deger==b1->piyon[i]){*p=0;}
}


}

void kontrol_beyazat_right(int deger,int*p,siyah*s1,beyaz*b1){
if (deger==b1->atL){*p=0;}
if (deger==b1->kaleL){*p=0;}
if (deger==b1->kaleR){*p=0;}    
if (deger==b1->filL){*p=0;}
if (deger==b1->filR){*p=0;}
if (deger==b1->sah){*p=0;}
if (deger==b1->vezir){*p=0;}
for (int i = 0; i < 8; i++)
{
    if (deger==b1->piyon[i]){*p=0;}
}


}
//!kaleler
void kontrolKaleL(int deger, int *p, beyaz *b1) {
    int kaleKonumu = b1->kaleL; 
    int satir = kaleKonumu / 8; 

    // Yukarı hareket kontrolü
    for (int yukari = kaleKonumu - 8; yukari >= 0; yukari -= 8) {
        if (tahta[yukari] != 0) { // Eğer kare doluysa hareketi durdur
        break;
    }
    if (yukari == deger) {
            *p = 1; //  kale yukarı hareket
            return;
        }

    // Aşağı hareket kontrolü
    for (int asagi = kaleKonumu + 8; asagi < 64; asagi += 8) {
    if (tahta[asagi]!=0)
    {
        break;
    }
    
    if (asagi == deger) {
            *p = 1; 
            return;
        }
    }

        

    // Sola hareket kontrolü
    for (int sola = kaleKonumu - 1; sola >= satir * 8; sola--) {

        if (tahta[sola]!=0)
        {
            break;
        }
        

        if (sola == deger) {
            *p = 1; // Sağ kale sola hareketle bu kareyi kontrol edebilir
            return;
        }
    }

    // Sağa hareket kontrolü
    for (int saga = kaleKonumu + 1; saga < (satir + 1) * 8; saga++) {

        if (tahta[saga]!=0)
        {
            break;
        }
        
        if (saga == deger) {
            *p = 1; // Sağ kale sağa hareketle bu kareyi kontrol edebilir
            return;
        }
    }

    *p = 0; // Sağ kale bu kareyi kontrol edemez
}
}

void kontrolKaleR(int deger, int *p, beyaz *b1) {
    int kaleKonumu = b1->kaleR; 
    int satir = kaleKonumu / 8; 

    // Yukarı hareket kontrolü
    for (int yukari = kaleKonumu - 8; yukari >= 0; yukari -= 8) {
        if (tahta[yukari] != 0) { // Eğer kare doluysa hareketi durdur
        break;
    }
    if (yukari == deger) {
            *p = 1; // kale yukarı hareket
            return;
        }

    // Aşağı hareket kontrolü
    for (int asagi = kaleKonumu + 8; asagi < 64; asagi += 8) {
    if (tahta[asagi]!=0)
    {
        break;
    }
    
    if (asagi == deger) {
            *p = 1; 
            return;
        }
    }

        

    // Sola hareket kontrolü
    for (int sola = kaleKonumu - 1; sola >= satir * 8; sola--) {

        if (tahta[sola]!=0)
        {
            break;
        }
        

        if (sola == deger) {
            *p = 1; // Sağ kale sola hareketle bu kareyi kontrol edebilir
            return;
        }
    }

    // Sağa hareket kontrolü
    for (int saga = kaleKonumu + 1; saga < (satir + 1) * 8; saga++) {

        if (tahta[saga]!=0)
        {
            break;
        }
        
        if (saga == deger) {
            *p = 1; // Sağ kale sağa hareketle bu kareyi kontrol edebilir
            return;
        }
    }

    *p = 0; // Sağ kale bu kareyi kontrol edemez
}
}
void kontrolSiyahKaleL(int deger, int *p, siyah *s1) {
    int kaleKonumu = s1->kaleL; 
    int satir = kaleKonumu / 8; 

    // Yukarı hareket kontrolü
    for (int yukari = kaleKonumu - 8; yukari >= 0; yukari -= 8) {
        if (tahta[yukari] != 0) { // Eğer kare doluysa hareketi durdur
        break;
    }
    if (yukari == deger) {
            *p = 2; //  kale yukarı hareket
            return;
        }

    // Aşağı hareket kontrolü
    for (int asagi = kaleKonumu + 8; asagi < 64; asagi += 8) {
    if (tahta[asagi]!=0)
    {
        break;
    }
    
    if (asagi == deger) {
            *p = 2; 
            return;
        }
    }

        

    // Sola hareket kontrolü
    for (int sola = kaleKonumu - 1; sola >= satir * 8; sola--) {

        if (tahta[sola]!=0)
        {
            break;
        }
        

        if (sola == deger) {
            *p = 2; // Sağ kale sola hareketle bu kareyi kontrol edebilir
            return;
        }
    }

    // Sağa hareket kontrolü
    for (int saga = kaleKonumu + 1; saga < (satir + 1) * 8; saga++) {

        if (tahta[saga]!=0)
        {
            break;
        }
        
        if (saga == deger) {
            *p = 2; // Sağ kale sağa hareketle bu kareyi kontrol edebilir
            return;
        }
    }

    *p = 0; // Sağ kale bu kareyi kontrol edemez
}
}

void kontrolSiyahKaleR(int deger, int *p, siyah *s1) {
    int kaleKonumu = s1->kaleR; 
    int satir = kaleKonumu / 8; 

    // Yukarı hareket kontrolü
    for (int yukari = kaleKonumu - 8; yukari >= 0; yukari -= 8) {
        if (tahta[yukari] != 0) { // Eğer kare doluysa hareketi durdur
        break;
    }
    if (yukari == deger) {
            *p = 2; //  kale yukarı hareket
            return;
        }

    // Aşağı hareket kontrolü
    for (int asagi = kaleKonumu + 8; asagi < 64; asagi += 8) {
    if (tahta[asagi]!=0)
    {
        break;
    }
    
    if (asagi == deger) {
            *p = 2; 
            return;
        }
    }

        

    // Sola hareket kontrolü
    for (int sola = kaleKonumu - 1; sola >= satir * 8; sola--) {

        if (tahta[sola]!=0)
        {
            break;
        }
        

        if (sola == deger) {
            *p = 2; // Sağ kale sola hareketle bu kareyi kontrol edebilir
            return;
        }
    }

    // Sağa hareket kontrolü
    for (int saga = kaleKonumu + 1; saga < (satir + 1) * 8; saga++) {

        if (tahta[saga]!=0)
        {
            break;
        }
        
        if (saga == deger) {
            *p = 2; // Sağ kale sağa hareketle bu kareyi kontrol edebilir
            return;
        }
    }

    *p = 0; // Sağ kale bu kareyi kontrol edemez
}
}



//! piyonlar
void kontrolPiyonBeyaz(int deger, int *p, beyaz *b1, int secim) {
    int i = secim - 9;
    int piyonKonumu = b1->piyon[i]; 
    int satir = piyonKonumu / 8;    
    int sutun = piyonKonumu % 8;    

    //  (bir kare yukarı)
    int normalHareket = piyonKonumu + 8;

    
    int alabilecegiPozisyonSol = piyonKonumu + 7; // Sol çapraz
    int alabilecegiPozisyonSag = piyonKonumu + 9; // Sağ çapraz

    // Beyaz piyon başlangıç satırındaysa iki kare ilerleme kontrolü
    if (piyonKonumu >= 8 && piyonKonumu <= 15) { // Başlangıç satırındaki piyonlar (2. satır)
        for (int j = 0; j < 2; j++) {
            if (normalHareket == deger) {
                *p = 1;
                return; 
            }
            normalHareket += 8; 
        }
    }

    // Tek kare ileri hareket kontrolü
    if (piyonKonumu + 8 == deger) {
        *p = 1;
        return;
    }

    // rakip taşı alma
    if (alabilecegiPozisyonSol == deger || alabilecegiPozisyonSag == deger) {
        *p = 1;
        return;
    }
}



void kontrolPiyonSiyah(int deger, int *p, siyah *b1,int secim) {
    int i = secim - 48;
    int piyonKonumu = b1->piyon[i]; 
    int satir = piyonKonumu / 8;    
    int sutun = piyonKonumu % 8;    

    // Beyaz piyonun normal hareketi 
    int normalHareket = piyonKonumu - 8;

    
    int alabilecegiPozisyonSol = piyonKonumu - 7; // Sol çapraz
    int alabilecegiPozisyonSag = piyonKonumu - 9; // Sağ çapraz

    // Beyaz piyon başlangıç satırındaysa iki kare ilerleme kontrolü
    if (piyonKonumu >= 49 && piyonKonumu <= 56) { // Başlangıç satırındaki piyonlar (2. satır)
        for (int j = 0; j < 2; j++) {
            if (normalHareket == deger) {
                *p = 2;
                return; // Fonksiyonu bitir
            }
            normalHareket += 8; // Bir sonraki kareye bak (iki kare ileri hareket)
        }
    }

    // Tek kare ileri hareket kontrolü
    if (piyonKonumu - 8 == deger) {
        *p = 2;
        return;
    }

    // rakip taşı alma
    if (alabilecegiPozisyonSol == deger || alabilecegiPozisyonSag == deger) {
        *p = 2;
        return;
    }
}

//! piyon taş yeme
void tasKaldir2(int deger, siyah *s1) {
    for (int i = 0; i < 8; i++) {
        if (deger == s1->piyon[i]) {
            s1->piyon[i] = -1; // Siyah piyonu tahtadan kaldır
        }
    }
    if (deger == s1->sah) s1->sah = -1;
    if (deger == s1->vezir) s1->vezir = -1;
    if (deger == s1->kaleL) s1->kaleL = -1;
    if (deger == s1->kaleR) s1->kaleR = -1;
    if (deger == s1->atL) s1->atL = -1;
    if (deger == s1->atR) s1->atR = -1;
    if (deger == s1->filL) s1->filL = -1;
    if (deger == s1->filR) s1->filR = -1;
}
void tasKaldir(int deger, beyaz *b1) {
    for (int i = 0; i < 8; i++) {
        if (deger == b1->piyon[i]) {
            b1->piyon[i] = -1; // Beyaz piyonu tahtadan kaldır
            return; 
        }
    }

    // Diğer taşları kaldır
    if (deger == b1->sah) {
        b1->sah = -1;
    } else if (deger == b1->vezir) {
        b1->vezir = -1;
    } else if (deger == b1->kaleL) {
        b1->kaleL = -1;
    } else if (deger == b1->kaleR) {
        b1->kaleR = -1;
    } else if (deger == b1->atL) {
        b1->atL = -1;
    } else if (deger == b1->atR) {
        b1->atR = -1;
    } else if (deger == b1->filL) {
        b1->filL = -1;
    } else if (deger == b1->filR) {
        b1->filR = -1;
    }
}








int main(){
int siyahh=0;
int secim=1;
beyaz b1;
siyah s1;
int p=2;
int deger;
int hata;
baslat_beyaz(&b1);
baslat_siyah(&s1);
while (secim >0)
{
    tahta_guncelle(&b1, &s1);
    printf("Beyaz taş seçmeli 1-8 veya piyonlar 9-16 (Pes etmek için için 0): \n");
    printf("1-kale 2-at 3-fil 4-vezir 5-sah 6-fil2 7-at2 8-kale2\n");
    printf("9-piyon1 10-piyon2 11-piyon3 12-piyon4 13-piyon5 14-piyon6 15-piyon7 16-piyon8\n");
    scanf("%d", &secim);
    if (b1.sah==-1)
    {
        printf("beyaz kazandı");
        secim=-1;
        p=-1;
        break;
    }
    if (secim==0)
    {
        printf("siyahlar pes etti beyazlar kazandı");
        break;
    }
    
    printf("oynamak istediğiniz kareyi seçiniz");
    scanf("%d",&deger);
   
    switch (secim)
    {
    case 1:
        kontrolKaleL(deger,&p,&b1);
        if (p==1)
        {
            b1.kaleL=deger;
            tasKaldir2(deger,&s1);
            

        }else{
            printf("hatalı hamle\n");
        }
        
        break;
        case 2:
        kontrolAL(deger,&p,&b1);
        kontrol_beyazat_left(deger,&p,&s1,&b1);
        if (p==1)
        {
            b1.atL=deger;
            tasKaldir2(deger,&s1);

        }else{
            printf("hatalı hamle\n");
        }
        
        break;
        case 3:
        kontrolFL(deger,&p,&b1);
        if (p==1)
        {
            b1.filL=deger;
            tasKaldir2(deger,&s1);

        }else{
            printf("hatalı hamle\n");
        }
        
        break;
        case 4:
        kontrolVezir(deger,&p,&b1);
        if (p==1)
        {
            b1.vezir=deger;
            tasKaldir2(deger,&s1);

        }else{
            printf("hatalı hamle\n");
        }
        
        break;
        case 5:
        kontrolBeyazSah(deger,&p,&b1);
        if (p==1)
        {
            b1.sah=deger;
            tasKaldir2(deger,&s1);

        }else{
            printf("hatalı hamle\n");
        }
        
        break;
        case 6:
        kontrolFR(deger,&p,&b1);
        if (p==1)
        {
            b1.filR=deger;
            tasKaldir2(deger,&s1);

        }else{
            printf("hatalı hamle\n");
        }
        
        break;
        case 7:
        kontrolAR(deger,&p,&b1);
        kontrol_beyazat_right(deger,&p,&s1,&b1);
        if (p==1)
        {
            b1.atR=deger;
            tasKaldir2(deger,&s1);

        }else{
            printf("hatalı hamle\n");
        }
        
        break;
        case 8:
        kontrolKaleR(deger,&p,&b1);
        if (p==1)
        {
            b1.kaleR=deger;
            tasKaldir2(deger,&s1);

        }else{
            printf("hatalı hamle\n");
        }
        
        break;
        case 9:
        kontrolPiyonBeyaz(deger,&p,&b1,secim);
        if (p==1)
        {
            b1.piyon[0]=deger;
            tasKaldir2(deger,&s1);
            
        }else{
            printf("hatalı hamle\n");
        }
        break;
        case 10:
        kontrolPiyonBeyaz(deger,&p,&b1,secim);
        if (p==1)
        {
            b1.piyon[1]=deger;
            tasKaldir2(deger,&s1);
            
        }else{
            printf("hatalı hamle\n");
        }
        break;
        case 11:
        kontrolPiyonBeyaz(deger,&p,&b1,secim);
        if (p==1)
        {
            b1.piyon[2]=deger;
            tasKaldir2(deger,&s1);
            
        }else{
            printf("hatalı hamle\n");
        }
        break;
        case 12:
        kontrolPiyonBeyaz(deger,&p,&b1,secim);
        if (p==1)
        {
            b1.piyon[3]=deger;
            tasKaldir2(deger,&s1);
            
        }else{
            printf("hatalı hamle\n");
        }
        break;
        case 13:
        kontrolPiyonBeyaz(deger,&p,&b1,secim);
        if (p==1)
        {
            b1.piyon[4]=deger;
            tasKaldir2(deger,&s1);
            
        }else{
            printf("hatalı hamle\n");
        }
        break;
        case 14:
        kontrolPiyonBeyaz(deger,&p,&b1,secim);
        if (p==1)
        {
            b1.piyon[5]=deger;
            tasKaldir2(deger,&s1);
            
        }else{
            printf("hatalı hamle\n");
        }
        break;
        case 15:
        kontrolPiyonBeyaz(deger,&p,&b1,secim);
        if (p==1)
        {
            b1.piyon[6]=deger;
            tasKaldir2(deger,&s1);
            
        }else{
            printf("hatalı hamle\n");
        }
        break;
        case 16:
        kontrolPiyonBeyaz(deger,&p,&b1,secim);
        if (p==1)
        {
            b1.piyon[7]=deger;
            tasKaldir2(deger,&s1);
            
        }else{
            printf("hatalı hamle\n");
        }
        break;
    
    
    
    
    
    default:
        break;
    
   }
   while (p==1)
   {
   
    tahta_guncelle(&b1, &s1);
    printf("Siyah taş seçmeli 57-64 veya piyonlar 49-56 (Pes etmek için için 0): ");
    printf("57-kale 58-at 59-fil 60-vezir 61-sah 62-fil2 63-at2 64-kale2\n");
    printf("49-piyon1 50-piyon2 51-piyon3 52-piyon4 53-piyon5 54-piyon6 55-piyon7 56-piyon8");
    scanf("%d", &secim);
    if (secim==0)
    {
        printf("Siyah pes etti beyazlar kazandı");
        break;
    }
    if (s1.sah==-1)
    {
        printf("beyaz kazandı");
        secim=-1;
        p=-1;
        break;
    }
    
    
    printf("oynamak istediğiniz kareyi seçiniz");
    scanf("%d",&deger);




    switch (secim)
    {
        case 49:
        kontrolPiyonSiyah(deger,&p,&s1,secim);
        if (p==2)
        {
            s1.piyon[0]=deger;
            tasKaldir(deger,&b1);
            
        }else{
            printf("hatalı hamle\n");
        }
        break;
        case 50:
        kontrolPiyonSiyah(deger,&p,&s1,secim);
        if (p==2)
        {
            s1.piyon[1]=deger;
            tasKaldir(deger,&b1);
            
        }else{
            printf("hatalı hamle\n");
        }
        break;
        case 51:
        kontrolPiyonSiyah(deger,&p,&s1,secim);
        if (p==2)
        {
            s1.piyon[2]=deger;
            tasKaldir(deger,&b1);
            
        }else{
            printf("hatalı hamle\n");
        }
        break;
        case 52:
        kontrolPiyonSiyah(deger,&p,&s1,secim);
        if (p==2)
        {
            s1.piyon[3]=deger;
            tasKaldir(deger,&b1);
            
        }else{
            printf("hatalı hamle\n");
        }
        break;
        case 53:
        kontrolPiyonSiyah(deger,&p,&s1,secim);
        if (p==2)
        {
            s1.piyon[4]=deger;
            tasKaldir(deger,&b1);
            
        }else{
            printf("hatalı hamle\n");
        }
        break;
        case 54:
        kontrolPiyonSiyah(deger,&p,&s1,secim);
        if (p==2)
        {
            s1.piyon[5]=deger;
            tasKaldir(deger,&b1);
            
        }else{
            printf("hatalı hamle\n");
        }
        break;
        case 55:
        kontrolPiyonSiyah(deger,&p,&s1,secim);
        if (p==2)
        {
            s1.piyon[6]=deger;  
            tasKaldir(deger,&b1);
            
        }else{
            printf("hatalı hamle\n");
        }
        break;
        case 56:
        kontrolPiyonSiyah(deger,&p,&s1,secim);
        if (p==2)
        {
            s1.piyon[7]=deger;
            tasKaldir(deger,&b1);
            
        }
    case 57:   
    kontrolSiyahKaleL(deger,&p,&s1);
    if (p==2)
    {
        s1.kaleL=deger;
        tasKaldir(deger,&b1);


    }else{
            printf("hatalı hamle\n");
        }
    
        break;
            case 58:
    kontrolSiyahAL(deger,&p,&s1);
    kontrol_siyahat_left(deger,&p,&s1,&b1);
    if (p==2)
    {
        s1.atL=deger;
        tasKaldir(deger,&b1);


    }else{
            printf("hatalı hamle\n");
        }
    
        break;
            case 59:
    kontrolFilSiyahSol(deger,&p,&s1);
    if (p==2)
    {
        s1.filL=deger;
        tasKaldir(deger,&b1);


    }else{
            printf("hatalı hamle\n");
        }
    
        break;
            case 60:
    kontrolVezirSiyah(deger,&p,&s1);
    if (p==2)
    {
        s1.vezir=deger;
        tasKaldir(deger,&b1);


    }else{
            printf("hatalı hamle\n");
        }
    
        break;
            case 61:
    kontrolSiyahSah(deger,&p,&s1);
    if (p==2)
    {
        s1.sah=deger;
        tasKaldir(deger,&b1);


    }else{
            printf("hatalı hamle\n");
        }
    
        break;
            case 62:
    kontrolFilSiyahR(deger,&p,&s1);
    if (p==2)
    {
        s1.filR=deger;
        tasKaldir(deger,&b1);


    }else{
            printf("hatalı hamle\n");
        }
    
        break;
            case 63:
    kontrolSiyahAR(deger,&p,&s1);
    kontrol_siyahat_right(deger,&p,&s1,&b1);
    if (p==2)
    {
        s1.atR=deger;
        tasKaldir(deger,&b1);


    }else{
            printf("hatalı hamle\n");
        }
    
        break;
            case 64:
    kontrolSiyahKaleR(deger,&p,&s1);
    if (p==2)
    {
        s1.kaleR=deger;
        tasKaldir(deger,&b1);


    }else{
            printf("hatalı hamle\n");
        }
    
        break;
    
    default:
        break;
    }




   }



}

}
