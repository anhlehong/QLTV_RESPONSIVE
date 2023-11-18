#include "Header.h"
#include "Admin.h"
#include "BanDoc.h"
#include "PhieuMuon.h"
#include "Sach.h"
#include "Node.h"

const int BACKSPACE = 8;
const int ENTER = 13;
const int SPACE = 32;
const int ESC = 27;
const int KEY_1 = 49;
const int KEY_2 = 50;
const int KEY_3 = 51;

int g_iPreviousConsoleWidth = 0;
int g_iPreviousConsoleHeight = 0;
int g_iConsoleWidth, g_iConsoleHeight;
int g_iStartX, g_iStartY;

ifstream cinAdmin;
ofstream coutAdmin;
LinkedList<Admin> admin;
ifstream cinSach;
ofstream coutSach;
LinkedList<Sach> sach;
ifstream cinPhieuMuon;
ofstream coutPhieuMuon;
LinkedList<PhieuMuon> phieumuon;
ifstream cinBanDoc;
ofstream coutBanDoc;
LinkedList<BanDoc> bandoc;

// // vị trí con trỏ khi xuất ra màn hình
// void gotoxy(int x, int y)
// {
//     COORD coord;
//     coord.X = x;
//     coord.Y = y;
//     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
// }
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void getConsoleSize(int &consoleWidth, int &consoleHeight)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}
void calculateCentered(const int consoleWidth, const int consoleHeight, const int objectWidth,
                        const int objectHeight, int &startX, int &startY)
{
    startX = (consoleWidth - objectWidth) / 2;
    startY = (consoleHeight - objectHeight) / 2;
}
// màu chữ
void textcolor(int x)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, x);
}
void login()
{
    calculateCentered(g_iConsoleWidth, g_iConsoleHeight, 28, 5, g_iStartX, g_iStartY);
    textcolor(6);
    gotoxy(g_iStartX, g_iStartY);
    cout << "****************************" << endl;
    gotoxy(g_iStartX, g_iStartY + 1);
    cout << "*";
    textcolor(10);
    gotoxy(g_iStartX+5, g_iStartY + 1);
    cout << "Dang nhap he thong";
    textcolor(6);
    gotoxy(g_iStartX+27, g_iStartY + 1);
    cout << "*" << endl;
    gotoxy(g_iStartX, g_iStartY + 2);
    cout << "****************************";
    textcolor(1);
    gotoxy(g_iStartX, g_iStartY + 3);
    cout << "Username: ";
    gotoxy(g_iStartX, g_iStartY + 4);
    cout << "Password: ";
    gotoxy(g_iStartX + 11, g_iStartY + 3);
}
string enterUsername() // x y là 2 tham số vị trí con trỏ khi in ra màn hình
{
    gotoxy(g_iStartX + 11, g_iStartY + 3);
    string strUserName = "";
    char cInputKey = _getch();
    while (cInputKey != ENTER)
    {
        if (cInputKey == BACKSPACE)
        {
            if (!strUserName.empty())
            {
                strUserName.pop_back();
                cout << "\b \b";
            }
        }
        else if (cInputKey == ESC)
            exit(0);
        else if (cInputKey != SPACE)
        {
            cout << cInputKey;
            strUserName += cInputKey;
        }
        cInputKey = _getch();
    }
    return strUserName;
}
string enterPassword() // x y là 2 tham số vị trí con trỏ khi in ra màn hình
{
    gotoxy(g_iStartX+11, g_iStartY + 4);
    string strPassword = "";
    char cInputKey = _getch();
    while (cInputKey != ENTER)
    {
        if (cInputKey == BACKSPACE)
        {
            if (!strPassword.empty())
            {
                strPassword.pop_back();
                cout << "\b \b";
            }
        }
        else if (cInputKey == ESC)
            exit(0);
        else if (cInputKey != SPACE)
        {
            cout << '*';
            strPassword += cInputKey;
        }
        cInputKey = _getch();
    }
    
    return strPassword;
}
void data_Admin()
{
    Admin _ad;
    cinAdmin.open("Admin.txt");
    while (!cinAdmin.eof())
    {
        cinAdmin >> _ad;
        admin.addTail(_ad);
    }
    cinAdmin.close();
}
bool isUser(string strUserName, string strPassword)
{
    Node<Admin> *p = admin.pHead;
    while (p != NULL)
    {
        if (strUserName == p->data.getUser() && strPassword == p->data.getPassword())
            return true;
        p = p->pNext;
    }
    delete p;
    return false;
}
void menu();
void runLogin()
{
    int loginn = 1;
    while(true){
        getConsoleSize(g_iConsoleWidth, g_iConsoleHeight);
        if (g_iConsoleWidth != g_iPreviousConsoleWidth || g_iConsoleHeight != g_iPreviousConsoleHeight)
        {
            system("cls");
            login();
            g_iPreviousConsoleWidth = g_iConsoleWidth;
            g_iPreviousConsoleHeight = g_iConsoleHeight;
        }
        if (_kbhit())
        {
            while (loginn < 4)
            {
                textcolor(9);
                string username = enterUsername();
                string password = enterPassword();
                if (isUser(username, password))
                {
                    g_iPreviousConsoleHeight = 0;
                    g_iPreviousConsoleWidth = 0;
                    menu();
                }
                else
                {
                    system("cls");
                    login();
                    textcolor(12);
                    gotoxy(g_iStartX, g_iStartY + 5);
                    cout << "Ban da nhap sai " << loginn << "/" << "3 lan.";
                    loginn++;
                }
            }
        }
        if (loginn == 4)
        {
            system("cls");
            exit(0);
        }
        Sleep(500);
    }
}
void miniMenu(int x, int y) // x, y: vi tri con tro
{
    textcolor(14);
    gotoxy(x, y+1);
    cout << "Backspace: ";
    textcolor(11);
    cout << "Back";
    gotoxy(x, y+2);
    textcolor(14);
    cout << "Esc: ";
    textcolor(11);
    cout << "Exit";
    textcolor(7);
    gotoxy(x, y + 3);
}
void menuQuanLySach();
void funcMiniMenu()
{
    char key = _getch();
    if (key == BACKSPACE)
    {
        g_iPreviousConsoleHeight = 0;
        g_iPreviousConsoleWidth = 0;
        menuQuanLySach();
        return;
    }
    else if (key == ESC)
    {
        system("cls");
        exit(0);
    }
}
void data_Sach()
{
    Sach _sach;
    cinSach.open("Sach.txt");
    while (cinSach >> _sach)
        sach.addTail(_sach);
    cinSach.close();
}
bool isSach(Sach _data) // so sanh ma sach
{
    Node<Sach>* p = sach.pHead;
    while (p != NULL)
    {
        if (_data == p->data)
            return true;
        p = p->pNext;
    }
    delete p;
    return false;
}
string center(const string &str, int w)
{
    int l = (w - str.size()) / 2;
    int r = w - l - str.size();
    return string(l, ' ') + str + string(r, ' ');
}
void funcMiniMenu();
void showInforSach()
{
    Node<Sach> *pSach = sach.pHead;
    int iMaxLenMaSach = 7, iMaxLenTenSach = 8, iMaxLenTacGia = 7, iMaxlenNhaXuatBan = 12;
    int iMaxLenGiaBan = 7, iMaxLenNamPhatHanh = 13, iMaxLenSoTrang = 8, iMaxLenNgayNhapKho = 13, iMaxLenTinhTrangSach = 15;
    
    while (pSach != NULL)
    {
        iMaxLenMaSach = max(iMaxLenMaSach, (int)(pSach->data.getMaSach().size()));
        iMaxLenTenSach = max(iMaxLenTenSach, (int)pSach->data.getTenSach().size());
        iMaxLenTacGia = max(iMaxLenTacGia, (int)pSach->data.getTacGia().size());
        iMaxlenNhaXuatBan = max(iMaxlenNhaXuatBan, (int)pSach->data.getNhaXuatBan().size());
        iMaxLenGiaBan = max(iMaxLenGiaBan, (int)(to_string(pSach->data.getGiaBan()).size()));
        iMaxLenNamPhatHanh = max(iMaxLenNamPhatHanh, (int)(to_string(pSach->data.getNamPhatHanh()).size()));
        iMaxLenSoTrang = max(iMaxLenSoTrang, (int)(to_string(pSach->data.getSoTrang()).size()));
        iMaxLenNgayNhapKho = max(iMaxLenNgayNhapKho, (int)pSach->data.getNgayNhapKho().size());
        iMaxLenTinhTrangSach = max(iMaxLenTinhTrangSach, (int)(to_string(pSach->data.getTinhTrang()).size()));
        pSach = pSach->pNext;
    }

    while(true)
    {
        getConsoleSize(g_iConsoleWidth, g_iConsoleHeight);
        if (g_iConsoleWidth != g_iPreviousConsoleWidth || g_iConsoleHeight != g_iPreviousConsoleHeight)
        {
            system("cls");
            int iLen = 22 + iMaxLenMaSach + iMaxLenTenSach + iMaxLenTacGia + iMaxlenNhaXuatBan;
            iLen += iMaxLenGiaBan + iMaxLenNamPhatHanh + iMaxLenSoTrang + iMaxLenNgayNhapKho + iMaxLenTinhTrangSach;
            int iLenTitle = (iLen-14)/2;
            calculateCentered(g_iConsoleWidth, g_iConsoleHeight,iLen, sach.getSize()+2, g_iStartX, g_iStartY);
            gotoxy(g_iStartX+ iLenTitle, g_iStartY);
            textcolor(3);
            cout << "THONG TIN SACH";
            gotoxy(g_iStartX, g_iStartY+1);
            //"MA SACHTEN SACHTAC GIANHA XUAT BANGIA BANNAM PHAT HANHSO TRANGNGAY NHAP KHOTINH TRANG SACH";
            textcolor(5);
            cout << '|' << center("MA SACH", iMaxLenMaSach + 3);
            cout << '|' << center("TEN SACH", iMaxLenTenSach + 3);
            cout << '|' << center("TAC GIA", iMaxLenTacGia + 3);
            cout << '|' << center("NHA XUAT BAN", iMaxlenNhaXuatBan + 3);
            cout << '|' << center("GIA BAN", iMaxLenGiaBan);
            cout << '|' << center("NAM PHAT HANH", iMaxLenNamPhatHanh);
            cout << '|' << center("SO TRANG", iMaxLenSoTrang);
            cout << '|' << center("NGAY NHAP KHO", iMaxLenNgayNhapKho);
            cout << '|' << center("TINH TRANG SACH", iMaxLenTinhTrangSach) << "|\n";

            pSach = sach.pHead;
            int i = 2;

            while (pSach != NULL)
            {
                gotoxy(g_iStartX, g_iStartY+i);
                textcolor(2);
                cout << "|" << setw(iMaxLenMaSach + 3) << left << pSach->data.getMaSach();
                cout << "|" << setw(iMaxLenTenSach + 3) << left << pSach->data.getTenSach();
                cout << "|" << setw(iMaxLenTacGia + 3) << left << pSach->data.getTacGia();
                cout << "|" << setw(iMaxlenNhaXuatBan + 3) << left << pSach->data.getNhaXuatBan();
                cout << '|' << center(to_string(pSach->data.getGiaBan()), iMaxLenGiaBan);
                cout << '|' << center(to_string(pSach->data.getNamPhatHanh()), iMaxLenNamPhatHanh);
                cout << '|' << center(to_string(pSach->data.getSoTrang()), iMaxLenSoTrang);
                cout << '|' << center(pSach->data.getNgayNhapKho(), iMaxLenNgayNhapKho);
                cout << '|' << center(to_string(pSach->data.getTinhTrang()), iMaxLenTinhTrangSach) << "|\n";
                pSach = pSach->pNext;
                ++i;
            }
            miniMenu(g_iStartX + iLenTitle, g_iStartY+i);
            g_iPreviousConsoleWidth = g_iConsoleWidth;
            g_iPreviousConsoleHeight = g_iConsoleHeight;
        }
        if(_kbhit())
            funcMiniMenu();
        Sleep(500);
    }
}

void addSach()
{
    system("cls");
    gotoxy(75, 1);
    textcolor(3);
    cout << "SACH CAN THEM";
    textcolor(6);
    gotoxy(68, 3);
    cout << "Ma sach: ";
    textcolor(6);
    gotoxy(68, 4);
    cout << "Ten sach: ";
    gotoxy(68, 5);
    cout << "Tac gia: ";
    gotoxy(68, 6);
    cout << "Nha xuat ban: ";
    gotoxy(68, 7);
    cout << "Gia ban: ";
    gotoxy(68, 8);
    cout << "Nam phat hanh: ";
    gotoxy(68, 9);
    cout << "So trang: ";

    textcolor(15);
    string strMaSach;
    gotoxy(85, 3);
    getline(cin, strMaSach);
    string strTenSach;
    gotoxy(85, 4);
    getline(cin, strTenSach);
    string strTacGia;
    gotoxy(85, 5);
    getline(cin, strTacGia);
    string strNXB;
    gotoxy(85, 6);
    getline(cin, strNXB);
    int iGiaBan;
    gotoxy(85, 7);
    cin >> iGiaBan;
    int iNamPhatHanh;
    gotoxy(85, 8);
    cin >> iNamPhatHanh;
    int iSoTrang;
    gotoxy(85, 9);
    cin >> iSoTrang;
    cin.ignore();
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int day = ltm->tm_mday;
    int month = ltm->tm_mon + 1;
    int nam = 1900 + ltm->tm_year;
    string strNgayNhap = to_string(day) + "/" + to_string(month) + "/" + to_string(nam);
    Sach sachTemp(strMaSach, strTenSach, strTacGia, strNXB, iGiaBan, iNamPhatHanh, iSoTrang, strNgayNhap, 0);
    if (strMaSach != "" && strTenSach != "" && strTacGia != "" && strNXB != "")
    {
        if (isSach(sachTemp))
        {
            gotoxy(75, 25);
            cout << "SACH DA TON TAI";
            textcolor(7);
            miniMenu(5, 35);
            system("pause>nul");
            funcMiniMenu();
        }
        else
        {
            gotoxy(75, 25);
            textcolor(10);
            cout << "THEM SACH THANH CONG";
            sach.addTail(sachTemp);
            coutSach.open("Sach.txt");
            Node<Sach> *p = sach.pHead;
            while (p != NULL)
            {
                coutSach << p->data;
                p = p->pNext;
            }
            delete p;
            coutSach.close();

            miniMenu(5, 35);
            system("pause>nul");
            funcMiniMenu();
        }
    }
    else
    {
        cout << "THONG TIN SACH CHUA DAY DU VA CHINH XAC";
        miniMenu(5, 35);
        system("pause>nul");
        funcMiniMenu();
    }
}
void removeSach()
{
    system("cls");
    showInforSach();
    textcolor(3);
    int y = sach.iSize + 5;
    gotoxy(67, y);
    textcolor(14);
    cout << "Nhap Ma Sach can xoa: ";
    string maSachCanXoa;
    textcolor(7);
    getline(cin, maSachCanXoa);
    y++;
    Node<Sach> *pSach = sach.pHead;
    while (pSach != NULL)
    {
        if (pSach->data.getMaSach() == maSachCanXoa)
        {
            if (pSach->data.getTinhTrang() == 0)
            {
                if (pSach == sach.pHead) // Xóa đầu danh sách
                    sach.removeHead();

                else
                    sach.remove(pSach->data);

                gotoxy(67, y);
                textcolor(10);
                cout << "XOA SACH THANH CONG!" << endl;
                coutSach.open("Sach.txt");
                Node<Sach> *p = sach.pHead;
                while (p != NULL)
                {
                    coutSach << p->data;
                    p = p->pNext;
                }
                delete p;
                coutSach.close();
                break;
            }
            else
            {
                gotoxy(60, y);
                textcolor(12);
                cout << "SACH DANG DUOC MUON. KHONG THE XOA!" << endl;
                break;
            }
        }
        pSach = pSach->pNext;
    }
    if (pSach == NULL)
    {
        gotoxy(67, y);
        textcolor(12);
        cout << "KHONG TIM THAY MA SACH " << maSachCanXoa << endl;
        delete pSach;
    }
    miniMenu(7, 35);
    system("pause>nul");
    funcMiniMenu();
}
void menuQuanLySach()
{
    while (true)
    {
        getConsoleSize(g_iConsoleWidth, g_iConsoleHeight);
        if (g_iConsoleWidth != g_iPreviousConsoleWidth || g_iConsoleHeight != g_iPreviousConsoleHeight)
        {
            system("cls");
            calculateCentered(g_iConsoleWidth, g_iConsoleHeight, 36, 6, g_iStartX, g_iStartY);
            getConsoleSize(g_iConsoleWidth, g_iConsoleHeight);
            if (g_iConsoleWidth != g_iPreviousConsoleWidth || g_iConsoleHeight != g_iPreviousConsoleHeight)
            {
                system("cls");
                calculateCentered(g_iConsoleWidth, g_iConsoleHeight, 36, 6, g_iStartX, g_iStartY);
                system("cls");
                textcolor(11);
                gotoxy(g_iStartX, g_iStartY);
                cout << ".-*-.-*-.-* QUAN LY SACH *-.-*-.-*-.\n";

                textcolor(15);
                gotoxy(g_iStartX + 5, g_iStartY + 1);
                cout << "1. HIEN THI THONG TIN SACH" << endl;
                gotoxy(g_iStartX + 5, g_iStartY + 2);
                cout << "2. THEM SACH" << endl;
                gotoxy(g_iStartX + 5, g_iStartY + 3);
                cout << "3. XOA SACH" << endl;
                textcolor(14);
                gotoxy(g_iStartX + 5, g_iStartY + 4);
                cout << "Backspace: ";
                textcolor(11);
                cout << "Back" << endl;
                gotoxy(g_iStartX + 5, g_iStartY + 5);
                textcolor(14);
                cout << "Esc: ";
                textcolor(11);
                cout << "Exit" << endl;
                gotoxy(g_iStartX + 5, g_iStartY + 6);
                g_iPreviousConsoleHeight = g_iConsoleHeight;
                g_iPreviousConsoleWidth = g_iConsoleWidth;
            }
        }
        if (_kbhit())
        {
            char key = _getch(); // Lấy ký tự người dùng vừa bấm
            if (key == KEY_1)
            {
                g_iPreviousConsoleHeight = 0;
                g_iPreviousConsoleWidth = 0;
                showInforSach();
                return;
            }
            else if (key == KEY_2)
            {
                g_iPreviousConsoleHeight = 0;
                g_iPreviousConsoleWidth = 0;
                addSach();
                return;
            }
            else if (key == KEY_3)
            {
                g_iPreviousConsoleHeight = 0;
                g_iPreviousConsoleWidth = 0;
                removeSach();
                return;
            }
            else if (key == BACKSPACE)
            {
                g_iPreviousConsoleHeight = 0;
                g_iPreviousConsoleWidth = 0;
                menu();
                return;
            }
            else if (key == ESC)
            {
                exit(0);
            }
        }
        Sleep(500);
    }
}
int sttPhieu = 1;
void data_PhieuMuon()
{
    PhieuMuon tmp;
    cinPhieuMuon.open("PhieuMuon.txt");
    
    while (cinPhieuMuon >> tmp)
    {
        phieumuon.addTail(tmp);
        sttPhieu++;
    }
    cinPhieuMuon.close();
}
void data_BanDoc()
{
    BanDoc tmp;
    cinBanDoc.open("BanDoc.txt");
    
    while (cinBanDoc >> tmp)
        bandoc.addTail(tmp);

    cinBanDoc.close();
}
void showInforPhieuMuon(int x, int y) // 7 3
{
    system("cls");
    Node<PhieuMuon> *pPhieuMuon = phieumuon.pHead;
    int iMaxLenSoTTPhieuMuon = 9, iMaxLenMaBanDoc = 11, iMaxLenMaSach = 7, iMaxLenNgayMuon = 9,
        iMaxLenNgayPhaiTra = 13, iMaxLenTinhTrangPhieuMuon = 21;
    while (pPhieuMuon != NULL)
    {
        iMaxLenSoTTPhieuMuon = max(iMaxLenSoTTPhieuMuon, (int)(to_string(pPhieuMuon->data.getSoTTPhieuMuon()).size()));
        iMaxLenMaBanDoc = max(iMaxLenMaBanDoc, (int)pPhieuMuon->data.getMaBanDoc().size());
        iMaxLenMaSach = max(iMaxLenMaSach, (int)pPhieuMuon->data.getMaSach().size());
        iMaxLenNgayMuon = max(iMaxLenNgayMuon, (int)pPhieuMuon->data.getNgayMuon().size());
        iMaxLenNgayPhaiTra = max(iMaxLenNgayPhaiTra, (int)pPhieuMuon->data.getNgayPhaiTra().size());
        iMaxLenTinhTrangPhieuMuon = max(iMaxLenTinhTrangPhieuMuon, (int)(to_string(pPhieuMuon->data.getTinhTrangPhieu()).size()));
        pPhieuMuon = pPhieuMuon->pNext;
    }
    gotoxy(75, 1);
    textcolor(3);
    cout << "THONG TIN PHIEU MUON";
    gotoxy(x, y);
    textcolor(5);
    cout << '|' << center("SO THU TU", iMaxLenSoTTPhieuMuon);
    cout << '|' << center("MA BAN DOC", iMaxLenMaBanDoc);
    cout << '|' << center("MA SACH", iMaxLenMaSach);
    cout << '|' << center("NGAY MUON", iMaxLenNgayMuon);
    cout << '|' << center("NGAY PHAI TRA", iMaxLenNgayPhaiTra);
    cout << '|' << center("TINH TRANG PHIEU MUON", iMaxLenTinhTrangPhieuMuon) << "|\n";
    pPhieuMuon = phieumuon.pHead;
    while (pPhieuMuon != NULL)
    {
        y++;
        gotoxy(x, y);
        textcolor(2);
        cout << '|' << center(to_string(pPhieuMuon->data.getSoTTPhieuMuon()), iMaxLenSoTTPhieuMuon);
        cout << '|' << center(pPhieuMuon->data.getMaBanDoc(), iMaxLenMaBanDoc);
        cout << '|' << center(pPhieuMuon->data.getMaSach(), iMaxLenMaSach);
        cout << '|' << center(pPhieuMuon->data.getNgayMuon(), iMaxLenNgayMuon);
        cout << '|' << center(pPhieuMuon->data.getNgayPhaiTra(), iMaxLenNgayPhaiTra);
        cout << '|' << center(to_string(pPhieuMuon->data.getTinhTrangPhieu()), iMaxLenTinhTrangPhieuMuon) << "|\n";
        pPhieuMuon = pPhieuMuon->pNext;
    }
}
bool isBanDoc(BanDoc _banDoc, string strMaBanDoc)
{
    return _banDoc.getMaBanDoc() == strMaBanDoc;
}
void truyvet(string strMaSach, string strMaBanDoc) // tim sach va ban doc, neu co thi cap nhat thong tin vao phieu muon va sach
{
	PhieuMuon tmp;
    Node<BanDoc>* pBanDoc = bandoc.pHead;
    while (pBanDoc != NULL)
	{
		if (isBanDoc(pBanDoc->data, strMaBanDoc))
		{
            Node<Sach>* pSach = sach.pHead;
            while (pSach != NULL)
            {
                if (pSach->data.getMaSach() == strMaSach)
                {
                    pSach->data.setTinhTrang(sttPhieu);
                    break;
                }
                pSach = pSach->pNext;
            }
			tmp.setSoTTPhieuMuon(sttPhieu);
			tmp.setMaBanDoc(strMaBanDoc);
			tmp.setMaSach(strMaSach);
			time_t now = time(0);
			tm* ltm = localtime(&now);
			int day = ltm->tm_mday;
			int month = ltm->tm_mon;
			month++;
			int year = ltm->tm_year;
			year += 1900;
			tmp.setNgayMuon(to_string(day) + "/" + to_string(month) + "/" + to_string(year));
            day += 7;
			if (month == 2)
			{
				if (year % 4 == 0 && year % 100 != 0)
				{
					if (day > 29)
					{
						day -= 29;
						month++;
					}
				}
				else
				{
					if (day > 28)
					{
						day -= 28;
						month++;
					}
				}
			}
			else
			{
				if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
				{
					if (day > 31)
					{
						day -= 31;
						month++;
						if (month > 12)
						{
							month -= 12;
							year++;
						}
					}
				}
				else
				{
					if (day > 30)
					{
						day -= 30;
						month++;
					}
				}
			}
			tmp.setNgayPhaiTra(to_string(day) + "/" + to_string(month) + "/" + to_string(year));
			tmp.setTinhTrangPhieu(1);
			phieumuon.addTail(tmp);
            sttPhieu++;
			
            coutPhieuMuon.open("PhieuMuon.txt");
            Node<PhieuMuon>* pPhieuMuon = phieumuon.pHead;
            while (pPhieuMuon != NULL)
            {
                coutPhieuMuon << pPhieuMuon->data;
                pPhieuMuon = pPhieuMuon->pNext;
            }
            coutPhieuMuon.close();

            coutSach.open("Sach.txt");
            pSach = sach.pHead;
            while (pSach != NULL)
            {
                coutSach << pSach->data;
                pSach = pSach->pNext;
            }
            delete pPhieuMuon, pSach;
            coutSach.close();
			return;
		}
        pBanDoc = pBanDoc->pNext;
	}
    delete pBanDoc;
}

void muonSach()
{
	system("cls");
	showInforSach();
	string strMaSach;
	string strMaBanDoc;
	textcolor(9);
    int x = 75, y = sach.iSize;
    gotoxy(x, y + 5);
    cout << "Ma Sach: ";
    gotoxy(x, y + 6);
    cout << "Ma Ban doc: ";
    
	textcolor(7);
    gotoxy(x + 13, y + 5);
    getline(cin, strMaSach);
    gotoxy(x + 13, y + 6);
    getline(cin, strMaBanDoc);

    bool flag = false;
    Node<Sach>* pSach = sach.pHead;
    while (pSach != NULL)
    {
		if (pSach->data.getMaSach() == strMaSach)
        {
            if (pSach->data.getTinhTrang() == 0)
            {
                truyvet(strMaSach, strMaBanDoc);    // thay doi tinhtrang sach khi dc muon -> flag = true
                flag = true;
            }
            break;
        }
        pSach = pSach->pNext;
	}
    
	textcolor(4);
	gotoxy(x - 2, y + 8);
	if (pSach == NULL)
		cout << "SACH KHONG TON TAI";

	else 
	{
        if (pSach->data.getTinhTrang() == 0)
            cout << "MA BAN DOC KHONG TON TAI";
        else
		{
            if (flag == false) 
                cout << "SACH DANG DUOC MUON";  
            else 
            {
                Node<BanDoc>* pBanDoc = bandoc.pHead;
                while (pBanDoc != NULL)
                {
                    if (isBanDoc(pBanDoc->data, strMaBanDoc))
                    {
                        textcolor(10);
                        cout << "SACH MUON THANH CONG"; 
                        break;
                    }
                    pBanDoc = pBanDoc->pNext;
                }
            }
        }
	}
    miniMenu(7, 35);
    system("pause>nul");
    funcMiniMenu();
}

bool flagTT = false;
bool checkPhieuMuon(PhieuMuon _phieumuon, int iSTT)
{
    if (_phieumuon.getSoTTPhieuMuon() == iSTT)
    {
        if (_phieumuon.getTinhTrangPhieu() == 1)
        {
            flagTT = true;
            Node<Sach>* pSach = sach.pHead;
            while (pSach != NULL)
            {
                if (pSach->data.getMaSach() == _phieumuon.getMaSach())
                {
                    pSach->data.setTinhTrang(0);
                    break;
                }
                pSach = pSach->pNext;
            }
        }
        return true;
    }
    return false;
}

void traSach()
{
    system("cls");
    showInforPhieuMuon(7, 3);
    
	textcolor(9);
    int x = 75, y = phieumuon.iSize;
    gotoxy(x, y + 5);
    cout << "So Phieu muon: ";
    
    int iSoPhieuMuon;
	textcolor(7);
    gotoxy(x + 16, y + 5);
    cin >> iSoPhieuMuon;
    cin.ignore();

    Node<PhieuMuon>* pPhieuMuon = phieumuon.pHead;
    while (pPhieuMuon != NULL)
    {
        if (checkPhieuMuon(pPhieuMuon->data, iSoPhieuMuon))
            break;
        pPhieuMuon = pPhieuMuon->pNext;
    }
    
    if (pPhieuMuon == NULL)
    {
        gotoxy(x - 2, y + 7);
        textcolor(4);
        cout << "PHIEU MUON KHONG TON TAI";
    }
    else
    {
        if (flagTT == true)
        {
            gotoxy(x - 1, y + 7);
            textcolor(10);
            cout << "TRA SACH THANH CONG";
            pPhieuMuon->data.setTinhTrangPhieu(0);
            coutPhieuMuon.open("PhieuMuon.txt");
            pPhieuMuon = phieumuon.pHead;
            while (pPhieuMuon != NULL)
            {
                coutPhieuMuon << pPhieuMuon->data;
                pPhieuMuon = pPhieuMuon->pNext;
            }
            coutPhieuMuon.close();

            coutSach.open("Sach.txt");
            Node<Sach>* pSach = sach.pHead;
            while (pSach != NULL)
            {
                coutSach << pSach->data;
                pSach = pSach->pNext;
            }
            delete pPhieuMuon, pSach;
            coutSach.close();
        }
        else
        {
            gotoxy(x - 10, y + 7);
            textcolor(4);
            cout << "SACH CHUA DUOC MUON. KHONG THE TRA SACH";
        }
    }
    miniMenu(7, 35);
    system("pause>nul");
    funcMiniMenu();
}

void menuQuanLyPhieuMuon()
{
	while(true)
	{
		system("cls");
        textcolor(11);
        gotoxy(70, 10);
        cout << ".-*-.-*-.-* QUAN LY PHIEU MUON *-.-*-.-*-.";
		while (true)
        {
            textcolor(15);
            gotoxy(75, 11);
            cout << "1. HIEN THI THONG TIN PHIEU MUON";
            gotoxy(75, 12);
            cout << "2. MUON SACH";
            gotoxy(75, 13);
            cout << "3. TRA SACH";
            textcolor(14);
            gotoxy(7, 35);
            cout << "Backspace: ";
            textcolor(11);
            cout << "Back";
            gotoxy(7 + 20, 35);
            textcolor(14);
            cout << "Esc: ";
            textcolor(11);
            cout << "Exit";
            char key = _getch(); //Lấy ký tự người dùng vừa bấm
            if (key == KEY_1)
            {
                showInforPhieuMuon(7, 3);
                miniMenu(7, 35);
                system("pause>nul");
                funcMiniMenu();
                break;
            }
            if (key == KEY_2)
            {
                muonSach();
                break;
            }
            if (key == KEY_3)
            {
                traSach();
                break;
            }
            if (key == BACKSPACE)
            {
                return;
                break;
            }
            if (key == ESC)
            {
                runLogin();
                break;
            }
        }
	}
}

void menu()
{
    string strQLTV = ".-*-.-*-.-* QUAN LY THU VIEN *-.-*-.-*-.";
    string strQLS = "1. QUAN LY SACH";
    string strQLPM = "2. QUAN LY PHIEU MUON";
    string strBS = "Backspace: ";
    string strBack = "Back";
    string strEsc = "Esc: ";
    string strExit = "Exit";

    while (true)
    {
        getConsoleSize(g_iConsoleWidth, g_iConsoleHeight);
        if (g_iConsoleWidth != g_iPreviousConsoleWidth || g_iConsoleHeight != g_iPreviousConsoleHeight)
        {
            system("cls");
            calculateCentered(g_iConsoleWidth, g_iConsoleHeight,strQLTV.size(), 4, g_iStartX, g_iStartY);

            gotoxy(g_iStartX, g_iStartY);
            textcolor(11);
            cout << strQLTV << endl;
            gotoxy(g_iStartX + (strQLTV.size()-strQLPM.size())/2, g_iStartY+1);
            textcolor(15);
            cout << strQLS << endl;
            gotoxy(g_iStartX + (strQLTV.size() - strQLPM.size()) / 2, g_iStartY + 2);
            cout << strQLPM << endl;
            gotoxy(g_iStartX + (strQLTV.size() - strQLPM.size()) / 2, g_iStartY + 3);
            textcolor(14);
            cout << strBS;
            textcolor(11);
            cout << strBack << endl;
            gotoxy(g_iStartX + (strQLTV.size() - strQLPM.size()) / 2, g_iStartY +4);
            textcolor(14);
            cout << strEsc;
            textcolor(11);
            cout << strExit << endl;
            gotoxy(g_iStartX + (strQLTV.size() - strQLPM.size()) / 2, g_iStartY + 5);

            g_iPreviousConsoleWidth = g_iConsoleWidth;
            g_iPreviousConsoleHeight = g_iConsoleHeight;
        }
        if (_kbhit())
        {
            char key = _getch(); // Lấy ký tự người dùng vừa bấm
            if (key == KEY_1)
            {
                g_iPreviousConsoleHeight = 0;
                g_iPreviousConsoleWidth = 0;
                menuQuanLySach();
                return;
            }
            if (key == KEY_2)
            {
                g_iPreviousConsoleHeight = 0;
                g_iPreviousConsoleWidth = 0;
                menuQuanLyPhieuMuon();
                return;
            }
            if (key == BACKSPACE)
            {
                g_iPreviousConsoleHeight = 0;
                g_iPreviousConsoleWidth = 0;
                runLogin();
                return;
            }
            if (key == ESC)
            {
                system("cls");
                exit(0);
            }
        }

        Sleep(500);
    }
}
