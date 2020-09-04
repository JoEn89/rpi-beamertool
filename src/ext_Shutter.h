// ext_Shutter.h

#include <string>

#ifndef ExtShutter_h
#define ExtShutter_h

#define 

namespace Beamertool {

    class ExtShutter {

    public:
        /**
         * standard constructor
         */
        ExtShutter();
        
        ~ExtShutter();      //Destruktor



        // Funktionen
        int getExtShutMode();
        void initExtShutter();
        void setExtShutter();
        int setShutterOpen();
        int setShutterClose();
        

    private:
        int Mode;          // 1 = Artnet | 2 = Automatisch | 0 = Aus
        int AutoTime;      // Wert in Sekunden | Zeit die vertreichen soll nachdem der Bildschirm Schwarz ist
        int mindeg;           // min Winkel von Servo
        int maxdeg;           // max Winkel von Servo
        int opendeg;          // Winkel bei geöffnetem Shutter
        int closedeg;         // Winkel bei geschlossenem Shutter
        int GPIO;          // GPIO Pin für den Servo Motor anzuschließen
    };
}

#endif // ext_Shutter.h