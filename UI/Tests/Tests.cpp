#include <gtest/gtest.h>
#include <stdio.h>


#include "UI.h"
#include "listofblocks.h"
#include "mainwindow.h"
#include "QTlistofblocks.h"
#include "qtrequiredvariables.h"
#include "qtscheme.h"
#include "Scheme.h"
#include "uiblock.h"

TEST(UI, ExampleCase) {
  EXPECT_EQ(5, 5);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}