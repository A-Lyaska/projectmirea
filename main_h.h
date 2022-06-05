#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <iomanip>
#include <vector>
#include <cstdlib>
using namespace std;

class Programm {
    int activeMenuItem = 0;
    int ch = 0;
    bool exit = false;
};

    struct Queen: public Programm {
        int health;   int protection;
        int damage;   int cycle;
        int count;    bool green;   bool black;    bool orange;
    };

    struct Units: public Programm {
        int health;       int protection;
        int damage;       int branch;
        int sheet;        int dewdrop;
        int stone;        int target_count;
        bool green;       bool black;           bool orange;
        int bite_count;   bool invulnerability;
    };

    struct Resourses: public Programm {
        int branch;   int dewdrop;
        int stone;    int leaf;
    };