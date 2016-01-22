// LevMishkin.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <locale>
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

struct element
{
	int a;                                         //коэффициент
	unsigned int n;                                //степень
	element *prev;                                 //ссылка на предыдущий элемент
	element *next;                                 //ссылка на следующий элемент
};

class polinom
{
private:
	element *head;                                  //указатель на начало списка
	element *tail;                                  //указатель на конец списка

public:
	polinom();                                      //конструктор
	polinom(polinom & A1);                          //конструктор копирования
	~polinom();                                     //деструктор
	element* find(unsigned int);                    //поиск
	int add(int, unsigned int);                     //добавление члена полинома
	int del(unsigned int);                          //удаление члена полинома
	void print();                                   //печать полинома на экране
	long long int znach(short int);                 //значение полинома в точке
	polinom operator = (polinom);                   //оператор присваивания полиномов
	polinom operator + (polinom);                   //оператор сложения полиномов
	polinom operator - (polinom);                   //оператор разности полиномов
};

//констуктор
polinom::polinom()
{
	head = NULL;
	tail = NULL;
}

//конструктор копирования
polinom::polinom(polinom & A1)
{
	head = NULL;
	tail = NULL;
	if (A1.head != NULL)
	{
		element *cur1 = A1.head;
		element *newelem = new element;
		newelem->a = cur1->a;
		newelem->n = cur1->n;
		newelem->next = NULL;
		newelem->prev = NULL;
		head = newelem;
		tail = newelem;
		cur1 = cur1->next;
		while (cur1 != NULL)
		{
			element *newelem = new element;
			newelem->a = cur1->a;
			newelem->n = cur1->n;
			newelem->prev = tail;
			newelem->next = NULL;
			tail->next = newelem;
			tail = newelem;
			cur1 = cur1->next;
		};
	};
}

//деструктор
polinom:: ~polinom()
{
	while (head != NULL)
	{
		tail = head->next;
		delete head;
		head = tail;
	};
}

//поиск: возвращает ссылку на найденный элемент или NULL
element* polinom::find(unsigned int N)
{
	element *cur = head;
	if (cur != NULL)
	{
		while ((cur != tail) && (cur->n != N))
			cur = cur->next;
		if ((cur == NULL) || ((cur == tail) && (cur->n != N)))
		{
			cur = NULL;
		}
		else
		{
			//	cout << cur->a << "x^" << cur->n << '\n';
		};
	}
	return cur;
}

//добавление: 1 - если добавлен новый элемент; 
//0 - если заменен коэффициент; -1 - если элемент не добавлен.
int polinom::add(int A, unsigned int N)
{
	int result;
	if (A != 0)
	{
		element *cur = find(N);
		if (cur != NULL)
		{
			cur->a = A;
			result = 0;
		}
		else
		{
			if (head == NULL)
			{
				element *newelem = new element;
				newelem->a = A;
				newelem->n = N;
				newelem->next = NULL;
				newelem->prev = NULL;
				head = newelem;
				tail = newelem;
				result = 1;
			}
			else
			{
				if (N > head->n)
				{
					element *newelem = new element;
					newelem->a = A;
					newelem->n = N;
					newelem->next = head;
					newelem->prev = NULL;
					head->prev = newelem;
					head = newelem;
					result = 1;
				}
				else
				{
					if (N < tail->n)
					{
						element *newelem = new element;
						newelem->a = A;
						newelem->n = N;
						newelem->next = NULL;
						newelem->prev = tail;
						tail->next = newelem;
						tail = newelem;
						result = 1;
					}
					else
					{
						cur = head;
						while (cur->n > N)
							cur = cur->next;
						element *newelem = new element;
						newelem->a = A;
						newelem->n = N;
						element *cur1 = cur->prev;
						newelem->next = cur;
						newelem->prev = cur1;
						cur->prev = newelem;
						cur1->next = newelem;
						result = 1;
					};
				};
			};
		};
	}
	else
		result = -1;
	return result;
}

//1 - если удален эелемент; 0 - если эелемента нет в полиноме.
int polinom::del(unsigned int N)
{
	int result;
	element *cur = find(N);
	if (cur != NULL)
	{
		if (cur == head)
		{
			cur = cur->next;
			delete head;
			head = cur;
			result = 1;
		}
		else
		{
			if (cur == tail)
			{
				cur = cur->prev;
				cur->next = NULL;
				delete tail;
				tail = cur;
				result = 1;
			}
			else
			{
				cur->prev->next = cur->next;
				cur->next->prev = cur->prev;
				delete cur;
				result = 1;
			};
		};
	}
	else
		result = 0;
	return result;
}

//вывод поилнома на экран
void polinom::print()
{
	if (head != NULL)
	{
		cout << "f(x) = ";
		element *cur = head;
		while (cur != tail)
		{
			cout << cur->a;
			if (cur->n != 0)
				cout << "x^" << cur->n;
			if (cur->next->a > 0)
				cout << "+";
			cur = cur->next;
		}
		cout << cur->a;
		if (cur->n != 0)
			cout << "x^" << cur->n;
		cout << '\n';
	}
	else
	{
		cout << "f(x) = 0" << '\n';
	};
}

long long int polinom::znach(short int x)
{
	long long int result = 0;
	if (head != NULL)
	{
		long long int st;
		unsigned int N;
		int A;
		element *cur = head;
		while (cur != NULL)
		{
			st = 1;
			N = cur->n;
			A = cur->a;
			while (N > 0)
			{
				st = st * x;
				N--;
			};
			result = result + (A * st);
			cur = cur->next;
		};
	};
	return result;
}

polinom polinom:: operator = (polinom A1)
{
	element *cur = head;
	element *cur1 = A1.head;
	polinom P;
	while ((cur != NULL) && (cur1 != NULL))
	{
		cur->a = cur1->a;
		cur->n = cur1->n;
		cur = cur->next;
		cur1 = cur1->next;
	};
	while ((cur == NULL) && (cur1 != NULL))
	{
		if (head == NULL)
		{
			element *newelem = new element;
			newelem->a = cur1->a;
			newelem->n = cur1->n;
			newelem->next = NULL;
			newelem->prev = NULL;
			head = newelem;
			tail = newelem;
			cur1 = cur1->next;
		}
		else
		{
			element *newelem = new element;
			newelem->a = cur1->a;
			newelem->n = cur1->n;
			newelem->next = NULL;
			newelem->prev = tail;
			tail->next = newelem;
			tail = newelem;
			cur1 = cur1->next;
		};
	};
	while ((cur != NULL) && (cur1 == NULL))
	{
		if (cur != head)
		{
			cur = cur->prev;
			element *cur2 = tail;
			while (cur != tail)
			{
				cur2 = tail->prev;
				delete tail;
				tail = cur2;
				tail->next = NULL;
			};
			cur = NULL;
		}
		else
		{
			while (head != NULL)
			{
				tail = head->next;
				delete head;
				head = tail;
			};
			head = NULL;
			tail = NULL;
			cur = NULL;
		};
	};
	cur = head;
	if (cur != NULL)
	{
		element *newelem = new element;
		newelem->a = cur->a;
		newelem->n = cur->n;
		newelem->prev = NULL;
		newelem->next = NULL;
		P.head = newelem;
		P.tail = newelem;
		cur = cur->next;
		while (cur != NULL)
		{
			element *newelem = new element;
			newelem->a = cur->a;
			newelem->n = cur->n;
			newelem->next = NULL;
			newelem->prev = P.tail;
			P.tail->next = newelem;
			P.tail = newelem;
			cur = cur->next;
		};
	}
	return P;
}

polinom polinom:: operator + (polinom A1)
{
	polinom P;
	element *cur = head;
	element *cur1 = A1.head;
	while ((cur != NULL) && (cur1 != NULL))
	{
		element *newelem = new element;
		newelem->next = NULL;
		if (cur->n == cur1->n)
		{
			newelem->a = cur->a + cur1->a;
			newelem->n = cur->n;
			cur = cur->next;
			cur1 = cur1->next;
		}
		else
		{
			if (cur->n > cur1->n)
			{
				newelem->a = cur->a;
				newelem->n = cur->n;
				cur = cur->next;
			}
			else
			{
				newelem->a = cur1->a;
				newelem->n = cur1->n;
				cur1 = cur1->next;
			};
		};
		if (newelem->a != 0)
		{
			if (P.head == NULL)
			{
				newelem->prev = NULL;
				P.head = newelem;
				P.tail = newelem;
			}
			else
			{
				newelem->prev = P.tail;
				P.tail->next = newelem;
				P.tail = newelem;
			};
		};
	};
	while ((cur != NULL) && (cur1 == NULL))
	{
		element *newelem = new element;
		newelem->next = NULL;
		newelem->a = cur->a;
		newelem->n = cur->n;
		cur = cur->next;
		if (P.head == NULL)
		{
			newelem->prev = NULL;
			P.head = newelem;
			P.tail = newelem;
		}
		else
		{
			newelem->prev = P.tail;
			P.tail->next = newelem;
			P.tail = newelem;
		};
	};
	while ((cur == NULL) && (cur1 != NULL))
	{
		element *newelem = new element;
		newelem->next = NULL;
		newelem->a = cur1->a;
		newelem->n = cur1->n;
		cur1 = cur1->next;
		if (P.head == NULL)
		{
			newelem->prev = NULL;
			P.head = newelem;
			P.tail = newelem;
		}
		else
		{
			newelem->prev = P.tail;
			P.tail->next = newelem;
			P.tail = newelem;
		};
	};
	return P;
}

polinom polinom:: operator - (polinom A1)
{
	polinom P;
	element *cur = head;
	element *cur1 = A1.head;
	while ((cur != NULL) && (cur1 != NULL))
	{
		element *newelem = new element;
		newelem->next = NULL;
		if (cur->n == cur1->n)
		{
			newelem->a = cur->a - cur1->a;
			newelem->n = cur->n;
			cur = cur->next;
			cur1 = cur1->next;
		}
		else
		{
			if (cur->n > cur1->n)
			{
				newelem->a = cur->a;
				newelem->n = cur->n;
				cur = cur->next;
			}
			else
			{
				newelem->a = -(cur1->a);
				newelem->n = cur1->n;
				cur1 = cur1->next;
			};
		};
		if (newelem->a != 0)
		{
			if (P.head == NULL)
			{
				newelem->prev = NULL;
				P.head = newelem;
				P.tail = newelem;
			}
			else
			{
				newelem->prev = P.tail;
				P.tail->next = newelem;
				P.tail = newelem;
			};
		};
	};
	while ((cur != NULL) && (cur1 == NULL))
	{
		element *newelem = new element;
		newelem->next = NULL;
		newelem->a = cur->a;
		newelem->n = cur->n;
		cur = cur->next;
		if (P.head == NULL)
		{
			newelem->prev = NULL;
			P.head = newelem;
			P.tail = newelem;
		}
		else
		{
			newelem->prev = P.tail;
			P.tail->next = newelem;
			P.tail = newelem;
		};
	};
	while ((cur == NULL) && (cur1 != NULL))
	{
		element *newelem = new element;
		newelem->next = NULL;
		newelem->a = -(cur1->a);
		newelem->n = cur1->n;
		cur1 = cur1->next;
		if (P.head == NULL)
		{
			newelem->prev = NULL;
			P.head = newelem;
			P.tail = newelem;
		}
		else
		{
			newelem->prev = P.tail;
			P.tail->next = newelem;
			P.tail = newelem;
		};
	};
	return P;
}

int _tmain(int argc, _TCHAR* argv[])
{
	polinom X;
	polinom Y, Z;

	int i;
	for (i = 10; i > 0; i--)
	{
		X.add(i + 2, i + 2);
		Y.add(i, i);
	};
	Z = Y - X;
	cout << "X:";
	X.print();
	cout << "Y:";
	Y.print();
	cout << "Z:";
	Z.print();
	X = Z = Z - Z + Z;
	cout << "Z=0:";
	Z.print();
	X.print();

	for (i = 10; i > 0; i--)
	{
		X.del(i);
	};
	X.print();
	Z.print();
	X.del(10);
	X.print();
	X.znach(5);

	X.~X();
	Y.~Y();
	system("PAUSE");
	return 0;
}



