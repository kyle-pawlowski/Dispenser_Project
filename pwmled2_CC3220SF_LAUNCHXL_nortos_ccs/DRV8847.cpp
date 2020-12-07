#include <DRV8847.h>

uint8_t global_count = 0;

static void lightThreshCallback(uint_least8_t index){
    global_count++;
}

DRV8847::DRV8847(uint8_t in1_pin, uint8_t in2_pin, uint8_t enable_pin){
    this->in1 = in1_pin;
    this->in2 = in2_pin;
    this->enable = enable_pin;
    GPIO_init();
    GPIO_setConfig(this->in1, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(this->in2, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(this->enable, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    /*PWM_init();
    PWM_Params_init(&params);
    params.dutyUnits = PWM_DUTY_US;
    params.dutyValue = (uint16_t)period*1000/2;
    params.periodUnits = PWM_PERIOD_US;
    params.periodValue = period * 1000;
    in1 = PWM_open(CONFIG_PWM_0, &params);
    in2 = PWM_open(CONFIG_PWM_1, &params);*/
}

void DRV8847::setComponentSpacing(uint8_t spacing){
    this->component_spacing = spacing;
}

void DRV8847::setTapePerStep(uint8_t factor){
    this->tape_per_step = factor;
}

void DRV8847::setHighLightValue(uint32_t value){
    this->high_light_value = value;
    this->light_sensor1.setHighLimit(this->light_sensor1.parseLux(this->high_light_value));
}

void DRV8847::openLoopDispense(uint8_t components){
    uint8_t steps = (uint8_t)(components * this->component_spacing)/this->tape_per_step;
    this->drive(steps);
}

void DRV8847::closedLoopDispense(uint8_t components){
    // calculate number of holes to pass by and additional tape to dispense
    double currentPosition = this->estimatePosition(); // offset from lined up with sensor 1
    uint8_t holes_to_pass = (uint8_t) components * this->component_spacing / HOLE_SPACING; // number of holes to pass by if starting lined up with sensor 1
    double remainder = (components * this->component_spacing) - HOLE_SPACING*holes_to_pass; // extra distance
    double endingPosition = remainder + currentPosition; // extra distance + initial offset = total offset

    // adjust number of holes based on total offset
    if(endingPosition < 0){
        holes_to_pass--;
        endingPosition += HOLE_SPACING;
    }
    else if(endingPosition > HOLE_SPACING){
        holes_to_pass++;
        endingPosition -= HOLE_SPACING;
    }

    // reset count used by interrupts
    global_count = 0;

    // set up interrupt
    GPIO_enableInt(this->light_int);

    while(global_count < holes_to_pass){ // check global count which in incremented by interrupts
        this->drive(1); // step and check for interrupts
        usleep(1000);
    }

    GPIO_disableInt(this->light_int);

    uint8_t extra_steps = endingPosition * this->tape_per_step;
    this->drive(extra_steps);
}

void DRV8847::driverEnable(){
    GPIO_write(this->enable, 1);
}

void DRV8847::driverDisable(){
    GPIO_write(this->enable, 0);
}

void DRV8847::enableSensors(I2C_Handle i2c, uint8_t light_int_pin){
    this->light_int = light_int_pin;
    //GPIO_setConfig(this->light_int, GPIO_CFG_IN_STD);
    GPIO_setCallback(this->light_int, lightThreshCallback);
    this->light_sensor1.init(i2c, OPT3001::SlaveAddress::ADDRPIN_GND, NULL);
    this->light_sensor2.init(i2c, OPT3001::SlaveAddress::ADDRPIN_VDD, NULL);
    this->light_sensor1.setLowLimit(this->light_sensor1.parseLux(0));
    this->light_sensor1.setHighLimit(this->light_sensor1.parseLux(this->high_light_value));
    this->light_sensor2.setLowLimit(this->light_sensor2.parseLux(0));
    this->light_sensor2.setHighLimit(this->light_sensor2.parseLux(0xFFFFFFFFFFFFFFFF));
}

void DRV8847::drive(uint8_t steps){
    for(int i = 0; i < steps; i++){
        if(this->drive_seq_ind > 3){
            this->drive_seq_ind = 0;
        }
        GPIO_write(this->in1, drive_seq[0][this->drive_seq_ind]);
        GPIO_write(this->in2, drive_seq[1][this->drive_seq_ind]);
        this->drive_seq_ind++;
        usleep(500000);
    }
}

double DRV8847::estimatePosition(){
    uint32_t sensor_value1 = this->light_sensor1.getResult();
    uint32_t sensor_value2 = this->light_sensor2.getResult();
    double abs_offset = ((sensor_value1 - this->low_light_value) /(this->high_light_value - this->low_light_value))* HOLE_SPACING;
    int8_t sign = sensor_value2 > ((high_light_value-low_light_value)/2) ? 1 : -1;
    return (abs_offset * sign);
}
