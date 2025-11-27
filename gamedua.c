#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#include <stdbool.h>
#include "gamedua.h"

void Gamedua() {
    srand(time(NULL)); // Mengacak hasil rand() agar hasil berbeda setiap permainan

    int pilihanuser;           
    char mainlagi = 'Y';       
    bool menang = true;        
    int skor_gamedua = 0;      

    printf("=== Quick Game Batu Gunting Kertas ===\n");

    while (toupper(mainlagi) == 'Y' && menang == true) {
        int pilihanlawan = rand() % 3; // Pilihan acak lawan (0–2)

        printf("\nSilahkan Pilih:\n0 = Batu\n1 = Gunting\n2 = Kertas\nMasukkan pilihan anda: ");

        // VALIDASI INPUT NON-INTEGER
        while (scanf("%d", &pilihanuser) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF); 
            printf("Input harus berupa angka 0, 1, atau 2!\n");
            printf("Masukkan pilihan anda: ");
        }

        // VALIDASI RANGE INPUT
        while (pilihanuser < 0 || pilihanuser > 2) {
            printf("Input tidak valid! Pilihan hanya 0, 1, atau 2.\n");
            printf("Masukkan pilihan anda: ");

            while (scanf("%d", &pilihanuser) != 1) {
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                printf("Input harus berupa angka 0, 1, atau 2!\n");
                printf("Masukkan pilihan anda: ");
            }
        }

        printf("Lawan memilih: %d\n", pilihanlawan);

        // LOGIKA HASIL
        if (pilihanuser == pilihanlawan) {
            printf("Hasil: Seri!\n");
            skor_gamedua += 5;
            menang = true;
        } 
        else if ((pilihanuser == 0 && pilihanlawan == 1) ||
                 (pilihanuser == 1 && pilihanlawan == 2) ||
                 (pilihanuser == 2 && pilihanlawan == 0)) {
            printf("Hasil: Kamu Menang!\n");
            skor_gamedua += 20;
            menang = true;
        } 
        else {
            printf("Hasil: Kamu Kalah!\n");
            skor_gamedua -= 10;
            if (skor_gamedua < 0) skor_gamedua = 0; 
            menang = false;
        }

        printf("Skor anda: %d\n", skor_gamedua);

        // Jika kalah, tawarkan main lagi
        if (menang == false) {
            printf("Main Lagi? (Y/N): ");
            scanf(" %c", &mainlagi);
            mainlagi = toupper(mainlagi);

            if (mainlagi == 'N') {
                printf("Terima kasih sudah bermain!\n");
                lastGameScore = skor_gamedua; // simpan skor
                menang = true; // reset status
                sleep(1);
                return; // kembali ke menu utama
            } 
            else {
                menang = true; // reset biar bisa lanjut lagi
            }
        }
    }

    // Kalau keluar dari loop karena menang beruntun atau seri terus
    lastGameScore = skor_gamedua;
    printf("\nPermainan selesai. Total skor: %d\n", skor_gamedua);
    sleep(1);
}
