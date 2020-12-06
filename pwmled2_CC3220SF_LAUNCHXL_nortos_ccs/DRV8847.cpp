#include <DRV8847.h>

uint8_t global_count = 0;

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

void DRV8847::openLoopDispense(uint8_t components){
    uint8_t steps = (uint8_t)(components * this->component_spacing)/this->tape_per_step;
    this->drive(steps);
}

void DRV8847::closedLoopDispense(uint8_t components){
    uint8_t holes_to_pass = (uint8_t) components * this->component_spacing / HOLE_SPACING; // number of holes to pass by
    uint8_t extra_tape = (uint8_t) components * this->component_spacing % HOLE_SPACING;
}

void DRV8847::driverEnable(){
    GPIO_write(this->enable, 1);
}

void DRV8847::driverDisable(){
    GPIO_write(this->enable, 0);
}

void DRV8847::enableSensors(I2C_Handle i2c){
    this->light_sensor1.init(i2c, OPT3001::SlaveAddress::ADDRPIN_GND, NULL);
    this->light_sensor2.init(i2c, OPT3001::SlaveAddress::ADDRPIN_VDD, NULL);
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

int8_t DRV8847::es
