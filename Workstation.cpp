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
#include "Workstation.h"
using namespace std;
using namespace sdds;
deque<CustomerOrder> g_pending{};
deque<CustomerOrder> g_completed{};
deque<CustomerOrder> g_incomplete{};

Workstation::Workstation(const string& data) : Station{ data } {}

void Workstation::fill(ostream& os)
{
	if (!m_orders.empty())
	{
		m_orders.front().fillItem(*this, os);
	}
}

bool Workstation::attemptToMoveOrder()
{
	bool returnValue = false;
	if (m_orders.empty())
	{
		returnValue = true;
	}
	else
	{
		if (m_orders.front().isItemFilled(getItemName()) || getQuantity() == 0)
		{
			if (!m_pNextStation)
			{
				if (m_orders.front().isOrderFilled())
				{
					g_completed.emplace_back(move(m_orders.front()));
				}
				else
				{
					g_incomplete.emplace_back(move(m_orders.front()));
				}
			}
			else
			{
				(*m_pNextStation) += move(m_orders.front());
			}
			m_orders.pop_front();
			returnValue = true;
		}
	}
	return returnValue;
}

void Workstation::setNextStation(Workstation* station)
{
	m_pNextStation = station;
}

Workstation* Workstation::getNextStation() const
{
	return m_pNextStation;
}

void Workstation::display(ostream& os) const
{
	os << getItemName();
	os << " --> ";

	if (!m_pNextStation)
	{
		os << "End of Line";
	}
	else
	{
		os << m_pNextStation->getItemName();
	}

	os << endl;
}

Workstation& Workstation::operator+=(CustomerOrder&& new_Order)
{
	m_orders.emplace_back(move(new_Order));
	return *this;
}

bool Workstation::empty() const
{
	return m_orders.empty();
}
