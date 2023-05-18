/*
*****************************************************************************
							   MileStone-2
Full Name  : Steven David Pillay
Student ID#: 162218218
Email      : spillay@myseneca.ca
Section    : ZDD
Date       : 25/03/2023

Authenticity Declaration:
I have done all the coding by myself and only copied the code that my
professor provided to complete my workshops and assignments.
*****************************************************************************
*/
#include "CustomerOrder.h"
#include "Utilities.h"
namespace sdds
{
	size_t CustomerOrder::m_widthField = 0;
	CustomerOrder::CustomerOrder()
	{
		m_cntItem = 0;
		m_lstItem = nullptr;
		m_name = "";
		m_product = "";
		m_widthField = 0;
	}
	CustomerOrder::CustomerOrder(const String record)
	{
		String temp;
		Utilities utility;
		size_t next_pos = 0;
		bool more = false;
		temp = utility.extractToken(record, next_pos, more);
		m_name = temp;
		if (more) {
			temp = utility.extractToken(record, next_pos, more);
			m_product = temp;
			if (more) {
				size_t count = next_pos;
				bool loop = more;
				size_t i;
				for (i = 0; loop; i++) {
				temp = utility.extractToken(record, count, loop);
				}
				m_cntItem = i;
				m_lstItem = new Item*[m_cntItem];
				for (i = 0; i < m_cntItem; i++) {
					m_lstItem[i] = new Item(
						utility.extractToken(record, next_pos, more));
				}
				if (m_widthField < utility.getFieldWidth())
				{
					m_widthField = utility.getFieldWidth();
				}
			}
		}
	}
	CustomerOrder::CustomerOrder(const CustomerOrder& src)
	{
		throw"No copy operations";
	}
	CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept
	{
		operator=(std::move(src));
	}
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept
	{
		if (this != &src)
		{
			for (size_t i = 0; i < m_cntItem; i++)
				delete m_lstItem[i];
			delete m_lstItem;
			m_name = src.m_name;
			src.m_name = "";
			m_cntItem = src.m_cntItem;
			src.m_cntItem = 0;
			m_product = src.m_product;
			src.m_product = "";
			m_lstItem = src.m_lstItem;
			src.m_lstItem = nullptr;
		}
		return *this;
	}
	bool CustomerOrder::isOrderFilled() const
	{
		size_t i;
		for (i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_isFilled == false) {
				break;
			}
		}
		return i == m_cntItem;
	}
	bool CustomerOrder::isItemFilled(const String& itemName) const
	{
		size_t i;
		bool returnValue = true;
		for (i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_itemName == itemName &&
				m_lstItem[i]->m_isFilled == false) {
				returnValue = false;
			}
		}
		return returnValue;
	}
	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_itemName == station.getItemName() &&
				m_lstItem[i]->m_isFilled == false) 
			{
				if (station.getQuantity() > 0)
				{
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					os << "    Filled " << m_name << ", " << m_product << " [";
					os << m_lstItem[i]->m_itemName << "]" << std::endl;
					break;
				}
				else
				{
					os << "    Unable to fill " << m_name << ", " << m_product;
					os << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
			}
		}
	}
	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - ";
		os << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			os << "[";
			os.width(6);
			os.fill('0');
			os << m_lstItem[i]->m_serialNumber;
			os << "] ";
			os.width(m_widthField);
			os.fill(' ');
			os.setf(std::ios::left);
			os << m_lstItem[i]->m_itemName;
			os.unsetf(std::ios::left);
			os << "   - ";
			if (m_lstItem[i]->m_isFilled == true)
			{
				os << "FILLED" << std::endl;
			}
			else
			{
				os << "TO BE FILLED" << std::endl;
			}

		}
	}
	CustomerOrder::~CustomerOrder()
	{
		for (size_t i = 0; i < m_cntItem; i++)
		{
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
	}
}