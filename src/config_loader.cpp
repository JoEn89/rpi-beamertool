// config_loader.cpp

#include <fstream>
#include <string>
#include "config_loader.h"

using namespace std;
using namespace Beamertool;

ConfigLoader::ConfigLoader() {
    this->artnet_universe = CFG_STD_ARTNET_UNIVERSE;
    this->artnet_subnet = CFG_STD_ARTNET_SUBNET;
    this->lasersim_num = CFG_STD_LASERSIM_NUM;
    this->lasersim_dmx_start = CFG_STD_LASERSIM_DMX_START;
    this->zooming_type = CFG_STD_ZOOMING;
    this->scaling_multiplier = CFG_STD_SCALE_MULTIPLIER;
    this->led_gpio_pin = CFG_STD_LED_GPIO_PIN;
    this->Servo_gpio_pin = CFG_STD_SERVO_GPOI_PIN;
    this->Servo_min=CFG_STD_SERVO_MIN;
    this->Servo_max=CFG_STD_SERVO_MAX;
    this->S_open=CFG_STD_S_OPEN;
    this->S_close=CFG_STD_S_CLOSE;
    loadConfigFile();
}

void ConfigLoader::loadConfigFile() {
    string line;
    ifstream cfgfile (CFG_FILE);
    if (cfgfile.is_open()) {
        while (getline(cfgfile, line)) {
            cleanLine(line);
            parseCleanLine(line);
        }
        cfgfile.close();
    }
}

void ConfigLoader::cleanLine(string &line) {
    string clean_line;
    clean_line.clear();
    string::iterator it=line.begin();
    while(it!=line.end() && *it !='#') {
        if (*it > 0x20 && *it < 0x7F) {
            clean_line.push_back(*it);
        }
        ++it;
    }
    line = clean_line;
}

void ConfigLoader::parseCleanLine(string &line) {

    // SUBNET
    if (line.compare(0, 7, "SUBNET=") == 0) {
        line.erase(0, 7);
        this->artnet_subnet = stoi(line);
        if (this->artnet_subnet < 0 || this->artnet_subnet > 15) {
            this->artnet_subnet = CFG_STD_ARTNET_SUBNET;
        }

    // UNIVERSE
    } else if (line.compare(0, 9, "UNIVERSE=") == 0) {
        line.erase(0, 9);
        this->artnet_universe = stoi(line);
        if (this->artnet_universe < 0 || this->artnet_universe > 15) {
            this->artnet_universe = CFG_STD_ARTNET_UNIVERSE;
        }

    // ANZAHL
    } else if (line.compare(0, 7, "ANZAHL=") == 0) {
        line.erase(0, 7);
        this->lasersim_num = stoi(line);
        if (this->lasersim_num < 1 || this->lasersim_num > 25) {
            this->lasersim_num = CFG_STD_LASERSIM_NUM;
        }

    // DMX_START
    } else if (line.compare(0, 10, "DMX_START=") == 0) {
        line.erase(0, 10);
        this->lasersim_dmx_start = stoi(line);
        if (this->lasersim_dmx_start < 1 || this->lasersim_dmx_start > 490) {
            this->lasersim_dmx_start = CFG_STD_LASERSIM_DMX_START;
        }

    // ZOOM
    } else if (line.compare(0, 5, "ZOOM=") == 0) {
        line.erase(0, 5);
        if (stoi(line) == 2) {
            this->zooming_type = 2;
        }

    // SCAL_MULT
    } else if (line.compare(0, 10, "SCAL_MULT=") == 0) {
        line.erase(0, 10);
        this->scaling_multiplier = stof(line);
        if (this->scaling_multiplier <= 0.f || this->scaling_multiplier >= 10.0f) {
            this->scaling_multiplier = CFG_STD_SCALE_MULTIPLIER;
        }

    // LED_GPIO_PIN
    } else if (line.compare(0, 13, "LED_GPIO_PIN=") == 0) {
        line.erase(0, 13);
        this->led_gpio_pin = stoi(line);
        if (this->led_gpio_pin < 0 || this->led_gpio_pin > 30) {
            this->led_gpio_pin = -1;
        }

        // SERVO_GPIO_PIN
    } else if (line.compare(0, 15, "SERVO_GPIO_PIN=") == 0) {
        line.erase(0, 13);
        this->Servo_gpio_pin = stoi(line);
        if (this->Servo_gpio_pin < 0 || this->Servo_gpio_pin > 30) {
            this->Servo_gpio_pin = -1;
        }
    
        // SERVO_MIN
    } else if (line.compare(0, 15, "SERVO_MIN=") == 0) {
        line.erase(0, 13);
        this->Servo_min = stoi(line);
        if (this->Servo_min < 0 || this->Servo_min > 30) {
            this->Servo_min = -1;
        }
    
        // SERVO_MAX
    } else if (line.compare(0, 15, "SERVO_MAX=") == 0) {
        line.erase(0, 13);
        this->Servo_max = stoi(line);
        if (this->Servo_max < 0 || this->Servo_max > 30) {
            this->Servo_max = -1;
        }

        // S_OPEN
    } else if (line.compare(0, 15, "S_OPEN=") == 0) {
        line.erase(0, 13);
        this->S_open = stoi(line);
        if (this->S_open < 0 || this->S_open > 30) {
            this->S_open = -1;
        }

        // S_CLOSE
    } else if (line.compare(0, 15, "S_CLOSE=") == 0) {
        line.erase(0, 13);
        this->S_close = stoi(line);
        if (this->S_close < 0 || this->S_close > 30) {
            this->S_close = -1;
        }
    }

    // plausibility test - passt DMX_START und Anzahl zusammen?
    if ((this->lasersim_dmx_start + 20 * this->lasersim_num) > 512) {
        this->lasersim_dmx_start = CFG_STD_LASERSIM_DMX_START;
        this->lasersim_num = CFG_STD_LASERSIM_NUM;
    }
}

int ConfigLoader::getArtnetUniverse() {
    return this->artnet_universe;
}

int ConfigLoader::getArtnetSubnet() {
    return this->artnet_subnet;
}

int ConfigLoader::getLasersimNum() {
    return this->lasersim_num;
}

int ConfigLoader::getLasersimDMXStart() {
    return this->lasersim_dmx_start;
}

int ConfigLoader::getZoomType() {
    return this->zooming_type;
}

float ConfigLoader::getScalingMultiplier() {
    return this->scaling_multiplier;
}

int ConfigLoader::getLedGpioPin() {
    return this->led_gpio_pin;
}

int ConfigLoader::getServoGpioPin() {
    return this->Servo_gpio_pin;
}

int ConfigLoader::getServoMin() {
    return this->Servo_min;
}

int ConfigLoader::getServoMax() {
    return this->Servo_max;
}

int ConfigLoader::getShutterOpen() {
    return this->S_open;
}

int ConfigLoader::getShutterClose() {
    return this->S_close;
}