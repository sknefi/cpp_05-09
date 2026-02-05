#include <list>

#include "MutantStack.hpp"

static void test_subject_style()
{
    std::cout << "\n=== test_subject_style ===\n";

    MutantStack<int>	mstack;
    mstack.push(5);
    mstack.push(17);

    std::cout << "top: " << mstack.top() << "\n";

    mstack.pop();
    std::cout << "size after pop: " << mstack.size() << "\n";

    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);

    MutantStack<int>::iterator	it = mstack.begin();
    MutantStack<int>::iterator	ite = mstack.end();

    ++it;
    --it;

    std::cout << "iterating:\n";
    while (it != ite)
    {
        std::cout << *it << "\n";
        ++it;
    }

    // must compile: copy into std::stack
    std::stack<int>	s(mstack);
    (void)s;
}

static void test_const_iteration()
{
    std::cout << "\n=== test_const_iteration ===\n";

    MutantStack<int>	tmp;
    tmp.push(10);
    tmp.push(20);
    tmp.push(30);

    const MutantStack<int>	mstack(tmp);

    MutantStack<int>::const_iterator	it = mstack.begin();
    MutantStack<int>::const_iterator	ite = mstack.end();

    std::cout << "const iterating:\n";
    while (it != ite)
    {
        std::cout << *it << "\n";
        ++it;
    }
}

static void test_reverse_iteration()
{
    std::cout << "\n=== test_reverse_iteration ===\n";

    MutantStack<int> mstack;
    for (int i = 1; i <= 5; ++i)
        mstack.push(i);

    MutantStack<int>::reverse_iterator	rit = mstack.rbegin();
    MutantStack<int>::reverse_iterator	rite = mstack.rend();

    std::cout << "reverse iterating:\n";
    while (rit != rite)
    {
        std::cout << *rit << "\n";
        ++rit;
    }
}

static void test_compare_with_list()
{
    std::cout << "\n=== test_compare_with_list ===\n";

    MutantStack<int>	mstack;
    mstack.push(1);
    mstack.push(2);
    mstack.push(3);

    std::list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);

    std::cout << "mutantstack:\n";
    for (MutantStack<int>::iterator	it = mstack.begin(); it != mstack.end(); ++it)
        std::cout << *it << "\n";

    std::cout << "list:\n";
    for (std::list<int>::iterator	it = lst.begin(); it != lst.end(); ++it)
        std::cout << *it << "\n";
}

int main()
{
    test_subject_style();
    test_const_iteration();
    test_reverse_iteration();
    test_compare_with_list();
    
	return (0);
}
