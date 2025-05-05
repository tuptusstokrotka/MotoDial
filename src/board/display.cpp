#include "display.h"

const char* CheerPhrases(int angle) {
    if      (angle < 10) return "";
    else if (angle < 15) return "COOL!";
    else if (angle < 20) return "RAD!";
    else if (angle < 25) return "WICKED!";
    else if (angle < 30) return "EXCELLENT!";
    else if (angle < 35) return "HYPE!";
    else if (angle < 40) return "TOTALLY!";
    else if (angle < 45) return "NO WAY!";
    else if (angle < 50) return "AWESOME!";
    else if (angle < 55) return "EXTREME!";
    else if (angle < 60) return "FUCK YEAH!";
    else                 return "HOLY SHIT!";
}

Display::Display() { }

Display::~Display() {
    delete ssd1306;
}

String Display::FloatToStr(float num) {
    if (num < 10)
        return String(num, 1);
    else
        return String(num, 0);
}


void Display::Init() {
    ssd1306 = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
    if(ssd1306->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println("SSD1306 Init Success");
    }
    else {
        Serial.println("SSD1306 Init Failed");
    }
    Show();
}

void Display::Clear() {
    ssd1306->clearDisplay();
    Serial.println("SSD1306 Clear");
}

void Display::Show() {
    ssd1306->display();
    Serial.println("SSD1306 Show");
}


void Display::SetCursor(int16_t x, int16_t y) {
    ssd1306->setCursor(x, y);
}

void Display::SetTextSize(int16_t font_size) {
    text_size = font_size;
    ssd1306->setTextSize(font_size);
}


void Display::CenterText(String text, int16_t line){
    int X = (SCREEN_WIDTH - (text.length() * FONT_WIDTH * text_size)) / 2;
    int Y = line * FONT_HEIGHT * text_size;
    ssd1306->setCursor(X, Y);
    ssd1306->print(text);

    Serial.println("Display CenterText");
    Serial.println(text);
    Serial.println(X);
    Serial.println(Y);
}

void Display::LeftText(String text, int16_t line){
    int X = 0;
    int Y = line * FONT_HEIGHT * text_size;
    ssd1306->setCursor(X, Y);
    ssd1306->print(text);
}

void Display::RightText(String text, int16_t line){
    int X = SCREEN_WIDTH - (text.length() * FONT_WIDTH * text_size);
    int Y = line * FONT_HEIGHT * text_size;
    ssd1306->setCursor(X, Y);
    ssd1306->print(text);
}


void Display::Print(String text) {
    ssd1306->print(text);
}