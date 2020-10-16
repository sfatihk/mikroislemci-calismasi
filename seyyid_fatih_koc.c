// isim: Seyyid Fatih KOÇ  nu: 030113003 

int led = 13;   // 13 nolu port cok kullanilacagi icin degiskene ataniyor
long studentNumber= 30113003;  // ogrenci numarasi ataniyor


void studentInfo();   // ogrenci bilgilerini seri porta yazdirir
int calculateTime(long studentNumber, int lastDigitsCount); // studentNumber sının, lastDigitsCount si isteniyorsa hesaplar
long powerOf10(int power); // 10 un power. kuvvetini hesaplar
void readAndWrite(int delayTime);  // seri porttan gelen veriyi okur, seri porta yazdirir


void setup() {
    pinMode(led, OUTPUT); // 13 nolu porta cikis veriliyor
    Serial.begin(9600);   //seri port 9600 baud rate hizinda ayarlaniyor
}


void loop() {
    studentInfo();    //  ogrenci bilgileri seri porttan cikti olarak gonderiliyor
    int delayTime = calculateTime(studentNumber,3);   // ogrenci numarasinin son 3 hanesi, gecikme delayTimesi olarak cekiliyor

    while(1){   // sonsuz dongu baslatiliyor. boylece seri porttan devamli veri girilebilir
        readAndWrite(delayTime); // seri porttan girdi bekleniyor, girdi girildikten sonra;
    }                               // her karakter farklı satirlarda seri port ciktisi olarak gonderiliyor
}                                   // her karakterden sonra led yaniyor, delayTime kadar bekleniyor, ardindan led sonuyor


void studentInfo(){
    Serial.print("Seyyid Fatih ");   // alt satira gecmeden ad yazdirilir
    delay(1500);        // 1.5 sn beklenir
    Serial.println("KOC");  // soyad yazdirilir, ardindan alt satira gecilir
}


int calculateTime(long studentNumber, int lastDigitsCount){
    long bolen = powerOf10(lastDigitsCount+1); //  bolen degeri 10 un kuvveti olarak hesaplanir
    long bolum = studentNumber / bolen;     //sayiyi bolen e bolunerek bolum hesaplanir
    return studentNumber- bolen*bolum;      //sayidan bolen*bolum cikarilarak son basamaklar hesaplanir
}


long powerOf10(int power){
    long on=1;  
    for (int i = 0; i < power-1; ++i){     //on degiskeni, power kadar 10 ile carpiliyor
      on *=10; 
    }
    return on;
}


void readAndWrite(int delayTime){
    char dataRead = 0;   
    if (Serial.available() > 0) {   // seri porttan gelip buffer da bekleyen veri varsa alttaki sorgu calisir
        dataRead = Serial.read();    // buffer daki siradaki veri cekilir
        Serial.println(dataRead);    // veri farkli bir satira yazdirilir
        digitalWrite(led, HIGH);    // led yakilir
        delay(delayTime);                // delayTime kadar ms beklenir
        digitalWrite(led, LOW);    //  led sondurulur
    }
}