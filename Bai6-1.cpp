#include<iostream>
#include<vector>
using namespace std;
// Hàm nhập mảng từ bàn phím
// Đầu vào: vector a (mảng cần nhập), số lượng phần tử n, tên mảng name
// Đầu ra: Mảng a được gán giá trị từ người dùng
void nhapMang(vector<int> &a, int n, const string& name){
    cout<<"Nhap phan tu cua mang "<<name<<": ";
    for(int i=0; i<n; i++) cin>>a[i];
}
// Hàm so sánh hai mảng có bằng nhau không
// Đầu vào: Hai vector a và b
// Đầu ra: Trả về true nếu hai mảng giống nhau, false nếu khác nhau
bool sosanhMang(const vector<int> &a, const vector<int> &b){
    return a==b;
}
// Hàm tìm vị trí xuất hiện của mảng con trong mảng lớn
// Đầu vào: check (mảng cần tìm), nums (mảng lớn), pos (vector lưu vị trí xuất hiện)
// Đầu ra: Số lần xuất hiện của check trong nums, và các vị trí xuất hiện trong pos
long long timvitrixuathien(const vector<int>& check, const vector<int>& nums, vector<int>& pos){
    int k=check.size(), n=nums.size();
    long long ans=0;
    vector<int> sdw(nums.begin(), nums.begin()+k); // Lấy đoạn đầu tiên trong nums có độ dài bằng check
    if(check==sdw){ // Kiểm tra nếu đoạn đầu tiên trùng với check
        ans++;
        pos.push_back(0);
    }
    for(int i=k; i<n; i++){ // Duyệt tiếp từ vị trí k đến hết mảng nums
        sdw.push_back(nums[i]); // Thêm phần tử mới vào cửa sổ trượt
        sdw.erase(sdw.begin()); // Xóa phần tử đầu tiên để giữ nguyên độ dài
        if(check==sdw){ // Kiểm tra nếu cửa sổ trùng với check
            ans++;
            pos.push_back(i-k+1);
        }
    }
    return ans;
}
int main(){
    int k, n; 
    cout<<"Nhap so luong cua mang A: "; cin>>k;
    cout<<"Nhap so luong cua mang B: "; cin>>n;
    vector<int> check(k), nums(n);
    if(!k||!n||k>n){ // Kiểm tra nếu mảng A rỗng hoặc lớn hơn B thì không thể tìm được
        cout<<"So la xuat hien: 0"<<endl; return 0;
    }
    nhapMang(check, k, "A"); // Nhập dữ liệu cho mảng A
    nhapMang(nums, n, "B"); // Nhập dữ liệu cho mảng B
    vector<int> pos;
    long long ans=timvitrixuathien(check, nums, pos); // Tìm kiếm vị trí xuất hiện
    cout<<"So lan xuat hien: "<<ans<<endl;
    cout<<"Cac vi tri bat dau: ";
    for(auto x:pos) cout<<x<<" ";
    cout<<endl;
    return 0;
}