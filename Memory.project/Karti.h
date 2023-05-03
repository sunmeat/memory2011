#include "beblioteca.h"

//Счетчик нажатие на карты (максимум 2)
int t = 0;

//Меню после победы
///////////////Прототипы функций
//Работа с мышкой
void mish(int arr_koordinat[40], int arr_kart[20], int data[20]);
//Рисует карточки
void kartinki(int arr_koordinat[40], int arr_kart[20], int data[20]);
//Меню при старте
void menu();
//Меню после победы
void posle_pobedi();
//Чистит экран консоли
void clear();
//Получает системное время (начало игры)
void sistem_time_start();
//Получает системное время (конец игры) и считает результат
void sistem_time_end();
//Выводит рекорд в конце
void show_record_end();



///////////////Функции проверки 
//Удаляет угаданные карты
void dell_kart(int arr_koordinat[40], int arr_kart[20], int data[20])
{

	if (t == 2)
	{
		//Переменные для записи открытых карт
		int f1 = 0;
		int f2 = 0;

		//Переменные для записи карт в массиве
		int k1 = 0;
		int k2 = 0;

		//Поиск открытых карт
		for (int i = -1; i < 20; i++)
		{
			int g = 2;
			if (g == arr_kart[i])
				f1 = i;
		}
		for (int i = 20; i > -1; i--)
		{
			int g = 2;
			if (g == arr_kart[i])
				f2 = i;
		}

		//Поиск расположение карт в массиве
		for (int i = -1; i < 20; i++)
		{
			int g = 2;
			if (f1 == data[i])
				k1 = i;
		}
		for (int i = -1; i < 20; i++)
		{
			int g = 2;
			if (f2 == data[i])
				k2 = i;
		}

		//Если первая карта четная - то похожая карта +1 (нечетная)
		if (k1 % 2 == 0)
		{
			if (k1 + 1 == k2)
			{
				Sleep(1000); t = 0;
				arr_kart[f1] = 0;
				arr_kart[f2] = 0;
				kartinki(arr_koordinat, arr_kart, data);
			}
			else
			{
				Sleep(1000); t = 0;
				arr_kart[f1] = 1;
				arr_kart[f2] = 1;
				kartinki(arr_koordinat, arr_kart, data);
			}
		}

		//Если первая карта нечетная - то похожая карта -1 (четная)
		if (k1 % 2 == 1)
		{
			if (k1 - 1 == k2)
			{
				Sleep(1000); t = 0;
				arr_kart[f1] = 0;
				arr_kart[f2] = 0;
				kartinki(arr_koordinat, arr_kart, data);
			}
			else
			{
				Sleep(1000); t = 0;
				arr_kart[f1] = 1;
				arr_kart[f2] = 1;
				kartinki(arr_koordinat, arr_kart, data);
			}
		}
	}
}
//Проверяет победу
void pobeda(int arr_kart[20])
{
	int g = 0;
	for (size_t i = 0; i < 20; i++)
		g += arr_kart[i];

	if (g >= 1) {}

	else
		sistem_time_end();
}


///////////////Карты 
//Рисует карточки
void kartinki(int arr_koordinat[40], int arr_kart[20], int data[20])
{
	//Чистит экран консоли
	clear();

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	HWND hwnd = GetConsoleWindow(); // дескриптор окна, используемый консолью
	HDC hdc = GetDC(hwnd);

	HPEN pen = CreatePen(PS_SOLID, 0, RGB(255, 255, 255));
	HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));

	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = false;
	cci.dwSize = 100;
	SetConsoleCursorInfo(h, &cci);

	pen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
	brush = CreateSolidBrush(RGB(127, 127, 127));
	SelectObject(hdc, pen);
	SelectObject(hdc, brush);

	int height_kart = 150;
	int width_kart = 120;
	cout << t << endl;

	////////////////////////////// РЯД 1

	////////// Карта 1.1
	//Закрыта
	if (arr_kart[data[0]] == 1)
		Rectangle(hdc, arr_koordinat[0], arr_koordinat[1], arr_koordinat[0] + width_kart, arr_koordinat[1] + height_kart);

	//Яблоко
	else if (arr_kart[data[0]] == 2)
	{
		//Фон
		brush = CreateSolidBrush(RGB(78, 182, 169));
		SelectObject(hdc, brush);
		Rectangle(hdc, arr_koordinat[0], arr_koordinat[1], arr_koordinat[0] + width_kart, arr_koordinat[1] + height_kart);

		//Красный круг
		pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		brush = CreateSolidBrush(RGB(255, 0, 0));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[0] + 35, arr_koordinat[1] + 40, arr_koordinat[0] + 35 + 60, arr_koordinat[1] + 40 + 60);

		//Круг цвет фона 
		brush = CreateSolidBrush(RGB(78, 182, 169));
		pen = CreatePen(PS_SOLID, 1, RGB(78, 182, 169));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[0] + 75, arr_koordinat[1] + 50, arr_koordinat[0] + 75 + 40, arr_koordinat[1] + 50 + 40);

		//Палка 
		brush = CreateSolidBrush(RGB(97, 30, 30));
		pen = CreatePen(PS_SOLID, 1, RGB(97, 30, 30));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Rectangle(hdc, arr_koordinat[0] + 62, arr_koordinat[1] + 15, arr_koordinat[0] + 62 + 5, arr_koordinat[1] + 15 + 25);

		//Лист 
		brush = CreateSolidBrush(RGB(14, 114, 21));
		pen = CreatePen(PS_SOLID, 1, RGB(14, 114, 21));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[0] + 62, arr_koordinat[1] + 12, arr_koordinat[0] + 62 + 20, arr_koordinat[1] + 12 + 10);
		DeleteObject(pen);
		DeleteObject(brush);

		//Рисовка для след карточек 
		pen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
		brush = CreateSolidBrush(RGB(127, 127, 127));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
	}
	else {}

	////////// Карта 1.2
	//Закрыта
	if (arr_kart[data[1]] == 1)
		Rectangle(hdc, arr_koordinat[2], arr_koordinat[3], arr_koordinat[2] + width_kart, arr_koordinat[3] + height_kart);

	//Яблоко
	else if (arr_kart[data[1]] == 2)
	{
		//Фон
		brush = CreateSolidBrush(RGB(78, 182, 169));
		SelectObject(hdc, brush);
		Rectangle(hdc, arr_koordinat[2], arr_koordinat[3], arr_koordinat[2] + width_kart, arr_koordinat[3] + height_kart);

		//Красный круг
		pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		brush = CreateSolidBrush(RGB(255, 0, 0));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[2] + 35, arr_koordinat[3] + 40, arr_koordinat[2] + 35 + 60, arr_koordinat[3] + 40 + 60);

		//Круг цвет фона 
		brush = CreateSolidBrush(RGB(78, 182, 169));
		pen = CreatePen(PS_SOLID, 1, RGB(78, 182, 169));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[2] + 75, arr_koordinat[3] + 50, arr_koordinat[2] + 75 + 40, arr_koordinat[3] + 50 + 40);

		//Палка 
		brush = CreateSolidBrush(RGB(97, 30, 30));
		pen = CreatePen(PS_SOLID, 1, RGB(97, 30, 30));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Rectangle(hdc, arr_koordinat[2] + 62, arr_koordinat[3] + 15, arr_koordinat[2] + 62 + 5, arr_koordinat[3] + 15 + 25);

		//Лист 
		brush = CreateSolidBrush(RGB(14, 114, 21));
		pen = CreatePen(PS_SOLID, 1, RGB(14, 114, 21));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[2] + 62, arr_koordinat[3] + 12, arr_koordinat[2] + 62 + 20, arr_koordinat[3] + 12 + 10);
		DeleteObject(pen);
		DeleteObject(brush);

		//Рисовка для след карточек 
		pen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
		brush = CreateSolidBrush(RGB(127, 127, 127));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
	}
	else {}

	////////// Карта 1.3
	//Закрыта
	if (arr_kart[data[2]] == 1)
		Rectangle(hdc, arr_koordinat[4], arr_koordinat[5], arr_koordinat[4] + width_kart, arr_koordinat[5] + height_kart);

	//Арбуз
	else if (arr_kart[data[2]] == 2)
	{
		//Фон
		brush = CreateSolidBrush(RGB(78, 182, 169));
		SelectObject(hdc, brush);
		Rectangle(hdc, arr_koordinat[4], arr_koordinat[5], arr_koordinat[4] + width_kart, arr_koordinat[5] + height_kart);

		//Зеленый Круг
		brush = CreateSolidBrush(RGB(0, 128, 45));
		pen = CreatePen(PS_SOLID, 1, RGB(0, 128, 45));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[4] + 22, arr_koordinat[5] + 50, arr_koordinat[4] + 22 + 80, arr_koordinat[5] + 50 + 70);

		//Полосы на арбузе
		pen = CreatePen(PS_SOLID, 1, RGB(27, 100, 50));
		brush = CreateSolidBrush(RGB(27, 100, 50));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[4] + 30, arr_koordinat[5] + 70, arr_koordinat[4] + 30 + 10, arr_koordinat[5] + 70 + 40);
		Ellipse(hdc, arr_koordinat[4] + 50, arr_koordinat[5] + 70, arr_koordinat[4] + 50 + 10, arr_koordinat[5] + 70 + 49);
		Ellipse(hdc, arr_koordinat[4] + 70, arr_koordinat[5] + 70, arr_koordinat[4] + 70 + 10, arr_koordinat[5] + 70 + 48);
		Ellipse(hdc, arr_koordinat[4] + 85, arr_koordinat[5] + 70, arr_koordinat[4] + 85 + 10, arr_koordinat[5] + 70 + 38);

		//Красный круг
		pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		brush = CreateSolidBrush(RGB(255, 0, 0));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[4] + 30, arr_koordinat[5] + 50, arr_koordinat[4] + 30 + 65, arr_koordinat[5] + 50 + 30);

		//Семки черные
		pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		brush = CreateSolidBrush(RGB(0, 0, 0));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[4] + 40, arr_koordinat[5] + 55, arr_koordinat[4] + 40 + 4, arr_koordinat[5] + 55 + 4);
		Ellipse(hdc, arr_koordinat[4] + 50, arr_koordinat[5] + 60, arr_koordinat[4] + 50 + 4, arr_koordinat[5] + 60 + 4);
		Ellipse(hdc, arr_koordinat[4] + 70, arr_koordinat[5] + 60, arr_koordinat[4] + 70 + 4, arr_koordinat[5] + 60 + 4);
		Ellipse(hdc, arr_koordinat[4] + 65, arr_koordinat[5] + 55, arr_koordinat[4] + 65 + 4, arr_koordinat[5] + 55 + 4);
		Ellipse(hdc, arr_koordinat[4] + 75, arr_koordinat[5] + 70, arr_koordinat[4] + 75 + 4, arr_koordinat[5] + 70 + 4);
		Ellipse(hdc, arr_koordinat[4] + 60, arr_koordinat[5] + 70, arr_koordinat[4] + 60 + 4, arr_koordinat[5] + 70 + 4);
		Ellipse(hdc, arr_koordinat[4] + 85, arr_koordinat[5] + 60, arr_koordinat[4] + 85 + 4, arr_koordinat[5] + 60 + 4);
		Ellipse(hdc, arr_koordinat[4] + 45, arr_koordinat[5] + 70, arr_koordinat[4] + 45 + 4, arr_koordinat[5] + 70 + 4);
		DeleteObject(brush);
		DeleteObject(pen);

		//Рисовка для след карточек
		pen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
		brush = CreateSolidBrush(RGB(127, 127, 127));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
	}
	else {}

	////////// Карта 1.4
	//Закрыта
	if (arr_kart[data[3]] == 1)
		Rectangle(hdc, arr_koordinat[6], arr_koordinat[7], arr_koordinat[6] + width_kart, arr_koordinat[7] + height_kart);

	//Арбуз
	else if (arr_kart[data[3]] == 2)
	{
		//Фон
		brush = CreateSolidBrush(RGB(78, 182, 169));
		SelectObject(hdc, brush);
		Rectangle(hdc, arr_koordinat[6], arr_koordinat[7], arr_koordinat[6] + width_kart, arr_koordinat[7] + height_kart);

		//Зеленый Круг
		brush = CreateSolidBrush(RGB(0, 128, 45));
		pen = CreatePen(PS_SOLID, 1, RGB(0, 128, 45));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[6] + 22, arr_koordinat[7] + 50, arr_koordinat[6] + 22 + 80, arr_koordinat[7] + 50 + 70);

		//Полосы на арбузе
		pen = CreatePen(PS_SOLID, 1, RGB(27, 100, 50));
		brush = CreateSolidBrush(RGB(27, 100, 50));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[6] + 30, arr_koordinat[7] + 70, arr_koordinat[6] + 30 + 10, arr_koordinat[7] + 70 + 40);
		Ellipse(hdc, arr_koordinat[6] + 50, arr_koordinat[7] + 70, arr_koordinat[6] + 50 + 10, arr_koordinat[7] + 70 + 49);
		Ellipse(hdc, arr_koordinat[6] + 70, arr_koordinat[7] + 70, arr_koordinat[6] + 70 + 10, arr_koordinat[7] + 70 + 48);
		Ellipse(hdc, arr_koordinat[6] + 85, arr_koordinat[7] + 70, arr_koordinat[6] + 85 + 10, arr_koordinat[7] + 70 + 38);

		//Красный круг
		pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		brush = CreateSolidBrush(RGB(255, 0, 0));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[6] + 30, arr_koordinat[7] + 50, arr_koordinat[6] + 30 + 65, arr_koordinat[7] + 50 + 30);

		//Семки черные
		pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		brush = CreateSolidBrush(RGB(0, 0, 0));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[6] + 40, arr_koordinat[7] + 55, arr_koordinat[6] + 40 + 4, arr_koordinat[7] + 55 + 4);
		Ellipse(hdc, arr_koordinat[6] + 50, arr_koordinat[7] + 60, arr_koordinat[6] + 50 + 4, arr_koordinat[7] + 60 + 4);
		Ellipse(hdc, arr_koordinat[6] + 70, arr_koordinat[7] + 60, arr_koordinat[6] + 70 + 4, arr_koordinat[7] + 60 + 4);
		Ellipse(hdc, arr_koordinat[6] + 65, arr_koordinat[7] + 55, arr_koordinat[6] + 65 + 4, arr_koordinat[7] + 55 + 4);
		Ellipse(hdc, arr_koordinat[6] + 75, arr_koordinat[7] + 70, arr_koordinat[6] + 75 + 4, arr_koordinat[7] + 70 + 4);
		Ellipse(hdc, arr_koordinat[6] + 60, arr_koordinat[7] + 70, arr_koordinat[6] + 60 + 4, arr_koordinat[7] + 70 + 4);
		Ellipse(hdc, arr_koordinat[6] + 85, arr_koordinat[7] + 60, arr_koordinat[6] + 85 + 4, arr_koordinat[7] + 60 + 4);
		Ellipse(hdc, arr_koordinat[6] + 45, arr_koordinat[7] + 70, arr_koordinat[6] + 45 + 4, arr_koordinat[7] + 70 + 4);
		DeleteObject(brush);
		DeleteObject(pen);

		//Рисовка для след карточек
		pen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
		brush = CreateSolidBrush(RGB(127, 127, 127));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
	}
	else {}

	////////// Карта 1.5
	//Закрыта
	if (arr_kart[data[4]] == 1)
		Rectangle(hdc, arr_koordinat[8], arr_koordinat[9], arr_koordinat[8] + width_kart, arr_koordinat[9] + height_kart);

	//Апельсин
	else if (arr_kart[data[4]] == 2)
	{
		//Фон
		brush = CreateSolidBrush(RGB(78, 182, 169));
		SelectObject(hdc, brush);
		Rectangle(hdc, arr_koordinat[8], arr_koordinat[9], arr_koordinat[8] + width_kart, arr_koordinat[9] + height_kart);

		//Оранжевый круг
		brush = CreateSolidBrush(RGB(255, 100, 0));
		pen = CreatePen(PS_SOLID, 1, RGB(255, 100, 0));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[8] + 35, arr_koordinat[9] + 50, arr_koordinat[8] + 35 + 50, arr_koordinat[9] + 50 + 50);

		//Точка на апельсине
		brush = CreateSolidBrush(RGB(90, 35, 0));
		pen = CreatePen(PS_SOLID, 1, RGB(90, 35, 0));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[8] + 65, arr_koordinat[9] + 60, arr_koordinat[8] + 65 + 5, arr_koordinat[9] + 60 + 5);
		DeleteObject(brush);
		DeleteObject(pen);

		//Рисовка для след карточек
		pen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
		brush = CreateSolidBrush(RGB(127, 127, 127));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
	}
	else {}


	////////////////////////////// РЯД 2

	////////// Карта 2.1
	//Закрыта
	if (arr_kart[data[5]] == 1)
		Rectangle(hdc, arr_koordinat[10], arr_koordinat[11], arr_koordinat[10] + width_kart, arr_koordinat[11] + height_kart);

	//Апельсин
	else if (arr_kart[data[5]] == 2)
	{
		//Фон
		brush = CreateSolidBrush(RGB(78, 182, 169));
		SelectObject(hdc, brush);
		Rectangle(hdc, arr_koordinat[10], arr_koordinat[11], arr_koordinat[10] + width_kart, arr_koordinat[11] + height_kart);

		//Оранжевый круг
		brush = CreateSolidBrush(RGB(255, 100, 0));
		pen = CreatePen(PS_SOLID, 1, RGB(255, 100, 0));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[10] + 35, arr_koordinat[11] + 50, arr_koordinat[10] + 35 + 50, arr_koordinat[11] + 50 + 50);

		//Точка на апельсине
		brush = CreateSolidBrush(RGB(90, 35, 0));
		pen = CreatePen(PS_SOLID, 1, RGB(90, 35, 0));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[10] + 65, arr_koordinat[11] + 60, arr_koordinat[10] + 65 + 5, arr_koordinat[11] + 60 + 5);
		DeleteObject(brush);
		DeleteObject(pen);

		//Рисовка для след карточек
		pen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
		brush = CreateSolidBrush(RGB(127, 127, 127));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
	}
	else {}

	////////// Карта 2.2
	//Закрыта
	if (arr_kart[data[6]] == 1)
		Rectangle(hdc, arr_koordinat[12], arr_koordinat[13], arr_koordinat[12] + width_kart, arr_koordinat[13] + height_kart);

	//Яйцо
	else if (arr_kart[data[6]] == 2)
	{
		//Фон
		brush = CreateSolidBrush(RGB(78, 182, 169));
		SelectObject(hdc, brush);
		Rectangle(hdc, arr_koordinat[12], arr_koordinat[13], arr_koordinat[12] + width_kart, arr_koordinat[13] + height_kart);

		//Бежевый овал
		brush = CreateSolidBrush(RGB(255, 200, 160));
		pen = CreatePen(PS_SOLID, 1, RGB(255, 200, 160));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[12] + 35, arr_koordinat[13] + 50, arr_koordinat[12] + 35 + 50, arr_koordinat[13] + 50 + 70);
		DeleteObject(pen);
		DeleteObject(brush);

		//Рисовка для след карточек
		pen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
		brush = CreateSolidBrush(RGB(127, 127, 127));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
	}
	else {}

	////////// Карта 2.3
	//Закрыта
	if (arr_kart[data[7]] == 1)
		Rectangle(hdc, arr_koordinat[14], arr_koordinat[15], arr_koordinat[14] + width_kart, arr_koordinat[15] + height_kart);

	//Яйцо
	else if (arr_kart[data[7]] == 2)
	{
		//Фон
		brush = CreateSolidBrush(RGB(78, 182, 169));
		SelectObject(hdc, brush);
		Rectangle(hdc, arr_koordinat[14], arr_koordinat[15], arr_koordinat[14] + width_kart, arr_koordinat[15] + height_kart);

		//Бежевый овал
		brush = CreateSolidBrush(RGB(255, 200, 160));
		pen = CreatePen(PS_SOLID, 1, RGB(255, 200, 160));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[14] + 35, arr_koordinat[15] + 50, arr_koordinat[14] + 35 + 50, arr_koordinat[15] + 50 + 70);
		DeleteObject(pen);
		DeleteObject(brush);

		//Рисовка для след карточек
		pen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
		brush = CreateSolidBrush(RGB(127, 127, 127));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
	}
	else {}

	////////// Карта 2.4
	//Закрыта
	if (arr_kart[data[8]] == 1)
		Rectangle(hdc, arr_koordinat[16], arr_koordinat[17], arr_koordinat[16] + width_kart, arr_koordinat[17] + height_kart);

	//Картошка
	else if (arr_kart[data[8]] == 2)
	{
		//Фон
		brush = CreateSolidBrush(RGB(78, 182, 169));
		SelectObject(hdc, brush);
		Rectangle(hdc, arr_koordinat[16], arr_koordinat[17], arr_koordinat[16] + width_kart, arr_koordinat[17] + height_kart);

		//Коричневый овал
		brush = CreateSolidBrush(RGB(110, 75, 30));
		pen = CreatePen(PS_SOLID, 1, RGB(110, 75, 30));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[16] + 30, arr_koordinat[17] + 55, arr_koordinat[16] + 30 + 60, arr_koordinat[17] + 55 + 40);

		//корешки феолетовые
		pen = CreatePen(PS_SOLID, 1, RGB(240, 150, 150));
		brush = CreateSolidBrush(RGB(120, 15, 115));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[16] + 40, arr_koordinat[17] + 65, arr_koordinat[16] + 40 + 5, arr_koordinat[17] + 65 + 5);
		Ellipse(hdc, arr_koordinat[16] + 45, arr_koordinat[17] + 70, arr_koordinat[16] + 45 + 5, arr_koordinat[17] + 70 + 5);
		Ellipse(hdc, arr_koordinat[16] + 45, arr_koordinat[17] + 60, arr_koordinat[16] + 45 + 5, arr_koordinat[17] + 60 + 5);
		DeleteObject(brush);
		DeleteObject(pen);

		//Рисовка для след карточек
		pen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
		brush = CreateSolidBrush(RGB(127, 127, 127));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
	}
	else {}

	////////// Карта 2.5
	//Закрыта
	if (arr_kart[data[9]] == 1)
		Rectangle(hdc, arr_koordinat[18], arr_koordinat[19], arr_koordinat[18] + width_kart, arr_koordinat[19] + height_kart);

	//Картошка
	else if (arr_kart[data[9]] == 2)
	{
		//Фон
		brush = CreateSolidBrush(RGB(78, 182, 169));
		SelectObject(hdc, brush);
		Rectangle(hdc, arr_koordinat[18], arr_koordinat[19], arr_koordinat[18] + width_kart, arr_koordinat[19] + height_kart);

		//Коричневый овал
		brush = CreateSolidBrush(RGB(110, 75, 30));
		pen = CreatePen(PS_SOLID, 1, RGB(110, 75, 30));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[18] + 30, arr_koordinat[19] + 55, arr_koordinat[18] + 30 + 60, arr_koordinat[19] + 55 + 40);

		//корешки феолетовые
		pen = CreatePen(PS_SOLID, 1, RGB(240, 150, 150));
		brush = CreateSolidBrush(RGB(120, 15, 115));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[18] + 40, arr_koordinat[19] + 65, arr_koordinat[18] + 40 + 5, arr_koordinat[19] + 65 + 5);
		Ellipse(hdc, arr_koordinat[18] + 45, arr_koordinat[19] + 70, arr_koordinat[18] + 45 + 5, arr_koordinat[19] + 70 + 5);
		Ellipse(hdc, arr_koordinat[18] + 45, arr_koordinat[19] + 60, arr_koordinat[18] + 45 + 5, arr_koordinat[19] + 60 + 5);
		DeleteObject(brush);
		DeleteObject(pen);

		//Рисовка для след карточек
		pen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
		brush = CreateSolidBrush(RGB(127, 127, 127));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
	}
	else {}


	////////////////////////////// РЯД 3

	////////// Карта 3.1
	//Закрыта
	if (arr_kart[data[10]] == 1)
		Rectangle(hdc, arr_koordinat[20], arr_koordinat[21], arr_koordinat[20] + width_kart, arr_koordinat[21] + height_kart);

	//Кокос
	else if (arr_kart[data[10]] == 2)
	{
		//Фон
		brush = CreateSolidBrush(RGB(78, 182, 169));
		SelectObject(hdc, brush);
		Rectangle(hdc, arr_koordinat[20], arr_koordinat[21], arr_koordinat[20] + width_kart, arr_koordinat[21] + height_kart);

		//Коричневый круг
		brush = CreateSolidBrush(RGB(100, 55, 35));
		pen = CreatePen(PS_SOLID, 1, RGB(100, 55, 35));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[20] + 35, arr_koordinat[21] + 50, arr_koordinat[20] + 35 + 50, arr_koordinat[21] + 50 + 50);

		//Точки на кокосе
		brush = CreateSolidBrush(RGB(70, 35, 25));
		pen = CreatePen(PS_SOLID, 1, RGB(70, 35, 25));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[20] + 65, arr_koordinat[21] + 60, arr_koordinat[20] + 65 + 6, arr_koordinat[21] + 60 + 6);
		Ellipse(hdc, arr_koordinat[20] + 52, arr_koordinat[21] + 60, arr_koordinat[20] + 52 + 6, arr_koordinat[21] + 60 + 6);
		Ellipse(hdc, arr_koordinat[20] + 58, arr_koordinat[21] + 65, arr_koordinat[20] + 58 + 6, arr_koordinat[21] + 65 + 6);
		DeleteObject(pen);
		DeleteObject(brush);

		//Рисовка для след карточек
		pen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
		brush = CreateSolidBrush(RGB(127, 127, 127));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
	}
	else {}

	////////// Карта 3.2
	//Закрыта
	if (arr_kart[data[11]] == 1)
		Rectangle(hdc, arr_koordinat[22], arr_koordinat[23], arr_koordinat[22] + width_kart, arr_koordinat[23] + height_kart);

	//Кокос
	else if (arr_kart[data[11]] == 2)
	{
		//Фон
		brush = CreateSolidBrush(RGB(78, 182, 169));
		SelectObject(hdc, brush);
		Rectangle(hdc, arr_koordinat[22], arr_koordinat[23], arr_koordinat[22] + width_kart, arr_koordinat[23] + height_kart);

		//Коричневый круг
		brush = CreateSolidBrush(RGB(100, 55, 35));
		pen = CreatePen(PS_SOLID, 1, RGB(100, 55, 35));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[22] + 35, arr_koordinat[23] + 50, arr_koordinat[22] + 35 + 50, arr_koordinat[23] + 50 + 50);

		//Точки на кокосе
		brush = CreateSolidBrush(RGB(70, 35, 25));
		pen = CreatePen(PS_SOLID, 1, RGB(70, 35, 25));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[22] + 65, arr_koordinat[23] + 60, arr_koordinat[22] + 65 + 6, arr_koordinat[23] + 60 + 6);
		Ellipse(hdc, arr_koordinat[22] + 52, arr_koordinat[23] + 60, arr_koordinat[22] + 52 + 6, arr_koordinat[23] + 60 + 6);
		Ellipse(hdc, arr_koordinat[22] + 58, arr_koordinat[23] + 65, arr_koordinat[22] + 58 + 6, arr_koordinat[23] + 65 + 6);
		DeleteObject(pen);
		DeleteObject(brush);

		//Рисовка для след карточек
		pen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
		brush = CreateSolidBrush(RGB(127, 127, 127));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
	}
	else {}

	////////// Карта 3.3
	//Закрыта
	if (arr_kart[data[12]] == 1)
		Rectangle(hdc, arr_koordinat[24], arr_koordinat[25], arr_koordinat[24] + width_kart, arr_koordinat[25] + height_kart);

	//Помидор
	else if (arr_kart[data[12]] == 2)
	{
		//Фон
		brush = CreateSolidBrush(RGB(78, 182, 169));
		SelectObject(hdc, brush);
		Rectangle(hdc, arr_koordinat[24], arr_koordinat[25], arr_koordinat[24] + width_kart, arr_koordinat[25] + height_kart);

		//Красный круг
		brush = CreateSolidBrush(RGB(255, 50, 50));
		pen = CreatePen(PS_SOLID, 1, RGB(255, 50, 50));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[24] + 35, arr_koordinat[25] + 50, arr_koordinat[24] + 35 + 50, arr_koordinat[25] + 50 + 50);

		//Зеленый квадрат
		brush = CreateSolidBrush(RGB(0, 110, 30));
		pen = CreatePen(PS_SOLID, 1, RGB(0, 110, 30));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Rectangle(hdc, arr_koordinat[24] + 60, arr_koordinat[25] + 55, arr_koordinat[24] + 60 + 5, arr_koordinat[25] + 55 + 15);
		Rectangle(hdc, arr_koordinat[24] + 55, arr_koordinat[25] + 60, arr_koordinat[24] + 55 + 15, arr_koordinat[25] + 60 + 5);
		DeleteObject(pen);
		DeleteObject(brush);

		//Рисовка для след карточек
		pen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
		brush = CreateSolidBrush(RGB(127, 127, 127));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
	}
	else {}

	////////// Карта 3.4
	//Закрыта
	if (arr_kart[data[13]] == 1)
		Rectangle(hdc, arr_koordinat[26], arr_koordinat[27], arr_koordinat[26] + width_kart, arr_koordinat[27] + height_kart);

	//Помидор
	else if (arr_kart[data[13]] == 2)
	{
		//Фон
		brush = CreateSolidBrush(RGB(78, 182, 169));
		SelectObject(hdc, brush);
		Rectangle(hdc, arr_koordinat[26], arr_koordinat[27], arr_koordinat[26] + width_kart, arr_koordinat[27] + height_kart);

		//Красный круг
		brush = CreateSolidBrush(RGB(255, 50, 50));
		pen = CreatePen(PS_SOLID, 1, RGB(255, 50, 50));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[26] + 35, arr_koordinat[27] + 50, arr_koordinat[26] + 35 + 50, arr_koordinat[27] + 50 + 50);

		//Зеленый квадрат
		brush = CreateSolidBrush(RGB(0, 110, 30));
		pen = CreatePen(PS_SOLID, 1, RGB(0, 110, 30));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Rectangle(hdc, arr_koordinat[26] + 60, arr_koordinat[27] + 55, arr_koordinat[26] + 60 + 5, arr_koordinat[27] + 55 + 15);
		Rectangle(hdc, arr_koordinat[26] + 55, arr_koordinat[27] + 60, arr_koordinat[26] + 55 + 15, arr_koordinat[27] + 60 + 5);
		DeleteObject(pen);
		DeleteObject(brush);

		//Рисовка для след карточек
		pen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
		brush = CreateSolidBrush(RGB(127, 127, 127));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
	}
	else {}

	////////// Карта 3.5
	//Закрыта
	if (arr_kart[data[14]] == 1)
		Rectangle(hdc, arr_koordinat[28], arr_koordinat[29], arr_koordinat[28] + width_kart, arr_koordinat[29] + height_kart);

	//Банан
	else if (arr_kart[data[14]] == 2)
	{
		//Фон
		brush = CreateSolidBrush(RGB(78, 182, 169));
		SelectObject(hdc, brush);
		Rectangle(hdc, arr_koordinat[28], arr_koordinat[29], arr_koordinat[28] + width_kart, arr_koordinat[29] + height_kart);

		//Желтый овал
		pen = CreatePen(PS_SOLID, 1, RGB(225, 225, 0));
		brush = CreateSolidBrush(RGB(225, 225, 0));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[28] + 35, arr_koordinat[29] + 30, arr_koordinat[28] + 35 + 60, arr_koordinat[29] + 30 + 80);

		//Круг цвет фона 
		brush = CreateSolidBrush(RGB(78, 182, 169));
		pen = CreatePen(PS_SOLID, 1, RGB(78, 182, 169));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[28] + 60, arr_koordinat[29] + 30, arr_koordinat[28] + 60 + 35, arr_koordinat[29] + 30 + 80);

		//Хвостик коричневый  
		brush = CreateSolidBrush(RGB(97, 30, 30));
		pen = CreatePen(PS_SOLID, 1, RGB(97, 30, 30));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Rectangle(hdc, arr_koordinat[28] + 70, arr_koordinat[29] + 106, arr_koordinat[28] + 70 + 8, arr_koordinat[29] + 106 + 5);

		//Кончик черный 
		brush = CreateSolidBrush(RGB(0, 0, 0));
		pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Rectangle(hdc, arr_koordinat[28] + 70, arr_koordinat[29] + 30, arr_koordinat[28] + 70 + 4, arr_koordinat[29] + 30 + 4);
		DeleteObject(pen);
		DeleteObject(brush);

		//Рисовка для след карточек 
		pen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
		brush = CreateSolidBrush(RGB(127, 127, 127));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
	}
	else {}


	////////////////////////////// РЯД 4

	////////// Карта 4.1
		//Закрыта
	if (arr_kart[data[15]] == 1)
		Rectangle(hdc, arr_koordinat[30], arr_koordinat[31], arr_koordinat[30] + width_kart, arr_koordinat[31] + height_kart);

	//Банан
	else if (arr_kart[data[15]] == 2)
	{
		//Фон
		brush = CreateSolidBrush(RGB(78, 182, 169));
		SelectObject(hdc, brush);
		Rectangle(hdc, arr_koordinat[30], arr_koordinat[31], arr_koordinat[30] + width_kart, arr_koordinat[31] + height_kart);

		//Желтый овал
		pen = CreatePen(PS_SOLID, 1, RGB(225, 225, 0));
		brush = CreateSolidBrush(RGB(225, 225, 0));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[30] + 35, arr_koordinat[31] + 30, arr_koordinat[30] + 35 + 60, arr_koordinat[31] + 30 + 80);

		//Круг цвет фона 
		brush = CreateSolidBrush(RGB(78, 182, 169));
		pen = CreatePen(PS_SOLID, 1, RGB(78, 182, 169));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[30] + 60, arr_koordinat[31] + 30, arr_koordinat[30] + 60 + 35, arr_koordinat[31] + 30 + 80);

		//Хвостик коричневый  
		brush = CreateSolidBrush(RGB(97, 30, 30));
		pen = CreatePen(PS_SOLID, 1, RGB(97, 30, 30));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Rectangle(hdc, arr_koordinat[30] + 70, arr_koordinat[31] + 106, arr_koordinat[30] + 70 + 8, arr_koordinat[31] + 106 + 5);

		//Кончик черный 
		brush = CreateSolidBrush(RGB(0, 0, 0));
		pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Rectangle(hdc, arr_koordinat[30] + 70, arr_koordinat[31] + 30, arr_koordinat[30] + 70 + 4, arr_koordinat[31] + 30 + 4);
		DeleteObject(pen);
		DeleteObject(brush);

		//Рисовка для след карточек 
		pen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
		brush = CreateSolidBrush(RGB(127, 127, 127));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
	}
	else {}

	////////// Карта 4.2
	//Закрыта
	if (arr_kart[data[16]] == 1)
		Rectangle(hdc, arr_koordinat[32], arr_koordinat[33], arr_koordinat[32] + width_kart, arr_koordinat[33] + height_kart);

	//Морковь
	else if (arr_kart[data[16]] == 2)
	{
		//Фон
		brush = CreateSolidBrush(RGB(78, 182, 169));
		SelectObject(hdc, brush);
		Rectangle(hdc, arr_koordinat[32], arr_koordinat[33], arr_koordinat[32] + width_kart, arr_koordinat[33] + height_kart);

		//Оранжевый прямоугольник
		pen = CreatePen(PS_SOLID, 1, RGB(230, 115, 0));
		brush = CreateSolidBrush(RGB(230, 115, 0));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Rectangle(hdc, arr_koordinat[32] + 50, arr_koordinat[33] + 40, arr_koordinat[32] + 50 + 25, arr_koordinat[33] + 40 + 70);

		//Прямоугольники цвет фона 
		brush = CreateSolidBrush(RGB(78, 182, 169));
		pen = CreatePen(PS_SOLID, 1, RGB(78, 182, 169));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Rectangle(hdc, arr_koordinat[32] + 68, arr_koordinat[33] + 90, arr_koordinat[32] + 68 + 20, arr_koordinat[33] + 90 + 20);
		Rectangle(hdc, arr_koordinat[32] + 38, arr_koordinat[33] + 90, arr_koordinat[32] + 38 + 20, arr_koordinat[33] + 90 + 20);
		Rectangle(hdc, arr_koordinat[32] + 35, arr_koordinat[33] + 70, arr_koordinat[32] + 35 + 20, arr_koordinat[33] + 70 + 20);
		Rectangle(hdc, arr_koordinat[32] + 71, arr_koordinat[33] + 70, arr_koordinat[32] + 71 + 20, arr_koordinat[33] + 70 + 20);
		Rectangle(hdc, arr_koordinat[32] + 73, arr_koordinat[33] + 50, arr_koordinat[32] + 73 + 20, arr_koordinat[33] + 50 + 20);
		Rectangle(hdc, arr_koordinat[32] + 33, arr_koordinat[33] + 50, arr_koordinat[32] + 33 + 20, arr_koordinat[33] + 50 + 20);

		//Прямоугольник зеленый 
		brush = CreateSolidBrush(RGB(0, 164, 0));
		pen = CreatePen(PS_SOLID, 1, RGB(0, 164, 0));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Rectangle(hdc, arr_koordinat[32] + 57, arr_koordinat[33] + 20, arr_koordinat[32] + 57 + 10, arr_koordinat[33] + 20 + 20);
		DeleteObject(pen);
		DeleteObject(brush);

		//Рисовка для след карточек 
		pen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
		brush = CreateSolidBrush(RGB(127, 127, 127));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
	}
	else {}

	////////// Карта 4.3
	//Закрыта
	if (arr_kart[data[17]] == 1)
		Rectangle(hdc, arr_koordinat[34], arr_koordinat[35], arr_koordinat[34] + width_kart, arr_koordinat[35] + height_kart);

	//Морковь
	else if (arr_kart[data[17]] == 2)
	{
		//Фон
		brush = CreateSolidBrush(RGB(78, 182, 169));
		SelectObject(hdc, brush);
		Rectangle(hdc, arr_koordinat[34], arr_koordinat[35], arr_koordinat[34] + width_kart, arr_koordinat[35] + height_kart);

		//Оранжевый прямоугольник
		pen = CreatePen(PS_SOLID, 1, RGB(230, 115, 0));
		brush = CreateSolidBrush(RGB(230, 115, 0));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Rectangle(hdc, arr_koordinat[34] + 50, arr_koordinat[35] + 40, arr_koordinat[34] + 50 + 25, arr_koordinat[35] + 40 + 70);

		//Прямоугольники цвет фона 
		brush = CreateSolidBrush(RGB(78, 182, 169));
		pen = CreatePen(PS_SOLID, 1, RGB(78, 182, 169));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Rectangle(hdc, arr_koordinat[34] + 68, arr_koordinat[35] + 90, arr_koordinat[34] + 68 + 20, arr_koordinat[35] + 90 + 20);
		Rectangle(hdc, arr_koordinat[34] + 38, arr_koordinat[35] + 90, arr_koordinat[34] + 38 + 20, arr_koordinat[35] + 90 + 20);
		Rectangle(hdc, arr_koordinat[34] + 35, arr_koordinat[35] + 70, arr_koordinat[34] + 35 + 20, arr_koordinat[35] + 70 + 20);
		Rectangle(hdc, arr_koordinat[34] + 71, arr_koordinat[35] + 70, arr_koordinat[34] + 71 + 20, arr_koordinat[35] + 70 + 20);
		Rectangle(hdc, arr_koordinat[34] + 73, arr_koordinat[35] + 50, arr_koordinat[34] + 73 + 20, arr_koordinat[35] + 50 + 20);
		Rectangle(hdc, arr_koordinat[34] + 33, arr_koordinat[35] + 50, arr_koordinat[34] + 33 + 20, arr_koordinat[35] + 50 + 20);

		//Прямоугольник зеленый 
		brush = CreateSolidBrush(RGB(0, 164, 0));
		pen = CreatePen(PS_SOLID, 1, RGB(0, 164, 0));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Rectangle(hdc, arr_koordinat[34] + 57, arr_koordinat[35] + 20, arr_koordinat[34] + 57 + 10, arr_koordinat[35] + 20 + 20);
		DeleteObject(pen);
		DeleteObject(brush);

		//Рисовка для след карточек 
		pen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
		brush = CreateSolidBrush(RGB(127, 127, 127));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
	}
	else {}

	////////// Карта 4.4
	//Закрыта
	if (arr_kart[data[18]] == 1)
		Rectangle(hdc, arr_koordinat[36], arr_koordinat[37], arr_koordinat[36] + width_kart, arr_koordinat[37] + height_kart);

	//Арбуз
	else if (arr_kart[data[18]] == 2)
	{
		//Фон
		brush = CreateSolidBrush(RGB(78, 182, 169));
		SelectObject(hdc, brush);
		Rectangle(hdc, arr_koordinat[36], arr_koordinat[37], arr_koordinat[36] + width_kart, arr_koordinat[37] + height_kart);

		//Зеленый Круг
		brush = CreateSolidBrush(RGB(255, 255, 150));
		pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 150));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[36] + 22, arr_koordinat[37] + 50, arr_koordinat[36] + 22 + 80, arr_koordinat[37] + 50 + 70);

		//Полосы на арбузе
		pen = CreatePen(PS_SOLID, 1, RGB(210, 210, 0));
		brush = CreateSolidBrush(RGB(210, 210, 0));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[36] + 30, arr_koordinat[37] + 70, arr_koordinat[36] + 30 + 10, arr_koordinat[37] + 70 + 40);
		Ellipse(hdc, arr_koordinat[36] + 50, arr_koordinat[37] + 70, arr_koordinat[36] + 50 + 10, arr_koordinat[37] + 70 + 49);
		Ellipse(hdc, arr_koordinat[36] + 70, arr_koordinat[37] + 70, arr_koordinat[36] + 70 + 10, arr_koordinat[37] + 70 + 48);
		Ellipse(hdc, arr_koordinat[36] + 85, arr_koordinat[37] + 70, arr_koordinat[36] + 85 + 10, arr_koordinat[37] + 70 + 38);

		//Красный круг
		pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 120));
		brush = CreateSolidBrush(RGB(255, 255, 120));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[36] + 30, arr_koordinat[37] + 50, arr_koordinat[36] + 30 + 65, arr_koordinat[37] + 50 + 30);

		//Семки черные
		pen = CreatePen(PS_SOLID, 1, RGB(180, 180, 0));
		brush = CreateSolidBrush(RGB(180, 180, 0));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[36] + 40, arr_koordinat[37] + 55, arr_koordinat[36] + 40 + 4, arr_koordinat[37] + 55 + 4);
		Ellipse(hdc, arr_koordinat[36] + 50, arr_koordinat[37] + 60, arr_koordinat[36] + 50 + 4, arr_koordinat[37] + 60 + 4);
		Ellipse(hdc, arr_koordinat[36] + 70, arr_koordinat[37] + 60, arr_koordinat[36] + 70 + 4, arr_koordinat[37] + 60 + 4);
		Ellipse(hdc, arr_koordinat[36] + 65, arr_koordinat[37] + 55, arr_koordinat[36] + 65 + 4, arr_koordinat[37] + 55 + 4);
		Ellipse(hdc, arr_koordinat[36] + 75, arr_koordinat[37] + 70, arr_koordinat[36] + 75 + 4, arr_koordinat[37] + 70 + 4);
		Ellipse(hdc, arr_koordinat[36] + 60, arr_koordinat[37] + 70, arr_koordinat[36] + 60 + 4, arr_koordinat[37] + 70 + 4);
		Ellipse(hdc, arr_koordinat[36] + 85, arr_koordinat[37] + 60, arr_koordinat[36] + 85 + 4, arr_koordinat[37] + 60 + 4);
		Ellipse(hdc, arr_koordinat[36] + 45, arr_koordinat[37] + 70, arr_koordinat[36] + 45 + 4, arr_koordinat[37] + 70 + 4);
		DeleteObject(brush);
		DeleteObject(pen);

		//Рисовка для след карточек
		pen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
		brush = CreateSolidBrush(RGB(127, 127, 127));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
	}
	else {}

	////////// Карта 4.5
		//Закрыта
	if (arr_kart[data[19]] == 1)
		Rectangle(hdc, arr_koordinat[38], arr_koordinat[39], arr_koordinat[38] + width_kart, arr_koordinat[39] + height_kart);

	//Арбуз
	else if (arr_kart[data[19]] == 2)
	{
		//Фон
		brush = CreateSolidBrush(RGB(78, 182, 169));
		SelectObject(hdc, brush);
		Rectangle(hdc, arr_koordinat[38], arr_koordinat[39], arr_koordinat[38] + width_kart, arr_koordinat[39] + height_kart);

		//Зеленый Круг
		brush = CreateSolidBrush(RGB(255, 255, 150));
		pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 150));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[38] + 22, arr_koordinat[39] + 50, arr_koordinat[38] + 22 + 80, arr_koordinat[39] + 50 + 70);

		//Полосы на арбузе
		pen = CreatePen(PS_SOLID, 1, RGB(210, 210, 0));
		brush = CreateSolidBrush(RGB(210, 210, 0));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[38] + 30, arr_koordinat[39] + 70, arr_koordinat[38] + 30 + 10, arr_koordinat[39] + 70 + 40);
		Ellipse(hdc, arr_koordinat[38] + 50, arr_koordinat[39] + 70, arr_koordinat[38] + 50 + 10, arr_koordinat[39] + 70 + 49);
		Ellipse(hdc, arr_koordinat[38] + 70, arr_koordinat[39] + 70, arr_koordinat[38] + 70 + 10, arr_koordinat[39] + 70 + 48);
		Ellipse(hdc, arr_koordinat[38] + 85, arr_koordinat[39] + 70, arr_koordinat[38] + 85 + 10, arr_koordinat[39] + 70 + 38);

		//Красный круг
		pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 120));
		brush = CreateSolidBrush(RGB(255, 255, 120));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[38] + 30, arr_koordinat[39] + 50, arr_koordinat[38] + 30 + 65, arr_koordinat[39] + 50 + 30);

		//Семки черные
		pen = CreatePen(PS_SOLID, 1, RGB(180, 180, 0));
		brush = CreateSolidBrush(RGB(180, 180, 0));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		Ellipse(hdc, arr_koordinat[38] + 40, arr_koordinat[39] + 55, arr_koordinat[38] + 40 + 4, arr_koordinat[39] + 55 + 4);
		Ellipse(hdc, arr_koordinat[38] + 50, arr_koordinat[39] + 60, arr_koordinat[38] + 50 + 4, arr_koordinat[39] + 60 + 4);
		Ellipse(hdc, arr_koordinat[38] + 70, arr_koordinat[39] + 60, arr_koordinat[38] + 70 + 4, arr_koordinat[39] + 60 + 4);
		Ellipse(hdc, arr_koordinat[38] + 65, arr_koordinat[39] + 55, arr_koordinat[38] + 65 + 4, arr_koordinat[39] + 55 + 4);
		Ellipse(hdc, arr_koordinat[38] + 75, arr_koordinat[39] + 70, arr_koordinat[38] + 75 + 4, arr_koordinat[39] + 70 + 4);
		Ellipse(hdc, arr_koordinat[38] + 60, arr_koordinat[39] + 70, arr_koordinat[38] + 60 + 4, arr_koordinat[39] + 70 + 4);
		Ellipse(hdc, arr_koordinat[38] + 85, arr_koordinat[39] + 60, arr_koordinat[38] + 85 + 4, arr_koordinat[39] + 60 + 4);
		Ellipse(hdc, arr_koordinat[38] + 45, arr_koordinat[39] + 70, arr_koordinat[38] + 45 + 4, arr_koordinat[39] + 70 + 4);
		DeleteObject(brush);
		DeleteObject(pen);

		//Рисовка для след карточек
		pen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
		brush = CreateSolidBrush(RGB(127, 127, 127));
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
	}
	else {}

	////////////////////////////////////////////////////

	//Проверяет победу
	pobeda(arr_kart);

	//Удаляет угаданные карты
	dell_kart(arr_koordinat, arr_kart, data);

	DeleteObject(brush);
	DeleteObject(pen);
	mish(arr_koordinat, arr_kart, data);
	Sleep(INFINITE);
}
//Работа с мышкой
void mish(int arr_koordinat[40], int arr_kart[20], int data[20])
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); // дескриптор окна
	COORD c; // переменная, отвечающая за координаты в консоли

	HANDLE hin = GetStdHandle(STD_INPUT_HANDLE); // дескриптор окна для работы с мышкой
	SetConsoleMode(hin, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS); // установка режима использования мышки

	const int events_count = 256;
	INPUT_RECORD all_events[events_count]; // массив событий, произошедших в консоли
	DWORD read_event; // переменная, в которую запишется количество произошедших событий
	int arr_i[20] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	while (true)
	{
		ReadConsoleInput(hin, all_events, events_count, &read_event); // получить все события, произошедшие в консоли
		for (int i = 0; i < read_event; i++)
		{

			//Запомнить координаты мышки
			c.X = all_events[i].Event.MouseEvent.dwMousePosition.X;
			c.Y = all_events[i].Event.MouseEvent.dwMousePosition.Y;

			//Если нажата ЛКМ

			////////////////////////////// РЯД 1
			////////// Карта 1.1
			if ((c.X > 3 && c.X < 19) && (c.Y > 0 && c.Y < 10) && all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{ arr_i[0]++; break; }
			////////// Карта 1.2
			if ((c.X > 22 && c.X < 37) && (c.Y > 0 && c.Y < 10) && all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{ arr_i[1]++; break; }
			////////// Карта 1.3
			if ((c.X > 41 && c.X < 56) && (c.Y > 0 && c.Y < 10) && all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{ arr_i[2]++; break; }
			////////// Карта 1.4
			if ((c.X > 59 && c.X < 75) && (c.Y > 0 && c.Y < 10) && all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{ arr_i[3]++; break; }
			////////// Карта 1.5
			if ((c.X > 78 && c.X < 93) && (c.Y > 0 && c.Y < 10) && all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{ arr_i[4]++; break; }
			
			////////////////////////////// РЯД 2
			////////// Карта 2.1
			if ((c.X > 3 && c.X < 18) && (c.Y > 11 && c.Y < 21) && all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{ arr_i[5]++; break; }
			////////// Карта 2.2
			if ((c.X > 22 && c.X < 37) && (c.Y > 11 && c.Y < 21) && all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{ arr_i[6]++; break; }
			////////// Карта 2.3
			if ((c.X > 41 && c.X < 56) && (c.Y > 11 && c.Y < 21) && all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{ arr_i[7]++; break; }
			////////// Карта 2.4
			if ((c.X > 59 && c.X < 75) && (c.Y > 11 && c.Y < 21) && all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{ arr_i[8]++; break; }
			////////// Карта 2.5
			if ((c.X > 78 && c.X < 93) && (c.Y > 11 && c.Y < 21) && all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{ arr_i[9]++; break; }

			////////////////////////////// РЯД 3
			////////// Карта 3.1
			if ((c.X > 3 && c.X < 18) && (c.Y > 22 && c.Y < 32) && all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{ arr_i[10]++; break; }
			////////// Карта 3.2
			if ((c.X > 22 && c.X < 37) && (c.Y > 22 && c.Y < 32) && all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{ arr_i[11]++; break; }
			////////// Карта 3.3
			if ((c.X > 41 && c.X < 56) && (c.Y > 22 && c.Y < 32) && all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{ arr_i[12]++; break; }
			////////// Карта 3.4
			if ((c.X > 59 && c.X < 75) && (c.Y > 22 && c.Y < 32) && all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{ arr_i[13]++; break; }
			////////// Карта 3.5
			if ((c.X > 78 && c.X < 93) && (c.Y > 22 && c.Y < 32) && all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{ arr_i[14]++; break; }

			////////////////////////////// РЯД 4
			////////// Карта 4.1
			if ((c.X > 3 && c.X < 18) && (c.Y > 34 && c.Y < 44) && all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{ arr_i[15]++; break; }
			////////// Карта 4.2
			if ((c.X > 22 && c.X < 37) && (c.Y > 34 && c.Y < 44) && all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{ arr_i[16]++; break; }
			////////// Карта 4.3
			if ((c.X > 41 && c.X < 56) && (c.Y > 34 && c.Y < 44) && all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{ arr_i[17]++; break; }
			////////// Карта 4.4
			if ((c.X > 59 && c.X < 75) && (c.Y > 34 && c.Y < 44) && all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{ arr_i[18]++; break; }
			////////// Карта 4.5
			if ((c.X > 78 && c.X < 93) && (c.Y > 34 && c.Y < 44) && all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{ arr_i[19]++; break; }
		}

		//----Проверка клика на карту
		for (int i = 0; i <= 19; i++)
		{
			if (arr_i[data[i]] == 1)
			{
				arr_kart[data[i]] = 2;
				t++;
				kartinki(arr_koordinat, arr_kart, data);
			}
		}
	}
}