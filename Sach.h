#include "Header.h"
class Sach
{
private:
    string strMaSach, strTenSach, strTacGia, strNhaXuatBan, strNgayNhapKho;
    int iGiaBan, iNamPhatHanh, iSoTrang, iTinhTrang;

public:
    Sach(string strMaSach = "", string strTenSach = "", string strTacGia = "", string strNhaXuatBan = "",
         int iGiaBan = 0, int iNamPhatHanh = 0, int iSoTrang = 0, string strNgayNhapKho = "", int iTinhTrang = 0)
    {
        this->strMaSach = strMaSach;
        this->strTenSach = strTenSach;
        this->strTacGia = strTacGia;
        this->strNhaXuatBan = strNhaXuatBan;
        this->iGiaBan = iGiaBan;
        this->iNamPhatHanh = iNamPhatHanh;
        this->iSoTrang = iSoTrang;
        this->strNgayNhapKho = strNgayNhapKho;
        this->iTinhTrang = iTinhTrang;
    }
    Sach(const Sach &_sach)
    {
        this->strMaSach = _sach.strMaSach;
        this->strTenSach = _sach.strTenSach;
        this->strTacGia = _sach.strTacGia;
        this->strNhaXuatBan = _sach.strNhaXuatBan;
        this->iGiaBan = _sach.iGiaBan;
        this->iNamPhatHanh = _sach.iNamPhatHanh;
        this->iSoTrang = _sach.iSoTrang;
        this->strNgayNhapKho = _sach.strNgayNhapKho;
        this->iTinhTrang = _sach.iTinhTrang;
    }
    ~Sach() {}

    string getMaSach()
    {
        return this->strMaSach;
    }
    string getTenSach() const
    {
        return this->strTenSach;
    }
    string getTacGia() const
    {
        return this->strTacGia;
    }
    string getNhaXuatBan() const
    {
        return this->strNhaXuatBan;
    }
    int getGiaBan() const
    {
        return this->iGiaBan;
    }
    int getNamPhatHanh() const
    {
        return this->iNamPhatHanh;
    }
    int getSoTrang() const
    {
        return this->iSoTrang;
    }
    string getNgayNhapKho() const
    {
        return this->strNgayNhapKho;
    }
    int getTinhTrang() const
    {
        return this->iTinhTrang;
    }

    void setMaSach(string strMaSach)
    {
        this->strMaSach = strMaSach;
    }
    void setTenSach(string strTenSach)
    {
        this->strTenSach = strTenSach;
    }
    void setTacGia(string strTacGia)
    {
        this->strTacGia = strTacGia;
    }
    void setNhaXuatBan(string strNhaXuatBan)
    {
        this->strNhaXuatBan = strNhaXuatBan;
    }
    void setGiaBan(int iGiaBan)
    {
        this->iGiaBan = iGiaBan;
    }
    void setNamPhatHanh(int iNamPhatHanh)
    {
        this->iNamPhatHanh = iNamPhatHanh;
    }
    void setSoTrang(int iSoTrang)
    {
        this->iSoTrang = iSoTrang;
    }
    void setNgayNhapKho(string strNgayNhapKho)
    {
        this->strNgayNhapKho = strNgayNhapKho;
    }
    void setTinhTrang(int iTinhTrang)
    {
        this->iTinhTrang = iTinhTrang;
    }
    friend istream& operator >> (istream& is,Sach& _sach)
	{
		getline(is, _sach.strMaSach);
		getline(is, _sach.strTenSach);
		getline(is, _sach.strTacGia);
		getline(is, _sach.strNhaXuatBan);
		is >> _sach.iGiaBan;
		is >> _sach.iNamPhatHanh;
		is >> _sach.iSoTrang;
		is.ignore();
		getline(is, _sach.strNgayNhapKho);
		is >> _sach.iTinhTrang;
		is.ignore();
		return is;
	}
	friend ostream& operator << (ostream& os, Sach _sach)
	{
	    os << _sach.strMaSach << endl;
        os << _sach.strTenSach << endl;
        os << _sach.strTacGia << endl;
        os << _sach.strNhaXuatBan << endl;
        os << _sach.iGiaBan << endl;
        os << _sach.iNamPhatHanh << endl;
        os << _sach.iSoTrang << endl;
        os << _sach.strNgayNhapKho << endl;
        os << _sach.iTinhTrang << endl;
	    return os;
	}
    
    bool operator==(Sach _sach)
    {
        return this->strMaSach == _sach.strMaSach;
    }

    bool operator!=(Sach _sach)
    {
        return this->strMaSach != _sach.strMaSach;
    }
};