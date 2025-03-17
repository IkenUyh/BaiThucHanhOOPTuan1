#include<iostream>
#include<vector>
#include<sstream>
using namespace std;
class SoTK{
    private:
        string ma, type, name, cmnd;
        int ngay, thang, nam;
        double money;
    public:
        // Nhập thông tin sổ tiết kiệm
        friend istream& operator>>(istream &in, SoTK &a);
        // Xuất thông tin sổ tiết kiệm
        friend ostream& operator<<(ostream &out, SoTK a);
        // So sánh sổ tiết kiệm theo ngày mở tài khoản
        friend bool operator>(const SoTK& x, const SoTK& y);
        friend bool operator<(const SoTK& x, const SoTK&y);
        // Nhập danh sách sổ tiết kiệm
        void nhapSoTK(vector<SoTK> &nums, int n);
        // Xuất danh sách sổ tiết kiệm
        void xuatSoTK(const vector<SoTK>& nums, int n);
        // Tìm kiếm sổ tiết kiệm theo mã số
        void timkiemma(const vector<SoTK>& nums, const string& ma);
        // Tìm kiếm sổ tiết kiệm theo CMND khách hàng
        void timkiemcmnd(const vector<SoTK>& nums, const string& cmnd);
         // Liệt kê sổ tiết kiệm được mở trong khoảng thời gian chỉ định
        void lietKeintime(const vector<SoTK>& nums, int tuNgay, int tuThang, int tuNam, int denNgay, int denThang, int denNam);
        // Tính lãi suất cho một sổ tiết kiệm
        void tienLai(SoTK& x, double laisuat, int thang);
        // Cập nhật lãi suất cho tất cả sổ tiết kiệm trong danh sách
        void capnhatlaiSuat(vector<SoTK>& nums, double laisuat);
        // Rút tiền từ sổ tiết kiệm
        void rutTien(SoTK& x, double sotienrut);
        // Sắp xếp danh sách sổ tiết kiệm theo ngày mở tài khoản tăng dần
        void NgaytangDan(vector<SoTK> &nums);
        // Sắp xếp danh sách sổ tiết kiệm theo số tiền giảm dần
        void TiengiamDan(vector<SoTK>& nums);
};
// Hàm kiểm tra ký tự có phải là chữ cái hoặc số không
// Đầu vào: Ký tự c
// Đầu ra: True nếu là chữ cái hoặc số, False nếu không
bool isma(char c){
    return (c>='0'&&c<='9')||(c>='a'&&c<='z')||(c>='A'&&c<='Z');
}
// Kiểm tra mã số tiết kiệm có hợp lệ không
// Đầu vào: Chuỗi mã số tiết kiệm
// Đầu ra: True nếu hợp lệ, False nếu không hợp lệ
bool kiemTraMaSo(const string &maSo){
    if(maSo.empty()||maSo.size()>5) return false;
    for(char c:maSo){
        if(!isma(c) || c==' ') return false;
    }
    return true;
}
// Kiểm tra loại tiết kiệm có hợp lệ không
// Đầu vào: Chuỗi loại tiết kiệm
// Đầu ra: True nếu hợp lệ, False nếu không hợp lệ
bool checktype(const string& type){
    return (!type.empty())&&(type.size()<=10);
}
// Kiểm tra ký tự có phải là chữ cái hoặc khoảng trắng không
// Đầu vào: Ký tự c
// Đầu ra: True nếu là chữ cái hoặc khoảng trắng, False nếu không
bool isname(char c){
    return (c>='a'&&c<='z')||(c>='A'&&c<='Z')||(c==' ');
}
// Kiểm tra họ tên có hợp lệ không
// Đầu vào: Chuỗi họ tên
// Đầu ra: True nếu hợp lệ, False nếu không hợp lệ
bool kiemTraHoTen(const string &hoTen){
    if(hoTen.empty()||hoTen.size()>30) return false;
    for(const auto& x:hoTen){
        if(!isname(x)) return false;
    }
    return true;
}
// Kiểm tra số chứng minh nhân dân có hợp lệ không
// Đầu vào: Chuỗi CMND
// Đầu ra: True nếu hợp lệ (9 hoặc 12 chữ số), False nếu không hợp lệ
bool kiemTraCMND(const string &cmnd){
    return cmnd.size()==9||cmnd.size()==12;
}
// Kiểm tra năm nhuận
// Đầu vào: Số nguyên năm
// Đầu ra: True nếu là năm nhuận, False nếu không
bool namNhuan(int n){ 
    return (n%4==0&&n%100!=0)||(n%400==0);
}
// Trả về số ngày trong tháng của một năm cụ thể
// Đầu vào: Tháng và năm
// Đầu ra: Số ngày trong tháng
int Songaytrongnam(int thang, int nam){
    int nthang[]={0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(thang==2 && namNhuan(nam)) return 29;
    return nthang[thang];
}
// Nhập thông tin cho sổ tiết kiệm từ bàn phím
// Đầu vào: Đối tượng SoTK
// Đầu ra: Dữ liệu được nhập vào đối tượng
istream& operator>>(istream &in, SoTK &a){
    in.ignore();
    cout<<"Nhap ma so tiet kiem: "; in>>a.ma;
    while(!kiemTraMaSo(a.ma)){
        cout<<"Ma so khong hop le! Moi ban nhap lai: "; in>>a.ma;
    }
    in.ignore();
    cout<<"Nhap loai tiet kiem: "; getline(in, a.type);
    while(!checktype(a.type)){
        cout<<"Loai tiet kiem khong hop le! Moi ban nhap lai: "; getline(in, a.type);
    }
    cout<<"Nhap ho ten khach hang: "; getline(in, a.name);
    while(!kiemTraHoTen(a.name)){
        cout<<"Ho ten khong hop le! Moi ban nhap lai: "; getline(in, a.name);
    }
    cout<<"Nhap chung minh nhan dan: "; in>>a.cmnd;
    while(!kiemTraCMND(a.cmnd)){
        cout<<"Chung minh nhan dan khong ton tai! Moi ban nhap lai: "; in>>a.cmnd;
    }
    cout<<"Nhap ngay mo so: "; in>>a.ngay;
    cout<<"Nhap thang mo so: "; in>>a.thang;
    cout<<"Nhap nam mo so: "; in>>a.nam;
    while(a.nam<1||a.thang<1||a.thang>12||a.ngay<1||a.ngay>Songaytrongnam(a.thang, a.nam)){
        cout<<"Khong ton tai ngay hoac thang hoac nam! Moi ban nhap lai: "<<endl;
        cout<<"Nhap ngay: "; in>>a.ngay;
        cout<<"Nhap thang: "; in>>a.thang;
        cout<<"Nhap nam: "; in>>a.nam;
    }
    cout<<"Nhap so tien gui: "; in>>a.money;
    while(a.money<=0){
        cout<<"So tien gui khong hop le! Moi ban nhap lai"; in>>a.money;
    }
    return in;
}
// Xuất thông tin của sổ tiết kiệm ra màn hình
// Đầu vào: Đối tượng SoTK
// Đầu ra: Hiển thị thông tin sổ tiết kiệm
ostream& operator<<(ostream& out, SoTK a){
    out<<"Ma so tiet kiem: "<<a.ma<<endl;
    out<<"Loai tiet kiem: "<<a.type<<endl;
    out<<"Ho ten khach hang: "<<a.name<<endl;
    out<<"Chung minh nhan dan: "<<a.cmnd<<endl;
    out<<"Thoi gian mo so: "<<a.ngay<<"/"<<a.thang<<"/"<<a.nam<<endl;
    out<<"So tien gui: "<<a.money<<" VND"<<endl;
    out<<"==============================================================\n";
    return out;
}
// So sánh ngày mở sổ giữa hai sổ tiết kiệm
// Đầu vào: Hai đối tượng SoTK
// Đầu ra: True nếu x có ngày mở sổ muộn hơn y, False nếu ngược lại
bool operator>(const SoTK& x, const SoTK& y){
    if(x.nam!=y.nam) return x.nam>y.nam;
    if(x.thang!=y.thang) return x.thang>y.thang;
    return x.ngay>y.ngay;
}
// So sánh số tiền giữa hai sổ tiết kiệm
// Đầu vào: Hai đối tượng SoTK
// Đầu ra: True nếu x có số tiền nhỏ hơn y, False nếu ngược lại
bool operator<(const SoTK& x, const SoTK&y){
    return x.money<y.money;
}
// Sắp xếp danh sách sổ tiết kiệm theo ngày mở sổ tăng dần
// Đầu vào: Vector nums chứa danh sách sổ tiết kiệm
// Đầu ra: Danh sách được sắp xếp theo ngày tăng dần
void SoTK::NgaytangDan(vector<SoTK> &nums){
    int n=nums.size();
    for(int i=0; i<n-1; i++){
        for(int j=i+1; j<n; j++){
            if(nums[i]>nums[j]) swap(nums[i], nums[j]);
        }
    }
}
// Sắp xếp danh sách sổ tiết kiệm theo số tiền giảm dần
// Đầu vào: Vector nums chứa danh sách sổ tiết kiệm
// Đầu ra: Danh sách được sắp xếp theo số tiền giảm dần
void SoTK::TiengiamDan(vector<SoTK>& nums){
    int n=nums.size();
    for(int i=0; i<n-1; i++){
        for(int j=i+1; j<n; j++){
            if(nums[i]<nums[j]) swap(nums[i], nums[j]);
        }
    }
}
// Rút tiền từ sổ tiết kiệm
// Đầu vào: Đối tượng SoTK, số tiền cần rút
// Đầu ra: Cập nhật số tiền trong tài khoản
void SoTK::rutTien(SoTK& x, double sotienrut){
    if(sotienrut>x.money) cout<<"So tien rut vuot qua so du hien co"<<endl;
    else{
        x.money-=sotienrut;
        cout<<"Ban da rut thanh cong "<<sotienrut<<" VND. So du con lai: "<<x.money<<" VND"<<endl;
    }
}
// Nhập danh sách n sổ tiết kiệm
// Đầu vào: Vector nums chứa danh sách sổ, số nguyên n là số lượng sổ cần nhập
// Đầu ra: Cập nhật danh sách nums
void SoTK::nhapSoTK(vector<SoTK> &nums, int n){
    for(int i=0; i<n; i++){
        cout<<"Nhap thong tin so tiet kiem thu "<<i+1<<": "<<endl;
        SoTK x; cin>>x;
        nums.push_back(x);
    }
}  
// Xuất danh sách sổ tiết kiệm
// Đầu vào: Vector nums chứa danh sách sổ, số nguyên n là số lượng sổ cần xuất
// Đầu ra: Hiển thị thông tin của các sổ
void SoTK::xuatSoTK(const vector<SoTK>& nums, int n){
    cout<<"\n================ THONG TIN SO TIET KIEM ================\n";
    for(int i=0; i<n; i++){
        cout<<"Thong tin so tiet kiem thu "<<i+1<<": "<<endl;
        cout<<nums[i];
    }
}
// Chuyển đổi chuỗi thành chữ thường
// Đầu vào: Chuỗi str
// Đầu ra: Chuỗi str sau khi được chuyển thành chữ thường
string tolowerCase(string str){
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}
// Tìm kiếm sổ tiết kiệm theo mã
// Đầu vào: Danh sách sổ nums, chuỗi mã sổ ma
// Đầu ra: Hiển thị thông tin sổ tiết kiệm nếu tìm thấy
void SoTK::timkiemma(const vector<SoTK>& nums, const string& ma){
    cout<<"\n===== KET QUA TIM KIEM =====\n";
    bool found=false;
    string keyword=tolowerCase(ma);
    for(const auto& x:nums){
        string tmp=tolowerCase(x.ma);
        if(tmp.find(keyword)!=string::npos){
            cout<<x; found=true;
        }
    }
    if(!found) cout<<"Khong ton tai ma so tiet kiem "<<ma<<endl<<"===================================\n";
}
// Tìm kiếm sổ tiết kiệm theo CMND
// Đầu vào: Danh sách sổ nums, chuỗi CMND cmnd
// Đầu ra: Hiển thị thông tin sổ tiết kiệm nếu tìm thấy
void SoTK::timkiemcmnd(const vector<SoTK>& nums, const string& cmnd){
    cout<<"\n===== KET QUA TIM KIEM =====\n";
    for(const auto& x:nums){
        if(x.cmnd==cmnd){
            cout<<x; return;
        }
    }
    cout<<"Khong tim thay so tiet kiem "<<endl<<"===================================\n";;
}
// Chuyển đổi ngày, tháng, năm thành một số nguyên để tiện so sánh
// Đầu vào: Số nguyên ngày, tháng, năm
// Đầu ra: Một số nguyên đại diện cho ngày đó
int chuyenNgayThanhSo(int ngay, int thang, int nam) {
    return nam*10000+thang*100+ngay;
}
// Liệt kê sổ tiết kiệm trong khoảng thời gian nhất định
// Đầu vào: Danh sách sổ tiết kiệm, khoảng thời gian từ ngày/tháng/năm đến ngày/tháng/năm
// Đầu ra: Các sổ tiết kiệm mở trong khoảng thời gian này
void SoTK::lietKeintime(const vector<SoTK>& nums, int tuNgay, int tuThang, int tuNam, int denNgay, int denThang, int denNam){
    int ngayBD=chuyenNgayThanhSo(tuNgay, tuThang, tuNam);
    int ngayKT=chuyenNgayThanhSo(denNgay, denThang, denNam);
    cout<<"Cac so tiet kiem mo trong khoang "<<tuNgay<<"/"<<tuThang<<"/"<<tuNam<<" - "<<denNgay<<"/"<<denThang<<"/"<<denNam<<": "<<endl;
    for(const auto& x:nums){
        int ngayMo=chuyenNgayThanhSo(x.ngay, x.thang, x.nam);
        if(ngayMo>=ngayBD && ngayMo<=ngayKT){
            cout<<x;
        }
    }
}
// Cập nhật lại lãi suất cho danh sách sổ tiết kiệm
// Đầu vào: Danh sách sổ nums, số thực laisuat
// Đầu ra: Cập nhật lãi suất mới cho tất cả các sổ
void SoTK::capnhatlaiSuat(vector<SoTK>& nums, double laisuat){
    for(auto& x:nums){
        double thang=(x.type=="ngan han")?6:12;
        double tienlai=x.money*(laisuat/100)*(thang/12.0);
        cout<<"Ma so: "<<x.ma<<" - Tien lai: "<<tienlai<<" VND"<<endl;
    }
}
// Tính tiền lãi cho một sổ tiết kiệm
// Đầu vào: Đối tượng sổ tiết kiệm x, lãi suất laisuat, số tháng thang
// Đầu ra: Cập nhật số tiền lãi vào sổ tiết kiệm
void SoTK::tienLai(SoTK& x, double laisuat, int thang){
    double tienlai=x.money*(laisuat/100)*(thang/12.0);
    cout<<"Tien lai cua so tiet kiem "<<x.ma<<": "<<tienlai<<" VND"<<endl;
}
int main(){
    cout<<"Nhap so luong so tiet kiem: "; 
    int n; cin>>n;
    vector<SoTK> nums;
    SoTK plane;
    plane.nhapSoTK(nums, n);
    while(true){
        cout<<"\n===== MENU =====\n";
        cout<<"0. Thoat chuong trinh\n";
        cout<<"1. Nhap ma so tiet kiem can tim\n";
        cout<<"2. Nhap chung minh nhan dan can tim\n";
        cout<<"3. Liet ke so tiet kiem mo trong khoang thoi gian\n";
        cout<<"4. Sap xep so tiet kiem theo ngay mo so tang dan\n";
        cout<<"5. Sap xep so tiet kiem theo so tien giam dan\n";
        cout<<"Lua chon cua ban la: ";
        int chon; cin>>chon;
        if(!chon){
            cout<<"Dang thoat chuong trinh...."<<endl;
            break;
        }
        else if(chon==1){
            cin.ignore();
            string keyword;
            cout<<"Nhap ma so tiet kiem: "; getline(cin, keyword);
            plane.timkiemma(nums, keyword);
        }
        else if(chon==2){
            cin.ignore();
            string keyword;
            cout<<"Nhap chung minh nhan dan: "; getline(cin, keyword);
            plane.timkiemcmnd(nums, keyword);
        }
        else if(chon==3){
            int tuNgay, tuThang, tuNam, denNgay, denThang, denNam;
            cout<<"Nhap ngay bat dau: "; cin>>tuNgay;
            cout<<"Nhap thang bat dau: "; cin>>tuThang;
            cout<<"Nhap nam bat dau: "; cin>>tuNam;
            cout<<"Nhap ngay ket thuc: "; cin>>denNgay;
            cout<<"Nhap thang ket thuc: "; cin>>denThang;
            cout<<"Nhap nam ket thuc: "; cin>>denNam;
            plane.lietKeintime(nums, tuNgay, tuThang, tuNam, denNgay, denThang, denNam);
        }
        else if(chon==4){
            plane.NgaytangDan(nums);
            cout<<"Danh sach so tiet kiem sau khi sap xep theo ngay mo so tang dan:\n";
            plane.xuatSoTK(nums, nums.size());
        }
        else if(chon==5){
            plane.TiengiamDan(nums);
            cout<<"Danh sach so tiet kiem sau khi sap xep theo so tien giam dan:\n";
            plane.xuatSoTK(nums, nums.size());
        }
        else{
            cout<<"Ban nhap sai roi, moi ban nhap lai"<<endl;
        }
    }
    return 0;
}