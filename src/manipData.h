#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

struct Item {  // struktur data yang akan muncul
    string nama;
    int qty;
    int harga;
};

bool loadData(vector<Item> &daftar, const string &filename = "data/stuff.txt") {  // load data akan menggambil semua data yang ada di txt lalu kirim ke vektor
    ifstream file(filename);
    if (!file.is_open()) {   // membuka file
        cerr << "Gagal membuka file: " << filename << endl; // jika gagal maka code berhenti
        return false;
    }

    daftar.clear(); // pastikan kosong sebelum load

    Item temp;
    while (file >> temp.nama >> temp.qty >> temp.harga) { // jika berhasil data akan di kirimkan ke code menu lain
        daftar.push_back(temp);
    }

    file.close(); //menutup file
    return true;
}

string dataTable(const vector<Item> &dataItem)  //mengambil semua data yang ada di vektor / stuf txt
{
    if (dataItem.empty())  // jika di dalam data kosong,maka akan muncul "data kosong"
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
    for (const auto &b : dataItem)  // jika berhasil akan di print/ditampilkan menggunakan forloop
    {
        ss << left
           << setw(15) << b.nama
           << setw(10) << b.qty
           << setw(10) << b.harga
           << "\n";
    }

    return ss.str();
}

bool saveData(const vector<Item> &dataItem, const string &filename = "data/stuff.txt") // menyimpan data yang di manipulasi dari tambahjenisbarang
{
    ofstream file(filename); // tulis ulang file

    if (!file.is_open()) //membuka file,jika gagal maka progam berhenti
        return false;

    for (const auto &item : dataItem)  //jika berhasil maka tersimpan di dalam file menggunakan forloop
    {
        file << item.nama << " "
             << item.qty << " "
             << item.harga << "\n";
    }

    file.close(); // menutup file
    return true;
}

bool tambahJenisBarang(vector<Item> &daftar, const string &namaBarang, int hargaAwal) { //mengambil semua data yang ada di vektor
    // Cek apakah barang sudah ada
    for (const auto &item : daftar) {  //forloop untuk memasukan/daftarkan data
        if (item.nama == namaBarang) {  //memasukan nama barang
            return false; // jika barang sudah ada maka progam berhenti
        }
    }

    // Tambah barang baru dengan qty 0
    // jika barang belum ada maka lanjut ke harga barang,lalu push dan tutup.otomatis akan tersimpan karena ada data save
    Item baru;
    baru.nama = namaBarang;
    baru.qty = 0;
    baru.harga = hargaAwal;
    daftar.push_back(baru);
    return true;
}

bool editHargaBarang(vector<Item> &daftar, const string &namaBarang, int hargaBaru){  
    // hargaBaru harus > 0.
    if (hargaBaru < 0) {
        return false;
    }

    // Jika barang ditemukan → ubah field harga.
    for (auto &item : daftar) {
        if (item.nama == namaBarang) { // nama stocknya
            item.harga = hargaBaru; //mauskan jumlah stock
            return true; // Berhasil
        }
    }
     // Kembalikan false jika tidak ditemukan.
    return false;
};


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
    if (hargaBaru < 0) {
        return false;
    }

    // Jika barang ditemukan → ubah field harga.
    for (auto &item : daftar) {
        if (item.nama == namaBarang) {
            item.harga = hargaBaru;
            return true; // Berhasil
        }
    }
     // Kembalikan false jika tidak ditemukan.
    return false;
};

bool editNamaBarang(vector<Item> &daftar, const string &namaLama, const string &namaBaru){
    // Pastikan tidak ada item lain yang memiliki namaBaru.
    for (const auto &item : daftar) {
        if (item.nama == namaBaru) {
            return false; // Nama baru sudah ada
        }
    }

    // Tidak boleh namaBaru kosong.
    if (namaBaru.empty()) {
        return false;
    }

    // Jika namaLama tidak ditemukan → return false.
    for (auto &item : daftar) {
        if (item.nama == namaLama) {
            item.nama = namaBaru;
            return true; // Berhasil
        }
    }
    return false; // Nama lama tidak ditemukan
};

bool hapusBarang(vector<Item> &daftar, const string &namaBarang){
    // Cari berdasarkan nama. Ketemu → hapus dari vector.
    for (auto it = daftar.begin(); it != daftar.end(); ++it) {
        if (it->nama == namaBarang) {
            daftar.erase(it);
            return true; // Berhasil dihapus
        }
    }    

    // Jika tidak → return false.
    return false;
};
