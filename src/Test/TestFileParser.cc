#include <gtest/gtest.h>

#include "../app/fileparserfacade.h"

TEST(FileParserFacade, Test1) {
  s21::FileParserFacade parser("for_test.obj");
  EXPECT_EQ(parser.processFile(), true);
  EXPECT_EQ(parser.getIndexes()[0], 4);
  EXPECT_EQ(parser.getIndexes()[1], 2);
  EXPECT_EQ(parser.getIndexes()[2], 2);
  EXPECT_EQ(parser.getIndexes()[3], 1);
  EXPECT_EQ(parser.getIndexes()[4], 1);
  EXPECT_EQ(parser.getIndexes()[5], 4);
  EXPECT_EQ(parser.getIndexes()[6], 1);
  EXPECT_EQ(parser.getVertexes()[4], 0.6f);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
