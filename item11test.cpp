class test 
{
public:
	test(const test&) 	     = delete;
	test& operator=(const test&) = delete;
};

int main() 
{
	 test t, ta;
	 ta = t;
	 test tc = t;

	std::vector<bool> v;
	
}
