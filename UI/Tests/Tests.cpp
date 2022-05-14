#include <gtest/gtest.h>
#include <stdio.h>
#include <string>
#include <vector>

#include "UI.h"
#include "mainwindow.h"
#include "qtlistofblocks.h"
#include "requiredvariables.h"
#include "schemewidget.h"
#include "blockwidget.h"
#include "newblockwidget.h"

#include "block.hpp"

TEST(scheme_getreqvars, OneBlockCase) {
  std::string dens = "density";
  std::string two = "2";
  std::string vol = "volume";
  std::string three = "3";
  std::string mas = "mass";
  std::string six = "6";
  Parameter density = {dens, two};
  Parameter volume = {vol, three};
  Parameter mass = {mas, six};
  std::vector<Parameter> givenvars;
  std::vector<Parameter> solvedvars;

  givenvars.push_back(density);
  givenvars.push_back(volume);
  solvedvars.push_back(mass);
  std::string path = "path";
  std::string name = "test block";
  std::string description = "It is a test block";
  std::string author = "Me";
  int color = 10;

  Block test_block = {path, givenvars, solvedvars, name, description, author, color};

  Scheme scheme;
  std::vector<Block> blocks_of_scheme;
  blocks_of_scheme.push_back(test_block);
  scheme.blocks = blocks_of_scheme;
  scheme.environment_variables = scheme.get_required_vars();
  
  ASSERT_EQ(scheme.environment_variables.size(), 2);
  EXPECT_EQ(scheme.environment_variables[0].param_name, dens);
  EXPECT_EQ(scheme.environment_variables[0].param_value, two);
  EXPECT_EQ(scheme.environment_variables[1].param_name, vol);
  EXPECT_EQ(scheme.environment_variables[1].param_value, three);
}

TEST(scheme_getreqvars, TwoBlocksCase) {
  std::string dens = "density";
  std::string two = "2";
  std::string vol = "volume";
  std::string three = "3";
  std::string mas = "mass";
  std::string six = "6";
  Parameter density = {dens, two};
  Parameter volume = {vol, three};
  Parameter mass = {mas, six};
  std::vector<Parameter> givenvars1;
  std::vector<Parameter> solvedvars1;

  givenvars1.push_back(density);
  givenvars1.push_back(volume);
  solvedvars1.push_back(mass);
  std::string path1 = "path";
  std::string name1 = "test block";
  std::string description1 = "It is a test block";
  std::string author1 = "Me";
  int color1 = 10;

  Block test_block1 = {path1, givenvars1, solvedvars1, name1, description1, author1, color1};

  std::string rad = "side";
  std::string four = "4";
  std::string ar = "area";
  std::string sixteen = "16";
  Parameter side = {rad, four};
  Parameter area = {ar, sixteen};
  std::vector<Parameter> givenvars2;
  std::vector<Parameter> solvedvars2;

  givenvars2.push_back(side);
  solvedvars2.push_back(area);
  std::string path2 = "path2";
  std::string name2 = "test block2";
  std::string description2 = "It is a test block2";
  std::string author2 = "Me";
  int color2 = 11;

  Block test_block2 = {path2, givenvars2, solvedvars2, name2, description2, author2, color2};

  Scheme scheme;
  std::vector<Block> blocks_of_scheme;
  blocks_of_scheme.push_back(test_block1);
  blocks_of_scheme.push_back(test_block2);
  scheme.blocks = blocks_of_scheme;
  scheme.environment_variables = scheme.get_required_vars();
  
  ASSERT_EQ(scheme.environment_variables.size(), 3);
  EXPECT_EQ(scheme.environment_variables[0].param_name, dens);
  EXPECT_EQ(scheme.environment_variables[0].param_value, two);
  EXPECT_EQ(scheme.environment_variables[1].param_name, vol);
  EXPECT_EQ(scheme.environment_variables[1].param_value, three);
  EXPECT_EQ(scheme.environment_variables[2].param_name, rad);
  EXPECT_EQ(scheme.environment_variables[2].param_value, sixteen);
}

TEST(scheme_deleteblock, OneBlockCase) {
  std::string dens = "density";
  std::string two = "2";
  std::string vol = "volume";
  std::string three = "3";
  std::string mas = "mass";
  std::string six = "6";
  Parameter density = {dens, two};
  Parameter volume = {vol, three};
  Parameter mass = {mas, six};
  std::vector<Parameter> givenvars;
  std::vector<Parameter> solvedvars;

  givenvars.push_back(density);
  givenvars.push_back(volume);
  solvedvars.push_back(mass);
  std::string path = "path";
  std::string name = "test block";
  std::string description = "It is a test block";
  std::string author = "Me";
  int color = 10;

  Block test_block = {path, givenvars, solvedvars, name, description, author, color};

  Scheme scheme;
  std::vector<Block> blocks_of_scheme;
  blocks_of_scheme.push_back(test_block);
  scheme.blocks = blocks_of_scheme;
  scheme.delete_block(0);

  EXPECT_EQ(scheme.blocks.size(), 0);
}

TEST(scheme_deleteblock, TwoBlocksCase) {
  std::string dens = "density";
  std::string two = "2";
  std::string vol = "volume";
  std::string three = "3";
  std::string mas = "mass";
  std::string six = "6";
  Parameter density = {dens, two};
  Parameter volume = {vol, three};
  Parameter mass = {mas, six};
  std::vector<Parameter> givenvars1;
  std::vector<Parameter> solvedvars1;

  givenvars1.push_back(density);
  givenvars1.push_back(volume);
  solvedvars1.push_back(mass);
  std::string path1 = "path";
  std::string name1 = "test block";
  std::string description1 = "It is a test block";
  std::string author1 = "Me";
  int color1 = 10;

  Block test_block1 = {path1, givenvars1, solvedvars1, name1, description1, author1, color1};

  std::string rad = "side";
  std::string four = "4";
  std::string ar = "area";
  std::string sixteen = "16";
  Parameter side = {rad, four};
  Parameter area = {ar, sixteen};
  std::vector<Parameter> givenvars2;
  std::vector<Parameter> solvedvars2;

  givenvars2.push_back(side);
  solvedvars2.push_back(area);
  std::string path2 = "path2";
  std::string name2 = "test block2";
  std::string description2 = "It is a test block2";
  std::string author2 = "Me";
  int color2 = 11;

  Block test_block2 = {path2, givenvars2, solvedvars2, name2, description2, author2, color2};

  Scheme scheme;
  std::vector<Block> blocks_of_scheme;
  blocks_of_scheme.push_back(test_block1);
  blocks_of_scheme.push_back(test_block2);
  scheme.blocks = blocks_of_scheme;
  scheme.delete_block(0);

  EXPECT_EQ(scheme.blocks.size(), 1);
  scheme.delete_block(0);
  EXPECT_EQ(scheme.blocks.size(), 0);
}

TEST(scheme_addblock, BaseCase) {
  std::string dens = "density";
  std::string two = "2";
  std::string vol = "volume";
  std::string three = "3";
  std::string mas = "mass";
  std::string six = "6";
  Parameter density = {dens, two};
  Parameter volume = {vol, three};
  Parameter mass = {mas, six};
  std::vector<Parameter> givenvars;
  std::vector<Parameter> solvedvars;

  givenvars.push_back(density);
  givenvars.push_back(volume);
  solvedvars.push_back(mass);
  std::string path = "path";
  std::string name = "test block";
  std::string description = "It is a test block";
  std::string author = "Me";
  int color = 10;

  Block test_block = {path, givenvars, solvedvars, name, description, author, color};

  Scheme scheme;
  scheme.add_block(test_block, 0);

  ASSERT_EQ(scheme.blocks.size(), 1);
  EXPECT_EQ(scheme.blocks[0].GetName(), name);
  EXPECT_EQ(scheme.blocks[0].GetAuthorName(), author);
  EXPECT_EQ(scheme.blocks[0].GetGivenVars()[0].param_name, dens);
}

TEST(list_of_blocks, NoThrowLOB) {
  ListOfBlocks list_of_blocks;
  EXPECT_NO_THROW(list_of_blocks.make_qt_frames());
}

TEST(scheme, NoThrowSCH) {
  Scheme scheme;
  EXPECT_NO_THROW(scheme.make_qt_frames());
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}