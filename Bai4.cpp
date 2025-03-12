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
int main(){
    double x;
    cout<<"Nhap gia tri x (don vi radian): "; cin>>x;
    sincalculate tmp(x); // Khởi tạo đối tượng sincalculate với giá trị x nhập từ bàn phím
    double result=tmp.calculate(); // Gọi hàm tính sin(x)
    cout<<"Sin("<<x<<") sap xi bang "<<result<<endl;
    return 0;
}