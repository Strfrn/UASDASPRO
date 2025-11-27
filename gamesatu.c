#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#include "gamesatu.h"

void Gamesatu() {
    const int MAX = 10;    // batas angka tebakan
    int tebakan, angka_rahasia, percobaan, skor;
    int total_skor = 0;    // total skor dari beberapa ronde
    char mainlagi = 'Y';   // kontrol main lagi di dalam game

    srand(time(0));

    printf("=== Permainan Tebak Angka ===\n");
    printf("Skor tebakan dihitung berdasarkan jumlah tebakan:\n");

    while (toupper(mainlagi) == 'Y') {
        angka_rahasia = rand() % MAX + 1; // angka acak baru
        percobaan = 0; // reset jumlah percobaan

        printf("Saya sudah memilih angka antara 1 sampai %d.\n", MAX);

        while (1) {
            printf("Masukkan tebakanmu: ");

            if (scanf("%d", &tebakan) != 1) {
                int c;
                while ((c = getchar()) != '\n' && c != EOF); // bersihkan buffer
                printf("Input tidak valid. Masukkan angka!\n");
                continue; // kembali ke awal loop tanpa menambah percobaan
            }

            if (tebakan < 1 || tebakan > 10) {
                printf("Tebakan harus antara 1 sampai 10!\n");
                continue;
            }

            percobaan++;

            if (tebakan > angka_rahasia) {
                printf("Terlalu besar!\n");
            } else if (tebakan < angka_rahasia) {
                printf("Terlalu kecil!\n");
            } else {
                skor = 100 - (percobaan - 1) * 20;
                if (skor < 0) skor = 0; // skor minimum 0
                printf("Benar! Angkanya adalah %d.\n", angka_rahasia);
                printf("Kamu menebak dengan %d percobaan.\n", percobaan);
                printf("Skor ronde ini: %d poin.\n\n", skor);
                total_skor += skor;
                break;
            }
        }

        printf("Mau main lagi? (Y/N): ");
        scanf(" %c", &mainlagi);

        if (toupper(mainlagi) == 'N') {
            printf("Permainan selesai!\n");
            printf("Total skor kamu: %d poin.\n", total_skor);
            lastGameScore = total_skor; // <-- set global score utk integrasi
            sleep(1); // Jeda 1 detik sebelum kembali ke menu utama
            return; // langsung kembali ke menu utama
        }
    }
}
