#include "hangman_client.h"


#include "gtest/gtest.h"
#include "dungeon_explorer/dungeon_explorer_client.h"

TEST(Test1, Equality) {
  char result = feedback(2, 2);

  EXPECT_EQ(result, 'o');
}

TEST(Test2, Equality) {
  char result = feedback(4, 4);

  EXPECT_EQ(result, 'x');
}



