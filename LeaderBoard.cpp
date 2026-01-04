#include "leaderboard.h"
#include <iostream>
#include <iomanip>

using namespace std;

bool isEmpty(BinTree tree){
    return tree == Nil;
}

void createTree(BinTree &tree){
    tree = Nil;
}

node alokasi(leaderboard info){
    node nodeBaru = new BST;
    nodeBaru->info.score = info.score;
    nodeBaru->info.id = info.id;
    nodeBaru->info.username = info.username;
    nodeBaru->info.level = info.level;
    nodeBaru->info.rank = info.rank;
    nodeBaru->left = Nil;
    nodeBaru->right = Nil;
    return nodeBaru;
}

void dealokasi(node nodeHapus){
    nodeHapus->left = NULL;
    nodeHapus->right = NULL;
    delete nodeHapus;
}

void insertNode(BinTree &tree, node nodeBaru){
    if(isEmpty(tree)){
        tree = nodeBaru;
    } else if(nodeBaru->info.score < tree->info.score){
        insertNode(tree->left, nodeBaru);
    } else if(nodeBaru->info.score > tree->info.score){
        insertNode(tree->right, nodeBaru);
    }else{
        insertNode(tree->right, nodeBaru);
    }
}
    

void InfoPlayer(BinTree tree){
    cout << "  | " << left << setw(8) << tree->info.score 
            << "| " << setw(10) << tree->info.id 
            << "| " << setw(18) << tree->info.username 
            << "| " << setw(8) << tree->info.level 
            << "| " << setw(15) << tree->info.rank << "|" << endl;
}

void preOrder(BinTree tree){
    if(isEmpty(tree)){
        return;
    }
    InfoPlayer(tree);
    preOrder(tree->left);
    preOrder(tree->right);
}

void inOrder(BinTree tree){
    if(isEmpty(tree)){
        return;
    }
    inOrder(tree->left);
    InfoPlayer(tree);
    inOrder(tree->right);
}

void postOrder(BinTree tree){
    if(isEmpty(tree)){
        return;
    }
    postOrder(tree->left);
    postOrder(tree->right);
    InfoPlayer(tree);
}

// void levelOrder(BinTree tree){

// }

void printLeaderboard(BinTree tree){
    if(isEmpty(tree)){
        return;
    }
    printLeaderboard(tree->right);
    InfoPlayer(tree);
    printLeaderboard(tree->left);
}

// void printTopN(BinTree tree, int n){

// }

int tentukanLevel(int score){
    return (score/500) + 1;
}

string tentukanRank(int score){
    if (score >= 3000){
        return "platinum";
    }else if (score >= 2000){
        return "Gold";
    }else if (score >= 1000){
        return "Silver";
    }else{
        return "Bronze";
    }
}

leaderboard inputPlayer() {
    leaderboard p;
        cout << "==========================================================================\n";
        cout << "  |                           INPUT DATA PEMAIN                        |\n";
        cout << "==========================================================================\n";
    cout << "  | ID         : ";
    cin >> p.id;
    cout << "  | Username   : ";
    cin >> p.username;
    cout << "  | Score      : ";
    cin >> p.score;
    p.level = tentukanLevel(p.score);
    p.rank = tentukanRank(p.score);
    return p;
}

void searchById(BinTree tree, string id){
    if (isEmpty(tree)) return;
    if (!searchByIdHelper(tree, id)){
        cout << "ID " << id << " tidak ditemukan !!!" << endl;
    }
}

bool searchByIdHelper(BinTree tree, string id){
    if (isEmpty(tree)) return false;
    if (tree->info.id == id){
        InfoPlayer(tree);
        return true;
    }
    return searchByIdHelper(tree->left, id) || searchByIdHelper(tree->right, id);
}

bool searchByUsernameHelper(BinTree tree, string username){
    if (isEmpty(tree)) return false;
    if (tree->info.username == username){
        InfoPlayer(tree);
        return true;
    }
    return searchByUsernameHelper(tree->left, username) || searchByUsernameHelper(tree->right, username);
}

void searchByUsername(BinTree tree, string username){
    if (isEmpty(tree)) return;
    if (!searchByUsernameHelper(tree, username)){
        cout << "Username " << username << " tidak ditemukan !!!" << endl;
    }
}

void searchByRange(BinTree tree, int minScore, int maxScore) {
    // Basis Rekursi: Jika pohon kosong, kembali
    if (tree == Nil) {
        return;
    }

    // 1. Cek Subtree Kiri
    // Hanya perlu menjelajahi subtree kiri jika minScore lebih kecil dari skor node saat ini.
    // Jika minScore sudah lebih besar dari skor node saat ini, semua node di kiri
    // pasti di luar rentang, jadi lewati.
    if (minScore < tree->info.score) {
        searchByRange(tree->left, minScore, maxScore);
    }

    // 2. Cek Node Saat Ini
    // Jika skor node saat ini berada dalam rentang [minScore, maxScore], cetak.
    if (tree->info.score >= minScore && tree->info.score <= maxScore) {
        InfoPlayer(tree); // Asumsi fungsi InfoPlayer mencetak detail
    }

    // 3. Cek Subtree Kanan
    // Hanya perlu menjelajahi subtree kanan jika maxScore lebih besar dari skor node saat ini.
    // Jika maxScore sudah lebih kecil dari skor node saat ini, semua node di kanan
    // pasti di luar rentang, jadi lewati.
    if (maxScore > tree->info.score) {
        searchByRange(tree->right, minScore, maxScore);
    }
}

node mostRight(BinTree tree){
    while (tree->right != Nil){
        tree = tree->right;
    }
    return tree;
}

node mostLeft(BinTree tree){
    while (tree->left != Nil){
        tree = tree->right;
    }
    return tree;
}

node deletebyScore(BinTree &tree, int score){
    if (isEmpty(tree)) {
        return Nil; //data tidak ditemukan di subtree ini
    } else {
        if (score < tree->info.score) {
            return deletebyScore(tree->left, score);
        } else if (score > tree->info.score) {
            return deletebyScore(tree->right, score);
        } else {
            //jika node yang mau dihapus ditemukan
            //Case 1 : node yang mau dihapus adalah leaf
            if (tree->left == Nil && tree->right == Nil) {
                node tmp = tree;
                tree = Nil;
                dealokasi(tmp);
            }
            //Case 2 : node yang mau dihapus hanya punya right child
            else if (tree->left == Nil) {
                node tmp = tree;
                tree = tree->right;
                dealokasi(tmp);
            }
            //Case 3 : node yang mau dihapus hanya punya left child
            else if (tree->right == Nil) {
                node tmp = tree;
                tree = tree->left;
                dealokasi(tmp);
            }
            // Case 4 : jika node yang mau dihapus punya dua child, maka ambil mostleft dari subtree kanan untuk menggantikan node yang mau dihapus
            else {
                //mostleft dari subtree kanan = node successor (node penerus)
                node successor = mostLeft(tree->right);
                //salin data successor ke node saat ini
                tree->info = successor->info;
                //hapus successor pada subtree kanan
                return deletebyScore(tree->right, successor->info.score);
            }
            return tree; //berhasil dihapus
        }
    }
}

bool deleteById(BinTree &tree, string id){
    if (isEmpty(tree)) return false;
    if (tree->info.id == id){
        int scoreDitemukan = tree->info.score;
        deletebyScore(tree, scoreDitemukan);
        return true;
    }
    return deleteById(tree->left, id) || deleteById(tree->right, id);
}

bool deleteByUsername(BinTree &tree, string username){
    if (isEmpty(tree)) return false;
    if (tree->info.username == username){
        int scoreDitemukan = tree->info.score;
        deletebyScore(tree, scoreDitemukan);
        return true;
    }
    return deleteByUsername(tree->left,username ) || deleteByUsername(tree->right, username);
}

bool findPlayerByUsername(BinTree tree, string username, leaderboard &result){
    if (isEmpty(tree)) return false;
    if (tree->info.username == username){
        result = tree->info; // ambil DATA
        return true;
    }
    return findPlayerByUsername(tree->left, username, result) || findPlayerByUsername(tree->right, username, result);
}

bool updateScoreByUsername(BinTree &tree , string username, int score){
    if(isEmpty(tree)){
        cout << "Kosong" << endl;
    }
    leaderboard data;
    if (!findPlayerByUsername(tree, username, data)){
        return false;
    }
    deleteByUsername(tree, username);
    data.score = score;
    data.level = tentukanLevel(score);
    data.rank  = tentukanRank(score);
    insertNode(tree, alokasi(data));
    return true;
}

int countPlayers(BinTree tree){
    if (isEmpty(tree)) return 0;
    int jumlah = 1 + countPlayers(tree->left) + countPlayers(tree->right);
    return jumlah;
}

void printHeader() {
        cout << "==========================================================================\n";
        cout << "  |                             LEADERBOARD                            |\n";
        cout << "==========================================================================\n";
    cout << "  | " << left << setw(8) << "Score" 
        << "| " << setw(10) << "ID" 
        << "| " << setw(18) << "Username" 
        << "| " << setw(8) << "Level" 
        << "| " << setw(15) << "Rank" << "|" << endl;
    cout << "------------------------------------------------------------------------" << endl;
}