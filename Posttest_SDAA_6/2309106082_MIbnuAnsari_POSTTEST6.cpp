#include <iostream>
#include <iomanip>
#include <string>
#include<stdlib.h>
#include <cmath>  // Untuk fungsi sqrt
#include <cctype>  // Untuk fungsi tolower
#include <vector>

using namespace std;

// Struct untuk menyimpan informasi tiket
struct Tiket {
    int id;
    string nama;
    string kategori;
    int harga;
};

// Variabel global untuk menyimpan tiket
vector<Tiket> tiketList;
int idTiket = 0;  // Global ID tiket

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
void menusorting();
void menuUtama();

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

int fibonacciSearch(Tiket arr[], int id, int size) {
    int fib2 = 0;  // (m-2)'th Fibonacci No.
    int fib1 = 1;  // (m-1)'th Fibonacci No.
    int fib = fib2 + fib1;  // m'th Fibonacci No.

    // fib is going to store the smallest Fibonacci Number >= size
    while (fib < size) {
        fib2 = fib1;
        fib1 = fib;
        fib = fib2 + fib1;
    }

    // Marks the eliminated range from front
    int offset = -1;

    // While there are elements to be inspected
    while (fib > 1) {
        // Check if fib2 is a valid location
        int i = min(offset + fib2, size - 1);

        // If ID is greater, cut the subarray from offset to i
        if (arr[i].id < id) {
            fib = fib1;
            fib1 = fib2;
            fib2 = fib - fib1;
            offset = i;
        }
        // If ID is smaller, cut the subarray after i+1
        else if (arr[i].id > id) {
            fib = fib2;
            fib1 = fib1 - fib2;
            fib2 = fib - fib1;
        }
        // Element found
        else return i;
    }

    // Comparing the last element with the ID
    if (fib1 && arr[offset + 1].id == id) return offset + 1;

    return -1;  // ID not found
}

int jumpSearch(Tiket arr[], int id, int size) {
    int step = sqrt(size);
    int prev = 0;

    // Finding the block where element is present
    while (arr[min(step, size) - 1].id < id) {
        prev = step;
        step += sqrt(size);
        if (prev >= size) return -1;
    }

    // Doing a linear search in the identified block
    while (arr[prev].id < id) {
        prev++;
        if (prev == min(step, size)) return -1;
    }

    // If element is found
    if (arr[prev].id == id) return prev;

    return -1;
}

// Fungsi untuk mengubah string menjadi lowercase
string toLowerCase(const string& str) {
    string lowerStr = str;
    for (int i = 0; i < lowerStr.size(); i++) {
        lowerStr[i] = tolower(lowerStr[i]);
    }
    return lowerStr;
}

int boyerMooreSearch(const string& text, const string& pattern) {
    // Mengubah teks dan pola menjadi lowercase untuk case-insensitive search
    string lowerText = toLowerCase(text);
    string lowerPattern = toLowerCase(pattern);

    int m = lowerPattern.size();
    int n = lowerText.size();

    if (m > n) return -1;

    // Bad character heuristic
    int badChar[256];
    for (int i = 0; i < 256; i++) badChar[i] = -1;
    for (int i = 0; i < m; i++) badChar[(int)lowerPattern[i]] = i;

    int s = 0;  // s is the shift of the pattern with respect to text
    while (s <= (n - m)) {
        int j = m - 1;

        // Keep reducing index j of pattern while characters of pattern and text are matching at this shift s
        while (j >= 0 && lowerPattern[j] == lowerText[s + j]) j--;

        // If pattern is present at current shift, then j will become -1
        if (j < 0) return s;

        else s += max(1, j - badChar[(int)lowerText[s + j]]);
    }

    return -1;
}

void menusorting() {
    int pilihan, idTiket;
    string keyword;

    do {
        system("cls");
        cout << "+--------------------------------------------+" << endl;
        cout << "|            Menu Pencarian Tiket            |" << endl;
        cout << "+--------------------------------------------+" << endl;
        cout << "| 1. Sort Ticket Ascending (Merge)           |" << endl;
        cout << "| 2. Sort Ticket Descending (Quick)          |" << endl;
        cout << "| 3. Kembali ke Menu Utama                   |" << endl;
        cout << "+--------------------------------------------+" << endl;

        cout << "\nMasukkan pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:  // Sort Ascending
                system("cls");
                sortTicketsAscending();
                break;

            case 2: // Sort Descending
                system("cls");
                sortTicketsDescending();
                break;

            case 3:  // Kembali ke Menu Utama
                system("cls");
                menuUtama();
                break;

            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }

        cout << "\nTekan enter untuk melanjutkan...";
        cin.ignore();
        cin.get();

    } while (pilihan != 3);
}

// Fungsi untuk menampilkan menu pencarian
void menuPencarian() {
    int pilihan, idTiket;
    string keyword;

    do {
        system("cls");
        cout << "+--------------------------------------------+" << endl;
        cout << "|            Menu Pencarian Tiket            |" << endl;
        cout << "+--------------------------------------------+" << endl;
        cout << "| 1. Cari ID dengan Fibonacci Search         |" << endl;
        cout << "| 2. Cari ID dengan Jump Search              |" << endl;
        cout << "| 3. Cari Nama dengan Boyer-Moore            |" << endl;
        cout << "| 4. Kembali ke Menu Utama                   |" << endl;
        cout << "+--------------------------------------------+" << endl;

        cout << "\nMasukkan pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:  // Cari ID dengan Fibonacci Search
                system("cls");
                cout << "Masukkan ID yang akan dicari: ";
                cin >> idTiket;
                if (top != -1 || rear != -1) {
                    int size = (top != -1) ? (top + 1) : (rear - front + 1);
                    int index = fibonacciSearch(tickets, idTiket, size);
                    if (index != -1) {
                        cout << "Tiket ditemukan pada posisi: " << index + 1 << endl;
                        cout << "Nama: " << tickets[index].nama << ", Kategori: " << tickets[index].kategori << endl;
                    } else {
                        cout << "Tiket dengan ID tersebut tidak ditemukan." << endl;
                    }
                } else {
                    cout << "Tidak ada tiket untuk dicari." << endl;
                }
                break;

            case 2:  // Cari ID dengan Jump Search
                system("cls");
                cout << "Masukkan ID yang akan dicari: ";
                cin >> idTiket;
                if (top != -1 || rear != -1) {
                    int size = (top != -1) ? (top + 1) : (rear - front + 1);
                    int index = jumpSearch(tickets, idTiket, size);
                    if (index != -1) {
                        cout << "Tiket ditemukan pada posisi: " << index + 1 << endl;
                        cout << "Nama: " << tickets[index].nama << ", Kategori: " << tickets[index].kategori << endl;
                    } else {
                        cout << "Tiket dengan ID tersebut tidak ditemukan." << endl;
                    }
                } else {
                    cout << "Tidak ada tiket untuk dicari." << endl;
                }
                break;

            case 3:  // Cari Nama atau Kategori dengan Boyer-Moore
                system("cls");
                cout << "Masukkan Nama yang dicari: ";
                cin.ignore();
                getline(cin, keyword);
                if (top != -1 || rear != -1) {
                    bool found = false;
                    int size = (top != -1) ? (top + 1) : (rear - front + 1);
                    for (int i = 0; i < size; i++) {
                        if (boyerMooreSearch(tickets[i].nama, keyword) != -1 ||
                            boyerMooreSearch(tickets[i].kategori, keyword) != -1) {
                            cout << "Tiket ditemukan pada ID: " << tickets[i].id << ", Nama: " << tickets[i].nama << endl;
                            found = true;
                        }
                    }
                    if (!found) cout << "Tiket dengan nama tersebut tidak ditemukan." << endl;
                } else {
                    cout << "Tidak ada tiket untuk dicari." << endl;
                }
                break;

            case 4:  // Kembali ke Menu Utama
                system("cls");
                menuUtama();
                break;

            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }

        cout << "\nTekan enter untuk melanjutkan...";
        cin.ignore();
        cin.get();

    } while (pilihan != 4);
}

void menuUtama() {
    int pilihan, harga;
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
        cout << "| 5. Sort Tickets Berdasarkan Harga          |" << endl;
        cout << "| 6. Pencarian Tiket                         |" << endl;
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

            case 5:  // Menu Sorting
                system("cls");
                menusorting();
                break;

            case 6: // Menu Searching
                system("cls");
                menuPencarian();
                break;

            case 7:  // Keluar
                system("cls");
                cout << "Keluar dari program." << endl;
                return;

            default:
                system("cls");
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }

        if (pilihan != 7) {
            cout << "\nApakah Anda ingin melanjutkan? (y/n): ";
            cin >> lanjut;
        }

    } while (pilihan != 7 && (lanjut == 'y' || lanjut == 'Y'));
}

int main() {
    // Menambahkan 5 data sample
    push(++idTiket, "Budi Santoso", "VIP", 150000);
    push(++idTiket, "Siti Rahayu", "Tribun", 100000);
    push(++idTiket, "Ahmad Fadli", "Ekonomi", 50000);
    push(++idTiket, "Dewi Lestari", "VIP", 150000);
    push(++idTiket, "Rudi Hermawan", "Tribun", 100000);
    
    menuUtama();  // Memulai dari menu utama
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