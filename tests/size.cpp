#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

SCENARIO( "vectors " ) {

    GIVEN( "A BinaryST with some items" ) {
        BinarySearchTree <int> test;
        
        WHEN("if BST null- size==0")
        {
          THEN("the size==0")
            {
            REQUIRE( test.size() == 0 );
            }
        }
        WHEN("if BST not null- size>0")
        {
          const BinarySearchTree<int> test1{1};
          BinarySearchTree<int> test2{1};
          THEN("the size>0")
           {
            REQUIRE ( test1.size()>0 && test2.size()>0 )
           }
        }
