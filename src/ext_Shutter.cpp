//ext_Shutter.cpp

#include "ext_Shutter.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <vector>
#include <thread>
#include "artnet_receiver.h"
#include <iostream.h>
#include "config_loader.h"

using namespace std;
using namespace Beamertool;

ExtShutter::ExtShutter(){
    // check for root
    this->is_root = false;
    if (getuid() == 0) {
        this->is_root = true;
    }

    // init LED
    initExtShutter();
    setExtShutter(1);
}

// Ansteuerung des externen Shutter über Servo Motor


void ExtShutter::initExtShutter() {
    if (this->is_root && this->led_gpio_pin >= 0) {
        FILE *ptr;

        ptr = fopen("/sys/class/gpio/export", "w");
        fprintf(ptr, "%d", this->led_gpio_pin);	// enable GPIO-Port
        fclose(ptr);

        char gpio[50];
        sprintf(gpio, "/sys/class/gpio/gpio%d/direction", this->led_gpio_pin);
        ptr = fopen(gpio, "w");
        fprintf(ptr, "pwm");  // set Port to output
        fclose(ptr);
    }
}

void ExtShutter::setExtShutter(int value) {
    if (this->is_root && this->led_gpio_pin >= 0) {
        int set_value;
        if (value >= 1) {
            set_value = 1;
            this->led_status = 1;
        } else {
            set_value = 0;
            this->led_status = 0;
        }

        FILE *ledptr;
        char gpio[50];
        sprintf(gpio, "/sys/class/gpio/gpio%d/value", this->led_gpio_pin);
        ledptr = fopen(gpio, "w");
        fprintf(ledptr, "%d", set_value);
        fclose(ledptr);
    }
}

void ExtShutter::quitExtShutter() {
    if (this->is_root && this->led_gpio_pin >= 0) {
        FILE *ptr;
        ptr = fopen("/sys/class/gpio/unexport", "w");
        fprintf(ptr, "%d", this->led_gpio_pin);
        fclose(ptr);
    }
}

void ExtShutter::setShutterState(int State){

}