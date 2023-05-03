#include "beblioteca.h"
#include "Bass.h"
#include "Karti.h"
#pragma comment(lib, "bass.lib")
#pragma comment(lib,"msimg32.lib")

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
enum Colors { DARK_GREEN = 3, GREEN = 6 };
enum Keys { ENTER = 13, ESCAPE = 27, SPACE = 32, LEFT = 75, RIGHT = 77, DOWN = 80, UP = 72 };

//// Переменные и массивы для подсчета рекорда и вывода его на экран
//Массив врмени для рекорда
int ar_rec[300] = {1,};
//Массив имен для рекорда
string ar_rec_name[100] = {"1",};
//Cчитает как выводить рекорд если он не 1;
int e = 0;
int e1 = 1;
//Переменая для записи времени вначале игры
int rec_start_time;
//Переменая для записи дня вначале игры
int rec_start_day;

///////////////Прототипы функций
//Меню при старте
void menu();
//Меню после победы
void posle_pobedi();
//Меню рекорды
void records();
//Получает системное время (конец игры) и считает результат
void sistem_time_end();
//Выводит рекорд в конце
void show_record_end();
//Меню рекорды
void records();


///////////////Различные функции
//Чистит экран консоли
void clear()
{
    COORD topLeft = { 0, 0 };
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    FillConsoleOutputAttribute(
        console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    SetConsoleCursorPosition(console, topLeft);
}
//Рандомно заполняет карты
void random_kart()
{
    const int koordinat_size = 20;

    int data[koordinat_size] =
    {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19
    };

    int left_koordinat[koordinat_size] =
    {
        30, 180, 330, 480, 630,
        30, 180, 330, 480, 630,
        30, 180, 330, 480, 630,
        30, 180, 330, 480, 630
    };

    int top_koordinat[koordinat_size] =
    {
        10, 10, 10, 10, 10,
        190, 190, 190, 190, 190,
        370, 370, 370, 370, 370,
        550, 550, 550, 550, 550
    };

    //Перемешивает 20 чисел массив data
    srand(time(0));
    for (int i = 0; i < koordinat_size; ++i)
    {
        swap(data[i], data[rand() % koordinat_size]);
    }

    //Массив координат для карт
    int arr_koordinat[40] =
    {
        left_koordinat[data[0]], top_koordinat[data[0]], left_koordinat[data[1]], top_koordinat[data[1]], left_koordinat[data[2]], top_koordinat[data[2]],
        left_koordinat[data[3]], top_koordinat[data[3]], left_koordinat[data[4]], top_koordinat[data[4]], left_koordinat[data[5]], top_koordinat[data[5]],
        left_koordinat[data[6]], top_koordinat[data[6]], left_koordinat[data[7]], top_koordinat[data[7]], left_koordinat[data[8]], top_koordinat[data[8]],
        left_koordinat[data[9]], top_koordinat[data[9]], left_koordinat[data[10]], top_koordinat[data[10]], left_koordinat[data[11]], top_koordinat[data[11]],
        left_koordinat[data[12]], top_koordinat[data[12]], left_koordinat[data[13]], top_koordinat[data[13]], left_koordinat[data[14]], top_koordinat[data[14]],
        left_koordinat[data[15]], top_koordinat[data[15]], left_koordinat[data[16]], top_koordinat[data[16]], left_koordinat[data[17]], top_koordinat[data[17]],
        left_koordinat[data[18]], top_koordinat[data[18]], left_koordinat[data[19]], top_koordinat[data[19]]
    };
    int arr_kart1[20] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

    int arr_kart[20] = {
        arr_kart1[data[0]], arr_kart1[data[1]], arr_kart1[data[2]], arr_kart1[data[3]], arr_kart1[data[4]],
        arr_kart1[data[5]], arr_kart1[data[6]], arr_kart1[data[7]], arr_kart1[data[8]], arr_kart1[data[9]],
        arr_kart1[data[10]], arr_kart1[data[11]], arr_kart1[data[12]], arr_kart1[data[13]], arr_kart1[data[14]],
        arr_kart1[data[15]], arr_kart1[data[16]], arr_kart1[data[17]], arr_kart1[data[18]], arr_kart1[data[19]] };

    //Получает системное время (начало игры)
    sistem_time_start();

    //Вызов рисовки карт
    kartinki(arr_koordinat, arr_kart, data);
}
//Музыка
int music(int r)
{
    string path;
    if (r == 1)
        path = "C://Users//Pavel//Pictures//ШАГ//1ый Курс//Курсовые//С++//Memory.project//Music//Cadilac.mp3";
    if (r == 2)
        path = "C://Users//Pavel//Pictures//ШАГ//1ый Курс//Курсовые//С++//Memory.project//Music//El Problemo.mp3";
    if (r == 3)
        path = "C://Users//Pavel//Pictures//ШАГ//1ый Курс//Курсовые//С++//Memory.project//Music//Cristal.mp3";
    if (r == 4)
        path = "C://Users//Pavel//Pictures//ШАГ//1ый Курс//Курсовые//С++//Memory.project//Music//New Merin.mp3";
    if (r == 5)
        path = "C://Users//Pavel//Pictures//ШАГ//1ый Курс//Курсовые//С++//Memory.project//Music//New Volna.mp3";

    if (HIWORD(BASS_GetVersion()) != BASSVERSION)
    {
        system("pause");
        return 1;
    }

    if (!BASS_Init(-1, 22050, NULL, 0, NULL))
    {
        system("pause");
        return 1;
    }

    HSAMPLE Sample;
    HCHANNEL Channel;
    Sample = BASS_SampleLoad(FALSE, path.c_str(), 0, 0, 2, BASS_SAMPLE_LOOP);
    if (!Sample)
    {
        system("pause");
        return 1;
    }

    Channel = BASS_SampleGetChannel(Sample, TRUE);
    if (!Channel)
    {
        system("pause");
        return 1;
    }

    if (!BASS_ChannelPlay(Channel, TRUE))
    {
        system("pause");
        return 1;
    }

    BASS_ChannelPlay(Channel, TRUE);
    system("pause >> NUL");
    return 0;
}
//Убирает мигающий курсор
void hidecursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}
//Получает системное время (начало игры)
void sistem_time_start()
{
    SYSTEMTIME st;
    GetSystemTime(&st);
    int hour = (st.wHour + 3) % 24;
    int minute = st.wMinute;
    int second = st.wSecond;
    int day = st.wDay;

    //Переменая для записи дня вначале игры
    rec_start_day = day;
    //Переменая для записи времени вначале игры
    rec_start_time = hour * 60 * 60 + minute * 60 + second;
}
//Получает системное время (конец игры) и считает результат
void sistem_time_end()
{
    SYSTEMTIME st;
    GetSystemTime(&st);

    int hour = (st.wHour + 3) % 24;
    int minute = st.wMinute;
    int second = st.wSecond;
    int day = st.wDay;

    if (rec_start_day == day)
        rec_start_time = (hour * 60 * 60 + minute * 60 + second) - rec_start_time;
    else
    {
        rec_start_time = 86400 - rec_start_time;
        rec_start_time = (hour * 60 * 60 + minute * 60 + second) + rec_start_time;
    }

    int hour_final;
    int minute_final;
    int second_final;

    //Считает результат если время меньше часа 
    if (rec_start_time > 0 && rec_start_time < 3600)
        {
            hour_final = 0;
            minute_final = rec_start_time / 60;
            second_final = rec_start_time - minute_final * 60;
        }
    else
        {
            hour_final = rec_start_time / 60 / 60;
            minute_final = rec_start_time / 60 - hour_final * 60;
            second_final = rec_start_time - minute_final * 60;
        }

    //Считает результат если время больше часа 
    if (e == 0)
        {
            ar_rec[1] = hour_final;
            ar_rec[2] = minute_final;
            ar_rec[3] = second_final;
            e++;
        }
    else
        {
            e1 = e * 3;
            ar_rec[e1 + 1] = hour_final;
            ar_rec[e1 + 2] = minute_final;
            ar_rec[e1 + 3] = second_final;
            e++;
        }
    
    //Выводит рекорд в конце
    show_record_end();
}
//Выводит рекорд в конце
void show_record_end()
{
    setlocale(0, "");
    //Чистит экран консоли
    clear();

    if (e == 1)
    {
        string name;
        cout << "\n                                               Красава, Ты победил" << endl;
        cout << "\n                                               Твое время: " << ar_rec[1] <<":" << ar_rec[2] << ":" << ar_rec[3] << endl;
        cout << "\n                                               Впиши имя для рекорда: ";
        cin >> name;
        ar_rec_name[1] = name;
    }
    else
    {
        e1 = (e - 1) * 3;
        string name;
        cout << "\n                                               Красава, Ты победил" << endl;
        cout << "\n                                               Твое время: " << ar_rec[e1 + 1] << ":" << ar_rec[e1 + 2] << ":" << ar_rec[e1 + 3] << endl;
        cout << "\n                                               Впиши имя для рекорда: ";
        cin >> name;
        ar_rec_name[e] = name;
    }
    posle_pobedi();
}


////////// МЕНЮ
//Меню Музыки
void menu_music()
{
    //Убирает мигающий курсор
    hidecursor();

    const int items_count = 6;
    string menu_items[items_count] = { "Cadilac", "El Problemo", "Cristal", "New Merin", "New Volna", "Назад" };
    int startX = 55;
    int startY = 3;
    int margin = 2;
    COORD position = { startX, startY };
    for (auto item : menu_items)
    {
        SetConsoleTextAttribute(h, DARK_GREEN);
        SetConsoleCursorPosition(h, position);
        cout << item;
        position.Y += margin;
    }
    int current_item = 0; // new game
    SetConsoleTextAttribute(h, GREEN);
    position.Y = startY + current_item * margin;
    SetConsoleCursorPosition(h, position);
    cout << menu_items[current_item];
    int code;
    int r = 0;
    while (true)
    {
        code = _getch();
        if (code == 224)
            code = _getch();
        SetConsoleTextAttribute(h, DARK_GREEN);
        position.Y = startY + current_item * margin;
        SetConsoleCursorPosition(h, position);
        cout << menu_items[current_item];

        // Вверх
        if ((code == DOWN || code == RIGHT) && current_item < items_count - 1)
            current_item++;

        // Вниз
        else if ((code == UP || code == LEFT) && current_item > 0)
            current_item--;

        // Выбор
        else if (code == ENTER)
            switch (current_item)
            {
            case 0:
                r = 1;
                music(r);
                break;
            case 1:
                r = 2;
                music(r);
                break;
            case 2:
                r = 3;
                music(r);
                break;
            case 3:
                r = 4;
                music(r);
                break;
            case 4:
                r = 5;
                music(r);
                break;
            case 5:
                clear();
                menu();
                break;
            }

        SetConsoleTextAttribute(h, GREEN);
        position.Y = startY + current_item * margin;
        SetConsoleCursorPosition(h, position);
        cout << menu_items[current_item];
    }
}
//Меню при старте
void menu()
{
    //Чистит экран консоли
    clear();

    //Убирает мигающий курсор
    hidecursor();

    const int items_count = 4;
    string menu_items[items_count] = { "СТАРТ","Рекорды","Музыка","Выход" };
    int startX = 55;
    int startY = 3;
    int margin = 2;
    COORD position = { startX, startY };
    for (auto item : menu_items)
    {
        SetConsoleTextAttribute(h, DARK_GREEN);
        SetConsoleCursorPosition(h, position);
        cout << item;
        position.Y += margin;
    }
    int current_item = 0; // new game
    SetConsoleTextAttribute(h, GREEN);
    position.Y = startY + current_item * margin;
    SetConsoleCursorPosition(h, position);
    cout << menu_items[current_item];
    int code;

    while (true)
    {
        code = _getch();
        if (code == 224)
            code = _getch();
        SetConsoleTextAttribute(h, DARK_GREEN);
        position.Y = startY + current_item * margin;
        SetConsoleCursorPosition(h, position);
        cout << menu_items[current_item];

        // Вверх
        if ((code == DOWN || code == RIGHT) && current_item < items_count - 1)
            current_item++;

        // Вниз
        else if ((code == UP || code == LEFT) && current_item > 0)
            current_item--;

        // Выбор
        else if (code == ENTER)
            switch (current_item)
            {
            case 0:
                random_kart();
                break;
            case 1:
                records();
                break;
            case 2:
                menu_music();
                break;
            case 3:
                exit(0);
            }

        SetConsoleTextAttribute(h, GREEN);
        position.Y = startY + current_item * margin;
        SetConsoleCursorPosition(h, position);
        cout << menu_items[current_item];
    }
}
//Меню рекорды
void records()
{
    setlocale(0, "");

    if (e > 0) 
    {
        //Чистит экран консоли
        clear();

        int y1 = 3;
        if (e == 1)
        {
            int i = 1;
            cout << "\n                                               1) Имя: " << ar_rec_name[i] << endl;
            cout << "\n                                                  Время: " << ar_rec[i] << ":" << ar_rec[i + 1] << ":" << ar_rec[i + 2] << endl;
            cout << "\n                                               _____________________________" << endl;
            y1 += 5;
        }
        else
        {
            int i = 1;
            cout << "\n                                               1) Имя: " << ar_rec_name[i] << endl;
            cout << "\n                                                  Время: " << ar_rec[i] << ":" << ar_rec[i + 1] << ":" << ar_rec[i + 2] << endl;
            cout << "\n                                               _____________________________" << endl;
            int i2 = 2;

            for (int i1 = 3; i1 < e * 3; i1 += 3)
            {
                cout << "\n                                               " << i2 << ") Имя: " << ar_rec_name[i2] << endl;
                cout << "\n                                                  Время: " << ar_rec[i1 + 1] << ":" << ar_rec[i1 + 2] << ":" << ar_rec[i1 + 3] << endl;
                cout << "\n                                               _____________________________" << endl;
                i2++;
                y1 += 5;
            }
        }

        //Убирает мигающий курсор
        hidecursor();

        const int items_count = 1;
        string menu_items[items_count] = { "Глвное меню" };
        int startX = 55;
        int startY = y1;
        int margin = 2;
        COORD position = { startX, startY };
        for (auto item : menu_items)
        {
            SetConsoleTextAttribute(h, DARK_GREEN);
            SetConsoleCursorPosition(h, position);
            cout << item;
            position.Y += margin;
        }
        int current_item = 0; // new game
        SetConsoleTextAttribute(h, GREEN);
        position.Y = startY + current_item * margin;
        SetConsoleCursorPosition(h, position);
        cout << menu_items[current_item];
        int code;

        while (true)
        {
            code = _getch();
            if (code == 224)
                code = _getch();
            SetConsoleTextAttribute(h, DARK_GREEN);
            position.Y = startY + current_item * margin;
            SetConsoleCursorPosition(h, position);
            cout << menu_items[current_item];

            // Вверх
            if ((code == DOWN || code == RIGHT) && current_item < items_count - 1)
                current_item++;

            // Вниз
            else if ((code == UP || code == LEFT) && current_item > 0)
                current_item--;

            // Выбор
            else if (code == ENTER)
                switch (current_item)
                {
                case 0:
                    menu();
                    break;
                }

            SetConsoleTextAttribute(h, GREEN);
            position.Y = startY + current_item * margin;
            SetConsoleCursorPosition(h, position);
            cout << menu_items[current_item];
        }
    }
    else if (e == 0)
    {
        //Чистит экран консоли
        clear();

        int y1 = 5;
        int i = 1;
        cout << "\n                                                    Рекордов пока нет. " << ar_rec_name[i] << endl;
        cout << "\n                                       Сыграйте игру, победите и впишите себя в таблицу" << endl;

        //Убирает мигающий курсор
        hidecursor();

        const int items_count = 2;
        string menu_items[items_count] = { "СТАРТ", "Главное меню" };
        int startX = 55;
        int startY = y1;
        int margin = 2;
        COORD position = { startX, startY };

        for (auto item : menu_items)
        {
            SetConsoleTextAttribute(h, DARK_GREEN);
            SetConsoleCursorPosition(h, position);
            cout << item;
            position.Y += margin;
        }

        int current_item = 0; // new game
        SetConsoleTextAttribute(h, GREEN);
        position.Y = startY + current_item * margin;
        SetConsoleCursorPosition(h, position);
        cout << menu_items[current_item];
        int code;

        while (true)
        {
            code = _getch();

            if (code == 224)
                code = _getch();

            SetConsoleTextAttribute(h, DARK_GREEN);
            position.Y = startY + current_item * margin;
            SetConsoleCursorPosition(h, position);
            cout << menu_items[current_item];

            // Вверх
            if ((code == DOWN || code == RIGHT) && current_item < items_count - 1)
                current_item++;

            // Вниз
            else if ((code == UP || code == LEFT) && current_item > 0)
                current_item--;

            // Выбор
            else if (code == ENTER)
                switch (current_item)
                {
                case 0:
                    random_kart();
                    break;
                case 1:
                    menu();
                    break;
                }

            SetConsoleTextAttribute(h, GREEN);
            position.Y = startY + current_item * margin;
            SetConsoleCursorPosition(h, position);
            cout << menu_items[current_item];
        }
    }
    
}
//Меню после победы
void posle_pobedi()
{
    //Чистит экран консоли
    clear();

    //Убирает мигающий курсор
    hidecursor();

    const int items_count = 4;
    string menu_items[items_count] = { "Заново","Рекорды","Главное меню","Выход" };
    int startX = 55;
    int startY = 3;
    int margin = 2;
    COORD position = { startX, startY };

    for (auto item : menu_items)
    {
        SetConsoleTextAttribute(h, DARK_GREEN);
        SetConsoleCursorPosition(h, position);
        cout << item;
        position.Y += margin;
    }

    int current_item = 0; // new game
    SetConsoleTextAttribute(h, GREEN);
    position.Y = startY + current_item * margin;
    SetConsoleCursorPosition(h, position);
    cout << menu_items[current_item];
    int code;

    while (true)
    {
        code = _getch();

        if (code == 224)
            code = _getch();

        SetConsoleTextAttribute(h, DARK_GREEN);
        position.Y = startY + current_item * margin;
        SetConsoleCursorPosition(h, position);
        cout << menu_items[current_item];

        // Вверх
        if ((code == DOWN || code == RIGHT) && current_item < items_count - 1)
            current_item++;

        // Вниз
        else if ((code == UP || code == LEFT) && current_item > 0)
            current_item--;

        // Выбор
        else if (code == ENTER)
            switch (current_item)
            {
            case 0:
                random_kart();
                break;
            case 1:
                records();
                break;
            case 2:
                menu();
                break;
            case 3:
                exit(0);
                break;
            }

        SetConsoleTextAttribute(h, GREEN);
        position.Y = startY + current_item * margin;
        SetConsoleCursorPosition(h, position);
        cout << menu_items[current_item];
    }
}

////////// MAIN
int main()
{
    SYSTEMTIME st;
    GetSystemTime(&st);
    setlocale(0, "");
    system("mode con cols=120 lines=50");
    system("title Мемори");

    menu();
 
    Sleep(INFINITE);
}