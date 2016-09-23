#include "BinarySearchTree.h"

int main()
{
	BinarySearchTree<int> bst1{ 5345, 435, 435, 34, 534 };
	std::cout << bst1 << '\n';
	std::ofstream ofs("C:\tree.txt");
	if (!ofs){
		std::cout << "file not create!!"<<'\n';
	}


	BinarySearchTree<int> bst2;
	std::cin >> bst2;
	if (bst2.insert(7)){
		std::cout << bst2 << '\n';
	}
	std::cout << bst2 << '\n';

	BinarySearchTree<int> bst3{ 5345, 3, 435, 34, 534 };
	const int* found = bst3.find(3);
	std::cout <<"FIND: "<< *found  << '\n';

	system("pause");
	return 0;
}
 
