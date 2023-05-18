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
#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include<string>
#include<iostream>
namespace sdds
{
	typedef std::string String;
	typedef unsigned int Int;
	class Station
	{
		int		m_id{};
		String	m_name{};
		String	m_desc{};
		Int		m_nextSerialNo{ 0 };
		Int		m_noOfItems{ 0 };
		static int id_generator;
		static size_t m_widthField;
	public:
		Station(const String record);
		const String& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}
#endif // !SDDS_STATION_H


