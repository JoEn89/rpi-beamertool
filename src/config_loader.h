// config_loader.h

#ifndef CONFIG_LOADER_H
#define CONFIG_LOADER_H

// Standard Werte für Einstellungen in der config Datei
#define CFG_STD_ARTNET_SUBNET 0
#define CFG_STD_ARTNET_UNIVERSE 0
#define CFG_STD_LASERSIM_NUM 1
#define CFG_STD_LASERSIM_DMX_START 100
#define CFG_STD_ZOOMING 1
#define CFG_STD_SCALE_MULTIPLIER 1.0f
#define CFG_STD_LED_GPIO_PIN -1
#define CFG_STD_SERVO_GPIO_PIN -1
#define CFG_STD_SERVO_MIN 0
#define CFG_STD_SERVO_MAX 360
#define CFG_STD_S_OPEN -1
#define CFG_STD_S_CLOSE -1

#define CFG_FILE "config.txt"   // Dateiname(/Pfad) der cfg Datei

#include <string>

namespace Beamertool {

    class ConfigLoader {

    public:
        /**
         * standard constructor
         */
        ConfigLoader();

        /**
         * read config file line by line
         */
        void loadConfigFile();

        /**
         * remove comments and whitespaces from a line
         * @param line the line to clean
         */
        void cleanLine(std::string &line);

        /**
         * parse a clean line to a config variable
         * @param line the clean config line
         */
        void parseCleanLine(std::string &line);

        // get the config values
        int getArtnetUniverse();
        int getArtnetSubnet();
        int getLasersimNum();
        int getLasersimDMXStart();
        int getZoomType();
        float getScalingMultiplier();
        int getLedGpioPin();
        int getServoGpioPin();
        int getServoMin();
        int getServoMax();
        int getShutterOpen();
        int getShutterClose();

    private:
        int artnet_universe;        // Art-Net Universe
        int artnet_subnet;          // Art-Net Subnet
        int lasersim_num;           // Anzahl der Laser Simulationen
        int lasersim_dmx_start;     // Startadresse des ersten Lasers
        int zooming_type;           // Zoom Typ: 1=Windows Beamertool, 2=Kreis
        float scaling_multiplier;   // Multiplikator für die Skalierung
        int led_gpio_pin;           // GPIO Pin der Artnet Receiver Status LED
        int Servo_gpio_pin;         // GPIO Pin zur Ensteuerung des Externen Shutter Servos
        int Servo_min;              // Min Winkel Servo (in ° std:0)
        int Servo_max;              // Max Winkel Servo (in ° std:360)
        int S_open;                 // Winkel der bei OPEN eingestellt werden soll
        int S_close;                // Winkel der bei CLOSE eingestellt werden soll
    };
}

#endif // CONFIG_LOADER_H
