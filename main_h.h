#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <bits/shared_ptr.h>
#include <algorithm>
#include <iomanip>
#include <windows.h>
#include <ctime>
using namespace std;




void PrintWord(const string& s, char c = ' ', int mode = 0){
    if(mode) cout << endl;
    int width_field = 70; //ширина поля
    string v(width_field, c); //для наглядности заполняем точками
    string v1;

    int l_word = s.size();
    int l_field = v.size();
    int step = (l_field - l_word)/2;

    for(int i = 0; i < l_word; i++){
        v1.push_back(s[i]);
    }
    copy(v1.begin(), v1.end(),v.begin()+step);
    for(auto x : v){
        cout << x;
    }
    if(mode) cout << endl;
}


enum Resources{
    twig = 0,
    dewdrop,
    pebble,
    leaf
};

enum Type_OP {
    Type_Worker_OP = 0x100,
    Type_Warrior_OP = 0x200,
    Type_Insect_OP = 0x300,
    Type_Parent_OP = 0x400,
};
enum Type_Worker{
    defW = 0,
    senior_worker = Type_Worker_OP, // старший рабочий
    ordinary_unique, // обычный неповторимый рабочий
    ordinary_worker, // обычный рабочий
    advanced_sleepy, // продвинутый сонный рабочий
    usual_stocky, // обычный коренастый рабочий
};
enum Type_Warrior{
    defWa = 0,
    senior_warrior = Type_Warrior_OP, // старший воин
    elite_anomal, // элитный аномальный воин
    advanced, // продвинутый воин
    legendary_legend, // легендарный легенда воин
    ordinary_warrier, // обычный воин
    usual_absent_minded, // обычный рассеянный воин
};
enum Type_Insect{
    defI = 0,
    butterfly = Type_Insect_OP, // бабочка
    thick_legged, // толстоножка
    wasp, // оса
};
enum Type_Parent{
    defP = 0,
    base = Type_Parent_OP,
    warrior,
    worker,
    insects,
    queen
};

struct Type {
    int value;

    Type(Type_Worker val) : value((int)val) { }
    Type(Type_Warrior val) : value((int)val) { }
    Type(Type_Insect val) : value((int)val) { }
    Type(Type_Parent val) : value((int)val) { }
    Type& operator=(Type_Worker val) {
        value = (int)val;
        return *this;
    }
    Type& operator=(Type_Warrior val) {
        value = (int)val;
        return *this;
    }
    Type& operator=(Type_Insect val) {
        value = (int)val;
        return *this;
    }
    Type& operator=(Type_Parent val) {
        value = (int)val;
        return *this;
    }

    Type_Worker get_worker() const {
        if (value >= senior_worker && value <= usual_stocky)
            return (Type_Worker)value;
        return defW;
    }
    Type_Warrior get_warrier() const {
        if (value >= senior_warrior && value <= usual_absent_minded)
            return (Type_Warrior)value;
        return defWa;
    }
    Type_Insect get_insect() const {
        if (value >= butterfly && value <= wasp)
            return (Type_Insect)value;
        return defI;
    }
    Type_Parent get_parent() const {
        if (value >= base && value <= queen)
            return (Type_Parent)value;
        return defP;
    }
};




class Empire;
class Heap;
class Q;
class Worker;
class SpecialInsect;
class Warrior;

std::vector<shared_ptr<Empire>> vE;
std::vector<Heap> vH;

class Base {
protected:
    int h = 0;
    int p = 0;
    int d = 0;
    bool isAlive = true;
    Type type = base;
    weak_ptr<Empire> e;
public:
    Base(int h = 0, int p = 0, int d = 0) {
        this->h = h;
        this->p = p;
        this->d = d;
        this->isAlive = true;
    }
    virtual ~Base() {
    }
    bool in_operation = true;
    int getH() const { return h;}
    void setH(int newH) { h = newH;}
    int getP() const { return p;}
    void setP(int newP) { p = newP;}
    int getD() const { return d;}
    void setD(int newD) { d = newD;}
    bool getIsAlive() const { return isAlive;}
    void setIsAlive(bool newIsAlive) { isAlive = newIsAlive;}
    void setT(Type newT) { type = newT;}
    Type getT() const { return type;}

    bool attacked(int damage);
    shared_ptr<Empire> getE() { return e.lock();}
    virtual void setE(weak_ptr<Empire> object) { e = object;}

    void show() {
        cout << "h: " << setw(3) << left << h <<
                " p: " << setw(3) << left << p <<
                " d: " << setw(3) << left << d << " ";
    }


    template<typename T>
    bool isA() {
        return (dynamic_cast<T*>(this) != NULL);
    }
};

//КЛАСС КОРОЛЕВА---------------------------------------------------------------------
class Q: public Base{
private:
    string name = "";
    string mother = "";
    int period = -1;
    int countChildren = 0;
    int countDaughter = 0;
    int fp = 0, tp = 0, fc = 0, tc = 0, fd = 0, td = 0;

    std::vector<Type_Worker> typeWork = {};
    std::vector<Type_Warrior> typeWar = {};
    std::vector<Type_Insect> typeInsect = {};
public:
    Q():Base(0,0,0) {
        setT(queen);
    }
    Q(string name, int h, int p, int d): Base(h, p, d), name(name) {
        setT(queen);
    }
    ~Q() {
    }

    string getName() { return name;}
    string getMName() {return mother;}
    void setName(std::string n) {this->name = n;}
    void setType(std::vector<Type_Worker> typeWork, std::vector<Type_Warrior> typeWar,
                 std::vector<Type_Insect> typeInsect) {
        this->typeWork = typeWork;
        this->typeWar = typeWar;
        this->typeInsect = typeInsect;
    }
    void setFTPeriod(int f, int t){ this->fp = f; this->tp = t;}
    void setFTDaught(int f, int t){ this->fd = f; this->td = t;}
    void setFTChildren(int f, int t){ this->fc = f; this->tc = t;}

    void set_period() { period = fp + (rand() % ((tp - fp) + 1)); }
    void set_daughter() { countDaughter = fd + (rand() % ((td - fp) + 1)); }
    void set_children() { countChildren = fc + (rand() % ((tc - fc) + 1)); }

    std::vector<Type_Worker> getTWork(){return typeWork;}
    std::vector<Type_Warrior> getTWar(){return typeWar;}
    std::vector<Type_Insect> getTI(){return typeInsect;}

    bool pregnancy();

    void show() {
        cout << "Королева: " << getName() << " "; Base::show();
        cout << endl;
    }
    void show_2() {
        cout << "       " << "Период: " << setw(3) << period <<
                             " Кол-во детей: " << setw(3) << countChildren <<
                             " Кол-во дочерей: " << setw(3) << countDaughter;
        cout << endl;
    }

    Q newQ();
    int getCountChildren() { return countChildren;}
    int getCountDaughter() { return countDaughter;}

};



//ИМПЕРИЯ---------------------------------------------------------------------------------
using  SharedWorkerPtr = std::shared_ptr<Worker>;
using  SharedWarriorPtr = std::shared_ptr<Warrior>;
using  SharedInsectPtr = std::shared_ptr<SpecialInsect>;

class Empire{
private:
    Q q;
    std::vector<SharedWarriorPtr> warriors = {};
    std::vector<SharedWorkerPtr> workers = {};
    std::vector<SharedInsectPtr> insects = {};
    std::map<Resources, int> resources;
public:
    Empire(Q& q) {
        this->q = q;
    }
    int EmpireName = -1;
    void setNameEmpire(int i) {
        EmpireName = i + 1;
    }

    ~Empire() {
        warriors.clear();
        workers.clear();
        insects.clear();
    }

    void generateWork(int count, Type T = defW);
    void generateWar(int count, Type T = defWa);
    void generateInsect(int count, Type T = defI);
    void setQptrOnE(weak_ptr<Empire> object) {q.setE(object);}

    friend bool isEnemy(weak_ptr<Empire> a, weak_ptr<Empire> e);

    void clear();

    void toTakeResources();
    void startDay();
    void showArmy();
    void showAllAnts();
    Q& getQ() { return q;}

    void randomDistribution();
    std::vector<SharedWorkerPtr>& getWorkers() { return workers;}
    std::vector<SharedInsectPtr>& getInsects() { return insects;}
    std::vector<SharedWarriorPtr>& getWarrior() { return warriors;}
    std::map<Resources, int> toGetResource() { return resources;}

    size_t sumResource() {
        size_t sum = 0;
        for(auto it: resources) {
            sum += it.second;
        }
        return sum;
    }
};


class Heap {
public:
    std::map<Resources, int> resources;
    bool empty = false;

    std::vector<SharedWarriorPtr> warriors = {};
    std::vector<SharedWorkerPtr> workers = {};
    std::vector<SharedInsectPtr> insects = {};

    Heap(int twig = 0, int dewdrop = 0, int pebble = 0, int leaf = 0) {
        resources[Resources::twig] = twig;
        resources[Resources::dewdrop] = dewdrop;
        resources[Resources::pebble] = pebble;
        resources[Resources::leaf] = leaf;
        setNameHeap(vH.empty()? -1 : vH.at(vH.size()-1).HeapName);
    }

    void addWar(SharedWarriorPtr& w);
    void addWork(SharedWorkerPtr& w);
    void addIns(SharedInsectPtr& w);

    int HeapName = -1;
    void setNameHeap(int i) {
        HeapName = i + 1;
    }

    void WAR();
    void TAKE_RES();

    ~Heap() {
        delMySelf();
    }

    void delMySelf();
    void totalDel();
    void show();
};

void newEmpire(Q& q, int cwork = 0, int cwar = 0, int cinsect = 0);

template <class T, class Q>
void hit(T t, Q q);

void startGame(int day);

void showWin(shared_ptr<Empire>& ptr);




//КЛАСС РАБОЧИЙ----------------------------------------------------------------------------
class Worker: virtual public Base {
protected:
    std::map<Resources, int> resources = {};
    int count_canTake = 0;
    std::vector<Resources> v = {};
    weak_ptr<Empire> e;
public:
    Worker();
    Worker(int health = 0, int protection = 0, int canTake = 0, std::vector<Resources> v = {}, Type t = worker):
        Base(health, protection) {
        setT(t);
        this->count_canTake = canTake;
        this->v = v;
        for(auto it: v) {
            resources[it] = 0;
        }
    }

    virtual ~Worker() {
    }
    virtual int getCountTake() { return count_canTake;}

    virtual void toTakeResource(std::map<Resources, int>& res, vector<SharedWorkerPtr>& worker) = 0;
    virtual std::map<Resources, int>& toGetResource() { return resources;}

    virtual void show() = 0;
    void show_2() {
        cout << "Кол-во, которое можно взять: " << setw(3) << left << count_canTake << " { ";
        for(auto it: v) cout << setw(3) << left << to_string(it) << " ";
        cout << " } "; show_3();
    }
    void show_3() {
        cout << " -----Есть----- :";
        for(auto& it: resources) {
            cout << " " << it.first << " = " << it.second;
        }
    }
};

/* senior_worker = Type_Worker_OP, // старший рабочий +
    ordinary_unique, // обычный неповторимый рабочий +-
    ordinary_worker, // обычный рабочий +
    advanced_sleepy, // продвинутый сонный рабочий +
    usual_stocky, // обычный коренастый рабочий +-
*/

class SeniorWorker: public Worker{
public:
    SeniorWorker(int health = 2, int protection = 1, int canTake = 1, std::vector<Resources> v = {dewdrop, pebble}):
        Base(health, protection),
        Worker::Worker(health, protection, canTake, v, senior_worker) {
    }
    ~SeniorWorker() {
    }
    void show() {
        cout << setw(25) << left << "Старший рабочий: "; Base::show(); Worker::show_2();
        cout << endl;
    }
    void toTakeResource(std::map<Resources, int>& res, vector<SharedWorkerPtr>& worker) {
        for(size_t i = 0; i < v.size(); ++i) {
            int a = resources[v.at(i)];
            if(res.find(v.at(i)) == res.end()) continue;
            res[v.at(i)] -= count_canTake;
            resources[v.at(i)] += count_canTake;
            if(res[v.at(i)] < 0) {
                resources[v.at(i)] += res[v.at(i)];
                res[v.at(i)] = 0;
            }
            if(a != resources[v.at(i)]) break;
        }
    }
};

class OrdinaryWorker: public Worker{
public:
    OrdinaryWorker(int health = 1, int protection = 0, int canTake = 1, std::vector<Resources> v = {pebble}):
            Base(health, protection),
            Worker::Worker(health, protection, canTake, v, ordinary_worker) {
    }
    ~OrdinaryWorker() {
    }
    void show() {
        cout << setw(25) << left << "Обычный рабочий: "; Base::show(); Worker::show_2();
        cout << endl;
    }
    void toTakeResource(std::map<Resources, int>& res, vector<SharedWorkerPtr>& worker) {
        for(size_t i = 0; i < v.size(); ++i) {
            int a = resources[v.at(i)];
            if(res.find(v.at(i)) == res.end()) continue;
            res[v.at(i)] -= count_canTake;
            resources[v.at(i)] += count_canTake;
            if(res[v.at(i)] < 0) {
                resources[v.at(i)] += res[v.at(i)];
                res[v.at(i)] = 0;
            }
            if(a != resources[v.at(i)]) break;
        }
    }
};

class Advanced_sleepy: public Worker{
    bool sleep = false;
public:
    Advanced_sleepy(int health = 6, int protection = 2, int canTake = 2, std::vector<Resources> v = {pebble, leaf}):
        Base(health, protection),
        Worker::Worker(health, protection, canTake, v, advanced_sleepy) {
    }
    ~Advanced_sleepy() {
    }
    void show() {
        cout << setw(25) << left << "Продвинутый сонный рабочий: "; Base::show(); Worker::show_2();
        cout << endl;
    }
    void toTakeResource(std::map<Resources, int>& res, vector<SharedWorkerPtr>& worker) {
        if((rand() % 10) < 3 && !sleep) {
            sleep = true;
            in_operation = false;
        }
        for(size_t i = 0; i < v.size(); ++i) {
            int a = resources[v.at(i)];
            if(res.find(v.at(i)) == res.end()) continue;
            res[v.at(i)] -= count_canTake;
            resources[v.at(i)] += count_canTake;
            if(res[v.at(i)] < 0) {
                resources[v.at(i)] += res[v.at(i)];
                res[v.at(i)] = 0;
            }
            if(a != resources[v.at(i)]) break;
        }
    }
    int getCountTake() {
        cout << "Продвинутый сонный рабочий ";
        if(sleep && !in_operation) {
            sleep = false;
            cout << "спит\n";
            return 0;
        }
        else if(!sleep && !in_operation) {
            in_operation = true;
        }
        return count_canTake;
    }
};

class UsualStocky: public Worker{
public:
    UsualStocky(int health = 1, int protection = 0, int canTake = 1, std::vector<Resources> v = {dewdrop}):
        Base(health, protection),
        Worker::Worker(health, protection, canTake, v, usual_stocky) {
    }
     ~UsualStocky() {
    }
    void show() {
        cout << setw(25) << left << "Jбычный коренастый рабочий: "; Base::show(); Worker::show_2();
        cout << endl;
    }
    void toTakeResource(std::map<Resources, int>& res, vector<SharedWorkerPtr>& workers) {
        auto it = workers.begin();
        for(size_t i = 0; i < v.size(); ++i) {
            int a = resources[v.at(i)];
            if(res.find(v.at(i)) == res.end()) continue;
            res[v.at(i)] -= count_canTake;
            resources[v.at(i)] += count_canTake;
            if(res[v.at(i)] < 0) {
                resources[v.at(i)] += res[v.at(i)];
                res[v.at(i)] = 0;
            }
            if(a != resources[v.at(i)]) break;
        }

        // реализовать выживание от одного укуса!!!!!---------------------------------------------------------!!!

        /* for(; it < workers.end() && resources.empty(); ) {
            if(isEnemy(this->e, it->get()->getE())) {
                map<Resources, int>& res = it->get()->toGetResource();
                res[dewdrop] -= count_canTake;
                resources[dewdrop] += count_canTake;
                if(res[dewdrop] < 0) {
                    resources[dewdrop] += res[dewdrop];
                    res[dewdrop] = 0;
                }
            }
            if(!resources.empty()) {
                cout << "An_ordinary_pickpocket украл :";
                this->show();
                it->get()->show();
            }
        }
         */

    }
};

class OrdinaryUnique: public Worker{
public:
    OrdinaryUnique(int health = 1, int protection = 0, int canTake = 1, std::vector<Resources> v = {pebble}):
            Base(health, protection),
            Worker::Worker(health, protection, canTake, v, ordinary_unique) {
    }
    ~OrdinaryUnique() {
    }
    void show() {
        cout << setw(25) << left << "Jбычный неповторимый рабочий: "; Base::show(); Worker::show_2();
        cout << endl;
    }
    void toTakeResource(std::map<Resources, int>& res, vector<SharedWorkerPtr>& workers) {
        auto it = workers.begin();
        for(size_t i = 0; i < v.size(); ++i) {
            if(res.find(v.at(i)) == res.end()) return;
            if(res[v.at(i)] == 0) {
                resources[v.at(i)] += count_canTake;
                return ;
            }
            int a = resources[v.at(i)];
            if(res.find(v.at(i)) == res.end()) continue;
            res[v.at(i)] -= count_canTake;
            resources[v.at(i)] += count_canTake;
            if(res[v.at(i)] < 0) {
                resources[v.at(i)] += res[v.at(i)];
                res[v.at(i)] = 0;
            }
            if(a != resources[v.at(i)]) break;
        }

        // реализовать игнорирование модификаторов !!!!!---------------------------------------------------------!!!
        // реализовать игнорирование атак любых типов!!!-------------------------------------!!!

    }
};


/*
senior_warrior = Type_Warrior_OP, // старший воин
elite_anomal, // элитный аномальный воин
advanced, // продвинутый воин
legendary_legend, // легендарный легенда воин
ordinary_warrier, // обычный воин +
usual_absent_minded, // обычный рассеянный воин
*/

//КЛАСС ВОИН-------------------------------------------------------------------------------
class Warrior: virtual public Base {
protected:
    int count_bite = 0;
    int count_targets = 0;
public:
    Warrior(int h = 0, int p = 0, int d = 0, int cb = 0, int ct = 0, Type t = warrior):
        Base(h, p, d), count_bite(cb), count_targets(ct) {
        setT(t);
    }
    virtual ~Warrior() {
    }

    int& getCountBite() {return count_bite;}
    int& getCountTargets() {return count_targets;}
    virtual bool attacked(int damage) { return Base::attacked(damage);}
    virtual void show() = 0;
    void show_2() {
        cout << "Кол-во укусов: " << setw(3) << left  << count_bite
             << " Кол-во целей: " << setw(3) << left  << count_targets;
    }
    virtual void setBT() = 0;
};

class Ordinary: public Warrior {
public:
#define B 1
#define T 1
    Ordinary(int health = 1, int protection = 0, int damage = 1, int cb = 1, int ct = 1):
            Base(health, protection, damage),
            Warrior::Warrior(health, protection, damage, cb, ct, ordinary_warrier) {
    }
    ~Ordinary() {
    }
    void show() {
        cout << setw(25) << left << "Обычный воин: "; Base::show(); Warrior::show_2();
        cout << endl;
    }
    void setBT() {
        count_bite = B;
        count_targets = T;
    }
#undef B
#undef T
};

class LegendaryLegend: public Warrior {
public:
#define B 1
#define T 3
    LegendaryLegend(int health = 10, int protection = 6, int damage = 4, int cb = 1, int ct = 3):
            Base(health, protection, damage),
            Warrior::Warrior(health, protection, damage, cb, ct, legendary_legend) {
    }
    ~LegendaryLegend() {
    }
    void show() {
        cout << setw(25) << left << "Легендарный легенда воин: "; Base::show(); Warrior::show_2();
        cout << endl;
    }
    void setBT() {
        count_bite = B;
        count_targets = T;
    }
#undef B
#undef T
};

class Advanced: public Warrior {
public:
#define B 1
#define T 2
    Advanced(int health = 6, int protection = 2, int damage = 3, int cb = 1, int ct = 2):
            Base(health, protection, damage),
            Warrior::Warrior(health, protection, damage, cb, ct, advanced) {
    }
    ~Advanced() {
    }
    void show() {
        cout << setw(25) << left << "Продвинутый воин: "; Base::show(); Warrior::show_2();
        cout << endl;
    }
    void setBT() {
        count_bite = B;
        count_targets = T;
    }
#undef B
#undef T
};

class EliteAnomal: public Warrior {
public:
#define B 2
#define T 2
    EliteAnomal(int health = 8, int protection = 4, int damage = 5, int cb = 2, int ct = 2):
            Base(health, protection, damage),
            Warrior::Warrior(health, protection, damage, cb, ct, elite_anomal) {
    }
    ~EliteAnomal() {
    }
    void show() {
        cout << setw(25) << left << "Элитный аномальный воин: "; Base::show(); Warrior::show_2();
        cout << endl;
    }
    void setBT() {
        count_bite = B;
        count_targets = T;
    }
#undef B
#undef T
};

class SeniorWarrior: public Warrior {
public:
#define B 1
#define T 1
    SeniorWarrior(int health = 2, int protection = 1, int damage = 2, int cb = 1, int ct = 1):
        Base(health, protection, damage),
        Warrior::Warrior(health, protection, damage, cb, ct, senior_warrior) {
    }
    ~SeniorWarrior() {
    }
    void show() {
        cout << setw(25) << left << "Старший воин: "; Base::show(); Warrior::show_2();
        cout << endl;
    }
    void setBT() {
        count_bite = B;
        count_targets = T;
    }
#undef B
#undef T
};

class UsualAbsentMinded: public Warrior {
public:
#define B 1
#define T 1
    UsualAbsentMinded(int health = 1, int protection = 0, float damage = 0.5, int cb = 1, int ct = 1):
            Base(health, protection, damage),
            Warrior::Warrior(health, protection, damage, cb, ct, usual_absent_minded) {
    }
    ~UsualAbsentMinded() {
    }
    void show() {
        cout << setw(25) << left << "Обычный рассеянный воин: "; Base::show(); Warrior::show_2();
        cout << endl;
    }
    void setBT() {
        count_bite = B;
        count_targets = T;
    }
#undef B
#undef T
};


/*
 * butterfly = Type_Insect_OP, // бабочка
    thick_legged, // толстоножка
    wasp, // оса
 */




//КЛАСС СПЕЦИАЛЬНЫЕ НАСЕКОМЫЕ--------------------------------------------------------------
class SpecialInsect: public Warrior, public Worker{
public:
    SpecialInsect(int h = 0, int p = 0, int d = 0, int canTake = 0,
                  std::vector<Resources> v = {}, int cb = 0, int ct = 0, Type t = insects):
        Base(h, p, d),
        Warrior::Warrior(h, p, d, cb, ct) , Worker::Worker(h, p, canTake, v) {
        setT(t);
    }
    virtual ~SpecialInsect() {
    }

    bool attacked(int damage) { return Warrior::attacked(damage);}
    virtual void show() = 0;
};

class ThickLegged: public SpecialInsect {
public:
#define B 3
#define T 3
    ThickLegged(int health = 17, int protection = 9, int damage = 10,
                int canTake = 0, std::vector<Resources> v = {}, int cb = 3, int ct = 3):
            Base(health, protection, damage),
            SpecialInsect::SpecialInsect(health, protection, damage, canTake, v, cb, ct, thick_legged) {
    }
    ~ThickLegged() {
    }

    bool attacked(int damage) { return Warrior::attacked(damage);}
    void show() {
        cout << setw(25) << left << "Ленивый обычный агрессивный феникс - Толстоножка: "; Base::show(); Warrior::show_2(); Worker::show_2();
        cout << endl;
    }
    void setBT() {
        count_bite = B;
        count_targets = T;
    }

#undef B
#undef T
};

class Butterfly: public SpecialInsect {
public:
#define B 2
#define T 3
    Butterfly(int health = 22, int protection = 9, int damage = 9,
              int canTake = 0, std::vector<Resources> v = {}, int cb = 2, int ct = 3):
        Base(health, protection, damage),
        SpecialInsect::SpecialInsect(health, protection, damage, canTake, v, cb, ct, butterfly) {
    }
    ~Butterfly() {
    }
    bool attacked(int damage) { return Warrior::attacked(damage);}
    void show() {
        cout << setw(25) << left << "Ленивый обычный агрессивный гибкий - Бабочка: "; Base::show(); Warrior::show_2(); Worker::show_2();
        cout << endl;
    }
    void setBT() {
        count_bite = B;
        count_targets = T;
    }

#undef B
#undef T

};

class Waspn: public SpecialInsect {
public:
#define B 0
#define T 0
    Waspn(int health = 29, int protection = 9, int damage = 5,
                int canTake = 2, std::vector<Resources> v = {dewdrop}, int cb = 1, int ct = 3):
            Base(health, protection, damage),
            SpecialInsect::SpecialInsect(health, protection, damage, canTake, v, cb, ct, wasp) {
    }
    ~Waspn() {
    }

    void show() {
        cout << setw(25) << left << "Ленивый неуязвимый агрессивный заботливый - Оса: "; Base::show(); Warrior::show_2(); Worker::show_2();
        cout << endl;
    }
    void setBT() {
        count_bite = B;
        count_targets = T;
    }

#undef B
#undef T
};




class Ragnarok{
public:
#define RagnarDay 5
#define EffectDay 3
    int day = RagnarDay;
    int ef_day = EffectDay;
    bool flag = false;
    void dopEffect(shared_ptr<Empire>& e);
    void revers(shared_ptr<Empire>& e);
    void setTD() { day = RagnarDay;}
    void setED() { ef_day = EffectDay;}
#undef RagnarDay
#undef EffectDay
};


