#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
