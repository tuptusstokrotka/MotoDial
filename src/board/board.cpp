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
        display = new Display();
        display->Init();
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
    angleMeter.Update();

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

    pixels->setPixelColor(0, GradientColor(angleMeter.GetAngle(), MAX_ANGLE));
    pixels->show();
}

void Board::DisplayUpdate() {
    if (display == nullptr)
        return;

    display->clearDisplay();
    display->SetTextSize(5);
    display->CenterText(String(angleMeter.GetAngle()), 0);

    display->SetTextSize(2);
    display->LeftText( String(angleMeter.GetLMax()), 3);
    display->RightText(String(angleMeter.GetRMax()), 3);
    display->display();
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