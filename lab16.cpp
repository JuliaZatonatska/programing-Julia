#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

const float PI = 3.14159f;

class Figure {
protected:
    float x_coord;
    float y_coord;
    string name;
    float area;
    float perimeter;

public:
    Figure(float x = 0.0f, float y = 0.0f, const string& n = "Figure")
        : x_coord(x), y_coord(y), name(n), area(0.0f), perimeter(0.0f) {}

    virtual void calculateArea() = 0;
    virtual void calculatePerimeter() = 0;

    void move(float dx, float dy);
    void rotate(float angle_deg);

    void displayName() const;
    void displayArea() const;
    void displayPerimeter() const;
    float getArea() const { return area; }
    float getPerimeter() const { return perimeter; }

    virtual ~Figure() {}
};

void Figure::move(float dx, float dy) {
    x_coord += dx;
    y_coord += dy;
    cout << "  * " << name << " moved by (" << dx << ", " << dy << "). New coordinates: ("
         << x_coord << ", " << y_coord << ")" << endl;
}

void Figure::rotate(float angle_deg) {
    cout << "  * " << name << " rotated " << angle_deg << " degrees around the reference point." << endl;
}

void Figure::displayName() const {
    cout << "--- " << name << " ---" << endl;
    cout << "  Reference point coordinates: (" << x_coord << ", " << y_coord << ")" << endl;
}

void Figure::displayArea() const {
    cout << "  Area (S): " << area << endl;
}

void Figure::displayPerimeter() const {
    cout << "  Perimeter (P): " << perimeter << endl;
}

class Trapezoid : public Figure {
private:
    float base_a;
    float base_b;
    float height;

public:
    Trapezoid(float x, float y, float a, float b, float h)
        : Figure(x, y, "Trapezoid"), base_a(a), base_b(b), height(h) {}

    void calculateArea() override;
    void calculatePerimeter() override;
    void displayDimensions() const;
};

void Trapezoid::calculateArea() {
    if (base_a > 0 && base_b > 0 && height > 0) {
        area = (base_a + base_b) / 2.0f * height;
    } else {
        area = 0.0f;
    }
}

void Trapezoid::calculatePerimeter() {
    float delta_base = abs(base_b - base_a);
    float leg_projection = delta_base / 2.0f;
    float leg_c = sqrt(height * height + leg_projection * leg_projection);
    perimeter = base_a + base_b + 2.0f * leg_c;
}

void Trapezoid::displayDimensions() const {
    cout << "  Dimensions: a=" << base_a << ", b=" << base_b << ", h=" << height << endl;
}

class Parallelogram : public Figure {
private:
    float base;
    float side_b;
    float height;

public:
    Parallelogram(float x, float y, float b, float s, float h)
        : Figure(x, y, "Parallelogram"), base(b), side_b(s), height(h) {}

    void calculateArea() override;
    void calculatePerimeter() override;
    void displayDimensions() const;
};

void Parallelogram::calculateArea() {
    if (base > 0 && height > 0) {
        area = base * height;
    } else {
        area = 0.0f;
    }
}

void Parallelogram::calculatePerimeter() {
    if (base > 0 && side_b > 0) {
        perimeter = 2.0f * (base + side_b);
    } else {
        perimeter = 0.0f;
    }
}

void Parallelogram::displayDimensions() const {
    cout << "  Dimensions: Base=" << base << ", Side=" << side_b << ", h=" << height << endl;
}

class Circle : public Figure {
private:
    float radius;
    float circumference;

public:
    Circle(float x, float y, float r)
        : Figure(x, y, "Circle"), radius(r), circumference(0.0f) {}

    void calculateArea() override;
    void calculatePerimeter() override;
    void displayCircumference() const;
    void displayDimensions() const;
};

void Circle::calculateArea() {
    if (radius > 0) {
        area = PI * radius * radius;
    } else {
        area = 0.0f;
    }
}

void Circle::calculatePerimeter() {
    if (radius > 0) {
        perimeter = 2.0f * PI * radius;
    } else {
        perimeter = 0.0f;
    }
    circumference = perimeter;
}

void Circle::displayCircumference() const {
    cout << "  Circumference: " << circumference << endl;
}

void Circle::displayDimensions() const {
    cout << "  Radius r: " << radius << endl;
}

void processFigures(vector<Figure*>& figures) {
    if (figures.empty()) {
        cout << "\nThe figure list is empty." << endl;
        return;
    }

    cout << "\n*** Processing and Calculating Figures ***" << endl;
    float total_area = 0.0f;
    float total_perimeter = 0.0f;
    Figure* figure_with_max_area = nullptr;
    float max_area = -1.0f;

    for (Figure* fig : figures) {
        fig->calculateArea();
        fig->calculatePerimeter();
        total_area += fig->getArea();
        total_perimeter += fig->getPerimeter();
        if (fig->getArea() > max_area) {
            max_area = fig->getArea();
            figure_with_max_area = fig;
        }
        fig->displayName();
        fig->displayArea();
        fig->displayPerimeter();

        if (Circle* c = dynamic_cast<Circle*>(fig)) {
            c->displayCircumference();
        } else if (Trapezoid* t = dynamic_cast<Trapezoid*>(fig)) {
            t->displayDimensions();
        } else if (Parallelogram* p = dynamic_cast<Parallelogram*>(fig)) {
            p->displayDimensions();
        }

        cout << "---" << endl;
    }

    cout << "\n*** Summary ***" << endl;
    cout << "Total area of all figures: " << total_area << endl;
    cout << "Total perimeter of all figures: " << total_perimeter << endl;

    if (figure_with_max_area) {
        cout << "\n*** Figure with the Largest Area (" << max_area << ") ***" << endl;
        figure_with_max_area->displayName();
    }
}

void performActions(vector<Figure*>& figures) {
    cout << "\n*** Demonstration of Moving and Rotating ***" << endl;
    for (size_t i = 0; i < figures.size(); ++i) {
        Figure* fig = figures[i];
        cout << "Actions with figure " << i + 1 << ":" << endl;
        fig->move(1.0f + i, 2.0f + i);
        fig->rotate(45.0f);
    }
}

void createFigures(vector<Figure*>& figures, int figure_count) {
    srand(time(0));
    cout << "\n*** Creating Figures ***" << endl;

    for (int i = 0; i < figure_count; ++i) {
        int type = rand() % 3;
        float start_x = (float)i * 15.0f;
        float start_y = (float)i * 15.0f;

        switch (type) {
            case 0:
                figures.push_back(new Trapezoid(start_x, start_y, 4.0f + i, 6.0f + i, 3.0f));
                cout << "Created Trapezoid." << endl;
                break;
            case 1:
                figures.push_back(new Parallelogram(start_x, start_y, 5.0f + i, 4.0f + i, 3.0f));
                cout << "Created Parallelogram." << endl;
                break;
            case 2:
                figures.push_back(new Circle(start_x, start_y, 2.0f + i / 2.0f));
                cout << "Created Circle." << endl;
                break;
        }
    }
}

int main() {
    setlocale(LC_ALL, "en_US.UTF-8");

    int figure_count;
    cout << "Enter the desired number of figures (integer > 0): ";

    if (!(cin >> figure_count) || figure_count <= 0) {
        cout << "Invalid input. Program will terminate." << endl;
        return 1;
    }

    vector<Figure*> figures;
    createFigures(figures, figure_count);
    performActions(figures);
    processFigures(figures);

    for (Figure* fig : figures) {
        delete fig;
    }
    figures.clear();

    cout << "\nProgram finished." << endl;
    return 0;
}
