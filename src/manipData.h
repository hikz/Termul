#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

struct Item {
    string nama;
    int qty;
    int harga;
};

bool loadData(vector<Item> &daftar, const string &filename = "data/stuff.txt") {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Gagal membuka file: " << filename << endl;
        return false;
    }

    daftar.clear(); // pastikan kosong sebelum load

    Item temp;
    while (file >> temp.nama >> temp.qty >> temp.harga) {
        daftar.push_back(temp);
    }

    file.close();
    return true;
}

string dataTable(const vector<Item> &dataItem)
{
    if (dataItem.empty())
        return "Data kosong.\n";

    stringstream ss;

    // Header kolom
    ss << left
       << setw(15) << "Nama Barang"
       << setw(10) << "Qty"
        << setw(10) << "Harga"
       << "\n";

    ss << string(35, '-') << "\n";

    // Isi data
    for (const auto &b : dataItem)
    {
        ss << left
           << setw(15) << b.nama
           << setw(10) << b.qty
           << setw(10) << b.harga
           << "\n";
    }

    return ss.str();
}

bool saveData(const vector<Item> &dataItem, const string &filename = "data/stuff.txt")
{
    ofstream file(filename); // tulis ulang file

    if (!file.is_open())
        return false;

    for (const auto &item : dataItem)
    {
        file << item.nama << " "
             << item.qty << " "
             << item.harga << "\n";
    }

    file.close();
    return true;
}

bool tambahJenisBarang(vector<Item> &daftar, const string &namaBarang, int hargaAwal) {
    // Cek apakah barang sudah ada
    for (const auto &item : daftar) {
        if (item.nama == namaBarang) {
            return false; // Barang sudah ada
        }
    }

    // Tambah barang baru dengan qty 0
    Item baru;
    baru.nama = namaBarang;
    baru.qty = 0;
    baru.harga = hargaAwal;
    daftar.push_back(baru);
    return true;
}


bool tambahStokBarang(vector<Item> &daftar, const string &namaBarang, int jumlahTambah) {
    // Tidak boleh input negatif
    if (jumlahTambah < 0) {
        return false;
    }

    // Cari barang berdasarkan nama
    for (auto &item : daftar) {
        if (item.nama == namaBarang) {
            item.qty += jumlahTambah;   // Tambah stok
            return true;                 // Berhasil
        }
    }

    return false; // Barang tidak ditemukan
}


bool kurangiStokBarang(vector<Item> &daftar, const string &namaBarang, int jumlahKurang){
     // Tidak boleh input negatif
    if (jumlahKurang < 0) {
        return false;
    }

    // Cari barang berdasarkan nama
    for (auto &item : daftar) {
        if (item.nama == namaBarang) {
            // Cek apakah stok cukup
            if (item.qty >= jumlahKurang) {
                item.qty -= jumlahKurang;   // Kurangi stok
                return true;                 // Berhasil
            } else {
                return false; // Stok tidak cukup
            }
        }
    }
    return false; // Barang tidak ditemukan
}

bool editHargaBarang(vector<Item> &daftar, const string &namaBarang, int hargaBaru){
    // hargaBaru harus > 0.

    // Jika barang ditemukan → ubah field harga.

    // Kembalikan false jika tidak ditemukan.
};

bool editNamaBarang(vector<Item> &daftar, const string &namaLama, const string &namaBaru){
    // Pastikan tidak ada item lain yang memiliki namaBaru.

    // Tidak boleh namaBaru kosong.

    // Jika namaLama tidak ditemukan → return false.
};

bool hapusBarang(vector<Item> &daftar, const string &namaBarang){
    // Cari berdasarkan nama.

    // Jika ketemu → hapus menggunakan erase.

    // Jika tidak → return false.
};