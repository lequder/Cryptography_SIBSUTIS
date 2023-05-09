#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream> 
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <algorithm>
#include <string.h>
#include <bitset>
#include "fstream"
#include <vector>
#include <string>

#define ll long long

using namespace std;
//1) Функция быстрого возведения числа в степень по модулю
ll powMod(ll a, ll b, ll p);

//2) Функция, реализующая обобщённый алгоритм Евклида. Функция должна позволять находить наибольший общий делитель и обе неизвестных из уравнения.
ll evklid_nod(ll a, ll b);
ll evklid_x(ll a, ll b);
ll evklid_y(ll a, ll b);

//3) Функция построения общего ключа для двух абонентов по схеме Диффи - Хеллмана
bool test_Ferma(ll p);
void random(ll& p, ll& q, ll& g);
ll Diffi_Hellman();

//1) Shamir cipher
ll Shamir(ll m);

//2) El-Gamal cipher
void El_Gamal_encrypt();
void El_Gamal_decrypt();

//3) Vernam cipher
void VernamEncrypt();
void VernamDecrypt();

//4) RSA cipher
void RSA_encrypt();
void RSA_decrypt();

//1) Digital signature El-Gamal
void El_Gamal_sign();
void El_Gamal_verify();

//2) Digital signature RSA
void RSA_sign();
void RSA_verify();

//3) Digital signature GOST
void GOST_sign();
void GOST_verify();

void poker();

void signature();
