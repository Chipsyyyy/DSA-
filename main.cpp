#include "reservation.h"
using namespace std;

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
        cin.ignore();

        switch (choice) {
            case 1:
                rs.displaySeats();
                break;
            case 2:
                cout << "Enter seat ID (e.g., A1): ";
                getline(cin, seatID);
                cout << "Enter your name: ";
                getline(cin, name);
                rs.reserveSeat(seatID, name);
                break;
            case 3:
                cout << "Enter seat ID to search: ";
                getline(cin, seatID);
                rs.searchSeat(seatID);
                break;
            case 4:
                cout << "Enter seat ID to cancel: ";
                getline(cin, seatID);
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
                cout << "Invalid choice.\n";
        }

    } while (choice != 12);

    return 0;
}
