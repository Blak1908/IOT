#ifndef UltraSonicDistanceSensor_H
#define UltraSonicDistanceSensor_H

#include "Arduino.h"

class UltraSonicDistanceSensor_hshop {
 public:
    /**
     * @param triggerPin  Digital pin that is used for controlling sensor (output).
     * @param echoPin  Digital pin that is used to get information from sensor (input).
     */
    UltraSonicDistanceSensor_hshop(int triggerPin, int echoPin);

    /**
     * Measures distance by sending ultrasonic waves and measuring time it takes them
     * to return.
     * @returns Distance in centimeters, or negative value if distance is greater than 400cm.
     */
    double measureDistanceCm();
 private:
    int triggerPin, echoPin;
};

#endif // HCSR04_H
