#include "main.h"

void poker() {
srand(time(NULL));
ll p, Ca, Cb, Da, Db, pack[55], u[9], card_A[2], card_B[2], card_table[5], view_A[2], view_B[2], view_table[5];;
int j, n;

point0:
while (1)
{
	p = (rand() << 1) | rand();
	if (test_Ferma(p) == 1)
	{
		break;
	}
}

Ca = ((rand() << 1) | rand()) % (p - 1);
Cb = ((rand() << 1) | rand()) % (p - 1);

while (1)
{
	Da = evklid_y(Ca, p - 1);
	if (Da < 0)
	{
		Da = Da + (p - 1);
	}

	Db = evklid_y(Cb, p - 1);
	if (Db < 0)
	{
		Db = Db + (p - 1);
	}

	if (((Ca * Da) % (p - 1) == 1) && ((Cb * Db) % (p - 1) == 1))
	{
		break;
	}
	else goto point0;
}
//Шаг 1. Шифруем и перемешиваем колоду
for (int i = 2; i < 55; i++)
{
	pack[i] = powMod(i, Ca, p);
	pack[i] = powMod(pack[i], Cb, p);//провели каждую карту через powMod
}
random_shuffle(&pack[2], &pack[55]); //перемешиваем колоду

//Шаг 2. Игроки берут по 2 карты
point1:
for (int i = 0; i < 2; i++) 
{
	j = 2 + rand() % 54;
	if (pack[j] != 0 && pack[j+1] != 0)
	{
		card_A[i] = pack[j]; // А берет 2 карты из колоды
		card_B[i] = pack[j+1]; // Б берет 2 карты из колоды
		pack[j] = pack[j+1] = 0;
	} else goto point1;
}

//Шаг 3. На стол выкладывается 5 карт
point2:
for (int i = 0; i < 5; i++)
{
	j = 2 + rand() % 54;
	if (pack[j] != 0)
	{
		card_table[i] = pack[j];
		pack[j] = 0;
	} else goto point2;

}

//Шаг 4. Игрок B узнает свои карты
cout << "\n------------------------------------ " << endl;
cout << "\nPlayer B: " << endl;
for (int i = 0; i < 2; i++)
{
	view_B[i] = powMod(card_B[i], Da, p);
	view_B[i] = powMod(view_B[i], Db, p);
	cout << "Card " << i+1 << " - " << view_B[i] << endl;
}

//Шаг 5. Игрок A узнает свои карты
cout << "\nPlayer A: " << endl;
for (int i = 0; i < 2; i++)
{
	view_A[i] = powMod(card_A[i], Db, p);
	view_A[i] = powMod(view_A[i], Da, p);
	cout << "Card " << i+1 << " - " << view_A[i] << endl;
}

//Шаг 6. Игроки узнают карты на столе
cout << "\nTable: " << endl;
for (int i = 0; i < 5; i++)
{
	view_table[i] = powMod(card_table[i], Da, p);
	view_table[i] = powMod(view_table[i], Db, p);
	cout << "Card " << i+1 << " - " << view_table[i] << endl;
}
cout << "\nCa - " << Ca << endl;
cout << "Cb - " << Cb << endl;

}