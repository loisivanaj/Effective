// 0 is an int, NULL is something (int typically but implementation dep)
// none of them are pointer types
// problem is that overloading on pointer and integral types would result in la grande surprise

void f(int);
void f(bool);
void f(void*);

f(0); 	   // calls f(int), not f(void*)
f(NULL);   // might not compile, will never call f(void*) anyway bum ass

// here comes nullptr -> not an integral type
// technically doesn't have a pointer type either, std::nullptr_t
// but implicitly converts to all raw pointer types

f(nullptr); // calls f(void*)

// also increases clarity
auto result = findRecord( /* args */ );
if (result == 0)       { ... } 	// not clear what result is
if (result == nullptr) { ... }	// clear that ptr

// shines in templates
int	f1(std::shared_ptr<Widget> spw);
double  f2(std::unique_ptr<Widget> upw);
bool    f3(Widget* pw);

std::mutex f1m, f2m, f3m;
using MuxGuard = std::lock_guard<std::mutex>;
{
	MuxGuard g(f1m); 	// lock f1 mutex
	auto result = f1(0);
}				// unlock

{
	MuxGuard g(f2m);
	auto result = f2(NULL);
}

{
	MuxGuard g(f3m);
	auto result = f3(nullptr);
}

template<typename FuncType,
	 typename MuxType,
	 typename PtrType>
auto lockAndCall(FuncType func,
		 MuxType& mutex,
		 PtrType ptr) -> decltype(func(ptr))
{
	MuxGuard g(mutex);
	return func(ptr);
}
