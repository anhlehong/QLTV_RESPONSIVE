#include"Header.h"

class BanDoc
{
private:
    string strMaBanDoc;
    string strHoTen;
    string strNgayDangKi;

public:
    BanDoc(string strMaBanDoc = "", string strHoTen = "", string strNgayDangKi = "")
    {
        this->strMaBanDoc = strMaBanDoc;
        this->strHoTen = strHoTen;
        this->strNgayDangKi = strNgayDangKi;
    }

    BanDoc(const BanDoc &bd)
    {
        this->strMaBanDoc = bd.strMaBanDoc;
        this->strHoTen = bd.strHoTen;
        this->strNgayDangKi = bd.strNgayDangKi;
    }
    ~BanDoc() {}

    string getMaBanDoc() const
    {
        return this->strMaBanDoc;
    }

    string getHoTen() const
    {
        return this->strHoTen;
    }

    string getNgayDangKi() const
    {
        return this->strNgayDangKi;
    }



    void setMaBanDoc(string strMaBanDoc)
    {
        this->strMaBanDoc = strMaBanDoc;
    }

    void setHoTen(string strHoTen)
    {
        this->strHoTen = strHoTen;
    }

    void setNgayDangKi(int NgayDangKi)
    {
        this->strNgayDangKi = strNgayDangKi;
    }

    friend istream& operator >> (istream& is, BanDoc& bd)
	{
	
		getline(is, bd.strMaBanDoc);
		getline(is, bd.strHoTen);
        getline(is, bd.strNgayDangKi);
		return is;
	}

    friend ostream& operator << (ostream& os, BanDoc bd)
	{
        os << bd.strMaBanDoc << endl;
        os << bd.strHoTen << endl;
        os << bd.strNgayDangKi << endl;
		return os;
	}
};