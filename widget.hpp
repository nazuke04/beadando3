#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "graphics.hpp"

using namespace genv;
using namespace std;

class Widget {
protected:
    int x, y, width, height;
    bool focused;

public:
    Widget(int x, int y, int width, int height)
        : x(x), y(y), width(width), height(height), focused(false) {}

    virtual void draw() const = 0;
    virtual void handle(event ev) = 0;

    bool is_selected(int mx, int my) const {
        return mx >= x && mx <= x + width && my >= y && my <= y + height;
    }

    void set_focus(bool f) { focused = f; }
    bool has_focus() const { return focused; }

    virtual ~Widget() {}
};

#endif
