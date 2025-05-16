#include "amobawidget.hpp"
#include "graphics.hpp"
#include <string>

using namespace genv;
using namespace std;

AmobaWidget::AmobaWidget(int meret, bool gepi_jatekos)
    : palya_meret(meret), gep(gepi_jatekos), mester(meret, gepi_jatekos),
      pont_X(0), pont_O(0), vege(false)
{
    cella_meret = 600 / palya_meret;
    width = palya_meret * cella_meret + 200;
    height = palya_meret * cella_meret + 100;
    gout.open(width, height);
}

void AmobaWidget::event_loop() {
    event ev;
    while (gin >> ev) {
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
    if (mester.van_nyertes(nyertes)) {
        vege = true;
        if (nyertes == Cell::X) {
            pont_X++;
            eredmeny_szoveg = "Player X won!";
        } else {
            pont_O++;
            eredmeny_szoveg = "Player O won!";
        }
    } else if (mester.dontetlen()) {
        vege = true;
        eredmeny_szoveg = "Draw!";
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
                 << box(cella_meret, cella_meret)
                 << move_to(px, py)
                 << color(0, 0, 0)
                 << line(0, cella_meret)
                 << line(cella_meret, 0)
                 << line(0, -cella_meret)
                 << line(-cella_meret, 0);

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
                 << color(0, 0, 255)
                 << dot;
        }
    }
}
            }
        }
    }

    gout << move_to(palya_meret * cella_meret + 10, 50)
         << color(0, 0, 0)
         << text("Next: ")
         << text(mester.elso_kovetkezik() ? "X (Red)" : "O (Blue)");

    gout << move_to(palya_meret * cella_meret + 10, 100)
         << text("Points:")
         << move_to(palya_meret * cella_meret + 10, 120)
         << text("X: " + to_string(pont_X))
         << move_to(palya_meret * cella_meret + 10, 140)
         << text("O: " + to_string(pont_O));

    if (vege) {
        gout << move_to(50, height - 70)
             << color(0, 0, 0)
             << text(eredmeny_szoveg);

        gout << move_to(50, height - 40)
             << color(200, 200, 200)
             << box(150, 30)
             << move_to(60, height - 20)
             << color(0, 0, 0)
             << text("New game");

        gout << move_to(250, height - 40)
             << color(200, 200, 200)
             << box(200, 30)
             << move_to(260, height - 20)
             << color(0, 0, 0)
             << text("Back to the mainmenu");
    }
}

void AmobaWidget::reset_jatek() {
    mester = JatekMester(palya_meret, gep);
    vege = false;
    eredmeny_szoveg = "";
}
