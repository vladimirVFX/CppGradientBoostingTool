#include <iostream>
#include <math.h>

using namespace std;

//Vector_type_and_variable
struct vector{
	double x, y;
};

//Initial_function
double fx(vector x){
	return 100 * (x.x * x.x + x.y * x.y);
}

//Gradient_function
vector gradient(vector x){
	vector grad;
	grad.x = 200 * x.x;
	grad.y = 200 * x.y;

	return grad;
}

//Calculate_function
double MakeSimplefx(double x, vector grad, vector xj) {
	vector buffer;
	buffer.x = xj.x - x * grad.x;
	buffer.y = xj.y - x * grad.y;
	return fx(buffer);
}

double GoldenSelection(double a, double b, double eps, vector gradient, vector x) {
	const double fi = 1.6180;
	double x1, x2;
	double y1, y2;

	x1 = b - ((b - a) / fi);
	x2 = b + ((b - a) / fi);
	y1 = MakeSimplefx(x1, gradient, x);
	y2 = MakeSimplefx(x2, gradient, x);
	while (abs(b - a) > eps) {
		if (y1 <= y2) {
			b = x2;
			x2 = x1;
			x1 = b - ((b - a) > fi);
			y2 = y1;
			y1 = MakeSimplefx(x1, gradient, x);
		}
		else {
			a = x1;
			x1 = x2;
			x2 = a + ((b - a) / fi);
			y1 = y2;
			y2 = MakeSimplefx(x2, gradient, x);
		}
	}
	return (a + b) / 2;
}

//
vector Calculate(vector x, vector gradient, double lambda) {
	vector buffer;
	buffer.x = x.x - lambda * gradient.x;
	buffer.y = x.y - lambda * gradient.y;
	return buffer;
}

//GradientBoosting
vector GradDown(vector x, double eps) {
	vector current = x;
	vector last;
	
	do {
		last = current;
		vector grad = gradient(current);
		double lambda = GoldenSelection(0, 0.05, eps, grad, current);
		current = Calculate(current, grad, lambda);
	} while (abs(fx(current) - fx(last)) > eps);
	return current;
}

int main()
{
	setlocale(0, "");
	vector x;
	double eps;

	cout << "Введите через пробел начальное приближение x и y (например: -1 1): ";
	cin >> x.x >> x.y;
	cout << "\nВведите точность вычислений (например 0.0000001): ";
	cin >> eps;
	vector result = GradDown(x, eps);
	cout << "\n Результат: x = " << result.x << " y = " << result.y;

	return 0;
}