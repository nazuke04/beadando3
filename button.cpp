#include "button.hpp"
#include "graphics.hpp"

using namespace genv;
using namespace std;

Button::Button(int x, int y, int width, int height, const string& label, function<void()> action)
    : Widget(x, y, width, height), label(label), action(action) {}

void Button::draw() const {
    gout << move_to(x, y)
         << color(200, 200, 200)
         << box(width, height)
         << move_to(x + 5, y + height / 2 + 5)
         << color(0, 0, 0)
         << text(label);
}

void Button::handle(event ev) {
    if (ev.type == ev_mouse && ev.button == btn_left && is_selected(ev.pos_x, ev.pos_y)) {
        if (action) action();
    }
}
