#include <stdio.h>                                           
#include <stdlib.h>
#define MAX 15                                                   // максимальное кол-во символов в названии
#include "header.h"
#include <locale.h>


int main()
{

	int amount, end_size, *names_ind;                             
	float highest_price, border_price;
	goods* ptr;                                                    // массив структур
	char choice;

	setlocale(LC_ALL, "Russian");
	
	do
	{

	amount = input_num();                                          // ввод количества товаров

	ptr = create_ptr(amount);                                      // создание массива структур

	border_price = input_price();                                  // ввод ориентировочной цены

	input(amount, ptr);                                            // ввод данных о товарах

	highest_price = high_price(amount, ptr);                       // поиск максимальной цены

	names_ind = under_price(amount, ptr, border_price, &end_size); // поиск товаров дешевле ориентировочной цены
	output(names_ind, end_size, highest_price, ptr);               // вывод результатов

	free_mem(names_ind, ptr);                                      // освобожление выделенной памяти
	printf("\n\nХотите продолжить? (y/Y): ");                      // вывод предложения о продолжении программы

	while (getchar() != '\n');
	scanf_s("%c", &choice, 1);                                      // сканирование выбора пользователя

	} while (choice == 'y' || choice == 'Y');                       // условие для продолжения
	return 0;
}