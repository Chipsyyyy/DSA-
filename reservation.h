#ifndef RESERVATION_H
#define RESERVATION_H

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <queue>

struct Seat {
    std::string seatID;
    std::string customerName;
    Seat* next;
};

class ReservationSystem {
private:
    Seat* head;
    std::stack<std::string> cancelStack;
    std::queue<std::string> waitQueue;

public:
    ReservationSystem();
    void loadFromFile();
    void saveToFile();
    void displaySeats();
    void reserveSeat(std::string seatID, std::string name);
    void deleteReservation(std::string seatID);
    void searchSeat(std::string seatID);
    void viewAllReservations();
    void viewCancelled();
    void clearCancelled();
    void addToWaitList(std::string name);
    void serveNextInQueue();
    ~ReservationSystem();
};

#endif
