#include "tx4_grid_layout.h"

tx4_grid_layout::tx4_grid_layout(QWidget *parent, int max_column_count) : QGridLayout(parent) {
    m_max_column_count = max_column_count;
}

tx4_grid_layout::~tx4_grid_layout() {}

void tx4_grid_layout::add_widget( QWidget* p_widget ) {
    int current_row = 0;
    int current_column = 0;

    while( itemAtPosition(current_row, current_column) != 0 )
    {
        if( current_column == (m_max_column_count-1) )
        {
            current_column = 0;
            ++current_row;
        }
        else
        {
            ++current_column;
        }
    }

    QGridLayout::addWidget( p_widget, current_row, current_column );
}