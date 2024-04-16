// lab_trees.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct tree_s {

    int is_val_stated[2];
    int val_1;
    int val_2;
    struct tree_s* branch[3];

};
typedef struct tree_s* Tree;

char* smart_gets() {
    int n = 2;
    char* meow = (char*)malloc(2 * sizeof(char));
    meow[0] = '\0';
    char buffer[2];
    buffer[1] = '\0';
    buffer[0] = getchar();
    while (buffer[0] != '\n') {

        strcat(meow, buffer);
        meow = realloc(meow, sizeof(char) * (n + 1));
        n += 1;
        buffer[0] = getchar();

    }
    return meow;
}

int* parse_int(char* k, int* length) {
    int* m = (int*)malloc(sizeof(int));
    int g = 0;
    int is_number = 0;
    int s = 0;
    int flag_negative = 0;
    for (int i = 0; i <= strlen(k); i++) {

        if (k[i] >= '0' && k[i] <= '9') {

            if (!is_number) {
                if (i > 0) {
                    if (k[i - 1] == '-') flag_negative = 1;
                }
                is_number = 1;
                g = k[i] - '0';
                if (flag_negative) g *= (-1);
            }
            else {
                g *= 10;
                if (flag_negative) {
                    g -= k[i] - '0';
                }
                else {
                    g += k[i] - '0';
                }
            }
        }
        else {
            if (is_number) {
                is_number = 0;
                flag_negative = 0;

                m = (int*)realloc(m, sizeof(int) * (s + 1));
                m[s] = g;
                s++;
                g = 0;
            }
        }
    }
    *length = s;
    return m;
}

enum {
    NotStated = 10000001
};

int t_getMax(Tree tree) {
    if (tree->branch[2] != NULL) {
        t_getMax(tree->branch[2]);
    }
    else {
        if (tree->is_val_stated[1] == 1) return tree->val_2;
        if (tree->is_val_stated[0] == 1) return tree->val_1;
        else return 10000001;
    }
}
int t_getMin(Tree tree) {
    if (tree->branch[0] != NULL) {
        return t_getMin(tree->branch[0]);
    }
    else {
        if (tree->is_val_stated[0]) return tree->val_1;
        if (tree->is_val_stated[1]) return tree->val_2;
        else return 10000001;
    }
}

int t_height(Tree tree, int height) {
    int h1 = -1;
    int h2 = -1;
    int h3 = -1;
    if (!(tree->branch[0] == NULL && tree->branch[1] == NULL && tree->branch[2] == NULL)) {
        if (tree->branch[0] != NULL) {
            h1 = t_height(tree->branch[0], height + 1);
        }
        if (tree->branch[1] != NULL) {
            h2 = t_height(tree->branch[1], height + 1);
        }
        if (tree->branch[2] != NULL) {
            h3 = t_height(tree->branch[2], height + 1);
        }
        if (h3 >= h2 && h3 >= h1) return h3;
        else if (h2 >= h3 && h2 >= h1) return h2;
        else if (h1 >= h3 && h1 >= h2) return h1;
    }
    else {
        return height;
    }
}

void t_sub_print(Tree tree, int height, int this_height, int block_size, int new_string) {


    int iterations = 3 * (this_height + 1);

    for (int i = 1; i <= iterations; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < block_size; j++) printf(".");
        }
        else {
            printf(".");
        }
    }
    if (tree != NULL) {
        int treeval_size = 0;
        int treeval = tree->is_val_stated[0] ? tree->val_1 : 1;
        while (treeval > 0) {
            treeval /= 10;
            treeval_size++;
        }
        if (tree->is_val_stated[0]) printf("[%d ", tree->val_1);
        else printf("[*");
        int spaces_from_center = block_size / 2 - treeval_size - 1;
        for (int i = 0; i < spaces_from_center; i++) printf(" ");
        treeval_size = 0;
        treeval = tree->is_val_stated[1] ? tree->val_2 : 1;
        while (treeval > 0) {
            treeval /= 10;
            treeval_size++;
        }
        spaces_from_center = block_size / 2 - treeval_size - 1;
        for (int i = 0; i < spaces_from_center; i++) printf(" ");
        if (tree->is_val_stated[1]) printf("%d]", tree->val_2);
        else printf("*]");

    }
    else {
        for (int j = 0; j < block_size; j++) printf("|");
    }
    if (this_height != 0) {
        t_sub_print(tree == NULL ? tree : tree->branch[0], height, this_height - 1, block_size, 0);
        t_sub_print(tree == NULL ? tree : tree->branch[1], height, this_height - 1, block_size, 0);
        t_sub_print(tree == NULL ? tree : tree->branch[2], height, this_height - 1, block_size, 0);
        printf("\n");
    }
}



void t_level_to_string(Tree tree, int this_height, int block_size, char* str, int target_height, int* blocks_counter) {


    if (this_height == target_height) {
        if (tree != NULL) {
            int treeval_size = 0;
            int treeval = tree->is_val_stated[0] ? tree->val_1 : 1;
            if (treeval < 0) treeval_size++;
            while (treeval != 0) {
                treeval /= 10;
                treeval_size++;
            }
            char* buf = (char*)malloc(sizeof(char) * block_size);
            (*blocks_counter)++;
            if (*blocks_counter == 1) strcat(str, " | ");
            if (tree->is_val_stated[0]) { strcat(str, "["); strcat(str, _itoa(tree->val_1, buf, 10)); }
            else strcat(str, "[*");
            int spaces_from_center = block_size / 2 - treeval_size;
            for (int i = 0; i < spaces_from_center; i++) strcat(str, " ");
            treeval_size = 0;
            treeval = tree->is_val_stated[1] ? tree->val_2 : 1;
            if (treeval < 0) treeval_size++;
            while (treeval != 0) {
                treeval /= 10;
                treeval_size++;
            }
            spaces_from_center = block_size / 2 - treeval_size - 1;
            for (int i = 0; i < spaces_from_center; i++) strcat(str, " ");
            if (tree->is_val_stated[1]) { strcat(str, _itoa(tree->val_2, buf, 10)); strcat(str, "]"); }
            else strcat(str, "*]");
            if (*blocks_counter == 3) { strcat(str, " | "); *blocks_counter = 0; }
            free(buf);
        }
        else {
            int iterations = pow(3, this_height);
            (*blocks_counter)++;
            if (*blocks_counter == 1) strcat(str, " | ");
            for (int j = 0; j < block_size; j++) strcat(str, " ");
            if (*blocks_counter == 3) { strcat(str, " | "); *blocks_counter = 0; }
        }
    }
    if (this_height >= target_height) {
        t_level_to_string(tree == NULL ? tree : tree->branch[0], this_height - 1, block_size, str, target_height, blocks_counter);
        t_level_to_string(tree == NULL ? tree : tree->branch[1], this_height - 1, block_size, str, target_height, blocks_counter);
        t_level_to_string(tree == NULL ? tree : tree->branch[2], this_height - 1, block_size, str, target_height, blocks_counter);
    }
}


void t_print(Tree tree) {

    int height = t_height(tree, 0);
    int max_n = t_getMax(tree);
    int min_n = t_getMin(tree);
    int number_length = max_n < 0 ? 1 : 0;
    while (max_n != 0) {
        max_n /= 10;
        number_length++;
    }
    if (min_n < 0) {
        int number_length_min = 1;
        while (min_n != 0) {
            min_n /= 10;
            number_length_min++;
        }
        if (number_length_min > number_length) number_length = number_length_min;
    }
    int block_size = number_length * 2 + 3; //длина макс. числа + пробел + две скобки
    char str[10000];
    for (int i = height; i >= 0; i--) {
        str[0] = '\0';
        int s = 0;
        int* blocks_counter;
        blocks_counter = &s;
        t_level_to_string(tree, height, block_size, str, i, blocks_counter);
        printf("\nHeight %d: ", i);
        int counter_of_spliters = 0;
        for (int i = 0; i < strlen(str); i++) {
            printf("%c", str[i]);
            if (str[i] == '|') counter_of_spliters++;
            if (counter_of_spliters == 6) { printf("\n         "); counter_of_spliters = 0; }
        }
        //printf("Height %d: %s\n", i, str);
    }
}


Tree t_init() {
    Tree tree = (Tree)malloc(sizeof(struct tree_s));
    tree->branch[0] = NULL;
    tree->branch[1] = NULL;
    tree->branch[2] = NULL;
    tree->is_val_stated[0] = 0;
    tree->is_val_stated[1] = 0;
    return tree;
}

int t_insert(Tree tree, int val) {
    if (!((tree->is_val_stated[0] && tree->val_1 == val) || (tree->is_val_stated[1] && tree->val_2 == val))) {

        if (!(tree->is_val_stated[0])) {
            tree->val_1 = val;
            tree->is_val_stated[0] = 1;
            if ((tree->is_val_stated[1]) && (tree->val_1 > tree->val_2)) {
                int temp = tree->val_1;
                tree->val_1 = tree->val_2;
                tree->val_2 = temp;
            }
            return 1;
        }

        if (!(tree->is_val_stated[1])) {
            tree->val_2 = val;
            tree->is_val_stated[1] = 1;
            if ((tree->is_val_stated[0]) && (tree->val_1 > tree->val_2)) {
                int temp = tree->val_1;
                tree->val_1 = tree->val_2;
                tree->val_2 = temp;
            }
            return 1;
        }

        if (val > tree->val_2) {
            if (tree->branch[2] == NULL)
                tree->branch[2] = t_init();

            t_insert(tree->branch[2], val);
        }
        else
            if (val < tree->val_1) {
                if (tree->branch[0] == NULL)
                    tree->branch[0] = t_init(val);

                t_insert(tree->branch[0], val);

            }
            else {
                if (tree->branch[1] == NULL)
                    tree->branch[1] = t_init(val);

                t_insert(tree->branch[1], val);

            }
    }
    else {
        return 0;
    }
}



int main()
{
    Tree tree = t_init();
    system("chcp 1251");
    while (1) {
        char* buffer;
        int inpt_size;
        int* user_input;
        system("cls");
        char itoa_buf[100];
        char itoa_buf1[100];
        printf(" Управление деревом:\n 1) Внести значение\n 2) Вывести дерево\n =====================\n      Сводка:\n  Высота: %d\n  Максимальное значение: %s\n  Минимальное значение: %s\n =====================\n Введите пункт меню: ", t_height(tree, 0), (t_getMax(tree) == NotStated ? "отсутствует" : _itoa(t_getMax(tree), itoa_buf, 10)), (t_getMin(tree) == NotStated ? "отсутствует" : _itoa(t_getMin(tree), itoa_buf1, 10)));
        while (1) {
            buffer = smart_gets();
            user_input = parse_int(buffer, &inpt_size);
            if (inpt_size != 1 || user_input[0] > 3 || user_input[0] < 1)
                printf("\n\n     [X] Неверный ввод. Попробуйте снова!\n Введите пункт меню: ");
            else
                break;
        }
        switch (*user_input) {
        case 1:
            while (1) {
                printf("\n\n Введите значение: ");
                buffer = smart_gets();
                inpt_size;
                user_input = parse_int(buffer, &inpt_size);
                if (inpt_size != 1 || *user_input > 10000000 || *user_input < -10000000) {
                    printf("\n\n     [X] Неверный ввод!");
                }
                else {
                    t_insert(tree, *user_input) ? printf("\n\n     [V] Значение внесено") : printf("\n\n     [X] Значение уже существует!");
                }
                break;
            }
        case 2:
            system("cls");
            t_print(tree);
            break;
        }
        _getch();
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
