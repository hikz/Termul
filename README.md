# Termul 📦

Sistem manajemen inventaris berbasis terminal yang dibangun dengan C++ dan ncurses, menampilkan menu interaktif untuk mengelola stok produk, harga, dan penyimpanan data.

## Fitur ✨

- *Lihat Semua Data Barang* - Tampilkan semua item dalam inventaris dengan detail
- *Tambah Jenis Barang* - Buat jenis produk baru dengan harga awal
- *Kelola Stok* - Tambah atau kurangi jumlah produk
- *Edit Harga Barang* - Perbarui harga produk
- *Edit Nama Barang* - Ubah nama produk yang ada
- *Hapus Barang* - Hapus item dari inventaris
- *Penyimpanan Data* - Semua perubahan otomatis disimpan ke disk
- *Antarmuka Interaktif* - Navigasi menggunakan tombol panah dan pilih dengan tombol panah

## Navigasi 🎮

- *↑ / ↓* - Navigasi menu item
- *→* - Pilih/Konfirmasi opsi
- *←* - Kembali/Batal

## Persyaratan 📋

- Kompiler C++ (g++)
- Library ncurses
- Sistem berbasis Linux/Unix (termasuk WSL di Windows)

## Membangun 🔨

Kompilasi proyek dengan dukungan ncurses:

bash
g++ main.cpp -o termul -lncurses


## Menjalankan 🚀

Jalankan file biner yang sudah dikompilasi:

bash
./termul


## Struktur Proyek 📁


Termul/
├── main.cpp              # Logika aplikasi utama dan menu
├── src/
│   ├── ascii-art.h       # Fungsi tampilan ASCII art
│   ├── manipData.h       # Manipulasi data dan input/output file
│   └── ncursesHelper.h   # Fungsi utilitas ncurses
├── data/
│   └── stuff.txt         # Penyimpanan data inventaris
└── README.md             # File ini


## Cara Kerja 🔄

1. Muat data inventaris dari data/stuff.txt
2. Tampilkan menu interaktif dengan 8 pilihan
3. Proses input pengguna menggunakan tombol panah dan pilihan
4. Lakukan operasi yang diminta pada inventaris
5. Simpan perubahan kembali ke file data
6. Kembali ke menu untuk operasi berikutnya

## Detail Teknis 💻

- *Bahasa*: C++
- *Library UI*: ncurses (antarmuka terminal)
- *Format Data*: Penyimpanan berbasis teks di data/stuff.txt
- *Sistem Menu*: Pemilihan interaktif berbasis keyboard

## Lisensi 📄

Proyek ini bersifat open source. Bebas digunakan, dimodifikasi, dan didistribusikan.

---

*Penulis*: hiroba, fajri, aldi, nia, pandu
*Repositori*: [Termul di GitHub](https://github.com/hikz/Termul)

