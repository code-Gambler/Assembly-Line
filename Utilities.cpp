/*
*****************************************************************************
							   MileStone-3
Full Name  : Steven David Pillay
Student ID#: 162218218
Email      : spillay@myseneca.ca
Section    : ZDD
Date       : 08/04/2023

Authenticity Declaration:
I have done all the coding by myself and only copied the code that my
professor provided to complete my workshops and assignments.
*****************************************************************************
*/
#include "Utilities.h"
namespace sdds
{
	char Utilities::m_delimiter = '\0';
	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}
	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}
	String Utilities::extractToken(const String& str, size_t& next_pos, bool& more)
	{
		String temp = "";
		temp = str.substr(next_pos, str.find(m_delimiter, next_pos) - next_pos);
		if (str.find(m_delimiter, next_pos) == next_pos)
		{
			more = false;
			throw ("Error:Delimiter Found at next_pos");
		}
		trim(temp);
		if (m_widthField < temp.length())
		{
			m_widthField = temp.length();
		}
		if(str.find(m_delimiter, next_pos) != String::npos)
		{
			next_pos = str.find(m_delimiter, next_pos) + 1;
			more = true;
		}
		else 
		{
			more = false;
		}
		return temp;
	}
	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}
	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}
	String Utilities::trim(String& str)
	{
		size_t i = str.find_first_not_of(" ");
		str = str.substr(i);

		i = str.find_last_not_of(" ");
		str = str.substr(0, i + 1);
		return str;
	}
}