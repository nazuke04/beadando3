#include "checkbox.hpp"
#include "graphics.hpp"

using namespace genv;
using namespace std;

Checkbox::Checkbox(int x, int y, const string& label, bool start_val, function<void(bool)> on_change)
    : Widget(x, y, 20, 20), label(label), checked(start_val), on_change(on_change) {}

void Checkbox::draw() const {
    gout << move_to(x, y)
         << color(0, 0, 0)
         << box(20, 20)
         << move_to(x + 1, y + 1)
         << color(255, 255, 255)
         << box(18, 18);

    if (checked) {
        gout << move_to(x + 4, y + 4)
             << color(0, 200, 0)
             << box(12, 12);
    }

    gout << move_to(x + 30, y + 15)
         << color(0, 0, 0)
         << text(label);
}

void Checkbox::handle(event ev) {
    if (ev.type == ev_mouse && ev.button == btn_left && is_selected(ev.pos_x, ev.pos_y)) {
        checked = !checked;
        if (on_change) on_change(checked);
    }
}

bool Checkbox::is_checked() const {
    return checked;
}
