#include <ncurses.h>
#include <vector>
#include <string>
#include <iostream>
#include "src/ascii-art.h"
#include "src/manipData.h"
using namespace std;

int main()
{
    while (true)
    {
        vector<Item> dataItem;
        loadData(dataItem);
        vector<string> menu = {
            "1. Lihat Semua Data Barang",
            "2. Tambah Barang",
            "3. Kurangi Barang",
            "4. Edit Data Barang",
            "5. Hapus Data Barang",
            "6. Keluar"};

        initscr();            // Start ncurses
        cbreak();             // Disable line buffering
        noecho();             // Don't echo pressed keys
        keypad(stdscr, TRUE); // Enable arrow keys
        curs_set(0);          // Hide cursor$1

        int menu_size = menu.size();

        int highlight = 0;
        int choice = -1;

        while (true)
        {
            clear();
            mvprintw(0, 2, "%s", helloTermulArt().c_str());
            mvprintw(15, 2, "=== TERMUL MENU ===");

            for (int i = 0; i < menu_size; i++)
            {
                if (i == highlight)
                {
                    attron(A_REVERSE);
                    mvprintw(i + 16, 4, "%s", menu[i].c_str());
                    attroff(A_REVERSE);
                }
                else
                {
                    mvprintw(i + 16, 4, "%s", menu[i].c_str());
                }
            }

            int key = getch();

            if (key == KEY_UP)
            {
                highlight--;
                if (highlight < 0)
                    highlight = menu_size - 1;
            }
            else if (key == KEY_DOWN)
            {
                highlight++;
                if (highlight >= menu_size)
                    highlight = 0;
            }
            else if (key == KEY_RIGHT)
            {
                choice = highlight; // OK / Select
                break;
            }
            else if (key == KEY_LEFT)
            {
                choice = -1; // Back / Cancel
                break;
            }
        }

        clear();

        if (choice == -1)
        {
            mvprintw(2, 2, "Anda menekan Kembali/Batal.");
        }
        else
        {
            mvprintw(2, 2, "%s", ("Anda memilih: " + menu[choice]).c_str());

            string selected = menu[choice];

            if (selected == "1. Lihat Semua Data Barang")
            {
                mvprintw(8, 2, "%s", dataTable(dataItem).c_str());
            }
            else if (selected == "2. Tambah Barang")
            {
                mvprintw(8, 2, "Fungsi: Menambahkan barang");
            }
            else if (selected == "3. Kurangi Barang")
            {
                mvprintw(8, 2, "Fungsi: Mengurangi jumlah stok barang.");
            }
            else if (selected == "4. Edit Data Barang")
            {
                mvprintw(8, 2, "Fungsi: Mengedit informasi barang.");
            }
            else if (selected == "5. Hapus Data Barang")
            {
                mvprintw(8, 2, "]Fungsi: Menghapus barang dari daftar.");
            }
            else if (selected == "6. Keluar")
            {
                return 0;
            }
            else
            {
                mvprintw(4, 2, "Menu tidak dikenali.");
            }
        }

        mvprintw(4, 2, "Tekan apapun untuk keluar...");
        getch();

        endwin(); // End ncurses
    }
    return 0;
}
// hai
