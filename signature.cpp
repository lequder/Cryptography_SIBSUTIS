#include "main.h"
#include "md5.h"

using namespace std;

ll MD5(ll Na, string message) {
	ll y = 10;
	string str = message;

	//string str = string(message); //переводим char в string
	string h_str = md5hash_to_string(MD5(&str[0], str.size())); //прогоняем сообщение через MD5 и получаем хеш
	char* h_char = strcpy(new char[h_str.length() + 1], h_str.c_str()); //переводим string в char

	for (int i = 0; i < strlen(h_char); i++) {
		y = powMod((y + (int)h_char[i]), 2, Na); //получаем хеш-значение по функции Yi=( Yi-1 + (ASCII код символа) )^2 mod Na
	}
	return y;
}

string open_file(string FileName) {
	string file;
	ifstream fin;
	fin.open(FileName);
	if (!fin.is_open())
	{
		cout << "Error file" << endl;
	}
	else
	{
		while (getline(fin, file))
		{
			fin >> file;
		}
	}
	fin.close();

	return file;
}

//1) Digital signature El-Gamal
void El_Gamal_sign() {
	ll p = 0, q = 0, g = 0;
	ll x, y, h, k, r, u, k1, s, w;
	string FileName, message, file_sign;
	random(p, q, g);
	x = ((rand() << 1) | rand()) % (p - 1);
	y = powMod(g, x, p);

	cout << "Enter file name: ";
	cin >> FileName;
	message = open_file(FileName);
	file_sign = "(sign)" + FileName;

	h = MD5(y, message);
	while (1)
	{
		k = ((rand() << 1) | rand()) % (p - 1);
		if (evklid_nod(k, p - 1) == 1)
		{
			break;
		}
	}
	r = powMod(g, k, p);
	u = (powMod((h - x * r), 1, (p - 1)) + (p - 1)) % (p - 1);
	k1 = (evklid_y(k, p - 1) + (p - 1)) % (p - 1);
	s = ((k1 % (p - 1)) * (u % (p - 1))) % (p - 1);

	ofstream fout;
	fout.open(file_sign);
	if (!fout.is_open())
	{
		cout << "Error file" << endl;
	}
	else
	{
		fout << y << endl;
		fout << r << endl;
		fout << p << endl;
		fout << g << endl;
		fout << s << endl;
	}
	fout.close();
}

void El_Gamal_verify() {
	ll h, y, r, p, g, s, yr, rs, yrrs;
	string FileName, message, file_sign;

	cout << "Enter file name: ";
	cin >> FileName;
	message = open_file(FileName);

	file_sign = open_file("(sign)" + FileName);
	cout << file_sign << endl;
	cout << message << endl;

	cout << "Enter y: ";
	cin >> y;
	cout << "Enter r: ";
	cin >> r;
	cout << "Enter p: ";
	cin >> p;
	cout << "Enter g: ";
	cin >> g;
	cout << "Enter s: ";
	cin >> s;

	h = MD5(y, message);

	yr = powMod(y, r, p);
	rs = powMod(r, s, p);
	yrrs = yr * rs;

	if (powMod(yrrs, 1, p) == powMod(g, h, p))
	{
		cout << "Verify successful" << endl;
	}
	else cout << "Verify not successful" << endl;
}

//2) Digital signature RSA
void RSA_sign() {
	ll Pa, Qa, Na, fa, Ca, Da, y, s, w;
	string FileName, message, file_sign;

	cout << "Enter file name: ";
	cin >> FileName;
	message = open_file(FileName);
	file_sign = "(sign)" + FileName;

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
		Qa = (rand() << 1) | rand(); 
		if (test_Ferma(Qa) == 1) 
		{
			break;
		}
	}

	Na = Pa * Qa;
	fa = (Pa - 1) * (Qa - 1);

	while (1)
	{
		Da = ((rand() << 1) | rand()) % (fa + 1);
		if (evklid_nod(Da, fa) == 1) 
		{
			break;
		}
	}

	Ca = evklid_y(fa, Da);

	if (Ca < 0)
	{
		Ca = Ca + fa;
	}
	
	y = MD5(Na, message);
	s = powMod(y, Ca, Na);

	ofstream fout;
	fout.open(file_sign);
	if (!fout.is_open())
	{
		cout << "Error file" << endl;
	}
	else
	{
		fout << Da << endl;
		fout << Na << endl;
		fout << s << endl;
	}
	fout.close();
}

void RSA_verify() {
	ll Da, Na, s, w, y;

	char message[50];
	cout << "Enter message: ";
	cin >> message;
	cout << "Enter Da: ";
	cin >> Da;
	cout << "Enter Na: ";
	cin >> Na;
	cout << "Enter signature s: ";
	cin >> s;

	y = MD5(Na, message);
	w = powMod(s, Da, Na);

	if (w == y) {
		cout << "Verify successful" << endl;
	} else cout << "Verify not successful" << endl;
}

void GOST_sign(){
	srand(time(NULL));
	ll q,p,b,a,g,x,y,h,r,s,k, das;
	string FileName, message, file_sign;

	cout << "Enter file name: ";
	cin >> FileName;
	message = open_file(FileName);
	file_sign = "(sign)" + FileName;

	point0:
	while (1)
	{
		q = ((rand() << 1) | rand()) % 30000;
		if (test_Ferma(q) == true)
		{
			b = ((rand() << 1) | rand()) % 30000;
			p = b * q + 1;
			if (test_Ferma(p) == true)
			{
			point1:
				g = ((rand() << 1) | rand()) % p-1;
				a = powMod(g, b, p);
				if (powMod(a, q, p) == 1) 
				{
					break;
				}
				else goto point1;
			}
		}
	}

	while (1) 
	{
		x = ((rand() << 1) | rand()) % q;
		y = powMod(a, x, p);
		h = MD5(a, message) % q;
		if (q < h)
		{
			goto point0;
		}
		else break;
	}


	while (1) 
	{
	point2:
		k = ((rand() << 1) | rand()) % q;
		r = powMod(a, k, p) % q;
		s = ((k * h) + (x * r)) % q;
		if (r == 0 || s == 0)
		{
			goto point2;
		} 
		else break;
	}

	ofstream fout;
	fout.open(file_sign);
	if (!fout.is_open())
	{
		cout << "Error file" << endl;
	}
	else
	{
		fout << a << endl;
		fout << r << endl;
		fout << s << endl;
		fout << p << endl;
		fout << q << endl;
		fout << y << endl;
	}
	fout.close();
	cout << "File signed" << endl;
}

void GOST_verify() {
	ll a, y, h, h1, q, s, r, u1, u2, v, p;
	
	char message[50];
	cout << "Enter message: ";
	cin >> message;

	cout << "a: " << endl;
	cin >> a;
	cout << "r: " << endl;
	cin >> r;
	cout << "s: " << endl;
	cin >> s;
	cout << "p: " << endl;
	cin >> p;
	cout << "q: " << endl;
	cin >> q;
	cout << "y: " << endl;
	cin >> y;

	h = MD5(a, message) % q;
	h1 = evklid_y(h, q);
	if (h1 < 0) 
	{
		h1 = h1 + q;
	}
	u1 = (s * h1) % q;
	u2 = (((-r)+q) * h1) % q;
	v = ((powMod(a, u1, p) * powMod(y, u2, p)) % p) % q;

	if (v == r) {
		cout << "The sign is correct" << endl;
	}else cout << "The sign is incorrect" << endl;
}

