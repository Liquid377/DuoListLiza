#include <iostream>
#include <fstream>
#include <Windows.h>
#include "conio.h"
#include "locale.h"
#include <string>
#define LIST struct List
using namespace std;

struct STUDENT
{
    char fam[25];
    char ini[25];
    char group[25];
    char grade[25];
};

LIST//Структура элемента двусвязного списка
{
STUDENT info;//Информация о ученике
LIST* next;//Указатель на следующий элемент
LIST* prev;//Указатель на предыдущийа
};
int cnt = 0;
void print_menu()//Вывод меню
{
    cout << "Введите пункт меню" << endl;
    cout << "1) Добавить информацию о ученике" << endl;
    cout << "2) Удалить информацию о ученике" << endl;
    cout << "3) Вывод всех учеников" << endl;
    cout << "4) Вывод учеников с двойками" << endl;
    cout << "5) Вывод учеников в file.txt" << endl;
    cout << "6) Ввод учеников из input.txt" << endl;
    cout << "7) Помощь" << endl;
    cout << "8) О программе" << endl;
    cout << "0) Выход" << endl;
    cout << endl;
}
void view(LIST** current);
int sred(char* s);
void ins(LIST** current, STUDENT item, char* fm) //Добавление в список
{
    LIST* new_node;
    new_node = new LIST;
    new_node->info = item;
    LIST* temp = *current;

    int flag = 0;//Переменная принимающая значение 1 при добавлении нового элемента
   while (temp)
    {
        if (temp->prev == NULL  and flag == 0) {
            flag = 1;
            new_node->prev = NULL;
            new_node->next = (*current);
            (*current)->prev = new_node;
            (*current) = new_node;
            cnt++;
        } 
        if (temp->prev == NULL and sred(temp->info.grade) <= sred(temp->next->info.grade) and flag == 0) //Вставка в начало
        {
            flag = 1;
            new_node->prev = NULL;
            new_node->next = (*current);
            (*current)->prev = new_node;
            (*current) = new_node;
        }

       else if (temp->next == NULL and sred(temp->prev->info.grade) >= sred(temp->info.grade) and flag == 0) //Вставка в конец
        {
            temp->next = new_node;
            new_node->prev = temp;
            new_node->next = NULL;
            temp = new_node;
            flag = 1;

        } 
        //else if (sred(temp->prev->info.grade) >= sred(temp->info.grade) and flag == 0) //Вставка в конец
        //{
        //    temp->next = new_node;
        //    new_node->prev = temp;
        //    new_node->next = NULL;
        //    temp = new_node;
         //   flag = 1;

        //}
        /*else if (flag == 0)
        {
            if (sred(temp->prev->info.grade) <= sred(temp->info.grade) and sred(temp->next->info.grade) >= sred(temp->info.grade))//Вставка посередине
            {
                new_node->next = temp->next;
                temp->next->prev = new_node;
                new_node->prev = temp;
                temp->next = new_node;
                flag = 1;
            }
         } */
       temp = temp->next;
    }
    if (flag == 0)
    {
        *current = new_node;
        new_node->next = NULL;
        new_node->prev = NULL;
    } 
    cout << "Ученик добавлен" << endl;
}

int sred(char *s) {
    int sr = 0;
    string str;
    string a;
    str = s;
    for (int i = 0; i < 10; i++) {
        a = str[i];
        try { sr += stoi(a); }
        catch (...) {

        }
    }
    sr = sr / 5;
    return sr;
}

void del(LIST** current, char* fm)//Удаление элемента
{
    if (*current)
    {
        LIST* old_node = *current;
        LIST temp;
        int count = 0;
        while (old_node)
        {
            if (strcmp(old_node->info.fam, fm) == 0)
                count += 1;
            old_node = old_node->next;
        }
        old_node = *current;
        if (count <= 1) {
            while (old_node)
            {
                if (strcmp(old_node->info.fam, fm) == 0)
                {
                    temp = *old_node;
                    if (old_node->prev == NULL)//Если ученик в начале
                    {
                        *current = (*current)->next;
                        if (*current)
                            (*current)->prev = NULL;
                    }
                    else
                    {
                        if (old_node->next == NULL)//Если ученик в конце
                        {
                            old_node->prev->next = NULL;
                        }
                        else//Если ученик посередине
                        {
                            old_node->prev->next = old_node->next;
                            old_node->next->prev = old_node->prev;
                        }
                    }
                    cout << "Работник удалён";
                    cout << endl;
                    free(old_node);
                    old_node = &temp;
                }
                if (old_node) old_node = old_node->next;
            }
            if (old_node == NULL)
            {
                cout << "Достигнут конец списка" << endl;
            }
        }
        else
        {
            int counter = 1;
            while (old_node)
            {
                if (strcmp(old_node->info.fam, fm) == 0)
                {
                    cout << "(" << counter << ")" << endl;
                    cout << "Фамилия: ";
                    cout << old_node->info.fam << endl;
                    cout << "И.О.:      ";
                    cout << old_node->info.ini << endl;
                    cout << "Группа:    ";
                    cout << old_node->info.group << endl;
                    cout << "Успеваемость: ";
                    cout << old_node->info.grade << endl;
                    cout << endl;
                    cout << endl;
                    counter++;
                }
                old_node = old_node->next;
            }
            old_node = *current;
            int choice;
            do
            {
                cout << "Удалить все или только определенного?" << endl;
                cout << "(1)Все" << endl;
                cout << "(2)Определенные" << endl;
                cin >> choice;
            } while (choice < 1 or (choice > 2));
            if (choice == 1)
            {
                while (old_node)
                {
                    if (strcmp(old_node->info.fam, fm) == 0)
                    {
                        temp = *old_node;
                        if (old_node->prev == NULL)//Если ученик в начале
                        {
                            *current = (*current)->next;
                            if (*current)
                                (*current)->prev = NULL;
                        }
                        else
                        {
                            if (old_node->next == NULL)//Если ученик в конце
                            {
                                old_node->prev->next = NULL;
                            }
                            else//Если ученик посередине
                            {
                                old_node->prev->next = old_node->next;
                                old_node->next->prev = old_node->prev;
                            }
                        }
                        cout << "Ученик удалён";
                        cout << endl;
                        free(old_node);
                        old_node = &temp;
                    }
                    if (old_node) old_node = old_node->next;
                }
                if (old_node == NULL)
                {
                    cout << "Достигнут конец списка" << endl;
                }
            }
            else
            {
                int number = 0;
                int counter_del = 0;
                do {
                    cout << "Введите кого удалить:";
                    cin >> number;
                } while (number < 1 or (number > counter - 1));

                while (old_node)
                {
                    if (strcmp(old_node->info.fam, fm) == 0)
                    {
                        counter_del += 1;
                        if (counter_del == number)
                        {
                            temp = *old_node;
                            if (old_node->prev == NULL)//Если ученик в начале
                            {
                                *current = (*current)->next;
                                if (*current)
                                    (*current)->prev = NULL;
                            }
                            else
                            {
                                if (old_node->next == NULL)//Если ученик в конце
                                {
                                    old_node->prev->next = NULL;
                                }
                                else//Если ученик посередине
                                {
                                    old_node->prev->next = old_node->next;
                                    old_node->next->prev = old_node->prev;
                                }
                            }
                            cout << "Ученик удалён";
                            cout << endl;
                            free(old_node);
                            old_node = &temp;
                        }
                    }
                    if (old_node) old_node = old_node->next;
                }
                if (old_node == NULL)
                {
                    cout << "Достигнут конец списка" << endl;
                }
            }


        }
    }
    else { cout << "База пуста" << endl; }
}
void find(LIST** current)//Выборка по стажу
{
    int name_found = 0;
    List* temp = *current;
    string str;


    int counter = 1;//Номер ученика по списку
    while (temp)
    {
        str = temp->info.grade;
        if (str.find("2") != string::npos)
        {
            cout << "(" << counter << ")" << endl;
            cout << "Фамилия: ";
            cout << temp->info.fam << endl;
            cout << "И.О.:      ";
            cout << temp->info.ini << endl;
            cout << "Группа:    ";
            cout << temp->info.group << endl;
            cout << "Успеваемость: ";
            cout << temp->info.grade << endl;
            cout << endl;
            cout << endl;
            name_found = 1;
            counter++;
        }
        temp = temp->next;
    }
    if (name_found == 0)
    {
        cout << "В базе нет ученика с таким стажем";
        cout << endl;
    } 
} 
/*void swap(LIST** i, LIST** j) {
    LIST* T = *i;
    LIST* F = *j;
    LIST* TEMP = T;
    T->next = F->next;
    T->prev = F->prev;
    F->next = TEMP->next;
    F->prev = TEMP->prev;
}
void sort(LIST** current) {
    int max = 0;
    LIST* temp = *current;
    LIST* I;
    LIST* J;
    I = temp;
    J = temp->next->next;
    /*for (int i = 0; i < cnt; i++) {
        if (sred(temp->info.grade) >= max) max = sred(temp->info.grade);
        temp = temp->next;
    }
    if (temp) {
        while (temp->prev != NULL)
        {
            temp = temp->prev;
        }
    }
    for (int i = 0; i < cnt; i++) {
        if ((sred(temp->info.grade) <= max)) {
            J = temp;
        }
        temp = temp->next;
    } 
    swap(I, J); 

} */
    

void view(LIST** current)//Вывод всех учеников
{
    int counter = 1;//Номер ученика по списку
    LIST* temp = *current;
    int max = 0;
    for (int i = 0; i < cnt; i++) {
        if (sred(temp->info.grade) >= max) max = sred(temp->info.grade);
        temp->next;
    }
    if (temp) {
        while (temp->prev != NULL)
        {
            temp = temp->prev;
        }
    }
    cout << max << endl;
    if (temp) {
        while (temp)
        {
            if(sred(temp->info.grade) == max)
            {
                cout << "(" << counter << ")" << endl;
                cout << "Фамилия: ";
                cout << temp->info.fam << endl;
                cout << "И.О.:      ";
                cout << temp->info.ini << endl;
                cout << "Группа:    ";
                cout << temp->info.group << endl;
                cout << "Успеваемость: ";
                cout << temp->info.grade << endl;
                cout << endl;
                cout << endl;
            }
            counter++;
            temp = temp->next;
            system("pause");
        }
    }
    else
    {
        cout << "База пуста" << endl;
    }
}

void revview(LIST** current)//Вывод всех учеников
{
    int counter = 1;//Номер ученика по списку
    LIST* temp = *current;
    if (temp) {
        while (temp->next!=NULL)
        {
            temp = temp->next;
        }
    }
    if (temp) {
        while (temp)
        {
            cout << "(" << counter << ")" << endl;
            cout << "Фамилия: ";
            cout << temp->info.fam << endl;
            cout << "И.О.:      ";
            cout << temp->info.ini << endl;
            cout << "Группа:    ";
            cout << temp->info.group << endl;
            cout << "Успеваемость: ";
            cout << temp->info.grade << endl;
            cout << endl;
            cout << endl;
            temp = temp->prev;
            counter++;
        }
    }
    else
    {
        cout << "База пуста" << endl;
    }
}



void file_output(LIST** current) //Вывод в файл
{
    int counter = 1;
    LIST* temp = *current;
    fstream file("file.txt");//Открытие(создание) файла (Можно поменять на input.txt)
    if (file) {//Если файл удалось открыть(создать)
        if (temp) {//Если список не пуст
            while (temp)//Пока не конец списка
            {
                //Выводится вся информация в файл
                file << "Фамилия: ";
                file << temp->info.fam << endl;
                file << "И.О.:      ";
                file << temp->info.ini << endl;
                file << "Группа:    ";
                file << temp->info.group << endl;
                file << "Успеваемость: ";
                file << temp->info.grade << endl;
                file << endl; //
                file << endl; //
                temp = temp->next;
                counter++;
            }
            cout << "Запись в file.txt законченна" << endl;
            file.close();
        }
        else
        {
            cout << "Нечего вводить в файл" << endl;
        }
    }
}

void clear_mem(LIST** current)
{
    LIST* old_node = *current;
    LIST temp;
    while (old_node)
    {
        temp = *old_node;
        if (old_node->prev == NULL)//Если ученик в начале
        {
            *current = (*current)->next;
            if (*current)
                (*current)->prev = NULL;
        }
        else
        {
            if (old_node->next == NULL)//Если ученик в конце
            {
                old_node->prev->next = NULL;
            }
            else//Если ученик посередине
            {
                old_node->prev->next = old_node->next;
                old_node->next->prev = old_node->prev;
            }
        }
        cout << "Ученик удалён";
        cout << endl;
        free(old_node);
        old_node = &temp;
        if (old_node) old_node = old_node->next;
    }
    if (old_node == NULL)
    {
        cout << "Достигнут конец списка" << endl;
    }
}


int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    LIST* L = 0;
    int choice;
    print_menu();
    STUDENT* s;
    bool good = false;
    while (1)
    {
        do
        {
            cout << "Ваш выбор:";
            cin >> choice;
        } while (choice < 0 or (choice > 8));

        cout << "-----------------------------------" << endl;
        switch (choice)
        {
        case 1://Добавить
        {
            s = new STUDENT;
            cout << "Введите фамилию ученика: ";
            cin.ignore();
            cin.getline(s->fam, 25);
            cout << endl;

            cout << "Введите инициалы ученика: ";
            cin.getline(s->ini, 25);
            cout << endl;;

            cout << "Введите группу ученика: ";
            cin.getline(s->group, 25);
            cout << endl;

            cout << "Введите успеваемость ученика(5 оценок через пробел): ";
            cin.getline(s->grade, 25);
            cout << endl;

            ins(&L, *s, s->fam);
            cout << "Для продолжения нажмите ENTER.";
            system("PAUSE>nul");
            system("cls");
            print_menu();
            break;
        }
        case 2://Удалить
        {
            cout << "Введите фамилию ученика для удаления: ";
            char fam[25];
            cin.ignore();
            cin.getline(fam, 25);
            del(&L, fam);
            cout << "Для продолжения нажмите ENTER.";
            system("PAUSE>nul");
            system("cls");
            print_menu();
            break;
        }
        case 3://Все
        {
            //sort(&L);
            int choice;
            cout << "Как вывести список ?" << endl;
            cout << "Выбор пункта (1-Алфавитный/ 2-Обратный):";
            cin >> choice;
            if (choice == 1)
            {
                view(&L);
            }
            else
            {
                revview(&L);
            }
            cout << "Для продолжения нажмите ENTER.";
            system("PAUSE>nul");
            system("cls");
            print_menu();
            break;
        }
        case 4://Двоешники
        {
            find(&L);
            cout << "Для продолжения нажмите ENTER.";
            system("PAUSE>nul");
            system("cls");
            print_menu();
            break;
        }
        case 5://Вывод в файл
        {
            file_output(&L);
            cout << "Для продолжения нажмите ENTER.";
            system("PAUSE>nul");
            system("cls");
            print_menu();
            break;
        }
        case 6://Ввод из файла
        {
            s = new STUDENT;
            ifstream fin("input.txt");
            if (fin) {
                while (!fin.eof()) {
                    fin.getline(s->fam, 25);
                    fin.getline(s->ini, 25);
                    fin.getline(s->group, 25);
                    fin.getline(s->grade, 25);
                    ins(&L, *s, s->fam);//Добавление в список
                }
            }
            else
            {
                cout << "Не удалось открыть файл" << endl;
            }
            cout << "Для продолжения нажмите ENTER.";
            system("PAUSE>nul");
            system("cls");
            print_menu();
            break;
        }
        case 7://Помощь
        {
            cout << "Вариант 3" << endl;
            cout << " 1.) Составить программу, которая содержит текущую информацию об успеваемости студентов." << endl;
            cout << " Сведения о студентах включают:" << endl;
            cout << " • фамилия и инициалы" << endl;
            cout << " •	номер группы" << endl;
            cout << " •	успеваемость (массив из пяти элементов" << endl;
            cout << " 2.)	Программа должна обеспечивать :" << endl;
            cout << " • хранение сведений обо всех студентах в виде двусвязного списка, записи должны быть упорядочены по алфавиту;" << endl;
            cout << " •	добавление данных о новых студентах;" << endl;
            cout << " •	удаление данных о студенте, фамилия которого введена с клавиатуры;" << endl;
            cout << " •	вывод сведений обо всех студентах;" << endl;
            cout << " •	по запросу выводятся сведения о студентах, которые имеют хотя бы одну двойку." << endl;
            cout << " 3.)	Программа должна обеспечивать диалог с помощью меню." << endl;
            cout << "Для продолжения нажмите ENTER.";
            system("PAUSE>nul");
            system("cls");
            print_menu();
            break;
        }
        case 8://О программе
        {
            cout << "Программа 'Двусвязные списки'" << endl;
            cout << "Версия" << endl;
            cout << "Разработчик: Орлова Елизавета Ивановна, ИНБб 2301-02-00" << endl;
            cout << "Для продолжения нажмите ENTER.";
            system("PAUSE>nul");
            system("cls");
            print_menu();
            break;
        }
        case 0://Выход
        {
            //delete(&L);
            return 0;
        }
        }
        cout << "-----------------------------------" << endl;
    }
}