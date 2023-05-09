#include "main.h"


//1) Шифр Шамира
ll Shamir(ll m) {
	srand(time(0));
	ll p, Ca, Cb, Da, Db, x1, x2, x3, x4 = 0; //Ca, Da - секретное число (знает только А); Cb, Db - секретное число (знает только B); p - открытое число, которое А открыто передает В
	
	while (1) 
	{ 
		p = (rand() << 15) | rand(); 
		if (test_Ferma(p) == 1) 
		{
			break;
		}
	}

	while (1) 
	{
		Ca = ((rand() << 15) | rand()) % (p - 2) + 1; 
		Cb = ((rand() << 15) | rand()) % (p - 2) + 1;
		if ((evklid_nod(Ca, p - 1) == 1) && (evklid_nod(Cb, p - 1) == 1)) 
		{ 
			break; 
		}
	}

	Da = evklid_y(Ca, p - 1); 
	Db = evklid_y(Cb, p - 1);

	if (Da < 0) 
	{ 
		Da = Da + (p - 1); 
	}

	if (Db < 0) 
	{ 
		Db = Db + (p - 1); 
	}

	x1 = powMod(m, Ca, p); x2 = powMod(x1, Cb, p); x3 = powMod(x2, Da, p); x4 = powMod(x3, Db, p); //x1 возводит А и передает B, x2 возводит B и передает A, x3 возводит А и передает B, x4 возводит B и получает сообщение m  
	
	return x4;
}

//2) Шифр Эль-Гамаля
void El_Gamal_encrypt() {
	ll m, p = 0, q = 0, g = 0;
	random(p, q, g);
	ll Ca = (rand() + 1) % (p - 1); //абонент A выбирает свое секретное число ci (1 < ci < p−1)
	ll Cb = (rand() + 1) % (p - 1); //абонент B выбирает свое секретное число ci (1 < ci < p−1)
	ll Da = powMod(g, Ca, p); //A вычисляет соответствующее ему открытое число di
	ll Db = powMod(g, Cb, p); //B вычисляет соответствующее ему открытое число di
	
	cout << "p = " << p << endl;
	cout << "g = " << g << endl;
	cout << "Ca = " << Ca << endl;
	cout << "Cb = " << Cb << endl;
	cout << "Da = " << Da << endl;
	cout << "Db = " << Db << endl;

	cout << "\nEnter a number m (m<p): ";
	cin >> m;

	if (m > p) {
		cout << ("ERROR m > p\n");
		exit(-2);
	}

	//Шаг 1. A формирует случайное число k, 1 ≤ k ≤ p−2 и вычисляет числа r, e		
	ll k = ((rand() << 15) | rand()) % (p - 2);
	cout << "\nk = " << k << endl;

	ll r = powMod(g, k, p);
	cout << "r = " << r << endl;

	ll e = m * powMod(Db, k, p) % p;
	cout << "e = " << e << endl;

	// передает пару чисел (r ,e) абоненту B =====>
	//Шаг 2. B, получив(r, e), вычисляет m_
	ll m_ = e * powMod(r, (p - 1 - Cb), p) % p;
	cout << "\nDecrypt m = " << m_ << endl << "\n";
}

void El_Gamal_decrypt() {
	ll r, e, p, Cb, m_;

	cout << "Enter r: ";
	cin >> r;
	cout << "Enter e: ";
	cin >> e;
	cout << "Enter p: ";
	cin >> p;
	cout << "Enter Cb: ";
	cin >> Cb;
	
	m_ = e * powMod(r, (p - 1 - Cb), p) % p;
	cout << "\nDecrypt m = " << m_ << endl;
}

//3) Шифр Вернама
string toBinary(string const& str) {
	string binary = "";
	for (char const& c : str) 
	{
		binary += bitset<8>(c).to_string();
	}
	return binary;
}

void VernamEncrypt(){
	string text, textBinary, key, keyBinary, textCrypt;
	
	cout << "\nEnter message: ";
	cin >> text;
	textBinary = toBinary(text);
	cout << "Binary message: " << textBinary << endl;

	cout << "\nEnter key: ";
	cin >> key;
	if (key.length() != text.length()) 
	{
		cout << "ERROR: key != text";
	}
	keyBinary = toBinary(key);
	cout << "Binary key: " << keyBinary << endl;

	for (int i = 0; i < textBinary.length(); i++) 
	{
		if (textBinary[i] == keyBinary[i])
			textCrypt += '0';
		else textCrypt += '1';
	}
	cout << "\nEncrypted message: " << endl;
	cout << textCrypt << endl;
}

void VernamDecrypt() {
	string text, key, textDecrypt;
	cout << "\nEnter encrypted message: ";
	cin >> text;

	cout << "\nEnter key: ";
	cin >> key;

	for (int i = 0; i < text.length(); i++)
	{
		if (key[i] == '1')
		{
			if (text[i] == '1')
			{
				textDecrypt += '0';
			}
			else textDecrypt += '1';
		}
		else if (text[i] == '1')
		{
			textDecrypt += '1';
		}
		else textDecrypt += '0';
	}
	cout << "\nBinary message: " << textDecrypt << endl;
}

//4) RSA cipher
void RSA_encrypt(){
ll Pa, Pb, Qa, Qb, Na, Nb, fa, fb, Ca, Cb, Da, Db, e, m, m_;

while (1) 
{ 
	Pa = (rand() << 1) | rand(); 
	if (test_Ferma(Pa) == 1) 
	{
		break;
	}
}
while (1) 
{ 
	Pb = (rand() << 1) | rand(); 
	if (test_Ferma(Pb) == 1) 
	{
		break;
	}
}
while (1) 
{ 
	Qa = (rand() << 1) | rand(); 
	if (test_Ferma(Qa) == 1) 
	{
		break;
	}
}
while (1) 
{ 
	Qb = (rand() << 1) | rand(); 
	if (test_Ferma(Qb) == 1) 
	{
		break;
	}
}

Na = Pa * Qa; Nb = Pb * Qb;
fa = (Pa - 1) * (Qa - 1); fb = (Pb - 1) * (Qb - 1);

while (1) 
{ 
	Da = ((rand() << 1) | rand()) % (fa + 1);
	Db = ((rand() << 1) | rand()) % (fb + 1);
	if ((evklid_nod(Da, fa) == 1) && (evklid_nod(Db, fb) == 1))
	{
		break;
	}
}

Ca = evklid_y(fa, Da); 
if (Ca < 0)
{
	Ca = Ca + fa;
}

Cb = evklid_y(fb, Db); 
if (Cb < 0)
{
	Cb = Cb + fb;
}

cout << "\nEnter a number m: ";
cin >> m;

cout << "\nCb: " << Cb << endl;
cout << "Nb: " << Nb << endl;

e = powMod(m, Db, Nb); //A вычисляет е по открытым ключам B
cout << "\nNumber e (encrypt m): " << e << endl;
}

void RSA_decrypt() {
	ll e, Cb, Nb, m;

	cout << "\nEnter e (encrypt m): ";
	cin >> e;

	cout << "\nEnter Cb: ";
	cin >> Cb;

	cout << "\nEnter Nb: ";
	cin >> Nb;

	m = powMod(e, Cb, Nb); //B вычисляет сообщение по своему секретному и открытому ключам и числа e
	cout << "\nDecrypt m: " << m << endl;
}
