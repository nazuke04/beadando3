#ifndef SLIDER_HPP
#define SLIDER_HPP

#include "widget.hpp"
#include <functional>

using namespace genv;
using namespace std;

class Slider : public Widget {
private:
    int min_val, max_val, value;
    function<void(int)> on_change;

public:
    Slider(int x, int y, int width, int min_val, int max_val, int start_val, function<void(int)> on_change);
    void draw() const override;
    void handle(event ev) override;
    int get_value() const;
};

#endif
