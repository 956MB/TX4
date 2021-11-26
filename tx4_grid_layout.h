#ifndef TX4_GRID_LAYOUT_H
#define TX4_GRID_LAYOUT_H

#include <QGridLayout>

class tx4_grid_layout : public QGridLayout {
	Q_OBJECT

    public:
        tx4_grid_layout(QWidget *parent, int max_column_count );
        ~tx4_grid_layout();

        void add_widget( QWidget* p_widget );

    private:
        int m_max_column_count;

};

#endif // TX4_GRID_LAYOUT_H