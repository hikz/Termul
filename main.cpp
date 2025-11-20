#include <ncurses.h>
#include <vector>
#include <string>
#include <iostream>
#include "src/ascii-art.h"
#include "src/manipData.h"
#include "src/ncursesHelper.h"
using namespace std;

int main()
{
    while (true)
    {
        vector<Item> dataItem;
        loadData(dataItem);
        vector<string> menu = {
            "1. Lihat Semua Data Barang",
            "2. Tambah jenis Barang",
            "3. Tambah Stok Barang",
            "4. Kurangi Stok Barang",
            "5. Edit harga Barang",
            "6. Edit Nama Barang",
            "7. Hapus Barang",
            "8. Keluar"};

        initscr();            // Start ncurses
        cbreak();             // langsung memasukan key tanpa enter
        noecho();             // untuk tidak memunculkan key di layar
        keypad(stdscr, TRUE); // untuk mengaktifkan key atas,bawah,kanan,kiri
        curs_set(0);          // mematikan cursor

        int menu_size = menu.size(); //menangkap banyaknya menu

        int highlight = 0; // menampilakn kotak warna
        int choice = -1; // untuk tidak menampilkan higligt

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

            int key = getch(); //untuk menggunakan atas,bawah,kiri,kanan

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

        if (choice == -1)  // tidak menapilkan higlight
        {
            mvprintw(2, 2, "Anda menekan Kembali/Batal.");
        }
        else
        {
            mvprintw(2, 2, "%s", ("Anda memilih: " + menu[choice]).c_str()); // menampilkan hightligh

            string selected = menu[choice];

            if (selected == "1. Lihat Semua Data Barang")
            {
                mvprintw(8, 2, "%s", dataTable(dataItem).c_str());
            }
            else if (selected == "2. Tambah jenis Barang")
            {
                int y = 8, x = 2;

                // kosongkan area prompt 
                for (int i = 0; i < 6; ++i)
                {
                    mvprintw(y + i, x, "%-80s", " ");
                }

                // Minta nama barang
                string namaBarang = nc_getstr(y, x, "Nama Barang : ", 50);
                if (namaBarang.empty())
                {
                    mvprintw(y + 4, x, "Dibatalkan: nama kosong.");
                    refresh();
                    getch();
                    continue;
                }

                // Minta harga awal barang sebagai integer
                auto [okHarga, hargaAwal] = nc_getint(y + 1, x, "Harga Awal Barang : ", 10);
                if (!okHarga)
                {
                    mvprintw(y + 4, x, "Input salah: harga harus angka.");
                    refresh();
                    getch();
                    continue;
                }

                tambahJenisBarang(dataItem, namaBarang, hargaAwal);
                saveData(dataItem);
                mvprintw(y + 3, x, "Berhasil menambahkan jenis barang: %s (Rp.%d)", namaBarang.c_str(), hargaAwal);
                refresh();
                getch();
            }

            else if (selected == "3. Tambah Stok Barang")
            {
                int y = 8, x = 2;

                // kosongkan area prompt 
                for (int i = 0; i < 6; ++i)
                {
                    mvprintw(y + i, x, "%-80s", " ");
                }

                // Minta nama barang
                string namaBarang = nc_getstr(y, x, "Nama Barang : ", 50);
                if (namaBarang.empty())
                {
                    mvprintw(y + 4, x, "Dibatalkan: nama kosong.");
                    refresh();
                    getch();
                    continue;
                }

                // Minta jumlah barang sebagai integer
                auto [okQty, tambahBarang] = nc_getint(y + 1, x, "Ingin ditambah berapa: ", 10);
                if (!okQty)
                {
                    mvprintw(y + 4, x, "Input salah: jumlah harus angka.");
                    refresh();
                    getch();
                    continue;
                }

                tambahStokBarang(dataItem, namaBarang, tambahBarang);
                saveData(dataItem);
                mvprintw(y + 3, x, "Berhasil menambahkan: %s (+%d)", namaBarang.c_str(), tambahBarang);
                refresh();
                getch(); 
            }
            else if (selected == "4. Kurangi Stok Barang")
            {
                int y = 8, x = 2;

                // kosongkan area prompt 
                for (int i = 0; i < 6; ++i)
                {
                    mvprintw(y + i, x, "%-80s", " ");
                }

                // Minta nama barang
                string namaBarang = nc_getstr(y, x, "Nama Barang : ", 50);
                if (namaBarang.empty())
                {
                    mvprintw(y + 4, x, "Dibatalkan: nama kosong.");
                    refresh();
                    getch();
                    continue;
                }

                // Minta jumlah barang sebagai integer
                auto [okQty, kurangiBarang] = nc_getint(y + 1, x, "Ingin dikurangi berapa: ", 10);
                if (!okQty)
                {
                    mvprintw(y + 4, x, "Input salah: harus angka.");
                    refresh();
                    getch();
                    continue;
                }

                kurangiStokBarang(dataItem, namaBarang, kurangiBarang);
                saveData(dataItem);
                mvprintw(y + 3, x, "Berhasil mengurangi: %s (-%d)", namaBarang.c_str(), kurangiBarang);
                refresh();
                getch();
            }
            else if (selected == "5. Edit harga Barang")
            {
                int y = 8, x = 2;

                // kosongkan area prompt 
                for (int i = 0; i < 6; ++i)
                {
                    mvprintw(y + i, x, "%-80s", " ");
                }

                // Minta nama barang
                string namaBarang = nc_getstr(y, x, "Nama Barang : ", 50);
                if (namaBarang.empty())
                {
                    mvprintw(y + 4, x, "Dibatalkan: nama kosong.");
                    refresh();
                    getch();
                    continue;
                }

                // Minta harga baru
                auto [okQty, hargaBaru] = nc_getint(y + 1, x, "Harga ingin dirubah menjadi berapa: ", 10);
                if (!okQty)
                {
                    mvprintw(y + 4, x, "Input salah: harga harus angka.");
                    refresh();
                    getch();
                    continue;
                }

                editHargaBarang(dataItem, namaBarang, hargaBaru);
                saveData(dataItem);
                mvprintw(y + 3, x, "Berhasil merubahi: %s (Rp.%d)", namaBarang.c_str(), hargaBaru);
                refresh();
                getch();
            }
            else if(selected == "6. Edit Nama Barang")
            {
                    int y = 8, x = 2;

                // kosongkan area prompt 
                for (int i = 0; i < 6; ++i)
                {
                    mvprintw(y + i, x, "%-80s", " ");
                }

                // Minta nama barang
                string namaBarang = nc_getstr(y, x, "Nama Barang : ", 50);
                if (namaBarang.empty())
                {
                    mvprintw(y + 4, x, "Dibatalkan: nama kosong.");
                    refresh();
                    getch();
                    continue;
                }

                // Minta nama barang baru
                auto namaBaru = nc_getstr(y + 1, x, "Nama barang ingin dirubah menjadi apa: ", 10);
                if (namaBaru.empty())
                {
                    mvprintw(y + 4, x, "Input salah: nama baru tidak boleh kosong.");
                    refresh();
                    getch();
                    continue;
                }

                editNamaBarang(dataItem, namaBarang, namaBaru);
                saveData(dataItem);
                mvprintw(y + 3, x, "Berhasil merubahi nama barang [%s] menjadi [%s]", namaBarang.c_str(), namaBaru.c_str());
                refresh();
                getch();
            }
            else if (selected == "7. Hapus Barang")
            {
                int y = 8, x = 2;

                // kosongkan area prompt 
                for (int i = 0; i < 6; ++i)
                {
                    mvprintw(y + i, x, "%-80s", " ");
                }

                // Minta nama barang
                string namaBarang = nc_getstr(y, x, "Nama Barang yang ingin dihapus: ", 50);
                if (namaBarang.empty())
                {
                    mvprintw(y + 4, x, "Dibatalkan: nama kosong.");
                    refresh();
                    getch();
                    continue;
                }

                hapusBarang(dataItem, namaBarang);
                saveData(dataItem);
                mvprintw(y + 3, x, "Berhasil menghapus barang: %s", namaBarang.c_str());
                refresh();
                getch();
            }
            else if (selected == "8. Keluar")
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
