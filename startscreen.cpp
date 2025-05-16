#include "startscreen.hpp"
#include "amobawidget.hpp"
#include "graphics.hpp"

using namespace genv;
using namespace std;

StartScreen::StartScreen()
    : width(900), height(700), palya_meret(20), gepi_jatekos(false), start_clicked(false)
{
    slider = new Slider(300, 150, 300, 15, 30, 20, [this](int val) {
        palya_meret = val;
    });

    checkbox = new Checkbox(300, 200, "Gépi játékos", false, [this](bool val) {
        gepi_jatekos = val;
    });

    start_button = new Button(370, 320, 160, 40, "Start", [this]() {
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
                if (ev.keycode == key_escape) exit(0);
            if (ev.type == ev_mouse || ev.type == ev_key) {
                for (Widget* w : widgets) {
                    w->handle(ev);
                }
            }

            gout << move_to(0, 0)
                 << color(240, 240, 240)
                 << box(width, height);

            gout << move_to(410, 80)
                 << color(0, 0, 0)
                 << text("Amõba játék");

            for (Widget* w : widgets) {
                w->draw();
            }

            gout << move_to(300, 120)
                 << color(0, 0, 0)
                 << text("Pályaméret választása:");

            gout << move_to(360, 250)
                 << text("Aktuális méret: " + to_string(palya_meret) + "x" + to_string(palya_meret));

            gout << refresh;
        }

        AmobaWidget jatek(palya_meret, gepi_jatekos);
        jatek.event_loop();
    }
}
