#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <unistd.h>
#include "gametiga.h"

void Gametiga() {
    static int highscore = 0;  // Menyimpan skor tertinggi dalam satu sesi
    float jawaban, jawabanBenar;  
    int bil1, bil2, operasi, skor = 0;
    char lambang;
    char mainlagi = 'Y'; // kontrol main lagi dengan Y/N

    printf("\n=== Game Soal Matematika ===\n");
    printf("Highscore Anda: %d\n", highscore);

    srand(time(0)); // Mengacak angka berdasarkan waktu saat ini

    while (toupper(mainlagi) == 'Y') { 
        operasi = rand() % 4;    // 0=+, 1=-, 2=*, 3=/
        bil1 = rand() % 99 + 1;  // Angka 1–100
        bil2 = rand() % 99 + 1;

        // Tentukan operasi dan hasil benar
        switch (operasi) {
            case 0:
                jawabanBenar = bil1 + bil2;
                lambang = '+';
                break;
            case 1:
                jawabanBenar = bil1 - bil2;
                lambang = '-';
                break;
            case 2:
                jawabanBenar = bil1 * bil2;
                lambang = '*';
                break;
            case 3:
                if (bil2 == 0) bil2 = 1;
                jawabanBenar = (float) bil1 / bil2;
                lambang = '/';
                break;
        }

        printf("\nBerapakah hasil dari %d %c %d ?\n", bil1, lambang, bil2);
        printf("Masukkan jawaban anda: ");

        // Validasi input agar angka
        while (scanf("%f", &jawaban) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);  // bersihkan buffer
            printf("Input tidak valid! Jawaban harus berupa angka.\n");
            printf("Masukkan jawaban anda: ");
        }

        // Bersihkan newline sisa
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);

        // Cek jawaban benar (selisih < 0.01)
        if (fabs(jawaban - jawabanBenar) < 0.01) {
            skor += 10;
            printf("Jawaban Anda benar!\n");
        } else {
            skor -= 10;
            if (skor < 0) skor = 0; // Skor tidak boleh negatif
            printf("Jawaban Anda salah. Jawaban yang benar adalah %.2f\n", jawabanBenar);
        }

        printf("Skor anda: %d\n", skor);

        // Tanya main lagi
        printf("Mau main lagi? (Y/N): ");
        scanf(" %c", &mainlagi);

        if (toupper(mainlagi) == 'N') {
            if (skor > highscore) {
                highscore = skor; // Update highscore
            }

            printf("\nTerima kasih telah bermain!\n");
            printf("Skor akhir Anda: %d\n", skor);

            // kirim skor ke main.c
            lastGameScore = skor;
            sleep(1);
            return; // kembali ke menu utama
        }
    }
}
