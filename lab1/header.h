#pragma once

struct goods                                                                // стркуктура товара
{
	char* name;
	float price;
	int min;
	int max;
};

void input(int amount, goods *s);                                            // заполнение полей структуры
float high_price(int amount, goods* ptr);                                    // поиск максимальной цены
int input_num();                                                             // ввод количества товаров
float input_price();                                                         // ввод ориентировочной цены
void output(int* names_ind, int end_size, float highest_price, goods* ptr);  // вывод результата
int* under_price(int amount, goods* ptr, float border_price, int* end_size); // поиск товаров ниже ориентировочной цены
goods* create_ptr(int amount);                                               // создание массива указателей
void free_mem(int* names_ind, goods* ptr);                                   // очистка памяти