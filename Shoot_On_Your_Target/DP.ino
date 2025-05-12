#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

SoftwareSerial serial(10, 11);
LiquidCrystal_I2C lcd(0x26,16,2);
LiquidCrystal_I2C lcd1(0x27,16,2);

unsigned long timer_versus, timer_solo1, timer_solo2, interval = 1000, timer_song = 0;
int cek1 = 0, cek2 = 0, cek3 = 0, cek4 = 0;
int button_versus = 2;
int button_solo1 = 3;
int button_solo2 = 4;
int buttonstate_versus, buttonstate_solo1, buttonstate_solo2;
unsigned long currentMillis_timer, currentMillis_timer1, currentMillis_ready1 = 0, currentMillis_ready2 = 0,currentMillis1, currentMillis2, currentMillis3, currentMillis4, currentMillis5, currentMillis6, currentMillis_lcd = 0;
bool check_button_versus = true,check_button_solo1 = true, check_button_solo2 = true, ready1 = false, ready2 = false, check_sensor1 = true, check_sensor2 = true, check_sensor3 = true, check_sensor4 = true, check_sensor5 = true, check_sensor6 = true, read_solo1 = true, read_solo2 = true, read_versus = true;
int Score1 = 0, Score2 = 0;
bool play_solo1 = false, play_solo2  = false, play_versus = false, start1 = false, start2 = false;

#define TCA_ADDR 0x70 // Alamat multiplexer TCA9548A
int R, G, B;
String color;

Adafruit_TCS34725 tcs1 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_TCS34725 tcs2 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_TCS34725 tcs3 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_TCS34725 tcs4 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_TCS34725 tcs5 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_TCS34725 tcs6 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void tcaselect(uint8_t i) {
  if (i > 7) return;

  Wire.beginTransmission(TCA_ADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}

void setup() {
  Serial.begin(230400);
  Wire.begin();
  
  //set up the button
  pinMode(button_versus, INPUT_PULLUP);
  pinMode(button_solo1, INPUT_PULLUP);
  pinMode(button_solo2, INPUT_PULLUP);

  // set up the music
  serial.begin(9600);  
  mp3_set_serial (serial);
  delay(5); 
  mp3_set_volume(40);
  delay(1000);
  mp3_play(1);
  
  lcd.init();
  lcd1.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd1.backlight();

  // Inisialisasi kedua sensor
  tcaselect(0);
  if (tcs1.begin()) {
    Serial.println("Sensor 1 ditemukan!");
  }
  tcaselect(1);
  if (tcs2.begin()) {
    Serial.println("Sensor 2 ditemukan!");
  }
  tcaselect(2);
  if (tcs3.begin()) {
    Serial.println("Sensor 3 ditemukan!");
  }
  tcaselect(3);
  if (tcs4.begin()) {
    Serial.println("Sensor 4 ditemukan!");
  }
  tcaselect(4);
  if (tcs5.begin()) {
    Serial.println("Sensor 5 ditemukan!");
  }
  tcaselect(5);
  if (tcs6.begin()) {
    Serial.println("Sensor 6 ditemukan!");
  }
}

void loop() {

  if (read_versus == true && read_solo1 == true && read_solo2 == true) {
    buttonstate_versus = digitalRead(button_versus);
  }
  if (read_solo1 == true) {
    buttonstate_solo1 = digitalRead(button_solo1);
  }
  if (read_solo2 == true) {
    buttonstate_solo2 = digitalRead(button_solo2);
  }
  
  // cek apakah tombol ditekan dan ambil waktu pada saat tombol ditekan
  if (check_button_versus == true && buttonstate_versus == HIGH) {
    cek1 = 0;
    cek2 = 0;
    read_solo1 = false;
    read_solo2 = false;
    mp3_play(2);
    delay(1000);
    play_versus = true;
    check_button_versus = false;
    Score1 = 0;
    Score2 = 0;

    lcd.clear();
    lcd1.clear();
    lcd.setCursor(5, 0);
    lcd.print("Ready");
    lcd1.setCursor(5, 0);
    lcd1.print("Ready");
    delay(1000);
    lcd.clear();
    lcd1.clear();
    mp3_play(4);
    lcd.setCursor(7, 0);
    lcd.print("3");
    lcd1.setCursor(7, 0);
    lcd1.print("3");
    delay(1000);
    lcd.setCursor(7, 0);
    lcd.print("2");
    lcd1.setCursor(7, 0);
    lcd1.print("2");
    delay(1000);
    lcd.setCursor(7, 0);
    lcd.print("1");
    lcd1.setCursor(7, 0);
    lcd1.print("1");
    delay(700);
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("GO!!!");
    lcd1.setCursor(5, 0);
    lcd1.print("GO!!!");
    delay(1000);
    lcd.clear();
    lcd1.clear();
    mp3_stop();
    currentMillis_timer = millis();
    timer_versus = 120000 + millis();
    timer_song = millis();

  } 
  if (check_button_solo1 == true && buttonstate_solo1 == HIGH) {
    cek3 = 0;
    cek4 = 0;
    read_versus = false;
    read_solo1 = false;
    play_solo1 = true;
    ready1 = true;
    mp3_play(2);
    delay(1000);
    check_button_solo1 = false;
    Score1 = 0;
    currentMillis_ready1 = millis();
    lcd.clear();
  }
  
  if (ready1 == true) {
    unsigned long elapsedMillis = millis() - currentMillis_ready1;
    if (elapsedMillis >= 1300 && elapsedMillis <= 1310) {
      mp3_play(4);
    }
    
    if (elapsedMillis < 1000) {
      lcd.setCursor(5, 0);
      lcd.print("Ready");
    } else if (elapsedMillis <= 1500) {
      lcd.clear();
    } else if (elapsedMillis < 2000) {
      lcd.setCursor(7,0);
      lcd.print("3");
    } else if (elapsedMillis <= 2100) {
      lcd.clear();
    } else if (elapsedMillis < 3000) {
      lcd.setCursor(7,0);
      lcd.print("2");
    } else if (elapsedMillis <= 3100) {
      lcd.clear();
    } else if (elapsedMillis < 3700) {
      lcd.setCursor(7,0);
      lcd.print("1");
    } else if (elapsedMillis <= 3800) {
      lcd.clear();
    } else if (elapsedMillis < 4700) {
      lcd.setCursor(5,0);
      lcd.print("GO!!!");
    } else if (elapsedMillis <= 4800) {
      lcd.clear();
    } else {
      currentMillis_timer = millis();
      timer_solo1 = 120000 + millis();
      timer_song = millis();
      start1 = true;
      ready1 = false;
      lcd.clear();
    }
  }

  if (check_button_solo2 == true && buttonstate_solo2 == HIGH) {
    cek1 = 0;
    cek2 = 0;
    read_versus = false;
    read_solo2 = false;
    mp3_play(2);
    delay(1000);
    play_solo2 = true;
    ready2 = true;
    check_button_solo2 = false;
    Score2 = 0;
    currentMillis_ready2 = millis();
    lcd1.clear();
  }
  
  if (ready2 == true) {
    unsigned long elapsedMillis1 = millis() - currentMillis_ready2;

    if (elapsedMillis1 >= 1300 && elapsedMillis1 <= 1350) {
      mp3_play(4);
    }

    if (elapsedMillis1 < 1000) {
      lcd1.setCursor(5, 0);
      lcd1.print("Ready");
    } else if (elapsedMillis1 <= 1500) {
      lcd1.clear();
    } else if (elapsedMillis1 < 2000) {
      lcd1.setCursor(7,0);
      lcd1.print("3");
    } else if (elapsedMillis1 <= 2100) {
      lcd1.clear();
    } else if (elapsedMillis1 < 3000) {
      lcd1.setCursor(7,0);
      lcd1.print("2");
    } else if (elapsedMillis1 <= 3100) {
      lcd1.clear();
    } else if (elapsedMillis1 < 3700) {
      lcd1.setCursor(7,0);
      lcd1.print("1");
    } else if (elapsedMillis1 <= 3800) {
      lcd1.clear();
    } else if (elapsedMillis1 < 4700) {
      lcd1.setCursor(5,0);
      lcd1.print("GO!!!");
    } else if (elapsedMillis1 <= 4800) {
      lcd1.clear();
    } else {
      timer_solo2 = 120000 + millis();
      currentMillis_timer1 = millis();
      timer_song = millis();
      start2 = true;
      ready2 = false;
      lcd1.clear();
    }
  }

  if (play_versus == false && play_solo1 == false && play_solo2 == false) {
    if (millis() - currentMillis_lcd < 2000) {
      lcd.setCursor(0, 0);
      lcd.print("Hi, Player 1");
      lcd.setCursor(6,1);
      lcd.print("^_^");
      lcd1.setCursor(0, 0);
      lcd1.print("Hi, Player 2");
      lcd1.setCursor(6,1);
      lcd1.print("^_^");
    } else if (millis() - currentMillis_lcd <= 2000) {
      lcd.clear();
      lcd1.clear();
    } else if (millis() - currentMillis_lcd < 4000) {
      lcd.setCursor(0,0);
      lcd.print("Choose the mode");
      lcd.setCursor(0,1);
      lcd.print("Solo/Versus");
      
      lcd1.setCursor(0,0);
      lcd1.print("Choose the mode");
      lcd1.setCursor(0,1);
      lcd1.print("Solo/Versus");
    } else {
      currentMillis_lcd = millis();
      lcd.clear();
      lcd1.clear();
    }
  }

  if (play_versus == true) {
    //timer game
    lcd.setCursor(0, 0);
    lcd.print("Score = ");
    lcd.print(Score1);
    lcd.setCursor(0, 1);
    lcd.print("Waktu = ");
    lcd.print((timer_versus - millis())/1000);
    lcd1.setCursor(0, 0);
    lcd1.print("Score = ");
    lcd1.print(Score2);
    lcd1.setCursor(0, 1);
    lcd1.print("Waktu = ");
    lcd1.print((timer_versus - millis())/1000);

    if ((timer_versus - millis())/1000 <= 99 && cek1 != 1) {
      lcd.clear();
      lcd1.clear();
      cek1 = cek1 + 1;
    }
    if ((timer_versus - millis())/1000 <= 9 && cek2 != 1) {
      lcd.clear();
      lcd1.clear();
      cek2 = cek2 + 1;
    }

    // Baca data dari sensor pertama, orange/kuning
    if (check_sensor1 == true) {
      tcaselect(0);
      float red1, green1, blue1;
      tcs1.getRGB(&red1, &green1, &blue1);
      R = int(red1);
      G = int(green1);
      B = int(blue1);
      color = "";
      if((R>110)&(R<190)&(G>50)&(G<88)&(B>20)&(B<44)){
        color = "Orange";
        currentMillis1 = millis(); 
        mp3_play(3);
        lcd.backlight();
        lcd.setCursor(0, 0);
        Score1 = Score1+1;
        lcd.print("Score = ");
        lcd.print(Score1);
        check_sensor1 = false;
      } else if((R>30)&(R<50)&(G>99)&(G<130)&(B>70)&(B<107)){
        color = "Blue";
        currentMillis1 = millis();
        check_sensor1 = false;
        mp3_play(5);
      } else if((R>59)&(R<93)&(G>110)&(G<130)&(B>37)&(B<55)){
        color = "Green";
        currentMillis1 = millis();
        check_sensor1 = false;
        mp3_play(5);
      } else if((R>55)&(R<80)&(G>92)&(G<115)&(B>60)&(B<75)){
        color = "White";
        currentMillis1 = millis();
        check_sensor1 = false;
        mp3_play(5);
      } else if ((R-B>40)&(G-B>40)){
        color = "Yellow";
        currentMillis1 = millis(); 
        mp3_play(3);
        lcd.backlight();
        lcd.setCursor(0, 0);
        Score1 = Score1+1;
        lcd.print("Score = ");
        lcd.print(Score1);
        check_sensor1 = false;
      }
      Serial.print("Sensor 1 - R: "); Serial.print(int(red1));
      Serial.print(" G: "); Serial.print(int(green1));
      Serial.print(" B: "); Serial.print(int(blue1));
      Serial.print("   Color: ");Serial.print(color);
      Serial.println();
    }

    if (millis() - currentMillis1 > 1000) {
      check_sensor1 = true;
    }

    // Baca data dari sensor kedua, putih hijau
    if (check_sensor2 == true) {
      tcaselect(1);
      float red2, green2, blue2;
      tcs2.getRGB(&red2, &green2, &blue2);
      R = int(red2);
      G = int(green2);
      B = int(blue2);
      color = "";
      if((R>110)&(R<190)&(G>50)&(G<88)&(B>20)&(B<44)){
        color = "Orange";
        currentMillis2 = millis();
        check_sensor2 = false;
        mp3_play(5);
      } else if((R>30)&(R<50)&(G>99)&(G<130)&(B>70)&(B<107)){
        color = "Blue";
        currentMillis2 = millis();
        check_sensor2 = false;
        mp3_play(5);
      } else if((R>59)&(R<93)&(G>110)&(G<130)&(B>37)&(B<55)){
        color = "Green";
        currentMillis2 = millis(); 
        mp3_play(3);
        lcd.backlight();
        lcd.setCursor(0, 0);
        Score1 = Score1+1;
        lcd.print("Score = ");
        lcd.print(Score1);
        check_sensor2 = false;
      } else if((R>55)&(R<80)&(G>92)&(G<115)&(B>60)&(B<75)){
        color = "White";
        currentMillis2 = millis(); 
        mp3_play(3);
        lcd.backlight();
        lcd.setCursor(0, 0);
        Score1 = Score1+1;
        lcd.print("Score = ");
        lcd.print(Score1);
        check_sensor2 = false;
      } else if ((R-B>40)&(G-B>40)){
        color = "Yellow";
        currentMillis2 = millis(); 
        check_sensor2 = false;
        mp3_play(5);
      }

      Serial.print("Sensor 2 - R: "); Serial.print(int(red2));
      Serial.print(" G: "); Serial.print(int(green2));
      Serial.print(" B: "); Serial.print(int(blue2));
      Serial.print("   Color: ");Serial.print(color);
      Serial.println();
    }

    if (millis() - currentMillis2 > 1000) {
      check_sensor2 = true;
    }

    // Baca data dari sensor ketiga biru
    if (check_sensor3 == true) {
      tcaselect(2);
      float red3, green3, blue3;
      tcs3.getRGB(&red3, &green3, &blue3);
      R = int(red3);
      G = int(green3);
      B = int(blue3);
      color = "";
      if((R>110)&(R<190)&(G>50)&(G<88)&(B>20)&(B<44)){
        color = "Orange";
        currentMillis3 = millis();
        check_sensor3 = false;
        mp3_play(5);
      } else if((R>30)&(R<50)&(G>99)&(G<130)&(B>70)&(B<107)){
        color = "Blue";
        currentMillis3 = millis();
        mp3_play(3);
        lcd.backlight();
        lcd.setCursor(0, 0);
        Score1 = Score1+1;
        lcd.print("Score = ");
        lcd.print(Score1);
        check_sensor3 = false;
      } else if((R>59)&(R<93)&(G>110)&(G<130)&(B>37)&(B<55)){
        color = "Green";
        currentMillis3 = millis();
        check_sensor3 = false;
        mp3_play(5);
      } else if((R>55)&(R<80)&(G>92)&(G<115)&(B>60)&(B<75)){
        color = "White";
        currentMillis3 = millis();
        check_sensor3 = false;
        mp3_play(5);
      } else if ((R-B>40)&(G-B>40)){
        color = "Yellow";
        currentMillis3 = millis(); 
        check_sensor3 = false;
        mp3_play(5);
      }

      Serial.print("Sensor 3 - R: "); Serial.print(int(red3));
      Serial.print(" G: "); Serial.print(int(green3));
      Serial.print(" B: "); Serial.print(int(blue3));
      Serial.print("   Color: ");Serial.print(color);
      Serial.println();
    }

    if (millis() - currentMillis3 > 1000) {
      check_sensor3 = true;
    }

    // Baca data dari sensor keempat, biru putih
    if (check_sensor4 == true) {
      tcaselect(3);
      float red4, green4, blue4;
      tcs4.getRGB(&red4, &green4, &blue4);
      R = int(red4);
      G = int(green4);
      B = int(blue4);
      color = "";
      if((R>110)&(R<190)&(G>50)&(G<88)&(B>20)&(B<44)){
        color = "Orange";
        currentMillis4 = millis();
        check_sensor4 = false;
        mp3_play(5);
      } else if((R>30)&(R<50)&(G>99)&(G<130)&(B>70)&(B<107)){
        color = "Blue";
        currentMillis4 = millis();
        mp3_play(3);
        lcd.backlight();
        lcd1.setCursor(0, 0);
        Score2 = Score2+1;
        lcd1.print("Score = ");
        lcd1.print(Score2);
        check_sensor3 = false;
      } else if((R>59)&(R<93)&(G>110)&(G<130)&(B>37)&(B<55)){
        color = "Green";
        currentMillis4 = millis();
        check_sensor4 = false;
        mp3_play(5);
      } else if((R>55)&(R<80)&(G>92)&(G<115)&(B>60)&(B<75)){
        color = "White";
        currentMillis4 = millis();
        mp3_play(3);
        lcd.backlight();
        lcd1.setCursor(0, 0);
        Score2 = Score2+1;
        lcd1.print("Score = ");
        lcd1.print(Score2);
        check_sensor4 = false;
      } else if ((R-B>40)&(G-B>40)){
        color = "Yellow";
        currentMillis4 = millis(); 
        check_sensor4 = false;
        mp3_play(5);
      }

      Serial.print("Sensor 4 - R: "); Serial.print(int(red4));
      Serial.print(" G: "); Serial.print(int(green4));
      Serial.print(" B: "); Serial.print(int(blue4));
      Serial.print("   Color: ");Serial.print(color);
      Serial.println();
    }

    if (millis() - currentMillis4 > 1000) {
      check_sensor4 = true;
    }

    // Baca data dari sensor kelima, orange kuning
    if (check_sensor5 == true) {
      tcaselect(4);
      float red5, green5, blue5;
      tcs5.getRGB(&red5, &green5, &blue5);
      R = int(red5);
      G = int(green5);
      B = int(blue5);
      color = "";
      if((R>110)&(R<190)&(G>50)&(G<88)&(B>20)&(B<44)){
        color = "Orange";
        currentMillis5 = millis(); 
        mp3_play(3);
        lcd.backlight();
        lcd1.setCursor(0, 0);
        Score2 = Score2+1;
        lcd1.print("Score = ");
        lcd1.print(Score2);
        check_sensor5 = false;
      } else if((R>30)&(R<50)&(G>99)&(G<130)&(B>70)&(B<107)){
        color = "Blue";
        currentMillis5 = millis();
        check_sensor5 = false;
        mp3_play(5);
      } else if((R>59)&(R<93)&(G>110)&(G<130)&(B>37)&(B<55)){
        color = "Green";
        currentMillis5 = millis();
        check_sensor5 = false;
        mp3_play(5);
      } else if((R>55)&(R<80)&(G>92)&(G<115)&(B>60)&(B<75)){
        color = "White";
        currentMillis5 = millis();
        check_sensor5 = false;
        mp3_play(5);
      } else if ((R-B>40)&(G-B>40)){
        color = "Yellow";
        currentMillis5 = millis(); 
        mp3_play(3);
        lcd.backlight();
        lcd1.setCursor(0, 0);
        Score2 = Score2+1;
        lcd1.print("Score = ");
        lcd1.print(Score2);
        check_sensor5 = false;
      }

      Serial.print("Sensor 5 - R: "); Serial.print(int(red5));
      Serial.print(" G: "); Serial.print(int(green5));
      Serial.print(" B: "); Serial.print(int(blue5));
      Serial.print("   Color: ");Serial.print(color);
      Serial.println();
    }

    if (millis() - currentMillis5 > 1000) {
      check_sensor5 = true;
    }

    // Baca data dari sensor keenam, hijau
    if (check_sensor6 == true) {
      tcaselect(5);
      float red6, green6, blue6;
      tcs6.getRGB(&red6, &green6, &blue6);
      R = int(red6);
      G = int(green6);
      B = int(blue6);
      color = "";
      if((R>110)&(R<190)&(G>50)&(G<88)&(B>20)&(B<44)){
        color = "Orange";
        currentMillis6 = millis();
        check_sensor6 = false;
        mp3_play(5);
      } else if((R>30)&(R<50)&(G>99)&(G<130)&(B>70)&(B<107)){
        color = "Blue";
        currentMillis6 = millis();
        check_sensor6 = false;
        mp3_play(5);
      } else if((R>59)&(R<93)&(G>110)&(G<130)&(B>37)&(B<55)){
        color = "Green";
        currentMillis6 = millis(); 
        mp3_play(3);
        lcd.backlight();
        lcd1.setCursor(0, 0);
        Score2 = Score2+1;
        lcd1.print("Score = ");
        lcd1.print(Score2);
        check_sensor6 = false;
      } else if((R>55)&(R<80)&(G>92)&(G<115)&(B>60)&(B<75)){
        color = "White";
        currentMillis6 = millis();
        check_sensor6 = false;
        mp3_play(5);
      } else if ((R-B>40)&(G-B>40)){
        color = "Yellow";
        currentMillis6 = millis(); 
        check_sensor6 = false;
        mp3_play(5);
      }

      Serial.print("Sensor 6 - R: "); Serial.print(int(red6));
      Serial.print(" G: "); Serial.print(int(green6));
      Serial.print(" B: "); Serial.print(int(blue6));
      Serial.print("   Color: ");Serial.print(color);
      Serial.println();
    }

    if (millis() - currentMillis6 > 1000) {
      check_sensor6 = true;
    }

    if (millis() - currentMillis_timer > 120000) {
        lcd.clear();
        lcd1.clear();
      if (Score1 > Score2) {
        lcd.setCursor(0,0);
        lcd.print("Congratulations");
        lcd.setCursor(0,1);
        lcd.print("You Win!!");
        lcd1.setCursor(0,0);
        lcd1.print("You Lose");
        lcd1.setCursor(0,1);
        lcd1.print("Keep Spirit!!");
        delay(5000);
      } else if (Score1 < Score2) {
        lcd1.setCursor(0,0);
        lcd1.print("Congratulations");
        lcd1.setCursor(0,1);
        lcd1.print("You Win!!");
        lcd.setCursor(0,0);
        lcd.print("You Lose");
        lcd.setCursor(0,1);
        lcd.print("Keep Spirit!!");
        delay(5000);
      } else if (Score1 == Score2) {
        lcd.setCursor(0,0);
        lcd.print("It's a draw!!");
        lcd1.setCursor(0,0);
        lcd1.print("It's a draw!!");
        delay(5000);
      }
      read_versus = true;
      read_solo1 = true;
      read_solo2 = true;
      check_button_versus = true;
      play_versus = false;
      mp3_play(1);
    }

  } 
  
  if (play_solo1 == true && start1 == true) {
    //timer game 
    if (millis() - currentMillis_timer < 120000) {
      lcd.setCursor(0, 0);
      lcd.print("Score = ");
      lcd.print(Score1);
      lcd.setCursor(0, 1);
      lcd.print("Waktu = ");
      lcd.print(((timer_solo1 - millis()))/1000);

      if ((timer_solo1 - millis())/1000 <= 99 && cek3 != 1) {
        lcd.clear();
        lcd1.clear();
        cek3 = cek3+1;
      }
      if ((timer_solo1 - millis())/1000 <= 9 && cek4 != 1) {
        lcd.clear();
        lcd1.clear();
        cek4 = cek4+1;
      }

      // Baca data dari sensor pertama
      if (check_sensor1 == true) {
        tcaselect(0);
        float red1, green1, blue1;
        tcs1.getRGB(&red1, &green1, &blue1);
        R = int(red1);
        G = int(green1);
        B = int(blue1);
        color = "";
        if((R>110)&(R<190)&(G>50)&(G<88)&(B>20)&(B<44)){
          color = "Orange";
          currentMillis1 = millis(); 
          mp3_play(3);
          lcd.backlight();
          lcd.setCursor(0, 0);
          Score1 = Score1+1;
          lcd.print("Score = ");
          lcd.print(Score1);
          check_sensor1 = false;
        } else if((R>30)&(R<50)&(G>99)&(G<130)&(B>70)&(B<107)){
          color = "Blue";
          currentMillis1 = millis();
          check_sensor1 = false;
          mp3_play(5);
        } else if((R>59)&(R<93)&(G>110)&(G<130)&(B>37)&(B<55)){
          color = "Green";
          currentMillis1 = millis();
          check_sensor1 = false;
          mp3_play(5);
        } else if((R>55)&(R<80)&(G>92)&(G<115)&(B>60)&(B<75)){
          color = "White";
          currentMillis1 = millis();
          check_sensor1 = false;
          mp3_play(5);
        } else if ((R-B>40)&(G-B>40)){
          color = "Yellow";
          currentMillis1 = millis(); 
          mp3_play(3);
          lcd.backlight();
          lcd.setCursor(0, 0);
          Score1 = Score1+1;
          lcd.print("Score = ");
          lcd.print(Score1);
          check_sensor1 = false;
        }
        Serial.print("Sensor 1 - R: "); Serial.print(int(red1));
        Serial.print(" G: "); Serial.print(int(green1));
        Serial.print(" B: "); Serial.print(int(blue1));
        Serial.print("   Color: ");Serial.print(color);
        Serial.println();
      }

      if (millis() - currentMillis1 > 1000) {
        check_sensor1 = true;
      }

      // Baca data dari sensor kedua, putih hijau
      if (check_sensor2 == true) {
        tcaselect(1);
        float red2, green2, blue2;
        tcs2.getRGB(&red2, &green2, &blue2);
        R = int(red2);
        G = int(green2);
        B = int(blue2);
        color = "";
        if((R>110)&(R<190)&(G>50)&(G<88)&(B>20)&(B<44)){
          color = "Orange";
          currentMillis2 = millis();
          check_sensor2 = false;
          mp3_play(5);
        } else if((R>30)&(R<50)&(G>99)&(G<130)&(B>70)&(B<107)){
          color = "Blue";
          currentMillis2 = millis();
          check_sensor2 = false;
          mp3_play(5);
        } else if((R>59)&(R<93)&(G>110)&(G<130)&(B>37)&(B<55)){
          color = "Green";
          currentMillis2 = millis(); 
          mp3_play(3);
          lcd.backlight();
          lcd.setCursor(0, 0);
          Score1 = Score1+1;
          lcd.print("Score = ");
          lcd.print(Score1);
          check_sensor2 = false;
        } else if((R>55)&(R<80)&(G>92)&(G<115)&(B>60)&(B<75)){
          color = "White";
          currentMillis2 = millis(); 
          mp3_play(3);
          lcd.backlight();
          lcd.setCursor(0, 0);
          Score1 = Score1+1;
          lcd.print("Score = ");
          lcd.print(Score1);
          check_sensor2 = false;
        } else if ((R-B>40)&(G-B>40)){
          color = "Yellow";
          currentMillis2 = millis(); 
          check_sensor2 = false;
          mp3_play(5);
        }

        Serial.print("Sensor 2 - R: "); Serial.print(int(red2));
        Serial.print(" G: "); Serial.print(int(green2));
        Serial.print(" B: "); Serial.print(int(blue2));
        Serial.print("   Color: ");Serial.print(color);
        Serial.println();
      }

      if (millis() - currentMillis2 > 1000) {
        check_sensor2 = true;
      }

      // Baca data dari sensor ketiga biru
      if (check_sensor3 == true) {
        tcaselect(2);
        float red3, green3, blue3;
        tcs3.getRGB(&red3, &green3, &blue3);
        R = int(red3);
        G = int(green3);
        B = int(blue3);
        color = "";
        if((R>110)&(R<190)&(G>50)&(G<88)&(B>20)&(B<44)){
          color = "Orange";
          currentMillis3 = millis();
          check_sensor3 = false;
          mp3_play(5);
        } else if((R>30)&(R<50)&(G>99)&(G<130)&(B>70)&(B<107)){
          color = "Blue";
          currentMillis3 = millis();
          mp3_play(3);
          lcd.backlight();
          lcd.setCursor(0, 0);
          Score1 = Score1+1;
          lcd.print("Score = ");
          lcd.print(Score1);
          check_sensor3 = false;
        } else if((R>59)&(R<93)&(G>110)&(G<130)&(B>37)&(B<55)){
          color = "Green";
          currentMillis3 = millis();
          check_sensor3 = false;
          mp3_play(5);
        } else if((R>55)&(R<80)&(G>92)&(G<115)&(B>60)&(B<75)){
          color = "White";
          currentMillis3 = millis();
          check_sensor3 = false;
          mp3_play(5);
        } else if ((R-B>40)&(G-B>40)){
          color = "Yellow";
          currentMillis3 = millis(); 
          check_sensor3 = false;
          mp3_play(5);
        }

        Serial.print("Sensor 3 - R: "); Serial.print(int(red3));
        Serial.print(" G: "); Serial.print(int(green3));
        Serial.print(" B: "); Serial.print(int(blue3));
        Serial.print("   Color: ");Serial.print(color);
        Serial.println();
      }

      if (millis() - currentMillis3 > 1000) {
        check_sensor3 = true;
      }

    } else if (millis() - currentMillis_timer > 120000 && millis() - currentMillis_timer < 120500) {
      lcd.clear();

    } else if (millis() - currentMillis_timer > 120000 && millis() - currentMillis_timer < 130000) {
      lcd.setCursor(0,0);
      lcd.print("Your Final Score");
      lcd.setCursor(7,1);
      lcd.print(Score1);

    } else if (millis() - currentMillis_timer > 130000) {
      start1 = false;
      read_solo1 = true;
      read_versus = true;
      check_button_solo1= true;
      play_solo1 = false;
      lcd.clear();
    }
  }

  if (play_solo2 == true && start2 == true) {
    if (millis() - currentMillis_timer1 < 120000) {
      //timer game
      lcd1.setCursor(0, 0);
      lcd1.print("Score = ");
      lcd1.print(Score2);
      lcd1.setCursor(0, 1);
      lcd1.print("Waktu = ");
      lcd1.print((timer_solo2 - millis())/1000);

      if ((timer_solo2 - millis())/1000 <= 99 && cek1 != 1) {
        lcd.clear();
        lcd1.clear();
        cek1 = cek1+1;
      }
      if ((timer_solo2 - millis())/1000 <= 9 && cek2 != 1) {
        lcd.clear();
        lcd1.clear();
        cek2 = cek2+1;
      }

      // Baca data dari sensor keempat, biru putih
      if (check_sensor4 == true) {
        tcaselect(3);
        float red4, green4, blue4;
        tcs4.getRGB(&red4, &green4, &blue4);
        R = int(red4);
        G = int(green4);
        B = int(blue4);
        color = "";
        if((R>110)&(R<190)&(G>50)&(G<88)&(B>20)&(B<44)){
          color = "Orange";
          currentMillis4 = millis();
          check_sensor4 = false;
          mp3_play(5);
        } else if((R>30)&(R<50)&(G>99)&(G<130)&(B>70)&(B<107)){
          color = "Blue";
          currentMillis4 = millis();
          mp3_play(3);
          lcd.backlight();
          lcd1.setCursor(0, 0);
          Score2 = Score2+1;
          lcd1.print("Score = ");
          lcd1.print(Score2);
          check_sensor3 = false;
        } else if((R>59)&(R<93)&(G>110)&(G<130)&(B>37)&(B<55)){
          color = "Green";
          currentMillis4 = millis();
          check_sensor4 = false;
          mp3_play(5);
        } else if((R>55)&(R<80)&(G>92)&(G<115)&(B>60)&(B<75)){
          color = "White";
          currentMillis4 = millis();
          mp3_play(3);
          lcd.backlight();
          lcd1.setCursor(0, 0);
          Score2 = Score2+1;
          lcd1.print("Score = ");
          lcd1.print(Score2);
          check_sensor4 = false;
        } else if ((R-B>40)&(G-B>40)){
          color = "Yellow";
          currentMillis4 = millis(); 
          check_sensor4 = false;
          mp3_play(5);
        }

        Serial.print("Sensor 4 - R: "); Serial.print(int(red4));
        Serial.print(" G: "); Serial.print(int(green4));
        Serial.print(" B: "); Serial.print(int(blue4));
        Serial.print("   Color: ");Serial.print(color);
        Serial.println();
      }

      if (millis() - currentMillis4 > 1000) {
        check_sensor4 = true;
      }

      // Baca data dari sensor kelima, orange kuning
      if (check_sensor5 == true) {
        tcaselect(4);
        float red5, green5, blue5;
        tcs5.getRGB(&red5, &green5, &blue5);
        R = int(red5);
        G = int(green5);
        B = int(blue5);
        color = "";
        if((R>110)&(R<190)&(G>50)&(G<88)&(B>20)&(B<44)){
          color = "Orange";
          currentMillis5 = millis(); 
          mp3_play(3);
          lcd.backlight();
          lcd1.setCursor(0, 0);
          Score2 = Score2+1;
          lcd1.print("Score = ");
          lcd1.print(Score2);
          check_sensor5 = false;
        } else if((R>30)&(R<50)&(G>99)&(G<130)&(B>70)&(B<107)){
          color = "Blue";
          currentMillis5 = millis();
          check_sensor5 = false;
          mp3_play(5);
        } else if((R>59)&(R<93)&(G>110)&(G<130)&(B>37)&(B<55)){
          color = "Green";
          currentMillis5 = millis();
          check_sensor5 = false;
          mp3_play(5);
        } else if((R>55)&(R<80)&(G>92)&(G<115)&(B>60)&(B<75)){
          color = "White";
          currentMillis5 = millis();
          check_sensor5 = false;
          mp3_play(5);
        } else if ((R-B>40)&(G-B>40)){
          color = "Yellow";
          currentMillis5 = millis(); 
          mp3_play(3);
          lcd.backlight();
          lcd1.setCursor(0, 0);
          Score2 = Score2+1;
          lcd1.print("Score = ");
          lcd1.print(Score2);
          check_sensor5 = false;
        }

        Serial.print("Sensor 5 - R: "); Serial.print(int(red5));
        Serial.print(" G: "); Serial.print(int(green5));
        Serial.print(" B: "); Serial.print(int(blue5));
        Serial.print("   Color: ");Serial.print(color);
        Serial.println();
      }

      if (millis() - currentMillis5 > 1000) {
        check_sensor5 = true;
      }

      // Baca data dari sensor keenam, hijau
      if (check_sensor6 == true) {
        tcaselect(5);
        float red6, green6, blue6;
        tcs6.getRGB(&red6, &green6, &blue6);
        R = int(red6);
        G = int(green6);
        B = int(blue6);
        color = "";
        if((R>110)&(R<190)&(G>50)&(G<88)&(B>20)&(B<44)){
          color = "Orange";
          currentMillis6 = millis();
          check_sensor6 = false;
          mp3_play(5);
        } else if((R>30)&(R<50)&(G>99)&(G<130)&(B>70)&(B<107)){
          color = "Blue";
          currentMillis6 = millis();
          check_sensor6 = false;
          mp3_play(5);
        } else if((R>59)&(R<93)&(G>110)&(G<130)&(B>37)&(B<55)){
          color = "Green";
          currentMillis6 = millis(); 
          mp3_play(3);
          lcd.backlight();
          lcd1.setCursor(0, 0);
          Score2 = Score2+1;
          lcd1.print("Score = ");
          lcd1.print(Score2);
          check_sensor6 = false;
        } else if((R>55)&(R<80)&(G>92)&(G<115)&(B>60)&(B<75)){
          color = "White";
          currentMillis6 = millis();
          check_sensor6 = false;
          mp3_play(5);
        } else if ((R-B>40)&(G-B>40)){
          color = "Yellow";
          currentMillis6 = millis(); 
          check_sensor6 = false;
          mp3_play(5);
        }

        Serial.print("Sensor 6 - R: "); Serial.print(int(red6));
        Serial.print(" G: "); Serial.print(int(green6));
        Serial.print(" B: "); Serial.print(int(blue6));
        Serial.print("   Color: ");Serial.print(color);
        Serial.println();
      }

      if (millis() - currentMillis6 > 1000) {
        check_sensor6 = true;
      }

    } else if (millis() - currentMillis_timer1 > 120000 && millis() - currentMillis_timer1 < 120500) {
      lcd1.clear();

    } else if (millis() - currentMillis_timer1 > 120000 && millis() - currentMillis_timer1 < 130000) {
      lcd1.setCursor(0,0);
      lcd1.print("Your Final Score");
      lcd1.setCursor(7,1);
      lcd1.print(Score2);

    } else if (millis() - currentMillis_timer1 > 130000) {
      lcd1.clear();
      start2 = false;
      read_solo2 = true;
      read_versus = true;
      check_button_solo2= true;
      play_solo2 = false;
    }
  }
}

