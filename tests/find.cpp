#include "../include/BinarySearchTree.h"
#include "catch.h"

SCENARIO("if_element_in_tree method must return it's pointer") 
{
    GIVEN("tree_not_zero") 
    {
        BinarySearchTree<int> tree{1, 4, 5};
        WHEN("find") 
        {
            THEN("must not nullptr") 
            {
                REQUIRE(*(tree.find(4)) == 4);
            }
        }
    }
}

SCENARIO("if element not in tree, method must return null") 
{
    GIVEN("tree") 
    {
        BinarySearchTree<int> tree{1, 4, 5};
        WHEN("find") 
        {
            THEN("must be nullptr") 
            {
                REQUIRE(tree.find(2) == nullptr);
            }
        }
    }
}

SCENARIO("method must work for constant and not constant tree") 
{
    GIVEN("constant and nt constant tree") 
    {
        const BinarySearchTree<int> tree1{1, -2, 0};
        BinarySearchTree<int> tree2{1, 4, 5};
        WHEN("find") 
        {
            THEN("return element for constant and non-constant tree") 
            {
                REQUIRE(tree1.find(-2) && tree2.find(1));
            }
        }
    }
}