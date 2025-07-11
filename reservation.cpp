#include "reservation.h"
using namespace std;

ReservationSystem::ReservationSystem() {
    head = NULL;
}

void ReservationSystem::loadFromFile() {
    ifstream file("reservations.txt");
    string seatID, customerName;
    while (file >> seatID >> customerName) {
        Seat* newSeat = new Seat;
        newSeat->seatID = seatID;
        newSeat->customerName = customerName;
        newSeat->next = head;
        head = newSeat;
    }
    file.close();
}

void ReservationSystem::saveToFile() {
    ofstream file("reservations.txt");
    Seat* current = head;
    while (current) {
        file << current->seatID << " " << current->customerName << endl;
        current = current->next;
    }
    file.close();
}

void ReservationSystem::displaySeats() {
    cout << "\n--- Seat Layout ---\n";
    string rows[] = {"A", "B"};
    for (int r = 0; r < 2; ++r) {
        for (int i = 1; i <= 5; ++i) {
            char numStr[3];
            sprintf(numStr, "%d", i);
            string seatID = rows[r] + string(numStr);

            bool taken = false;
            Seat* current = head;
            while (current) {
                if (current->seatID == seatID) {
                    taken = true;
                    break;
                }
                current = current->next;
            }

            cout << seatID << "[" << (taken ? "X" : " ") << "] ";
        }
        cout << endl;
    }
}

void ReservationSystem::reserveSeat(string seatID, string name) {
    Seat* current = head;
    while (current) {
        if (current->seatID == seatID) {
            cout << "Seat already reserved! Adding to waitlist...\n";
            addToWaitList(name);
            return;
        }
        current = current->next;
    }
    Seat* newSeat = new Seat;
    newSeat->seatID = seatID;
    newSeat->customerName = name;
    newSeat->next = head;
    head = newSeat;
    cout << "Reservation successful for " << seatID << "!\n";
}

void ReservationSystem::deleteReservation(string seatID) {
    Seat* current = head;
    Seat* prev = NULL;
    while (current) {
        if (current->seatID == seatID) {
            if (prev) prev->next = current->next;
            else head = current->next;
            cancelStack.push(current->seatID + " (" + current->customerName + ")");
            delete current;
            cout << "Reservation for " << seatID << " canceled.\n";
            return;
        }
        prev = current;
        current = current->next;
    }
    cout << "Seat not found.\n";
}

void ReservationSystem::searchSeat(string seatID) {
    Seat* current = head;
    while (current) {
        if (current->seatID == seatID) {
            cout << "Seat " << seatID << " is reserved by " << current->customerName << ".\n";
            return;
        }
        current = current->next;
    }
    cout << "Seat " << seatID << " is available.\n";
}

void ReservationSystem::viewAllReservations() {
    if (!head) {
        cout << "No reservations yet.\n";
        return;
    }
    Seat* current = head;
    cout << "\nReserved Seats:\n";
    while (current) {
        cout << current->seatID << " - " << current->customerName << endl;
        current = current->next;
    }
}

void ReservationSystem::viewCancelled() {
    if (cancelStack.empty()) {
        cout << "No cancelled reservations.\n";
        return;
    }
    cout << "Cancelled Reservations:\n";
    stack<string> temp = cancelStack;
    while (!temp.empty()) {
        cout << temp.top() << endl;
        temp.pop();
    }
}

void ReservationSystem::clearCancelled() {
    while (!cancelStack.empty()) {
        cancelStack.pop();
    }
    cout << "Cancelled reservation history cleared.\n";
}

void ReservationSystem::addToWaitList(string name) {
    waitQueue.push(name);
    cout << name << " added to waiting list.\n";
}

void ReservationSystem::serveNextInQueue() {
    if (waitQueue.empty()) {
        cout << "No one in waiting list.\n";
        return;
    }
    string next = waitQueue.front();
    waitQueue.pop();
    cout << "Serving next in queue: " << next << endl;
}

ReservationSystem::~ReservationSystem() {
    Seat* current = head;
    while (current) {
        Seat* temp = current;
        current = current->next;
        delete temp;
    }
}
