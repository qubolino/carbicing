
#include <Arduino.h>

//------------------
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 25     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

//-------------------
#include <MAX31855.h>

#define MAXDO     19 // Defining the MISO pin
#define MAXCS     26 // Defining the CS pin
#define MAXCLK    18 // Defining the SCK pin
MAX31855 thermocouple1;
MAX31855 thermocouple2;


//--------------------
#include <WiFi.h>


float oat_temp;
float oat_humid;
float airbox_temp;
float carby_temp;


//-----------------------
int data[50][60]={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,1,1,1,1,1,1,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,1,1,1,1,1,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,1,1,1,1,1,1,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,2,2,2,2,2,2,2,1,1,1,1,1,1,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,2,2,2,2,2,2,2,1,1,1,1,1,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,2,2,2,2,2,2,2,1,1,1,1,1,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,2,2,2,2,2,2,1,1,1,1,1,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,2,2,2,2,2,2,1,1,1,1,1,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,2,2,2,2,2,2,1,1,1,1,1,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,1,1,1,1,1,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,1,1,1,1,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,1,1,1,1,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,1,1,1,1,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,3,3,3,3,3,3,3,3,3,2,2,2,2,2,1,1,1,1,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,3,3,3,3,3,3,3,3,2,2,2,2,2,1,1,1,1,1,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,3,3,3,3,3,3,3,2,2,2,2,2,2,1,1,1,1,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,3,3,3,3,3,3,3,3,2,2,2,2,2,1,1,1,1,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,3,3,3,3,3,3,3,2,2,2,2,2,1,1,1,1,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,3,3,3,3,3,3,2,2,2,2,2,1,1,1,1,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,3,3,3,3,3,2,2,2,2,2,2,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,3,3,3,3,3,2,2,2,2,2,2,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,3,3,3,3,3,2,2,2,2,2,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,3,3,3,3,3,2,2,2,2,2,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,3,3,3,3,2,2,2,2,2,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,3,3,3,2,2,2,2,2,2,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,3,3,3,2,2,2,2,2,2,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,3,3,3,3,2,2,2,2,2,2,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,2,2,2,2,2,2,2,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
// def risk(oat, dew):
//     return data[oat+20, 50-dew-20]

float dew_point(float temp, float humid){
  return temp - ((100 - humid)/5.);
}


int icing_risk(int oat, int dew){
  if (oat > -21 && oat < 40 && dew > -21 && dew < 30){
    return data[50-dew-20][oat+20];
  }

  return 0;
}

// Variables: D=(density altitude) P=(pressure altitude)
// T=(temperature in degrees celsius)
// D = (145426 * (1- ((( 288.16 - P * .001981) /288.16)^5.2563 / ((273.16 + T) / 288.16))^0.235))

// APPROXIMATIONS:
// For fixed pitch prop, increase sea level standard day takeoff distance 15% 
// for each 1000 foot increase in density altitude. Approximation good to 8000 
// feet density altitude
// For constant speed prop, replace 15% with 13% in the above equation
// For fixed pitch prop, decrease sea level standard day climb rate 7.5% for 
// each 1000 foot increase in density altitude.
// For constant speed prop, replace 7.5% with 7% in the above equation.
// (Equations and approximations from "Axioms of Flight", James Embree, Flight 
// Information Publications, St. Louis MO, 1984. ISBN 0-9601062-7-8)
// Density altitude equation not independently verified. Use and report 
// results please.

#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif


// ESP32 C3 CORE LUATOS : 1.3" OLED IIC V2.0. SSD1309 (not SSD1306 or SH1106), only SSD1309 and  NONAME2   !!!
// U8G2_SSD1309_128X64_NONAME2_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); 


U8G2_ST7567_ENH_DG128064I_F_HW_I2C u8g2(U8G2_R2);


void display_temps(float oat_temp, float oat_humid, float airbox_temp, float carby_temp){

  char buffer[10];
  float dew = dew_point(oat_temp, oat_humid);
  int risk = icing_risk(int(oat_temp), int(dew));

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_unifont_t_weather);
    u8g2.drawGlyph(-4, 16, 0x31);	  // temp
    u8g2.setFont(u8g2_font_9x15_t_symbols);
    u8g2.drawGlyph(8, 15, 0x2103);	  // Celsius

    // u8g2.setCursor(15, 15);
    // u8g2.print(F("+20"));
    sprintf(buffer, "%+3.0f", oat_temp);
    u8g2.drawStr( 18, 15, buffer);


    u8g2.drawGlyph(45, 15, 0x21d2);  // => arrow
    // u8g2.setCursor(55, 15);
    // u8g2.print(F("+24"));
    sprintf(buffer, "%+3.0f", airbox_temp);
    u8g2.drawStr( 55, 15, buffer);

    u8g2.drawGlyph(85, 15, 0x21a3);  // >-> arrow
    // u8g2.setCursor(95, 15); 
    // u8g2.print(F("-12"));
    sprintf(buffer, "%+3.0f", carby_temp);
    u8g2.drawStr( 95, 15, buffer);




    u8g2.setFont(u8g2_font_unifont_t_weather);
    u8g2.drawGlyph(0, 40, 0x32);	  // drop
    u8g2.setFont(u8g2_font_9x15_t_symbols);
    // u8g2.setCursor(18, 39);
    // u8g2.print(F(" 60%"));
    sprintf(buffer, "%3.0f%%", oat_humid);
    u8g2.drawStr( 18, 39, buffer);

    // u8g2.setFont(u8g2_font_unifont_t_77);  // rain
    // u8g2.drawGlyph(100, 16, 0x26c6);	


    u8g2.setFont(u8g2_font_unifont_t_78_79);
    for (int i=0; i< risk; i++){
      u8g2.drawGlyph(64+i*16, 40, 0x274a);	// snowflake
    }


    u8g2.setFont(u8g2_font_unifont_t_weather);
    u8g2.drawGlyph(0, 60, 0x3b);	  // fog
    u8g2.setFont(u8g2_font_9x15_t_symbols);
    // u8g2.setCursor(18, 59);
    // u8g2.print(F("+12"));
    sprintf(buffer, "%+3.0f", dew);
    u8g2.drawStr( 18, 59, buffer);
    u8g2.drawGlyph(45, 59, 0x2103);	  // Celsius


    u8g2.setFont(u8g2_font_unifont_t_78_79);
    u8g2.drawGlyph(75, 61, 0x2708);  // plane

    // u8g2.setFont(u8g2_font_9x15_t_symbols);
    // u8g2.drawGlyph(90, 61, 0x00d7); // x
    // u8g2.setCursor(100, 61);
    // u8g2.print(F("1.3"));

  } while ( u8g2.nextPage() );


}

void setup(void) {

  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);
  btStop();
  // setCpuFrequencyMhz(40);

  Serial.begin(115200);

  dht.begin();

  thermocouple1.begin(MAXCLK, MAXCS, MAXDO);
  thermocouple2.begin(MAXCLK, MAXCS+1, MAXDO);

  //u8g2.setBusClock( 1000000); // I2C default =  400000
  //u8g2.setBusClock(80000000); // SPI default = 4000000
  u8g2.setI2CAddress(0x3F * 2);
  u8g2.begin();
  u8g2.setContrast(254);

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB14_tr);
    u8g2.setCursor(15, 35);
    u8g2.print(F("Welcome!"));
  } while ( u8g2.nextPage() );
  delay(1000);
}


void loop(void) {
  {

    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    oat_humid = dht.readHumidity();
    // Read temperature as Celsius (the default)
    oat_temp = dht.readTemperature();

    // Check if any reads failed and exit early (to try again).
    if (isnan(oat_humid) || isnan(oat_temp)) {
      Serial.println(F("Failed to read from DHT sensor!"));
    }

    Serial.print("OAT: ");
    Serial.print(oat_temp);
    Serial.print(F("°C "));
    Serial.print(F("RH: "));
    Serial.print(oat_humid);
    Serial.print(F("% "));
    Serial.print(F("Dew:"));
    Serial.print(dew_point(oat_temp, oat_humid));
    Serial.print(F("°C "));
    Serial.print(F("IcingRisk:"));
    Serial.print(icing_risk(int(oat_temp), int(dew_point(oat_temp, oat_humid))));
    Serial.println();
  }

  {
    int status = thermocouple1.read();
    if (status==STATUS_OK){
      airbox_temp = thermocouple1.getTemperature();
    } else {
      airbox_temp = sqrt (-1); //NaN
    }

    Serial.print("Thermocouple1 ");
    Serial.print("\tstatus: ");
    Serial.print(status!=STATUS_OK);
    Serial.print("\ttemp: ");
    Serial.print(airbox_temp);
    Serial.println();
  }

  {
    int status = thermocouple2.read();
    if (status==STATUS_OK){
      carby_temp = thermocouple2.getTemperature();
    } else {
      carby_temp = sqrt (-1); //NaN
    }

    Serial.print("Thermocouple2 ");
    Serial.print("\tstatus: ");
    Serial.print(status!=STATUS_OK);
    Serial.print("\ttemp: ");
    Serial.print(carby_temp);
    Serial.println();
  }


  display_temps(oat_temp, oat_humid, airbox_temp, carby_temp);
  delay(500);

}