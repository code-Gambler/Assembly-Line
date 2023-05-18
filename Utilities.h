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
#pragma once
#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H
#include<string>
namespace sdds
{
	typedef std::string String;
	class Utilities
	{
		size_t m_widthField{ 1 };
		static char m_delimiter;
	public:
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		String extractToken(const String& str, size_t& next_pos, bool& more);
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();
		static String trim(String& str);
	};
}
#endif // !SDDS_UTILITIES_H


