#ifndef JATEK_MESTER_HPP
#define JATEK_MESTER_HPP

#include <vector>

using namespace std;

enum class Cell { Ures, X, O };

class JatekMester {
private:
    int meret;
    vector<vector<Cell>> tabla;
    bool elso_jatekos_kovetkezik;
    bool gepi_jatekos;

public:
    JatekMester(int meret, bool gepi);

    bool lep(int x, int y);
    bool gep_lep();
    bool van_nyertes(Cell& ki, vector<pair<int,int>>& gyoztes_pontok);
    bool dontetlen();
    const vector<vector<Cell>>& get_tabla() const;
    bool elso_kovetkezik() const;
};

#endif
