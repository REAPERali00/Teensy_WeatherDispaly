#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <SPI.h>
#include <TimeLib.h>

// ILI9341 Pins
#define TFT_CS    10
#define TFT_RST   8
#define TFT_DC    9

// Create the ILI9341 display object
Adafruit_ILI9341 display = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

// Colors for better layout visibility
#define BACKGROUND_COLOR ILI9341_BLACK
#define TEXT_COLOR ILI9341_WHITE
#define ICON_COLOR ILI9341_CYAN

enum Weather{ 
  SUN, 
  RAIN, 
  STORM, 
  CLOUD,
};

void setup() {
  display.begin();
  display.fillScreen(BACKGROUND_COLOR);
  drawStaticUI();
}

void loop() {
  // put your main code here, to run repeatedly:

  drawDynamicUI();
  delay(1000);
}

void drawStaticUI(){
  display.setRotation(0);
  printText("20 C", 40, 20);
  weather_icon(SUN, 200,30);
  //process("CPU", 50,150,10);
  //process("GPU", 125,150,70);
  //process("MEM", 200,150,90);
}

void drawDynamicUI(){
  int cpuPercentage = random(0, 101);  // Random value between 0 and 100
  int gpuPercentage = random(0, 101);
  int memPercentage = random(0, 101);
  timer("59:00", 50,250,5);
  process("CPU", 50,150,cpuPercentage);
  process("GPU", 125,150,gpuPercentage);
  process("MEM", 200,150,memPercentage);
} 

void printText(String txt, int x, int y){
  display.setTextColor(TEXT_COLOR);
  display.setTextSize(3);
  display.setCursor(x,y);
  display.print(txt);
}

void weather_icon(Weather wttr, int x, int y){ 
  switch(wttr){ 
    case SUN: 
      drawSun(x,y,10,10,ICON_COLOR);
    break; 

    case RAIN: 
      drawRain(x,y,10,ICON_COLOR,ICON_COLOR);
    break; 

    case STORM: 
      drawStorm(x,y,10,ICON_COLOR,ICON_COLOR);
    break; 

    case CLOUD: 
      drawCloud(x, y, 20, ICON_COLOR);         // Draw cloud at position (100, 50)
    break; 
  } 
}

void drawSun(int x, int y, int radius, int rayLength, uint16_t color) {
  // Draw the central sun circle
  display.fillCircle(x, y, radius, color);

  // Draw the rays around the sun
  for (int angle = 0; angle < 360; angle += 45) {
    int xStart = x + cos(radians(angle)) * (radius + 2);  // Start of the ray
    int yStart = y + sin(radians(angle)) * (radius + 2);
    int xEnd = x + cos(radians(angle)) * (radius + rayLength);  // End of the ray
    int yEnd = y + sin(radians(angle)) * (radius + rayLength);
    display.drawLine(xStart, yStart, xEnd, yEnd, color);
  }
}

void drawCloud(int x, int y, int size, uint16_t color) {
  // Draw overlapping circles to form the cloud shape
  display.fillCircle(x, y, size, color);           // Central circle
  display.fillCircle(x - size / 2, y, size - 5, color); // Left circle
  display.fillCircle(x + size / 2, y, size - 5, color); // Right circle
  display.fillRect(x - size, y, size * 2, size / 2, color); // Bottom rectangle for the base
}

void drawRain(int x, int y, int size, uint16_t cloudColor, uint16_t rainColor) {
  // Draw the cloud
  drawCloud(x, y, size, cloudColor);

  // Draw raindrops as vertical lines
  int dropSpacing = 10; // Spacing between raindrops
  for (int i = -1; i <= 1; i++) {
    display.drawLine(x + i * dropSpacing, y + size, x + i * dropSpacing, y + size + 10, rainColor);
  }
}

void drawStorm(int x, int y, int size, uint16_t cloudColor, uint16_t lightningColor) {
  // Draw the cloud
  drawCloud(x, y, size, cloudColor);

  // Draw a lightning bolt
  int boltX1 = x - 5;
  int boltX2 = x;
  int boltX3 = x + 5;
  int boltY1 = y + size + 5;
  int boltY2 = boltY1 + 10;
  int boltY3 = boltY2 + 10;

  display.drawLine(boltX1, boltY1, boltX2, boltY2, lightningColor); // Top diagonal line
  display.drawLine(boltX2, boltY2, boltX3, boltY3, lightningColor); // Bottom diagonal line
}

void process(String name, int x, int y, double percentage) {
  // Define the radius and thickness of the circular progress bar
  int radius = 30;
  int thickness = 6; // Thickness of the circular bar
  uint16_t outlineColor = TEXT_COLOR;    // Outline color
  uint16_t fillColor = ILI9341_WHITE;    // Fill color for percentage bar
  uint16_t backgroundColor = BACKGROUND_COLOR; // Background color

  // Clear the previous progress by filling the circular area
  display.fillCircle(x, y, radius, backgroundColor);

  // Draw the outer circle (outline)
  display.drawCircle(x, y, radius, outlineColor);

  // Draw the filled circular percentage bar
  for (int angle = 0; angle <= (percentage / 100.0) * 360; angle++) {
    float radians = angle * DEG_TO_RAD;
    int x1 = x + cos(radians) * radius;
    int y1 = y + sin(radians) * radius;
    int x2 = x + cos(radians) * (radius - thickness);
    int y2 = y + sin(radians) * (radius - thickness);
    display.drawLine(x1, y1, x2, y2, fillColor);
  }

  // Draw the inner circle (background to create the hollow effect)
  display.fillCircle(x, y, radius - thickness, backgroundColor);

  // Print the label inside the circle
  display.setTextColor(TEXT_COLOR);
  display.setTextSize(1);
  int textWidth = name.length() * 6; // Approximate width for each character
  display.setCursor(x - textWidth / 2, y - 3); // Center the text
  display.print(name);
}

void timer(String time, int x, int y, int size) {
  static unsigned long previousMillis = 0; // Store the last update time
  static int minutes = 0;
  static int seconds = 0;

  // Parse the time string only on the first call
  if (minutes == 0 && seconds == 0) {
    int colonIndex = time.indexOf(':');
    minutes = time.substring(0, colonIndex).toInt();
    seconds = time.substring(colonIndex + 1).toInt();
  }

  unsigned long currentMillis = millis();

  // Check if 1 second has passed
  if (currentMillis - previousMillis >= 1000) {
    previousMillis = currentMillis;

    // Decrement the timer
    if (seconds == 0) {
      if (minutes > 0) {
        seconds = 59;
        minutes--;
      }
    } else {
      seconds--;
    }

    // Clear the previous time display
    display.fillRect(x, y, size * 6 * 5, size * 10, BACKGROUND_COLOR);

    // Display the updated time
    display.setTextColor(TEXT_COLOR);
    display.setTextSize(size);
    display.setCursor(x, y);
    if (minutes < 10) display.print('0');
    display.print(minutes);
    display.print(':');
    if (seconds < 10) display.print('0');
    display.print(seconds);
  }
}
