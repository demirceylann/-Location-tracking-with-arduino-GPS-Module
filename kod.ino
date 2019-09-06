#include <NeoSWSerial.h>//NeoSWSerial kutuphanesi
#include <TinyGPS++.h>//TinyGPS++ kutuphanesi
#include <LiquidCrystal.h>//Lcd ekran kutuphanesi
NeoSWSerial gpsSerial( 2, 3 );//2 ve 3 seri haberlesme pinleri(Rx-Tx)
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);//LCD pinleri ataniyor.
TinyGPSPlus gps;// gps nesnesi tanımlanıyor.
float Enlem;//Bulundugumuz enlemi alan degisken
float Boylam;///Bulundugumuz boylami alan degisken

void setup()
{
  Serial.begin( 9600 );//Pc - Arduino haberlesme hizi (9600 baud)
  gpsSerial.begin( 9600 );//Gps modulu - Arduino haberlesme hizi
  lcd.begin(16, 2);//Adruino'ya 16*2 lcd ekran kullanacagimizi belirttik
  lcd.print("GPS Konumum");//
  delay(2000);//2 saniye bekleme
  lcd.clear();//lcd'yi temizle
}

void loop()
{
 /* if (gpsSerial.available())
    Serial.write( gpsSerial.read() );*/
  while(1)
  {
   while (gpsSerial.available() > 0)//Gps'den herhangi bir veri alindi mi?
   { 
      gps.encode(gpsSerial.read());//gps modulunden veriyi al.
   }

      if (gps.location.isUpdated())//gps konumu degisti mi?
      {
       Serial.print("Enlem="); 
       Serial.println(gps.location.lat(), 6);//gps.location.lat() fonksiyonu enlem degeri dondurur. (Seri Port ekranina yazdirir.)
       Serial.print("Boylam="); 
       Serial.println(gps.location.lng(), 6);//gps.location.lng() fonksiyonu boylam degeri dondurur. (Seri Port ekranina yazdirir.)
       
       Enlem = gps.location.lat();//gps modulunden alinan enlem degerini degiskene aktar.
       Boylam = gps.location.lng();//gps modulundan alinan boylam degerini degiskene aktar.
       break;//Donguyu kirdik.
      }
  }
 lcd.print("Enlem ");//Enlem diye ekrana yazdirilir
 lcd.print(Enlem,6);//LCD ekrana enlem degeri yazdirilir.
 lcd.setCursor(0, 1);//LCD ekranin bir alt satira gecmesi icin
 lcd.print("Boylam ");
 lcd.print(Boylam,6);//LCD ekrana boylam degeri yazdirilir.
 delay(1000);//1 saniye bekleme yapilir.
 lcd.clear();//LCD ekran temizlenir.
}
