#ifndef STARTSCREEN_HPP
#define STARTSCREEN_HPP

#include "button.hpp"
#include "slider.hpp"
#include "checkbox.hpp"
#include <vector>

using namespace std;

class StartScreen {
private:
    int width, height;
    vector<Widget*> widgets;

    Slider* slider;
    Checkbox* checkbox;
    Button* start_button;

    int palya_meret;
    bool gepi_jatekos;
    bool start_clicked;

public:
    StartScreen();
    void event_loop();
};

#endif
