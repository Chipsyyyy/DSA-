#include "reservation.h"
#include <cctype>
#include <cstdlib>  // For atoi()
using namespace std;

// Manual loop version for Dev-C++ (no range-based for loops)
bool isValidSeatID(const string& seatID) {
    if (seatID.length() < 2 || seatID.length() > 3) return false;
    char row = toupper(seatID[0]);
    if (row != 'A' && row != 'B') return false;

    string numberPart = seatID.substr(1);
    for (int i = 0; i < numberPart.length(); i++) {
        if (!isdigit(numberPart[i])) return false;
    }
    int num = atoi(numberPart.c_str());
    return num >= 1 && num <= 5;
}

bool isValidName(const string& name) {
    if (name.empty()) return false;
    for (int i = 0; i < name.length(); i++) {
        if (!isalpha(name[i]) && name[i] != ' ') return false;
    }
    return true;
}

void showMenu() {
    cout << "\nMovie Seat Reservation System\n";
    cout << "1. Display Seat Layout\n";
    cout << "2. Reserve a Seat\n";
    cout << "3. Search a Seat\n";
    cout << "4. Delete Reservation\n";
    cout << "5. View All Reserved Seats\n";
    cout << "6. View Cancelled Reservations\n";
    cout << "7. Clear Cancelled History\n";
    cout << "8. Add to Waiting List\n";
    cout << "9. Serve Next in Waiting List\n";
    cout << "10. Save Reservations to File\n";
    cout << "11. Load Reservations from File\n";
    cout << "12. Exit\n";
    cout << "Enter choice: ";
}

int main() {
    ReservationSystem rs;
    int choice;
    string seatID, name;

    do {
        showMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter numbers only.\n";
            continue;
        }

        cin.ignore(); // Clear newline character

        switch (choice) {
            case 1:
                rs.displaySeats();
                break;

            case 2:
                cout << "Enter seat ID (e.g., A1): ";
                getline(cin, seatID);
                if (!isValidSeatID(seatID)) {
                    cout << "Invalid seat ID. Must be from A1 to B5.\n";
                    break;
                }
                cout << "Enter your name: ";
                getline(cin, name);
                if (!isValidName(name)) {
                    cout << "Invalid name. Letters and spaces only.\n";
                    break;
                }
                rs.reserveSeat(seatID, name);
                break;

            case 3:
                cout << "Enter seat ID to search: ";
                getline(cin, seatID);
                if (!isValidSeatID(seatID)) {
                    cout << "Invalid seat ID.\n";
                    break;
                }
                rs.searchSeat(seatID);
                break;

            case 4:
                cout << "Enter seat ID to cancel: ";
                getline(cin, seatID);
                if (!isValidSeatID(seatID)) {
                    cout << "Invalid seat ID.\n";
                    break;
                }
                rs.deleteReservation(seatID);
                break;

            case 5:
                rs.viewAllReservations();
                break;

            case 6:
                rs.viewCancelled();
                break;

            case 7:
                rs.clearCancelled();
                break;

            case 8:
                cout << "Enter name to add to waitlist: ";
                getline(cin, name);
                if (!isValidName(name)) {
                    cout << "Invalid name. Letters and spaces only.\n";
                    break;
                }
                rs.addToWaitList(name);
                break;

            case 9:
                rs.serveNextInQueue();
                break;

            case 10:
                rs.saveToFile();
                cout << "Reservations saved to file.\n";
                break;

            case 11:
                rs.loadFromFile();
                cout << "Reservations loaded from file.\n";
                break;

            case 12:
                cout << "Exiting system...\n";
                break;

            default:
                cout << "Invalid choice. Please select from 1 to 12.\n";
        }

    } while (choice != 12);

    return 0;
}
