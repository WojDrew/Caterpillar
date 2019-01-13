#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <cstdlib>
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

typedef struct Element
{
	char ch;
	Element(char c)
	{
		ch = c;
	}
	Element* next;
	Element* prev;
};
void pushFront(char cha, Element** head, Element** tail);
void pushBack(char cha, Element** tail, Element** head);
void removeFront(Element** head, Element** tail);
void removeBack(Element** tail, Element** head);
void showList(Element** head, Element** tail);
void wykonajRuch(Element** head, Element** tail, char **field, char** waste, int& x, int& y, int n, int m, int& kierunek, int koniec, int c);

int main()
{
	int n = 0, m = 0, c = 0;
	int x = 0, y = 0, d = 0;
	int kierunek = RIGHT;

	scanf_s("%d %d %d",&n ,&m ,&c);

	scanf_s("%d %d %d", &x, &y, &d);

	char **field = new char*[m];
	for (int i = 0; i < m; i++)
		field[i] = new char[n];
	char **waste = new char*[m];
	for (int i = 0; i < m; i++)
		waste[i] = new char[n];
	char *caterpillar = new char[d];

	scanf("%s", caterpillar);
	for (int i = 0; i < m; i++)
		scanf("%s",field[i]);

	Element* temp = new Element('#');
	Element* glowa = temp;
	Element* ogon = temp;
	for (int i = d-1; i >= 0; i--)
		pushFront(caterpillar[i], &glowa, &ogon);

	/*if (field[y - 1][x - 1] == '1')
		kierunek = UP;
	else if (field[y - 1][x - 1] == '2')
		kierunek = DOWN;
	else if (field[y - 1][x - 1] == '3')
		kierunek = LEFT;*/

	for (int i = 0; i < c; i++)
	{
		if (glowa->ch != '#')
		{
			wykonajRuch(&glowa, &ogon, field, waste, x, y, n, m, kierunek, i, c);
		}
	}

	printf("%d %d ", x, y);
	showList(&glowa, &ogon);
	putchar('\n');
	for (int i = 0; i < m; i++)
	{
		printf("%s", field[i]);
		putchar('\n');
	}
	/*delete caterpillar;
	for (int i = 0; i < m; ++i)
		delete waste[i];
	for (int i = 0; i < m; ++i)
		delete field[i];
	delete field;
	delete waste;*/
	
	//system("pause");
	return 0;
}

void pushFront(char cha, Element** head, Element** tail)
{
	if ((*head)->ch == '#')
	{
		Element* temp = *head;
		delete temp;
		Element* el = new Element(cha);
		el->next = nullptr;
		el->prev = nullptr;
		*head = el;
		*tail = el;
	}
	else
	{
		Element* el = new Element(cha);
		el->next = *head;
		(*head)->prev = el;
		el->prev = nullptr;
		*head = el;
	}
}

void pushBack(char cha, Element** tail, Element** head)
{
	if ((*head)->ch == '#')
	{
		Element* temp = *head;
		delete temp;
		Element* el = new Element(cha);
		el->next = nullptr;
		el->prev = nullptr; 
		*tail= el;
		*head = el;
	}
	else
	{
		Element* el = new Element(cha);
		el->next = nullptr;
		(*tail)->next = el;
		el->prev = *tail;
		*tail = el;
	}
}

void removeFront(Element** head, Element** tail)
{
		if ((*head)->next == nullptr && (*tail)->prev == nullptr)
		{
			Element* temp = *head;
			Element* temp_2 = new Element('#');
			temp_2->next = nullptr;
			temp_2->prev = nullptr;
			*head = temp_2;
			*tail = temp_2;
			delete temp;

		}
		else
		{
			Element* temp = *head;
			(*head)->next->prev = nullptr;
			*head = temp->next;
			delete temp;
		}
}
void removeBack(Element** tail, Element** head)
{
		if ((*head)->next == nullptr && (*tail)->prev == nullptr)
		{
			Element* temp = *head;
			Element* temp_2 = new Element('#');
			temp_2->next = nullptr;
			temp_2->prev = nullptr;
			*head = temp_2;
			*tail = temp_2;
			delete temp;
		}
		else
		{
			Element* temp = *tail;
			(*tail)->prev->next = nullptr;
			*tail = temp->prev;
			delete temp;
		}
}

void showList(Element** head, Element** tail)
{
	Element* temp = *head;
	while (temp != nullptr)
	{
		putchar(temp->ch);
		temp = temp->next;
	}
}

void wykonajRuch(Element** head, Element** tail, char **field, char** waste, int& x, int& y, int n, int m, int& kierunek, int koniec, int c)
{
	
		if (field[y - 1][x - 1] == '1')
			kierunek = UP;
		else if (field[y - 1][x - 1] == '2')
			kierunek = DOWN;
		else if (field[y - 1][x - 1] == '3')
			kierunek = LEFT;
		else if (field[y - 1][x - 1] == '4')
			kierunek = RIGHT;
		else if (field[y - 1][x - 1] >= 65 && field[y - 1][x - 1] <= 90)
		{

			if (field[y - 1][x - 1] == 'A')
			{
				pushBack(field[y - 1][x - 1] + 32, tail, head);
				field[y - 1][x - 1] = '@';
				waste[y - 1][x - 1] = 'A';
			}
			else
			{
				pushBack(field[y - 1][x - 1] + 32, tail, head);
				field[y - 1][x - 1] = field[y - 1][x - 1] - 1;
			}

		}
		else if (field[y - 1][x - 1] >= 97 && field[y - 1][x - 1] <= 122)
		{

			if (field[y - 1][x - 1] == 'a')
			{
				pushFront(field[y - 1][x - 1], head, tail);
				field[y - 1][x - 1] = '@';
				waste[y - 1][x - 1] = 'a';
			}
			else
			{
				pushFront(field[y - 1][x - 1], head, tail);
				field[y - 1][x - 1] = field[y - 1][x - 1] - 1;
			}

		}
		else if (field[y - 1][x - 1] == '@')
		{
			if (waste[y - 1][x - 1] == 'a')
				removeFront(head, tail);
			else if (waste[y - 1][x - 1] == 'A')
				removeBack(tail, head);
		}
		if (koniec != c-1 && (*head)->ch != '#')
		{
			switch (kierunek)
			{
			case RIGHT:
				x++;
				break;
			case LEFT:
				x--;
				break;
			case UP:
				y--;
				break;
			case DOWN:
				y++;
				break;
			default:
				break;
			}
		}

		if (x < 1)
			x = n;
		else if (x > n)
			x = 1;
		else if (y < 1)
			y = m;
		else if (y > m)
			y = 1;
	

}





