#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH    128
#define SCREEN_HEIGHT   64
#define OLED_RESET      -1
#define SCREEN_ADDRESS  0x3C

#define FONT_WIDTH      6   // Nominal width
#define FONT_HEIGHT     8   // Nominal height

extern const char* CheerPhrases(int angle);

class Display {
private:
    Adafruit_SSD1306* ssd1306 = nullptr;
    int text_size = 1;

    String FloatToStr(float num);

public:
    Display();
    ~Display();

    // Initialization
    void Init();
    // Clear and display
    void Clear();
    void Show();

    // Text Configuration
    void SetCursor(int16_t x, int16_t y);
    void SetTextSize(int16_t font_size);

    // Text Positioning
    void CenterText(String text, int16_t line);
    void LeftText(String text, int16_t line);
    void RightText(String text, int16_t line);

    // Text Printing
    void Print(String text);
};