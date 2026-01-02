#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define MAX 100   // Maksimal 100 pesanan

// Struktur data pesanan
typedef struct {
    int kode;
    char nama[50];
    int harga;
    int jumlah;
    int subtotal;
} Pesanan;

// Database menu restoran
typedef struct {
    int kode;
    char nama[50];
    int harga;
} Menu;

// Array global
Pesanan list[MAX];
Menu daftarMenu[10];
int jumlahPesanan = 0;


// ================================
// PROTOTYPE FUNGSI
// ================================
void initMenu();
void headerProgram();
void tampilMenuMakanan();
void inputPesananAwal();
void tambahPesanan();
void hapusPesanan();
void lihatPesanan();
void menuEditPesanan();
int cariMenuByKode(int kode);
void sortingHargaAscending();
void searchingNamaMenu();
void pembayaran();
void cetakStruk(char metode[]);
void waktuSekarang(char *tanggal, char *jam);


// ================================
// MAIN PROGRAM
// ================================
int main() {
    int pilihan;

    initMenu(); // Inisialisasi menu restoran

    do {
        headerProgram();
        printf("===== SISTEM KASIR RESTORAN =====\n");
        printf("1. Input Pesanan Awal\n");
        printf("2. Tambah / Hapus / Lihat Pesanan\n");
        printf("3. Pembayaran & Cetak Struk\n");
        printf("4. Sorting Harga Pesanan\n");
        printf("5. Searching Nama Menu\n");
        printf("6. Keluar\n");
        printf("Pilih menu : ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                inputPesananAwal();
                break;

            case 2:
                menuEditPesanan();
                break;

            case 3:
                pembayaran();
                break;

            case 4:
                sortingHargaAscending();
                break;

            case 5:
                searchingNamaMenu();
                break;

            case 6:
                printf("\nTerima kasih telah menggunakan program kasir!\n");
                break;

            default:
                printf("Pilihan tidak valid!\n");
        }

        printf("\nTekan ENTER untuk melanjutkan...");
        getchar();
        getchar();

    } while (pilihan != 6);

    return 0;
}


// ================================
// FUNGSI: HEADER PROGRAM
// ================================
void headerProgram() {
    system("cls"); // Windows, kalau linux ganti "clear"
    printf("===========================================\n");
    printf("          PROGRAM KASIR RESTORAN\n");
    printf("===========================================\n\n");
}


// ================================
// FUNGSI: Inisialisasi Menu
// ================================
void initMenu() {
    daftarMenu[0] = (Menu){101, "Nasi Goreng", 20000};
    daftarMenu[1] = (Menu){102, "Ayam Bakar", 25000};
    daftarMenu[2] = (Menu){103, "Mie Ayam", 15000};
    daftarMenu[3] = (Menu){104, "Soto Ayam", 18000};
    daftarMenu[4] = (Menu){105, "Es Teh", 5000};
    daftarMenu[5] = (Menu){106, "Teh Hangat", 4000};
    daftarMenu[6] = (Menu){107, "Jus Alpukat", 12000};
    daftarMenu[7] = (Menu){108, "Jus Jeruk", 10000};
    daftarMenu[8] = (Menu){109, "Air Mineral", 3000};
    daftarMenu[9] = (Menu){110, "Kopi Hitam", 7000};
}


// ================================
// FUNGSI: Tampilkan Menu Makanan
// ================================
void tampilMenuMakanan() {
    printf("\n============= DAFTAR MENU ==============\n");
    printf("KODE   NAMA MENU             HARGA\n");
    printf("----------------------------------------\n");

    for (int i = 0; i < 10; i++) {
        printf("%d   %-20s Rp %d\n",
               daftarMenu[i].kode,
               daftarMenu[i].nama,
               daftarMenu[i].harga);
    }
}


// ================================
// FUNGSI: Cari Menu Berdasarkan Kode
// ================================
int cariMenuByKode(int kode) {
    for (int i = 0; i < 10; i++) {
        if (daftarMenu[i].kode == kode) {
            return i; // Index ditemukan
        }
    }
    return -1; // Tidak ditemukan
}


// ================================
// FUNGSI: Input Pesanan Awal
// ================================
void inputPesananAwal() {
    int kode, jumlah;

    tampilMenuMakanan();

    printf("\nMasukkan kode menu (0 untuk selesai): ");
    scanf("%d", &kode);

    while (kode != 0) {
        int idx = cariMenuByKode(kode);

        if (idx == -1) {
            printf("Kode menu tidak valid!\n");
        } else {
            printf("Masukkan jumlah pesanan: ");
            scanf("%d", &jumlah);

            list[jumlahPesanan].kode = daftarMenu[idx].kode;
            strcpy(list[jumlahPesanan].nama, daftarMenu[idx].nama);
            list[jumlahPesanan].harga = daftarMenu[idx].harga;
            list[jumlahPesanan].jumlah = jumlah;
            list[jumlahPesanan].subtotal = jumlah * daftarMenu[idx].harga;

            jumlahPesanan++;

            printf("Pesanan berhasil ditambahkan!\n");
        }

        printf("\nMasukkan kode menu berikutnya (0 untuk selesai): ");
        scanf("%d", &kode);
    }
}


// ================================
// FUNGSI: Menu Edit Pesanan
// ================================
void menuEditPesanan() {
    int pilih;

    do {
        headerProgram();

        printf("=========== EDIT PESANAN ===========\n");
        printf("1. Tambah Pesanan\n");
        printf("2. Hapus Pesanan\n");
        printf("3. Lihat Pesanan\n");
        printf("4. Kembali\n");
        printf("Pilih: ");
        scanf("%d", &pilih);

        switch (pilih) {
            case 1:
                tambahPesanan();
                break;

            case 2:
                hapusPesanan();
                break;

            case 3:
                lihatPesanan();
                break;

            case 4:
                return;

            default:
                printf("Pilihan tidak valid!\n");
        }

        printf("\nTekan ENTER...");
        getchar();
        getchar();

    } while (pilih != 4);
}


// ================================
// FUNGSI: Tambah Pesanan Baru
// ================================
void tambahPesanan() {
    int kode, jumlah;

    tampilMenuMakanan();

    printf("\nMasukkan kode menu yang ingin ditambah: ");
    scanf("%d", &kode);

    int idx = cariMenuByKode(kode);

    if (idx == -1) {
        printf("Kode menu tidak ditemukan!\n");
        return;
    }

    printf("Masukkan jumlah pesanan: ");
    scanf("%d", &jumlah);

    list[jumlahPesanan].kode = daftarMenu[idx].kode;
    strcpy(list[jumlahPesanan].nama, daftarMenu[idx].nama);
    list[jumlahPesanan].harga = daftarMenu[idx].harga;
    list[jumlahPesanan].jumlah = jumlah;
    list[jumlahPesanan].subtotal = jumlah * daftarMenu[idx].harga;

    jumlahPesanan++;

    printf("Pesanan berhasil ditambahkan!\n");
}


// ================================
// FUNGSI: Hapus Pesanan Berdasarkan Kode Menu
// ================================
void hapusPesanan() {
    if (jumlahPesanan == 0) {
        printf("\nBelum ada pesanan!\n");
        return;
    }

    lihatPesanan();

    int kode;
    printf("\nMasukkan kode menu yang ingin dihapus: ");
    scanf("%d", &kode);

    int found = -1;

    for (int i = 0; i < jumlahPesanan; i++) {
        if (list[i].kode == kode) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Kode pesanan tidak ditemukan!\n");
        return;
    }

    for (int i = found; i < jumlahPesanan - 1; i++) {
        list[i] = list[i + 1];
    }

    jumlahPesanan--;
    printf("Pesanan berhasil dihapus!\n");
}


// ================================
// FUNGSI: Menampilkan Semua Pesanan
// ================================
void lihatPesanan() {
    if (jumlahPesanan == 0) {
        printf("\nBelum ada pesanan yang dimasukkan!\n");
        return;
    }

    printf("\n=============== DAFTAR PESANAN ===============\n");
    printf("No  Kode   Nama Menu           Harga   Qty   Subtotal\n");
    printf("-------------------------------------------------------\n");

    for (int i = 0; i < jumlahPesanan; i++) {
        printf("%-3d %-6d %-18s %-7d %-5d %-7d\n",
               i + 1,
               list[i].kode,
               list[i].nama,
               list[i].harga,
               list[i].jumlah,
               list[i].subtotal);
    }
}


// ================================
// FUNGSI: Sorting Harga (Ascending)
// ================================
void sortingHargaAscending() {
    if (jumlahPesanan == 0) {
        printf("\nBelum ada pesanan untuk disorting!\n");
        return;
    }

    for (int i = 0; i < jumlahPesanan - 1; i++) {
        for (int j = 0; j < jumlahPesanan - i - 1; j++) {
            if (list[j].harga > list[j + 1].harga) {
                Pesanan temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }

    printf("\nSorting berdasarkan harga (termurah → termahal) berhasil!\n");
    lihatPesanan();
}


// ================================
// FUNGSI: Searching Nama Menu (Linear, Case-Insensitive)
// ================================
void searchingNamaMenu() {
    if (jumlahPesanan == 0) {
        printf("\nBelum ada pesanan!\n");
        return;
    }

    char cari[50];
    fflush(stdin);
    printf("Masukkan nama menu yang dicari: ");
    gets(cari);

    // Ubah input menjadi lowercase
    for (int i = 0; cari[i]; i++) {
        cari[i] = tolower(cari[i]);
    }

    int found = 0;

    printf("\nHasil pencarian untuk '%s':\n", cari);
    printf("-------------------------------------------------------\n");

    for (int i = 0; i < jumlahPesanan; i++) {
        char namaLower[50];
        strcpy(namaLower, list[i].nama);

        // Ubah nama menu menjadi lowercase
        for (int j = 0; namaLower[j]; j++) {
            namaLower[j] = tolower(namaLower[j]);
        }

        if (strstr(namaLower, cari) != NULL) {
            printf("Kode: %d | Menu: %s | Harga: %d | Qty: %d | Subtotal: %d\n",
                   list[i].kode,
                   list[i].nama,
                   list[i].harga,
                   list[i].jumlah,
                   list[i].subtotal);

            found = 1;
        }
    }

    if (!found) {
        printf("Menu tidak ditemukan!\n");
    }
}


// ================================
// FUNGSI: Mendapatkan Tanggal & Jam
// ================================
void waktuSekarang(char *tanggal, char *jam) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    sprintf(tanggal, "%02d-%02d-%04d",
            t->tm_mday, t->tm_mon + 1, t->tm_year + 1900);

    sprintf(jam, "%02d:%02d:%02d",
            t->tm_hour, t->tm_min, t->tm_sec);
}


// ================================
// FUNGSI: Pembayaran
// ================================
void pembayaran() {
    if (jumlahPesanan == 0) {
        printf("\nBelum ada pesanan!\n");
        return;
    }

    int total = 0;

    for (int i = 0; i < jumlahPesanan; i++) {
        total += list[i].subtotal;
    }

    float pajak = total * 0.10;      // pajak 10%
    float diskon = total * 0.05;     // diskon 5%
    float totalAkhir = total + pajak - diskon;

    int metode;
    int uang;
    int kembalian;

    printf("\n=========== PEMBAYARAN ===========\n");
    printf("Total Belanja : Rp %d\n", total);
    printf("Pajak (10%%)   : Rp %.0f\n", pajak);
    printf("Diskon (5%%)   : Rp %.0f\n", diskon);
    printf("-------------------------------------\n");
    printf("Total Akhir   : Rp %.0f\n", totalAkhir);

    printf("\nPilih metode pembayaran:\n");
    printf("1. Cash\n");
    printf("2. QRIS\n");
    printf("Pilih: ");
    scanf("%d", &metode);

    if (metode == 1) {
        // ================= CASH ======================
        do {
            printf("Masukkan uang pembeli: Rp ");
            scanf("%d", &uang);

            if (uang < totalAkhir) {
                printf("Uang tidak cukup! Masukkan kembali.\n");
            }

        } while (uang < totalAkhir);

        kembalian = uang - totalAkhir;

        printf("\nPembayaran berhasil!\n");
        printf("Kembalian: Rp %d\n", kembalian);

        cetakStruk("CASH");

    } else if (metode == 2) {
        // ================ QRIS ======================
        printf("\nSilakan scan QRIS...\n");
        printf("(anggap berhasil)\n");

        cetakStruk("QRIS");

    } else {
        printf("Metode pembayaran tidak valid!\n");
    }
}


// ================================
// FUNGSI: Cetak Struk Pembelian
// ================================
void cetakStruk(char metode[]) {
    char tanggal[20], jam[20];
    waktuSekarang(tanggal, jam);

    int total = 0;
    for (int i = 0; i < jumlahPesanan; i++) {
        total += list[i].subtotal;
    }

    float pajak = total * 0.10;
    float diskon = total * 0.05;
    float totalAkhir = total + pajak - diskon;

    printf("\n\n=====================================\n");
    printf("            STRUK PEMBELIAN           \n");
    printf("=====================================\n");
    printf("Tanggal : %s\n", tanggal);
    printf("Waktu   : %s\n", jam);
    printf("-------------------------------------\n");

    for (int i = 0; i < jumlahPesanan; i++) {
        printf("%-15s x%-2d = Rp %d\n",
               list[i].nama,
               list[i].jumlah,
               list[i].subtotal);
    }

    printf("-------------------------------------\n");
    printf("Total            : Rp %d\n", total);
    printf("Pajak (10%%)      : Rp %.0f\n", pajak);
    printf("Diskon (5%%)      : Rp %.0f\n", diskon);
    printf("TOTAL AKHIR      : Rp %.0f\n", totalAkhir);
    printf("Metode Bayar     : %s\n", metode);
    printf("=====================================\n");
    printf("            TERIMA KASIH!            \n");
    printf("=====================================\n\n");
}

