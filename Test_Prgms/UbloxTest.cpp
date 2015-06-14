#include "/home/pi/Libraries/UbloxGPS.h"

int main() {
    Ublox gps;
    gps.initialize();
    gps.getMessages();
    return 0;
}
