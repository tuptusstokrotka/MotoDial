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

class Display : public Adafruit_SSD1306 {
private:
    int text_size = 1; // Required for text positioning
public:
    Display();
    ~Display();

    // Initialization
    void Init();

    // Text Configuration
    void SetTextSize(int16_t font_size);

    // Text Positioning
    void CenterText(String text, int16_t line);
    void LeftText(String text, int16_t line);
    void RightText(String text, int16_t line);

    // Float to String - for Angle with precision
    String FloatToStr(float num);
};