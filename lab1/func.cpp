#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include <string.h>
#define MAX 15
#define AGE 5
#define NAME "constructor"


void input(int amount, goods* s)                                                             // функция для заполнения полей структуры
{
	printf("Введите сведения о %d товарах: \n", amount);
	for (int i = 0; i < amount; i++)
	{
		printf("\nВведите сведения о %d товаре: \n", i+1);
		printf("Введите название товара - ");
		s[i].name = (char*)calloc(MAX + 1, sizeof(char));                                     // выделение памяти для поля с названием

		scanf_s("%s", s[i].name, MAX+1);

		printf("Введите цену товара - ");                                                     // заполнение поля с ценой
		while (scanf_s("%f", &s[i].price) != 1 || s[i].price <= 0)
		{
			printf("Ошибка - цена должна быть положительным числом.\nВведите цену товара - ");
			rewind(stdin);
		}

		printf("Введите возраст от - ");													   // заполнение поля с минимальным возрастом
		while (scanf_s("%d", &s[i].min) != 1 || s[i].min < 0)
		{
			printf("Ошибка - возраст не может быть отрицательным.\nВведите возраст от - ");
			rewind(stdin);
		}

		printf("Введите возраст до - ");                                                        // заполнение поля с максимальным возрастом
		while (scanf_s("%d", &s[i].max) != 1 || s[i].max <= s[i].min)
		{
			printf("Ошибка - возраст 'до' должен быть больше возраста 'от'.\nВведите возраст до - ");
			rewind(stdin);
		}

	}
}

float high_price(int amount, goods* ptr)                                                   // функция для нахождения конструктора с максимальной ценой
{
	float highest = 0;                                                                     // начальное значение для максимальной цены
	for (int i = 0; i < amount; i++)
	{
		if (strcmp(ptr[i].name, NAME) == 0)                                                // является ли товар конструктором 
		{
			if (highest == 0 || ptr[i].price > highest)                                    
			{
				highest = ptr[i].price;                                                    
			}
		}
		
	}
	return highest;                                                                         // вернуть значение максимальной цены
}

int input_num()                                                                             // функция для ввода количества товаров
{
	int num;
	printf("Введите количество товаров - ");
	while (scanf_s("%d", &num) != 1 || num <= 0)                                            // проверка корректности ввода
	{
		printf("Ошибка - введите положительное целое число: ");
		rewind(stdin);
	}
	return num;                                                                             // вернуть введенное число
}

float input_price()                                                                         // функция для ввода ориетировочной цены 
{
	float price;
	printf("Введите цену для ориентира - ");

	while (scanf_s("%f", &price) != 1 || price<=0)                                          // проверка корректности ввода
	{
		printf("Ошибка - некорректный ввод. \nВведите целое число - ");
		rewind(stdin);
	}

	rewind(stdin);
	return price;                                                                           // вернуть введенное число
}
	
	
int* under_price(int amount, goods* ptr, float border_price, int* end_size)            // функция для поиска товаров, которые дешевле ориетировочной цены
{
	int* names_ind = (int*)malloc(amount * sizeof(int));                               // выделение памяти для массива индексов названий
	if (names_ind == NULL)
	{
		exit(1);
	}

	*end_size = 0;                                                                     // начальное значение количества подходящих товаров

	for (int i = 0; i < amount; i++)
	{
		if (ptr[i].price <= border_price && ptr[i].min < AGE && AGE < ptr[i].max)       // условие для отбора товаров
		{
			names_ind[*end_size] = i; 
			(*end_size)++;
		
		}
	}
	if (*end_size > 0)                                                                  // если есть такие товары 
	{
		int* temp = (int*)realloc(names_ind, *end_size * sizeof(int));                  // сокращение лишней памяти
		if (temp != NULL) 
		{
			names_ind = temp;  
		}
	}
	else
	{
		free(names_ind);                                                                // очистка выделенной памяти
		names_ind = NULL;
	}
	
	return names_ind;
}

void output(int* names_ind, int end_size, float highest_price, goods* ptr)                         // функция для вывода результатов
{
	int choice = 0;
	printf("\nКакие сведения хотите получить?");
	printf("\n1. Названия товаров, у которых цена не превышает заданную, и подходят детям 5 лет.");
	printf("\n2. Цену самого дорогого конструктора.");
	printf("\nВведите номер пункта - ");                                                                     
	while (scanf_s("%d", &choice) != 1 || choice < 1 || choice > 2)                                 // выбор пользователя для вывода
	{
		printf("Ошибка - некорректный ввод. \nВведите число 1 или 2: ");
		rewind(stdin);
	}
	if(choice == 1)                                                            
	{
		if (end_size == 0)                                                                          // проверка количества товаров
		{
			printf("\nНет товаров, подходящих по цене и возрасту!\n");
		}
		else
		{
			printf("\nТовары для детей %d лет с ценой меньше заданной:\n", AGE);                   // вывод названий подходящих товаров
			for (int i = 0; i < end_size; i++)
			{
				printf("\nТовар номер %d - '%s'", i + 1, ptr[names_ind[i]].name);
			}
		}
	}
	else if (choice == 2)
	{
		if (highest_price == 0)                                                                    // проверка максимальной цены
		{
			printf("\nКонструктора нет в списке");
		}
		else
		{
			printf("\nЦена самого дорогого конструктора - %.2f", highest_price);                  // вывод цены самого дорогого конструктора
		}
	}
	
}
goods* create_ptr(int amount)                                                                     // функция создания массива структур
{
	goods* ptr = (goods*)malloc(amount * sizeof(goods));                                          // выделение памяти под массив структур
	if (ptr == NULL)                                                                              // проверка выделения памяти
	{
		exit(1);
	}
	return ptr;
}

void free_mem(int * names_ind, goods* ptr)                                                         // функция для очистки памяти
{
	free(names_ind);
	free(ptr);
}