#include "leaderboard.h"
#include <iostream>
#include <limits>
using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#endif
}

void pause() {
    cout << "\nTekan ENTER untuk melanjutkan...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int main() {
    BinTree tree;
    createTree(tree);

    int choice;

    do {
        clearScreen();
    cout << "==========================================================================\n";
    cout << "  |                        MENU LEADERBOARD BST                        |\n";
    cout << "==========================================================================\n";
    cout << "  | 1. Tambah Pemain                                                   |\n";
    cout << "  | 2. Tampilkan Leaderboard (Score Tertinggi -> Terendah)             |\n";
    cout << "  | 3. Cari Pemain berdasarkan ID                                      |\n";
    cout << "  | 4. Cari Pemain berdasarkan Username                                |\n";
    cout << "  | 5. Cari Pemain berdasarkan Range Score                             |\n";
    cout << "  | 6. Hapus Pemain berdasarkan ID                                     |\n";
    cout << "  | 7. Hapus Pemain berdasarkan Username                               |\n";
    cout << "  | 8. Update Score Pemain                                             |\n";
    cout << "  | 9. Tampilkan Jumlah Pemain                                         |\n";
    cout << "  | 0. Keluar                                                          |\n";
    cout << "==========================================================================\n";
    cout << "Pilih menu: ";
        cin >> choice;

        clearScreen();

        switch (choice) {

        case 1: {
            leaderboard p = inputPlayer();
            insertNode(tree, alokasi(p));
            cout << ">> Pemain berhasil ditambahkan!\n";
            break;
        }

        case 2:
            printHeader();
            printLeaderboard(tree);
            break;

        case 3: {
            string id;
            cout << "Masukkan ID pemain: ";
            cin >> id;
            printHeader();
            searchById(tree, id);
            break;
        }

        case 4: {
            string uname;
            cout << "Masukkan Username pemain: ";
            cin >> uname;
            printHeader();
            searchByUsername(tree, uname);
            break;
        }

        case 5: {
            int minScore, maxScore;
            cout << "Masukkan score minimum: ";
            cin >> minScore;
            cout << "Masukkan score maksimum: ";
            cin >> maxScore;
            printHeader();
            searchByRange(tree, minScore, maxScore);
            break;
        }

        case 6: {
            string id;
            cout << "Masukkan ID pemain yang ingin dihapus: ";
            cin >> id;
            if (deleteById(tree, id))
                cout << ">> Pemain berhasil dihapus.\n";
            else
                cout << ">> Pemain tidak ditemukan.\n";
            break;
        }

        case 7: {
            string uname;
            cout << "Masukkan Username pemain yang ingin dihapus: ";
            cin >> uname;
            if (deleteByUsername(tree, uname))
                cout << ">> Pemain berhasil dihapus.\n";
            else
                cout << ">> Pemain tidak ditemukan.\n";
            break;
        }

        case 8: {
            string uname;
            int score;
            cout << "Masukkan Username: ";
            cin >> uname;
            cout << "Masukkan score baru: ";
            cin >> score;
            if (updateScoreByUsername(tree, uname, score))
                cout << ">> Score berhasil diupdate.\n";
            else
                cout << ">> Gagal update score.\n";
            break;
        }

        case 9:
            cout << "Jumlah pemain saat ini: " << countPlayers(tree) << endl;
            break;

        case 0:
            cout << "Terima kasih, program selesai.\n";
            break;

        default:
            cout << "Pilihan tidak valid!\n";
        }

        if (choice != 0)
            pause();

    } while (choice != 0);

    return 0;
}
