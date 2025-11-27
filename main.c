#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

// STORAGE & SEARCH
#define MAKS_USER 100
#define NAMA_FILE "data_user.txt"

struct Player {
    char username[50];
    int skorGame1;
    int skorGame2;
    int skorGame3;
    int skorGame4;
    int totalSkor;
};

struct Player daftarUser[MAKS_USER];
int jumlahUser = 0;

// Deklarasi fungsi game dari file terpisah
#include "gamesatu.h"
#include "gamedua.h"
#include "gametiga.h"
#include "gameempat.h"

// global untuk menangkap skor dari tiap game tanpa mengubah logika utama game terlalu banyak
int lastGameScore = 0; // di-set oleh setiap game sebelum return

int cariUser(char nama[]) {
    for (int i = 0; i < jumlahUser; i++) {
        if (strcmp(daftarUser[i].username, nama) == 0) return i;
    }
    return -1;
}

// FILE MANAGEMENT
void saveDataToFile() {
    FILE *fp = fopen(NAMA_FILE, "w");
    if (!fp) {
        printf("Gagal membuka file untuk menyimpan data!\n");
        return;
    }

    // tulis jumlah user
    fprintf(fp, "%d\n", jumlahUser);

    for (int i = 0; i < jumlahUser; i++) {
        // format: username totalSkor skorGame1 skorGame2 skorGame3 skorGame4
        fprintf(fp, "%s %d %d %d %d %d\n",
            daftarUser[i].username,
            daftarUser[i].totalSkor,
            daftarUser[i].skorGame1,
            daftarUser[i].skorGame2,
            daftarUser[i].skorGame3,
            daftarUser[i].skorGame4);
    }

    fclose(fp);
    //printf("Data berhasil disimpan ke '%s'.\n", NAMA_FILE);
}


// Fungsi untuk memuat data dari file saat program dimulai
void loadDataFromFile() {
    FILE *fp = fopen(NAMA_FILE, "r");
    if (!fp) {
        return;
    }

    int n = 0;
    if (fscanf(fp, "%d", &n) != 1) {
        fclose(fp);
        return;
    }

    if (n < 0 || n > MAKS_USER) {
        fclose(fp);
        return;
    }

    jumlahUser = n;

    for (int i = 0; i < jumlahUser; i++) {
        fscanf(fp, "%49s %d %d %d %d %d",
            daftarUser[i].username,
            &daftarUser[i].totalSkor,
            &daftarUser[i].skorGame1,
            &daftarUser[i].skorGame2,
            &daftarUser[i].skorGame3,
            &daftarUser[i].skorGame4);
    }

    fclose(fp);
}

// LEADERBOARD
void tampilLeaderboard() {
    printf("===== LEADERBOARD =====\n");

    // copy untuk sorting
    struct Player temp[MAKS_USER];
    for (int i = 0; i < jumlahUser; i++) temp[i] = daftarUser[i];

    for (int i = 0; i < jumlahUser - 1; i++) {
        for (int j = i + 1; j < jumlahUser; j++) {
            if (temp[j].totalSkor > temp[i].totalSkor) {
                struct Player swap = temp[i];
                temp[i] = temp[j];
                temp[j] = swap;
            }
        }
    }

    for (int i = 0; i < jumlahUser; i++) {
        printf("%d. %s - %d poin\n", i + 1, temp[i].username, temp[i].totalSkor);
    }
}

// FUNGSI REKURSIF UNTUK MENAMPILKAN RIWAYAT USER
void tampilRiwayatRekursif(struct Player user, int index) {
    // BASE CASE: sudah melewati game ke-4
    if (index > 4) {
        return;
    }

    char* namaGame;
    int skor;

    // Tentukan game berdasarkan index
    switch(index) {
        case 1: 
            namaGame = "Tebak Angka";
            skor = user.skorGame1;
            break;
        case 2:
            namaGame = "Batu Gunting Kertas";
            skor = user.skorGame2;
            break;
        case 3:
            namaGame = "Soal Matematika"; 
            skor = user.skorGame3;
            break;
        case 4:
            namaGame = "Tebak Kata";
            skor = user.skorGame4;
            break;
    }

    // Tampilkan data game saat ini
    printf("  %s: %d poin\n", namaGame, skor);

    // RECURSIVE CASE: panggil fungsi yang sama untuk game berikutnya
    tampilRiwayatRekursif(user, index + 1);
}

// FUNGSI UNTUK MENAMPILKAN RIWAYAT USER
void tampilRiwayatUser(int idxUser) {
    sleep(1);
    printf("\n\n=== RIWAYAT PERMAINAN ===\n");
    printf("User: %s\n", daftarUser[idxUser].username);
    printf("Total Skor: %d\n", daftarUser[idxUser].totalSkor);
    
    // Mulai rekursi dari game 1
    tampilRiwayatRekursif(daftarUser[idxUser], 1);
    printf("==========================\n");
}

// Main menu 
int main() {
    loadDataFromFile(); 
    srand(time(NULL));

    char username[50];
    printf("Masukkan username Anda: ");
    scanf("%49s", username);

    int idx = cariUser(username);
    if (idx == -1) {
        // buat akun baru
        strcpy(daftarUser[jumlahUser].username, username);
        daftarUser[jumlahUser].skorGame1 = 0;
        daftarUser[jumlahUser].skorGame2 = 0;
        daftarUser[jumlahUser].skorGame3 = 0;
        daftarUser[jumlahUser].skorGame4 = 0;
        daftarUser[jumlahUser].totalSkor = 0;
        idx = jumlahUser;
        jumlahUser++;
        printf("Akun baru dibuat: %s\n", username);
    } else {
        printf("Welcome back, %s!\n", username);
    }

    int pilihan = -1;
    while (pilihan != 7) {
        printf("\n\n==========================================\n\n");
        printf("|| Selamat datang di Arcade Kelompok 2! ||\n");
        printf("\n\n==========================================\n\n");
        printf("Pilih game yang ingin Anda mainkan:\n");
        printf("1. Tebak Angka\n");
        printf("2. Batu Gunting Kertas\n");
        printf("3. Soal Matematika\n");
        printf("4. Tebak Kata\n");
        printf("5. Lihat Riwayat Saya\n"); 
        printf("6. Lihat Leaderboard\n"); 
        printf("7. Keluar\n"); 
        printf("Masukkan pilihan Anda (1-7): ");
        if (scanf("%d", &pilihan) != 1) {
            // clear input
            int c; 
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Input tidak valid. Coba lagi.\n");
            continue;
        }

        lastGameScore = 0; // reset
        switch (pilihan) {
            case 1:
                Gamesatu(); // game akan set lastGameScore
                daftarUser[idx].skorGame1 += lastGameScore;
                break;
            case 2:
                Gamedua();
                daftarUser[idx].skorGame2 += lastGameScore;
                break;
            case 3:
                Gametiga();
                daftarUser[idx].skorGame3 += lastGameScore;
                break;
            case 4:
                Gameempat();
                daftarUser[idx].skorGame4 += lastGameScore;
                break;
            case 5:  // LIHAT RIWAYAT
                tampilRiwayatUser(idx);  
                break;
            case 6:
                tampilLeaderboard();
                saveDataToFile();
                break;
            case 7: // exit
                printf("Terima kasih telah bermain! Sampai jumpa lagi!\n");
                saveDataToFile();
                exit(0);
            default:
                printf("Pilihan tidak valid. Coba lagi.\n");
        }

        // update total skor user
        daftarUser[idx].totalSkor = daftarUser[idx].skorGame1 
                                  + daftarUser[idx].skorGame2 
                                  + daftarUser[idx].skorGame3 
                                  + daftarUser[idx].skorGame4;

        if (pilihan >= 1 && pilihan <= 4) {
            printf("Skor ronde yang tercatat untuk akun Anda: %d\n", lastGameScore);
            printf("Total skor sekarang (%s): %d\n\n", daftarUser[idx].username, daftarUser[idx].totalSkor);
            sleep(1);
        }
    }

    return 0;
}
