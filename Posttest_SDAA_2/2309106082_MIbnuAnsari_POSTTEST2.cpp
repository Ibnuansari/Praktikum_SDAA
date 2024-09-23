#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int max_tiket = 100;

struct Ticket {
    int id;
    string nama;
    string kategori;
    int harga;
};

void menuawal();
void inputNama(string& nama);
int pilihKategori();
int inputJumlahTiket();
void buatTiket(Ticket* tiket, int id, const string& nama, const string& kategori, int harga);
void tampilkanRingkasan(const Ticket* tiket, int jumlahTiket);

int main() {
    Ticket tiketArray[max_tiket];
    int jumlahTiket, pilihan, harga;
    string nama;
    string kategori;
    
    menuawal();
    
    inputNama(nama);
    
    pilihan = pilihKategori();
    
    switch (pilihan) {
        case 1:
            kategori = "Ekonomi";
            harga = 50000;
            break;
        case 2:
            kategori = "Tribun";
            harga = 100000;
            break;
        case 3:
            kategori = "VIP";
            harga = 150000;
            break;
        default:
            cout << "Pilihan tidak valid. Program berhenti." << endl;
            return 1;
    }
    
    jumlahTiket = inputJumlahTiket();
    
    for (int i = 0; i < jumlahTiket; i++) {
        buatTiket(&tiketArray[i], i+1, nama, kategori, harga);
    }
    
    tampilkanRingkasan(tiketArray, jumlahTiket);
    
    cout << "\nTekan enter untuk melanjutkan...";
    cin.ignore();
    cin.ignore();

    return 0;
}

void menuawal() {
    cout << "+--------------------------------------------+" << endl;
    cout << "|      Pemesanan Tiket Stadion Sepak Bola    |" << endl;
    cout << "+--------------------------------------------+" << endl;
    cout << "| Pertandingan: Borneo VS Persija            |" << endl;
    cout << "| Jadwal: Minggu,22-09-2024                  |" << endl;
    cout << "+--------------------------------------------+" << endl;
    cout << "| Pilih kategori tiket:                      |" << endl;
    cout << "| 1. Ekonomi (Rp 50.000)                     |" << endl;
    cout << "| 2. Tribun (Rp 100.000)                     |" << endl;
    cout << "| 3. VIP (Rp 150.000)                        |" << endl;
    cout << "+--------------------------------------------+" << endl;
}

void inputNama(string& nama) {
    cout << "Masukkan nama pemesan: ";
    getline(cin, nama);
}

int pilihKategori() {
    int pilihan;
    cout << "Masukkan pilihan Anda (1-3): ";
    cin >> pilihan;
    cin.ignore();
    return pilihan;
}

int inputJumlahTiket() {
    int jumlah;
    do {
        cout << "Masukkan jumlah tiket yang ingin dibeli: ";
        cin >> jumlah;
        if (jumlah <= 0) {
            cout << "Input tidak valid. Mohon masukkan angka positif." << endl;
        }
    } while (jumlah <= 0);
    return jumlah;
}

void buatTiket(Ticket* tiket, int id, const string& nama, const string& kategori, int harga) {
    tiket->id = id;
    tiket->nama = nama;
    tiket->kategori = kategori;
    tiket->harga = harga;
}

void tampilkanRingkasan(const Ticket* tiket, int jumlahTiket) {
    int totalHarga = tiket->harga * jumlahTiket;
    
    cout << "\n+--------------------------------------------+" << endl;
    cout << "|            Ringkasan Pemesanan             |" << endl;
    cout << "+--------------------------------------------+" << endl;
    
    for (int i = 0; i < jumlahTiket; i++) {
        cout << "| Tiket #" << tiket[i].id << " -ID: " << &tiket[i].id << "                 |" << endl;
    }
    
    cout << "+--------------------------------------------+" << endl;
    cout << "| Nama Pemesan   : " << setw(26) << left << tiket->nama << "|" << endl;
    cout << "| Tim Bertanding : Borneo VS Persija         |" << endl;
    cout << "| Jadwal         : Minggu,22-09-2024         |" << endl;
    cout << "| Kategori Tiket : " << setw(26) << left << tiket->kategori << "|" << endl;
    cout << "| Harga per Tiket: Rp " << setw(23) << left << tiket->harga << "|" << endl;
    cout << "+--------------------------------------------+" << endl;
    cout << "| Jumlah Tiket   :" << setw(26) << right << "x" << jumlahTiket << "|" << endl;
    cout << "| Total Harga    :" << setw(21) << right << "Rp " << totalHarga << "|" << endl;
    cout << "+--------------------------------------------+" << endl;
    
    cout << "\nTerima kasih telah memesan tiket!" << endl;
}
