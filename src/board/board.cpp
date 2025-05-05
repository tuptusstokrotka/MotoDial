#include "board.h"

Board::Board() { }

Board::~Board() {
    delete pixels;
}

void Board::Init() {
    pinMode(BUTTON_PIN, INPUT);

    // I2C
    Wire.begin(SDA, SCL);
    // Accelerometer
    angleMeter.Init();
    // OLED
    #ifdef OLED_ENABLE
        display.Init();
    #endif
    // LED
    #ifdef LED_ENABLE
        pixels = new Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
        pixels->begin();
        pixels->setBrightness(BRIGHTNESS);
    #endif

    SetState(State::READY);
}

void Board::Update() {
    // angleMeter.Update();

    LedUpdate();
    DisplayUpdate();
    ButtonUpdate();

}

void Board::Calibrate() {
    // Calibrate the accelerometer
}


void Board::LedUpdate() {
    if (pixels == nullptr)
        return;

    // pixels->setPixelColor(0, GradientColor(angleMeter.GetAngle(), MAX_ANGLE));
    pixels->setPixelColor(0, pixels->Color(0, 0, 0)); //DEBUG
    pixels->show();
}

void Board::DisplayUpdate() {
    display.Clear();
    display.SetTextSize(1);
    // display.CenterText(String(angleMeter.GetAngle()), 0);
    display.LeftText("TEST", 0);
    display.CenterText("TEST", 1);
    display.RightText("TEST", 2);
    display.Show();
}

void Board::ButtonUpdate() {
    // Button Press
    if(digitalRead(BUTTON_PIN) == HIGH) {
        pixels->setPixelColor(0, pixels->Color(0, 0, 255)); //DEBUG
        pixels->show(); //DEBUG
        while(digitalRead(BUTTON_PIN) == HIGH) {;} //DELETE this is no no
    }
    // Button Hold
    //TODO
}