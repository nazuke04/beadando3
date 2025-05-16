#include "jatek_mester.hpp"


using namespace std;

JatekMester::JatekMester(int meret, bool gepi)
    : meret(meret), elso_jatekos_kovetkezik(true), gepi_jatekos(gepi)
{
    tabla = vector<vector<Cell>>(meret, vector<Cell>(meret, Cell::Ures));
}

bool JatekMester::lep(int x, int y) {
    if (tabla[y][x] != Cell::Ures) return false;

    tabla[y][x] = elso_jatekos_kovetkezik ? Cell::X : Cell::O;
    elso_jatekos_kovetkezik = !elso_jatekos_kovetkezik;
    return true;
}

const vector<vector<Cell>>& JatekMester::get_tabla() const {
    return tabla;
}

bool JatekMester::elso_kovetkezik() const {
    return elso_jatekos_kovetkezik;
}

Cell JatekMester::get_aktualis_jel() const {
    return elso_jatekos_kovetkezik ? Cell::X : Cell::O;
}

bool JatekMester::van_nyertes(Cell& ki) {
    int iranyok[4][2] = { {1,0}, {0,1}, {1,1}, {1,-1} };

    for (int y = 0; y < meret; ++y) {
        for (int x = 0; x < meret; ++x) {
            Cell c = tabla[y][x];
            if (c == Cell::Ures) continue;

            for (auto& d : iranyok) {
                int dx = d[0], dy = d[1];
                int count = 1;
                for (int i = 1; i < 5; ++i) {
                    int nx = x + i*dx, ny = y + i*dy;
                    if (nx < 0 || nx >= meret || ny < 0 || ny >= meret) break;
                    if (tabla[ny][nx] == c) count++;
                    else break;
                }
                if (count == 5) {
                    ki = c;
                    return true;
                }
            }
        }
    }
    return false;
}

bool JatekMester::dontetlen() {
    for (const auto& sor : tabla)
        for (Cell c : sor)
            if (c == Cell::Ures)
                return false;
    return true;
}
