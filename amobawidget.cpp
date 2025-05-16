#include "amobawidget.hpp"
#include "graphics.hpp"

using namespace genv;
using namespace std;

AmobaWidget::AmobaWidget(int meret, bool gepi_jatekos)
    : palya_meret(meret), gep(gepi_jatekos), mester(meret, gepi_jatekos),
      pont_X(0), pont_O(0), vege(false)
{
    cella_meret = 600 / palya_meret;
    width = palya_meret * cella_meret + 300;
    height = palya_meret * cella_meret + 100;
}

void AmobaWidget::event_loop() {
    event ev;
    while (gin >> ev) {
        if (ev.keycode == key_escape) exit(0);
        if (ev.type == ev_mouse && ev.button == btn_left && !vege) {
            int oszlop = ev.pos_x / cella_meret;
            int sor = ev.pos_y / cella_meret;
            if (oszlop < palya_meret && sor < palya_meret) {
                lepes(sor, oszlop);
            }
        }

        if (ev.type == ev_mouse && ev.button == btn_left && vege) {
            if (ev.pos_x >= 50 && ev.pos_x <= 200 && ev.pos_y >= height - 40 && ev.pos_y <= height - 10) {
                reset_jatek();
            }
            if (ev.pos_x >= 250 && ev.pos_x <= 450 && ev.pos_y >= height - 40 && ev.pos_y <= height - 10) {
                break;
            }
        }

        rajzol();
        gout << refresh;
    }
}

void AmobaWidget::lepes(int sor, int oszlop) {
    if (!mester.lep(oszlop, sor)) return;

    Cell nyertes;
    vector<pair<int,int>> pontok;
    if (mester.van_nyertes(nyertes, pontok)) {
        vege = true;
        gyoztes_pontok = pontok;
        if (nyertes == Cell::X) pont_X++, eredmeny_szoveg = "Játékos X nyert!";
        else pont_O++, eredmeny_szoveg = gep ? "Gép nyert!" : "Játékos O nyert!";
        return;
    } else if (mester.dontetlen()) {
        vege = true;
        eredmeny_szoveg = "Döntetlen!";
        return;
    }

    if (gep && !mester.elso_kovetkezik()) {
        mester.gep_lep();
        if (mester.van_nyertes(nyertes, pontok)) {
            vege = true;
            gyoztes_pontok = pontok;
            if (nyertes == Cell::X) pont_X++, eredmeny_szoveg = "Játékos X nyert!";
            else pont_O++, eredmeny_szoveg = "Gép nyert!";
        } else if (mester.dontetlen()) {
            vege = true;
            eredmeny_szoveg = "Döntetlen!";
        }
    }
}

void AmobaWidget::rajzol() const {
    gout << move_to(0, 0) << color(255, 255, 255) << box(width, height);
    auto tabla = mester.get_tabla();
    for (int y = 0; y < palya_meret; ++y) {
        for (int x = 0; x < palya_meret; ++x) {
            int px = x * cella_meret;
            int py = y * cella_meret;

            gout << move_to(px, py)
                 << color(200, 200, 200)
                 << box(cella_meret, cella_meret);

            gout << move_to(px, py)
             << color(0, 0, 0)
             << line(cella_meret, 0)
             << line(0, cella_meret)
             << line(-cella_meret, 0)
             << line(0, -cella_meret);

            if (tabla[y][x] == Cell::X) {
                gout << move_to(px + 5, py + 5)
                     << color(255, 0, 0)
                     << line(cella_meret - 10, cella_meret - 10)
                     << move_to(px + 5, py + cella_meret - 5)
                     << line(cella_meret - 10, -cella_meret + 10);
            } else if (tabla[y][x] == Cell::O) {
                    int cx = px + cella_meret / 2;
                    int cy = py + cella_meret / 2;
                    int r = cella_meret / 3;
                    for (int dx = -r; dx <= r; ++dx) {
                        for (int dy = -r; dy <= r; ++dy) {
                            if (dx*dx + dy*dy <= r*r) {
                                gout << move_to(cx + dx, cy + dy)
                                << color(0, 0, 200) << dot;
                                }
                            if (dx*dx + dy*dy <= (r - 2)*(r - 2)) {
                                gout << move_to(cx + dx, cy + dy)
                                << color(200, 200, 200) << dot;
                                }
                            }
                        }
                    }
        }
    }

    for (const auto& p : gyoztes_pontok) {
        int gx = p.first * cella_meret;
        int gy = p.second * cella_meret;
        gout << move_to(gx, gy)
             << color(0, 200, 0)
             << line(cella_meret, 0)
             << line(0, cella_meret)
             << line(-cella_meret, 0)
             << line(0, -cella_meret);
    }

    int infoX = palya_meret * cella_meret + 15;
    gout << move_to(infoX, 50) << color(0, 0, 0)
         << text("Kovetkezo: ")
         << text(mester.elso_kovetkezik() ? "X (piros)" : "O (kek)");

    gout << move_to(infoX, 100)
         << text("Pontszamok:");

    gout << move_to(infoX, 120)
         << text("X: " + to_string(pont_X));

    gout << move_to(infoX, 140)
         << text("O: " + to_string(pont_O));

    if (vege) {
        gout << move_to(infoX, 170)
             << text(eredmeny_szoveg);

        gout << move_to(50, height - 40)
             << color(200, 200, 200)
             << box(150, 30)
             << move_to(95, height - 20)
             << color(0, 0, 0)
             << text("Uj játék");

        gout << move_to(250, height - 40)
             << color(200, 200, 200)
             << box(210, 30)
             << move_to(260, height - 20)
             << color(0, 0, 0)
             << text("Vissza a kezdõképernyõre");
    }
}

void AmobaWidget::reset_jatek() {
    mester = JatekMester(palya_meret, gep);
    vege = false;
    eredmeny_szoveg = "";
    gyoztes_pontok.clear();
}
