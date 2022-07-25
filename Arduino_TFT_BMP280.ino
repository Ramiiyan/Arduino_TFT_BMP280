/* Adafruit library For TFT */
#include <Adafruit_ST7735.h> 
#include <SPI.h>

#include <stdio.h>

/* Adafruit library examples for BME280 sensor */
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>


#define TFT_CS    10
#define TFT_RST   8  
#define TFT_DC    9 

#define TFT_SCLK 13   
#define TFT_MOSI 11   

#if defined(__SAM3X8E__)

#undef __FlashStringHelper::F(string_literal)

#define F(string_literal) string_literal

#endif

//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

//Black theme

#define COLOR1 ST7735_WHITE
#define COLOR2 ST7735_BLACK

//White theme

//#define COLOR1 ST7735_BLACK
//#define COLOR2 ST7735_WHITE

Adafruit_BME280 bme;

int text_color_humidex;

float humidity, temperature, pressure;

String message;

void setup() {

  Serial.begin(9600);
  
  /* assuming I2C address set is 0x76. If you are using 0x77, update 0x77 as the I2C address  */
  if (!bme.begin(0x76)) {
    Serial.println("No BME280 device found!");
    while (1);
  }
  
  tft.initR(INITR_BLACKTAB);  
  tft.fillScreen(COLOR2); 
 
//  tft.setTextColor(ST7735_WHITE);
//  tft.setTextSize(0);
//  tft.setCursor(30,80);
//  tft.println("Hello World!");  
//  delay(1000);
  
}

void testdrawtext(char* text, uint16_t color)
{
    tft.setCursor(0, 0);
    tft.setTextColor(color);
    tft.setTextWrap(true);
    tft.print(text);
}

void loop() {
  humidity = bme.readHumidity();
  temperature = bme.readTemperature();
  pressure = bme.readPressure()/100.0F;

//  Serial.println("Altitude in m = ");
//  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
//  tft.fillScreen(ST7735_WHITE); 
//  delay(1000);
//  tft.setTextColor(ST7735_BLACK);
//  tft.setTextSize(0);
//  tft.setCursor(40,80);
//  tft.println("Hey Levi!");
//  tft.setCursor(15,100);
//  tft.println("The Wonder Girl ;)");

  // Table
  tft.drawRect(0, 0, 128, 160, COLOR1);
  tft.drawLine(0, 50, 128, 50, COLOR1);
  tft.drawLine(0, 100, 128, 100, COLOR1);

  // data is outputed
  temperature_to_lcd(temperature, 4);
  humidity_to_lcd(humidity, 55);
  pressure_to_lcd(pressure, 105);  

  delay(10000);
}

// outputs temperature to LCD
void temperature_to_lcd(float temperature, unsigned char text_position){
    int text_color;
    tft.setCursor(4, text_position);
    tft.setTextColor(COLOR1, COLOR2);
    tft.setTextSize(1);

    tft.print("Temperature:");
    tft.setTextSize(3);
    if (temperature < 35)
    {
        text_color = ST7735_BLUE;
    }
    else
    {
        text_color = ST7735_RED;
    }

    tft.setCursor(1, text_position + 20);
    fix_number_position(temperature);
    tft.setTextColor(text_color, COLOR2);
    tft.print(temperature, 1);
    tft.setCursor(108, text_position + 20);
    tft.print("C");
    tft.drawChar(90, text_position + 20, 247, text_color, COLOR2, 2); //degree symbol

}

//outputs humidity to LCD
void humidity_to_lcd(float humidity, unsigned char text_position){
    tft.setTextColor(COLOR1, COLOR2);
    tft.setCursor(4, text_position);
    tft.setTextSize(1);
    tft.println("Humidity:");
    tft.setTextSize(3);
    tft.setCursor(1, text_position + 20);
    fix_number_position(humidity);
    tft.print(humidity, 1);
    tft.print(" %");
}

//outputs Pressure to LCD

void pressure_to_lcd(float pressure, unsigned char text_position){
  
    tft.setCursor(4, text_position);
    tft.setTextSize(1);
    tft.println("Pressure [Feel Like]:");
    tft.setTextSize(3);

    tft.setCursor(1, text_position + 17);
    fix_number_position(pressure);
    tft.print(pressure, 1);
    tft.print(" Pa");
}
void fix_number_position(float number){
    
    if ((number >= -40) && (number < -9.9))
    {
        ;
    }

    if ((number >= -9.9) && (number < 0.0))
    {
        tft.print(" ");
    }

    if ((number >= 0.0) && (number < 9.9))
    {
        tft.print(" ");
    }

    if ((number >= 9.9) && (number < 99.9))
    {
        tft.print(" ");
    }

    if ((number >= 99.9) && (number < 151))
    {
        tft.print("");
    }
}
