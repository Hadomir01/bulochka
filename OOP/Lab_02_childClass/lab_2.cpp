#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

const double pi = 3.1415926;

class Triangle {
    private:
        double x1, y1;
        double x2, y2;
        double x3, y3;
    public:
        Triangle() {
            x1 = 0; y1 = 0;
            x2 = 0; y2 = 0;
            x3 = 0; y3 = 0;
        }

        void input() {
            cout << "Введите координаты точки 1 >> ";
            cin >> x1 >> y1;
            cout << "Введите координаты точки 2 >> ";
            cin >> x2 >> y2;
            cout << "Введите координаты точки 3 >> ";
            cin >> x3 >> y3;
        }

        double getSide(double xa, double ya, double xb, double yb) {
            return sqrt(pow((xb - xa), 2) + pow((yb - ya), 2));
        }

        double getA() {
            return getSide(x1, y1, x2, y2);
        }
        double getB() {
            return getSide(x2, y2, x3, y3);
        }
        double getC() {
            return getSide(x3, y3, x1, y1);
        }

        bool isValid() {
            double a = getA();
            double b = getB();
            double c = getC();

            return (a + b > c) && (a + c > b) && (b + c > a);
        }

        double getPerimeter() {
            if (!isValid()) return 0;

            return getA() + getB() + getC();
        }

        double getArea() {
            if (!isValid()) return 0;
            double a = getA();
            double b = getB();
            double c = getC();
            double p = (a + b + c) / 2;

            return sqrt(p * (p-a) * (p-b) * (p-c));
        }

        bool isSimilar(Triangle t2) {
            if (!this->isValid() || !t2.isValid()) return false;

            double a1 = this->getA();
            double b1 = this->getB();
            double c1 = this->getC();

            double a2 = t2.getA();
            double b2 = t2.getB();
            double c2 = t2.getC();

            if (a1 > b1) swap(a1, b1);
            if (b1 > c1) swap(b1, c1);
            if (a1 > b1) swap(a1, b1);

            if (a2 > b2) swap(a2, b2);
            if (b2 > c2) swap(b2, c2);
            if (a2 > b2) swap(a2, b2);

            double eps = 0.000001;
            double k1 = a1 / a2;
            double k2 = b1 / b2;
            double k3 = c1 / c2;

            return (abs(k1 - k2) < eps) && (abs(k2 - k3) < eps);
        }

        void printInfo() {
            if (!isValid()) {
                cout << "Треугольника с такими координатами не существует" << endl;
                return;
            }

            double a = getA();
            double b = getB();
            double c = getC();

            cout << "--- Сведения о треугольнике ---" << endl;
            cout << "Длины сторон: a = " << a << ", b = " << b << ", c = " << c << endl;
            cout << "Периметр: " << getPerimeter() << endl;
            cout << "Площадь: " << getArea() << endl;

            double angleA = acos((b*b + c*c - a*a) / (2.0 * b * c)) * 180.0 / pi;
            double angleB = acos((a*a + c*c - b*b) / (2.0 * a * c)) * 180.0 / pi;
            double angleC = acos((a*a + b*b - c*c) / (2.0 * a * b)) * 180.0 / pi;

            cout << "Углы (в градусах): " << angleA << ", " << angleB << ", " << angleC << endl;
        }

};

class IsoscelesTriangle : public Triangle {
    public:
        bool isIsosceles() {
            if (!isValid()) return false;
            double a = getA();
            double b = getB();
            double c = getC();
            
            double eps = 0.000001; 
            
            return (abs(a - b) < eps) || (abs(b - c) < eps) || (abs(a - c) < eps);
        }
};

int main() {
    int N, M;
    cout << "Введите кол-во обычных треугольников >> ";
    cin >> N;

    Triangle triangles[32];
    for (int i = 0; i < N; i++ ) {
        cout << "\n Введите данные треугольника " << i+1 << endl;
        triangles[i].input();
        if (!triangles[i].isValid()) {
            cout << "Такого треугольника не может быть" << endl;
            i--;
        } 
    } 

    cout << "Введите кол-во равнобедренных треугольников >> ";
    cin >> M;

    IsoscelesTriangle  isoTriangles[32];
    for (int i = 0; i < M; i++ ) {
        cout << "\n Введите данные треугольника " << i+1 << endl;
        isoTriangles[i].input();
        if (!isoTriangles[i].isValid()) {
            cout << "Такого треугольника не может быть" << endl;
            i--;
        } else if (!isoTriangles[i].isIsosceles()) {
            cout << "Ошибка: этот треугольник не является равнобедренным!" << endl;
            i--;
        }
    } 

    if (N > 1) {
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                if (triangles[i].isSimilar(triangles[j])) {
                    cout << "Треугольник №" << i + 1 << " ПОДОБЕН треугольнику №" << j + 1 << endl;
                } else {
                    cout << "Треугольник №" << i + 1 << " НЕ подобен треугольнику №" << j + 1 << endl;
                }
            }
        }
    }

    if (M > 0) {
        double maxArea = isoTriangles[0].getArea();
        int maxIndex = 0;

        for (int i = 1; i < M; i++) {
            if (isoTriangles[i].getArea() > maxArea) {
                maxArea = isoTriangles[i].getArea();
                maxIndex = i;
            }
        }

        cout << "\nРавнобедренный треугольник с наибольшей площадью — " << maxIndex + 1 
             << " (Площадь: " << maxArea << ")" << endl;
        cout << "Его подробные характеристики:" << endl;
        isoTriangles[maxIndex].printInfo();
    } else {
        cout << "\nРавнобедренные треугольники не были введены." << endl;
    }

    return 0;
}