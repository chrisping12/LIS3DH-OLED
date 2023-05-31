// display.display() is NOT necessary after every single drawing command,
// unless thats what you want. rather, you can batch up a bunch of
// drawing operations and then update the screen all at once by calling
// display.display(). 

#include <Arduino.h>
#include <Adafruit_SH110X.h>
#include <Adafruit_GFX.h>
#include <WIRE.h>
#include <adafruit_LIS3DH.h>
#include <adafruit_sensor.h>

#define BUTTON_A  9
#define BUTTON_B  6
#define BUTTON_C  5
#define SCREEN_WIDTH 64 //
#define SCREEN_HEIGHT 128 //

Adafruit_SH1107 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

Adafruit_LIS3DH lis = Adafruit_LIS3DH();

void setup() {

    Serial.begin(115200);
    delay(250); // wait for the OLED to power up
    display.begin(0x3C, true);  // Address 0x3C for 128x64

    Serial.println("OLED begun");

    // Show image buffer on the display hardware.
    // Since the buffer is intialized with an Adafruit splashscreen
    // internally, this will display the splashscreen.
    display.display();
    delay(1000);

    // Clear the buffer.
    display.clearDisplay();
    display.display();

    pinMode(BUTTON_A, INPUT_PULLUP);
    pinMode(BUTTON_B, INPUT_PULLUP);
    pinMode(BUTTON_C, INPUT_PULLUP);



// Begin LIS3DH start up sequence.

  Serial.println("LIS3DH test!");
  if (! lis.begin(0x18)) 
  {    Serial.println("Couldnt start LIS3DH");
    while (1) yield(); }

  Serial.println("LIS3DH found!");

  {
  Serial.print("Range = "); Serial.print(4 << lis.getRange());  // lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!
  Serial.println("G");
  Serial.print("Data rate set to: ");
  switch (lis.getDataRate()) {  // lis.setDataRate(LIS3DH_DATARATE_50_HZ);
    case LIS3DH_DATARATE_1_HZ: Serial.println("1 Hz"); break;
    case LIS3DH_DATARATE_10_HZ: Serial.println("10 Hz"); break;
    case LIS3DH_DATARATE_25_HZ: Serial.println("25 Hz"); break;
    case LIS3DH_DATARATE_50_HZ: Serial.println("50 Hz"); break;
    case LIS3DH_DATARATE_100_HZ: Serial.println("100 Hz"); break;
    case LIS3DH_DATARATE_200_HZ: Serial.println("200 Hz"); break;
    case LIS3DH_DATARATE_400_HZ: Serial.println("400 Hz"); break;

    case LIS3DH_DATARATE_POWERDOWN: Serial.println("Powered Down"); break;
    case LIS3DH_DATARATE_LOWPOWER_5KHZ: Serial.println("5 Khz Low Power"); break;
    case LIS3DH_DATARATE_LOWPOWER_1K6HZ: Serial.println("16 Khz Low Power"); break;
    display.display();
    delay(3500);
    }
  }


 {
// define header info for constant display.
    display.setRotation(1);
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(13,2);
    display.print("Accelerometer Data");
    display.drawFastHLine(12,11,103,1);

//Display * X:______ m/x2
    display.setCursor(0,18); display.print(" \tX-Axis ="); display.setCursor(95,18); display.println("m/s");
    display.drawPixel(113,17,1); display.drawPixel(114,17,1); 
    display.drawPixel(115,18,1); display.drawPixel(114,19,1); 
    display.drawPixel(113,20,1); 
    display.drawFastHLine(113,21,3,1);
//Display * Y:______ m/x2
    display.setCursor(0,35); display.print(" \tY-Axis ="); display.setCursor(95,35); display.println("m/s");
    display.drawPixel(113,34,1); display.drawPixel(114,34,1); 
    display.drawPixel(115,35,1); display.drawPixel(114,36,1); 
    display.drawPixel(113,37,1); 
    display.drawFastHLine(113,38,3,1);
//Display * Z:______ m/x2
    display.setCursor(0,52); display.print(" \tZ-Axis ="); display.setCursor(95,52); display.println("m/s");
    display.drawPixel(113,51,1); display.drawPixel(114,51,1); 
    display.drawPixel(115,52,1); display.drawPixel(114,53,1); 
    display.drawPixel(113,54,1); 
    display.drawFastHLine(113,55,3,1);

display.display();
 }
}


void loop() {  // put your main code here, to run repeatedly:
  
/* Get a new sensor event */ //From Sensors.h library.
  sensors_event_t event; 
  lis.getEvent(&event);

/* Display the results (acceleration is measured in m/s^2) */
    display.setCursor(63,18);
    display.println(event.acceleration.x,1);
    display.setCursor(63,35);
    display.println(event.acceleration.y,1);
    display.setCursor(63,52);
    display.println(event.acceleration.z,1);

display.display();  // actually display all of the above

delay(250);
      display.drawFastHLine(62,18,30,0); display.drawFastHLine(62,19,30,0); display.drawFastHLine(62,20,30,0);
      display.drawFastHLine(62,21,30,0); display.drawFastHLine(62,22,30,0); display.drawFastHLine(62,23,30,0); display.drawFastHLine(62,24,30,0);
      display.drawFastHLine(62,35,30,0); display.drawFastHLine(62,36,30,0); display.drawFastHLine(62,37,30,0);
      display.drawFastHLine(62,38,30,0); display.drawFastHLine(62,39,30,0); display.drawFastHLine(62,40,30,0); display.drawFastHLine(62,41,30,0);
      display.drawFastHLine(62,52,30,0); display.drawFastHLine(62,53,30,0); display.drawFastHLine(62,54,30,0);
      display.drawFastHLine(62,55,30,0); display.drawFastHLine(62,56,30,0); display.drawFastHLine(62,57,30,0); display.drawFastHLine(62,58,30,0);
display.display();

// Talkin bout the PING buttons
if(!digitalRead(BUTTON_A)){
    display.clearDisplay();
// Draw out The P in PING
    display.fillRect(9,2,31,30,1); display.fillRect(15,8,19,6,0); display.fillRect(15,20,25,12,0); display.drawFastVLine(9,2,3,0); display.writePixel(10,2,0); 
    display.writePixel(9,30,0); display.writePixel(14,30,0); display.drawFastHLine(9,31,2,0); display.drawFastHLine(13,31,2,0);  
    display.fillRect(38,2,2,4,0); display.fillRect(38,16,2,4,0); display.drawFastHLine(35,2,3,0); display.drawFastHLine(35,19,3,0); 
    display.writePixel(37,3,0); display.writePixel(39,6,0); display.writePixel(39,15,0); display.writePixel(37,18,0); 
// Draw out the I in PING
    display.fillRect(44,2,6,30,1); display.drawFastHLine(44,2,2,0); display.writePixel(44,3,0); display.drawFastHLine(48,2,2,0); display.writePixel(49,3,0);
    display.drawFastHLine(44,31,2,0); display.drawFastHLine(48,31,2,0); display.writePixel(44,30,0); display.writePixel(49,30,0);  
// Draw out the N in PING
    display.fillRect(54,2,6,30,1); display.fillRect(60,2,18,30,1); display.fillRect(78,2,6,30,1); display.drawFastHLine(54,2,2,0); display.writePixel(54,3,0); 
    display.drawFastHLine(54,31,2,0); display.writePixel(54,30,0); display.drawFastHLine(58,31,2,0); display.writePixel(59,30,0); 
    display.fillTriangle(60,31,60,13,78,31,0); display.fillTriangle(59,2,77,2,77,20,0);
    display.drawFastHLine(78,2,2,0); display.drawFastHLine(82,2,2,0); display.drawFastHLine(82,31,2,0);  
    display.writePixel(78,3,0); display.writePixel(83,3,0); display.writePixel(783,30,0); 
void fillTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
// Draw out the G in PING
    display.fillRect(88,2,31,30,1); display.fillRect(94,8,25,6,0); display.fillRect(94,14,3,6,0); display.fillRect(94,20,19,6,0);
    display.drawFastHLine(88,2,3,0); display.drawFastHLine(88,31,3,0); display.drawFastHLine(97,14,2,0); display.drawFastHLine(97,19,2,0);
    display.drawFastHLine(117,2,2,0); display.drawFastHLine(177,7,2,0); display.drawFastHLine(115,14,4,0); display.drawFastHLine(115,14,4,0);
    display.drawFastHLine(115,31,4,0); display.drawFastHLine(117,15,2,0); display.drawFastHLine(117,30,2,0); display.drawFastVLine(118,16,2,0);
    display.drawFastVLine(118,28,2,0); display.writePixel(88,3,0); display.writePixel(88,30,0); display.writePixel(97,15,0); display.writePixel(97,18,0); 
    display.writePixel(118,3,0); display.writePixel(118,6,0); display.writePixel(118,3,0); 
// Draw Line
    display.fillRoundRect(6,36,116,4,1,1);
// Display ALLL
    display.display();
// Leave Beautiful Artwork on screen for a bit
    delay(8000);
    display.clearDisplay();
}
  display.display();
}
