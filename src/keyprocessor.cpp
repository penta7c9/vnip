#include "keyprocessor.h"


KeyProcessor::KeyProcessor()
{
	numList.push_back('1');
	numList.push_back('2');
	numList.push_back('3');
	numList.push_back('4');
	numList.push_back('5');
	numList.push_back('6');
	numList.push_back('7');
	numList.push_back('8');
	numList.push_back('9');
}

// Convert normal string to Unicode
QString KeyProcessor::process(QString str)
{
	QString result = str;

	int keyIndex = -1;
	QString key(getNewPressedKey(str, keyIndex));

	if (keyIndex != -1)
	{
		bool stop = false;
		for (int i = keyIndex - 1; i >= 0; i--)
		{
			QChar converFrom = str[i];
			if (converFrom == ' ') break;
			if (stop && converFrom != 'd') continue;

			int convertFromIndex = findSpecialChar(converFrom);
			if (convertFromIndex == -1) continue;

			QString convertTo = KeyData::RESULT_CHARS[convertFromIndex][numList.indexOf(key[0])];
			if (convertTo == "") continue;
			
			result = str.remove(keyIndex, 1);
			result = result.replace(i, 1, convertTo);

			if (i - 1 >= 0)
			{
				QChar beforeConvertFrom = str[i - 1];
				int beforeConvertFromIndex = findSpecialChar(beforeConvertFrom);
				if (beforeConvertFromIndex != -1)
				{
					QString beforeCases = "iyu";
					stop = beforeCases.contains(beforeConvertFrom);

					QString uForms = "uúùủũụưứừửữự";
					QString oForms = "ơớờởỡợ";
					QString yForms = "yýỳỷỹỵ";
					bool beforeRelatedToU = uForms.contains(beforeConvertFrom);
					bool currentRelatedToO = oForms.contains(convertTo);
					bool currentRelatedToY = yForms.contains(convertTo);
					if (beforeRelatedToU && currentRelatedToO)
					{
						result = result.replace(i - 1, 1, "ư");
						stop = true;
					}
					if (beforeRelatedToU && currentRelatedToY)
					{
						stop = false;
					}
				}	
			}
		}
	}

	lastString = result;
	return result;
}

// Get new pressed key from 1 to 9
QChar KeyProcessor::getNewPressedKey(QString str, int &index)
{
	// Compare lastString and str, check if there is a new pressed number (1 to 9)
	if (lastString.count() == str.count() - 1)
	{
		// Find change in the middle
		for (int i = 0; i < lastString.count(); ++i)
		{
			if (lastString[i] != str[i] && numList.contains(str[i])) 
			{
				index = i;
				return str[i];
			}
		}

		// There is no change in the middle of 'str'
		if (numList.contains(str[str.count() - 1]))
		{
			index = str.count() - 1;
			return str[index];
		}
	}

	return '0';
}

// Find all index of 'charToFind' in the 'str' and return a list of index
QList<int> KeyProcessor::findAllInStr(QString str, QChar charToFind)
{
	int i = 0;
	QList<int> resultList;

	while (i != -1 && i < str.count())
	{
		i = str.indexOf(charToFind, i);
		if (i != -1)
		{
			resultList.push_back(i);
			i += 1;
		}
	}

	return resultList;
}

// Check if the input char is in the KeyData::LOOKUP_CHARS
int KeyProcessor::findSpecialChar(QChar sChar)
{
	QString str(sChar);
	for (int i = 0; i < KeyData::LOOKUP_CHARS_LENGTH; ++i)
	{
		if (str == KeyData::LOOKUP_CHARS[i]) return i;
	}
	return -1;
}