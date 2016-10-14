#include <BinarySearchTree.hpp>
#include "catch.hpp"

  SCENARIO("the tree size must decrease by one after removing element")
  {
      GIVEN("two trees")
      {
           BinarySearchTree<int> bst1{ 10,20,30,15,14,40};
           BinarySearchTree<int> bst2{ 10,20,30,15,40};
           
           WHEN("remove node that hasn't children")
            {
              bst1.remove(bst1.root_,14);
              THEN("trees must be equal")
                {
                  REQUIRE(bst1==bst2);
                }
             }
             
            bst1 = BinarySearchTree<int> ({ 10,20,30,15,14,40});
            bst2 = BinarySearchTree<int> ({ 10,20,15,14,40});
             WHEN("remove node that has only right child")
            {
              bst1.remove(bst1.root_,30);
              THEN("trees must be equal")
                {
                  REQUIRE(bst1==bst2);
                }
             }
             
             bst1 = BinarySearchTree<int> ({ 10,20,30,15,14,40});
             bst2 = BinarySearchTree<int> ({ 10,20,30,14,40});
             WHEN("remove node that has only left child")
            {
               bst1.remove(bst1.root_,15);
              THEN("trees must be equal")
                {
                  REQUIRE(bst1==bst2);
                }
             }
             
            bst1 = BinarySearchTree<int> ({ 10,20,30,15,14,40});
            bst2 = BinarySearchTree<int> ({ 10,30,15,14,40});
             WHEN("remove node that has both children")
            {
               bst1.remove(bst1.root_,20);
              THEN("trees must be equal")
                {
                  REQUIRE(bst1==bst2);
                }
             }
             
            bst1 = BinarySearchTree<int>({ 10,20,30,15,14,40});
            bst2 = BinarySearchTree<int>({ 10,20,30,15,14,40});
             WHEN("remove node that doesn't exist")
            {
               bst1.remove(bst1.root_,200);
              THEN("trees must be equal")
                {
                  REQUIRE(bst1==bst2);
                }
             }
        
            bst1 = BinarySearchTree<int>({ 10,20,30,15,14,40});
	    bst2 = BinarySearchTree<int>({ 20,30,15,14,40});
             WHEN("remove root")
            {
               bst1.remove(bst1.root_,10);
              THEN("trees must be equal")
                {
                  REQUIRE(bst1==bst2);
                }
             }
          }
       }
