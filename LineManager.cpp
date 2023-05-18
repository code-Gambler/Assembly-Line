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
#include "LineManager.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"
#include<stdexcept>

using namespace std;
namespace sdds {

	LineManager::LineManager(const string& file, const vector<Workstation*>& stations) {
		Utilities util;
		ifstream srcFile(file);
		string temp;
		if (!srcFile.is_open()) {
			throw invalid_argument("Unable to open file.");
		}
		while (!srcFile.eof())
		{
			getline(srcFile, temp);
			size_t nextPos = 0;
			bool moreToken = true;
			string currentStation, nextStation;
			currentStation = util.extractToken(temp, nextPos, moreToken);

			if (moreToken) {
				nextStation = util.extractToken(temp, nextPos, moreToken);
			}

			Workstation* currentWorkstation{};
			Workstation* nextWorkstation{};
			for_each(stations.begin(), stations.end(), [&currentWorkstation, &nextWorkstation, currentStation, nextStation](Workstation* workstation) {
				if (workstation->getItemName() == currentStation) {
					currentWorkstation = workstation;
				}
				else if (workstation->getItemName() == nextStation) {
					nextWorkstation = workstation;
				}
				});

			if (!m_active_Line.size()) {
				m_first_Station = currentWorkstation;
			}

			currentWorkstation->setNextStation(nextWorkstation);
			m_active_Line.push_back(currentWorkstation);
		}
		srcFile.close();
	}

	void LineManager::reorderStations() {
		vector<Workstation*> reorderedStations;
		Workstation* endOfStation{};
		unsigned int counter{};
		while (counter < m_active_Line.size()) {
			for (unsigned int i = 0; i < m_active_Line.size(); i++) {
				if (m_active_Line[i]->getNextStation() == endOfStation) {
					counter++;
					reorderedStations.push_back(m_active_Line[i]);
					endOfStation = m_active_Line[i];
					break;
				}
			}
		}
		reverse(reorderedStations.begin(), reorderedStations.end());
		m_first_Station = reorderedStations[0];
		m_active_Line = reorderedStations;
	}

	bool LineManager::run(ostream& os) {
		static int counter = 0;
		bool returnValue = true;
		counter++;
		os << "Line Manager Iteration: " << counter << endl;

		if (!g_pending.empty()) {
			(*m_first_Station) += move(g_pending.front());
			g_pending.pop_front();
		}

		for (unsigned int i = 0; i < m_active_Line.size(); i++) {
			m_active_Line[i]->fill(os);
		}

		for (unsigned int i = 0; i < m_active_Line.size(); i++) {
			m_active_Line[i]->attemptToMoveOrder();
		}

		for (unsigned int i = 0; i < m_active_Line.size(); i++) {
			if (!m_active_Line[i]->empty()) {
				returnValue = false;
				break;
			}
		}

		return returnValue;
	}

	void LineManager::display(ostream& os) const {
		for (unsigned int i = 0; i < m_active_Line.size(); i++) {
			m_active_Line[i]->display(os);
		}
	}
}