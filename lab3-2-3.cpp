#include <iostream>
using namespace std;

// Шаблонный класс Вектор
template<class T, size_t _dimension> //Комментарий для того, что-бы IntelleiSense не мозолил мне глаза ошибкой
class Vector { 
private:
	T _data[_dimension]; // Создание статического массива заданной размерности и типа

public:

	// Конструктор, использущий initializer_list
	// Нужен для инициализации вектора как массива с помощью скобок {} 
	Vector(const std::initializer_list<T>& list)
	{
		size_t i = 0;
		for (auto& element : list) {
			_data[i++] = element;
		}
	}
	// Перегрузка оператора присваивания с тем же initializer_list
	// для того присваивать значения через {}
	Vector& operator= (const std::initializer_list<T>& list) {
		size_t i = 0;
		for (auto& element : list) {
			_data[i++] = element;
		}

		return *this;
	}

	// Возвращает размерность
	size_t dimension() const { return _dimension; }

	// Возвращает длину вектора
	// Формула длины вектора = Корень из суммы квадратов координат вектора
	double length() const {
		T sum = 0;
		for (const T& coor : _data) {
			sum += coor * coor;
		}

		return sqrt(sum);
	}

	// Возвращает длину между векторами
	// Формула: корень из суммы квадратов разностей координат векторов
	double distanceBetween(Vector& other) const {
		if (_dimension != other.dimension()) {
			std::cout << "ERROR: the vectors are in different dimensions...\n";
			exit(1);
		}
		// Считаем сумму квадратов разностей
		T sum = 0;
		for (int i = 0; i < _dimension; i++) {
			sum += (other[i] - _data[i]) * (other[i] - _data[i]);
		}

		return sqrt(sum);
	}
	// Метод доступа к элементу массива (возращает копию данных, т.е. их нельзя изменить)
	T  at(int index) const { return _data[index]; }
	// Перегрузка оператора доступа к элементу массива (возвращает по ссылке, данные можно изменить)
	T& operator[](int index) { return _data[index]; }

	// Перегрузка оператора вывода - печатает данные в виде "[a, b, c]"
	friend std::ostream& operator<< (std::ostream& out, const Vector& vec) {
		out << "[";
		for (size_t i = 0; i < vec.dimension() - 1; i++) {
			out << vec.at(i) << ", ";
		}
		out << vec.at(vec.dimension() - 1) << "]";

		return out;
	}

	// Перегузка оператора приведения к вещественному типу - возращает длину
	operator double() { return length(); }
};


// variadic template функция:

// Перегрузка для терминального значения
double countSum() {
	return 0;
}

// Шаблон функции, принимающей множество аргументов разных типов
template<typename... RestArgs>
// Есть гарантированный первый элемент double first
double countSum(double first, RestArgs... rest) {
	// Сумма с помощью рекурсии
	return first + countSum(rest...);
}


int main() {
	int x, y, z;
	double x1, y1;
	cout << "Enter two numbers (press Enter to enter next number)\n";
	cin >> x1;
	cin >> y1;
	cout << "Enter vector coordinates (press Enter to enter next number)\n";
	cin >> x;
	cin >> y;
	cin >> z;
	// выводим сумму разных типов
	cout << "\n Sum is " << countSum(x1, y1, Vector<int, 3>{x, y, z}) << "\n"; 

	return 0;
}