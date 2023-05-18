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
#ifndef SDDS_CUSTOMERORDER_H
#include<string>
#include<iostream>
#include"Station.h"
typedef std::string String;
namespace sdds
{
	struct Item
	{
		String m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		Item(const String& src) : m_itemName(src) {};
	};
	class CustomerOrder
	{
		String m_name{};
		String m_product{};
		size_t m_cntItem{};
		Item** m_lstItem{};
		static size_t m_widthField;
	public:
		CustomerOrder();
		CustomerOrder(const String record);
		CustomerOrder& operator=(const CustomerOrder& src) = delete;
		CustomerOrder(const CustomerOrder& src);
		CustomerOrder(CustomerOrder&& src) noexcept;
		CustomerOrder& operator=(CustomerOrder&& src) noexcept;
		bool isOrderFilled() const;
		bool isItemFilled(const String& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
		~CustomerOrder();
	};
}
#endif // !SDDS_CUSTOMERORDER_H


