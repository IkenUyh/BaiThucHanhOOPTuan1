#include<iostream>
using namespace std;
#define ll long long
#define endl "\n"
// Hàm tìm ước chung lớn nhất (GCD) của hai số nguyên
// Đầu vào: hai số nguyên a, b
// Đầu ra: ước chung lớn nhất của a và b
inline ll gcd(ll a, ll b){ll r; while(b){r=a%b;a=b;b=r;} return a;}
// Hàm tìm bội chung nhỏ nhất (LCM) của hai số nguyên
// Đầu vào: hai số nguyên a, b
// Đầu ra: bội chung nhỏ nhất của a và b
inline ll lcm(ll a, ll b){return a/gcd(a, b)*b;}
// Lớp Phân Số
class PhanSo{
    private:
        int tu, mau; // Tử số và mẫu số
    public:
        PhanSo(); // Hàm dựng mặc định
        PhanSo(int, int); // Hàm dựng có tham số
        friend istream& operator>>(istream &in, PhanSo &a); // Toán tử nhập
        friend ostream& operator<<(ostream &out, PhanSo a); // Toán tử xuất
        void rutgon(); // Hàm rút gọn phân số
        friend PhanSo operator+(PhanSo a, PhanSo b); // Toán tử cộng
        friend PhanSo operator-(PhanSo a, PhanSo b); // Toán tử trừ
        friend PhanSo operator*(PhanSo a, PhanSo b); // Toán tử nhân
        friend PhanSo operator/(PhanSo a, PhanSo b); // Toán tử chia
};
// Hàm dựng mặc định
// Đầu vào: không có
// Đầu ra: khởi tạo phân số với tử và mẫu bằng 0
PhanSo::PhanSo(){
    tu=mau=0;
}
// Hàm dựng có tham số
// Đầu vào: tử số tu, mẫu số mau
// Đầu ra: khởi tạo phân số với tử và mẫu được chỉ định
PhanSo::PhanSo(int tu, int mau){
    this->tu=tu;
    this->mau=mau;
}
// Toán tử nhập
// Đầu vào: đối tượng istream, phân số a
// Đầu ra: nhập tử và mẫu số từ bàn phím, kiểm tra mẫu số khác 0
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
// Hàm rút gọn phân số
// Đầu vào: không có (làm việc với tử và mẫu của chính đối tượng)
// Đầu ra: phân số được rút gọn
void PhanSo::rutgon(){
    int ucln=gcd(abs(tu), abs(mau)); // Tìm GCD của tử và mẫu
    tu/=ucln; mau/=ucln; // Chia tử và mẫu cho GCD
    // Đảm bảo mẫu luôn dương (quy ước chung của phân số)
    if(mau<0){
        tu=-tu;
        mau=-mau;
    }
}
// Toán tử xuất
// Đầu vào: đối tượng ostream, phân số a
// Đầu ra: hiển thị phân số dưới dạng tối giản
ostream& operator<<(ostream &out, PhanSo a){
    a.rutgon();
    if(!a.tu){
        out<<"Phan so la so 0"; return out;
    }
    else if(a.mau==1) out<<"Phan So la so "<<a.tu;
    else out<<"Phan So la so "<<a.tu<<"/"<<a.mau;
    return out;
}
// Toán tử cộng hai phân số
// Đầu vào: hai phân số a, b
// Đầu ra: tổng của hai phân số dưới dạng rút gọn
PhanSo operator+(PhanSo a, PhanSo b){
    a.rutgon(); b.rutgon();
    int bcnn=lcm(a.mau, b.mau); // Tìm bội chung nhỏ nhất của mẫu số
    a.tu*=(bcnn/a.mau); b.tu*=(bcnn/b.mau);
    PhanSo c;
    c.tu=a.tu+b.tu; c.mau=bcnn;
    return c;
}
// Toán tử trừ hai phân số
// Đầu vào: hai phân số a, b
// Đầu ra: hiệu của hai phân số dưới dạng rút gọn
PhanSo operator-(PhanSo a, PhanSo b){
    a.rutgon(); b.rutgon();
    int bcnn=lcm(a.mau, b.mau);
    a.tu*=(bcnn/a.mau); b.tu*=(bcnn/b.mau);
    PhanSo c;
    c.tu=a.tu-b.tu;
    c.mau=bcnn;
    return c;
}
// Toán tử nhân hai phân số
// Đầu vào: hai phân số a, b
// Đầu ra: tích của hai phân số dưới dạng rút gọn
PhanSo operator*(PhanSo a, PhanSo b){
    a.rutgon(); b.rutgon();
    PhanSo c;
    c.tu=a.tu*b.tu; c.mau=a.mau*b.mau;
    return c;
}
// Toán tử chia hai phân số
// Đầu vào: hai phân số a, b
// Đầu ra: thương của hai phân số dưới dạng rút gọn, kiểm tra b.tu khác 0
PhanSo operator/(PhanSo a, PhanSo b){
    a.rutgon(); b.rutgon();
    PhanSo c;
    if(!b.tu){ // Kiểm tra tử số của b không được là 0 để tránh lỗi chia cho 0
        cout<<"Phan so thu 2 tu khong duoc la 0"<<endl;
        return PhanSo(0, 1);
    }
    c.tu=a.tu*b.mau; c.mau=a.mau*b.tu;
    return c;
}
int main(){
try_again:
    PhanSo a, b;
    cout<<"Nhap phan so thu nhat: "<<endl; cin>>a;
    cout<<"Nhap phan so thu hai: "<<endl; cin>>b;
    while(true){
                cout<<"Ban co cac lua chon la:"<<endl;
                cout<<"1. Thoat chuong trinh"<<endl;
                cout<<"2. Tinh tong 2 phan so"<<endl;
                cout<<"3. Tinh hieu 2 phan so"<<endl;
                cout<<"4. Tinh tich 2 phan so"<<endl;
                cout<<"5. Tinh thuong 2 phan so"<<endl;
                cout<<"6. Toi muon doi phan so khac"<<endl;
                cout<<"Lua chon cua ban la:"<<endl;
                int chon; cin>>chon;
                if(chon==1){
                    cout<<"Dang thoat chuong trinh...."<<endl;
                    break;
                }
                else if(chon==2){
                    cout<<"Tong 2 phan so la: "<<(a+b)<<endl;
                }
                else if(chon==3){
                    cout<<"Hieu 2 phan so la: "<<(a-b)<<endl; 
                }
                else if(chon==4){
                    cout<<"Tich 2 phan so la: "<<(a*b)<<endl;
                }
                else if(chon==5){
                    cout<<"Thuong 2 phan so la: "<<(a/b)<<endl; 
                }
                else if(chon==6) goto try_again;
                else cout<<"Ban nhap sai roi, moi ban nhap lai"<<endl;
            }
    return 0;
}