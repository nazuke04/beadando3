#ifndef CHECKBOX_HPP
#define CHECKBOX_HPP

#include "widget.hpp"
#include <functional>
#include <string>

using namespace genv;
using namespace std;

class Checkbox : public Widget {
private:
    bool checked;
    function<void(bool)> on_change;
    string label;

public:
    Checkbox(int x, int y, const string& label, bool start_val, function<void(bool)> on_change);
    void draw() const override;
    void handle(event ev) override;
    bool is_checked() const;
};

#endif
