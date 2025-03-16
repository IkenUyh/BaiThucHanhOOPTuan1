#include<iostream>
#include<vector>
using namespace std;
class HocSinh{
    private:
        string name;
        double toan, van, eng, dtb;
    public:
        // Nhập thông tin một học sinh từ bàn phím
        friend istream& operator>>(istream& in, HocSinh &a);
        // Xuất thông tin một học sinh 
        friend ostream& operator<<(ostream& out, HocSinh a);
        // So sánh học sinh theo điểm trung bình
        friend bool operator>(const HocSinh& x,const HocSinh& y);
        // So sánh học sinh theo điểm toán
        friend bool operator<(const HocSinh& x,const HocSinh& y);
        // Hàm nhập điểm cho một môn học
        friend double nhapDiem(const string& mon);
        // Kiểm tra tên học sinh có hợp lệ không
        bool checkname(const string& name);
        // Nhập danh sách học sinh
        void NhapHS(vector<HocSinh> &nums, int n);
        // Xuất danh sách học sinh
        void XuatHS(const vector<HocSinh>& nums, int n);
        // Phân loại học sinh theo điểm trung bình
        void phanLoai();
        // Tìm học sinh có điểm trung bình cao nhất
        void no1(const vector<HocSinh>& nums, int n);
        // Tìm học sinh theo tên hoặc từ khóa
        void find(const vector<HocSinh>& nums, const string &ten);
        // Tìm học sinh có điểm toán thấp nhất
        void ngutoan(const vector<HocSinh>& nums, int n);
};
// Hàm nhập điểm cho một môn học
// Đầu vào: Tên môn học (chuỗi)
// Đầu ra: Điểm số hợp lệ (double) trong khoảng từ 0 đến 10
double nhapDiem(const string& mon){
    double diem;
    cout<<"Nhap diem mon "<<mon<<" (0-10): "; cin>>diem;
    while(diem<0||diem>10){
        cout<<"Diem khong hop le! vui long nhap lai: "; cin>>diem;
    }
    return diem;
}
// Kiểm tra tên hợp lệ (không chứa số)
// Đầu vào: Tên học sinh (chuỗi)
// Đầu ra: true nếu hợp lệ, false nếu không hợp lệ
bool HocSinh::checkname(const string& name){
    for(int i=0; i<name.size(); i++){
        if(name[i]>='0'&&name[i]<='9') return false;
    }
    return !name.empty();
}
// Nhập thông tin học sinh từ bàn phím
// Đầu vào: Đối tượng HocSinh (tham chiếu)
// Đầu ra: Cập nhật thông tin học sinh
istream& operator>>(istream& in, HocSinh &a){
    cin.ignore();
    cout<<"Nhap ten hoc sinh: ";
    getline(cin, a.name);
    while(!a.checkname(a.name)){
        cout<<"Ho va ten khong hop le! vui long nhap lai: ";
        getline(cin, a.name);
    }
    a.toan=nhapDiem("Toan");
    a.van=nhapDiem("Van");
    a.eng=nhapDiem("Anh");
    a.dtb=(2*a.toan+a.van+a.eng)/4;
    return in;
}
// Phân loại học sinh theo điểm trung bình
// Đầu vào: Không có
// Đầu ra: Xuất loại học sinh dựa trên điểm trung bình
void HocSinh::phanLoai(){
    if(dtb>=9) cout<<"Diem trung binh: "<<dtb<<" - Loai: Xuat Sac"<<endl;
    else if(dtb>=8) cout<<"Diem trung binh: "<<dtb<<" - Loai: Gioi"<<endl;
    else if(dtb>=6.5) cout<<"Diem trung binh: "<<dtb<<" - Loai: Kha"<<endl;
    else if(dtb>=5) cout<<"Diem trung binh: "<<dtb<<" - Loai: Trung Binh"<<endl;
    else cout<<"Diem trung binh: "<<dtb<<" - Loai: Yeu"<<endl;
}
// Xuất thông tin học sinh ra màn hình
// Đầu vào: Đối tượng HocSinh
// Đầu ra: In thông tin học sinh
ostream& operator<<(ostream& out, HocSinh a){
    out<<"Ho va ten: "<<a.name<<endl;
    out<<"Diem Toan: "<<a.toan<<endl;
    out<<"Diem Van: "<<a.van<<endl;
    out<<"Diem Anh: "<<a.eng<<endl;
    a.phanLoai();
    out<<"===================================\n";
    return out;
}
// Nhập danh sách học sinh
// Đầu vào: Danh sách học sinh (vector) và số lượng học sinh (n)
// Đầu ra: Danh sách được cập nhật với n học sinh
void HocSinh::NhapHS(vector<HocSinh> &nums, int n){
    for(int i=0; i<n; i++){
        cout<<"Nhap hoc sinh thu "<<i+1<<": "<<endl;
        HocSinh x; cin>>x;
        nums.push_back(x);
    }
}
// Xuất danh sách học sinh
// Đầu vào: Danh sách học sinh (vector) và số lượng học sinh (n)
// Đầu ra: In danh sách học sinh
void HocSinh::XuatHS(const vector<HocSinh>& nums, int n){
    cout<<"\n===== DANH SACH HOC SINH =====\n";
    for(int i=0; i<n; i++){
        cout<<"Thong tin hoc sinh thu "<<i+1<<": "<<endl;
        cout<<nums[i];
    }
}
// So sánh học sinh theo điểm trung bình
// Đầu vào: Hai đối tượng HocSinh
// Đầu ra: True nếu học sinh thứ nhất có điểm trung bình cao hơn
bool operator>(const HocSinh& x,const HocSinh& y){
    return x.dtb>y.dtb;
}
// So sánh học sinh theo điểm toán
// Đầu vào: Hai đối tượng HocSinh
// Đầu ra: True nếu học sinh thứ nhất có điểm toán thấp hơn
bool operator<(const HocSinh& x,const HocSinh& y){
    return x.toan<y.toan;
}
// Tìm học sinh có điểm trung bình cao nhất
// Đầu vào: Danh sách học sinh (vector) và số lượng học sinh (n)
// Đầu ra: Xuất học sinh có điểm trung bình cao nhất
void HocSinh::no1(const vector<HocSinh>& nums, int n){
    if(nums.empty()) return;
    HocSinh tmp=nums[0];
    for(int i=0; i<n; i++){
        if(nums[i]>tmp) tmp=nums[i];
    }
    cout<<"\n===== HOC SINH CO DTB CAO NHAT =====\n"<<tmp;
}
// Tìm học sinh có điểm toán thấp nhất
// Đầu vào: Danh sách học sinh (vector) và số lượng học sinh (n)
// Đầu ra: Xuất danh sách học sinh có điểm toán thấp nhất
void HocSinh::ngutoan(const vector<HocSinh>& nums, int n){
    if(nums.empty()) return;
    HocSinh tmp=nums[0];
    for(int i=0; i<n; i++){
        if(nums[i]<tmp) tmp=nums[i];
    }
    cout<<"\n===== HOC SINH CO DIEM TOAN THAP NHAT =====\n";
    for(const auto& x:nums){
        if(x.toan==tmp.toan) cout<<x.name<<" - Diem Toan: "<<x.toan<<endl;
    }
    cout<<"===================================\n";
}
// Chuyển đổi chuỗi sang chữ thường
// Đầu vào: Chuỗi ký tự
// Đầu ra: Chuỗi đã chuyển sang chữ thường
string tolowerCase(string str){
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}
// Tìm học sinh theo tên hoặc từ khóa
// Đầu vào: Danh sách học sinh (vector) và từ khóa (chuỗi)
// Đầu ra: Danh sách học sinh có tên chứa từ khóa
void HocSinh::find(const vector<HocSinh>& nums, const string& keyword){
    cout<<"\n===== KET QUA TIM KIEM =====\n";
    bool found=false;
    string tukhoa=tolowerCase(keyword);
    for(const auto& x:nums){
        string name=tolowerCase(x.name);
        if(name.find(tukhoa)!=string::npos){
            cout<<x; found=true;
        }
    }
    if(!found) cout<<"Khong tim thay hoc sinh chua "<<keyword<<endl<<"===================================\n";
}
int main(){
    cout<<"Nhap so luong hoc sinh: ";
    int n; cin>>n;
    vector<HocSinh> nums;
    HocSinh hs;
    hs.NhapHS(nums, n);
    hs.XuatHS(nums, n);
    hs.no1(nums, n);
    hs.ngutoan(nums, n);
    while(true){
        cout<<"\n===== MENU =====\n";
        cout<<"0. Thoat chuong trinh\n";
        cout<<"1. Nhap ten hoc sinh can tim\n";
        cout<<"Lua chon cua ban la: ";
        int chon; cin>>chon;
        if(!chon){
            cout<<"Dang thoat chuong trinh...."<<endl;
            break;
        }
        else if(chon==1){
            cin.ignore();
            string keyword;
            cout<<"Nhap ten cua hoc sinh can tim: ";
            getline(cin, keyword);
            hs.find(nums, keyword);
        }
        else{
            cout<<"Ban nhap sai roi, moi ban nhap lai"<<endl;
        }
    }
    return 0;
}
