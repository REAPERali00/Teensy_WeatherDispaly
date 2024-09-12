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

void setup() {
  // Initialize the display
  display.begin();
  display.setRotation(3); // Adjust orientation
  display.fillScreen(BACKGROUND_COLOR); // Set background color

  // Set the time manually for testing purposes
  setTime(15, 34, 0, 17, 9, 2024); // Time: 3:34 PM, Date: Sep 17, 2024

  // Call the function to draw the static UI
  drawStaticUI();
}

void loop() {
  // Call the function to update the dynamic parts (time, CPU, etc.)
  updateDynamicUI();

  // Refresh every second
  delay(5000);
}

void drawStaticUI() {
  // Clear the screen and draw static parts of the UI
  display.setRotation(0);
  // Date and Time label
  display.setTextSize(2);
  display.setTextColor(TEXT_COLOR);
  display.setCursor(10, 10);
  display.print("Sunday Mar 17");

  // Static sections for icons and system info

  // Draw weather icon (for simplicity, use a circle as an icon placeholder)
  display.fillCircle(40, 60, 15, ICON_COLOR); // Draw a circle for weather icon
  display.setCursor(70, 50);
  display.setTextSize(2);
  display.print("-0.1C   23%"); // Temperature and humidity

  // Game controller and connection block
  display.drawRect(10, 110, 60, 60, ILI9341_WHITE); // Placeholder for game icon
  display.setCursor(80, 130);
  display.setTextSize(2);
  display.print("HDMI 1");

  // CPU, GPU, MEM labels
  display.setCursor(10, 190);
  display.setTextSize(2);
  display.print("CPU");

  display.setCursor(10, 230);
  display.print("GPU");

  display.setCursor(10, 270);
  display.print("MEM");

  // Draw CPU, GPU, MEM usage bars (static part)
  display.drawRect(50, 190, 150, 20, ILI9341_WHITE); // CPU bar outline
  display.drawRect(50, 230, 150, 20, ILI9341_WHITE); // GPU bar outline
  display.drawRect(50, 270, 150, 20, ILI9341_WHITE); // MEM bar outline
}

void updateDynamicUI() {
  // Update date and time
  display.setTextSize(3);
  display.setTextColor(TEXT_COLOR);
  display.fillRect(10, 40, 220, 30, BACKGROUND_COLOR); // Clear previous time
  display.setCursor(10, 40);
  String currentTime = String(hour()) + ":" + (minute() < 10 ? "0" : "") + String(minute());
  display.print(currentTime);

  // Simulate CPU, GPU, MEM values (replace with real values in your application)
  int cpuUsage = 40; // 40% usage
  int gpuUsage = 20; // 20% usage
  int memUsage = 60; // 60% usage

  // Clear and update CPU bar
  display.fillRect(51, 191, 148, 18, BACKGROUND_COLOR); // Clear the old CPU bar
  display.fillRect(51, 191, cpuUsage * 1.5, 18, ILI9341_RED); // Draw CPU usage

  // Clear and update GPU bar
  display.fillRect(51, 231, 148, 18, BACKGROUND_COLOR); // Clear the old GPU bar
  display.fillRect(51, 231, gpuUsage * 1.5, 18, ILI9341_ORANGE); // Draw GPU usage

  // Clear and update MEM bar
  display.fillRect(51, 271, 148, 18, BACKGROUND_COLOR); // Clear the old MEM bar
  display.fillRect(51, 271, memUsage * 1.5, 18, ILI9341_YELLOW); // Draw MEM usage
}
