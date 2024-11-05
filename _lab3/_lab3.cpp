#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

// Функции добавления элемента, просмотра списка
void spstore(void), review(void), del(void);
void priority(void); // Функция нахождения максимального значения 

char find_el[256];
void find(char* name); // функция нахождения элемента
struct node* get_struct(void); // функция создания элемента

struct node* head = NULL; // указатель на первый элемент

int prior = 0; // для приоритетной очеред

struct node {
    char surname[256];  // фамилия студента
    int scores; // баллы ЕГЭ
    int numb; // для приоритетной очеред
    struct node* next; // ссылка на следующий элемент 
};

struct node* get_struct(void) {
    struct node* p = NULL;
    char s[256];
    if ((p = (struct node*)malloc(sizeof(struct node))) == NULL) {
        printf("Ошибка при распределении памяти\n");
        exit(1);
    }
    printf("Введите фамилию студента: \n");   // вводим данные
    scanf("%s", &s);
    if (*s == 0) {
        printf("Запись не была произведена\n");
        return NULL;
    }
    strcpy(p->surname, s);
    printf("Введите сумму баллов:\n");
    scanf("%d", &p->scores);
    printf("Введите номер приоритета:\n");
    scanf("%d", &p->numb);
    printf("Номер записи: %d\n", p->numb);
    p->next = NULL;
    return p; // возвращаем указатель на созданный элемент
}

/* Добавление в список с учетом приоритета */
void spstore(void) {
    struct node* p = get_struct();
    if (p == NULL) {
        return; // Если не удалось создать элемент, выходим
    }

    if (head == NULL || head->numb < p->numb) { // Если список пуст или приоритет нового элемента выше
        p->next = head; // Добавляем новый элемент в начало
        head = p;
    }
    else {
        struct node* current = head;
        while (current->next != NULL && current->next->numb >= p->numb) {
            current = current->next; // Находим позицию для вставки
        }
        p->next = current->next; // Устанавливаем следующий элемент
        current->next = p; // Вставляем новый элемент
    }
}

/* Просмотр содержимого списка. */
void review(void) {
    struct node* struc = head;
    if (head == NULL) {
        printf("Список пуст\n\n\n");
    }
    else {
        while (struc) {
            printf("Фамилия - %s, \n", struc->surname);
            printf("Сумма баллов - %d, \n", struc->scores);
            printf("Номер записи - %d, \n\n\n", struc->numb);
            struc = struc->next;
        }
    }
}

/* Поиск элемента по содержимому. */
void find(char* name) {
    struct node* struc = head;
    int found = 0; // Индикатор, был ли найден хотя бы один элемент
    if (head == NULL) {
        printf("Список пуст\n");
        return;
    }

    while (struc) {
        if (strcmp(name, struc->surname) == 0) {
            printf("Фамилия - %s, \n", struc->surname);
            printf("Сумма баллов - %d, \n", struc->scores);
            printf("Номер записи - %d, \n\n\n", struc->numb);
            found = 1; // Устанавливаем индикатор, что нашли элемент
        }
        struc = struc->next;
    }

    if (!found) {
        printf("Элемент не найден\n\n");
    }
}

/* Удаление элемента по содержимому. */
/*void del(void) {
    struct node* struc = head; // указатель, проходящий по списку установлен 
    struct node* prev = NULL; // Инициализируем prev как NULL
    int flag = 0; // индикатор отсутствия удаляемого элемента в списке
    if (head == NULL) { // если голова списка равна NULL, то список пуст
        printf("Список пуст\n");
        return;
    }
    if (prior == struc->numb) { // если удаляемый элемент - первый
        flag = 1;
        head = struc->next; // устанавливаем голову на следующий элемент
        free(struc); // удаляем первый элемент
        struc = head; // устанавливаем указатель для продолжения поиска
    }
    else {
        prev = struc; // Устанавливаем prev на первый элемент
        struc = struc->next;
    }

    while (struc) { // проход по списку и поиск удаляемого элемента
        if (prior == struc->numb) { // если нашли, то
            flag = 1; // выставляем индикатор
            if (struc->next) { // если найденный элемент не последний в 
                prev->next = struc->next; // меняем указатели
                free(struc); // удаляем элемент
                struc = prev->next; // устанавливаем указатель для 
            }
            else { // если найденный элемент последний в 
                prev->next = NULL; // обнуляем указатель 
                free(struc); // удаляем элемент
                return;
            }
        }
        else { // если не нашли, то
            prev = struc; // устанавливаем указатели для продолжения 
            struc = struc->next;
        }
    }
    if (flag == 0) { // если флаг = 0, значит нужный 
        printf("Элемент не найден\n");
        return;
    }
}

/* Вычисление максимального приоритета */

/* Удаление элементов по фамилии. */
void del(char* surname) {
    struct node* struc = head; // указатель, проходящий по списку установлен 
    struct node* prev = NULL; // Инициализируем prev как NULL
    int flag = 0; // индикатор отсутствия удаляемого элемента в списке
    if (head == NULL) { // если голова списка равна NULL, то список пуст
        printf("Список пуст\n");
        return;
    }

    while (struc) { // проход по списку и поиск удаляемого элемента
        if (strcmp(surname, struc->surname) == 0) { // если фамилия совпадает
            flag = 1; // выставляем индикатор
            if (prev == NULL) { // если удаляемый элемент - первый
                head = struc->next; // устанавливаем голову на следующий элемент
                free(struc); // удаляем элемент
                struc = head; // устанавливаем указатель для продолжения поиска
            }
            else { // если не первый
                prev->next = struc->next; // меняем указатели
                free(struc); // удаляем элемент
                struc = prev->next; // устанавливаем указатель для продолжения поиска
            }
        }
        else { // если не нашли, то
            prev = struc; // устанавливаем указатели для продолжения 
            struc = struc->next;
        }
    }

    if (flag == 0) { // если флаг = 0, значит нужный элемент не найден
        printf("Элемент с фамилией '%s' не найден\n", surname);
    }
}

void priority() {
    struct node* struc = head; // указатель, проходящий по списку установлен 
    prior = 0;
    while (struc) { // проход по списку и поиск удаляемого элемента
        if (struc->numb > prior)
            prior = struc->numb;
        struc = struc->next; // устанавливаем указатель для продолжения поиска
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    int menu = 0;
    char m[256];
    char* name;
    printf("Определить максимальный приоритет: 0\n");
    printf("Для добавления элемента нажмите:   1\n");
    printf("Для удаления элемента нажмите:     2\n");
    printf("Для поиска элемента нажмите:       3\n");
    printf("Для просмотра элемента нажмите:    4\n");
    printf("Для выхода нажмите:                5\n\n");
    while (menu != 5) {
        scanf("%d", &menu);
        switch (menu) {
        case 0:
            priority();
            printf("Максимальный приоритет: %d\n\n", prior);
            break;
        case 1:
            spstore();
            break;
        case 2:    
            printf("Введите фамилию студента для удаления: \n");    
            scanf("%s", m);    
            del(m);    
            break;
        case 3:
            printf("Введите фамилию студента для поиска данных: \n\n");
            scanf("%s", m);
            name = m;
            find(name);
            break;
        case 4:
            review();
            break;
        }
    }
    return 0;
}