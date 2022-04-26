#include<stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>

/* Даны два списка строк. Сформировать третий список так,
 * что каждый его элемент является строкой максимальной длины
 * среди соответствующих элементов первых двух списков, причем
 * если длины строк равны, то в результирующий список элемент не
 * добавляется. Если длина списков различна, то недостающие строки заменять пустой строкой. */

using namespace std;

struct node {
    string data;
    node *next;
};

string random_string() {
    char char_array[13];
    char symbols[17] = "abcdefghigklmnop";
    for (int i = 0; i < (rand() % 10) + 3; ++i) {
        char_array[i] = symbols[rand() % 17];
    }

    string new_string = char_array;
    return new_string;
}

void add_to_list(node **head, const string &data) {
    node *ptr = (node *) malloc(sizeof(node));
    ptr->data = data;

    if (*head == nullptr) {
        *head = ptr;
        ptr->next = nullptr;
    } else {
        node *temp = *head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = ptr;
        ptr->next = nullptr;
    }
}

void print_list(node *head) {
    while (head) {
        printf("[%s]->", head->data.c_str());
        head = head->next;
    }
    printf("[-]\n\n");
}


int list_input(node **head) {
    string data = " ";
    int i = 0;
    bool finish = false;
    while (!finish) {
        fflush(stdin);
        getline(cin, data);
        if (*data.c_str() != '\0') {
            add_to_list(head, data);
            i++;
        } else finish = true;
    }

    if (i == 0) {
        return 0;
    }
    return i;
}

void result_list(node *first_head, node *second_head, node **result_head, const int count) {
    for (int i = 0; i < count; i++) {
        int first_count, second_count;
        if (first_head && second_head) {
            first_count = strlen(first_head->data.c_str());
            second_count = strlen(second_head->data.c_str());
            if (first_count > second_count) {
                add_to_list(result_head, first_head->data.c_str());
            } else if (first_count == second_count) {
                continue;
            } else {
                add_to_list(result_head, second_head->data.c_str());
            }

            first_head = first_head->next;
            second_head = second_head->next;
        } else {
            if (first_head) first_head = first_head->next;
            if (second_head) second_head = second_head->next;
            add_to_list(result_head, "");
        }
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    bool exit = false;

    while (!exit) {
        char choose;
        bool right_choose = false;

        printf("Меню:\n1 - Ввести списки строк\n2 - Создать случайные списки строк\n3 - Выход\n");


        while (!right_choose) {
            fflush(stdin);
            scanf("%c", &choose);
            if (isdigit(choose)) {
                int digit = atoi(&choose);
                if (digit > 3) {
                    printf("Введите число, которое есть в меню!\n");
                } else {
                    right_choose = true;
                }
            } else {
                printf("Введите число!\n");
            }
        }


        switch (choose) {
            case '1': {
                node *first_head = nullptr;
                int first_count, second_count, third_count;
                printf("Введите первый список строк через enter, чтобы закончить ввод, нажмите enter два раза: \n");
                first_count = list_input(&first_head);
                if (first_count) {
                    printf("Первый список: \n");
                    printf("Количество элементов = %d\n", first_count);
                    print_list(first_head);

                    node *second_head = nullptr;
                    printf("Введите второй список строк через enter, чтобы закончить ввод, нажмите enter два раза: \n");
                    second_count = list_input(&second_head);
                    if (second_count) {
                        printf("Второй список: \n");
                        printf("Количество элементов = %d\n", second_count);
                        print_list(second_head);

                        if (first_count > second_count) { third_count = first_count; } else third_count = second_count;
                        node *third_head = nullptr;
                        result_list(first_head, second_head, &third_head, third_count);
                        printf("Сформированный список: \n");
                        print_list(third_head);
                    } else printf("Список пуст!\n\n");
                } else printf("Список пуст!\n\n");

            }
                break;
            case '2': {
                int first_count = rand() % 10, second_count = rand() % 10, third_count;
                node *first_head = nullptr, *second_head = nullptr, *third_head = nullptr;
                for (int i = 0; i < first_count; ++i) {
                    string data = random_string();
                    add_to_list(&first_head, data);
                }
                printf("Первый список: \n");
                print_list(first_head);
                for (int i = 0; i < second_count; ++i) {
                    string data = random_string();
                    add_to_list(&second_head, data);
                }
                printf("Второй список: \n");
                print_list(second_head);

                if (first_count > second_count) { third_count = first_count; } else third_count = second_count;
                result_list(first_head, second_head, &third_head, third_count);
                printf("Сформированный список: \n");
                print_list(third_head);

                break;
            }
            case '3':
                printf("***Программа завершена***");
                exit = true;
                break;
            default:
                break;
        }
    }
}