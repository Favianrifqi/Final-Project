#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Struktur data untuk node buku (Linked List)
typedef struct Buku {
    int id;
    char judul[100];
    char pengarang[100];
    struct Buku* next;
} Buku;

// Struktur data untuk pengguna
typedef struct Pengguna {
    char nama[100];
    int idPeminjaman; 
    int hariPeminjaman; 
} Pengguna;

// Node untuk queue
typedef struct QueueNode {
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
    struct StackNode* next;
} StackNode;

// Variabel global
Buku* head = NULL;                 
Queue antreanPeminjaman = {NULL, NULL}; 
StackNode* stackBuku = NULL;       
const int DENDA_PER_HARI = 500;    


//fungsi menambah buku ke linked list (admin)
void tambahBuku(){
   buku* buku = (buku*)malloc(sizeof(buku));
   printf("masukkan ID buku: ");
   scanf("d%", &buku->ID);
   getchar(); 
   printf("masukkan judul buku: ");
   fgets(buku->judul, MAX_JUDUL, stdin);
   buku->judul[strcspn(buku->judul, "\n")] = 0;
   printf("masukkan pengarang buku: ");
   fgets(buku->pengarang, MAX_PENGARANG, stdin);
   buku->pengarang[strcspn(buku->pengarang, "\n")] = 0;
   buku->next = NULL;

   if(head = NULL){
      head = buku;
   }else {
        buku* temp = head;
        while (temp->next != NULL){
              temp = temp->next;
         }
         temp->next = buku;
   }
   printf("buku berhasil ditambahkan!n\");
  }

//fungsi menampilkan daftar buku 
void tampilkanBuku(){
      if (head = NULL){
          printf("tidak ada buku dalam perpustakaan.\n");
          return;
      }

      printf("\nDaftar buku:\n");
      buku* temp = head;
      while (temp != NULL){
            printf("ID: %d, Judul: %s, Pengarang: %s\n", temp->id,temp->judul, temp->pengarang);
            temp = temp ->next;
      }
   }

//fungsi mencari  buku
buku* cariBuku(int ID){
      buku* temp = head;
      while(temp != NULL){
          if (temp->ID =ID){
              return;
          }
          temp = temp->next;
      }
      return NULL;
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

// Fungsi peminjaman buku
void pinjamBuku() {
    int idBuku, hariPeminjaman;
    printf("Masukkan ID buku yang ingin dipinjam: ");
    scanf("%d", &idBuku);
    getchar();
    
    Buku* buku = cariBuku(idBuku);
    if (buku == NULL) {
        printf("Buku dengan ID %d tidak ditemukan.\n", idBuku);
        return;
    }

    printf("Masukkan jumlah hari peminjaman: ");
    scanf("%d", &hariPeminjaman);
    getchar();

    enqueue(&antreanPeminjaman, idBuku, hariPeminjaman);
    hapusBuku(idBuku); 
    printf("Buku dengan ID %d berhasil dipinjam.\n", idBuku);
}

// Fungsi pengembalian buku dengan aturan denda
void kembalikanBuku() {
    int idBuku, hariPinjam;
    printf("Masukkan ID buku yang dikembalikan: ");
    scanf("%d", &idBuku);
    getchar();

    printf("Masukkan jumlah hari peminjaman: ");
    scanf("%d", &hariPinjam);
    getchar();

    if (hariPinjam > 7) {
        int hariTerlambat = hariPinjam - 7;
        int denda = hariTerlambat * 5000; 
        printf("Anda terlambat mengembalikan buku selama %d hari.\n", hariTerlambat);
        printf("Denda yang harus dibayar adalah Rp%d.\n", denda);
    } else {
        printf("Buku dikembalikan tepat waktu. Tidak ada denda.\n");
    }

    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->idBuku = idBuku;
    newNode->next = stackBuku;
    stackBuku = newNode;

    printf("Buku dengan ID %d berhasil dikembalikan.\n", idBuku);
}

// Fungsi untuk menambah elemen ke queue
void enqueue(Queue* q, int idBuku, int hariPeminjaman) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->idBuku = idBuku;
    newNode->hariPeminjaman = hariPeminjaman;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}


// Fungsi menampilkan antrean peminjaman
void lihatAntreanPeminjaman() {
    if (antreanPeminjaman.front == NULL) {
        printf("Antrean peminjaman kosong.\n");
        return;
    }

    printf("\nAntrean Peminjaman:\n");
    QueueNode* temp = antreanPeminjaman.front;
    while (temp != NULL) {
        printf("ID Buku: %d, Hari Peminjaman: %d\n", temp->idBuku, temp->hariPeminjaman);
        temp = temp->next;
    }
}

// Fungsi untuk melihat stack buku
void lihatStackBuku() {
    if (stackBuku == NULL) {
        printf("Stack buku kosong.\n");
        return;
    }

    printf("\nStack Buku:\n");
    StackNode* temp = stackBuku;
    while (temp != NULL) {
        printf("ID Buku: %d\n", temp->idBuku);
        temp = temp->next;
    }
}

// Fungsi untuk menampilkan menu admin
void menuAdmin() {
    int pilihan;
    do {
        printf("\n=== Menu Admin ===\n");
        printf("1. Tambah Buku\n");
        printf("2. Tampilkan Buku\n");
        printf("3. Hapus Buku\n");
        printf("4. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan){
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
                printf("Buku berhasil dihapus\n");
                break;
            }
            case 4:
                printf("Keluar dari menu Admin.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan !=4);
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
    } while (pilihan !=4);
}

int main() {
    Pengguna pengguna = {"", -1, 0};
    int pilihan;

    printf("Selamar datang di sistem perpustakaan!\n");
    printf("Masukkan nama anda: ");
    getchar();
    fgets(pengguna.nama, 100, stdin);
    pengguna.nama[strcspn(pengguna.nama, "\n")] = '\0';

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
            case 2:
                menuUser(&pengguna);
                break;
            case 3:
                printf("Keluar dari sistem. Terima kasih!\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 3);

    return 0;
}
