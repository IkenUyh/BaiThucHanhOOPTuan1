#include<iostream>
#include<vector>
using namespace std;
class ChuyenBay{
    private:
        string ma, di, den;
        int ngay, thang, nam;
        int gio, phut;
    public:
        // Nhập thông tin chuyến bay từ bàn phím
        friend istream& operator>>(istream &in, ChuyenBay &x);
        // Xuất thông tin chuyến bay ra màn hình
        friend ostream& operator<<(ostream &out, ChuyenBay x);
        // So sánh hai chuyến bay dựa vào ngày, giờ khởi hành
        friend bool operator>(const ChuyenBay& x, const ChuyenBay& y);
        // Tìm chuyến bay theo mã
        void findma(const vector<ChuyenBay> nums, const string& ma);
        // Tìm chuyến bay theo nơi đi
        void findlocatedi(const vector<ChuyenBay> nums, const string& locate);
        // Tìm chuyến bay theo nơi đến
        void findlocateden(const vector<ChuyenBay> nums, const string& locate);
        // Sắp xếp danh sách chuyến bay theo thời gian
        void sapXep(vector<ChuyenBay>& nums);
        // Nhập danh sách chuyến bay
        void NhapCB(vector<ChuyenBay>& nums, int n);
        // Xuất danh sách chuyến bay
        void XuatCB(const vector<ChuyenBay>& nums, int n);
        // Đếm tổng số chuyến bay đi địa điểm này đến địa điểm khác
        int demChuyenBay(const vector<ChuyenBay>& nums, const string& noiDi, const string& noiDen);
};
// Hàm kiểm tra một ký tự có phải là ký tự hợp lệ cho mã chuyến bay không
// Đầu vào: một ký tự c
// Đầu ra: true nếu c là số hoặc chữ cái, false nếu ngược lại
bool isma(char c){
    return (c>='0'&&c<='9')||(c>='a'&&c<='z')||(c>='A'&&c<='Z');
}
// Hàm kiểm tra một ký tự có phải là ký tự hợp lệ cho địa điểm không
// Đầu vào: một ký tự c
// Đầu ra: true nếu c là chữ cái hoặc khoảng trắng, false nếu ngược lại
bool islocate(char c){
    return (c>='a'&&c<='z')||(c>='A'&&c<='Z')||(c==' ');
}
// Hàm kiểm tra mã chuyến bay có hợp lệ không
// Đầu vào: chuỗi mã chuyến bay
// Đầu ra: true nếu mã hợp lệ, false nếu ngược lại
bool checkma(const string& ma){
    if(ma.empty()||ma.size()>5) return false;
    for(char c:ma){
        if(!isma(c) || c==' ') return false;
    }
    return true;
}
// Hàm kiểm tra địa điểm có hợp lệ không
// Đầu vào: chuỗi địa điểm
// Đầu ra: true nếu địa điểm hợp lệ, false nếu ngược lại
bool checkdiadiem(const string& noi){
    if(noi.empty()||noi.size()>20) return false;
    for(char c:noi){
        if(!islocate(c)) return false;
    }
    return true;
}
// Hàm kiểm tra thời gian có hợp lệ không
// Đầu vào: giờ và phút
// Đầu ra: true nếu thời gian hợp lệ, false nếu ngược lại
bool checkclock(int gio, int phut){
    return (gio>=0&&gio<24&&phut>=0&&phut<60);
}
// Hàm kiểm tra năm có phải năm nhuận không
// Đầu vào: số nguyên năm
// Đầu ra: true nếu là năm nhuận, false nếu không
bool namNhuan(int n){ 
    return (n%4==0&&n%100!=0)||(n%400==0);
}
// Hàm trả về số ngày trong tháng của một năm nhất định
// Đầu vào: tháng và năm
// Đầu ra: số ngày của tháng đó
int Songaytrongnam(int thang, int nam){
    int nthang[]={0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(thang==2&&namNhuan(nam)) return 29;
    return nthang[thang];
}
// Hàm so sánh hai chuyến bay dựa trên thời gian khởi hành
// Đầu vào: hai đối tượng ChuyenBay x, y
// Đầu ra: true nếu x khởi hành sau y, false nếu ngược lại
bool operator>(const ChuyenBay& x, const ChuyenBay& y){
    if(x.nam!=y.nam) return x.nam>y.nam;
    if(x.thang!=y.thang) return x.thang>y.thang;
    if(x.ngay!=y.ngay) return x.ngay>y.ngay;
    return x.gio>y.gio;
}
// Chuyển đổi chuỗi sang chữ thường
// Đầu vào: Chuỗi ký tự
// Đầu ra: Chuỗi đã chuyển sang chữ thường
string tolowerCase(string str){
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}
// Hàm nhập thông tin chuyến bay từ bàn phím
// Đầu vào: luồng nhập in, đối tượng ChuyenBay x
// Đầu ra: luồng nhập in
istream& operator>>(istream &in, ChuyenBay &x){
    in.ignore();
    cout<<"Nhap vao ma chuyen bay: "; getline(in, x.ma);
    while(!checkma(x.ma)){
        cout<<"Ma khong hop le! xin vui long nhap lai ma moi: "; getline(in, x.ma);
    }
    cout<<"Nhap dia diem di: "; getline(in, x.di);
    while(!checkdiadiem(x.di)){
        cout<<"Diem di khong hop le! moi ban nhap lai: "; getline(in, x.di);
    }
    cout<<"Nhap dia diem den: "; getline(in, x.den);
    while(!checkdiadiem(x.den)){
        cout<<"Diem den khong hop le! moi ban nhap lai: "; getline(in, x.den);
    }
    cout<<"Nhap ngay: "; in>>x.ngay;
    cout<<"Nhap thang: "; in>>x.thang;
    cout<<"Nhap nam: "; in>>x.nam;
    while(x.nam<1||x.thang<1||x.thang>12||x.ngay<1||x.ngay>Songaytrongnam(x.thang, x.nam)){
        cout<<"Khong ton tai ngay hoac thang hoac nam, moi ban nhap lai: "<<endl;
        cout<<"Nhap ngay: "; in>>x.ngay;
        cout<<"Nhap thang: "; in>>x.thang;
        cout<<"Nhap nam: "; in>>x.nam;
    }
    cout<<"Nhap thoi gian khoi hanh: "<<endl;
    cout<<"Nhap gio: "; in>>x.gio;
    cout<<"Nhap phut: "; in>>x.phut;
    while(!checkclock(x.gio, x.phut)){
        cout<<"Thoi gian khoi hanh khong ton tai! moi ban nhap lai"<<endl;
        cout<<"Nhap gio: "; in>>x.gio;
        cout<<"Nhap phut: "; in>>x.phut;
    }
    return in;
}
// Hàm xuất thông tin chuyến bay ra màn hình
// Đầu vào: luồng xuất out, đối tượng ChuyenBay x
// Đầu ra: luồng xuất out
ostream& operator<<(ostream &out, ChuyenBay x){
    out<<"Ma chuyen bay: "<<x.ma<<endl;
    out<<"Ngay bay: "<<x.ngay<<"/"<<x.thang<<"/"<<x.nam<<endl;
    if(x.gio<10&&x.phut<10) out<<"Thoi gian khoi hanh: 0"<<x.gio<<":0"<<x.phut<<endl;
    else if(x.gio<10) out<<"Thoi gian khoi hanh: 0"<<x.gio<<":"<<x.phut<<endl;
    else if(x.phut<10) out<<"Thoi gian khoi hanh: "<<x.gio<<":0"<<x.phut<<endl;
    else out<<"Thoi gian khoi hanh: "<<x.gio<<":"<<x.phut<<endl;
    out<<"Dia diem di: "<<x.di<<endl;
    out<<"Diem diem den: "<<x.den<<endl;
    out<<"==============================================================\n";
    return out;
}
// Hàm nhập danh sách chuyến bay
// Đầu vào: danh sách chuyến bay nums, số lượng chuyến bay n
// Đầu ra: danh sách chuyến bay nums sau khi nhập
void ChuyenBay::NhapCB(vector<ChuyenBay>& nums, int n){
    for(int i=0; i<n; i++){
        cout<<"Nhap thong tin chuyen bay "<<i+1<<": "<<endl;
        ChuyenBay x; cin>>x;
        nums.push_back(x);
    }
}
// Hàm xuất danh sách chuyến bay
// Đầu vào: danh sách chuyến bay nums, số lượng chuyến bay n
// Đầu ra: thông tin chuyến bay hiển thị trên màn hình
void ChuyenBay::XuatCB(const vector<ChuyenBay>& nums, int n){
    cout<<"\n================ DANH SACH CHUYEN BAY ================\n";
    for(int i=0; i<n; i++){
        cout<<"Thong tin chuyen bay thu "<<i+1<<": "<<endl;
        cout<<nums[i];
    }
}
// Hàm tìm chuyến bay theo địa điểm đi
// Đầu vào: danh sách chuyến bay nums, địa điểm cần tìm locate
// Đầu ra: danh sách chuyến bay có địa điểm đi trùng với locate
void ChuyenBay::findlocatedi(const vector<ChuyenBay> nums, const string& locate){
    cout<<"\n===== KET QUA TIM KIEM =====\n";
    bool found=false;
    string keyword=tolowerCase(locate);
    for(const auto& x:nums){
        string tmp=tolowerCase(x.di);
        if(tmp.find(keyword)!=string::npos){
            cout<<x; found=true;
        }
    }
    if(!found) cout<<"Khong ton tai chuyen bao di "<<locate<<endl<<"===================================\n";
}
// Hàm tìm chuyến bay theo địa điểm đến
// Đầu vào: danh sách chuyến bay nums, địa điểm cần tìm locate
// Đầu ra: danh sách chuyến bay có địa điểm đến trùng với locate
void ChuyenBay::findlocateden(const vector<ChuyenBay> nums, const string& locate){
    cout<<"\n===== KET QUA TIM KIEM =====\n";
    bool found=false;
    string keyword=tolowerCase(locate);
    for(const auto& x:nums){
        string tmp=tolowerCase(x.den);
        if(tmp.find(keyword)!=string::npos){
            cout<<x; found=true;
        }
    }
    if(!found) cout<<"Khong ton tai chuyen bao den "<<locate<<endl<<"===================================\n";
}
// Hàm tìm chuyến bay theo mã
// Đầu vào: danh sách chuyến bay nums, mã chuyến bay cần tìm ma
// Đầu ra: chuyến bay có mã trùng với ma
void ChuyenBay::findma(const vector<ChuyenBay> nums, const string& ma){ 
    cout<<"\n===== KET QUA TIM KIEM =====\n";
    bool found=false;
    string keyword=tolowerCase(ma);
    for(const auto& x:nums){
        string tmp=tolowerCase(x.ma);
        if(tmp.find(keyword)!=string::npos){
            cout<<x; found=true;
        }
    }
    if(!found) cout<<"Khong ton tai ma "<<ma<<endl<<"===================================\n";
}
// Hàm sắp xếp danh sách chuyến bay theo thời gian khởi hành
// Đầu vào: danh sách chuyến bay nums
// Đầu ra: danh sách chuyến bay được sắp xếp theo thời gian
void ChuyenBay::sapXep(vector<ChuyenBay>& nums){
    int n=nums.size();
    for(int i=0; i<n-1; i++){
        for(int j=i+1; j<n; j++){
            if(nums[i]>nums[j]) swap(nums[i], nums[j]);
        }
    }
}
// Hàm đếm số chuyến bay giữa hai địa điểm
// Đầu vào: danh sách chuyến bay nums, địa điểm đi noiDi, địa điểm đến noiDen
// Đầu ra: số chuyến bay thỏa mãn điều kiện
int ChuyenBay::demChuyenBay(const vector<ChuyenBay>& nums, const string& noiDi, const string& noiDen){
    int cnt=0;
    for(const auto& x:nums){
        if(x.di==noiDi&&x.den==noiDen) cnt++;
    }
    return cnt;
}
int main(){
    cout<<"Nhap so luong chuyen bay: ";
    int n; cin>>n;
    vector<ChuyenBay> nums;
    ChuyenBay plane;
    plane.NhapCB(nums, n);
    plane.sapXep(nums);
    plane.XuatCB(nums, n);
    while(true){
        cout<<"\n===== MENU =====\n";
        cout<<"0. Thoat chuong trinh\n";
        cout<<"1. Nhap ma chuyen bay can tim\n";
        cout<<"2. Nhap noi khoi hanh chuyen bay can tim\n";
        cout<<"3. Nhap noi den chuyen bay can tim\n";
        cout<<"Lua chon cua ban la: ";
        int chon; cin>>chon;
        if(!chon){
            cout<<"Dang thoat chuong trinh...."<<endl;
            break;
        }
        else if(chon==1){
            cin.ignore();
            string keyword;
            cout<<"Nhap ma chuyen bay: "; getline(cin, keyword);
            while(!checkma(keyword)){
                cout<<"Ma khong hop le! xin vui long nhap lai ma moi: "; getline(cin, keyword);
            }
            plane.findma(nums, keyword);
        }
        else if(chon==2){
            cin.ignore();
            string keyword;
            cout<<"Nhap dia diem di: "; getline(cin, keyword);
            while(!checkdiadiem(keyword)){
                cout<<"Diem di khong hop le! moi ban nhap lai: "; getline(cin, keyword);
            }
            plane.findlocatedi(nums, keyword);
        }
        else if(chon==3){
            cin.ignore();
            string keyword;
            cout<<"Nhap dia diem den: "; getline(cin, keyword);
            while(!checkdiadiem(keyword)){
                cout<<"Diem den khong hop le! moi ban nhap lai: "; getline(cin, keyword);
            }
            plane.findlocateden(nums, keyword);
        }
        else{
            cout<<"Ban nhap sai roi, moi ban nhap lai"<<endl;
        }
    }
}
/*
10

VN109
Hue	
HCM
30
11
2025	
12	
12

VN107	
Hanoi	
HCM	
29	
5	
2025	
18	
5

VN103	
HCM	
Phuquoc	
23	
8	
2025	
7	
0

VN110	
HCM	
Danang	
21	
12	
2025	
16	
45

VN105	
HCM	
Danang	
17	
7	
2025	
20	
20

VN102	
Danang	
Hanoi	
5	
6	
2025	
9	
15

VN108	
Danang	
Hue	
9	
9	
2025	
5	
55

VN106	
Cantho	
Hanoi	
11	
4	
2025	
15	
10

VN101	
Hanoi	
HCM	
12	
3	
2025	
14	
30

VN104	
Hanoi	
Hue	
1	
1	
2025	
6	
45
*/