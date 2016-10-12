#include <BinarySearchTree.hpp>
#include "catch.hpp"

  SCENARIO("после удаления элемемнта из дерева структура должна быть другой")
  {
      GIVEN("TWO TREES")
           BinarySearchTree<int> bst1{ 10,15,14,16,20,25,7};
           BinarySearchTree<int> bst2{ 10,15,14,16,20,25,};
           WHEN("удаления элемента без дочерних")
            {
              bst1.remove(7);
              THEN("деревья должны быть одинаковыми")
                {
                  REQUIRE(bst1==bst2);
                }
             }
             
             BinarySearchTree<int> bst1{ 10,15,14,16,20,25,7,17};
             BinarySearchTree<int> bst2{ 10,15,14,16,20,25,7};
             WHEN("удаления элемента у которого есть один правый ребенок")
            {
              bst1.remove(17);
              THEN("деревья должны быть одинаковыми")
                {
                  REQUIRE(bst1==bst2);
                }
             }
             
             BinarySearchTree<int> bst1{ 10,15,14,16,20,25,7,17,30};
             BinarySearchTree<int> bst2{ 10,15,14,16,20,25,7,17};
             WHEN("удаления элемента у которого есть один левый ребенок")
            {
              bst1.remove(30);
              THEN("деревья должны быть одинаковыми")
                {
                  REQUIRE(bst1==bst2);
                }
             }
             
             BinarySearchTree<int> bst1{ 10,15,14,16,20,25,7,17,30};
             BinarySearchTree<int> bst2{ 10,15,14,16,25,7,17,30};
             WHEN("удаления элемента у которого есть и левый ребенок и правый")
            {
              bst1.remove(20);
              THEN("деревья должны быть одинаковыми")
                {
                  REQUIRE(bst1==bst2);
                }
             }
             
             
             BinarySearchTree<int> bst1{ 10};
             BinarySearchTree<int> bst2();
             WHEN("удаления корня")
            {
              bst1.remove(10);
              THEN("деревья должны быть одинаковыми")
                {
                  REQUIRE(bst1==bst2);
                }
             }
             
             BinarySearchTree<int> bst1{ 10,15,14,16,20,25,7,17,30};
             BinarySearchTree<int> bst2{ 10,15,14,16,20,25,7,17,30};
             WHEN("удаление элемента, которого нет в дереве")
            {
              bst1.remove(6666);
              THEN("деревья должны быть одинаковыми")
                {
                  REQUIRE(bst1==bst2);
                }
             }
          }
       }
