#include "Header.h"
class PhieuMuon
{
private:
    int iSoTTPhieuMuon;
    string strMaBanDoc;
    string strMaSach;
    string strNgayMuon;
    string strNgayPhaiTra;
    int iTinhTrangPhieu;

public:
    PhieuMuon(int iSoTTPhieuMuon = 0, string strMaBanDoc = "", string strMaSach = "", string strNgayMuon = "", string strNgayPhaiTra = "", int iTinhTrangPhieu = 1)
    {
        this->iSoTTPhieuMuon = iSoTTPhieuMuon;
        this->strMaBanDoc = strMaBanDoc;
        this->strMaSach = strMaSach;
        this->strNgayMuon = strNgayMuon;
        this->strNgayPhaiTra = strNgayPhaiTra;
        this->iTinhTrangPhieu = iTinhTrangPhieu;
    }
    PhieuMuon(const PhieuMuon &_phieumuon)
    {
        this->iSoTTPhieuMuon = _phieumuon.iSoTTPhieuMuon;
        this->strMaBanDoc = _phieumuon.strMaBanDoc;
        this->strMaSach = _phieumuon.strMaSach;
        this->strNgayMuon = _phieumuon.strNgayMuon;
        this->strNgayPhaiTra = _phieumuon.strNgayPhaiTra;
        this->iTinhTrangPhieu = _phieumuon.iTinhTrangPhieu;
    }
    ~PhieuMuon() {}
    int getSoTTPhieuMuon() const
    {
        return this->iSoTTPhieuMuon;
    }
    string getMaBanDoc() const
    {
        return this->strMaBanDoc;
    }
    string getMaSach() const
    {
        return this->strMaSach;
    }
    string getNgayMuon() const
    {
        return this->strNgayMuon;
    }
    string getNgayPhaiTra() const
    {
        return this->strNgayPhaiTra;
    }
    int getTinhTrangPhieu() const
    {
        return this->iTinhTrangPhieu;
    }
    void setSoTTPhieuMuon(int iSoTTPhieuMuon)
    {
        this->iSoTTPhieuMuon = iSoTTPhieuMuon;
    }
    void setMaBanDoc(string strMaBanDoc)
    {
        this->strMaBanDoc = strMaBanDoc;
    }
    void setMaSach(string strMaSach)
    {
        this->strMaSach = strMaSach;
    }
    void setNgayMuon(string ngayMuon)
    {
        this->strNgayMuon = ngayMuon;
    }
    void setNgayPhaiTra(string ngayPhaiTra)
    {
        this->strNgayPhaiTra = ngayPhaiTra;
    }
    void setTinhTrangPhieu(int iTinhTrangPhieu)
    {
        this->iTinhTrangPhieu = iTinhTrangPhieu;
    }
    friend istream &operator>>(istream &is, PhieuMuon &_phieumuon)
    {
        is >> _phieumuon.iSoTTPhieuMuon;
        is.ignore();
        getline(is, _phieumuon.strMaBanDoc);
        getline(is, _phieumuon.strMaSach);
        is >> _phieumuon.strNgayMuon;
        is >> _phieumuon.strNgayPhaiTra;
        is >> _phieumuon.iTinhTrangPhieu;
        is.ignore();
        return is;
    }
    friend ostream &operator<<(ostream &os, PhieuMuon _phieumuon)
    {
        os << _phieumuon.iSoTTPhieuMuon << endl;
        os << _phieumuon.strMaBanDoc << endl;
        os << _phieumuon.strMaSach << endl;
        os << _phieumuon.strNgayMuon << endl;
        os << _phieumuon.strNgayPhaiTra << endl;
        os << _phieumuon.iTinhTrangPhieu << endl;
        return os;
    }
};