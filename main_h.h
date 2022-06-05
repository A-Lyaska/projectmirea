#include <iostream>
#include <time.h>
#include <map>
#include <conio.h>
#include <string>
#include <windows.h>

using namespace std;

void line() {
    cout
            << "---------------------------------------------------------------------------------------------------------------------"
            << endl;
}

void line2() {
    cout << "################################################" << endl;
}

bool FlagAttack = false, FlagOut = false;
int RedWorker_count = 14, GreenWorker_count = 17, RedWarrior_count = 6, GreenWarrior_count = 5;
int RedLarva, GreenLarva;

struct Heap {
    int branch, stone, leaf, dewdrop;
};

Heap heap1 = {15, 39, 0, 39};
Heap heap2 = {19, 0, 41, 0};
Heap heap3 = {17, 0, 42, 0};
Heap heap4 = {49, 37, 0, 0};
Heap heap5 = {23, 21, 40, 0};

map<string, int> Green_resource = {
        {"branch",  0},
        {"dewdrop", 0},
        {"leaf",    0},
        {"stone",   0}
};
map<string, int> Red_resource = {
        {"branch",  0},
        {"dewdrop", 0},
        {"leaf",    0},
        {"stone",   0}
};

class Ant {
public:

    int health, armor, heap_location;
    char colony;

    void Attack(int damage, int Bites_count, int warrior_heap_location) {
        if (warrior_heap_location == heap_location && health > 0) {
            FlagAttack = true;
            (armor > 0) ? armor = armor - (damage * Bites_count) : health = health - (damage * Bites_count);
        }
    }

    Ant() {}

    Ant(int h, int a, char c, int g) {
        health = h;
        armor = a;
        colony = c;
        heap_location = g;
    }



};

class Warrior : public Ant {
public:
    int damage, target, Bites_count;

    void Setter_War(int health, int armor, char colony, int heap_location, int damage, int target, int Bites_count) {
        this->health = health;
        this->armor = armor;
        this->colony = colony;
        this->heap_location = heap_location;
        this->damage = damage;
        this->target = target;
        this->Bites_count = Bites_count;
    }

    Warrior(int h, int a, char c, int g, int d, int t, int BC) : Ant(h, a, c, g) {
        target = t;
        Bites_count = BC;
        damage = d;
    };

    Warrior() {}

    static void Print_Ant(string type, int health, int armor, int damage, string Qname, char job) {
        cout << "---------------------------------------\n---------------------------------------";
        cout << "\nТип: " << type << endl;
        cout << "   Здоровье = " << health << ", защита = " << armor << ", урон = " << damage << endl;
        cout << "   Королева << " << Qname << " >>" << endl;
        cout << "---------------------------------------\n---------------------------------------" << endl;
    }
};

class Medvedka : public Ant {
public:

    int Resource_count;
    char Resource[2];

    Medvedka(int h, int a, char c, int g, int RC, char R1, char R2) : Ant(h, a, c, g) {
        Resource_count = RC;
        Resource[0] = R1;
        Resource[1] = R2;
    }
};

class Sverchok : public Ant {
public:

    int damage;
    int target;
    int Bites_count;
    int Resource_count;
    char Resource[2];

    Sverchok(int h, int a, char c, int g, int d, int t, int BC, int RC, char R1, char R2) : Ant(h, a, c, g) {
        damage = d;
        target = t;
        Bites_count = BC;
        Resource_count = RC;
        Resource[0] = R1;
        Resource[1] = R2;
    }
};

class Worker : public Ant {
public:

    int Resource_count;
    char Resource[2];

    void Worker_frame(int h, int a, char c, int g, int RC, char R1, char R2, char R3) {
        this->health = h;
        this->armor = a;
        this->colony = c;
        this->heap_location = g;
        this->Resource_count = RC;
        this->Resource[0] = R1;
        this->Resource[1] = R2;
        this->Resource[2] = R3;
    }

    virtual void Resource_collecting(Heap heapRandom) {
        for (int i = 0; i < Resource_count; i++) {
            bool flag = false;
            for (int j = 0; j < 2; j++) {
                if (flag == 0) {
                    switch (Resource[j]) {
                        case 'b': {
                            if (heapRandom.branch > 0) {
                                heapRandom.branch = heapRandom.branch - 1;
                                (colony == 'g') ? Green_resource["branch"]++ : Red_resource["branch"]++;
                                flag = true;
                            }
                            continue;
                            break;
                        }

                        case 'd': {
                            if (heapRandom.dewdrop > 0) {
                                heapRandom.dewdrop = heapRandom.dewdrop - 1;
                                (colony == 'g') ? Green_resource["dewdrop"]++ : Red_resource["dewdrop"]++;
                                flag = true;
                            }
                            continue;
                            break;
                        }

                        case 'l': {
                            if (heapRandom.leaf > 0) {
                                heapRandom.leaf = heapRandom.leaf - 1;
                                (colony == 'g') ? Green_resource["leaf"]++ : Red_resource["leaf"]++;
                                flag = true;
                            }
                            continue;
                            break;
                        }

                        case 's': {
                            if (heapRandom.stone > 0) {
                                heapRandom.stone = heapRandom.stone - 1;
                                (colony == 'g') ? Green_resource["stone"]++ : Red_resource["stone"]++;
                                flag = true;
                            }
                            continue;
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
            switch (heap_location) {
                case 1:
                    heap1 = heapRandom;
                    break;
                case 2:
                    heap2 = heapRandom;
                    break;
                case 3:
                    heap3 = heapRandom;
                    break;
                case 4:
                    heap4 = heapRandom;
                    break;
                case 5:
                    heap5 = heapRandom;
                    break;
                default:
                    break;
            }
        }

    }

    Worker(int h, int a, char с, int g, int RC, char R1, char R2, char R3) : Ant(h, a, с, g) {
        this->Resource_count = RC;
        this->Resource[0] = R1;
        this->Resource[1] = R2;
        this->Resource[2] = R3;
    }

    Worker() {}

    static void Print_Ant(string type, int health, int armor, int damage, string Qname, char job) {
        cout << "---------------------------------------\n---------------------------------------";
        cout << "\nТип: " << type << endl;
        cout << "   Здоровье = " << health << ", защита = " << armor << endl;
        cout << "   Королева << " << Qname << " >>" << endl;
        cout << "---------------------------------------\n---------------------------------------" << endl;
    }
};

Worker Peasant_Red[200] = {Worker(10, 6, 'r', 0, 3, 'l', 'd', 'd'), Worker(10, 6, 'r', 0, 3, 'l', 'd', 'd'),
                           Worker(10, 6, 'r', 0, 3, 'l', 'd', 'd'), Worker(1, 0, 'r', 0, 1, 'd', 0, 0),
                           Worker(1, 0, 'r', 0, 1, 'd', 0, 0), Worker(1, 0, 'r', 0, 1, 'd', 0, 0),
                           Worker(1, 0, 'r', 0, 1, 'd', 0, 0), Worker(1, 0, 'r', 0, 1, 'd', 0, 0),
                           Worker(1, 0, 'r', 0, 1, 'd', 0, 0),
                           Worker(1, 0, 'r', 0, 1, 'd', 0, 0), Worker(2, 1, 'r', 0, 1, 'd', 'b', 0),
                           Worker(2, 1, 'r', 0, 1, 'd', 'b', 0), Worker(2, 1, 'r', 0, 1, 'd', 'b', 0),
                           Worker(2, 1, 'r', 0, 1, 'd', 'b', 0)};


Worker Peasant_Green[200] = {Worker(1, 0, 'g', 0, 1, 'd', 0, 0), Worker(1, 0, 'g', 0, 1, 'd', 0, 0),
                             Worker(1, 0, 'g', 0, 1, 'd', 0, 0), Worker(1, 0, 'g', 0, 1, 'd', 0, 0),
                             Worker(1, 0, 'g', 0, 1, 'd', 0, 0), Worker(1, 0, 'g', 0, 1, 'd', 0, 0),
                             Worker(1, 0, 'g', 0, 1, 'd', 0, 0),
                             Worker(8, 4, 'g', 0, 2, 'l', 'd', 0), Worker(8, 4, 'g', 0, 2, 'l', 'd', 0),
                             Worker(8, 4, 'g', 0, 2, 'l', 'd', 0), Worker(8, 4, 'g', 0, 2, 'l', 'd', 0),
                             Worker(8, 4, 'g', 0, 2, 'l', 'd', 0),
                             Worker(2, 1, 'g', 0, 1, 'l', 's', 0), Worker(2, 1, 'g', 0, 1, 'l', 's', 0),
                             Worker(2, 1, 'g', 0, 1, 'l', 's', 0), Worker(2, 1, 'g', 0, 1, 'l', 's', 0),
                             Worker(2, 1, 'g', 0, 1, 'l', 's', 0)};


Worker Peasant_Red_Special[200] = {Worker(10, 6, 'r', 0, 4, 'l', 'd', 'd'), Worker(10, 6, 'r', 0, 4, 'l', 'd', 'd'),
                                   Worker(10, 6, 'r', 0, 4, 'l', 'd', 'd'), Worker(1, 0, 'r', 0, 2, 'd', 0, 0),
                                   Worker(1, 0, 'r', 0, 2, 'd', 0, 0), Worker(1, 0, 'r', 0, 2, 'd', 0, 0),
                                   Worker(1, 0, 'r', 0, 2, 'd', 0, 0), Worker(1, 0, 'r', 0, 2, 'd', 0, 0),
                                   Worker(1, 0, 'r', 0, 2, 'd', 0, 0),
                                   Worker(1, 0, 'r', 0, 2, 'd', 0, 0), Worker(2, 1, 'r', 0, 2, 'd', 'b', 0),
                                   Worker(2, 1, 'r', 0, 2, 'd', 'b', 0), Worker(2, 1, 'r', 0, 2, 'd', 'b', 0),
                                   Worker(2, 1, 'r', 0, 2, 'd', 'b', 0)};


Worker Peasant_Green_Special[200] = {Worker(1, 0, 'g', 0, 2, 'd', 0, 0), Worker(1, 0, 'g', 0, 2, 'd', 0, 0),
                                     Worker(1, 0, 'g', 0, 2, 'd', 0, 0), Worker(1, 0, 'g', 0, 2, 'd', 0, 0),
                                     Worker(1, 0, 'g', 0, 2, 'd', 0, 0), Worker(1, 0, 'g', 0, 2, 'd', 0, 0),
                                     Worker(1, 0, 'g', 0, 2, 'd', 0, 0),
                                     Worker(8, 4, 'g', 0, 3, 'l', 'd', 0), Worker(8, 4, 'g', 0, 3, 'l', 'd', 0),
                                     Worker(8, 4, 'g', 0, 3, 'l', 'd', 0), Worker(8, 4, 'g', 0, 3, 'l', 'd', 0),
                                     Worker(8, 4, 'g', 0, 3, 'l', 'd', 0),
                                     Worker(2, 1, 'g', 0, 2, 'l', 's', 0), Worker(2, 1, 'g', 0, 2, 'l', 's', 0),
                                     Worker(2, 1, 'g', 0, 2, 'l', 's', 0), Worker(2, 1, 'g', 0, 2, 'l', 's', 0),
                                     Worker(2, 1, 'g', 0, 2, 'l', 's', 0)};


Warrior Warrior_Red[200] = {Warrior(1, 0, 'r', 0, 1, 1, 1), Warrior(1, 0, 'r', 0, 1, 1, 1),
                            Warrior(8, 4, 'r', 0, 5, 2, 2), Warrior(8, 4, 'r', 0, 5, 2, 2),
                            Warrior(10, 6, 'r', 0, 4, 3, 1), Warrior(10, 6, 'r', 0, 4, 3, 1)};


Warrior Warrior_Green[200] = {Warrior(8, 4, 'g', 0, 5, 2, 2), Warrior(8, 4, 'g', 0, 5, 2, 2),
                              Warrior(10, 6, 'g', 0, 4, 3, 1), Warrior(6, 2, 'g', 0, 3, 2, 1),
                              Warrior(6, 2, 'g', 0, 3, 2, 1)};


class Queen : public Ant {
public:

    int damage, CiclRostaLichinok;
    string name;

    virtual void Larva() {
        int Larva_count = 1 + rand() % (11 - 1);
        (colony == 'g') ? GreenLarva = Larva_count : RedLarva = Larva_count;
        for (int i = 0; i < Larva_count; i++) {
            int randomTemp = rand() % 2;
            if (randomTemp == 0) {
                if (colony == 'r') {
                    int rtv = rand() % 3;
                    if (rtv == 0) {
                        Warrior_Red[RedWarrior_count].Setter_War(1, 0, 'r', 0, 1, 1, 1);
                        RedWarrior_count++;
                    } else if (rtv == 1) {
                        Warrior_Red[RedWarrior_count].Setter_War(8, 4, 'r', 0, 5, 2, 2);
                        RedWarrior_count++;
                    } else if (rtv == 2) {
                        Warrior_Red[RedWarrior_count].Setter_War(10, 6, 'r', 0, 4, 3, 1);
                        RedWarrior_count++;
                    }

                } else {
                    int gtv = rand() % 3;
                    if (gtv == 0) {
                        Warrior_Green[GreenWarrior_count].Setter_War(8, 4, 'g', 0, 5, 2, 2);
                        GreenWarrior_count++;
                    } else if (gtv == 1) {
                        Warrior_Green[GreenWarrior_count].Setter_War(10, 6, 'g', 0, 4, 3, 1);
                        GreenWarrior_count++;
                    } else if (gtv == 2) {
                        Warrior_Green[GreenWarrior_count].Setter_War(6, 2, 'g', 0, 3, 2, 1);
                        GreenWarrior_count++;
                    }
                }
            } else {
                if (colony == 'r') {
                    int rtr = rand() % 3;
                    if (rtr == 0) {
                        Peasant_Red[RedWorker_count].Worker_frame(10, 6, 'r', 0, 3, 'l', 'r', 'r');
                        RedWorker_count++;
                    } else if (rtr == 1) {
                        Peasant_Red[RedWorker_count].Worker_frame(1, 0, 'r', 0, 1, 'r', 0, 0);
                        RedWorker_count++;
                    } else if (rtr == 2) {
                        Peasant_Red[RedWorker_count].Worker_frame(2, 1, 'r', 0, 1, 'r', 'v', 0);
                        RedWorker_count++;
                    }

                } else {
                    int gtr = rand() % 3;
                    if (gtr == 0) {
                        Peasant_Green[GreenWorker_count].Worker_frame(1, 0, 'g', 0, 1, 'r', 0, 0);
                        GreenWorker_count++;
                    } else if (gtr == 1) {
                        Peasant_Green[GreenWorker_count].Worker_frame(8, 4, 'g', 0, 2, 'l', 'r', 0);
                        GreenWorker_count++;
                    } else if (gtr == 2) {
                        Peasant_Green[GreenWorker_count].Worker_frame(2, 1, 'g', 0, 1, 'l', 'k', 0);
                        GreenWorker_count++;
                    }

                }
            }
        }
    }

    Queen(int h, int a, char c, int g, int d, string n, int C) : Ant(h, a, c, g) {
        CiclRostaLichinok = C;
        name = n;
        damage = d;
    }
};