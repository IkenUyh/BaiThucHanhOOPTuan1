#include<iostream>
using namespace std;
#define ll long long
/*
Hàm tính ước chung lớn nhất (GCD) của hai số nguyên
Đầu vào: hai số nguyên a, b
Đầu ra: giá trị GCD của a và b
 */
inline ll gcd(ll a, ll b){ll r; while(b){r=a%b;a=b;b=r;} return a;}
class PhanSo{
    private:
        int tu, mau; // Tử số và mẫu số của phân số
    public:
        // Hàm nhập phân số từ bàn phím (nạp chồng toán tử >>)
        friend istream& operator>>(istream &in, PhanSo &a);
        // Hàm xuất phân số ra màn hình (nạp chồng toán tử <<)
        friend ostream& operator<<(ostream &out, PhanSo a);
        // Hàm rút gọn phân số
        void rutgon();
};
/*
Hàm rút gọn phân số bằng cách chia tử và mẫu cho GCD
Đầu vào: không có
Đầu ra: không có, nhưng giá trị của tử và mẫu sẽ được cập nhật
 */
void PhanSo::rutgon(){
    int ucln=gcd(abs(tu), abs(mau)); // Tìm GCD của tử và mẫu
    tu/=ucln; mau/=ucln; // Chia tử và mẫu cho GCD
    // Đảm bảo mẫu luôn dương (quy ước chung của phân số)
    if(mau<0){
        tu=-tu;
        mau=-mau;
    }
}
/*
Hàm nhập phân số từ bàn phím
Đầu vào: luồng nhập (istream)
Đầu ra: phân số a (thông qua tham chiếu)
 */
istream& operator>>(istream &in, PhanSo &a){
    cout<<"Nhap tu so: "; in>>a.tu;
    cout<<"Nhap mau so: "; in>>a.mau;
    // Kiểm tra nếu mẫu số nhập vào là 0 thì yêu cầu nhập lại
    while(!a.mau){
        cout<<"Nhap lai mau so khac 0: ";
        in>>a.mau;
    }
    return in;
}
/*
Hàm xuất phân số ra màn hình
Đầu vào: luồng xuất (ostream)
Đầu ra: phân số a được in ra màn hình
 */
ostream& operator<<(ostream &out, PhanSo a){
    if(!a.tu){
        out<<"Phan so la so 0"; return out;
    }
    else if(a.mau==1) out<<"Phan So la so "<<a.tu;
    else out<<"Phan So la so "<<a.tu<<"/"<<a.mau;
    return out;
}
/*
Hàm main để chạy chương trình chính
Nhập một phân số, rút gọn, và in kết quả ra màn hình
 */
int main(){
    PhanSo a;
    cin>>a; // Nhập phân số
    a.rutgon(); // Rút gọn phân số
    cout<<a<<endl; // Xuất phân số sau khi rút gọn
    return 0;
}
