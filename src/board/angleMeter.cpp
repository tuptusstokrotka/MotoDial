#include "angleMeter.h"

/**
 * @brief Update the max angle
 * @param value Current angle
 * @note After a while, the max angle will be cleared
 */
void MaxAngle::Update(uint32_t value) {
    // Check if current angle is greater than max
    if (value > this->value) {
        this->value = value;
        this->updateTime = millis();
    }
    // Clear the max value after a while
    if(millis() - updateTime > MAX_ANGLE_HOLD_TIME) {
        this->value = 0;
        return;
    }
}

AngleMeter::AngleMeter(int address, bool invertDirection) : DFRobot_BMI160(){
    this->address = address;
    this->invertDirection = invertDirection;
}

AngleMeter::~AngleMeter() { }

/**
 * @brief Initialize the AngleMeter
 */
bool AngleMeter::Init() {
    if (softReset() != BMI160_OK){
        DEBUG_ANGLE_PRINTLN("reset false");
        while(1);
    }

    if (I2cInit(this->address) != BMI160_OK){
        DEBUG_ANGLE_PRINTLN("init false");
        while(1);
    }

    return BMI160_OK;
}

/**
 * @brief Get the working axis from the reading
 * @note Axis is determined by the reading exceeding the threshold
 */
bool AngleMeter::Calibrate() {
    Read();

    // TODO: Add offsets calibration

    // Determine the axis (dummy) //CHECK
    if (     roll  > CALIBRATION_THRESHOLD || roll  < -CALIBRATION_THRESHOLD) { mode = eAxis::_ROLL;  }
    else if (pitch > CALIBRATION_THRESHOLD || pitch < -CALIBRATION_THRESHOLD) { mode = eAxis::_PITCH; }

    return true;
}

/**
 * @brief Read the data from the AngleMeter. Parse the data into pitch and roll
 */
void AngleMeter::Read() {
   int16_t accelGyro[6] = {0};
    if(getAccelGyroData(accelGyro) == 0) {
        // Calculate the time delta
        float dt = (millis() - lastUpdateTime) / 1000.0f;
        lastUpdateTime = millis();

        // Gyroscope: raw to deg/s (assuming ±250 dps → 131 LSB/°/s)
        float gx = accelGyro[0] / 131.0f;
        float gy = accelGyro[1] / 131.0f;
        float gz = accelGyro[2] / 131.0f;

        // Accelerometer: raw to g
        float ax = accelGyro[3] / 16384.0f;
        float ay = accelGyro[4] / 16384.0f;
        float az = accelGyro[5] / 16384.0f;

        // Compute roll and pitch from accelerometer
        float accRoll  = atan2(ay, az) * 180.0f / PI;
        float accPitch = atan2(-ax, sqrt(ay * ay + az * az)) * 180.0f / PI;

        // Integrate gyro rates to update angles
        roll  += gx * dt;
        pitch += gy * dt;

        // Apply complementary filter to stabilize
        roll  = ALPHA * roll  + (1.0f - ALPHA) * accRoll;
        pitch = ALPHA * pitch + (1.0f - ALPHA) * accPitch;
    }
}

/**
 * @brief Update the current angle and max values
 */
void AngleMeter::Update() {
    // Read the data
    Read();

    // Get the angle - SIGNED
    int32_t angle = (mode == eAxis::_PITCH) ? (int32_t)pitch : (int32_t)roll;

    // Update the max values
    if (invertDirection){
        RMax.Update(angle < 0 ? abs(angle)  : 0);
        LMax.Update(angle > 0 ? angle       : 0);
    } else{
        RMax.Update(angle > 0 ? angle       : 0);
        LMax.Update(angle < 0 ? abs(angle)  : 0);
    }
}

/**
 * @brief Get the current angle based on the mode
 * @return The current angle
 */
uint32_t AngleMeter::GetAngle() { switch (mode) {
    case eAxis::_PITCH:
        return abs(pitch);
    case eAxis::_ROLL:
        return abs(roll);
    default:
        return 0;
    }
}