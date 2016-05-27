#ifndef KEYPROCESSOR_H
#define KEYPROCESSOR_H

#include <QString>
#include <QList>
#include "keydata.h"

class KeyProcessor
{

public:
	KeyProcessor();
    QString process(QString str);


private:
	QString lastString;
	QList<QChar> numList;

	QChar getNewPressedKey(QString str, int &index);
	QList<int> findAllInStr(QString str, QChar charToFind);
	int findSpecialChar(QChar sChar);
    
};

#endif