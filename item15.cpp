// constexpr objects are const
// can be used where C++ needs an integral constant expression
{ // error
	int sz;
	constexpr auto arraySize1 = sz;
	std::array<int, sz> data1;
}

constexpr auto arraySize2 = 10;
std::array<int, arraySize2> data2; // ok but needs constexpr, const doesn't cut it

// constexpr functions produce compile-time constants when they are called with compile-time
// constants
// Doesn't mean that returns a const

constexpr
int pow(int base, int exp) noexcept
{
	...
}

constexpr auto numbConds = 5;
std::array<int, pow(3, numConds)> results;

// in C++11, only a return statement, but you can do things like ternary op and recursion
// in C++14, much looser. One condition is that you must take and return literal types
// (types that can have values determined during compilation, all built-in except void)

class Point 
{
public:
	constexpr Point(double xVal = 0, double yVal = 0) noexcept
	: x(xVal), y(yVal)
	{}

	constexpr double xValue() const noexcept { return x; }
	constexpr double yValue() const noexcept { return y; }

	void setX(double newX) noexcept { x = newX; }
	void setY(double newY) noexcept { y = newY; }
private:
	double x, y;
};

// so these are fine
constexpr Point p1(9.4, 27.7);
constexpr Point p2(28.8, 5.3);
