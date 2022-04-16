#include "uiblock.h"

UIBlock::UIBlock(QWidget *parent) : QWidget(parent) {
  new QLabel("block_name", parent);
}
