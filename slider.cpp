#include "slider.hpp"
#include "graphics.hpp"

using namespace genv;
using namespace std;

Slider::Slider(int x, int y, int width, int min_val, int max_val, int start_val, function<void(int)> on_change)
    : Widget(x, y, width, 20), min_val(min_val), max_val(max_val), value(start_val), on_change(on_change) {}

void Slider::draw() const {
    gout << move_to(x, y)
         << color(220, 220, 220)
         << box(width, height);

    int knob_x = x + (value - min_val) * width / (max_val - min_val);
    gout << move_to(knob_x - 5, y)
         << color(100, 100, 250)
         << box(10, height);

    gout << move_to(x + width + 10, y + height - 4)
         << color(0, 0, 0)
         << text(to_string(value) + "x" + to_string(value));
}

void Slider::handle(event ev) {
    if (ev.type == ev_mouse && ev.button == btn_left && is_selected(ev.pos_x, ev.pos_y)) {
        int rel_x = ev.pos_x - x;
        value = min_val + rel_x * (max_val - min_val) / width;
        if (value < min_val) value = min_val;
        if (value > max_val) value = max_val;
        if (on_change) on_change(value);
    }
}

int Slider::get_value() const {
    return value;
}
