#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

// Функции добавления элемента, просмотра списка
void spstore(void), review(void), del(void);

void priority(void); // Функция нахождения максимального значения приоритетной очереди

char find_el[256];
struct node* find(char* name); // функция нахождения элемента
struct node* get_struct(void); // функция создания элемента

struct node* head = NULL, * last = NULL, * f = NULL; // указатели на первый и последний элементы списка
int dlinna = 0;
int number = 1;
int prior;

struct node
{
	char surname[256];  // фамилия студента
	int scores; // баллы ЕГЭ
	int numb; // для приоритетной очереди
	struct node* next; // ссылка на следующий элемент 
};


struct node* get_struct(void)
{
	struct node* p = NULL;
	char s[256];

	if ((p = (node*)malloc(sizeof(struct node))) == NULL)  // выделяем память под новый элемент списка
	{
		printf("Ошибка при распределении памяти\n");
		exit(1);
	}

	printf("Введите фамилию студента: \n");   // вводим данные
	scanf("%s", &s);
	if (*s == 0)
	{
		printf("Запись не была произведена\n");
		return NULL;
	}
	strcpy(p->surname, s);
	printf("Введите сумму баллов:\n");
	scanf("%d", &p->scores);

	p->numb = number;
	printf("Номер записи: %d\n", p->numb);
	number += 1;

	p->next = NULL;

	return p;		// возвращаем указатель на созданный элемент
}

/* Последовательное добавление в список элемента (в конец)*/
void spstore(void)
{
	struct node* p = NULL;
	p = get_struct();
	if (head == NULL && p != NULL)	// если списка нет, то устанавливаем голову списка
	{
		head = p;
		last = p;
	}
	else if (head != NULL && p != NULL) // список уже есть, то вставляем в конец
	{
		last->next = p;
		last = p;
	}
	return;
}


/* Просмотр содержимого списка. */
void review(void)
{
	struct node* struc = head;
	if (head == NULL)
	{
		printf("Список пуст\n");
	}
	while (struc)
	{
		printf("Фамилия - %s, \n", struc->surname);
		printf("Сумма баллов - %d, \n", struc->scores);
		printf("Номер записи - %d, \n", struc->numb);
		struc = struc->next;
	}
	return;
}


/* Поиск элемента по содержимому. */
struct node* find(char* name)
{
	struct node* struc = head;
	if (head == NULL)
	{
		printf("Список пуст\n");
	}
	while (struc)
	{
		if (strcmp(name, struc->surname) == 0)
		{
			printf("Фамилия - %s, \n", struc->surname);
			printf("Сумма баллов - %d, \n", struc->scores);
			printf("Номер записи - %d, \n", struc->numb);
			return struc;
		}
		struc = struc->next;
	}
	printf("Элемент не найден\n");
	return NULL;
}

/* Удаление элемента по содержимому. */
void del(void)
{
	struct node* struc = head; // указатель, проходящий по списку установлен на начало списка
	struct node* prev = NULL;  // указатель на предшествующий удаляемому элемент
	int flag = 0;              // индикатор отсутствия удаляемого элемента в списке

	if (head == NULL) // если голова списка равна NULL, то список пуст
	{
		printf("Список пуст\n");
		return;
	}

	if (prior == struc->numb) // если удаляемый элемент - первый
	{
		flag = 1;
		head = struc->next; // установливаем голову на следующий элемент
		free(struc);  // удаляем первый элемент
		struc = head; // устанавливаем указатель для продолжения поиска
	}
	else
	{
		prev = struc; // инициализируем prev, так как struc уже указывает на первый элемент
		struc = struc->next;
	}

	while (struc) // проход по списку и поиск удаляемого элемента
	{
		if (prior == struc->numb) // если нашли, то
		{
			flag = 1;         // выставляем индикатор
			if (struc->next)  // если найденный элемент не последний в списке
			{
				prev->next = struc->next; // меняем указатели
				free(struc);           // удаляем элемент
				struc = prev->next;    // устанавливаем указатель для продолжения поиска
			}
			else // если найденный элемент последний в списке
			{
				prev->next = NULL; // обнуляем указатель предшествующего элемента
				free(struc);       // удаляем элемент
				last = prev;       // обновляем указатель last
				return;
			}
		}
		else // если не нашли, то
		{
			prev = struc; // устанавливаем указатели для продолжения поиска
			struc = struc->next;
		}
	}

	if (flag == 0) // если флаг = 0, значит нужный элемент не найден
	{
		printf("Элемент не найден\n");
		return;
	}
}	

/* Вычисление максимального приоритета */
void priority(void)
{
	struct node* struc = head; // указатель, проходящий по списку установлен на начало списка
	struct node* prev;// указатель на предшествующий удаляемому элемент
	prior = 0;

	while (struc) // проход по списку и поиск удаляемого элемента
	{
		if (struc->numb > prior)
			prior = struc->numb;
		prev = struc; // устанавливаем указатели для продолжения поиска
		struc = struc->next;
	}

}

int main()
{
	setlocale(LC_ALL, "rus");
	int menu = 0;
	char m[256];
	char* name;

	printf("Для добавления элемента нажмите:   1\n");
	printf("Для удаления элемента нажмите:     2\n");
	printf("Для поиска элемента нажмите:       3\n");
	printf("Для просмотра элемента нажмите:    4\n");
	printf("Для выхода нажмите:                5\n");

	while (menu != 5)
	{
		scanf("%d", &menu);

		switch (menu)
		{
		case 1:
			spstore();
			break;
		case 2:
			priority();
			del();
			break;
		case 3:
			printf("Введите фамилию студента для поиска данных: \n");
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
