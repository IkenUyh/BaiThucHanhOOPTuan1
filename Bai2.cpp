#include<iostream>
using namespace std;
#define ll long long
/*
Hàm tính ước chung lớn nhất (GCD) của hai số nguyên
Đầu vào: hai số nguyên a, b
Đầu ra: giá trị GCD của a và b
 */
inline ll gcd(ll a, ll b){ll r; while(b){r=a%b;a=b;b=r;} return a;}
/*
Hàm tính bội chung nhỏ nhất (LCM) của hai số nguyên
Đầu vào: hai số nguyên a, b
Đầu ra: giá trị LCM của a và b
*/
inline ll lcm(ll a, ll b){return a/gcd(a, b)*b;}
/*
Lớp PhanSo để làm việc với phân số
Gồm các thuộc tính: tử số (tu) và mẫu số (mau)
 */
class PhanSo{
    private:
        int tu, mau; // Tử số và mẫu số
    public:
        // Nạp chồng toán tử nhập xuất để làm việc với đối tượng PhanSo
        friend istream& operator>>(istream& in, PhanSo &a);
        friend ostream& operator<<(ostream& out, PhanSo a);
        // Hàm rút gọn phân số về dạng tối giản
        void rutgon();
        // Hàm tìm phân số lớn hơn giữa hai phân số
        friend PhanSo find(PhanSo, PhanSo);
};
/*
Hàm rút gọn phân số
Đầu vào: không có (sử dụng trực tiếp trên đối tượng PhanSo)
Đầu ra: phân số được rút gọn tối giản
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
Nạp chồng toán tử nhập '>>' để nhập phân số từ bàn phím
Đầu vào: luồng nhập (cin), đối tượng phân số a
Đầu ra: không có (nhập dữ liệu trực tiếp vào đối tượng a)
 */
istream& operator>>(istream& in, PhanSo &a){
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
Nạp chồng toán tử xuất '<<' để hiển thị phân số ra màn hình
Đầu vào: luồng xuất (cout), đối tượng phân số a
Đầu ra: hiển thị phân số đã được rút gọn
 */
ostream& operator<<(ostream &out, PhanSo a){
    a.rutgon(); // Đảm bảo phân số luôn được rút gọn trước khi in
    if(!a.tu){ // Nếu tử số là 0 thì in ra 0
        out<<"0"; return out;
    }
    else if(a.mau==1) out<<a.tu; // Nếu mẫu số là 1 thì chỉ in tử số
    else out<<a.tu<<"/"<<a.mau; // In phân số ở dạng tu/mau
    return out;
}
/*
Hàm tìm phân số lớn hơn giữa hai phân số
Đầu vào: hai phân số a, b
Đầu ra: phân số lớn hơn giữa a và b
 */
PhanSo find(PhanSo a, PhanSo b){
    a.rutgon(); b.rutgon();
    // So sánh hai phân số bằng cách quy về phép nhân chéo
    if(a.tu*b.mau>b.tu*a.mau) return a;
    else return b;
}
int main(){
    PhanSo a, b;
    cout<<"Nhap phan so thu nhat: "<<endl; cin>>a;
    cout<<"Nhap phan so thu hai: "<<endl; cin>>b;
    cout<<"Phan so lon nhat la: "<<find(a, b);
    return 0;
}