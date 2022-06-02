#include "main_h.h"


bool Base::attacked(int damage) {
    if(this->p - damage > 0)  this->p -= damage;
    else {
        damage -= this->p;
        this->p = 0;
        this->h -= damage;
        this->isAlive = this->h > 0 ? true : false;
    }
    return this->isAlive;
}

Q Q::newQ(){
    Q new_q = (*this);
    new_q.mother = this->name;
    int pos = new_q.name.find('_');
    if(pos == -1) {
        new_q.name += "_0";
        pos = new_q.name.find('_');
    }
    int n = stoi(new_q.name.substr(pos+1));
    n += 1;
    new_q.name = std::string(new_q.name, 0, pos+1) + std::to_string(n);
    return (new_q);
}

bool Q::pregnancy() {
    show_2();
    if(period == 0) {
        --period;
        return true;
    }
    else if(period == -1) {
        set_period();
        set_daughter();
        set_children();
    }
    --period;
    return false;
}

void Empire::generateWar(int cwar, Type T)
{
    std::vector<Type_Warrior> v = q.getTWar();
    bool flag = T.value == 0;
    while(cwar--) {
        if(flag) T = v[0 + rand() % v.size()];
        switch (T.value) {
            case(ordinary_warrior):
                warriors.emplace_back(std::make_shared<Ordinary>(1, 0, 1, 1, 1));
                break;
            case(legendary_legend):
                warriors.emplace_back(std::make_shared<LegendaryLegend>(10, 6, 4, 1, 3));
                break;
            case(advanced):
                warriors.emplace_back(std::make_shared<Advanced>(6, 2, 3, 1, 2));
                break;
            case(elite_anomal):
                warriors.emplace_back(std::make_shared<EliteAnomal>(8, 4, 5, 2, 2));
                break;
            case(senior_warrior):
                warriors.emplace_back(std::make_shared<SeniorWarrior>(2, 1, 2, 1, 1));
                break;
            case(usual_absent_minded):
                warriors.emplace_back(std::make_shared<UsualAbsentMinded>(1, 0, 0.5, 1, 1));
                break;

        }
        warriors[warriors.size()-1].get()->show();
        warriors[warriors.size()-1].get()->setE(q.getE());
    }
}

void Empire::generateWork(int cwork, Type T)
{
    std::vector<Type_Worker> v = q.getTWork();
    bool flag = T.value == 0;
    while(cwork--) {
        if(flag) T = v[0 + rand() % v.size()];
        switch (T.value) {
            case(senior_worker):
                workers.emplace_back(std::make_shared<SeniorWorker>(2, 1, 1, std::vector<Resources>{dewdrop, pebble}));
                break;
            case(ordinary_unique):
                workers.emplace_back(std::make_shared<OrdinaryUnique>(1, 0, 1, std::vector<Resources>{pebble}));
                break;
            case(advanced_sleepy):
                workers.emplace_back(std::make_shared<Advanced_sleepy>(6, 2, 2, std::vector<Resources>{pebble, leaf}));
                break;
            case(ordinary_worker):
                workers.emplace_back(std::make_shared<OrdinaryWorker>(1, 0, 1, std::vector<Resources>{pebble}));
                break;
            case(usual_stocky):
                workers.emplace_back(std::make_shared<UsualStocky>(1, 0, 1, std::vector<Resources>{dewdrop}));
                break;
        }
    }
        workers[workers.size()-1].get()->show();
        workers[workers.size()-1].get()->setE(q.getE());
}


void Empire::generateInsect(int cinsect, Type T)
{
    std::vector<Type_Insect> v = q.getTI();
    bool flag = T.value == 0;
    while(cinsect--) {
        if(flag) T = v[0 + rand() % v.size()];
        switch (T.value) {
            case(butterfly):
                insects.emplace_back(std::make_shared<Butterfly>(22, 9, 9, 0, std::vector<Resources>{}, 2, 3));
                break;
            case(thick_legged):
                insects.emplace_back(std::make_shared<ThickLegged>(17, 9, 10, 0, std::vector<Resources>{}, 3, 3));
                break;
            case(wasp):
                insects.emplace_back(std::make_shared<Waspn>(29, 9, 5, 0, std::vector<Resources>{}, 1, 3));
                break;
        }
        insects[insects.size()-1].get()->show();
        insects[insects.size()-1].get()->setE(q.getE());
    }
}

void Empire::startDay() {
    q.show();
    if(q.pregnancy()) {
        PrintWord("Королева родила", '*', 1);
        for(int i = q.getCountDaughter(); i>0 ; --i) {
            if((bool) 0 + rand() % 2) {
                Q qs = q.newQ();
                newEmpire(qs);
            }
        }
        int count = q.getCountChildren();
        int cwar = 0 + (rand() % ((count-0) + 1)); //min + (rand() % ((max - min) + 1))
        count -= cwar;
        int cwork = (count/2) + (rand() % ((count-(count/2)) + 1));
        count -= cwork;
        generateWar(cwar);
        generateWork(cwork);
        generateInsect(count);
        PrintWord("Добавилось: " + to_string(cwar) + " к воинам, " + to_string(cwork) + " к рабочим, " +
                  to_string(count) + " к насекомым");
        PrintWord("", '*', 1);
    }
}

void Empire::randomDistribution()
{
    if(vH.empty()) {
        return ;
    }
    for(size_t i = 0; i < warriors.size(); ++i) {
        vH[rand() % vH.size() + 0].addWar(warriors.at(i));
    }
    for(size_t i = 0; i < workers.size(); ++i) {
        vH[rand() % vH.size() + 0].addWork(workers.at(i));
    }
    for(size_t i = 0; i < insects.size(); ++i) {
        vH[rand() % vH.size() + 0].addIns(insects.at(i));
    }
}

void Empire::toTakeResources() {
    for(auto it = workers.begin(); it != workers.end(); ++it) {
        if(!it->get()->getCountTake()) continue;
        for(auto& ii: it->get()->toGetResource()) {
            resources[ii.first] += ii.second;
            ii.second = 0;
        }
    }
    for(auto it = insects.begin(); it != insects.end(); ++it) {
        if(!it->get()->getCountTake()) continue;
        for(auto& ii: it->get()->toGetResource()) {
            resources[ii.first] += ii.second;
            ii.second = 0;
        }
    }
    cout << "Добыли новые ресурсы, теперь мы имеем: ";
    for(pair<Resources, int> i: resources)
        cout << to_string(i.first) << ": " << i.second << " ";
}

void Empire::clear() {
    for(auto it = warriors.begin(); it != warriors.end(); it++) {
        if(!it->get()->getIsAlive()) {
            warriors.erase(it);
            --it;
        }
        else {
            it->get()->setBT();
        }
    }
    for(auto it = workers.begin(); it != workers.end(); it++) {
        if(!it->get()->getIsAlive()) {
            workers.erase(it);
            --it;
        }
    }
    for(auto it = insects.begin(); it != insects.end(); it++) {
        if(!it->get()->getIsAlive()) {
            insects.erase(it);
            --it;
        }
        else {
            it->get()->setBT();
        }
    }
    cout << "Сегодня мы простились с нашими братьями, а раненных подлатали." << endl;
}

void Empire::showArmy() {
    showAllAnts();
    cout << "Ресурсы: ";
    for(pair<Resources, int> i: resources)
        cout << to_string(i.first) << ": " << i.second << " ";
    cout << endl;
}

void Empire::showAllAnts(){
    cout << "Всего муравье: " << setw(3) << warriors.size() << "воинов, "
                              << setw(3) << workers.size() << "рабочих, "
                              << setw(3) << insects.size() << "насекомых";
    cout << endl;
    cout << "\tWarrior:" << endl;
    for(auto& it: warriors){
        cout << "\t\t";
        it->show();
    }
    cout << "\tWorker:" << endl;
    for(auto& it: workers){
        cout << "\t\t";
        it->show();
    }
    cout << "\tInsect:" << endl;
    for(auto& it: warriors){
        cout << "\t\t";
        it->show();
    }
}

void newEmpire(Q& q, int cwork, int cwar, int cinsect) {
    shared_ptr<Empire> E = make_shared<Empire>(q);
    q.show();
    E->setNameEmpire(vE.empty()? -1 : vE.at(vE.size()-1)->EmpireName);
    E->setQptrOnE(E);
    E->generateWar(cwar);
    E->generateWork(cwork);
    E->generateInsect(cinsect);
    cout << endl;
    PrintWord("New Empire: name " + to_string(E->EmpireName) + " Queen: " + E->getQ().getName(), ' ', 1);
    cout << endl;
    vE.emplace_back(E);
}

void Heap::addWar(SharedWarriorPtr& w) {
    if(w->in_operation)
        warriors.emplace_back(w);
}

void Heap::addWork(SharedWorkerPtr& w) {
    if(w->in_operation){
        workers.emplace_back(w);
    }
}

void Heap::addIns(SharedInsectPtr& w) {
    if(w->in_operation){
        insects.emplace_back(w);
    }
}

void hit(Warrior* w, Warrior* d) {
    PrintWord(" Битва ", ' ', 1);
    cout << "До: ";
    cout << "\t" << w->getE()->EmpireName << ' ';  w->show();
    cout << "\t" << d->getE()->EmpireName << ' ';  d->show();
    cout << endl;
    while(w->getCountBite() || d->getCountBite()) {
        if(!w->getIsAlive()) break;
        if(w->getCountBite() > 0) {
            d->attacked(w->getD());
            --w->getCountBite() ;
        }
        if(!d->getIsAlive()) break;
        if(d->getCountBite() > 0) {
            w->attacked(d->getD());
            --d->getCountBite();
        }
    }
    --w->getCountTargets();
    --d->getCountTargets();
    if(w->getCountTargets() <= 0) w->in_operation = false;
    if(d->getCountTargets() <= 0) d->in_operation = false;
    cout << "После: ";
    cout << "\t" << w->getE()->EmpireName << ' ';  w->show();
    cout << "\t" << d->getE()->EmpireName << ' ';  d->show();
    PrintWord("", '_');
    cout << endl;
}

void hit(Warrior* w, Worker* d) {
    PrintWord(" Битва ", ' ', 1);
    cout << "До: ";
    cout << "\t" << w->getE()->EmpireName << ' ';  w->show();
    cout << "\t" << d->getE()->EmpireName << ' ';  d->show();
    cout << endl;
    while(w->getCountBite()) {
        if(!w->getIsAlive()) break;
        if(w->getCountBite() > 0) {
            d->attacked(w->getD());
            --w->getCountBite() ;
        }
        if(!d->getIsAlive()) break;
    }
    --w->getCountTargets();
    if(w->getCountTargets() <= 0) w->in_operation = false;
    cout << "После: ";
    cout << "\t" << w->getE()->EmpireName << ' ';  w->show();
    cout << "\t" << d->getE()->EmpireName << ' ';  d->show();
    PrintWord("", '_');
    cout << endl;
}

void Heap::delMySelf() {
    warriors.clear();
    workers.clear();
    insects.clear();
}

bool isEnemy(weak_ptr<Empire> a, weak_ptr<Empire> e){
    if(a.lock() == e.lock()) return false;
    Q& our = a.lock()->q;
    Q& enemy = e.lock()->q;
    if(enemy.getName() == our.getMName()) return false;
    if(enemy.getMName() == our.getName()) return false;
    return true;
}

template <typename  T, typename Q>
void asd(T& t, Q& q) {
    for(auto it = t.begin(); it < t.end(); ++it) {
        for(auto ii = q.begin(); ii < q.end(); ++ii) {
            if(isEnemy(it->get()->getE(), ii->get()->getE())) {
                hit(it->get(), ii->get());
                if(!it->get()->getIsAlive() || !it->get()->in_operation) {
                    it->get()->in_operation = true;
                    t.erase(it);
                    --it; --ii;
                    if(distance(t.begin(), it ) == -1) ++it;
                }
                if(distance(q.begin(), ii ) != -1) {
                    if(!ii->get()->getIsAlive() || !ii->get()->in_operation) {
                        ii->get()->in_operation = true;
                        q.erase(ii);
                        --ii;
                    }
                }
                if(t.empty()) return;
            }
        }
    }
}

void Heap::TAKE_RES() {
    for(auto it = workers.begin(); it < workers.end(); ++it) {
        it->get()->toTakeResource(resources, workers);
    }

    cout << "Ресурсы: ";
    for(pair<Resources, int> i: resources)
        cout << to_string(i.first) << ": " << i.second << " ";
    cout << endl;

    empty = resources[Resources::twig] + resources[Resources::dewdrop] + resources[Resources::leaf] +
            resources[Resources::pebble] <= 0 ;
}

void Heap::WAR() {
    cout << "Ресурсы: ";
    for(pair<Resources, int> i: resources)
        cout << to_string(i.first) << ": " << i.second << " ";
    cout << endl << endl;
    cout << "Warrior:" << endl;
    for(auto& it: warriors){
        cout << "\t" << it->getE()->EmpireName << ' ';
        it->show();
    }
    cout << "Worker:" << endl;
    for(auto& it: workers){
        cout << "\t" << it->getE()->EmpireName << ' ';
        it->show();
    }
    cout << "Insect:" << endl;
    for(auto& it: insects){
        cout << "\t" << it->getE()->EmpireName << ' ';
        it->show();
    }
    cout << endl;

    for(SharedInsectPtr& it: insects) {
        if(it->getCountTargets() > 0)
            warriors.emplace_back(it);
    }
    random_shuffle(warriors.begin(), warriors.end());
    asd(warriors, warriors);

    for(SharedInsectPtr& it: insects) {
        if(it->getIsAlive() && it->getCountTake())
            workers.emplace_back(it);
    }
    random_shuffle(workers.begin(), workers.end());
    asd(warriors, workers);

    TAKE_RES();
}

void Heap::show() {
    cout << "\n\n------------------------------------------------------------------------\n";
    cout << setw(10) << left << "HEAP: ";
    for(pair<Resources, int> i: resources)
        cout << to_string(i.first) << ": " << i.second << " ";
    cout << endl;
    cout << "\nWAR:";
    for(auto& it: warriors) it.get()->show();
    cout << "\nWORKER:";
    for(auto& it: workers) it.get()->show();
    cout << "\nINSECT:";
    for(auto& it: insects) it.get()->show();
    cout << endl << endl;
}

void Ragnarok::dopEffect(shared_ptr<Empire>& e) {
    PrintWord("", '!', 1);
    PrintWord("Эффект тропиков начинает свое господство в Empire " + to_string(e->EmpireName));
    PrintWord("", '!', 1);
    vector<SharedWorkerPtr>& work = e->getWorkers();
    vector<SharedInsectPtr>& ins = e->getInsects();
    for(auto it = work.begin(); it < work.end(); ++it) {
        e->generateInsect(1);
        ins[ins.size()-1].get()->setT(it->get()->getT());
        work.erase(it);
        --it;
    }
}

void Ragnarok::revers(shared_ptr<Empire> &e) {
    PrintWord("", '!', 1);
    PrintWord("Эффект тропиков закончил свое господство в Empire " + to_string(e->EmpireName));
    PrintWord("", '!', 1);
    vector<SharedInsectPtr>& ins = e->getInsects();
    for(auto it = ins.begin(); it < ins.end(); ++it) {
        if(it->get()->getT().get_insect() != defI) continue;
        e->generateWork(1, it->get()->getT());
        ins.erase(it);
        --it;
    }
}


void showWin(shared_ptr<Empire>& ptr) {
    PrintWord(" И в этих 75-х Очень голодных играх побеждает... ", ' ', 1);
    cout << ptr->getQ().getName() << endl;
    cout << "Её детки ЛУЧШЕ ВСЕХ умеют пиздить других и тащить нажитое непосильным трудом добро к мамке. \n";
    cout << "Всего они смогли надыбать: ";
    for(pair<Resources, int> i: ptr->toGetResource())
        cout << to_string(i.first) << ": " << i.second << " ";
    cout << endl;
}

void startGame(int day) {
    srand(time(0));
    Ragnarok t;
    PrintWord("Добро пожаловать на 75-е Очень Голодные игры!!!");
    PrintWord("И пусть удача всегда будет с вами!", ' ', 1);
    while(day && vH.size() > 0) {
        PrintWord("", '+', 1);
        PrintWord("До полного звиздеца осталось: " + to_string(day) + (day != 1 ? " дней" : " день"), ' ');
        PrintWord("", '+', 1);

        if(t.flag == false || t.ef_day == 0) {
            if(!t.flag){
                t.flag = 0 + rand() % 2;
                if(t.flag == false) goto K;
                else t.setTD();
            }
            if(t.ef_day == 0) {
                t.setED();
            }
            if(t.flag == true) {
                for(auto& it: vE) {
                    t.dopEffect(it);
                }
            }
        }
        K:
        for(size_t i = 0; i < vE.size(); ++i) {
            PrintWord(" Empire " + to_string(vE.at(i)->EmpireName), '-', 1);
            vE.at(i)->startDay();
            vE.at(i)->showArmy();
            vE.at(i)->randomDistribution();
        }

        PrintWord("", 'x', 1);
        PrintWord("Война", ' ');
        PrintWord("", 'x', 1);
        for(auto& it: vH) {
            PrintWord(" Heap " + to_string(it.HeapName), '-', 1);
            it.WAR();
            it.delMySelf();
        }
        PrintWord("", '$', 1);
        PrintWord(" Итоги походов ", ' ');
        PrintWord("", '$', 1);
        for(auto& it: vE) {
            PrintWord(" Empire " + to_string(it->EmpireName), '-', 1);
            it->clear();
            it->toTakeResources();
            PrintWord("", '-', 1);
        }
        for(auto it = vH.begin(); it < vH.end(); ++it) {
            if(it->empty){
                PrintWord(" Объявление ", '.', 1);
                cout << "Куча гоФна под названием " << it->HeapName
                     << " опустела! И она выбывает из гонки на выживание.";
                PrintWord("", '_', 1);
                vH.erase(it);
                --it;
            }
        }

        --day;
        if(t.flag) {
            --t.day;
            --t.ef_day;
            if(t.ef_day == 0)
                for(auto& it: vE)
                    t.revers(it);
            if(t.day == 0)
                t.flag = false;
        }
    }

    size_t max = 0;
    size_t i_max = 0;
    for(size_t i = 0; i < vE.size(); ++i) {
        if(vE.at(i)->sumResource() > max) {
            max = vE.at(i)->sumResource();
            i_max = i;
        }
    }
    showWin(vE.at(i_max));
}

int main() {
     PrintWord("", '0', 1);


    {
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
        int n;
        while(true) {
            cout << "Input day: ";
            cin >> n;
            if(n < 0) {
                cout << "\nError! Try to again.\n";
            }
            else break;
        }
        Q elizaveta("Elizaveta", 28, 9, 20);
        elizaveta.setFTChildren(1, 15);
        elizaveta.setFTDaught(1, 3);
        elizaveta.setFTPeriod(3, 4);
        elizaveta.setType(std::vector<Type_Worker>{senior_worker, advanced_sleepy},
                          std::vector<Type_Warrior>{senior_warrior, advanced, elite_anomal},
                          std::vector<Type_Insect>{butterfly});
        newEmpire(elizaveta, 17, 7, 1);

        Q blanka("Blanka", 24, 6, 21);
        blanka.setFTChildren(1, 15);
        blanka.setFTDaught(1, 3);
        blanka.setFTPeriod(1, 5);
        blanka.setType(std::vector<Type_Worker>{senior_worker, usual_stocky},
                       std::vector<Type_Warrior>{senior_warrior, ordinary_warrior, legendary_legend},
                       std::vector<Type_Insect>{thick_legged});
        newEmpire(blanka, 17, 7, 1);

        vH.push_back(Heap(36, 16, 0, 39));
        vH.push_back(Heap(21, 32, 0, 0));
        vH.push_back(Heap(35, 12, 45, 12));
        vH.push_back(Heap(21, 19, 0, 15));
        vH.push_back(Heap(28, 0, 45, 0));

        startGame(n);
    }

     PrintWord("", '0', 1);
    return 0;
}




