#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Buku {
    int id;
    char judul[100];
    char pengarang[100];
    int stok;
    struct Buku* next;
} Buku;

typedef struct Pengguna {
    char nama[100];
    int idPeminjaman;
    int hariPeminjaman;
    struct Pengguna* next;
} Pengguna;

Buku* head = NULL;
Pengguna* penggunaHead = NULL;
const int MAX_HARI = 7;
const int DENDA_PER_HARI = 5000;

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
    strcpy(buku2->pengarang, "Rinaldi Munir");
    buku2->stok = 3;
    buku2->next = NULL;
    buku1->next = buku2;

    Buku* buku3 = (Buku*)malloc(sizeof(Buku));
    buku3->id = 3;
    strcpy(buku3->judul, "Jaringan Komputer");
    strcpy(buku3->pengarang, "Andrew S. Tanenbaum");
    buku3->stok = 4;
    buku3->next = NULL;
    buku2->next = buku3;

    printf("Buku default berhasil ditambahkan ke sistem!\n");
}

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

void tambahBuku() {
    Buku* buku = (Buku*)malloc(sizeof(Buku));
    printf("Masukkan ID buku: ");
    scanf("%d", &buku->id);
    getchar();
    printf("Masukkan judul buku: ");
    fgets(buku->judul, 100, stdin);
    buku->judul[strcspn(buku->judul, "\n")] = '\0';
    printf("Masukkan pengarang buku: ");
    fgets(buku->pengarang, 100, stdin);
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

void hapusBuku() {
    int id;
    printf("Masukkan ID buku yang akan dihapus: ");
    scanf("%d", &id);

    if (head == NULL) {
        printf("Tidak ada buku dalam daftar.\n");
        return;
    }

    if (head->id == id) {
        Buku* temp = head;
        head = head->next;
        free(temp);
        printf("Buku berhasil dihapus.\n");
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
        printf("Buku berhasil dihapus.\n");
    } else {
        printf("Buku dengan ID %d tidak ditemukan.\n", id);
    }
}

void tampilkanBuku() {
    if (head == NULL) {
        printf("Tidak ada buku dalam perpustakaan.\n");
        return;
    }

    printf("\nDaftar Buku:\n");
    Buku* temp = head;
    while (temp != NULL) {
        printf("ID: %d, Judul: %s, Pengarang: %s, Stok: %d\n",
               temp->id, temp->judul, temp->pengarang, temp->stok);
        temp = temp->next;
    }
}

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
    printf("Masukkan jumlah hari peminjaman (maksimal %d hari): ", MAX_HARI);
    scanf("%d", &hari);

    if (hari > MAX_HARI) {
        printf("Peminjaman tidak boleh lebih dari %d hari.\n", MAX_HARI);
        return;
    }

    pengguna->idPeminjaman = idBuku;
    pengguna->hariPeminjaman = hari;
    buku->stok--;

    printf("Buku '%s' berhasil dipinjam untuk %d hari.\n", buku->judul, hari);
}

void kembalikanBuku(Pengguna* pengguna) {
    if (pengguna->idPeminjaman == -1) {
        printf("Anda tidak memiliki buku yang dipinjam.\n");
        return;
    }

    int hariPengembalian;
    printf("Masukkan hari pengembalian: ");
    scanf("%d", &hariPengembalian);

    int keterlambatan = hariPengembalian - pengguna->hariPeminjaman;
    int denda = (keterlambatan > 0) ? keterlambatan * DENDA_PER_HARI : 0;

    if (denda > 0) {
        printf("Anda terlambat mengembalikan buku selama %d hari. Denda: Rp%d\n",
               keterlambatan, denda);
    } else {
        printf("Buku dikembalikan tepat waktu. Tidak ada denda.\n");
    }

    Buku* buku = cariBuku(pengguna->idPeminjaman);
    if (buku != NULL) {
        buku->stok++;
    }

    pengguna->idPeminjaman = -1;
    pengguna->hariPeminjaman = 0;

    printf("Buku berhasil dikembalikan!\n");
}

void menuAdmin() {
    int pilihan;
    do {
        printf("\n=== Menu Admin ===\n");
        printf("1. Tambah Buku\n");
        printf("2. Hapus Buku\n");
        printf("3. Tampilkan Buku\n");
        printf("4. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                tambahBuku();
                break;
            case 2:
                hapusBuku();
                break;
            case 3:
                tampilkanBuku();
                break;
            case 4:
                printf("Keluar dari menu Admin.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 4);
}

void menuUser(Pengguna* pengguna) {
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

int main() {
    int pilihan;
    Pengguna pengguna = {"", -1, 0};

    tambahBukuDefault();

    printf("Selamat datang di Sistem Perpustakaan!\n");

    do {
        printf("\n=== Menu Utama ===\n");
        printf("1. Admin\n");
        printf("2. User\n");
        printf("3. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                menuAdmin();
                break;
            case 2: {
                printf("Masukkan nama Anda: ");
                getchar();
                fgets(pengguna.nama, 100, stdin);
                pengguna.nama[strcspn(pengguna.nama, "\n")] = '\0';
                menuUser(&pengguna);
                break;
            }
            case 3:
                printf("Keluar dari sistem. Terima kasih!\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 3);

    return 0;
}
