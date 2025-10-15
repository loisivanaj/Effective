if (v[0] == 0) ...	// decltype(v[0]) is int&
		
// primary use: function templates
// say the return type depends on the parameter type
// operator[] return depends on the container, typically a & but not always
// std::vector<bool> [] returns a copy and not a bool&
// in the following example, decltype fixes that for us

template<typename Container, typename Index>
auto authAndAccess(Container& c, Index, i) -> decltype(c[i])
{
	authenticateUsers();
	return c[i];
}

// auto has nothing to do with type deduction.
// here it means that trailing type declaration for a function is in use

// after c++14, the trailing part isn't even needed for all functions and lambdas
template<typename Container, typename Index>
auto authAndAccess(Container& c, Index, i)
{
	authenticateUsers();
	return c[i];
}

// problem now: if a function has an auto return type, template type deduc is used
// but template type deduc drops reference-ness
std::deque<int> d;
authAndAccess(d, 5) = 10;	// auth user, return d[5]
				// then assign 10 -> won't compile
				// d[5] is an int& but auto drops the &
				// hence the return is an rvalue and you try
				// to assign 10 to an rvalue
// c++14:
template<typename Container, typename Index>
decltype(auto)			// means that auto will take decltype return
authAndAccess(Container& c, Index i)
{
	authenticateUser();
	return c[i];
}
// reminder, auto is essentially the "T" in the template used for deduction.
// So if you pass by value, it'll drop the ref (and the const)
// if you say const auto& -> it will do const T& in the template and so on

Widget w;
const Widget& cw = w; 		// Widget
auto myWidget1 = cw;		// Widget
decltype(auto) myWidget2 = cw;	// const Widget&

// fun fact for me: when you write
const std::string& s = std::string("Hello");
// you're binding an R value to a const lvalue reference
// the compiler then kinda extends the lifetime of the temp

//back on track
template<typename Container, typename Index>
decltype(auto) authAndAccess(Container&& c, Index i);
// you want to be careful using pass-by-value in general because you don't really know
// what kind of object a user is going to put in there and that might incur unnecessary
// copies. Index is ok

template<typename Container, typename Index>
decltype(auto)
authAndAccess(Container&& c, Index i)
{
	authenticateUser();
	return std::forward<Container>(c)[i];
}
