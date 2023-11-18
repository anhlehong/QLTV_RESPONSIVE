#include"Header.h"

class Admin
{
private:
    string strUser, strPassword;
public:
    //Phuong thuc khoi tao, huy
    Admin()
    {
        this->strUser = "";
        this->strPassword = "";
    }
    Admin(string strUser, string strPassword)
    {
        this->strUser = strUser;
        this->strPassword = strPassword;
    }
    Admin(const Admin &_Admin)
    {
        this->strUser = _Admin.strUser;
        this->strPassword = _Admin.strPassword;
    }
    ~Admin(){}
    
    //Phuong thuc get
    string getUser() const
    {
        return this->strUser;
    }
    string getPassword() const 
    {
        return this->strPassword;
    }

    //Phuong thuc Set
    void setUser(string strUser)
    {
        this->strUser = strUser;
    }
    void setPassword(string strPassword)
    {
        this->strPassword = strPassword;
    }

    //Qua tai nhap xuat
    friend istream& operator >> (istream& is,Admin& _Admin)
		{
			is >> _Admin.strUser;
			is >> _Admin.strPassword;
			return is;
		}
    friend ostream& operator << (ostream& os,Admin _Admin)
		{
			os << _Admin.strUser << endl << _Admin.strPassword << endl;
			return os;
		}
};