#include "../include/BinarySearchTree.h"
#include <string>
#include <fstream>
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
int main()
{
	BinarySearchTree<int> bst1{ 5345, 435, 435, 34, 534 };
	std::cout << bst1 << '\n';
	
	return 0;
}
 
