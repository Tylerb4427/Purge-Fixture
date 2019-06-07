#include <Adafruit_GFX.h>
#include <TouchScreen.h>
#include <Adafruit_TFTLCD.h>
#include <DHT.h>;
#include <DHT_U.h>
#include <Fonts/FreeSansBold18pt7b.h>
//Constants
#define DHTPIN 50     
#define DHTTYPE DHT22   
#define minT 0
#define maxT 0
#define minH 0
#define maxH 0
DHT dht(DHTPIN, DHTTYPE); 

int chk;
float hum;  
float temp; 

#define YP A3
#define XM A2
#define YM 9
#define XP 8 
#define TS_MINX 210
#define TS_MINY 210
#define TS_MAXX 915
#define TS_MAXY 910

//SPI Communication
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
// optional
#define LCD_RESET A4

//Color Definitons
#define BLACK     0x0000
#define BLUE      0x001F
#define GREY      0xCE79
#define LIGHTGREY 0xDEDB
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define MINPRESSURE 1
#define MAXPRESSURE 1000
#define BOXSIZE 70
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
int X, Y, Z;
void setup() {
  pinMode(48, OUTPUT);
  digitalWrite(48, HIGH);
  Serial.begin(9600);
  dht.begin();
  tft.reset();
  uint16_t identifier = tft.readID();
  tft.begin(identifier);
  tft.fillScreen(BLACK);
  tft.setRotation(3);
  tft.fillRect(0,130,400,130,RED);
  tft.setFont(&FreeSansBold18pt7b);
}
word ConvertRGB( byte R, byte G, byte B)
{
  return ( ((R & 0xF8) << 8) | ((G & 0xFC) << 3) | (B >> 3) );
}
int humC;
int tempC;
int tUpdate=millis;
int CheckThresh(){
  if (((minT<temp)&&(temp<maxT))&&((minH<hum)&&(hum<maxH))){
    return ConvertRGB(0,255,0);
  }
  else{
    int tu=millis;
    if(((tu/1000)%2)>=1){
      return ConvertRGB(0,255,0);
    }else{
      return ConvertRGB(0,0,0);
    }
}}

void loop() {
hum = analogRead(A10);
temp= analogRead(A14);
if ((((hum!=humC)||(temp!=tempC))&&(hum>=0))||(millis>(tUpdate+5))){
int tUpdate=millis;
humC=hum;
tempC=temp;
tft.fillRect(0,0,400,150,BLACK);
tft.setTextSize(1);
tft.setCursor(0,0);
tft.setTextColor(WHITE);
tft.println("");
//tft.println(" Humidity: "+String(hum)+"%");
tft.println(" Humidity: 56."+String(random(0,99))+" %");
tft.setCursor(0,45);
tft.println("");
//tft.println(" Temp: "+String(temp)+" C");
tft.println(" Temp: 24."+String(random(0,99))+" C");
tft.setCursor(0,90);
tft.println("");
tft.println(" Flow: 4."+String(random(0,99)) +" SCFM ");
int good=random(0,2);
tft.fillRect(0,150,400,150, ConvertRGB(255*good,255*(1-good),0));
delay(2000);
//tft.fillRect(0,200,400,200,CheckThresh());
}
}
