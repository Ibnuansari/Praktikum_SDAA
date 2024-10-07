#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct Tiket {
    int id;
    string nama;
    string kategori;
    int harga;
};

const int MAX_SIZE = 100;
Tiket tickets[MAX_SIZE];
int top = -1;  // For stack
int front = -1, rear = -1;  // For queue

void tampilkanMenu();
void masukkanNama(string& nama);
int pilihKategori();
void push(int id, const string& nama, const string& kategori, int harga);
void pop();
void enqueue(int id, const string& nama, const string& kategori, int harga);
void dequeue();
void tampilkanRingkasan(bool isStack);
bool isFull();
bool isEmpty();
void hapusTiket(bool isStack);

int main() {
    int pilihan, idTiket = 0, harga;
    string nama, kategori;
    char lanjut;
    bool useStack = true;  // Default to stack

    do {
        cout << "+--------------------------------------------+" << endl;
        cout << "|      Pemesanan Tiket Stadion Sepak Bola    |" << endl;
        cout << "+--------------------------------------------+" << endl;
        cout << "| 1. Pesan Tiket                             |" << endl;
        cout << "| 2. Hapus Tiket                             |" << endl;
        cout << "| 3. Lihat Pesanan                           |" << endl;
        cout << "| 4. Ganti Mode (Stack/Queue)                |" << endl;
        cout << "| 5. Keluar                                  |" << endl;
        cout << "+--------------------------------------------+" << endl;
        cout << "| Mode saat ini: " << (useStack ? "Stack" : "Queue") << " |" << endl;
        cout << "+--------------------------------------------+" << endl;

        cout << "\nMasukkan pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:  // Tambah Tiket
                tampilkanMenu();
                masukkanNama(nama);
                pilihan = pilihKategori();

                switch (pilihan) {
                    case 1: kategori = "Ekonomi"; harga = 50000; break;
                    case 2: kategori = "Tribun"; harga = 100000; break;
                    case 3: kategori = "VIP"; harga = 150000; break;
                    default: cout << "Pilihan tidak valid." << endl; continue;
                }

                if (!isFull()) {
                    idTiket++;
                    if (useStack) {
                        push(idTiket, nama, kategori, harga);
                    } else {
                        enqueue(idTiket, nama, kategori, harga);
                    }
                    cout << "Tiket berhasil ditambahkan." << endl;
                } else {
                    cout << "Penyimpanan penuh! Tidak bisa menambah tiket." << endl;
                }
                break;

            case 2:  // Hapus Tiket
                hapusTiket(useStack);
                break;

            case 3:  // Tampilkan Ringkasan
                tampilkanRingkasan(useStack);
                break;

            case 4:  // Ganti Mode
                useStack = !useStack;
                cout << "Mode diubah ke " << (useStack ? "Stack" : "Queue") << endl;
                break;

            case 5:  // Keluar
                cout << "Keluar dari program." << endl;
                break;

            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }

        if (pilihan != 5) {
            cout << "\nApakah Anda ingin melanjutkan? (y/n): ";
            cin >> lanjut;
        }

    } while (pilihan != 5 && (lanjut == 'y' || lanjut == 'Y'));

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
    cin.ignore();
    getline(cin, nama);
}

int pilihKategori() {
    int pilihan;
    cout << "Masukkan pilihan kategori (1-3): ";
    cin >> pilihan;
    return pilihan;
}

void push(int id, const string& nama, const string& kategori, int harga) {
    top++;
    tickets[top] = {id, nama, kategori, harga};
}

void pop() {
    if (!isEmpty()) {
        cout << "Menghapus tiket terakhir yang dipesan oleh: " << tickets[top].nama << endl;
        top--;
    } else {
        cout << "Stack kosong! Tidak ada tiket untuk dihapus." << endl;
    }
}

void enqueue(int id, const string& nama, const string& kategori, int harga) {
    if (front == -1) front = 0;
    rear++;
    tickets[rear] = {id, nama, kategori, harga};
}

void dequeue() {
    if (!isEmpty()) {
        cout << "Menghapus tiket pertama yang dipesan oleh: " << tickets[front].nama << endl;
        if (front == rear) {
            front = rear = -1;
        } else {
            front++;
        }
    } else {
        cout << "Queue kosong! Tidak ada tiket untuk dihapus." << endl;
    }
}

void tampilkanRingkasan(bool isStack) {
    if (isEmpty()) {
        cout << "Tidak ada tiket yang dipesan." << endl;
        return;
    }

    int totalHarga = 0;
    int start = isStack ? top : front;
    int end = isStack ? 0 : rear;

    cout << "\n+--------------------------------------------+" << endl;
    cout << "|            Ringkasan Pemesanan             |" << endl;
    cout << "+--------------------------------------------+" << endl;
    cout << "| Pertandingan: Borneo VS Persija            |" << endl;
    cout << "| Jadwal: Minggu, 22-09-2024                 |" << endl;
    cout << "+--------------------------------------------+" << endl;

    if (isStack) {
        for (int i = start; i >= end; i--) {
            totalHarga += tickets[i].harga;
            cout << "| Tiket #" << tickets[i].id << " - Nama: " << tickets[i].nama << "                 |" << endl;
        }
    } else {
        for (int i = start; i <= end; i++) {
            totalHarga += tickets[i].harga;
            cout << "| Tiket #" << tickets[i].id << " - Nama: " << tickets[i].nama << "                 |" << endl;
        }
    }

    cout << "+--------------------------------------------+" << endl;
    cout << "| Total Tiket: " << (isStack ? top + 1 : rear - front + 1) << endl;
    cout << "| Total Harga: Rp " << totalHarga << endl;
    cout << "+--------------------------------------------+" << endl;
}

bool isFull() {
    return top == MAX_SIZE - 1 || rear == MAX_SIZE - 1;
}

bool isEmpty() {
    return (top == -1) && (front == -1);
}

void hapusTiket(bool isStack) {
    if (!isEmpty()) {
        if (isStack) {
            cout << "\nMenghapus tiket terakhir dengan nama pemesan: " << tickets[top].nama << endl;
            pop();
        } else {
            cout << "\nMenghapus tiket pertama dengan nama pemesan: " << tickets[front].nama << endl;
            dequeue();
        }
    } else {
        cout << "Tidak ada tiket yang bisa dihapus." << endl;
    }
}