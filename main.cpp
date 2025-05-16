#include "startscreen.hpp"

int main() {
    StartScreen* start = new StartScreen(800, 600);
    start->event_loop();
    delete start;
    return 0;
}
