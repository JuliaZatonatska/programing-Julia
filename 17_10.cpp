#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>

class VectorException : public std::runtime_error {
public:
    VectorException(const std::string& message)
        : std::runtime_error("Vector Error: " + message) {}
};

class Vector {
private:
    double* data;
    size_t size;

    void cleanup() {
        if (data != nullptr) {
            delete[] data;
            data = nullptr;
        }
    }

    void allocate(size_t n) {
        if (n == 0) {
            data = nullptr;
            size = 0;
            return;
        }
        try {
            data = new double[n];
            size = n;
        } catch (const std::bad_alloc& e) {
            throw VectorException("Failed to allocate memory for the vector (std::bad_alloc).");
        }
    }

public:
    Vector();

    explicit Vector(size_t n);

    Vector(size_t n, double defaultValue);

    Vector(const Vector& other);

    Vector& operator=(const Vector& other);

    ~Vector();

    size_t getSize() const { return size; }

    double& at(size_t index);
    const double& at(size_t index) const;

    double& operator[](size_t index) { return at(index); }
    const double& operator[](size_t index) const { return at(index); }

    void fillRandom(double min_val = 0.0, double max_val = 10.0);

    void readFromFile(const std::string& filename);
    void writeToFile(const std::string& filename) const;

    Vector operator+(const Vector& other) const;

    double scalarProduct(const Vector& other) const;
    double operator*(const Vector& other) const { return scalarProduct(other); }

    friend std::ostream& operator<<(std::ostream& os, const Vector& vec);
    friend std::istream& operator>>(std::istream& is, Vector& vec);
};

namespace {
    struct RandomInitializer {
        RandomInitializer() {
            std::srand(std::time(0));
        }
    } init;
}

Vector::Vector() : data(nullptr), size(0) {}

Vector::Vector(size_t n) : data(nullptr), size(0) {
    allocate(n);
}

Vector::Vector(size_t n, double defaultValue) : data(nullptr), size(0) {
    allocate(n);
    for (size_t i = 0; i < size; ++i) {
        data[i] = defaultValue;
    }
}

Vector::Vector(const Vector& other) : data(nullptr), size(0) {
    allocate(other.size);
    for (size_t i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}

Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        cleanup();
        allocate(other.size);
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

Vector::~Vector() {
    cleanup();
}

double& Vector::at(size_t index) {
    if (index >= size) {
        throw VectorException("Index out of bounds: " + std::to_string(index) +
                              " (size: " + std::to_string(size) + ")");
    }
    return data[index];
}

const double& Vector::at(size_t index) const {
    if (index >= size) {
        throw VectorException("Index out of bounds (const access): " + std::to_string(index) +
                              " (size: " + std::to_string(size) + ")");
    }
    return data[index];
}

void Vector::fillRandom(double min_val, double max_val) {
    for (size_t i = 0; i < size; ++i) {
        data[i] = min_val + (static_cast<double>(std::rand()) / RAND_MAX) * (max_val - min_val);
    }
}

Vector Vector::operator+(const Vector& other) const {
    if (size != other.size) {
        throw VectorException("Vector addition error: sizes do not match (" +
                              std::to_string(size) + " != " + std::to_string(other.size) + ")");
    }

    Vector result(size);
    for (size_t i = 0; i < size; ++i) {
        result.data[i] = this->data[i] + other.data[i];
    }
    return result;
}

double Vector::scalarProduct(const Vector& other) const {
    if (size != other.size) {
        throw VectorException("Scalar product error: sizes do not match (" +
                              std::to_string(size) + " != " + std::to_string(other.size) + ")");
    }

    double product = 0.0;
    for (size_t i = 0; i < size; ++i) {
        product += this->data[i] * other.data[i];
    }
    return product;
}

void Vector::writeToFile(const std::string& filename) const {
    std::ofstream ofs(filename);
    if (!ofs.is_open()) {
        throw VectorException("File error: could not open file for writing: " + filename);
    }

    ofs << size << std::endl;
    for (size_t i = 0; i < size; ++i) {
        ofs << data[i] << " ";
    }
    ofs.close();
}

void Vector::readFromFile(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        throw VectorException("File error: could not open file for reading: " + filename);
    }

    size_t new_size;
    if (!(ifs >> new_size)) {
        throw VectorException("File read error: could not read vector size from file: " + filename);
    }

    cleanup();
    allocate(new_size);

    for (size_t i = 0; i < size; ++i) {
        if (!(ifs >> data[i])) {
            cleanup();
            throw VectorException("File read error: could not read element " + std::to_string(i) + " from file: " + filename);
        }
    }

    if (ifs.fail() && !ifs.eof()) {
        cleanup();
        throw VectorException("File read error: unexpected reading issue near the end of file: " + filename);
    }
    ifs.close();
}

std::ostream& operator<<(std::ostream& os, const Vector& vec) {
    os << "Vector(" << vec.size << "): [";
    for (size_t i = 0; i < vec.size; ++i) {
        os << vec.data[i];
        if (i < vec.size - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

std::istream& operator>>(std::istream& is, Vector& vec) {
    std::cout << "Enter " << vec.size << " double values for the vector:\n";

    for (size_t i = 0; i < vec.size; ++i) {
        std::cout << "Element [" << i << "]: ";
        if (!(is >> vec.data[i])) {
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw VectorException("Input Error: Invalid data type entered for element " + std::to_string(i));
        }
    }
    return is;
}


void demonstrateFileIO(Vector& v, const std::string& filename) {
    std::cout << "\n--- File I/O Demonstration ---\n";
    try {
        std::cout << "Writing vector V1 to '" << filename << "'...\n";
        v.writeToFile(filename);
        std::cout << "Successfully written.\n";

        Vector v_from_file;
        std::cout << "Reading vector from '" << filename << "'...\n";
        v_from_file.readFromFile(filename);
        std::cout << "Read vector: " << v_from_file << std::endl;

    } catch (const VectorException& e) {
        std::cerr << "Caught Vector Exception in File I/O: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Caught Standard Exception in File I/O: " << e.what() << std::endl;
    }
}

void demonstrateArithmetic(const Vector& v1, const Vector& v2) {
    std::cout << "\n--- Arithmetic Demonstration (V1=" << v1.getSize() << ", V2=" << v2.getSize() << ") ---\n";
    try {
        Vector v_sum = v1 + v2;
        std::cout << "V1 + V2 = " << v_sum << std::endl;

        double scalar_prod = v1 * v2;
        std::cout << "V1 * V2 (Scalar Product) = " << scalar_prod << std::endl;

    } catch (const VectorException& e) {
        std::cerr << "Caught Vector Exception in Arithmetic: " << e.what() << std::endl;
    }
}

void demonstrateErrorHandling() {
    std::cout << "\n--- Error Handling Tests ---\n";

    Vector v1(3);
    v1.fillRandom(10.0, 20.0);
    std::cout << "Test Vector V1: " << v1 << std::endl;

    try {
        std::cout << "Attempting to access index 3...\n";
        double val = v1.at(3);
    } catch (const VectorException& e) {
        std::cerr << "Successfully caught Index Exception: " << e.what() << std::endl;
    }

    Vector v_diff(4);
    v_diff.fillRandom();
    try {
        std::cout << "Attempting V1(" << v1.getSize() << ") + V_diff(" << v_diff.getSize() << ")...\n";
        Vector v_sum_fail = v1 + v_diff;
    } catch (const VectorException& e) {
        std::cerr << "Successfully caught Arithmetic Exception (size mismatch): " << e.what() << std::endl;
    }
   
    try {
        Vector v_nonexistent(1);
        v_nonexistent.readFromFile("nonexistent_file_xyz.txt");
    } catch (const VectorException& e) {
        std::cerr << "Successfully caught File Exception (read): " << e.what() << std::endl;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.precision(4);

    try {
        std::cout << "--- Vector Class Initialization ---\n";
       
        Vector v1(3);
        Vector v2(3, 5.0);
       
        v1.fillRandom(1.0, 5.0);
       
        std::cout << "V1: " << v1 << std::endl;
        std::cout << "V2: " << v2 << std::endl;
       
        try {
            Vector v3(2);
            std::cin >> v3;
            std::cout << "V3 from input: " << v3 << std::endl;
        } catch (const VectorException& e) {
            std::cerr << "Caught Input Exception: " << e.what() << "\n\n";
        }
       
        demonstrateArithmetic(v1, v2);
        demonstrateFileIO(v1, "vector_data.txt");
        demonstrateErrorHandling();

    } catch (const VectorException& e) {
        std::cerr << "Caught Critical Vector Exception in main: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Caught Critical Standard Exception in main: " << e.what() << std::endl;
        return 1;
    }
   
    return 0;
}