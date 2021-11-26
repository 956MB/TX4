#ifndef TX4_CHECKBOX_H
#define TX4_CHECKBOX_H

#include <QWidget>
#include "tx4_util.h"

#define BOX_S 18

class tx4_checkbox : public QWidget {
	Q_OBJECT

	public:
		explicit tx4_checkbox(QWidget* parent = nullptr);
		~tx4_checkbox();

	public:
		void setCheckboxState(bool state);

	private:
		QWidget *outer;
		QWidget *inner;
	
		bool checkActive;

		QString outerStyle = "background-color: none; border-style: solid; border-width: 3px; border-color: white;";
		QString innerStyle = "background-color: white; border: none; outline: none;";
		QString blankStyle = "background-color: none; border: none; outline: none;";
		
		void initContents();

};

#endif // TX4_CHECKBOX_H