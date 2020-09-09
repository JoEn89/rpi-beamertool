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

// deklaration der Variabeln aus dem Config Loader
#define Servo_gpio_pin = getServoGpioPin();
#define Servo_min = getServoMin();          // Min Winkel Servo (in ° std:0)
#define Servo_max = getServoMax();          // Max Winkel Servo (in ° std:360)
#define S_open = getShutterOpen();          // Winkel der bei OPEN eingestellt werden soll
#define S_close = getShutterClose();        // Winkel der bei CLOSE eingestellt werden soll              

ExtShutter::ExtShutter(){
    // check for root
    this->is_root = false;
    if (getuid() == 0) {
        this->is_root = true;
    }

    // init LED
    initExtShutter();
<<<<<<< HEAD
    setExtShutter();

    switch (dmxval) {
        case <=10 :{
            setShutterState(0);        // DMX-Wert 0-10 (Aus)
            break;
        }

        case >=11 && <=127 :{         // DMX-Wert 11-127 (Manuell Shutter Close)
            setShutterState(0);
            break;
        }

        case >=128 && <=244 :{      // DMX-Wert 128-244 (Manuell Schutter Open)
            setShutterState(1);
            break;
        }
        case >=245 && <=255 :{      // DMX-Wert 245-255 (Auto Mode)
            Shutter_Auto_Mode();
            break;
        }
        default; {                  // Rückfallebene (zur Not offen)
            setShutterState(1);
        }
    }
=======
    setExtShutter(1);
>>>>>>> f81ede94273a23f4dd45667c3385763c673341bd
}

// Ansteuerung des externen Shutter über Servo Motor


void ExtShutter::initExtShutter() {
<<<<<<< HEAD
    if (this->is_root && this->Servo_gpio_pin >= 0) {
        FILE *ptr;

        ptr = fopen("/sys/class/gpio/export", "w");
        fprintf(ptr, "%d", this->Servo_gpio_pin);	// enable GPIO-Port
        fclose(ptr);

        char gpio[50];
        sprintf(gpio, "/sys/class/gpio/gpio%d/direction", this->Servo_gpio_pin);
        ptr = fopen(gpio, "w");
        fprintf(ptr, "pwm");  // set Port to pwm
=======
    if (this->is_root && this->led_gpio_pin >= 0) {
        FILE *ptr;

        ptr = fopen("/sys/class/gpio/export", "w");
        fprintf(ptr, "%d", this->led_gpio_pin);	// enable GPIO-Port
        fclose(ptr);

        char gpio[50];
        sprintf(gpio, "/sys/class/gpio/gpio%d/direction", this->led_gpio_pin);
        ptr = fopen(gpio, "w");
        fprintf(ptr, "pwm");  // set Port to output
>>>>>>> f81ede94273a23f4dd45667c3385763c673341bd
        fclose(ptr);
    }
}

<<<<<<< HEAD
void ExtShutter::setShutterState(int value) {
    if (this->is_root && this->Servo_gpio_pin >= 0) {
        int set_value;
        if (value >= 1) {           //Wert >=1 dann Shutter open
            set_value = 1;
            this->led_status = 1;
        } else {                    //Wert 0 dann Shutter Close
=======
void ExtShutter::setExtShutter(int value) {
    if (this->is_root && this->led_gpio_pin >= 0) {
        int set_value;
        if (value >= 1) {
            set_value = 1;
            this->led_status = 1;
        } else {
>>>>>>> f81ede94273a23f4dd45667c3385763c673341bd
            set_value = 0;
            this->led_status = 0;
        }

        FILE *ledptr;
        char gpio[50];
<<<<<<< HEAD
        sprintf(gpio, "/sys/class/gpio/gpio%d/value", this->Servo_gpio_pin);
=======
        sprintf(gpio, "/sys/class/gpio/gpio%d/value", this->led_gpio_pin);
>>>>>>> f81ede94273a23f4dd45667c3385763c673341bd
        ledptr = fopen(gpio, "w");
        fprintf(ledptr, "%d", set_value);
        fclose(ledptr);
    }
}

void ExtShutter::quitExtShutter() {
<<<<<<< HEAD
    if (this->is_root && this->Servo_gpio_pin >= 0) {
        FILE *ptr;
        ptr = fopen("/sys/class/gpio/unexport", "w");
        fprintf(ptr, "%d", this->Servo_gpio_pin);
=======
    if (this->is_root && this->led_gpio_pin >= 0) {
        FILE *ptr;
        ptr = fopen("/sys/class/gpio/unexport", "w");
        fprintf(ptr, "%d", this->led_gpio_pin);
>>>>>>> f81ede94273a23f4dd45667c3385763c673341bd
        fclose(ptr);
    }
}

<<<<<<< HEAD
void ExtShutter::Shutter_Auto_Mode(int State){

/*muss noch programmiert werden
Wenn Bilrschirm eine gewisse Zeit schwarz anzeigt dann Schutter zu sonst auf*/
=======
void ExtShutter::setShutterState(int State){
>>>>>>> f81ede94273a23f4dd45667c3385763c673341bd

}