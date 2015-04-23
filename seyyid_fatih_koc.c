// isim: Seyyid Fatih KOÇ  nu: 030113003 

int led = 13;   // 13 nolu port cok kullanilacagi icin degiskene ataniyor
long ogr_numara= 30113003;  // ogrenci numarasi ataniyor


void ogr_bilgi();   // ogrenci bilgilerini seri porta yazdirir
int zaman_hesapla(long ogr_numara, int sondan_kac_hane); // ogr_numara sının, sondan_kac_hane si isteniyorsa hesaplar
long kuvvet_10(int us); // 10 un us. kuvvetini hesaplar
void oku_yazdir(int sure);  // seri porttan gelen veriyi okur, seri porta yazdirir


void setup() {
    pinMode(led, OUTPUT); // 13 nolu porta cikis veriliyor
    Serial.begin(9600);   //seri port 9600 baud rate hizinda ayarlaniyor
}


void loop() {
    ogr_bilgi();    //  ogrenci bilgileri seri porttan cikti olarak gonderiliyor
    int gecikme_suresi = zaman_hesapla(ogr_numara,3);   // ogrenci numarasinin son 3 hanesi, gecikme suresi olarak cekiliyor

    while(1){   // sonsuz dongu baslatiliyor. boylece seri porttan devamli veri girilebilir
        oku_yazdir(gecikme_suresi); // seri porttan girdi bekleniyor, girdi girildikten sonra;
    }                               // her karakter farklı satirlarda seri port ciktisi olarak gonderiliyor
}                                   // her karakterden sonra led yaniyor, gecikme_suresi kadar bekleniyor, ardindan led sonuyor


void ogr_bilgi(){
    Serial.print("Seyyid Fatih ");   // alt satira gecmeden ad yazdirilir
    delay(1500);        // 1.5 sn beklenir
    Serial.println("KOC");  // soyad yazdirilir, ardindan alt satira gecilir
}


int zaman_hesapla(long ogr_numara, int sondan_kac_hane){
    long bolen = kuvvet_10(sondan_kac_hane+1); //  bolen degeri 10 un kuvveti olarak hesaplanir
    long bolum = ogr_numara / bolen;     //sayiyi bolen e bolunerek bolum hesaplanir
    return ogr_numara- bolen*bolum;      //sayidan bolen*bolum cikarilarak son basamaklar hesaplanir
}


long kuvvet_10(int us){
    long on=1;  
    for (int i = 0; i < us-1; ++i){     //on degiskeni, us kadar 10 ile carpiliyor
      on *=10; 
    }
    return on;
}


void oku_yazdir(int sure){
    char okunan_veri = 0;   
    if (Serial.available() > 0) {   // seri porttan gelip buffer da bekleyen veri varsa alttaki sorgu calisir
        okunan_veri = Serial.read();    // buffer daki siradaki veri cekilir
        Serial.println(okunan_veri);    // veri farkli bir satira yazdirilir
        digitalWrite(led, HIGH);    // led yakilir
        delay(sure);                // sure kadar ms beklenir
        digitalWrite(led, LOW);    //  led sondurulur
    }
}