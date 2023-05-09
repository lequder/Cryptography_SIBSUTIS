#include "main.h" 

using namespace std;
//1) Функция быстрого возведения числа в степень по модулю
ll powMod(ll a, ll b, ll p) {
	ll y = 1;
	while (b) 
	{
		if (b & 1) y = (y * a) % p;
		b = b >> 1;
		a = (a * a) % p;
	}
	return y;
}

//2) Функция, реализующая обобщённый алгоритм Евклида. Функция должна позволять находить наибольший общий делитель и обе неизвестных из уравнения.
ll evklid_nod(ll a, ll b) {
	ll temp;
	if (b > a) 
	{ 
		temp = a; a = b; b = temp; 
	}
	ll q = 0;
	ll U[] = { a,1,0 }, V[] = { b,0,1 }, T[] = { 0,0,0 };
	
	while (V[0] != 0) 
	{
		q = U[0] / V[0];
		T[0] = U[0] - q * V[0]; T[1] = U[1] - q * V[1]; T[2] = U[2] - q * V[2];
		U[0] = V[0]; U[1] = V[1]; U[2] = V[2];
		V[0] = T[0]; V[1] = T[1]; V[2] = T[2];
	}
	return U[0];
}

ll evklid_x(ll a, ll b) {
	ll temp;
	if (b > a) 
	{ 
		temp = a; a = b; b = temp; 
	}

	ll q = 0;
	ll U[] = { a,1,0 }, V[] = { b,0,1 }, T[] = { 0,0,0 };
	
	while (V[0] != 0) 
	{
		q = U[0] / V[0];
		T[0] = U[0] - q * V[0]; T[1] = U[1] - q * V[1]; T[2] = U[2] - q * V[2];
		U[0] = V[0]; U[1] = V[1]; U[2] = V[2];
		V[0] = T[0]; V[1] = T[1]; V[2] = T[2];
	}
	return U[1];
}

ll evklid_y(ll a, ll b) {
	ll temp;
	if (b > a) 
	{ 
		temp = a; a = b; b = temp; 
	}
	ll q = 0;
	ll U[] = { a,1,0 }, V[] = { b,0,1 }, T[] = { 0,0,0 };
	
	while (V[0] != 0) 
	{
		q = U[0] / V[0];
		T[0] = U[0] - q * V[0]; T[1] = U[1] - q * V[1]; T[2] = U[2] - q * V[2];
		U[0] = V[0]; U[1] = V[1]; U[2] = V[2];
		V[0] = T[0]; V[1] = T[1]; V[2] = T[2];
	}
	return U[2];
}

//3) Функция построения общего ключа для двух абонентов по схеме Диффи - Хеллмана
bool test_Ferma(ll p) {
	if (p == 0)
	{
		return false;
	}
	ll a, b;

	for (int i = 0; i < 100; i++) 
	{ //Для того, чтобы проверить число на простоту, достаточно 100 раз проверить случайное число
		a = rand() % p + 1;  //Выбор случайного основания от 2 до n - 1
		b = powMod(a, (p - 1), p);
		if (evklid_nod(a, p) != 1)
		{
			return false;
		}
		if (b != 1)
		{
			return false;
		}
	}
	return true;
}

void random(ll& p, ll& q, ll& g) {
	while (1) 
	{
		p = (rand() << 15) | rand(); //сдвиг rand() на 15 битов влево ИЛИ побитово сравнивает с rand() (сделать число больше)
		if (test_Ferma(p) == true)
		{
			q = (p - 1) / 2;
		}
		if (test_Ferma(q) == true)
		{
			break;
		}
	}

	while (1) 
	{ 
		g = ((rand() << 15) | rand()) % (p - 1); 
		if (powMod(g, q, p) != 1)
		{
			break;
		}
	}
}

ll Diffi_Hellman() {
	srand(time(0));
	ll Xa, Xb, Ya, Yb, Zab, Zba;
	ll q = 0, g = 0, p = 0;
	random(q, g, p);
	Xa = (rand() << 15) | rand(); 
	Xb = (rand() << 15) | rand();
	Ya = powMod(g, Xa, p); 
	Yb = powMod(g, Xb, p);
	Zab = powMod(Yb, Xa, p); 
	Zba = powMod(Ya, Xb, p);
	if (Zab == Zba)
	{
		return Zab;
	}
}
