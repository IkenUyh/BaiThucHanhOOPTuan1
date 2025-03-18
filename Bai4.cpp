#include<iostream>
#include<cmath>
using namespace std;
/*
Lớp sincalculate để tính giá trị gần đúng của sin(x)
Gồm các thuộc tính: giá trị góc x và độ chính xác precision
 */
class sincalculate{
    private:
        double x, precision;
    public:
        sincalculate(double, double);
        double calculate();
};
/*
Hàm khởi tạo của lớp sincalculate
Đầu vào:
- double x: giá trị góc cần tính (đơn vị radian)
- double precision: độ chính xác mong muốn (mặc định là 0.00001) 
Đầu ra: Không có giá trị trả về, nhưng sẽ khởi tạo đối tượng với giá trị x và precision
*/
sincalculate::sincalculate(double x, double precision=0.00001){
    this->x=fmod(x, 2*M_PI); // Giới hạn giá trị x trong khoảng [0, 2π] để tối ưu tính toán
    this->precision=precision; // Gán độ chính xác
}
/*
Hàm tính gần đúng sin(x) bằng khai triển Taylor 
Đầu vào: Không có tham số đầu vào, sử dụng giá trị x đã khởi tạo trong đối tượng     
Đầu ra: Trả về giá trị gần đúng của sin(x) dưới dạng số thực (double)
*/
double sincalculate::calculate(){
    double res=0, ans=x;
    for(int i=1; fabs(ans)>=precision; i++){ // Lặp đến khi số hạng nhỏ hơn độ chính xác
        res+=ans;
        ans*=-x*x/((2*i)*(2*i+1)); // Tính số hạng tiếp theo dựa trên công thức Taylor
    }
    return res;
}
/*
Hàm chuyển đổi chuỗi nhập vào thành giá trị radian
Đầu vào: string input - giá trị góc có thể ở dạng số thực hoặc bội số của pi
Đầu ra: double - giá trị góc đã chuyển thành radian
*/
double convertToRadian(string input) {
    // Nếu chứa "pi" thì xử lý dạng bội số của π
    size_t pos=input.find("pi");
    if(pos!=string::npos) {
        double coefficient=1.0; // Hệ số nhân với π
        if(pos>0) { // Nếu có số trước "pi"
            coefficient=stod(input.substr(0, pos));
        }
        return coefficient*M_PI; // Trả về giá trị nhân với π
    } 
    return stod(input); // Nếu không có "pi", chuyển thành số thực bình thường
}
int main(){
    string input;
    cout<<"Nhap gia tri x (co the nhap dang so hoac dang pi, vi du: pi/6, 0.5, 2pi): ";
    cin>>input;
    double x=convertToRadian(input); // Chuyển đổi về radian
    sincalculate tmp(x); // Khởi tạo đối tượng
    double result=tmp.calculate(); // Gọi hàm tính sin(x)
    cout<<"Sin("<<input<<") sap xi bang "<<result<<endl;
    return 0;
}
