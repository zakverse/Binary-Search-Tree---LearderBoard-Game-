#ifndef LEADERBOARD_H
#define LEADERBOARD_H
#define Nil NULL

#include <locale>
#include <iostream>
using namespace std;

struct leaderboard{
    int score;
    string id;
    string username;
    int level;
    string rank;
};

typedef struct BST *node;

struct BST{
    leaderboard info;
    node left;
    node right;
};

typedef node BinTree;

// Harus ada
//============================================================
bool isEmpty(BinTree tree);
void createTree(BinTree &tree);
node alokasi(leaderboard info);
void dealokasi(node nodeHapus);
void insertNode(BinTree &tree, node nodeBaru);
//============================================================

//Print
//============================================================
void inOrder(BinTree tree);
void postOrder(BinTree tree);
void preOrder(BinTree tree);
void printLeaderboard(BinTree tree);
// void levelOrder(BinTree tree);
// void printTopN(BinTree tree, int n);
//============================================================

// Search
//============================================================
bool searchByIdHelper(BinTree tree, string id);
void searchById(BinTree tree, string id);
bool searchByUsernameHelper(BinTree tree, string username);
void searchByUsername(BinTree tree, string username);
// void searchByScore(BinTree tree, int score);
void searchByRange(BinTree tree, int minScore, int maxScore);
//=============================================================

// Delete
//=============================================================
node mostRight(BinTree tree);
node mostLeft(BinTree tree);
node deletebyScore(BinTree &tree, int score);
bool deleteById(BinTree &tree, string id);
bool deleteByUsername(BinTree &tree, string username);
//=============================================================

// Update
//=============================================================
bool findPlayerByUsername(BinTree tree, string username, leaderboard &result);
bool updateScoreByUsername(BinTree &tree, string username, int score);
int countPlayers(BinTree tree);
// int countTotalScore(BinTree tree);
//=============================================================

// Input User
//=============================================================
int tentukanLevel(int score);
string tentukanRank(int score);
leaderboard inputPlayer();
void InfoPlayer(BinTree tree);
//=============================================================

void printHeader();

#endif