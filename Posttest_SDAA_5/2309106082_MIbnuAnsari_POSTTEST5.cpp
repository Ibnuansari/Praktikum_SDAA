#include <iostream>
#include <iomanip>
#include <string>
#include<stdlib.h>

using namespace std;

// Struct untuk menyimpan informasi tiket
struct Tiket {
    int id;
    string nama;
    string kategori;
    int harga;
};

// Konstanta dan variabel untuk Stack dan Queue
const int MAX_SIZE = 100;
Tiket tickets[MAX_SIZE];
int top = -1;  // Untuk stack
int front = -1, rear = -1;  // Untuk queue

// Deklarasi fungsi
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
void displaySortedTickets(Tiket arr[], int size, string sortType);
void sortTicketsAscending();
void sortTicketsDescending();

// Fungsi untuk swap tiket
void swap(Tiket &a, Tiket &b) {
    Tiket temp = a;
    a = b;
    b = temp;
}

// Merge Sort (Ascending)
void merge(Tiket arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Tiket L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i].harga <= R[j].harga) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Rekursif Merge Sort
void mergeSort(Tiket arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// Quick Sort (Descending)
int partition(Tiket arr[], int low, int high) {
    int pivot = arr[high].harga;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].harga >= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Rekursif Quick Sort
void quickSort(Tiket arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Fungsi menampilkan hasil sorting
void displaySortedTickets(Tiket arr[], int size, string sortType) {
    cout << "\n+--------------------------------------------+" << endl;
    cout << "|        Urutan tiket (" << sortType << ")        |" << endl;
    cout << "+--------------------------------------------+" << endl;
    cout << "| ID | Nama           | Kategori | Harga     |" << endl;
    cout << "+--------------------------------------------+" << endl;

    for (int i = 0; i < size; i++) {
        cout << "| " << setw(2) << arr[i].id << " | "
            << setw(14) << arr[i].nama << " | "
            << setw(8) << arr[i].kategori << " | Rp "
            << setw(7) << arr[i].harga << " |" << endl;
    }
    cout << "+--------------------------------------------+" << endl;
}

// Sorting tiket secara ascending (Merge Sort)
void sortTicketsAscending() {
    int size = (top != -1) ? (top + 1) : (rear - front + 1);
    if (size > 0) {
        mergeSort(tickets, 0, size - 1);
        displaySortedTickets(tickets, size, "Ascending");
    } else {
        cout << "Tidak ada tiket untuk diurutkan." << endl;
    }
}

// Sorting tiket secara descending (Quick Sort)
void sortTicketsDescending() {
    int size = (top != -1) ? (top + 1) : (rear - front + 1);
    if (size > 0) {
        quickSort(tickets, 0, size - 1);
        displaySortedTickets(tickets, size, "Descending");
    } else {
        cout << "Tidak ada tiket untuk diurutkan." << endl;
    }
}

// Fungsi utama
int main() {
    int pilihan, idTiket = 0, harga;
    string nama, kategori;
    char lanjut;
    bool useStack = true;  // Default awal stack

    do {
        system("cls");
        cout << "+--------------------------------------------+" << endl;
        cout << "|      Pemesanan Tiket Stadion Sepak Bola    |" << endl;
        cout << "+--------------------------------------------+" << endl;
        cout << "| 1. Pesan Tiket                             |" << endl;
        cout << "| 2. Hapus Tiket                             |" << endl;
        cout << "| 3. Lihat Pesanan                           |" << endl;
        cout << "| 4. Ganti Mode (Stack/Queue)                |" << endl;
        cout << "| 5. Sort Tickets (Ascending)                |" << endl;
        cout << "| 6. Sort Tickets (Descending)               |" << endl;
        cout << "| 7. Keluar                                  |" << endl;
        cout << "+--------------------------------------------+" << endl;
        cout << "| Mode saat ini: " << (useStack ? "Stack" : "Queue") << " |" << endl;
        cout << "+--------------------------------------------+" << endl;

        cout << "\nMasukkan pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:  // Tambah Tiket
                system("cls");
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
                system("cls");
                hapusTiket(useStack);
                break;

            case 3:  // Tampilkan Ringkasan
                system("cls");
                tampilkanRingkasan(useStack);
                break;

            case 4:  // Ganti Mode
                useStack = !useStack;
                system("cls");
                cout << "Mode diubah ke " << (useStack ? "Stack" : "Queue") << endl;
                break;

            case 5:  // Sort Ascending
                system("cls");
                sortTicketsAscending();
                break;

            case 6:  // Sort Descending
                system("cls");
                sortTicketsDescending();
                break;
            case 7:  // Keluar
                system("cls");
                cout << "Keluar dari program." << endl;
                break;
            default:
                system("cls");
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }

        if (pilihan != 7) {
            cout << "\nApakah Anda ingin melanjutkan? (y/n): ";
            cin >> lanjut;
        }

    } while (pilihan != 7 && (lanjut == 'y' || lanjut == 'Y'));

    return 0;
}

// Fungsi menampilkan menu kategori tiket
void tampilkanMenu() {
    cout << "+--------------------------------------------+" << endl;
    cout << "|      Pemesanan Tiket Stadion Sepak Bola    |" << endl;
    cout << "+--------------------------------------------+" << endl;
    cout << "| Pertandingan: Borneo VS Persija            |" << endl;
    cout << "| Jadwal: Minggu, 22-09-2024                 |" << endl;
    cout << "+--------------------------------------------+" << endl;
    cout << "| Pilih kategori tiket:                      |" << endl;
    cout << "| 1. Ekonomi   - Rp 50.000                   |" << endl;
    cout << "| 2. Tribun    - Rp 100.000                  |" << endl;
    cout << "| 3. VIP       - Rp 150.000                  |" << endl;
    cout << "+--------------------------------------------+" << endl;
}

// Fungsi input nama
void masukkanNama(string& nama) {
    cout << "Masukkan nama Anda: ";
    cin.ignore();
    getline(cin, nama);
}

// Fungsi input pilihan kategori tiket
int pilihKategori() {
    int kategori;
    cout << "Masukkan pilihan kategori (1/2/3): ";
    cin >> kategori;
    return kategori;
}

// Fungsi untuk menambah tiket (Stack)
void push(int id, const string& nama, const string& kategori, int harga) {
    if (!isFull()) {
        top++;
        tickets[top].id = id;
        tickets[top].nama = nama;
        tickets[top].kategori = kategori;
        tickets[top].harga = harga;
    }
}

// Fungsi untuk menghapus tiket (Stack)
void pop() {
    if (!isEmpty()) {
        top--;
    }
}

// Fungsi untuk menambah tiket (Queue)
void enqueue(int id, const string& nama, const string& kategori, int harga) {
    if (!isFull()) {
        if (front == -1) front = 0;
        rear++;
        tickets[rear].id = id;
        tickets[rear].nama = nama;
        tickets[rear].kategori = kategori;
        tickets[rear].harga = harga;
    }
}

// Fungsi untuk menghapus tiket (Queue)
void dequeue() {
    if (!isEmpty()) {
        front++;
        if (front > rear) front = rear = -1;
    }
}

// Fungsi menampilkan ringkasan tiket
void tampilkanRingkasan(bool isStack) {
    if (!isEmpty()) {
        cout << "+--------------------------------------------+" << endl;
        cout << "|           Ringkasan Tiket Pesanan          |" << endl;
        cout << "+--------------------------------------------+" << endl;
        cout << "| ID | Nama           | Kategori | Harga     |" << endl;
        cout << "+--------------------------------------------+" << endl;

        if (isStack) {
            for (int i = top; i >= 0; i--) {
                cout << "| " << setw(2) << tickets[i].id << " | "
                    << setw(14) << tickets[i].nama << " | "
                    << setw(8) << tickets[i].kategori << " | Rp "
                    << setw(7) << tickets[i].harga << " |" << endl;
            }
        } else {
            for (int i = front; i <= rear; i++) {
                cout << "| " << setw(2) << tickets[i].id << " | "
                    << setw(14) << tickets[i].nama << " | "
                    << setw(8) << tickets[i].kategori << " | Rp "
                    << setw(7) << tickets[i].harga << " |" << endl;
            }
        }

        cout << "+--------------------------------------------+" << endl;
    } else {
        cout << "Tidak ada tiket yang dipesan." << endl;
    }
}

// Fungsi mengecek apakah penyimpanan tiket penuh
bool isFull() {
    return (top == MAX_SIZE - 1 || rear == MAX_SIZE - 1);
}

// Fungsi mengecek apakah penyimpanan tiket kosong
bool isEmpty() {
    return (top == -1 && front == -1);
}

// Fungsi untuk menghapus tiket (dari Stack atau Queue)
void hapusTiket(bool isStack) {
    if (!isEmpty()) {
        if (isStack) {
            pop();
            cout << "Tiket berhasil dihapus (Stack)." << endl;
        } else {
            dequeue();
            cout << "Tiket berhasil dihapus (Queue)." << endl;
        }
    } else {
        cout << "Tidak ada tiket yang bisa dihapus." << endl;
    }
}
