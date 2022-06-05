#include "main_h.h"



int main() {
    SetConsoleOutputCP(CP_UTF8);

    srand(time(NULL));

    Medvedka Medvedka_red(28, 9, 'r', 0, 1, 'b', 0);
    Sverchok Sverchok_green(17, 8, 'g', 0, 13, 2, 1, 1, 'l', 0);

    Queen Queen_Red(21, 9, 'r', 0, 24, "Беатрикс", 4);
    Queen Queen_Green(22, 5, 'g', 0, 19, "София", 3);

    int randomDay = 1 + rand() % 9;
    int rg, multy, multy2, choise;

    for (int day = 0; day < 10; day++) {
        int Red_Branch = Red_resource["branch"], Red_Dewdrop = Red_resource["dewdrop"], Red_Leaf = Red_resource["leaf"], Red_Stone = Red_resource["stone"];
        int Green_Branch = Green_resource["branch"], Green_Dewdrop = Green_resource["dewdrop"], Green_Leaf = Green_resource["leaf"], Green_Stone = Green_resource["stone"];
        bool FlagDop = false, FlagOut = false, FlagInOut = false, FlagKek = false, FlagKek2 = false;

        int queendaysred = 0, queendaysgreen = 0;

        queendaysred++;
        queendaysgreen++;

        if (queendaysred >= 3 && queendaysred <= 5) {
            int rqs = rand() % 2;
            if (rqs == 0) {
                Queen_Red.Larva();
                queendaysred = 0;
            } else break;
        }

        if (queendaysgreen >= 2 && queendaysgreen <= 4) {
            int gqs = rand() % 2;
            if (gqs == 0) {
                Queen_Green.Larva();
                queendaysgreen = 0;
            } else break;
        }

        int Silkworm_count = 0;

        if (day == randomDay || (day < randomDay + 3 && day > randomDay) && Silkworm_count == 0) {
            FlagDop = true;
            for (int i = 0; i < RedWorker_count; i++) {
                if (Peasant_Red_Special[i].health > 0) {
                    int randomHeap = rand() % 5;
                    Peasant_Red_Special[i].heap_location = randomHeap + 1;
                    switch (Peasant_Red_Special[i].heap_location) {
                        case 1: {
                            Peasant_Red_Special[i].Resource_collecting(heap1);
                            break;
                        }
                        case 2: {
                            Peasant_Red_Special[i].Resource_collecting(heap2);
                            break;
                        }
                        case 3: {
                            Peasant_Red_Special[i].Resource_collecting(heap3);
                            break;
                        }
                        case 4: {
                            Peasant_Red_Special[i].Resource_collecting(heap4);
                            break;
                        }
                        case 5: {
                            Peasant_Red_Special[i].Resource_collecting(heap5);
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
            Silkworm_count = 1;
        } else {
            Silkworm_count = 0;
            for (int i = 0; i < RedWorker_count; i++) {
                if (Peasant_Red[i].health > 0) {
                    int randomHeap = rand() % 5;
                    Peasant_Red[i].heap_location = randomHeap + 1;
                    switch (Peasant_Red[i].heap_location) {
                        case 1: {
                            Peasant_Red[i].Resource_collecting(heap1);
                            break;
                        }
                        case 2: {
                            Peasant_Red[i].Resource_collecting(heap2);
                            break;
                        }
                        case 3: {
                            Peasant_Red[i].Resource_collecting(heap3);
                            break;
                        }
                        case 4: {
                            Peasant_Red[i].Resource_collecting(heap4);
                            break;
                        }
                        case 5: {
                            Peasant_Red[i].Resource_collecting(heap5);
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
        }
        if (day == randomDay || (day < randomDay + 3 && day > randomDay) && Silkworm_count == 0) {
            FlagDop = true;
            for (int i = 0; i < GreenWorker_count; i++) {
                if (Peasant_Green_Special[i].health > 0) {
                    int randomHeap = rand() % 5;
                    Peasant_Green_Special[i].heap_location = randomHeap + 1;
                    switch (Peasant_Green_Special[i].heap_location) {
                        case 1: {
                            Peasant_Green_Special[i].Resource_collecting(heap1);
                            break;
                        }
                        case 2: {
                            Peasant_Green_Special[i].Resource_collecting(heap2);
                            break;
                        }
                        case 3: {
                            Peasant_Green_Special[i].Resource_collecting(heap3);
                            break;
                        }
                        case 4: {
                            Peasant_Green_Special[i].Resource_collecting(heap4);
                            break;
                        }
                        case 5: {
                            Peasant_Green_Special[i].Resource_collecting(heap5);
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
            Silkworm_count = true;
        } else {
            Silkworm_count = false;
            for (int i = 0; i < GreenWorker_count; i++) {
                if (Peasant_Green[i].health > 0) {
                    int randomHeap = rand() % 5;
                    Peasant_Green[i].heap_location = randomHeap + 1;
                    switch (Peasant_Green[i].heap_location) {
                        case 1: {
                            Peasant_Green[i].Resource_collecting(heap1);
                            break;
                        }
                        case 2: {
                            Peasant_Green[i].Resource_collecting(heap2);
                            break;
                        }
                        case 3: {
                            Peasant_Green[i].Resource_collecting(heap3);
                            break;
                        }
                        case 4: {
                            Peasant_Green[i].Resource_collecting(heap4);
                            break;
                        }
                        case 5: {
                            Peasant_Green[i].Resource_collecting(heap5);
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
        }

        for (int k1 = 0; k1 < 40; k1++) {
            Warrior_Green[k1].heap_location = rand() % 5 + 1;
            Warrior_Red[k1].heap_location = rand() % 5 + 1;
        }

        Medvedka_red.heap_location = rand() % 5 + 1;
        Sverchok_green.heap_location = rand() % 5 + 1;

        for (int g = 0; g < GreenWarrior_count; g++) // атаки зелёных красными
        {
            if (Warrior_Green[g].health > 0) {
                for (int t2 = 0; t2 < Warrior_Green[g].target; t2++) {
                    FlagAttack = false;
                    for (int b = 0; b < RedWarrior_count; b++) {
                        Warrior_Red[b].Attack(Warrior_Green[g].damage, Warrior_Green[g].Bites_count,
                                              Warrior_Green[g].heap_location);
                        if (FlagAttack == true)
                            break;
                    }
                    if (FlagAttack == false) {
                        for (int a = 0; a < RedWorker_count; a++) {
                            Peasant_Red[a].Attack(Warrior_Green[g].damage, Warrior_Green[g].Bites_count,
                                                  Warrior_Green[g].heap_location);
                            if (FlagAttack == true)
                                break;
                        }
                    }
                    if (FlagAttack == false)
                        Medvedka_red.Attack(Warrior_Green[g].damage, Warrior_Green[g].Bites_count,
                                            Warrior_Green[g].heap_location);
                }
            }
        }

        for (int r = 0; r < RedWarrior_count; r++) // атаки красных зелёными
        {
            if (Warrior_Red[r].health > 0) {

                for (int t1 = 0; t1 < Warrior_Red[r].target; t1++) {
                    FlagAttack = false;
                    for (int y = 0; y < GreenWarrior_count; y++) {
                        Warrior_Green[y].Attack(Warrior_Red[r].damage, Warrior_Red[r].Bites_count,
                                                Warrior_Red[r].heap_location);
                        if (FlagAttack == true)
                            break;
                    }
                    if (FlagAttack == false) {
                        for (int x = 0; x < GreenWorker_count; x++) {
                            Peasant_Green[x].Attack(Warrior_Red[r].damage, Warrior_Red[r].Bites_count,
                                                    Warrior_Red[r].heap_location);
                            if (FlagAttack == true)
                                break;
                        }
                    }
                    if (FlagAttack == false)
                        Sverchok_green.Attack(Warrior_Red[r].damage, Warrior_Red[r].Bites_count,
                                              Warrior_Red[r].heap_location);
                }
            }
        }

        for (int h = 0; h < Sverchok_green.target; h++) // атакуют сверчка
        {
            FlagAttack = false;
            for (int y = 0; y < RedWarrior_count; y++) {
                Warrior_Red[y].Attack(Sverchok_green.damage, 1, Sverchok_green.heap_location);
                if (FlagAttack == 1)
                    break;
            }
            if (FlagAttack == 0) {
                for (int x = 0; x < RedWorker_count; x++) {
                    Peasant_Red[x].Attack(Sverchok_green.damage, 1, Sverchok_green.heap_location);
                    if (FlagAttack == 1)
                        break;
                }
            }
        }

        line();

        cout << "\n\t\tНачало дня:";
        cout << "\nдень " << day + 1 << " до засухи осталось " << 9 - day << " дней" << endl;
        cout << endl;

        int Warrior_green_count = 0, Warrior_red_count = 0, Peasant_green_count = 0, Peasant_red_count = 0, Medvedka_red_count = 0, Sverchok_green_count = 0;

        for (int a = 0; a < 40; a++) // кол-во муравьёв
        {
            if (Warrior_Green[a].health > 0)
                Warrior_green_count++;
            if (Warrior_Red[a].health > 0)
                Warrior_red_count++;
        }

        for (int x = 0; x < 40; x++) {
            if (Peasant_Green[x].health > 0)
                Peasant_green_count++;
            if (Peasant_Red[x].health > 0)
                Peasant_red_count++;
        }

        if (Medvedka_red.health > 0)
            Medvedka_red_count++;

        if (Sverchok_green.health > 0)
            Sverchok_green_count++;

        cout << "Колония Красных\n" << "   Королева: Беатрикс " << endl;
        cout << "   Ресурсы: веточка = " << Red_resource["branch"] << "  листик = " << Red_resource["leaf"]
             << "  камушек = " << Red_resource["stone"] << "  росинка = " << Red_resource["dewdrop"] << ";\n" << endl;
        cout << "   Популяция " << Warrior_red_count + Peasant_red_count + Medvedka_red_count << ": рабочих = "
             << Peasant_red_count << ", воинов = " << Warrior_red_count << ", особенных = " << Medvedka_red_count
             << ";\n" << endl;
        cout << "Колония Зеленых\n" << "   Королева: София " << endl;
        cout << "   Ресурсы: веточка = " << Green_resource["branch"] << "  листик = " << Green_resource["leaf"]
             << "  камушек = " << Green_resource["stone"] << "  росинка = " << Green_resource["dewdrop"] << endl;
        cout << "   Популяция " << Warrior_green_count + Peasant_green_count + Sverchok_green_count << ": рабочих = "
             << Peasant_green_count << ", воинов = " << Warrior_green_count << ", особенных = " << Sverchok_green_count
             << ";\n" << endl;
        cout << "Куча 1: " << "веточка = " << heap1.branch << ", листик = " << heap1.leaf << ", камушек = "
             << heap1.stone << ", росинка = " << heap1.dewdrop << ";\n" << endl;
        cout << "Куча 2: " << "веточка = " << heap2.branch << ", листик = " << heap2.leaf << ", камушек = "
             << heap2.stone << ", росинка = " << heap2.dewdrop << ";\n" << endl;
        cout << "Куча 3: " << "веточка = " << heap3.branch << ", листик = " << heap3.leaf << ", камушек = "
             << heap3.stone << ", росинка = " << heap3.dewdrop << ";\n" << endl;
        cout << "Куча 4: " << "веточка = " << heap4.branch << ", листик = " << heap4.leaf << ", камушек = "
             << heap4.stone << ", росинка = " << heap4.dewdrop << ";\n" << endl;
        cout << "Куча 5: " << "веточка = " << heap5.branch << ", листик = " << heap5.leaf << ", камушек = "
             << heap5.stone << ", росинка = " << heap5.dewdrop << ";\n" << endl;

        if (FlagDop)
            cout
                    << "\nГлобальный эффект:\n _Шелкопряд_ происходит каждый день \nнити шелкопряда позволяют увеличить количество ресурсов, которые можно переносить на 1 всеми насекомыми);"
                    << endl;

        if (day == 9) {
            cout << "\nНаступила засуха\n";
            int Red_resource_count =
                    Red_resource["branch"] + Red_resource["leaf"] + Red_resource["dewdrop"] + Red_resource["stone"];
            int Green_resource_count = Green_resource["branch"] + Green_resource["leaf"] + Green_resource["dewdrop"] +
                                       Green_resource["stone"];
            (Red_resource_count > Green_resource_count) ? cout << "Выиграла КРАСНАЯ колония муравьев " : cout
                    << "Выиграла ЗЕЛЁНАЯ колония муравьев";
        }

        if (day != 9) {
start0:
            cout << "\n\n\t"
                 << "Нажмите <1>(статистика красной колонии) или <2>(статистика зелёной колонии), <3>(Подробная статистика дня),\n \t\t\t\t\t<4>(Информация о каждом муравье)\n \t\t\t\t\t\t<9>(Играть)"
                 << "\n\n" << endl;
            cin >> choise;
            switch (choise) {
                case 1:
                    line2();
                    cout << "\t\tСтатистика" << endl;
                    line2();
                    cout << "Колония Красных:\n" << "   Королева: Беатрикс;" << endl;
                    cout << "Здоровье = " << Queen_Red.health << ", защита = " << Queen_Red.armor << ", урон = "
                         << Queen_Red.damage << endl;
                    cout << "   Ресурсы: веточка = " << Red_resource["branch"] << "  листик = " << Red_resource["leaf"]
                         << "  камушек = " << Red_resource["stone"] << "  росинка = " << Red_resource["dewdrop"]
                         << ";\n" << endl;
                    cout << "<<<<<<<<<< Рабочие >>>>>>>>>>" << endl;
                    cout << "Тип: Легендарный\n" << "   Параметры: здоровье = " << Peasant_Red[0].health
                         << ", защита = " << Peasant_Red[0].armor << endl;
                    cout << "Тип: Обычный\n" << "   Параметры: здоровье = " << Peasant_Red[4].health << ", защита = "
                         << Peasant_Red[4].armor << endl;
                    cout << "Тип: Старший спринтер\n" << "   Параметры: здоровье = " << Peasant_Red[10].health
                         << ", защита = " << Peasant_Red[10].armor << endl;
                    cout
                            << "Модификатор: может брать 1 ресурс: 'росинка или веточка' за раз; не может быть атакован первым."
                            << endl;
                    cout << "<<<<<<<<<< Воины >>>>>>>>>>" << endl;
                    cout << "Тип: Обычный\n" << "   Параметры: здоровье = " << Warrior_Red[0].health << ", защита = "
                         << Warrior_Red[0].armor << ", урон = " << Warrior_Red[0].damage << endl;
                    cout << "Тип: Элитный\n" << "   Параметры: здоровье = " << Warrior_Red[2].health << ", защита = "
                         << Warrior_Red[2].armor << ", урон = " << Warrior_Red[2].damage << endl;
                    cout << "Тип: Легендарный трусливый\n" << "   Параметры: здоровье = " << Warrior_Red[4].health
                         << ", защита = " << Warrior_Red[4].armor << ", урон = " << Warrior_Red[4].damage << endl;
                    cout
                            << "Модификатор: может атаковать 3 цели за раз и наносит 1 укус; если кто-то из союзников получил урон, то не атакует."
                            << endl;
                    cout << "<<<<<<<<<< Особенный >>>>>>>>>>" << endl;
                    cout << "Тип: Трудолюбивый неуязвимый мирный марафонец - Медведка\n" << "   Параметры: здоровье = "
                         << Medvedka_red.health << ", защита = " << Medvedka_red.armor << endl;
                    cout
                            << "Модификаторы: \nможет брать ресурсы (1 ресурс: веточка); \nне может быть атакован войнами; \nпосле смерти все равно доставляет ресурс в колонию."
                            << endl;
                    line2();
                    FlagOut = true;
                    goto start0;

                case 2:
                    line2();
                    cout << "\t\tСтатистика" << endl;
                    line2();
                    cout << "Колония Зелёные:\n" << "   Королева: София;" << endl;
                    cout << "Здоровье = " << Queen_Green.health << ", защита = " << Queen_Green.armor << ", урон = "
                         << Queen_Green.damage << endl;
                    cout << "   Ресурсы: веточка = " << Green_resource["branch"] << "  листик = "
                         << Green_resource["leaf"] << "  камушек = " << Green_resource["stone"] << "  росинка = "
                         << Green_resource["dewdrop"] << ";\n" << endl;
                    cout << "<<<<<<<<<< Рабочие >>>>>>>>>>" << endl;
                    cout << "Тип: Обычный\n" << "   Параметры: здоровье = " << Peasant_Green[0].health << ", защита = "
                         << Peasant_Green[0].armor << endl;
                    cout << "Тип: Элитный\n" << "   Параметры: здоровье = " << Peasant_Green[7].health << ", защита = "
                         << Peasant_Green[7].armor << endl;
                    cout << "Тип: Старший любимчик королевы\n" << "   Параметры: здоровье = "
                         << Peasant_Green[12].health << ", защита = " << Peasant_Green[12].armor << endl;
                    cout
                            << "Модификатор: может брать 1 ресурс: 'листик или камушек' за раз; всегда отправляется только на ту кучу, где нет вражеских воинов."
                            << endl;
                    cout << "<<<<<<<<<< Воины >>>>>>>>>>" << endl;
                    cout << "Тип: Элитный\n" << "   Параметры: здоровье = " << Warrior_Green[0].health << ", защита = "
                         << Warrior_Green[0].armor << ", урон = " << Warrior_Green[0].damage << endl;
                    cout << "Тип: Легендарный\n" << "   Параметры: здоровье = " << Warrior_Green[2].health
                         << ", защита = " << Warrior_Green[2].armor << ", урон = " << Warrior_Green[2].damage << endl;
                    cout << "Тип: Продвинутый мстительный\n" << "   Параметры: здоровье = " << Warrior_Green[4].health
                         << ", защита = " << Warrior_Green[4].armor << ", урон = " << Warrior_Green[4].damage << endl;
                    cout
                            << "Модификатор: может атаковать 2 цели за раз и наносит 1 укус; убивает своего убийцу, даже если он неуязвим."
                            << endl;
                    cout << "<<<<<<<<<< Особенный >>>>>>>>>>" << endl;
                    cout << "Тип: Трудолюбивый обычный агрессивный толстый ветеран - Сверчок\n"
                         << "   Параметры: здоровье = " << Sverchok_green.health << ", защита = "
                         << Sverchok_green.armor << endl;
                    cout
                            << "Модификаторы: \nможет брать ресурсы (1 ресурс: листик); \nможет быть атакован войнами; \nатакует врагов(2 цели за раз и наносит 1 укус); \nпринимает все атаки на себя, здоровье и защита увеличены в двое; \nотменяет все модификаторы своих и вражеских рабочих."
                            << endl;
                    line2();
                    FlagOut = true;
                    goto start0;

                case 3: {
                    FlagOut = true;
                    cout << "Начало Похода:\n" << endl;

                    int RedPeas = 0, RedWar = 0, GreenPeas = 0, GreenWar = 0;
                    bool RedS = false, GreenS = false;

                    for (int red = 0; red < 5; red++) {
                        for (int i = 0; i < 40; i++) {
                            (Peasant_Red[i].heap_location == (red + 1) && Peasant_Red[i].health > 0) ? RedPeas++
                                                                                                     : RedPeas = RedPeas;
                            (Warrior_Red[i].heap_location == (red + 1) && Warrior_Red[i].health > 0) ? RedWar++
                                                                                                     : RedWar = RedWar;
                        }
                        (Medvedka_red.heap_location == (red + 1) && Medvedka_red.health > 0) ? RedS = true
                                                                                             : RedS = false;
                        if (RedPeas > 0 || RedWar > 0 || RedS)
                            cout << "   С колонии Красных отправилось: рабочих = " << RedPeas << ", воинов = " << RedWar
                                 << ",\n oсобенных = " << RedS << " на кучу " << red + 1 << endl;
                    }

                    for (int green = 0; green < 5; green++) {
                        for (int i = 0; i < 40; i++) {
                            (Peasant_Green[i].heap_location == (green + 1) && Peasant_Green[i].health > 0) ? GreenPeas++
                                                                                                           : GreenPeas = GreenPeas;
                            (Warrior_Green[i].heap_location == (green + 1) && Warrior_Green[i].health > 0) ? GreenWar++
                                                                                                           : GreenWar = GreenWar;
                        }
                        (Sverchok_green.heap_location == (green + 1) && Sverchok_green.health > 0) ? GreenS = true
                                                                                                   : GreenS = false;
                        if (GreenPeas > 0 || (GreenWar > 0) || GreenS)
                            cout << "   С колонии Зелёных отправилось: рабочих = " << GreenPeas << ", воинов = "
                                 << GreenWar << ",\n oсобенных = " << GreenS << " на кучу " << green + 1 << endl;
                    }

                    cout << "\nКонец Похода:" << endl;

                    int RedPeasAlive = 0, GreenPeasAlive = 0, RedWarAlive = 0, GreenWarAlive = 0;
                    bool RedSAlive = false, GreenSAlive = false;

                    for (int i = 0; i < 40; i++) {
                        (Peasant_Red[i].health > 0) ? RedPeasAlive++ : RedPeasAlive = RedPeasAlive;
                        (Warrior_Red[i].health > 0) ? RedWarAlive++ : RedWarAlive = RedWarAlive;
                    }

                    (Medvedka_red.health > 0) ? RedSAlive = true : RedSAlive = false;

                    for (int i = 0; i < 40; i++) {
                        (Peasant_Green[i].health > 0) ? GreenPeasAlive++ : GreenPeasAlive = GreenPeasAlive;
                        (Warrior_Green[i].health > 0) ? GreenWarAlive++ : GreenWarAlive = GreenWarAlive;
                    }

                    (Sverchok_green.health > 0) ? GreenSAlive = true : GreenSAlive = false;

                    cout << "\nВ колонию Красныx вернулись:\n   рабочие = " << RedPeasAlive << ", воины = "
                         << RedWarAlive << ", oсобенные = " << RedSAlive << endl;
                    cout << "   Добыто ресурсов: \n      веточек = " << Red_resource["branch"] - Red_Branch
                         << "; \n      листиков = " << Red_resource["leaf"] - Red_Leaf << "; \n      камушков = "
                         << Red_resource["stone"] - Red_Stone << "; \n      росинок = "
                         << Red_resource["dewdrop"] - Red_Dewdrop << endl;
                    (RedLarva > 0) ? cout << "   Новые личинки: " << RedLarva << endl : cout << "   Личинки еще растут"
                                                                                             << endl;
                    cout << "В колонию Зелёных вернулись:\n   рабочие = " << GreenPeasAlive << ", воины = "
                         << GreenWarAlive << ", oсобенные = " << GreenSAlive << endl;
                    cout << "   Добыто ресурсов: \n      веточек = " << Green_resource["branch"] - Green_Branch
                         << "; \n      листиков = " << Green_resource["leaf"] - Green_Leaf << "; \n      камушков = "
                         << Green_resource["stone"] - Green_Stone << "; \n      росинок = "
                         << Green_resource["dewdrop"] - Green_Dewdrop << endl;
                    (GreenLarva > 0) ? cout << "   Новые личинки: " << GreenLarva << endl : cout
                            << "   Личинки еще растут" << endl;
                    goto start0;
                }

                case 4: {
                    FlagOut = true;
                    line();
start:
                    cout << "\t<1>Красные\t<2>Зелёные\n\t\t\t<9>Назад" << endl;
                    line();
                    cout << "\n";
                    cin >> rg;

                    switch (rg) {
                        case 1: {
start1:
                            line();
                            cout << "\t<0>Легендарный рабочий\t<1>Обычный рабочий\t<2>Старший спринтер рабочий\n\t<3>Обычный воин\t<4>Элитный воин\t<5>Легендарный трусливый воин\n \t\t\t\t\t\t<9>(Назад)" << endl;
                            line();
                            cout << "\n";
                            cin >> multy;
                            switch (multy) {
                                case 0:
                                    Worker::Print_Ant("Легендарный рабочий", 10, 6, 0, "Беатрикс", 'r');
                                    goto start1;
                                case 1:
                                    Worker::Print_Ant("Обычный рабочий", 1, 0, 0, "Беатрикс", 'r');
                                    goto start1;
                                case 2:
                                    Worker::Print_Ant("Старший спринтер рабочий", 2, 1, 0, "Беатрикс", 'r');
                                    goto start1;
                                case 3:
                                    Warrior::Print_Ant("Обычный воин", 1, 0, 1, "Беатрикс", 'v');
                                    goto start1;
                                case 4:
                                    Warrior::Print_Ant("Элитный воин", 8, 4, 5, "Беатрикс", 'v');
                                    goto start1;
                                case 5:
                                    Warrior::Print_Ant("Легендарный трусливый воин", 10, 6, 4, "Беатрикс", 'v');
                                    goto start1;
                                case 9:
                                    goto start;
                                default:
                                    break;
                            }
                            break;
                        }
                        case 2: {
start12:
                            line();
                            cout << "\t<0>Обычный рабочий;\t<1>Элитный рабочий\t<2>Старший любимчик королевы рабочий\n\t<3>Элитный воин\t<4>Легендарный воин\t<5>Продвинутый мстительный воин\n \t\t\t\t\t\t<9>(Назад)" << endl;
                            line();
                            cout << "\n";
                            cin >> multy2;
                            switch (multy2) {
                                case 0:
                                    Worker::Print_Ant("Обычный рабочий", 1, 0, 0, "София", 'r');
                                    goto start12;
                                case 1:
                                    Worker::Print_Ant("Элитный рабочий", 8, 4, 0, "София", 'r');
                                    goto start12;
                                case 2:
                                    Worker::Print_Ant("Старший любимчик королевы рабочий", 2, 1, 0, "София", 'r');
                                    goto start12;
                                case 3:
                                    Warrior::Print_Ant("Элитный воин", 8, 4, 5, "София", 'v');
                                    goto start12;
                                case 4:
                                    Warrior::Print_Ant("Легендарный воин", 10, 6, 4, "София", 'v');
                                    goto start12;
                                case 5:
                                    Warrior::Print_Ant("Продвинутый мстительный воин", 6, 2, 3, "София", 'v');
                                    goto start12;
                                case 9:
                                    goto start;
                                default:
                                    break;
                            }
                            break;
                        }
                        case 9: {
                            goto start0;
                        }
                        default:
                            break;
                    }
                    break;
                }
                case 9: {
                    break;
                }
                default:
                    break;
            }
            if (FlagOut == 1)
                int b = _getch();
        }
    }
    return 0;
}
