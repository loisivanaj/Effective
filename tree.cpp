#include <utility>
#include <iostream>

template <class T>
class tree {
public:
	T value;
	tree<T> *lptr, *rptr;

	tree(const T& val) : value(val), lptr(nullptr), rptr(nullptr) {}
	~tree() { delete lptr; delete rptr; }
};

template <class T>
void invert(tree<T>* tptr)
{
	if (tptr == nullptr) { return; }
	std::swap(tptr->lptr, tptr->rptr);
	invert(tptr->lptr); invert(tptr->rptr);
}

template <class T>
void print_inorder(const tree<T>* node) {
    if (!node) return;
    print_inorder(node->lptr);
    std::cout << node->value << " ";
    print_inorder(node->rptr);
}

int main()
{
	tree<int>* root = new tree<int>(10); // const T& binds to rvalue, extends rvalue lifetime
	root->lptr = new tree<int>(5);
	root->rptr = new tree<int>(15);
	root->lptr->lptr = new tree<int>(2);
	root->rptr->rptr = new tree<int>(7);

	std:: cout << "in-order" << '\n';
	print_inorder(root);
	std::cout << '\n';

	std::cout << "reverse" << '\n';
	invert(root);
	print_inorder(root);
	std::cout << '\n';

	delete root;
}
