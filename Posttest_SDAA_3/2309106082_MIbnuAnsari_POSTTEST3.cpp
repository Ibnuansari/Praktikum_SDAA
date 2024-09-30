#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct Tiket {
    int id;
    string nama;
    string kategori;
    int harga;
    Tiket* berikutnya;
};

void tampilkanMenu();
void masukkanNama(string& nama);
int pilihKategori();
int masukkanJumlahTiket();
void buatTiket(Tiket*& head, int id, const string& nama, const string& kategori, int harga);
void tampilkanRingkasan(const Tiket* head, int jumlahTiket);
void bebaskanMemori(Tiket* head);

int main() {
    Tiket* head = nullptr;
    int jumlahTiket, pilihan, harga;
    string nama;
    string kategori;
    
    tampilkanMenu();
    
    masukkanNama(nama);
    
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
    
    jumlahTiket = masukkanJumlahTiket();
    
    for (int i = 0; i < jumlahTiket; i++) {
        buatTiket(head, i+1, nama, kategori, harga);
    }
    
    tampilkanRingkasan(head, jumlahTiket);
    
    bebaskanMemori(head);
    
    cout << "\nTekan enter untuk melanjutkan...";
    cin.ignore();
    cin.get();

    return 0;
}

void tampilkanMenu() {
    cout << "+--------------------------------------------+" << endl;
    cout << "|      Pemesanan Tiket Stadion Sepak Bola    |" << endl;
    cout << "+--------------------------------------------+" << endl;
    cout << "| Pertandingan: Borneo VS Persija            |" << endl;
    cout << "| Jadwal: Minggu, 22-09-2024                 |" << endl;
    cout << "+--------------------------------------------+" << endl;
    cout << "| Pilih kategori tiket:                      |" << endl;
    cout << "| 1. Ekonomi (Rp 50.000)                     |" << endl;
    cout << "| 2. Tribun (Rp 100.000)                     |" << endl;
    cout << "| 3. VIP (Rp 150.000)                        |" << endl;
    cout << "+--------------------------------------------+" << endl;
}

void masukkanNama(string& nama) {
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

int masukkanJumlahTiket() {
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

void buatTiket(Tiket*& head, int id, const string& nama, const string& kategori, int harga) {
    Tiket* tiketBaru = new Tiket;
    tiketBaru->id = id;
    tiketBaru->nama = nama;
    tiketBaru->kategori = kategori;
    tiketBaru->harga = harga;
    tiketBaru->berikutnya = nullptr;

    if (head == nullptr) {
        head = tiketBaru;
    } else {
        Tiket* current = head;
        while (current->berikutnya != nullptr) {
            current = current->berikutnya;
        }
        current->berikutnya = tiketBaru;
    }
}

void tampilkanRingkasan(const Tiket* head, int jumlahTiket) {
    int totalHarga = head->harga * jumlahTiket;
    
    cout << "\n+--------------------------------------------+" << endl;
    cout << "|            Ringkasan Pemesanan             |" << endl;
    cout << "+--------------------------------------------+" << endl;
    
    const Tiket* current = head;
    while (current != nullptr) {
        cout << "| Tiket #" << current->id << " -ID: " << &(current->id) << "                 |" << endl;
        current = current->berikutnya;
    }
    
    cout << "+--------------------------------------------+" << endl;
    cout << "| Nama Pemesan   : " << setw(26) << left << head->nama << "|" << endl;
    cout << "| Tim Bertanding : Borneo VS Persija         |" << endl;
    cout << "| Jadwal         : Minggu, 22-09-2024        |" << endl;
    cout << "| Kategori Tiket : " << setw(26) << left << head->kategori << "|" << endl;
    cout << "| Harga per Tiket: Rp " << setw(23) << left << head->harga << "|" << endl;
    cout << "+--------------------------------------------+" << endl;
    cout << "| Jumlah Tiket   :" << setw(26) << right << "x" << jumlahTiket << "|" << endl;
    cout << "| Total Harga    :" << setw(21) << right << "Rp " << totalHarga << "|" << endl;
    cout << "+--------------------------------------------+" << endl;
    
    cout << "\nTerima kasih telah memesan tiket!" << endl;
}

void bebaskanMemori(Tiket* head) {
    while (head != nullptr) {
        Tiket* temp = head;
        head = head->berikutnya;
        delete temp;
    }
}