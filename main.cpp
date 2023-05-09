#include "main.h"

int main() {
	setlocale(LC_ALL, "Russian");

	cout << "	FUNCTIONS:" << endl;
	cout << "1. powMod" << endl;
	cout << "2. Evklid NOD" << endl;
	cout << "3. Diffi-Hellman" << endl;

	cout << "\n	ENCRYPTION:" << endl;
	cout << "4. Shamir cipher" << endl;
	cout << "5. El-Gamal cipher (encryption)" << endl;
	cout << "6. El-Gamal cipher (decryption)" << endl;
	cout << "7. Vernam cipher (encryption)" << endl;
	cout << "8. Vernam cipher (decryption)" << endl;
	cout << "9. RSA cipher (encryption)" << endl;
	cout << "10. RSA cipher (decryption)" << endl;

	cout << "\n	DIGITAL SIGNATURE:" << endl;
	cout << "11. El-Gamal signature" << endl;
	cout << "12. El-Gamal verify" << endl;
	cout << "13. RSA signature" << endl;
	cout << "14. RSA verify" << endl;
	cout << "15. GOST signature" << endl;
	cout << "16. GOST verify" << endl;

	cout << "\n	POKER:" << endl;
	cout << "17. Start poker" << endl;

	cout << "\n	SIGNATURE:" << endl;
	cout << "18. Start" << endl;

	cout << "\n0. EXIT" << endl;

	while (true)
	{
		int variant;
		cout << "\nSelect an action: ";
		cin >> variant;

		switch (variant) 
		{
			case 0:
			{
				cout << "\nGoodbye!\n" << endl;
				break;
			}
			case 1:
			{
				cout << endl << powMod(2, 5, 11) << endl;
				break;
			}
			case 2:
			{
				cout << endl << "NOD: = " << evklid_nod(3, 11) << endl;
				cout << "X: =  " << evklid_x(3, 11) << endl;
				cout << "Y: =  " << evklid_y(3, 11) << endl;
				break;
			}
			case 3:
			{
				cout << Diffi_Hellman() << endl;
				break;
			}
			case 4:
			{
				cout << "\nMessage m: " << Shamir(5050) << endl;
				break;
			}
			case 5:
			{
				El_Gamal_encrypt();
				break;
			}
			case 6:
			{
				El_Gamal_decrypt();
				break;
			}
			case 7:
			{
				VernamEncrypt();
				break;
			}
			case 8:
			{
				VernamDecrypt();
				break;
			}
			case 9:
			{
				RSA_encrypt();
				break;
			}
			case 10:
			{
				RSA_decrypt();
				break;
			}
			case 11:
			{
				El_Gamal_sign();
				break;
			}
			case 12:
			{
				El_Gamal_verify();
				break;
			}
			case 13:
			{
				RSA_sign();
				break;
			}
			case 14:
			{
				RSA_verify();
				break;
			}
			case 15:
			{
				GOST_sign();
				break;
			}
			case 16:
			{
				GOST_verify();
				break;
			}
			case 17:
			{
				poker();
				break;
			}
			case 18:
			{
				signature();
				break;
			}
			default:
			{
				cout << "\nERROR" << endl;
				break;
			}
		}
		if (variant == 0) 
		{
			break;
		}	
	}

	system("pause");
	return 0;
}
