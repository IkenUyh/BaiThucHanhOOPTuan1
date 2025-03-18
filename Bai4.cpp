#include<iostream>
#include<cmath>
#include<iomanip>
#include<string>
#include<sstream>
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
    this->x=fmod(x,2*M_PI); // Giới hạn giá trị x trong khoảng [0,2π] để tối ưu tính toán
    this->precision=precision; // Gán độ chính xác
}
/*
Hàm tính gần đúng sin(x) bằng khai triển Taylor 
Đầu vào: Không có tham số đầu vào, sử dụng giá trị x đã khởi tạo trong đối tượng     
Đầu ra: Trả về giá trị gần đúng của sin(x) dưới dạng số thực (double)
*/
double sincalculate::calculate(){
    double res=0, term=x; // Tổng của chuỗi và số hạng đầu tiên
    int i=0;    
    while(fabs(term)>=precision&&i<100){ // Điều kiện sửa: AND thay vì OR, giới hạn số vòng lặp
        res+=term;
        i++;
        term*=-x*x/((2*i)*(2*i+1)); // Tính số hạng tiếp theo dựa trên công thức Taylor
    }  
    return res;
}
/*
Hàm chuyển đổi chuỗi nhập vào thành giá trị radian
Đầu vào: string input - giá trị góc có thể ở dạng số thực hoặc bội số của pi
Đầu ra: double - giá trị góc đã chuyển thành radian
*/
double convertToRadian(string input){
    // Chuyển về chữ thường để dễ xử lý
    for(char &c:input)c=tolower(c);   
    if(input.find("pi")!=string::npos){ // Nếu có "pi"
        double coefficient=1.0, divisor=1.0;
        size_t piPos=input.find("pi");  
        // Xử lý hệ số trước pi
        if(piPos>0){
            string coeffStr=input.substr(0,piPos);
            if(!coeffStr.empty()&&coeffStr!="-")coefficient=stod(coeffStr);
            else if(coeffStr=="-")coefficient=-1.0;
        } 
        // Xử lý phân số sau pi (nếu có)
        size_t divPos=input.find("/",piPos);
        if(divPos!=string::npos&&divPos+1<input.length())divisor=stod(input.substr(divPos+1));
        return coefficient*M_PI/divisor;
    } 
    // Nếu không có "pi", chuyển thành số thực bình thường
    return stod(input);
}
int main(){
    string input;
    cout<<"Nhap gia tri x (co the nhap dang so hoac dang pi, vi du: pi/6, 0.5, 2pi): ";
    getline(cin,input); // Sử dụng getline để đọc cả dòng, bao gồm dấu cách
    try{
        double x=convertToRadian(input); // Chuyển đổi về radian
        sincalculate tmp(x); // Khởi tạo đối tượng
        double result=tmp.calculate(); // Gọi hàm tính sin(x)
        cout<<fixed<<setprecision(5);
        if(fabs(result)<1e-6)result=0; // Sửa lỗi -0.00000
        cout<<"Sin("<<input<<") sap xi bang "<<result<<endl;      
        // So sánh với giá trị thực của hàm sin trong thư viện cmath
        cout<<"Gia tri thu vien sin("<<input<<") = "<<sin(x)<<endl;
        cout<<"Sai so: "<<fabs(result-sin(x))<<endl;
    }
    catch(const exception &e){
        cout<<"Loi: Khong the xu ly dau vao. Vui long nhap dung dinh dang."<<endl;
    }
    return 0;
}
