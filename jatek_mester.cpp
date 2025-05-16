#include "jatek_mester.hpp"
#include <cstdlib>
#include <cmath>
#include <algorithm>

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

bool JatekMester::gep_lep() {
    if (!gepi_jatekos || elso_jatekos_kovetkezik) return false;

    auto probal = [&](Cell proba_kitolt) -> pair<int, int> {
        for (int y = 0; y < meret; ++y) {
            for (int x = 0; x < meret; ++x) {
                if (tabla[y][x] == Cell::Ures) {
                    tabla[y][x] = proba_kitolt;
                    Cell tmp;
                    vector<pair<int,int>> dummy;
                    if (van_nyertes(tmp, dummy) && tmp == proba_kitolt) {
                        tabla[y][x] = Cell::Ures;
                        return {x, y};
                    }
                    tabla[y][x] = Cell::Ures;
                }
            }
        }
        return {-1, -1};
    };

    auto lep1 = probal(Cell::O);
    if (lep1.first != -1) {
        tabla[lep1.second][lep1.first] = Cell::O;
        elso_jatekos_kovetkezik = true;
        return true;
    }

    auto lep2 = probal(Cell::X);
    if (lep2.first != -1) {
        tabla[lep2.second][lep2.first] = Cell::O;
        elso_jatekos_kovetkezik = true;
        return true;
    }

    vector<pair<int, int>> pref;
    for (int y = 0; y < meret; ++y) {
        for (int x = 0; x < meret; ++x) {
            if (tabla[y][x] == Cell::Ures) {
                int szomszed = 0;
                for (int dy = -1; dy <= 1; ++dy) {
                    for (int dx = -1; dx <= 1; ++dx) {
                        int ny = y + dy;
                        int nx = x + dx;
                        if (nx >= 0 && ny >= 0 && nx < meret && ny < meret && !(dx == 0 && dy == 0)) {
                            if (tabla[ny][nx] == Cell::O) szomszed++;
                        }
                    }
                }
                if (szomszed >= 2) {
                    pref.push_back({x, y});
                }
            }
        }
    }

    if (!pref.empty()) {
        auto valasztott = pref[rand() % pref.size()];
        tabla[valasztott.second][valasztott.first] = Cell::O;
        elso_jatekos_kovetkezik = true;
        return true;
    }

    vector<pair<int, int>> ures_mezok;
    for (int y = 0; y < meret; ++y)
        for (int x = 0; x < meret; ++x)
            if (tabla[y][x] == Cell::Ures)
                ures_mezok.push_back({x, y});

    if (!ures_mezok.empty()) {
        int middle = meret / 2;
        sort(ures_mezok.begin(), ures_mezok.end(), [middle](auto a, auto b) {
            int da = abs(a.first - middle) + abs(a.second - middle);
            int db = abs(b.first - middle) + abs(b.second - middle);
            return da < db;
        });

        auto valasztott = ures_mezok.front();
        tabla[valasztott.second][valasztott.first] = Cell::O;
        elso_jatekos_kovetkezik = true;
        return true;
    }

    return false;
}

bool JatekMester::van_nyertes(Cell& ki, vector<pair<int,int>>& gyoztes_pontok) {
    int iranyok[4][2] = { {1,0}, {0,1}, {1,1}, {1,-1} };
    for (int y = 0; y < meret; ++y) {
        for (int x = 0; x < meret; ++x) {
            Cell c = tabla[y][x];
            if (c == Cell::Ures) continue;

            for (auto& d : iranyok) {
                int dx = d[0], dy = d[1];
                vector<pair<int,int>> pontok = { {x, y} };

                for (int i = 1; i < 5; ++i) {
                    int nx = x + i*dx, ny = y + i*dy;
                    if (nx < 0 || nx >= meret || ny < 0 || ny >= meret) break;
                    if (tabla[ny][nx] == c) {
                        pontok.push_back({nx, ny});
                    } else break;
                }

                if (pontok.size() == 5) {
                    ki = c;
                    gyoztes_pontok = pontok;
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

const vector<vector<Cell>>& JatekMester::get_tabla() const {
    return tabla;
}

bool JatekMester::elso_kovetkezik() const {
    return elso_jatekos_kovetkezik;
}
