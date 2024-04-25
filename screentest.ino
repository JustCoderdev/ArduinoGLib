#include <MCUFRIEND_kbv.h>
#include <assert.h>

#define DEBUG 0

#define PORTRAIT 0
#define LANDSCAPE 3
#define PORTRAIT_REV 2
#define LANDSCAPE_REV 1

// RRRRRGGG GGGBBBBB
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800

#define WIDTH 320
#define HEIGHT 240

MCUFRIEND_kbv screen(A3, A2, A1, A0, A4);

void death_screen_show() {
  for (int16_t color = 0x8888; 1; color = ~color) {
    screen.fillScreen(color);
    delay(1000);
  }
}

void setup() {
  // Setup serial && screen
  Serial.begin(9600);
  screen.begin(screen.readID());
  screen.setRotation(LANDSCAPE);

  if (WIDTH != screen.width() || HEIGHT != screen.height()) {
    Serial.println("[FATAL] WIDTH or HEIGHT mismatch");
    death_screen_show();
  }

  Serial.print("Initiated screen (");
  Serial.print(screen.width());
  Serial.print("x");
  Serial.print(screen.height());
  Serial.println(")");


#if DEBUG
  // DEBUG SCREEN SIZE
  screen.fillScreen(BLACK);
  screen.fillRect(20, 20, WIDTH - 40, HEIGHT - 40, RED);

  screen.fillCircle(10, 10, 5, BLUE);                   // TOP-LEFT
  screen.fillCircle(10, HEIGHT - 10, 5, BLUE);          // BOTTOM-LEFT
  screen.fillCircle(WIDTH - 10, HEIGHT - 10, 5, BLUE);  // BOTTOM-RIGHT

  // DEBUG SCREEN ROTATION
  for (char i = 0; i < 4; ++i) {
    screen.setRotation(i);
    screen.drawChar(2, 2, '0' + i, BLUE, BLACK, 4);
  }
#endif
}

void loop() {
}
