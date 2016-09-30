#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
SCENARIO("size off empty tree must be equal"){
  GIVEN("emptytree"){
     
    WHEN ("decide size"){
       BinarySearchTree<T> tree;
      THEN("size must be equal")
        REQUIRE(tree.size()==0);
    }  
 
  
      WHEN("not empry tree"){
        BinarySearchTree<T> tree {234,4234,421};
        THEN("size must be not equal")
          REQUIRE(tree.size()!=0);
  }
    WHEN("const"){
      const BinarySearchTree<T> tree {234,4234,421};
      BinarySearchTree<T> const_tree {234,4234,421};
      THEN("const and not const")
        REQUIRE(tree.size()!=0 && const_tree.size()!=0);
    }
  }
}
