#include "startscreen.hpp"
#include "graphics.hpp"
#include <ctime>

using namespace genv;

int main() {
    gout.open(900, 700);
    srand(time(0));
    StartScreen start;
    start.event_loop();
    return 0;
}
