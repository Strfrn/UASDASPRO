#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include "gameempat.h"

void Gameempat() {
    #define LIST_KATA 15
    #define DIGIT_KATA 4

    printf("=== Game Empat: Tebak Kata ===\n");

    char daftarKata[LIST_KATA][DIGIT_KATA + 1] = {
        "APEL", "BATU", "RUSA", "PITA", "EKOR",
        "ULAR", "GULA", "HARI", "IKAT", "JARI",
        "ROTI", "LAUT", "MADU", "NASI", "OBAT"
    };
    
    srand(time(NULL));
    char mainLagi = 'Y';
    int score = 0;

    printf(" SELAMAT DATANG DI TEBAK KATA! \n\n");
    printf("============ GUIDE ============\n\n");
    printf("| _ | _ | _ | _ |\n\n");
    printf("Ketik kata tebakanmu: APEL\n");
    printf("Tujuanmu adalah menebak kata 4 huruf yang benar.\n");
    printf("===============================\n");

    while (toupper(mainLagi) == 'Y') { // kontrol permainan utama
        int level, lives;
        char input[10];

        printf("\nPilih tingkat kesulitan:\n");
        printf("1. Easy (10 LIVES)\n");
        printf("2. Normal (6 LIVES)\n");
        printf("3. Hard (3 LIVES)\n");
        printf("Pilih: ");
        scanf("%s", input); 
        
        // Validasi input level
        if (sscanf(input, "%d", &level) != 1 || level < 1 || level > 3) {
            printf("Input tidak valid! Default ke Normal.\n");
            level = 2;
        }

        switch (level) {
            case 1: lives = 10; break;
            case 2: lives = 6; break;
            case 3: lives = 3; break;
        }

        int random = rand() % LIST_KATA;
        char *kunciJawaban = daftarKata[random];
        char slot[DIGIT_KATA + 1];
        char clue[DIGIT_KATA] = {0};
        int jumlahClue = 0;
        int menang = 0;

        for (int i = 0; i < DIGIT_KATA; i++) slot[i] = '_';

        printf("\n=== TYPE EXIT TO BACK TO MENU ===\n");

        while (lives > 0 && !menang) {
            printf("\n%d LIVES\n", lives);
            printf("| ");
            for (int i = 0; i < DIGIT_KATA; i++) printf("%c | ", slot[i]);
            printf("\n");

            // tampilkan clue
            if (jumlahClue > 0) {
                printf("Clue: ");
                for (int i = 0; i < jumlahClue; i++) {
                    printf("%c", clue[i]);
                    if (i < jumlahClue - 1) printf(", ");
                }
                printf("\n");
            }

            printf("Ketik kata tebakanmu: ");
            char tebakan[10];
            scanf("%s", tebakan);

            // ubah ke kapital
            for (int i = 0; tebakan[i]; i++) tebakan[i] = toupper(tebakan[i]);

            if (strcmp(tebakan, "EXIT") == 0) {
                printf("\nKamu keluar dari permainan.\n");
                printf("Total skor kamu: %d\n", score);
                lastGameScore = score;
                sleep(1);
                return;
            }

            if (strlen(tebakan) != DIGIT_KATA) {
                printf("Kata harus %d huruf!\n", DIGIT_KATA);
                continue;
            }

            printf("\n===============================\n");

            if (strcmp(tebakan, kunciJawaban) == 0) {
                menang = 1;
                for (int i = 0; i < DIGIT_KATA; i++) slot[i] = kunciJawaban[i];
                break;
            }

            lives--;

            int correctPlace[DIGIT_KATA] = {0};
            int correctLetter[DIGIT_KATA] = {0};

            for (int i = 0; i < DIGIT_KATA; i++) {
                if (tebakan[i] == kunciJawaban[i]) {
                    slot[i] = kunciJawaban[i];
                    correctPlace[i] = 1;
                    correctLetter[i] = 1;
                }
            }

            for (int i = 0; i < DIGIT_KATA; i++) {
                if (!correctPlace[i]) {
                    for (int j = 0; j < DIGIT_KATA; j++) {
                        if (!correctLetter[j] && tebakan[i] == kunciJawaban[j] && i != j) {
                            int ada = 0;
                            for (int k = 0; k < jumlahClue; k++) {
                                if (clue[k] == tebakan[i]) { ada = 1; break; }
                            }
                            if (!ada && jumlahClue < DIGIT_KATA)
                                clue[jumlahClue++] = tebakan[i];
                            correctLetter[j] = 1;
                            break;
                        }
                    }
                }
            }
        }

        printf("\n");
        if (menang) {
            int poinMenang = 0;
            if (level == 1) poinMenang = 10 + (lives * 5);
            else if (level == 2) poinMenang = 30 + (lives * 10);
            else if (level == 3) poinMenang = 50 + (lives * 20);
            score += poinMenang;

            printf("| ");
            for (int i = 0; i < DIGIT_KATA; i++) printf("%c | ", slot[i]);
            printf("\n");

            printf("Selamat!! Kata kali ini adalah [%s]\n", kunciJawaban);
            printf("Kamu mendapat %d poin!\n", poinMenang);
            printf("Total skor kamu sekarang: %d\n", score);
        } else {
            printf("Kamu kehabisan nyawa!\n");
            printf("Kata sebenarnya: [%s]\n", kunciJawaban);
            printf("Skor kamu tetap: %d\n", score);
        }

        printf("\n==============================\n");
        printf("Mau main lagi? (Y/N): ");
        scanf(" %c", &mainLagi);
        mainLagi = toupper(mainLagi);

        if (mainLagi == 'N') {
            printf("\nTotal skor akhir kamu: %d\n", score);
            lastGameScore = score;
            printf("Terima kasih sudah bermain!\n");
            sleep(1);
            return;
        }
    }
}
