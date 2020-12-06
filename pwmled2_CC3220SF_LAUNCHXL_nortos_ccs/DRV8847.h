#ifndef DRV8847_H
#define DRV8847_H

#include <unistd.h>
#include <stddef.h>

#include <ti/drivers/PWM.h>
#include <ti/drivers/GPIO.h>

#include <ti_drivers_config.h>

#include <OPT3001.h>

#define HIGH_LIGHT_VALUE 50
#define LOW_LIGHT_VALUE 0

#define HOLE_SPACING 4 // in mm

const uint8_t drive_seq [2][4] = { {1, 1, 0, 0}, {0, 1, 1, 0} };

class DRV8847{
public:
    DRV8847(uint8_t in1_pin, uint8_t in2_pin, uint8_t enable_pin);

    /* sets space between components used for calculation
     * spacing is space between components in mm
     */
    void setComponentSpacing(uint8_t spacing);

    /* sets the approximate distance tape moves per
     * motor step
     * factor is the distance in mm
     */
    void setTapePerStep(uint8_t factor); // factor in mm

    void openLoopDispense(uint8_t components);

    void closedLoopDispense(uint8_t components);

    void driverEnable();

    void driverDisable();

    void enableSensors(I2C_Handle i2c);

private:
    uint8_t component_spacing = 0;
    uint8_t tape_per_step = 0;
    uint8_t drive_seq_ind = 0;
    uint8_t in1;
    uint8_t in2;
    uint8_t enable;
    uint8_t light_int;
    OPT3001 light_sensor1;
    OPT3001 light_sensor2;
    uint32_t high_light_value = 50;
    uint32_t low_light_value = 0;
    void drive(uint8_t steps);

    /* estimate the position of the tape from the
     * light sensors.
     * returns a positive or negative number representing
     * the distance in mm the tape is away from being aligned
     * with light_sensor1
     */
    double estimatePosition();
};

#endif //DRV8847_H
