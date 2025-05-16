#ifndef AMOBAWIDGET_HPP
#define AMOBAWIDGET_HPP

#include "jatek_mester.hpp"
#include <vector>
#include <string>

using namespace std;

class AmobaWidget {
private:
    int width, height;
    int palya_meret;
    int cella_meret;
    bool gep;
    JatekMester mester;
    int pont_X, pont_O;
    bool vege;
    string eredmeny_szoveg;
    vector<pair<int,int>> gyoztes_pontok;

public:
    AmobaWidget(int palya_meret, bool gepi_jatekos);
    void event_loop();
    void rajzol() const;
    void lepes(int sor, int oszlop);
    void reset_jatek();
};

#endif
