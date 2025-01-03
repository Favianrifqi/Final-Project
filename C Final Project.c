// Sistem Perpustakaan Menggunakan Linked List, Queue, dan Stack

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur data untuk node buku (Linked List)
typedef struct Buku {
    int id;
    char judul[100];
    char pengarang[100];
    int stok; // Tambahan untuk menyimpan stok buku
    struct Buku* next;
} Buku;

// Struktur data untuk pengguna
typedef struct Pengguna {
    char nama[100];
    int idPeminjaman; // ID buku yang sedang dipinjam (jika ada)
    int hariPeminjaman; // Hari peminjaman buku
    struct Pengguna* next;
} Pengguna;

// Node untuk queue
typedef struct QueueNode {
    char namaPengguna[100]; // Nama pengguna yang meminjam
    int idBuku;
    int hariPeminjaman;
    struct QueueNode* next;
} QueueNode;

// Struktur untuk Queue
typedef struct {
    QueueNode* front;
    QueueNode* rear;
} Queue;

// Struktur untuk Stack
typedef struct StackNode {
    int idBuku;
    char namaPengguna[100];
    char aktivitas[50];
    struct StackNode* next;
} StackNode;

// Variabel global
Buku* head = NULL;                 // Head untuk Linked List buku
Pengguna* penggunaHead = NULL;     // Head untuk daftar pengguna
Queue antreanPeminjaman = {NULL, NULL}; // Queue untuk antrean peminjaman buku
StackNode* stackBuku = NULL;       // Stack untuk buku yang dipinjam sementara
const int DENDA_PER_HARI = 5000;    // Denda keterlambatan per hari

// Fungsi untuk menambah buku ke linked list (Admin)
void tambahBuku() {
    Buku* buku = (Buku*)malloc(sizeof(Buku));
    printf("Masukkan ID buku: ");
    scanf("%d", &buku->id);
    getchar();
    printf("Masukkan judul buku: ");
    fgets(buku->judul, sizeof(buku->judul), stdin);
    buku->judul[strcspn(buku->judul, "\n")] = '\0';
    printf("Masukkan pengarang buku: ");
    fgets(buku->pengarang, sizeof(buku->pengarang), stdin);
    buku->pengarang[strcspn(buku->pengarang, "\n")] = '\0';
    printf("Masukkan stok buku: ");
    scanf("%d", &buku->stok);
    buku->next = NULL;

    if (head == NULL) {
        head = buku;
    } else {
        Buku* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = buku;
    }

    printf("Buku berhasil ditambahkan!\n");
}

// Fungsi untuk menghapus buku dari Linked List
void hapusBuku(int id) {
    if (head == NULL) return;

    if (head->id == id) {
        Buku* temp = head;
        head = head->next;
        free(temp);
        return;
    }

    Buku* temp = head;
    while (temp->next != NULL && temp->next->id != id) {
        temp = temp->next;
    }

    if (temp->next != NULL) {
        Buku* toDelete = temp->next;
        temp->next = temp->next->next;
        free(toDelete);
    }
}

// Fungsi untuk menampilkan daftar buku (Linked List)
void tampilkanBuku() {
    if (head == NULL) {
        printf("Tidak ada buku dalam perpustakaan.\n");
        return;
    }

    printf("\nDaftar Buku:\n");
    Buku* temp = head;
    while (temp != NULL) {
        printf("ID: %d, Judul: %s, Pengarang: %s, Stok: %d\n", temp->id, temp->judul, temp->pengarang, temp->stok);
        temp = temp->next;
    }
}

// Fungsi untuk mencari buku berdasarkan ID
Buku* cariBuku(int id) {
    Buku* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

// Fungsi untuk menambah elemen ke queue
void enqueue(Queue* q, int idBuku, int hariPeminjaman, const char* namaPengguna) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->idBuku = idBuku;
    newNode->hariPeminjaman = hariPeminjaman;
    strcpy(newNode->namaPengguna, namaPengguna);
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// Fungsi untuk menghapus elemen dari queue
void dequeue(Queue* q) {
    if (q->front == NULL) return;

    QueueNode* temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
}

// Fungsi untuk menambah pengguna baru ke linked list pengguna
void tambahPengguna(char* nama) {
    Pengguna* pengguna = (Pengguna*)malloc(sizeof(Pengguna));
    strcpy(pengguna->nama, nama);
    pengguna->idPeminjaman = -1;
    pengguna->hariPeminjaman = 0;
    pengguna->next = NULL;

    if (penggunaHead == NULL) {
        penggunaHead = pengguna;
    } else {
        Pengguna* temp = penggunaHead;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = pengguna;
    }
}

// Fungsi untuk menampilkan daftar pengguna yang sedang meminjam buku
void lihatPeminjam() {
    if (penggunaHead == NULL) {
        printf("Tidak ada pengguna yang terdaftar.\n");
        return;
    }

    printf("\nDaftar Pengguna yang Meminjam Buku:\n");
    Pengguna* temp = penggunaHead;
    while (temp != NULL) {
        if (temp->idPeminjaman != -1) {
            printf("Nama: %s, ID Buku: %d, Hari Peminjaman: %d\n", temp->nama, temp->idPeminjaman, temp->hariPeminjaman);
        }
        temp = temp->next;
    }
}

// Fungsi untuk meminjam buku (User )
void pinjamBuku(Pengguna* pengguna) {
    if (pengguna->idPeminjaman != -1) {
        printf("Anda masih memiliki buku yang dipinjam. Kembalikan terlebih dahulu!\n");
        return;
    }

    int idBuku;
    printf("Masukkan ID buku yang ingin dipinjam: ");
    scanf("%d", &idBuku);

    Buku* buku = cariBuku(idBuku);
    if (buku == NULL || buku->stok <= 0) {
        printf("Buku tidak tersedia.\n");
        return;
    }

    int hari;
    printf("Masukkan tanggal peminjaman: ");
    scanf("%d", &hari);

    pengguna->idPeminjaman = idBuku;
    pengguna->hariPeminjaman = hari;
    buku->stok--; // Kurangi stok buku

    printf("Buku berhasil dipinjam!\n");
}

// Fungsi untuk mengembalikan buku (User )
void kembalikanBuku(Pengguna* pengguna) {
    if (pengguna->idPeminjaman == -1) {
        printf("Anda tidak memiliki buku yang dipinjam.\n");
        return;
    }

    int hariPengembalian;
    printf("Masukkan tanggal pengembalian: ");
    scanf("%d", &hariPengembalian);

    // Hitung denda jika terlambat
    int keterlambatan = hariPengembalian - pengguna->hariPeminjaman - 7; // Batas peminjaman adalah 7 hari
    int denda = (keterlambatan > 0) ? keterlambatan * DENDA_PER_HARI : 0;

    if (denda > 0) {
        printf("Anda terlambat mengembalikan buku selama %d hari. Denda: Rp%d\n", keterlambatan, denda);
    } else {
        printf("Buku dikembalikan tepat waktu. Tidak ada denda.\n");
    }

    Buku* buku = cariBuku(pengguna->idPeminjaman);
    if (buku != NULL) {
        buku->stok++; // Tambah stok buku
    }

    pengguna->idPeminjaman = -1;
    pengguna->hariPeminjaman = 0;

    printf("Buku berhasil dikembalikan!\n");
}

// Fungsi untuk menampilkan menu Admin
void menuAdmin() {
    int pilihan;
    do {
        printf("\n=== Menu Admin ===\n");
        printf("1. Tambah Buku\n");
        printf("2. Tampilkan Buku\n");
        printf("3. Hapus Buku\n");
        printf("4. Tambah Stok Buku\n");
        printf("5. Kurangi Stok Buku\n");
        printf("6. Tampilkan Stok Buku\n");
        printf("7. Lihat Daftar Peminjam Buku\n");
        printf("8. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                tambahBuku();
                break;
            case 2:
                tampilkanBuku();
                break;
            case 3: {
                int id;
                printf("Masukkan ID buku yang akan dihapus: ");
                scanf("%d", &id);
                hapusBuku(id);
                printf("Buku berhasil dihapus jika ditemukan!\n");
                break;
            }
            case 4: {
                int id, jumlah;
                printf("Masukkan ID buku yang akan ditambah stoknya: ");
                scanf("%d", &id);
                printf("Masukkan jumlah stok yang ingin ditambah: ");
                scanf("%d", &jumlah);
                Buku* buku = cariBuku(id);
                if (buku != NULL) {
                    buku->stok += jumlah; // Tambah stok buku
                    printf("Stok buku berhasil ditambahkan!\n");
                } else {
                    printf("Buku tidak ditemukan.\n");
                }
                break;
            }
            case 5: {
                int id, jumlah;
                printf("Masukkan ID buku yang akan dikurangi stoknya: ");
                scanf("%d", &id);
                printf("Masukkan jumlah stok yang ingin dikurangi: ");
                scanf("%d", &jumlah);
                Buku* buku = cariBuku(id);
                if (buku != NULL) {
                    if (buku->stok >= jumlah) {
                        buku->stok -= jumlah; // Kurangi stok buku
                        printf("Stok buku berhasil dikurangi!\n");
                    } else {
                        printf("Stok buku tidak cukup untuk dikurangi.\n");
                    }
                } else {
                    printf("Buku tidak ditemukan.\n");
                }
                break;
            }
            case 6:
                tampilkanBuku();
                break;
            case 7:
                lihatPeminjam();
                break;
            case 8:
                printf("Keluar dari menu Admin.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 8);
}

// Fungsi untuk menampilkan menu User
void menuUser (Pengguna* pengguna) {
    int pilihan;
    do {
        printf("\n=== Menu User ===\n");
        printf("1. Pinjam Buku\n");
        printf("2. Kembalikan Buku\n");
        printf("3. Tampilkan Buku\n");
        printf("4. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                pinjamBuku(pengguna);
                break;
            case 2:
                kembalikanBuku(pengguna);
                break;
            case 3:
                tampilkanBuku();
                break;
            case 4:
                printf("Keluar dari menu User.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 4);
}

// Fungsi untuk menambahkan buku default ke dalam sistem
void tambahBukuDefault() {
    Buku* buku1 = (Buku*)malloc(sizeof(Buku));
    buku1->id = 1;
    strcpy(buku1->judul, "Pemrograman C");
    strcpy(buku1->pengarang, "Budi Raharjo");
        buku1->stok = 5;
    buku1->next = NULL;
    head = buku1;

    Buku* buku2 = (Buku*)malloc(sizeof(Buku));
    buku2->id = 2;
    strcpy(buku2->judul, "Algoritma dan Struktur Data");
    strcpy(buku2->pengarang, "Andi Setiawan");
    buku2->stok = 3;
    buku2->next = NULL;
    buku1->next = buku2; // Link the first book to the second book
}

// Fungsi untuk membebaskan memori yang dialokasikan
void freeMemory() {
    // Bebaskan semua buku
    Buku* tempBuku;
    while (head != NULL) {
        tempBuku = head;
        head = head->next;
        free(tempBuku);
    }

    // Bebaskan semua pengguna
    Pengguna* tempPengguna;
    while (penggunaHead != NULL) {
        tempPengguna = penggunaHead;
        penggunaHead = penggunaHead->next;
        free(tempPengguna);
    }
}

// Fungsi utama
int main() {
    // Inisialisasi sistem dengan buku default
    tambahBukuDefault();

    // Menu utama
    int pilihan;
    do {
        printf("\n=== Menu Utama ===\n");
        printf("1. Masuk sebagai Admin\n");
        printf("2. Masuk sebagai User\n");
        printf("3. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1: {
                // Login sebagai admin
                menuAdmin();
                break;
            }
            case 2: {
                // Login sebagai user
                char nama[100];
                printf("Masukkan nama pengguna: ");
                getchar(); // Menghapus newline dari input sebelumnya
                fgets(nama, sizeof(nama), stdin);
                nama[strcspn(nama, "\n")] = '\0'; // Menghapus newline

                // Tambahkan pengguna baru
                tambahPengguna(nama);

                // Ambil pointer ke pengguna yang baru ditambahkan
                Pengguna* pengguna = penggunaHead;
                while (pengguna != NULL && strcmp(pengguna->nama, nama) != 0) {
                    pengguna = pengguna->next;
                }

                if (pengguna != NULL) {
                    menuUser (pengguna);
                } else {
                    printf("Pengguna tidak ditemukan.\n");
                }
                break;
            }
            case 3:
                printf("Keluar dari sistem.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 3);

    // Bebaskan memori sebelum keluar
    freeMemory();

    return 0;
}
