#include "block.hpp"
#include <vector>
#include <QLayout>
#include "qtscheme.h"

#ifndef CHEME_H
#define CHEME_H

class Scheme
{
public:
    std::vector<Parameter> environment_variables;
    std::vector<Block> blocks;

    Scheme();
    ~Scheme();
    void delete_block(size_t identificator);
    void add_block(Block block, size_t position);
    std::vector<Parameter> get_required_vars();
    std::vector<Parameter> run();
    QTScheme make_qt_frames();
};

#endif // CHEME_H
