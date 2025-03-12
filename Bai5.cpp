#include<iostream>
using namespace std;
class Ngay{
    private:
        int ngay, thang, nam;
    public:
        // Các hàm bạn của lớp Ngay
        friend bool namnhuan(int);
        friend int songaytrongthang(int , int);
        friend istream& operator>>(istream &in, Ngay &a);
        friend ostream& operator<<(ostream &out,const Ngay& a);
        // Hàm thành viên
        Ngay ngayketiep() const;
        Ngay ngaytruocdo() const;
        int thututrongnam() const;
};
// Hàm kiểm tra năm nhuận
// Input: Số nguyên n (năm cần kiểm tra)
// Output: Trả về true nếu là năm nhuận, false nếu không phải
bool namnhuan(int n){
    return (n%4==0&&n%100!=0)||(n%400==0);
}
// Hàm trả về số ngày trong một tháng của năm cụ thể
// Input: thang (số nguyên từ 1 đến 12), nam (số nguyên dương)
// Output: Số nguyên là số ngày trong tháng đó
int songaytrongthang(int thang, int nam){
    int nthang[]={0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(thang==2 && namnhuan(nam)) return 29;
    else return nthang[thang];
}
// Hàm nhập ngày, tháng, năm từ người dùng
// Input: Luồng nhập in từ bàn phím (các giá trị ngay, thang, nam)
// Output: Trả về đối tượng Ngay với dữ liệu hợp lệ
istream& operator>>(istream &in, Ngay &a){
    cout<<"Nhap ngay: "; in>>a.ngay;
    cout<<"Nhap thang: "; in>>a.thang;
    cout<<"Nhap nam: "; in>>a.nam;
    // Kiểm tra tính hợp lệ của ngày, tháng, năm
    while(a.nam<1||a.thang<1||a.thang>12||a.ngay<1||a.ngay>songaytrongthang(a.thang, a.nam)){
        cout<<"Ban nhap sai roi, moi ban nhap lai ";
        cout<<"Nhap ngay: "; in>>a.ngay;
        cout<<"Nhap thang: "; in>>a.thang;
        cout<<"Nhap nam: "; in>>a.nam;
    }
    return in;
}
// Hàm xuất ngày, tháng, năm ra màn hình
// Input: Đối tượng Ngay a
// Output: Chuỗi hiển thị theo định dạng ngay/thang/nam
ostream& operator<<(ostream &out,const Ngay& a){
    out<<a.ngay<<"/"<<a.thang<<"/"<<a.nam<<endl; 
    return out;
}
// Hàm trả về ngày kế tiếp
// Input: Không có đầu vào trực tiếp (sử dụng dữ liệu từ đối tượng Ngay gọi hàm)
// Output: Một đối tượng Ngay chứa ngày kế tiếp
Ngay Ngay::ngayketiep() const {
    Ngay next=*this;
    if(next.ngay<songaytrongthang(next.thang, next.nam)) next.ngay++; // Nếu chưa phải ngày cuối tháng thì tăng ngày
    else{
        next.ngay=1; // Reset ngày về 1
        if(next.thang==12){ // Nếu là tháng 12 thì sang năm mới
            next.thang=1;
            next.nam++;
        }
        else next.thang++; // Nếu không thì sang tháng tiếp theo
    }
    return next;
}
// Hàm trả về ngày trước đó
// Input: Không có đầu vào trực tiếp (sử dụng dữ liệu từ đối tượng Ngay gọi hàm)
// Output: Một đối tượng Ngay chứa ngày trước đó
Ngay Ngay::ngaytruocdo() const{
    Ngay prev=*this;
    if(prev.ngay>1) prev.ngay--; // Nếu chưa phải ngày đầu tháng thì giảm ngày
    else{
        if(prev.thang==1){ // Nếu là tháng 1 thì quay về tháng 12 năm trước
            prev.thang=12;
            prev.nam--;
        }
        else prev.thang--; // Nếu không thì lùi về tháng trước
        prev.ngay=songaytrongthang(prev.thang, prev.nam); // Lấy ngày cuối tháng trước
    }
    return prev;
}
// Hàm xác định thứ tự của ngày trong năm
// Input: Không có đầu vào trực tiếp (sử dụng dữ liệu từ đối tượng Ngay gọi hàm)
// Output: Trả về số nguyên là thứ tự ngày trong năm
int Ngay::thututrongnam() const{
    int dem=ngay;
    for(int i=1; i<thang; i++) dem+=songaytrongthang(i, nam); // Cộng dồn số ngày của các tháng trước đó
    return dem;
}
// Hàm chính
// Input: Nhập ngày, tháng, năm từ bàn phím
// Output: Hiển thị ngày hiện tại, ngày kế tiếp, ngày trước đó, và thứ tự trong năm
int main(){
    Ngay day;
    cin>>day; // Nhập ngày từ bàn phím
    cout<<"Ngay hien tai: "<<day;
    cout<<"Ngay ke tiep: "<<day.ngayketiep();
    cout<<"Ngay truoc do: "<<day.ngaytruocdo();
    cout<<"Ngay nay la ngay thu "<<day.thututrongnam()<<" trong nam"<<endl;
    return 0; 
}