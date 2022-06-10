#include <LiquidCrystal_I2C.h>

#include <AntaresESP8266HTTP.h>
#include <RTClib.h>
RTC_DS3231 rtc;

#define Touch 14 // pin d5
#define Relay 12 // pin d6
float statusLampu = 0; // memberikan informasi pada lampu
float fi = 1; 

// Kirim Data
#define ACCESSKEY "9b50980dd0c757de:64dbb197d3487286"
#define WIFISSID "Galaxy"
#define PASSWORD "12345678"

#define projectName "kelompok-4"
#define deviceName "touchsensor"

AntaresESP8266HTTP antares(ACCESSKEY);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600); // kecepatan pengiriman data
  pinMode(Touch, INPUT); // input touch sensor
  pinMode(Relay, OUTPUT); // output pada relay
  rtc.begin(); // memulai rtc

  lcd.init();
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("KELOMPOK 4");
  lcd.setCursor(5,1);
  lcd.print("CPS LAB");

  rtc.adjust(DateTime(__DATE__, __TIME__)); //mengatur waktu pada RTC sesuai dengan waktu pada komputer
  rtc.adjust(DateTime(2022, 06, 10, 19, 18, 0)); // kalibrasi manual
  antares.setDebug(false); 
  antares.wifiConnection(WIFISSID,PASSWORD);
}

void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Date: ");
  lcd.setCursor(0, 1);
  lcd.print("Time: ");

  DateTime now = rtc.now();

  lcd.setCursor(6, 0);
  lcd.print(now.year(), DEC);
  lcd.print(":");
  lcd.print(now.month(), DEC);
  lcd.print(":");
  lcd.print(now.day(), DEC);
 
  lcd.setCursor(6, 1);
  lcd.print(now.hour(), DEC);
  lcd.print(":");
  lcd.print(now.minute(), DEC);
  lcd.print(":");
  lcd.print(now.second(), DEC);

 
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  float kondisi= digitalRead(Touch);

  if (now.hour() >= 18 && now.hour() < 19 && fi==1){
    digitalWrite(Relay, HIGH);
    statusLampu =1;
    fi=0;
  }
 
  
  if (now.hour() < 18 && fi==0 || now.hour() >= 19 && fi==0) {
    digitalWrite(Relay, LOW);
    statusLampu =0;
    fi=1;
    }
    
  if (kondisi == 1){ // kondisi lampu menyala
    if(statusLampu == 0){ 
      Serial.println("Lampu HIDUP"); 
      statusLampu = 1;
      digitalWrite(Relay, HIGH);
    }
    else {
      Serial.println("Lampu MATI");
      statusLampu = 0;
      digitalWrite(Relay, LOW);
    }
    Serial.println("DISENTUH");
  
}
  antares.add("lampu", statusLampu);
  antares.add("TAHUN",now.year());
  antares.add("BULAN",now.month());
  antares.add("TANGGAL",now.day());
  antares.add("JAM",now.hour());
  antares.add("MENIT",now.minute());
  antares.add("DETIK",now.second());
  antares.send(projectName, deviceName);
}
