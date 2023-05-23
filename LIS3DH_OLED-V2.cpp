


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

    display.setRotation(1);
    // define text info for display.
    display.setTextSize(2);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0,0);
    delay(500);

  // Begin LIS3DH start up sequence.

  Serial.println("LIS3DH test!");
  if (! lis.begin(0x18)) 
  {   
    Serial.println("Couldnt start LIS3DH");
    while (1) yield();
  }
  Serial.println("LIS3DH found!");

  {
  Serial.print("Range = "); Serial.print(2 << lis.getRange());  // lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!
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
  display.clearDisplay();
  delay(500);
}


void loop() {  // put your main code here, to run repeatedly:
    
    /* Get a new sensor event */ 

    sensors_event_t event; 
    lis.getEvent(&event);
  
    /* Display the results (acceleration is measured in m/s^2) */
    display.print(" \tX: "); display.println(event.acceleration.x);
    display.print(" \tY: "); display.println(event.acceleration.y);
    display.print(" \tZ: "); display.println(event.acceleration.z);
    display.println(" m/s^2 ");
    display.display();  // actually display all of the above
  delay(1000);
  
}