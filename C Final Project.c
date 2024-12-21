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
    int idPeminjaman; 
    int hariPeminjaman; 
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
@@ -34,67 +38,45 @@ typedef struct {
// Struktur untuk Stack
typedef struct StackNode {
int idBuku;
    char namaPengguna[100];
    char aktivitas[50];
struct StackNode* next;
} StackNode;

// Variabel global
Buku* head = NULL;                 
Queue antreanPeminjaman = {NULL, NULL}; 
StackNode* stackBuku = NULL;       
const int DENDA_PER_HARI = 500;    


//fungsi menambah buku ke linked list (admin)
void tambahBuku(){
   Buku* buku = (Buku*)malloc(sizeof(Buku));
   printf("masukkan ID buku: ");
   scanf("%d", &buku->id);
   getchar(); 
   printf("masukkan judul buku: ");
   fgets(buku->judul,sizeof(buku->judul), stdin);
   buku->judul[strcspn(buku->judul, "\n")] = 0;
   printf("masukkan pengarang buku: ");
   fgets(buku->pengarang,sizeof(buku->pengarang), stdin);
   buku->pengarang[strcspn(buku->pengarang, "\n")] = 0;
   buku->next = NULL;

   if(head = NULL){
      head = buku;
   }else {
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
        while (temp->next != NULL){
              temp = temp->next;
         }
         temp->next = buku;
   }
   printf("buku berhasil ditambahkan!\n");
  }

//fungsi menampilkan daftar buku 
void tampilkanBuku(){
      if (head = NULL){
          printf("tidak ada buku dalam perpustakaan.\n");
          return;
      }

      printf("\nDaftar buku:\n");
      Buku* temp = head;
      while (temp != NULL){
            printf("ID: %d, Judul: %s, Pengarang: %s\n", temp->id,temp->judul, temp->pengarang);
            temp = temp ->next;
      }
   }

//fungsi mencari  buku
Buku* cariBuku(int ID){
      Buku* temp = head;
      while(temp != NULL){
          if (temp->id =ID){
              return;
          }
          temp = temp->next;
      }
      return NULL;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = buku;
    }

    printf("Buku berhasil ditambahkan!\n");
}

// Fungsi untuk menghapus buku dari Linked List
@@ -120,117 +102,314 @@ void hapusBuku(int id) {
}
}

// Fungsi peminjaman buku
void pinjamBuku() {
    int idBuku, hariPeminjaman;

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

// Fungsi untuk menambah elemen ke stack
void push(StackNode** top, int idBuku) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->idBuku = idBuku;
    newNode->next = *top;
    *top = newNode;
}

// Fungsi untuk menghapus elemen dari stack
void pop(StackNode** top) {
    if (*top == NULL) return;

    StackNode* temp = *top;
    *top = (*top)->next;
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

// Fungsi untuk meminjam buku (User)
void pinjamBuku(Pengguna* pengguna) {
    if (pengguna->idPeminjaman != -1) {
        printf("Anda masih memiliki buku yang dipinjam. Kembalikan terlebih dahulu!\n");
        return;
    }

    int idBuku;
printf("Masukkan ID buku yang ingin dipinjam: ");
scanf("%d", &idBuku);
    getchar();
    
    Buku* buku = cariBuku(idBuku);
    if (buku == NULL) {
        printf("Buku dengan ID %d tidak ditemukan.\n", idBuku);

    Buku* buku = head;
    while (buku != NULL && buku->id != idBuku) {
        buku = buku->next;
    }

    if (buku == NULL || buku->stok <= 0) {
        printf("Buku tidak tersedia.\n");
return;
}

    printf("Masukkan jumlah hari peminjaman: ");
    scanf("%d", &hariPeminjaman);
    getchar();
    int hari;
    printf("Masukkan hari peminjaman: ");
    scanf("%d", &hari);

    enqueue(&antreanPeminjaman, idBuku, hariPeminjaman);
    hapusBuku(idBuku); 
    printf("Buku dengan ID %d berhasil dipinjam.\n", idBuku);
    pengguna->idPeminjaman = idBuku;
    pengguna->hariPeminjaman = hari;
    buku->stok--; // Kurangi stok buku

    printf("Buku berhasil dipinjam!\n");
}

// Fungsi pengembalian buku dengan aturan denda
void kembalikanBuku() {
    int idBuku, hariPinjam;
    printf("Masukkan ID buku yang dikembalikan: ");
    scanf("%d", &idBuku);
    getchar();
// Fungsi untuk mengembalikan buku (User)
void kembalikanBuku(Pengguna* pengguna) {
    if (pengguna->idPeminjaman == -1) {
        printf("Anda tidak memiliki buku yang dipinjam.\n");
        return;
    }

    printf("Masukkan jumlah hari peminjaman: ");
    scanf("%d", &hariPinjam);
    getchar();
    int hariPengembalian;
    printf("Masukkan hari pengembalian: ");
    scanf("%d", &hariPengembalian);

    // Hitung denda jika terlambat
    int keterlambatan = hariPengembalian - pengguna->hariPeminjaman - 7; // Batas peminjaman adalah 7 hari
    int denda = (keterlambatan > 0) ? keterlambatan * DENDA_PER_HARI : 0;

    if (hariPinjam > 7) {
        int hariTerlambat = hariPinjam - 7;
        int denda = hariTerlambat * 5000; 
        printf("Anda terlambat mengembalikan buku selama %d hari.\n", hariTerlambat);
        printf("Denda yang harus dibayar adalah Rp%d.\n", denda);
    if (denda > 0) {
        printf("Anda terlambat mengembalikan buku selama %d hari. Denda: Rp%d\n", keterlambatan, denda);
} else {
printf("Buku dikembalikan tepat waktu. Tidak ada denda.\n");
}

    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->idBuku = idBuku;
    newNode->next = stackBuku;
    stackBuku = newNode;
    Buku* buku = head;
    while (buku != NULL && buku->id != pengguna->idPeminjaman) {
        buku = buku->next;
    }

    if (buku != NULL) {
        buku->stok++; // Tambah stok buku
    }

    pengguna->idPeminjaman = -1;
    pengguna->hariPeminjaman = 0;

    printf("Buku dengan ID %d berhasil dikembalikan.\n", idBuku);
    printf("Buku berhasil dikembalikan!\n");
}

// Fungsi untuk menambah elemen ke queue
void enqueue(Queue* q, int idBuku, int hariPeminjaman) {
// Fungsi untuk menambah pengguna ke antrean pemesanan buku
void antrePesanBuku(Queue* antreanPesan, char* namaPengguna, int idBuku) {
QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
newNode->idBuku = idBuku;
    newNode->hariPeminjaman = hariPeminjaman;
    strcpy(newNode->namaPengguna, namaPengguna);
newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    if (antreanPesan->rear == NULL) {
        antreanPesan->front = antreanPesan->rear = newNode;
} else {
        q->rear->next = newNode;
        q->rear = newNode;
        antreanPesan->rear->next = newNode;
        antreanPesan->rear = newNode;
}

    printf("Pengguna '%s' telah masuk ke antrean pemesanan untuk buku ID %d.\n", namaPengguna, idBuku);
}

// Fungsi untuk memproses antrean pemesanan buku (ketika stok tersedia)
void prosesAntreanPesan(Queue* antreanPesan) {
    if (antreanPesan->front == NULL) {
        printf("Tidak ada antrean pemesanan.\n");
        return;
    }

    QueueNode* temp = antreanPesan->front;
    printf("Memproses pesanan untuk pengguna '%s' pada buku ID %d.\n", temp->namaPengguna, temp->idBuku);
    dequeue(antreanPesan); // Menghapus dari antrean setelah diproses
}

void tambahkanRiwayat(StackNode** stackRiwayat, int idBuku, char* namaPengguna, char* aktivitas) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->idBuku = idBuku;
    strcpy(newNode->namaPengguna, namaPengguna);
    strcpy(newNode->aktivitas, aktivitas);
    newNode->next = *stackRiwayat;
    *stackRiwayat = newNode;

    printf("Riwayat '%s' untuk buku ID %d oleh '%s' telah ditambahkan.\n", aktivitas, idBuku, namaPengguna);
}

// Fungsi menampilkan antrean peminjaman
void lihatAntreanPeminjaman() {
    if (antreanPeminjaman.front == NULL) {
        printf("Antrean peminjaman kosong.\n");
// Fungsi untuk menampilkan riwayat peminjaman
void tampilkanRiwayat(StackNode* stackRiwayat) {
    if (stackRiwayat == NULL) {
        printf("Tidak ada riwayat peminjaman atau pengembalian.\n");
return;
}

    printf("\nAntrean Peminjaman:\n");
    QueueNode* temp = antreanPeminjaman.front;
    printf("\nRiwayat Peminjaman/Pengembalian:\n");
    StackNode* temp = stackRiwayat;
while (temp != NULL) {
        printf("ID Buku: %d, Hari Peminjaman: %d\n", temp->idBuku, temp->hariPeminjaman);
        printf("Buku ID: %d, Pengguna: %s, Aktivitas: %s\n", temp->idBuku, temp->namaPengguna, temp->aktivitas);
temp = temp->next;
}
}

// Fungsi untuk melihat stack buku
void lihatStackBuku() {
    if (stackBuku == NULL) {
        printf("Stack buku kosong.\n");

// Fungsi untuk menambah stok buku
void tambahStokBuku(Buku* buku, int jumlah) {
    if (buku == NULL) {
        printf("Buku tidak ditemukan.\n");
return;
}
    buku->stok += jumlah;
    printf("Stok buku '%s' berhasil ditambah menjadi %d.\n", buku->judul, buku->stok);
}

    printf("\nStack Buku:\n");
    StackNode* temp = stackBuku;
// Fungsi untuk mengurangi stok buku
void kurangiStokBuku(Buku* buku, int jumlah) {
    if (buku == NULL) {
        printf("Buku tidak ditemukan.\n");
        return;
    }

    if (buku->stok < jumlah) {
        printf("Stok buku '%s' tidak mencukupi untuk pengurangan.\n", buku->judul);
        return;
    }

    buku->stok -= jumlah;
    printf("Stok buku '%s' berhasil dikurangi menjadi %d.\n", buku->judul, buku->stok);
}

// Fungsi untuk menampilkan stok buku
void tampilkanStokBuku(Buku* head) {
    if (head == NULL) {
        printf("Tidak ada buku dalam perpustakaan.\n");
        return;
    }

    printf("\nDaftar Stok Buku:\n");
    Buku* temp = head;
while (temp != NULL) {
        printf("ID Buku: %d\n", temp->idBuku);
        printf("ID: %d, Judul: %s, Pengarang: %s, Stok: %d\n", temp->id, temp->judul, temp->pengarang, temp->stok);
temp = temp->next;
}
}

// Fungsi untuk menampilkan menu admin
//// Fungsi untuk menampilkan daftar pengguna yang meminjam buku
//void lihatPeminjam() {
//    printf("\n=== Daftar Pengguna yang Meminjam Buku ===\n");
//
//    QueueNode* temp = antreanPeminjaman.front;
//    if (temp == NULL) {
//        printf("Tidak ada buku yang sedang dipinjam.\n");
//        return;
//    }
//
//    while (temp != NULL) {
//        Buku* buku = cariBuku(temp->idBuku);
//        printf("ID Buku: %d, Hari Peminjaman: %d\n", temp->idBuku, temp->hariPeminjaman);
//        temp = temp->next;
//    }
//}

// Fungsi untuk menampilkan menu Admin
void menuAdmin() {
int pilihan;
do {
printf("\n=== Menu Admin ===\n");
printf("1. Tambah Buku\n");
printf("2. Tampilkan Buku\n");
printf("3. Hapus Buku\n");
        printf("4. Lihat Antrean Peminjaman\n");
        printf("5. Lihat Stack Buku\n");
        printf("6. Keluar\n");
        printf("4. Tambah Stok Buku\n");
        printf("5. Kurangi Stok Buku\n");
        printf("6. Tampilkan Stok Buku\n");
//        printf("7. Lihat Antrean Pemesanan Buku\n");
//        printf("8. Proses Antrean Pemesanan\n");
//        printf("9. Tampilkan Riwayat Peminjaman/Pengembalian\n");
        printf("10. Keluar\n");
printf("Pilih menu: ");
scanf("%d", &pilihan);

        switch (pilihan){
        switch (pilihan) {
case 1:
tambahBuku();
break;
@@ -242,24 +421,67 @@ void menuAdmin() {
printf("Masukkan ID buku yang akan dihapus: ");
scanf("%d", &id);
hapusBuku(id);
                printf("Buku berhasil dihapus\n");
                printf("Buku berhasil dihapus jika ditemukan!\n");
break;
}
            case 4:
                lihatAntreanPeminjaman();
            case 4: {
                int id, jumlah;
                printf("Masukkan ID buku yang akan ditambah stoknya: ");
                scanf("%d", &id);
                printf("Masukkan jumlah stok yang ingin ditambah: ");
                scanf("%d", &jumlah);
                Buku* buku = head;
                while (buku != NULL && buku->id != id) {
                    buku = buku->next;
                }
                tambahStokBuku(buku, jumlah);
break;
            case 5:
                lihatStackBuku();
            }
            case 5: {
                int id, jumlah;
                printf("Masukkan ID buku yang akan dikurangi stoknya: ");
                scanf("%d", &id);
                printf("Masukkan jumlah stok yang ingin dikurangi: ");
                scanf("%d", &jumlah);
                Buku* buku = head;
                while (buku != NULL && buku->id != id) {
                    buku = buku->next;
                }
                kurangiStokBuku(buku, jumlah);
break;
            }
case 6:
                tampilkanStokBuku(head);
                break;
//            case 7:
//                if (antreanPeminjaman.front == NULL) {
//                    printf("Tidak ada antrean pemesanan.\n");
//                } else {
//                    QueueNode* temp = antreanPeminjaman.front;
//                    printf("\nAntrean Pemesanan Buku:\n");
//                    while (temp != NULL) {
//                        printf("Pengguna: %s, ID Buku: %d\n", temp->namaPengguna, temp->idBuku);
//                        temp = temp->next;
//                    }
//                }
//                break;
//            case 8:
//                prosesAntreanPesan(&antreanPeminjaman);
//                break;
//            case 9:
//                tampilkanRiwayat(stackBuku);
//                break;
            case 10:
printf("Keluar dari menu Admin.\n");
break;
default:
printf("Pilihan tidak valid.\n");
}
    } while (pilihan != 6);
    } while (pilihan != 10);
}


// Fungsi untuk menampilkan menu User
void menuUser(Pengguna* pengguna) {
int pilihan;
do {
@@ -271,8 +493,8 @@ void menuUser(Pengguna* pengguna) {
printf("Pilih menu: ");
scanf("%d", &pilihan);

    switch (pilihan) {
        case 1:
        switch (pilihan) {
            case 1:
pinjamBuku(pengguna);
break;
case 2:
@@ -287,18 +509,46 @@ void menuUser(Pengguna* pengguna) {
default:
printf("Pilihan tidak valid.\n");
}
    } while (pilihan !=4);
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

int main() {
Pengguna pengguna = {"", -1, 0};
int pilihan;

    printf("Selamar datang di sistem perpustakaan!\n");
    printf("Masukkan nama anda: ");
    getchar();
    fgets(pengguna.nama, 100, stdin);
    pengguna.nama[strcspn(pengguna.nama, "\n")] = '\0';
    // Tambahkan buku default ke sistem perpustakaan
    tambahBukuDefault();

    printf("Selamat datang di Sistem Perpustakaan!\n");

do {
printf("\n=== Menu Utama ===\n");
@@ -312,15 +562,22 @@ int main() {
case 1:
menuAdmin();
break;
            case 2:
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

    return 0;
}
