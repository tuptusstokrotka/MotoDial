#ifndef ANGLE_METER_H
#define ANGLE_METER_H

#include <DFRobot_BMI160.h>

#pragma region DEBUG
    #ifndef DEBUG_ANGLE_PRINT_ENABLE
    #define DEBUG_ANGLE_PRINT_ENABLE 0
    #endif
    #if DEBUG_ANGLE_PRINT_ENABLE == 1
        #define DEBUG_ANGLE_PRINT(s)   	Serial.print(s);
        #define DEBUG_ANGLE_PRINTLN(s) 	Serial.println(s);
    #else
        #define DEBUG_ANGLE_PRINT(s)   	;
        #define DEBUG_ANGLE_PRINTLN(s) 	;
    #endif
#pragma endregion

#define BMI_ADDRESS 0x69

#define CALIBRATION_THRESHOLD 15    // degrees
#define MAX_ANGLE_RANGE 70          // degrees
#define MAX_ANGLE_HOLD_TIME 10000   // ms
#define ALPHA 0.92f                 // Complementary filter

// DUMMY for testing - calibration will get the correct offsets
enum class eAxis { //DEBUG
    _CALIBRATE,
    _PITCH,
    _ROLL,
};

class MaxAngle {
    uint32_t value = 0;
    unsigned long updateTime = 0;
public:
    MaxAngle(){};

    void Update(uint32_t value);
    inline uint32_t GetValue() { return value; }
};

class AngleMeter : public DFRobot_BMI160 {
private:
/*  Configuration  */
    int address = 0;
    // eAxis mode  = eAxis::_CALIBRATE;    //DEBUG
    eAxis mode  = eAxis::_ROLL;         //DEBUG
    bool invertDirection = false;

    float pitch_offset = 0;
    float roll_offset  = 0;

/*  Attributes */
    // Raw Angles
    float pitch   = 0;
    float roll    = 0;

    // Max angles
    MaxAngle LMax;
    MaxAngle RMax;


    unsigned long lastUpdateTime = 0;
    void Read();

public:
    AngleMeter(int address = BMI_ADDRESS, bool invertDirection = false);
    ~AngleMeter();

    bool Init();
    bool Calibrate();

    void Update();

    inline eAxis GetMode() { return mode; }

    // Raw Angles
    inline float GetPitch() { return pitch; }
    inline float GetRoll()  { return roll;  }

    // Absolute Angles - Selected Axis ONLY
    uint32_t GetAngle();
    inline uint32_t GetLMax()  { return LMax.GetValue(); }
    inline uint32_t GetRMax()  { return RMax.GetValue(); }
};
#endif