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

LIST//��������� �������� ����������� ������
{
STUDENT info;//���������� � �������
LIST* next;//��������� �� ��������� �������
LIST* prev;//��������� �� �����������
};
int cnt = 0;
void print_menu()//����� ����
{
    cout << "������� ����� ����" << endl;
    cout << "1) �������� ���������� � �������" << endl;
    cout << "2) ������� ���������� � �������" << endl;
    cout << "3) ����� ���� ��������" << endl;
    cout << "4) ����� �������� � ��������" << endl;
    cout << "5) ����� �������� � file.txt" << endl;
    cout << "6) ���� �������� �� input.txt" << endl;
    cout << "7) ������" << endl;
    cout << "8) � ���������" << endl;
    cout << "0) �����" << endl;
    cout << endl;
}
void view(LIST** current);
int sred(char* s);
void ins(LIST** current, STUDENT item, char* fm) //���������� � ������
{
    LIST* new_node;
    new_node = new LIST;
    new_node->info = item;
    LIST* temp = *current;

    int flag = 0;//���������� ����������� �������� 1 ��� ���������� ������ ��������
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
        if (temp->prev == NULL and sred(temp->info.grade) <= sred(temp->next->info.grade) and flag == 0) //������� � ������
        {
            flag = 1;
            new_node->prev = NULL;
            new_node->next = (*current);
            (*current)->prev = new_node;
            (*current) = new_node;
        }

       else if (temp->next == NULL and sred(temp->prev->info.grade) >= sred(temp->info.grade) and flag == 0) //������� � �����
        {
            temp->next = new_node;
            new_node->prev = temp;
            new_node->next = NULL;
            temp = new_node;
            flag = 1;

        } 
        //else if (sred(temp->prev->info.grade) >= sred(temp->info.grade) and flag == 0) //������� � �����
        //{
        //    temp->next = new_node;
        //    new_node->prev = temp;
        //    new_node->next = NULL;
        //    temp = new_node;
         //   flag = 1;

        //}
        /*else if (flag == 0)
        {
            if (sred(temp->prev->info.grade) <= sred(temp->info.grade) and sred(temp->next->info.grade) >= sred(temp->info.grade))//������� ����������
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
    cout << "������ ��������" << endl;
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

void del(LIST** current, char* fm)//�������� ��������
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
                    if (old_node->prev == NULL)//���� ������ � ������
                    {
                        *current = (*current)->next;
                        if (*current)
                            (*current)->prev = NULL;
                    }
                    else
                    {
                        if (old_node->next == NULL)//���� ������ � �����
                        {
                            old_node->prev->next = NULL;
                        }
                        else//���� ������ ����������
                        {
                            old_node->prev->next = old_node->next;
                            old_node->next->prev = old_node->prev;
                        }
                    }
                    cout << "�������� �����";
                    cout << endl;
                    free(old_node);
                    old_node = &temp;
                }
                if (old_node) old_node = old_node->next;
            }
            if (old_node == NULL)
            {
                cout << "��������� ����� ������" << endl;
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
                    cout << "�������: ";
                    cout << old_node->info.fam << endl;
                    cout << "�.�.:      ";
                    cout << old_node->info.ini << endl;
                    cout << "������:    ";
                    cout << old_node->info.group << endl;
                    cout << "������������: ";
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
                cout << "������� ��� ��� ������ �������������?" << endl;
                cout << "(1)���" << endl;
                cout << "(2)������������" << endl;
                cin >> choice;
            } while (choice < 1 or (choice > 2));
            if (choice == 1)
            {
                while (old_node)
                {
                    if (strcmp(old_node->info.fam, fm) == 0)
                    {
                        temp = *old_node;
                        if (old_node->prev == NULL)//���� ������ � ������
                        {
                            *current = (*current)->next;
                            if (*current)
                                (*current)->prev = NULL;
                        }
                        else
                        {
                            if (old_node->next == NULL)//���� ������ � �����
                            {
                                old_node->prev->next = NULL;
                            }
                            else//���� ������ ����������
                            {
                                old_node->prev->next = old_node->next;
                                old_node->next->prev = old_node->prev;
                            }
                        }
                        cout << "������ �����";
                        cout << endl;
                        free(old_node);
                        old_node = &temp;
                    }
                    if (old_node) old_node = old_node->next;
                }
                if (old_node == NULL)
                {
                    cout << "��������� ����� ������" << endl;
                }
            }
            else
            {
                int number = 0;
                int counter_del = 0;
                do {
                    cout << "������� ���� �������:";
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
                            if (old_node->prev == NULL)//���� ������ � ������
                            {
                                *current = (*current)->next;
                                if (*current)
                                    (*current)->prev = NULL;
                            }
                            else
                            {
                                if (old_node->next == NULL)//���� ������ � �����
                                {
                                    old_node->prev->next = NULL;
                                }
                                else//���� ������ ����������
                                {
                                    old_node->prev->next = old_node->next;
                                    old_node->next->prev = old_node->prev;
                                }
                            }
                            cout << "������ �����";
                            cout << endl;
                            free(old_node);
                            old_node = &temp;
                        }
                    }
                    if (old_node) old_node = old_node->next;
                }
                if (old_node == NULL)
                {
                    cout << "��������� ����� ������" << endl;
                }
            }


        }
    }
    else { cout << "���� �����" << endl; }
}
void find(LIST** current)//������� �� �����
{
    int name_found = 0;
    List* temp = *current;
    string str;


    int counter = 1;//����� ������� �� ������
    while (temp)
    {
        str = temp->info.grade;
        if (str.find("2") != string::npos)
        {
            cout << "(" << counter << ")" << endl;
            cout << "�������: ";
            cout << temp->info.fam << endl;
            cout << "�.�.:      ";
            cout << temp->info.ini << endl;
            cout << "������:    ";
            cout << temp->info.group << endl;
            cout << "������������: ";
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
        cout << "� ���� ��� ������� � ����� ������";
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
    

void view(LIST** current)//����� ���� ��������
{
    int counter = 1;//����� ������� �� ������
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
                cout << "�������: ";
                cout << temp->info.fam << endl;
                cout << "�.�.:      ";
                cout << temp->info.ini << endl;
                cout << "������:    ";
                cout << temp->info.group << endl;
                cout << "������������: ";
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
        cout << "���� �����" << endl;
    }
}

void revview(LIST** current)//����� ���� ��������
{
    int counter = 1;//����� ������� �� ������
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
            cout << "�������: ";
            cout << temp->info.fam << endl;
            cout << "�.�.:      ";
            cout << temp->info.ini << endl;
            cout << "������:    ";
            cout << temp->info.group << endl;
            cout << "������������: ";
            cout << temp->info.grade << endl;
            cout << endl;
            cout << endl;
            temp = temp->prev;
            counter++;
        }
    }
    else
    {
        cout << "���� �����" << endl;
    }
}



void file_output(LIST** current) //����� � ����
{
    int counter = 1;
    LIST* temp = *current;
    fstream file("file.txt");//��������(��������) ����� (����� �������� �� input.txt)
    if (file) {//���� ���� ������� �������(�������)
        if (temp) {//���� ������ �� ����
            while (temp)//���� �� ����� ������
            {
                //��������� ��� ���������� � ����
                file << "�������: ";
                file << temp->info.fam << endl;
                file << "�.�.:      ";
                file << temp->info.ini << endl;
                file << "������:    ";
                file << temp->info.group << endl;
                file << "������������: ";
                file << temp->info.grade << endl;
                file << endl; //
                file << endl; //
                temp = temp->next;
                counter++;
            }
            cout << "������ � file.txt ����������" << endl;
            file.close();
        }
        else
        {
            cout << "������ ������� � ����" << endl;
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
        if (old_node->prev == NULL)//���� ������ � ������
        {
            *current = (*current)->next;
            if (*current)
                (*current)->prev = NULL;
        }
        else
        {
            if (old_node->next == NULL)//���� ������ � �����
            {
                old_node->prev->next = NULL;
            }
            else//���� ������ ����������
            {
                old_node->prev->next = old_node->next;
                old_node->next->prev = old_node->prev;
            }
        }
        cout << "������ �����";
        cout << endl;
        free(old_node);
        old_node = &temp;
        if (old_node) old_node = old_node->next;
    }
    if (old_node == NULL)
    {
        cout << "��������� ����� ������" << endl;
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
            cout << "��� �����:";
            cin >> choice;
        } while (choice < 0 or (choice > 8));

        cout << "-----------------------------------" << endl;
        switch (choice)
        {
        case 1://��������
        {
            s = new STUDENT;
            cout << "������� ������� �������: ";
            cin.ignore();
            cin.getline(s->fam, 25);
            cout << endl;

            cout << "������� �������� �������: ";
            cin.getline(s->ini, 25);
            cout << endl;;

            cout << "������� ������ �������: ";
            cin.getline(s->group, 25);
            cout << endl;

            cout << "������� ������������ �������(5 ������ ����� ������): ";
            cin.getline(s->grade, 25);
            cout << endl;

            ins(&L, *s, s->fam);
            cout << "��� ����������� ������� ENTER.";
            system("PAUSE>nul");
            system("cls");
            print_menu();
            break;
        }
        case 2://�������
        {
            cout << "������� ������� ������� ��� ��������: ";
            char fam[25];
            cin.ignore();
            cin.getline(fam, 25);
            del(&L, fam);
            cout << "��� ����������� ������� ENTER.";
            system("PAUSE>nul");
            system("cls");
            print_menu();
            break;
        }
        case 3://���
        {
            //sort(&L);
            int choice;
            cout << "��� ������� ������ ?" << endl;
            cout << "����� ������ (1-����������/ 2-��������):";
            cin >> choice;
            if (choice == 1)
            {
                view(&L);
            }
            else
            {
                revview(&L);
            }
            cout << "��� ����������� ������� ENTER.";
            system("PAUSE>nul");
            system("cls");
            print_menu();
            break;
        }
        case 4://���������
        {
            find(&L);
            cout << "��� ����������� ������� ENTER.";
            system("PAUSE>nul");
            system("cls");
            print_menu();
            break;
        }
        case 5://����� � ����
        {
            file_output(&L);
            cout << "��� ����������� ������� ENTER.";
            system("PAUSE>nul");
            system("cls");
            print_menu();
            break;
        }
        case 6://���� �� �����
        {
            s = new STUDENT;
            ifstream fin("input.txt");
            if (fin) {
                while (!fin.eof()) {
                    fin.getline(s->fam, 25);
                    fin.getline(s->ini, 25);
                    fin.getline(s->group, 25);
                    fin.getline(s->grade, 25);
                    ins(&L, *s, s->fam);//���������� � ������
                }
            }
            else
            {
                cout << "�� ������� ������� ����" << endl;
            }
            cout << "��� ����������� ������� ENTER.";
            system("PAUSE>nul");
            system("cls");
            print_menu();
            break;
        }
        case 7://������
        {
            cout << "������� 3" << endl;
            cout << " 1.) ��������� ���������, ������� �������� ������� ���������� �� ������������ ���������." << endl;
            cout << " �������� � ��������� ��������:" << endl;
            cout << " � ������� � ��������" << endl;
            cout << " �	����� ������" << endl;
            cout << " �	������������ (������ �� ���� ���������" << endl;
            cout << " 2.)	��������� ������ ������������ :" << endl;
            cout << " � �������� �������� ��� ���� ��������� � ���� ����������� ������, ������ ������ ���� ����������� �� ��������;" << endl;
            cout << " �	���������� ������ � ����� ���������;" << endl;
            cout << " �	�������� ������ � ��������, ������� �������� ������� � ����������;" << endl;
            cout << " �	����� �������� ��� ���� ���������;" << endl;
            cout << " �	�� ������� ��������� �������� � ���������, ������� ����� ���� �� ���� ������." << endl;
            cout << " 3.)	��������� ������ ������������ ������ � ������� ����." << endl;
            cout << "��� ����������� ������� ENTER.";
            system("PAUSE>nul");
            system("cls");
            print_menu();
            break;
        }
        case 8://� ���������
        {
            cout << "��������� '���������� ������'" << endl;
            cout << "������" << endl;
            cout << "�����������: ������ ��������� ��������, ���� 2301-02-00" << endl;
            cout << "��� ����������� ������� ENTER.";
            system("PAUSE>nul");
            system("cls");
            print_menu();
            break;
        }
        case 0://�����
        {
            //delete(&L);
            return 0;
        }
        }
        cout << "-----------------------------------" << endl;
    }
}