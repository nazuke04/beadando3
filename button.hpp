#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "widget.hpp"
#include <functional>
#include <string>

using namespace std;

class Button : public Widget {
private:
    string label;
    function<void()> action;

public:
    Button(int x, int y, int width, int height, const string& label, function<void()> action);
    void draw() const override;
    void handle(genv::event ev) override;
};

#endif
