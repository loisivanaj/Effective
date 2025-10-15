// no init
int x;

// long ass type declarations
template<class It>
void dwim(It b, It e)
{
	while (b != e)
	{
		// std::iterator_traits<It>::value_type could be an enum value
		// typename specifies that it's a type
		typename std::iterator_traits<It>::value_type currValue = *b;
	}
}

// closures have abominable compiler generated types
??? f = [](int x) { return x*2; }

// auto fixes all of these
// (1) auto type comes from initializer, so need to be initialized
int x1; 	// uninit
auto x2;	// error, init required
auto x3 = 0;	// yessir

// (2)
template<class It>
void dwim(It b, It e)
{
	while (b != e)
	{
		auto currValue = *b;
	}
}

// (3)
auto derefUPLess = [](const std::unique_ptr<Widget>& p1, const std::unique_ptr<Widget>& p2) { return *p1 < *p2; }
auto derefLess = [](const auto& p1, const auto& p2) { return *p1 < *p2; }; // c++14: auto in lambda arg

// another way to store lambdas
std::function<bool(const std::unique_ptr<Widget>&, const std::unique_ptr<Widget>&)>
derefUpLess = [](const std::unique_ptr<Widget>& p1, const std::unique_ptr<Widget>& p2)
	        { return *p1 < *p2; };

// problem is that using std::function is not the same as auto
// - auto-declared variable holding a closure will have the same type as the closure
//   hence it will use only as much memory as the closure requires (quick note: closure is instanciated lambda expression)
// - std::function will need the memory needed for that (fixed) and needed additional
//   mem for the closure will be allocated on the heap -> more space and slower

// a big problem with explicit typing is that implicit type conversions can happen unbeknownst
std::vec<int> v;
unsigned sz = v.size(); // decltype(v.size()) is actually std::vector<int>::size_type
			// size_type is 64 bits whereas unsigned is 32 bits

std::unordered_map<std::string, int> m;
for (const std::pair<std::string, int>& p : m) { do_something(p); }
// problem: the key is supposed to be const, so really we should have const std::pair<const std::string, int>&
// compilers will try to go from the const to a non-cost and typically will create a temp copy to which p will bind
// instead of binding to what we really wanted (the hashtable)

// fix:
for (const auto& p : m) { ... }
