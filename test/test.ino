#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ILI9341.h> // ILI9341 library

// Define pins for ILI9341
#define TFT_CS     10  // Chip select pin
#define TFT_DC     9   // Data/Command pin
#define TFT_RST    8   // Reset pin
// Initialize ILI9341 display object
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  // Initialize the display
  tft.begin();

  // Rotate display (optional)
  tft.setRotation(-1); // Landscape mode
  sayHi();
 
}

void sayHi(){ 
 // Fill screen with a solid color
  tft.fillScreen(ILI9341_BLACK);

  // Set text color and size
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(3);

  // Define the text to display
  String text = "Hello, World!";

  // Get text width and height using getTextBounds
  int16_t x1, y1; // Variables to store coordinates of the text's top-left corner
  uint16_t textWidth, textHeight;
  tft.getTextBounds(text, 0, 0, &x1, &y1, &textWidth, &textHeight);

  // Calculate position to center the text
  int16_t centerX = (tft.width() - textWidth) / 2;
  int16_t centerY = (tft.height() - textHeight) / 2;

  // Set cursor to the calculated center position
  tft.setCursor(centerX, centerY);

  // Print the text
  tft.print(text);

  // Draw a cube around the centered text
  // We'll create a 3D cube effect by drawing overlapping rectangles
  int padding = 10; // Space between the text and the cube edges
  int cubeWidth = textWidth + 2 * padding;
  int cubeHeight = textHeight + 2 * padding;

  // Front face of the cube
  tft.drawRect(centerX - padding, centerY - padding, cubeWidth, cubeHeight, ILI9341_YELLOW);

  // Back face of the cube (offset diagonally for 3D effect)
  int offset = 10; // Amount of diagonal offset for the 3D effect
  tft.drawRect(centerX - padding + offset, centerY - padding + offset, cubeWidth, cubeHeight, ILI9341_YELLOW);

  // Connect the corners to create the 3D effect
  tft.drawLine(centerX - padding, centerY - padding, centerX - padding + offset, centerY - padding + offset, ILI9341_YELLOW); // Top-left corner
  tft.drawLine(centerX - padding + cubeWidth, centerY - padding, centerX - padding + cubeWidth + offset, centerY - padding + offset, ILI9341_YELLOW); // Top-right corner
  tft.drawLine(centerX - padding, centerY - padding + cubeHeight, centerX - padding + offset, centerY - padding + cubeHeight + offset, ILI9341_YELLOW); // Bottom-left corner
  tft.drawLine(centerX - padding + cubeWidth, centerY - padding + cubeHeight, centerX - padding + cubeWidth + offset, centerY - padding + cubeHeight + offset, ILI9341_YELLOW); // Bottom-right corner

}
void loop() {
  // Nothing in the loop for this example
}
