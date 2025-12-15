#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <limits>
#include <algorithm>

const double EPSILON = 1e-9;

class Equation {
public:
    virtual ~Equation() {}
    virtual void solve() = 0;
    virtual void displayResult() const = 0;
    virtual void displayEquation() const = 0;
    virtual std::string getType() const = 0;
    virtual void loadCoefficients(std::istream& is) = 0;
    virtual bool hasInfiniteSolutions() const { return false; }
    virtual bool hasNoRealSolutions() const = 0;
    virtual std::vector<double> getRealSolutions() const = 0;
};

class LinearEquation : public Equation {
protected:
    double a, b;
    double solution;
    bool infiniteSet;
    bool noSolutions;

public:
    LinearEquation() : a(0.0), b(0.0), solution(std::numeric_limits<double>::quiet_NaN()),
                       infiniteSet(false), noSolutions(false) {}

    void setCoefficients(double _a, double _b) {
        a = _a;
        b = _b;
    }

    void loadCoefficients(std::istream& is) override {
        is >> a >> b;
    }

    void displayEquation() const override {
        std::cout << std::fixed << std::setprecision(2) << a << "x + " << b << " = 0";
    }

    void solve() override {
        infiniteSet = false;
        noSolutions = false;
        solution = std::numeric_limits<double>::quiet_NaN();

        if (std::abs(a) < EPSILON) {
            if (std::abs(b) < EPSILON) {
                infiniteSet = true;
            } else {
                noSolutions = true;
            }
        } else {
            solution = -b / a;
        }
    }

    void displayResult() const override {
        displayEquation();
        std::cout << " -> ";
        if (infiniteSet) {
            std::cout << "Infinite set of solutions (any real number)";
        } else if (noSolutions) {
            std::cout << "No real solutions";
        } else {
            std::cout << "x = " << std::fixed << std::setprecision(4) << solution;
        }
    }

    bool hasInfiniteSolutions() const override {
        return infiniteSet;
    }

    bool hasNoRealSolutions() const override {
        return noSolutions;
    }

    std::string getType() const override {
        return "Linear";
    }

    std::vector<double> getRealSolutions() const override {
        if (!std::isnan(solution)) {
            return {solution};
        }
        return {};
    }
};

class QuadraticEquation : public LinearEquation {
protected:
    double c;
    std::vector<double> solutions;

public:
    QuadraticEquation() : LinearEquation(), c(0.0) {}

    void setCoefficients(double _a, double _b, double _c) {
        a = _a;
        b = _b;
        c = _c;
    }

    void loadCoefficients(std::istream& is) override {
        is >> a >> b >> c;
    }

    void displayEquation() const override {
        std::cout << std::fixed << std::setprecision(2) << a << "x^2 + " << b << "x + " << c << " = 0";
    }

    void solve() override {
        solutions.clear();
        infiniteSet = false;
        noSolutions = false;

        if (std::abs(a) < EPSILON) {
            LinearEquation::a = b;
            LinearEquation::b = c;
            LinearEquation::solve();

            infiniteSet = LinearEquation::infiniteSet;
            noSolutions = LinearEquation::noSolutions;

            if (!std::isnan(LinearEquation::solution)) {
                solutions.push_back(LinearEquation::solution);
            }
            return;
        }

        double D = b * b - 4 * a * c;

        if (D < -EPSILON) {
            noSolutions = true;
        } else if (std::abs(D) < EPSILON) {
            solutions.push_back(-b / (2 * a));
        } else {
            double sqrtD = std::sqrt(D);
            solutions.push_back((-b + sqrtD) / (2 * a));
            solutions.push_back((-b - sqrtD) / (2 * a));
        }
    }

    void displayResult() const override {
        displayEquation();
        std::cout << " -> ";
        if (infiniteSet) {
            std::cout << "Infinite set of solutions";
        } else if (noSolutions) {
            std::cout << "No real solutions";
        } else if (solutions.empty()) {
            std::cout << "No real solutions";
        } else {
            std::cout << "Solutions: ";
            for (size_t i = 0; i < solutions.size(); ++i) {
                std::cout << "x" << i + 1 << " = " << std::fixed << std::setprecision(4) << solutions[i] << (i < solutions.size() - 1 ? "; " : "");
            }
        }
    }

    bool hasNoRealSolutions() const override {
        return noSolutions && !infiniteSet;
    }

    std::string getType() const override {
        return "Quadratic";
    }

    std::vector<double> getRealSolutions() const override {
        return solutions;
    }
};

class BiquadraticEquation : public QuadraticEquation {
private:
    std::vector<double> realSolutions;

public:
    BiquadraticEquation() : QuadraticEquation() {}

    void displayEquation() const override {
        std::cout << std::fixed << std::setprecision(2) << a << "x^4 + " << b << "x^2 + " << c << " = 0";
    }

    void solve() override {
        realSolutions.clear();
        infiniteSet = false;
        noSolutions = false;

        if (std::abs(a) < EPSILON) {
            if (std::abs(b) < EPSILON) {
                if (std::abs(c) < EPSILON) {
                    infiniteSet = true;
                    return;
                } else {
                    noSolutions = true;
                    return;
                }
            }

            double y = -c / b;

            if (y > -EPSILON) {
                if (std::abs(y) < EPSILON) {
                    realSolutions.push_back(0.0);
                } else {
                    realSolutions.push_back(std::sqrt(y));
                    realSolutions.push_back(-std::sqrt(y));
                }
            } else {
                noSolutions = true;
            }
            return;
        }

        double D = b * b - 4 * a * c;
        std::vector<double> y_solutions;

        if (D > EPSILON) {
            y_solutions.push_back((-b + std::sqrt(D)) / (2 * a));
            y_solutions.push_back((-b - std::sqrt(D)) / (2 * a));
        } else if (std::abs(D) < EPSILON) {
            y_solutions.push_back(-b / (2 * a));
        } else {
            noSolutions = true;
            return;
        }

        for (double y : y_solutions) {
            if (y > -EPSILON) {
                if (std::abs(y) < EPSILON) {
                    if (std::find(realSolutions.begin(), realSolutions.end(), 0.0) == realSolutions.end()) {
                        realSolutions.push_back(0.0);
                    }
                } else {
                    realSolutions.push_back(std::sqrt(y));
                    realSolutions.push_back(-std::sqrt(y));
                }
            }
        }

        if (realSolutions.empty() && !noSolutions) {
            noSolutions = true;
        }
    }

    void displayResult() const override {
        displayEquation();
        std::cout << " -> ";
        if (infiniteSet) {
            std::cout << "Infinite set of solutions";
        } else if (noSolutions) {
            std::cout << "No real solutions";
        } else if (realSolutions.empty()) {
             std::cout << "No real solutions";
        } else {
            std::cout << "Solutions: ";
            for (size_t i = 0; i < realSolutions.size(); ++i) {
                std::cout << "x" << i + 1 << " = " << std::fixed << std::setprecision(4) << realSolutions[i] << (i < realSolutions.size() - 1 ? "; " : "");
            }
        }
    }

    bool hasNoRealSolutions() const override {
        return noSolutions && !infiniteSet;
    }

    std::string getType() const override {
        return "Biquadratic";
    }

    std::vector<double> getRealSolutions() const override {
        return realSolutions;
    }
};

Equation* createEquation(const std::string& type) {
    if (type == "L") {
        return new LinearEquation();
    } else if (type == "Q") {
        return new QuadraticEquation();
    } else if (type == "B") {
        return new BiquadraticEquation();
    }
    return nullptr;
}

std::vector<Equation*> readEquationsFromFile(const std::string& fileName) {
    std::vector<Equation*> equations;
    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << fileName << std::endl;
        return equations;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string equationType;
        ss >> equationType;

        Equation* ptr = createEquation(equationType);
        if (ptr) {
            ptr->loadCoefficients(ss);
            equations.push_back(ptr);
        } else {
            std::cerr << "Error: Unknown equation type in line: " << line << std::endl;
        }
    }

    file.close();
    return equations;
}

int main() {
    const std::string FILE_NAME = "equations.txt";
    std::ofstream ofs(FILE_NAME);
    ofs << "L 2.0 4.0\n";
    ofs << "L 0.0 5.0\n";
    ofs << "L 0.0 0.0\n";
    ofs << "Q 1.0 -5.0 6.0\n";
    ofs << "Q 1.0 2.0 3.0\n";
    ofs << "Q 0.0 2.0 4.0\n";
    ofs << "B 1.0 -5.0 4.0\n";
    ofs << "B 1.0 5.0 6.0\n";
    ofs << "B 1.0 0.0 -1.0\n";
    ofs << "B 0.0 1.0 0.0\n";
    ofs.close();

    std::cout << "=====================================================" << std::endl;
    std::cout << "             READING AND SOLVING EQUATIONS" << std::endl;
    std::cout << "=====================================================" << std::endl;

    std::vector<Equation*> equations = readEquationsFromFile(FILE_NAME);

    for (Equation* eq : equations) {
        eq->solve();
        eq->displayResult();
        std::cout << std::endl;
    }

    std::cout << "\n=====================================================" << std::endl;
    std::cout << "                  RESULTS ANALYSIS" << std::endl;
    std::cout << "=====================================================" << std::endl;

    std::cout << "1. Equations with an infinite number of solutions:" << std::endl;
    int infiniteCount = 0;
    for (Equation* eq : equations) {
        if (eq->hasInfiniteSolutions()) {
            std::cout << "    - [" << eq->getType() << "] ";
            eq->displayEquation();
            std::cout << std::endl;
            infiniteCount++;
        }
    }
    if (infiniteCount == 0) {
        std::cout << "    (None found)" << std::endl;
    }

    int noRealSolutionsCount = 0;
    for (Equation* eq : equations) {
        if (eq->hasNoRealSolutions()) {
            noRealSolutionsCount++;
        }
    }
    std::cout << "\n2. Number of equations with no real solutions: " << noRealSolutionsCount << std::endl;

    double minAbsSolution = std::numeric_limits<double>::max();
    bool solutionFound = false;

    for (Equation* eq : equations) {
        if (eq->hasInfiniteSolutions()) continue;

        std::vector<double> equationSolutions = eq->getRealSolutions();
        for (double x : equationSolutions) {
            double abs_x = std::abs(x);
            if (abs_x < minAbsSolution) {
                minAbsSolution = abs_x;
                solutionFound = true;
            }
        }
    }

    std::cout << "\n3. Smallest real solution by absolute value: ";
    if (solutionFound) {
        std::cout << std::fixed << std::setprecision(4) << minAbsSolution << std::endl;
    } else {
        std::cout << "Not found (all equations have an infinite set or no real solutions)." << std::endl;
    }

    double sumOfSquares = 0.0;

    for (Equation* eq : equations) {
        if (eq->hasInfiniteSolutions()) continue;

        std::vector<double> equationSolutions = eq->getRealSolutions();
        for (double x : equationSolutions) {
            sumOfSquares += x * x;
        }
    }

    std::cout << "\n4. Sum of squares of all real solutions: "
              << std::fixed << std::setprecision(4) << sumOfSquares << std::endl;

    std::cout << "=====================================================" << std::endl;

    for (Equation* eq : equations) {
        delete eq;
    }
    equations.clear();

    return 0;
}