#ifndef STARTSCREEN_HPP
#define STARTSCREEN_HPP

#include "widget.hpp"
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
    StartScreen(int w, int h);
    void event_loop();
    int get_palya_meret() const;
    bool is_gep_valasztva() const;
    bool is_start_pressed() const;
};

#endif
