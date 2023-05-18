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
#include "Station.h"
#include"Utilities.h"
namespace sdds
{
	int Station::id_generator = 0;
	size_t Station::m_widthField = 0;
	Station::Station(const String record)
	{
		String temp;
		Utilities utility;
		size_t next_pos = 0;
		bool more = false;
		m_id = id_generator + 1;
		id_generator++;
		temp = utility.extractToken(record, next_pos, more);
		m_name = temp;
		if (more) {
			temp = utility.extractToken(record, next_pos, more);
			m_nextSerialNo = stoi(temp);
			if (more) {
				temp = utility.extractToken(record, next_pos, more);
				m_noOfItems = stoi(temp);
				if (m_widthField < utility.getFieldWidth())
				{
					m_widthField = utility.getFieldWidth();
				}
				if (more) {
					temp = utility.extractToken(record, next_pos, more);
					m_desc = temp;
				}
			}
		}
	}
	const String& Station::getItemName() const
	{
		return m_name;
	}
	size_t Station::getNextSerialNumber()
	{
		return m_nextSerialNo++;
	}
	size_t Station::getQuantity() const
	{
		return m_noOfItems;
	}
	void Station::updateQuantity()
	{
		if (m_noOfItems > 0) {
			m_noOfItems--;
		}
	}
	void Station::display(std::ostream& os, bool full) const
	{
		os.setf(std::ios::right);
		os.width(3); //Macro
		os.fill('0');
		os << m_id << " | ";
		os.unsetf(std::ios::right);
		os.setf(std::ios::left);
		os.width(m_widthField);
		os.fill(' ');
		os << m_name << "  | ";
		os.unsetf(std::ios::left);
		os.setf(std::ios::right);
		os.fill('0');
		os.width(6);
		os << m_nextSerialNo << " | ";
		os.unsetf(std::ios::right);
		if (full) {
			os.setf(std::ios::right);
			os.width(4);
			os.fill(' ');
			os << m_noOfItems << " | ";
			os.unsetf(std::ios::right);
			os.setf(std::ios::left);
			os << m_desc;
			os.unsetf(std::ios::left);
		}
		os << std::endl;
	}
}


