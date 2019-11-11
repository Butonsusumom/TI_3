#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm> 
#include <vector>
#include <fstream>
using namespace std;


vector <int> PervRoots;

#define ID_BUTTON_CIPHER 1001
#define ID_BUTTON_DECIPHER 1002
#define ID_BUTTON_FILEOPEN 1003
#define ID_BUTTON_SHOW 1004
#define ID_EDIT_FILE 1005
#define ID_EDIT_P 1006
#define ID_EDIT_K 1007
#define ID_EDIT_X 1008
#define ID_EDIT_G 1009
#define ID_EDIT_ROOTS 10010
#define ID_EDIT_EXIT 10011
#define ID_LABEL_P 10012
#define ID_LABEL_K 10013
#define ID_LABEL_X 10014
#define ID_LABEL_G 10015
#define ID_LABEL_ROOTS 10016
#define ID_LABEL_EXIT 10017
#define ID_LABEL_FILE 10018

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

char szClassName[] = "CG_WAPI_Template";
HWND hEdit1;
HWND hEdit2;
HWND hEdit3;
HWND hEdit4;
HWND hEdit5;
HWND hEdit6;
HWND hEdit7;
HWND hWndButton;
HWND hWndButton1;
HWND hWndButton2;
HWND hWndButton3;
HWND hWndButton4;
HWND TitleLabel1;
HWND TitleLabel2;
HWND TitleLabel3;
HWND TitleLabel4;
HWND TitleLabel5;
HWND TitleLabel6;



//=================================================BEGIN ALGORITHMTH=======================================================

//Find array of simple diveders
vector <long long> find_prime_factors(long long n) {
	vector <long long> Arr;
	for (long long i = 2; i*i <= n; ++i) {
		if (n % i == 0) {
			Arr.push_back(i);
			while (n % i == 0)
				n /= i;
		}
	}
	if (n != 1) {
		Arr.push_back(n);
	}
	return Arr;
}
// Help Fast exponentiation modulo
long long mul(long long a, long long b, long long m) {
	if (b == 1)
		return a;
	if (b % 2 == 0) {
		long long t = mul(a, b / 2, m);
		return (2 * t) % m;
	}
	return (mul(a, b - 1, m) + a) % m;
}

//Fast exponentiation modulo
long long pows(long long a, long long b, long long m) {
	if (b == 0)
		return 1;
	if (b % 2 == 0) {
		long long t = pows(a, b / 2, m);
		return mul(t, t, m) % m;
	}
	return (mul(pows(a, b - 1, m), a, m)) % m;
}

//Find NOD, Evklid algorithm
long long gcd(long long a, long long b) {
	if (b == 0)
		return a;
	return gcd(b, a%b);
}

//check if number is simple
bool ferma(long long x) {
	if (x == 2)
		return true;
	srand(time(NULL));
	for (int i = 0; i < 100; i++) {
		long long a = (rand() % (x - 2)) + 2;
		if (gcd(a, x) != 1)
			return false;
		if (pows(a, x - 1, x) != 1)
			return false;
	}
	return true;
}

//Fast a^z mod n
int Fastexp(long long a, long long z, long long n) {
	long long a1 = a;
	long long z1 = z;
	long long x = 1;
	while (z1 != 0) {
		while (z1 % 2 == 0) {
			z1 /= 2;
			a1 = (a1*a1) % n;
		}
		z1--;
		x = (x*a1) % n;
	}
	return x;
}

vector<int> FindRoots(long long p) {
	vector <long long> simple = find_prime_factors(p - 1);
	vector<int> res;
	string s;
	bool flag;
	for (long long g = 2; g < p; g++) {
		flag = true;
		for (int j = 0; j < simple.size(); j++) {
			if (Fastexp(g, (p - 1) / simple[j], p) == 1) flag = false;
			else {
				if ((j == simple.size() - 1) && (flag)) { res.push_back(g); s = s + to_string(g) + "\r\n"; }
			}
		}
	}
	string s1;
	char ex[10000];
	s1 = "There are " + to_string(res.size()) + " roots\r\n"+s;
	SetWindowText(hEdit6, s1.c_str());

	return res;
}

long long CheckP(string s) {
	long long res = atoll(s.c_str());
	for (int i = 0; i < s.length(); i++) {
		if ((s[i] != '0') && (s[i] != '1') && (s[i] != '2') && (s[i] != '3') && (s[i] != '4') && (s[i] != '5') && (s[i] != '6') && (s[i] != '7') && (s[i] != '8') && (s[i] != '9'))
			return 0;
	}
	if (res > 255) {
		if (ferma(res)) return res;
	}
	return 0;
}





long long CheckK(string s, long long p) {
	long long res = atoll(s.c_str());
	for (int i = 0; i < s.length(); i++) {
		if ((s[i] != '0') && (s[i] != '1') && (s[i] != '2') && (s[i] != '3') && (s[i] != '4') && (s[i] != '5') && (s[i] != '6') && (s[i] != '7') && (s[i] != '8') && (s[i] != '9'))
			return 0;
	}
	if (res > 1) {
		if (res < p - 1) {
			if (gcd(res, p) == 1) return res;
		}
	}
	return 0;
}


long long CheckX(string s, long long p) {
	long long res = atoll(s.c_str());
	for (int i = 0; i < s.length(); i++) {
		if ((s[i] != '0') && (s[i] != '1') && (s[i] != '2') && (s[i] != '3') && (s[i] != '4') && (s[i] != '5') && (s[i] != '6') && (s[i] != '7') && (s[i] != '8') && (s[i] != '9'))
			return 0;
	}
	if (res > 1) {
		if (res < p - 1) {
			return res;
		}
	}
	return 0;
}

long long CheckG(string s) {
	long long res = atoll(s.c_str());
	for (int i = 0; i < s.length(); i++) {
		if ((s[i] != '0') && (s[i] != '1') && (s[i] != '2') && (s[i] != '3') && (s[i] != '4') && (s[i] != '5') && (s[i] != '6') && (s[i] != '7') && (s[i] != '8') && (s[i] != '9'))
			return 0;
	}
	if (find(PervRoots.begin(), PervRoots.end(), res) != PervRoots.end()) {
		return res;
	}
	return 0;
}

void Cipher(long long g, long long x, long long p, long long k) {
	int y, a, e, b, te;
	unsigned char byte;
	char ch;
	char name[500];
	char cipher_namename[500];
	string s,ex;
	GetWindowText(hEdit1,name, 500);
	
	y = Fastexp(g, x, p);
	a = Fastexp(g, k, p);
	ifstream in(name, ios::binary);
	if (!in) MessageBox(NULL, "Invalid file input", " Try again", MB_OK | MB_DEFBUTTON1 | MB_ICONEXCLAMATION | MB_DEFAULT_DESKTOP_ONLY);
	else {
		strcpy_s(cipher_namename, name);
		strcat_s(cipher_namename, "(cipher).txt");
		
		ofstream out(cipher_namename);
		//ofstream out(cipher_namename, ios::binary);
		in.read((char*)&byte, sizeof(unsigned char));
		while (!in.eof()) {
			b = (Fastexp(y, k, p)*(byte%p)) % p;
			ex =ex+ to_string(a) + ' ' + to_string(b) + ' '+ "\r\n";
			SetWindowText(hEdit7,ex.c_str());
			if (in.eof()) out << a << " " << b ;
			else
			out << a << " " << b << " ";
			//out.write((char*)&a, sizeof(short int));
			//out.write((char*)&b, sizeof(short int));

			in.read((char*)&byte, sizeof(unsigned char));
		}

		out.close();
		in.close();
	}
}

void Decipher(long long p, long long x) {
	int y, e,  te, m;
	short int a, b;
	unsigned char byte;
	char ch;
	string s;
	char name[500];
	char fname[9];
	char dir[64];
	char drive[3];
	char ext[5];
	char cipher_namename[500];
	GetWindowText(hEdit1, name, 500);
	ifstream in(name);
	//ifstream in(name, ios::binary);

	
	strcpy_s(cipher_namename, name);
	char* temp = strstr(cipher_namename, "(cipher)");
	temp[0] = 0;
	_splitpath_s(cipher_namename, drive, dir, fname, ext);
	
	strcat_s(cipher_namename, "(decipher)");
	strcat_s(cipher_namename, ext);
	ofstream out(cipher_namename, ios::binary);
	in >> a;
	in >> b;
	//in.read((char*)&a, sizeof(short int));
	//in.read((char*)&b, sizeof(short int));

	while (!in.eof()) {

		m = (Fastexp((a), x*(p - 2), p)*(b%p)) % p;
		out.write((char*)&m, sizeof(unsigned char));
		s = s + to_string(m)+"  "+char(m) + "\r\n";
		SetWindowText(hEdit7, s.c_str());
		in >> a;
		in >> b;
		//in.read((char*)&a, sizeof(short int));
		//in.read((char*)&b, sizeof(short int));

	}

	out.close();
	in.close();
}

//=======================================END ALGORITHM===========================================================


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG lpMsg;
	WNDCLASS wc;

	// Заполняем структуру класса окна
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(200, 160, 241)); 
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;

	// Регистрируем класс окна
	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, "Не могу зарегистрировать класс окна!", "Ошибка", MB_OK);
		return 0;
	}

	// Создаем основное окно приложения
	hWnd = CreateWindow(
		szClassName,                // Имя класса                   
		"Elgamal Cipher", // Текст заголовка
		WS_OVERLAPPEDWINDOW,        // Стиль окна                                             
		50, 50,                   // Позиция левого верхнего угла  
		800, 800,                  // Ширина и высота окна    
		(HWND)NULL,                // Указатель на родительское окно NULL    
		(HMENU)NULL,               // Используется меню класса окна              
		(HINSTANCE)hInstance,       // Указатель на текущее приложение
		NULL);                  // Передается в качестве lParam в событие WM_CREATE

	if (!hWnd)
	{
		MessageBox(NULL, "Не удается создать главное окно!", "Ошибка", MB_OK);
		return 0;
	}


	// Показываем наше окно
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	PAINTSTRUCT  ps;
	HDC          hdc;
	//SetTimer(hWnd, 2, 100, NULL);
	// Выполняем цикл обработки сообщений до закрытия приложения
	while (GetMessage(&lpMsg, NULL, 0, 0))
	{
		TranslateMessage(&lpMsg);
		DispatchMessage(&lpMsg);

	}
	return (lpMsg.wParam);
}

LRESULT onCreateWindow(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	/*
	 hWndButton = CreateWindow("button", "Click Me", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 
		30, 30, 100, 20, hWnd, (HMENU)ID_BUTTON_FILEOPEN, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);
	UpdateWindow(hWndButton);*/


	 hWndButton2 = CreateWindow("button", "Cipher", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		400, 670, 150, 40, hWnd, (HMENU)ID_BUTTON_CIPHER, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);
	UpdateWindow(hWndButton2);

	 hWndButton3 = CreateWindow("button", "Decipher", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		600, 670, 150, 40, hWnd, (HMENU)ID_BUTTON_DECIPHER, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);
	UpdateWindow(hWndButton3);

	 hWndButton4 = CreateWindow("button", "Show roots", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		210, 390, 120, 20, hWnd, (HMENU)ID_BUTTON_SHOW, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);
	UpdateWindow(hWndButton3);




	 hEdit1 = CreateWindow("Edit", NULL, WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE,
		130, 30, 620, 20, hWnd, (HMENU)ID_EDIT_FILE, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

	 hEdit2 = CreateWindow("Edit", NULL, WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE,
		30, 110, 300, 20, hWnd, (HMENU)ID_EDIT_P, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

	 hEdit3 = CreateWindow("Edit", NULL, WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE,
		30, 190, 300, 20, hWnd, (HMENU)ID_EDIT_K, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

	 hEdit4 = CreateWindow("Edit", NULL, WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE,
		30, 270, 300, 20, hWnd, (HMENU)ID_EDIT_X, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

	 hEdit5 = CreateWindow("Edit", NULL, WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE,
		30, 350, 300, 20, hWnd, (HMENU)ID_EDIT_G, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

	 hEdit6 = CreateWindow("Edit", NULL, WS_VSCROLL | WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE| ES_AUTOVSCROLL| ES_MULTILINE,
		30, 430, 300, 280, hWnd, (HMENU)ID_EDIT_ROOTS, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

	 hEdit7 = CreateWindow("Edit", NULL, WS_VSCROLL | WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_MULTILINE,
		400, 110, 350, 530, hWnd, (HMENU)ID_EDIT_EXIT, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);




	

	 TitleLabel1 = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Please, enter  simple number p more than 255", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU,
		30, 70, 300, 20, hWnd, (HMENU)ID_LABEL_P, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

	 TitleLabel2 = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Please, enter number k more than 1 and less than p-1, mutually simple with p-1", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU,
		30, 140, 300, 40, hWnd, (HMENU)ID_LABEL_K, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

	 TitleLabel3 = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Please, enter positive number x, not equal to 1 and less than p-1", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU,
		30, 220, 300, 40, hWnd, (HMENU)ID_LABEL_X, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

	 TitleLabel4 = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Please, choose the primitive root g from the available", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU,
		30, 300, 300, 40, hWnd, (HMENU)ID_LABEL_G, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

	 TitleLabel5 = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Possible primitive roots", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU,
		30, 390, 120, 20, hWnd, (HMENU)ID_LABEL_ROOTS, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

	 TitleLabel6 = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Exit file", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU,
		400, 70, 80, 20, hWnd, (HMENU)ID_LABEL_EXIT, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);
	 TitleLabel6 = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "   File Name", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU,
		 30, 30, 100, 20, hWnd, (HMENU)ID_LABEL_FILE, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);




	return 0;
}

LRESULT onButtonCipher(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	long long p, k, x, g, y;
	char buff[200];
	string s;
	GetWindowText(hEdit2,buff,200);
	s = buff;
	p = CheckP(s);
	if (p != 0) {
		GetWindowText(hEdit3, buff, 200);
		s = buff;
		k = CheckK(s, p - 1);
		if (k != 0) {
			GetWindowText(hEdit4, buff, 200);
			s = buff;
			x = CheckX(s, p);
			if (x != 0) {
				PervRoots = FindRoots(p);
				GetWindowText(hEdit5, buff, 200);
				s = buff;
				g = CheckG(s);
				if (g != 0) {
					Cipher(g, x, p, k);
				}
				else {
					MessageBox(NULL, "Invalid input g", " Try again", MB_OK | MB_DEFBUTTON1 | MB_ICONEXCLAMATION | MB_DEFAULT_DESKTOP_ONLY);
					SetWindowText(hEdit5, "");
				}
			}
			else {
				MessageBox(NULL, "Invalid input x", " Try again", MB_OK | MB_DEFBUTTON1 | MB_ICONEXCLAMATION | MB_DEFAULT_DESKTOP_ONLY);
				SetWindowText(hEdit4, "");
			}
		}
		else {
			MessageBox(NULL, "Invalid input k", " Try again", MB_OK | MB_DEFBUTTON1 | MB_ICONEXCLAMATION | MB_DEFAULT_DESKTOP_ONLY);
			SetWindowText(hEdit3, "");
		}
	}
	else {
		MessageBox(NULL,"Invalid input p"," Try again", MB_OK| MB_DEFBUTTON1 |MB_ICONEXCLAMATION | MB_DEFAULT_DESKTOP_ONLY);
		SetWindowText(hEdit2, "");
	}
	return 0;
}

LRESULT onButtonDeCipher(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	long long p, k, x, g, y;
	char buff[200];
	string s;
	GetWindowText(hEdit2, buff, 200);
	s = buff;
	p = CheckP(s);
	if (p != 0) {
		GetWindowText(hEdit4, buff, 200);
		s = buff;
		x = CheckX(s, p);
		if (x != 0) {
			Decipher(p, x);
		}
	    else {
			MessageBox(NULL, "Invalid input x", " Try again", MB_OK | MB_DEFBUTTON1 | MB_ICONEXCLAMATION | MB_DEFAULT_DESKTOP_ONLY);
			SetWindowText(hEdit4, "");
		}
	}
	else {
		MessageBox(NULL, "Invalid input p", " Try again", MB_OK | MB_DEFBUTTON1 | MB_ICONEXCLAMATION | MB_DEFAULT_DESKTOP_ONLY);
		SetWindowText(hEdit2, "");
	}
	return 0;
}

LRESULT onButtonShow(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	int p;
	char buff[200];
	string s;
	GetWindowText(hEdit2, buff, 200);
	s = buff;
	p = CheckP(s);
	if (p != 0) {
		PervRoots = FindRoots(p);
	}
	else {
		MessageBox(NULL, "Invalid input p", " Try again", MB_OK | MB_DEFBUTTON1 | MB_ICONEXCLAMATION | MB_DEFAULT_DESKTOP_ONLY);
		SetWindowText(hEdit2, "");

	}
	return 0;

}

LRESULT onButtonOpenFile(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
/*	OPENFILENAME ofn;       // common dialog box structure
	TCHAR szFile[260];       // if using TCHAR macros

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = _countof(szFile);
	ofn.lpstrFile[0] = '\0';
	ofn.lpstrFilter = _T("All\0*.*\0Text\0*.TXT\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = _T("c:/work");
	ofn.Flags = OFN_EX_NOPLACESBAR;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		// use ofn.z 
	}*/
	//SetWin
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CREATE:
		return onCreateWindow(hWnd, message, wParam, lParam);

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_BUTTON_FILEOPEN:
			return onButtonOpenFile(hWnd, message, wParam, lParam);

		case ID_BUTTON_CIPHER:
			return onButtonCipher(hWnd, message, wParam, lParam);

		case ID_BUTTON_DECIPHER:
			return onButtonDeCipher(hWnd, message, wParam, lParam);

		case ID_BUTTON_SHOW:
			return onButtonShow(hWnd, message, wParam, lParam);
		}
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam); //освобождаем очередь приложения от нераспознаных
}

