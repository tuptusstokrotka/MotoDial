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
    //TODO: Check if components are connected & working
    //TODO: Check for errors
    //TODO: Update state

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

    switch(GetState()) {
        case State::IDLE:{
            pixels->setPixelColor(0, pixels->Color(255, 255, 255));
            break;
        }
        case State::READY:{
            pixels->setPixelColor(0, GradientColor(angleMeter.GetAngle(), MAX_ANGLE));
            break;
        }
        case State::CALIBRATING:{
            // Blink PINK
            if((millis() / 500 % 2 == 0))
                pixels->setPixelColor(0, pixels->Color(255, 0, 120));
            else
                pixels->setPixelColor(0, pixels->Color(0, 0, 0));
            break;
        }
        case State::ERROR:{
            // Blink RED
            if((millis() / 500 % 2 == 0))
                pixels->setPixelColor(0, pixels->Color(255, 0, 0));
            else
                pixels->setPixelColor(0, pixels->Color(0, 0, 0));
            break;
        }
    }
    pixels->show();
}

void Board::DisplayUpdate() {
    if (display == nullptr)
        return;

    display->clearDisplay();
    switch(GetState()) {
        case State::READY:{
            display->SetTextSize(5);
            display->CenterText(String(angleMeter.GetAngle()), 0);

            display->SetTextSize(2);
            display->LeftText( String(angleMeter.GetLMax()), 3);
            display->RightText(String(angleMeter.GetRMax()), 3);
            break;
        }
        case State::CALIBRATING:{
            display->SetTextSize(2);
            display->CenterText("CALIBRATE", 0);
            display->RightText(String(angleMeter.GetRoll()),  2);
            display->RightText(String(angleMeter.GetPitch()), 3);

            display->SetTextSize(1);
            display->LeftText("ROLL",  4);
            display->LeftText("PITCH", 6);

            break;
        }
        case State::ERROR:{
            display->SetTextSize(2);
            display->CenterText("ERROR", 0);

            String errorCodeStr = (errorCode <= 0x0F ? "0x0" : "0x") + String(errorCode, HEX);
            display->CenterText(errorCodeStr, 2);
            break;
        }
        default:
            break;
    }
    display->display();
}

void Board::ButtonUpdate() {
    // Button Press
    if(digitalRead(BUTTON_PIN) == HIGH) {
        //DEBUG state change
        if(GetState() == State::IDLE)
            SetState(State::CALIBRATING);
        else if(GetState() == State::CALIBRATING)
            SetState(State::READY);
        else if(GetState() == State::READY)
            SetState(State::ERROR);
        else if(GetState() == State::ERROR)
            SetState(State::IDLE);

        while(digitalRead(BUTTON_PIN) == HIGH) {;} //DELETE this is no no
    }
    // Button Hold
    //TODO
}