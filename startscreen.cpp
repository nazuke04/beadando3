#include "startscreen.hpp"
#include "amobawidget.hpp"
#include "graphics.hpp"

using namespace genv;
using namespace std;

StartScreen::StartScreen(int w, int h)
    : width(w), height(h), palya_meret(20), gepi_jatekos(false), start_clicked(false)
{
    gout.open(width, height);

    slider = new Slider(250, 150, 300, 15, 30, 20, [this](int val) {
        palya_meret = val;
    });

    checkbox = new Checkbox(250, 200, "AI player", false, [this](bool val) {
        gepi_jatekos = val;
    });

    start_button = new Button(300, 300, 200, 40, "Start", [this]() {
        start_clicked = true;
    });

    widgets.push_back(slider);
    widgets.push_back(checkbox);
    widgets.push_back(start_button);
}

void StartScreen::event_loop() {
    while (true) {
        start_clicked = false;
        event ev;
        while (gin >> ev && !start_clicked) {
            if (ev.type == ev_mouse || ev.type == ev_key) {
                for (Widget* w : widgets) {
                    w->handle(ev);
                }
            }

            gout << move_to(0, 0)
                 << color(240, 240, 240)
                 << box(width, height);

            gout << move_to(320, 50)
                 << color(0, 0, 0)
                 << text("Tic-tac-toe");

            for (Widget* w : widgets) {
                w->draw();
            }

            gout << move_to(250, 120)
                 << color(0, 0, 0)
                 << text("Choose map size");

            gout << move_to(250, 250)
                 << text("Map size: " + to_string(palya_meret) + "x" + to_string(palya_meret));

            gout << refresh;
        }
        AmobaWidget* jatek = new AmobaWidget(palya_meret, gepi_jatekos);
        jatek->event_loop();
        delete jatek;
    }
}
