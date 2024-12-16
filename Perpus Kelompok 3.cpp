// Sistem Perpustakaan Menggunakan Linked List, Queue, dan Stack

#include <iostream>
#include <string>
#include <queue>
#include <stack>

using namespace std;

// Struktur data untuk node buku (Linked List)
struct Buku {
    int id;
    string judul;
    string pengarang;
    Buku* next;
};

// Struktur data untuk pengguna
struct Pengguna {
    string nama;
    int idPeminjaman; // ID buku yang sedang dipinjam (jika ada)
    int hariPeminjaman; // Hari peminjaman buku
};

// Variabel global
Buku* head = nullptr;               // Head untuk Linked List buku
queue<pair<int, int>> antreanPeminjaman; // Queue untuk antrean peminjaman buku (ID Buku, Hari Peminjaman)
stack<int> stackBuku;               // Stack untuk buku yang dipinjam sementara (simulasi tumpukan buku)
const int DENDA_PER_HARI = 500;     // Denda keterlambatan per hari

// Fungsi untuk menambah buku ke linked list (Admin)
void tambahBuku() {
    Buku* buku = new Buku;
    cout << "Masukkan ID buku: ";
    cin >> buku->id;
    cin.ignore();
    cout << "Masukkan judul buku: ";
    getline(cin, buku->judul);
    cout << "Masukkan pengarang buku: ";
    getline(cin, buku->pengarang);
    buku->next = nullptr;

    if (head == nullptr) {
        head = buku;
    } else {
        Buku* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = buku;
    }

    cout << "Buku berhasil ditambahkan!\n";
}

// Fungsi untuk menampilkan daftar buku (Linked List)
void tampilkanBuku() {
    if (head == nullptr) {
        cout << "Tidak ada buku dalam perpustakaan.\n";
        return;
    }

    cout << "\nDaftar Buku:\n";
    Buku* temp = head;
    while (temp != nullptr) {
        cout << "ID: " << temp->id << ", Judul: " << temp->judul << ", Pengarang: " << temp->pengarang << "\n";
        temp = temp->next;
    }
}

// Fungsi untuk mencari buku dalam Linked List
Buku* cariBuku(int id) {
    Buku* temp = head;
    while (temp != nullptr) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

// Fungsi untuk menghapus buku dari Linked List
void hapusBuku(int id) {
    if (head == nullptr) return;

    if (head->id == id) {
        Buku* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Buku* temp = head;
    while (temp->next != nullptr && temp->next->id != id) {
        temp = temp->next;
    }

    if (temp->next != nullptr) {
        Buku* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
    }
}

// Fungsi untuk meminjam buku (User)
void pinjamBuku(Pengguna& pengguna) {
    if (pengguna.idPeminjaman != -1) {
        cout << "Anda masih memiliki buku yang dipinjam. Kembalikan terlebih dahulu!\n";
        return;
    }

    int idBuku;
    cout << "Masukkan ID buku yang ingin dipinjam: ";
    cin >> idBuku;
    int hari;
    cout << "Masukkan hari peminjaman: ";
    cin >> hari;

    Buku* buku = cariBuku(idBuku);
    if (buku != nullptr) {
        pengguna.idPeminjaman = idBuku;
        pengguna.hariPeminjaman = hari;
        antreanPeminjaman.push({idBuku, hari});
        stackBuku.push(idBuku); // Buku ditambahkan ke stack
        hapusBuku(idBuku);
        cout << "Buku berhasil dipinjam!\n";
    } else {
        cout << "Buku tidak ditemukan atau sudah dipinjam.\n";
    }
}

// Fungsi untuk mengembalikan buku (User)
void kembalikanBuku(Pengguna& pengguna) {
    if (pengguna.idPeminjaman == -1) {
        cout << "Anda tidak memiliki buku yang dipinjam.\n";
        return;
    }

    int hariPengembalian;
    cout << "Masukkan hari pengembalian: ";
    cin >> hariPengembalian;

    // Hitung denda jika terlambat
    int keterlambatan = hariPengembalian - pengguna.hariPeminjaman - 7; // Batas peminjaman adalah 7 hari
    int denda = (keterlambatan > 0) ? keterlambatan * DENDA_PER_HARI : 0;

    if (denda > 0) {
        cout << "Anda terlambat mengembalikan buku selama " << keterlambatan << " hari. Denda: Rp" << denda << "\n";
    } else {
        cout << "Buku dikembalikan tepat waktu. Tidak ada denda.\n";
    }

    Buku* buku = new Buku;
    buku->id = pengguna.idPeminjaman;
    cout << "Masukkan judul buku yang dikembalikan: ";
    cin.ignore();
    getline(cin, buku->judul);
    cout << "Masukkan pengarang buku yang dikembalikan: ";
    getline(cin, buku->pengarang);
    buku->next = nullptr;

    if (head == nullptr) {
        head = buku;
    } else {
        Buku* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = buku;
    }

    pengguna.idPeminjaman = -1;
    if (!stackBuku.empty()) {
        stackBuku.pop(); // Hapus dari stack
    }

    cout << "Buku berhasil dikembalikan!\n";
}

// Fungsi untuk melihat antrean peminjaman (Admin)
void lihatAntrean() {
    if (antreanPeminjaman.empty()) {
        cout << "Tidak ada antrean peminjaman.\n";
        return;
    }

    cout << "\nAntrean Peminjaman:\n";
    queue<pair<int, int>> temp = antreanPeminjaman;
    while (!temp.empty()) {
        cout << "ID Buku: " << temp.front().first << ", Hari: " << temp.front().second << "\n";
        temp.pop();
    }
}

// Fungsi untuk melihat stack buku (Admin)
void lihatStack() {
    if (stackBuku.empty()) {
        cout << "Stack buku kosong.\n";
        return;
    }

    cout << "\nStack Buku yang Dipinjam:\n";
    stack<int> temp = stackBuku;
    while (!temp.empty()) {
        cout << "ID Buku: " << temp.top() << "\n";
        temp.pop();
    }
}

// Menu utama untuk admin
void menuAdmin() {
    int pilihan;
    do {
        cout << "\nMenu Admin:\n";
        cout << "1. Tambah Buku\n";
        cout << "2. Tampilkan Daftar Buku\n";
        cout << "3. Lihat Antrean Peminjaman\n";
        cout << "4. Lihat Stack Buku yang Dipinjam\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahBuku();
                break;
            case 2:
                tampilkanBuku();
                break;
            case 3:
                lihatAntrean();
                break;
            case 4:
                lihatStack();
                break;
            case 0:
                cout << "Keluar dari menu admin.";
                break;
                    default:
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (pilihan != 0);
}

// Menu utama untuk pengguna
void menuUser(Pengguna& pengguna) {
    int pilihan;
    do {
        cout << "\nMenu User:\n";
        cout << "1. Tampilkan Daftar Buku\n";
        cout << "2. Pinjam Buku\n";
        cout << "3. Kembalikan Buku\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tampilkanBuku();
                break;
            case 2:
                pinjamBuku(pengguna);
                break;
            case 3:
                kembalikanBuku(pengguna);
                break;
            case 0:
                cout << "Keluar dari menu user.\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (pilihan != 0);
}

// Fungsi utama
int main() {
    int role;
    Pengguna pengguna = {"", -1, 0}; // Default pengguna (idPeminjaman = -1 berarti tidak meminjam buku)

    cout << "Selamat datang di Sistem Perpustakaan!\n";
    do {
        cout << "\nPilih peran Anda:\n";
        cout << "1. Admin\n";
        cout << "2. User\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> role;

        switch (role) {
            case 1:
                menuAdmin();
                break;
            case 2:
                cout << "Masukkan nama Anda: ";
                cin.ignore();
                getline(cin, pengguna.nama);
                menuUser(pengguna);
                break;
            case 0:
                cout << "Terima kasih telah menggunakan sistem perpustakaan. Sampai jumpa!\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (role != 0);

    return 0;
}
