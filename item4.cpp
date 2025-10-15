const int theAnswer = 42;
auto x = theAnswer;
auto y = &theAnswer;

template<class T>
class TD;

// try compiler diagnostics
TD<decltype(x)> xType;		// int
TD<decltype(y)> yType;		// const int*

// runtime output
std::cout << typeid(x).name() << '\n'; // returns std::type_info obejct
std::cout << typeid(y).name() << '\n';
// kinda ok-ish

template<class T>
void f(const T& param);

std::vector<Widget> createVec();

const auto vw = createVec();

if (!vw.empty())
{
	f(&vw[0]); // weird stuff happens with typeid here
}

// boost solves all of this
#include <boost/type_index.hpp>
template<class T>
void f(const T& param)
{
	using std::cout;
	using boost::typeindex::type_id_with_cvr;
	
	// show T
	cout << "T = 	"
	     << type_id_with_cvr<T>().pretty_name() // cvr = const, volatile, reference (which auto kills)
	     << '\n';

	// show param type
	cout << "param = "
	     << type_id_with_cvr<decltype(param)>().pretty_name()
	     << '\n';
}
