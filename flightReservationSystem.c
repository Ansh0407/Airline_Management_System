#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FLIGHTS 10
#define MAX_RESERVATIONS 50

typedef struct
{
    int flightNumber;
    char source[50];
    char destination[50];
    char departTime[50];
    char arriveTime[50];
    int availableSeats;
    float ticketPrice;
    char flightStatus[50];
} Flight;

typedef struct
{
    char passengerName[50];
    int flightNumber;
    int seatNumber;
} Reservation;

Flight flights[MAX_FLIGHTS];
Reservation reservations[MAX_RESERVATIONS];
int numFlights = 0;
int numReservations = 0;

void displayFlights()
{
    printf("Available Flights for today:\n");
    for (int i = 0; i < numFlights; i++)
    {
        printf("\tFlight #%d from %s to %s | Departing Time: %s | Arrival Time: %s | Available Seats: %d | Ticket Price: Rs. %.2f | Flight Status: %s\n", flights[i].flightNumber, flights[i].source, flights[i].destination, flights[i].departTime, flights[i].arriveTime, flights[i].availableSeats, flights[i].ticketPrice, flights[i].flightStatus);
    }
}

void makeReservation()
{
    char name[50];
    int flightNum;
    printf("Enter your name: ");
    fflush(stdin);
    gets(name);
    int flightIndex = -1;

    printf("Enter the flight number you want to book: ");
    scanf(" %d", &flightNum);

    for (int i = 0; i < numFlights; i++)
    {
        if (flights[i].flightNumber == flightNum)
        {
            flightIndex = i;
            break;
        }
    }

    if (flightIndex == -1)
    {
        printf("Invalid flight number.\n");
        return;
    }

    if (flights[flightIndex].availableSeats > 0)
    {
        reservations[numReservations].flightNumber = flightNum;
        strcpy(reservations[numReservations].passengerName, name);
        reservations[numReservations].seatNumber = flights[flightIndex].availableSeats;
        flights[flightIndex].availableSeats--;
        printf("\n\n\tReservation successful!\n======================================================\nPassenger Name: %s\nFlight Number: %d\nSeat Number: %d\n\nThank you for booking with us, Have a great flight!\n", reservations[numReservations].passengerName, reservations[numReservations].flightNumber, reservations[numReservations].seatNumber);
        numReservations++;
    }
    else
    {
        printf("No available seats for this flight.\n");
    }
}

void addFlight()
{
    int flightNo, seats;
    float price;
    char sou[50], desti[50], depTime[50], arrTime[50], status[50];

    printf("Flight Number: ");
    scanf("%d", &flightNo);
    flights[numFlights].flightNumber = flightNo;

    printf("Flight Source: ");
    fflush(stdin);
    gets(sou);
    strcpy(flights[numFlights].source, strupr(sou));

    printf("Flight Destination: ");
    fflush(stdin);
    gets(desti);
    strcpy(flights[numFlights].destination, strupr(desti));

    printf("Flight Departure Time: ");
    fflush(stdin);
    gets(depTime);
    strcpy(flights[numFlights].departTime, depTime);

    printf("Flight Arrival Time: ");
    fflush(stdin);
    gets(arrTime);
    strcpy(flights[numFlights].arriveTime, arrTime);

    printf("Total Seats: ");
    scanf("%d", &seats);
    flights[numFlights].availableSeats = seats;

    printf("Ticket Price: ");
    scanf("%f", &price);
    flights[numFlights].ticketPrice = price;

    printf("Flight Status: ");
    fflush(stdin);
    gets(status);
    strcpy(flights[numFlights].flightStatus, status);

    printf("\n======================================================\n\tFlight Added!\n");
    printf("Flight #%d from %s to %s | Departing Time: %s | Arrival Time: %s | Available Seats: %d | Ticket Price: Rs. %.2f | Flight Status: %s\n", flights[numFlights].flightNumber, flights[numFlights].source, flights[numFlights].destination, flights[numFlights].departTime, flights[numFlights].arriveTime, flights[numFlights].availableSeats, flights[numFlights].ticketPrice, flights[numFlights].flightStatus);
    numFlights++;
}

void changeStatus()
{
    int flightIndex = -1, flightNum;
    printf("Enter the flight number you want to change status of: ");
    scanf(" %d", &flightNum);
    for (int i = 0; i < numFlights; i++)
    {
        if (flights[i].flightNumber == flightNum)
        {
            flightIndex = i;
            break;
        }
    }
    if (flightIndex == -1)
    {
        printf("Invalid flight number.\n");
        return;
    }
    char newStatus[50];
    printf("Flight New Status: ");
    fflush(stdin);
    gets(newStatus);
    strcpy(flights[flightIndex].flightStatus, newStatus);
    printf("\n======================================================\n\tFlight Status Changed Successfully!\n");
}

void displayFlightPassesgers()
{
    int flightIndex = -1, flightNum;
    printf("Enter the flight number you want to display details of: ");
    scanf(" %d", &flightNum);
    for (int i = 0; i < numFlights; i++)
    {
        if (flights[i].flightNumber == flightNum)
        {
            flightIndex = i;
            break;
        }
    }
    if (flightIndex == -1)
    {
        printf("Invalid flight number.\n");
        return;
    }
    printf("\n\tFlight #%d from %s to %s | Departing Time: %s | Arrival Time: %s | Available Seats: %d | Ticket Price: Rs. %.2f | Flight Status: %s\n\n\tPassengers Onboarding:\n", flights[flightIndex].flightNumber, flights[flightIndex].source, flights[flightIndex].destination, flights[flightIndex].departTime, flights[flightIndex].arriveTime, flights[flightIndex].availableSeats, flights[flightIndex].ticketPrice, flights[flightIndex].flightStatus);
    for (int i = 0; i < numReservations; i++)
    {
        if (reservations[i].flightNumber == flightNum)
        {
            printf("\t\t %s | #%d | %d\n", reservations[i].passengerName, reservations[i].flightNumber, reservations[i].seatNumber);
        }
    }
}
void removePassenger()
{
    int flightIndex = -1, flightNum;
    printf("Enter the flight number you want to remove a passenger from: ");
    scanf("%d", &flightNum);

    for (int i = 0; i < numFlights; i++)
    {
        if (flights[i].flightNumber == flightNum)
        {
            flightIndex = i;
            break;
        }
    }

    if (flightIndex == -1)
    {
        printf("Invalid flight number.\n");
        return;
    }

    printf("Enter the seat number of the passenger to be removed: ");
    int seatToRemove;
    scanf("%d", &seatToRemove);

    int reservationIndex = -1;
    for (int i = 0; i < numReservations; i++)
    {
        if (reservations[i].flightNumber == flightNum && reservations[i].seatNumber == seatToRemove)
        {
            reservationIndex = i;
            break;
        }
    }

    if (reservationIndex == -1)
    {
        printf("No reservation found for the given seat number.\n");
        return;
    }

    for (int i = reservationIndex; i < numReservations - 1; i++)
    {
        reservations[i] = reservations[i + 1];
    }

    flights[flightIndex].availableSeats++;

    printf("\nPassenger removed from flight #%d, seat #%d.\n", flightNum, seatToRemove);
    numReservations--;
}

void adminDuty()
{
    char password[50];
    printf("Enter Admin Password: ");
    fflush(stdin);
    gets(password);

    if (strcmp(password, "Adminlogin123") == 0)
    {

        int choice;
        do
        {
            printf("\n======================================================\nAdmin Menu:\n");
            printf("1. Add New Flight\n");
            printf("2. Change Current Flight Status\n");
            printf("3. Display Flight with their Passengers Details\n");
            printf("4.Remove Passenger\n");
            printf("0. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            printf("\n======================================================\n\n");

            switch (choice)
            {
            case 1:
                addFlight();
                break;
            case 2:
                changeStatus();
                break;
            case 3:
                displayFlightPassesgers();
                break;
            case 4:
                removePassenger();
                break;
            case 0:
                printf("Thank you...\n");
                break;
            default:
                printf("Invalid choice, try again.\n");
            }
        } while (choice != 0);
    }
    else
    {
        printf("\nInvalid Admin Password! Exiting...\n");
        return;
    }
}

void main()
{
    flights[numFlights].flightNumber = 101;
    strcpy(flights[numFlights].source, "BANGALORE");
    strcpy(flights[numFlights].destination, "NEW DELHI");
    strcpy(flights[numFlights].departTime, "09:25");
    strcpy(flights[numFlights].arriveTime, "11:45");
    flights[numFlights].availableSeats = 10;
    flights[numFlights].ticketPrice = 3500.0;
    strcpy(flights[numFlights].flightStatus, "On Time");
    numFlights++;

    flights[numFlights].flightNumber = 102;
    strcpy(flights[numFlights].source, "BANGALORE");
    strcpy(flights[numFlights].destination, "HYDERABAD");
    strcpy(flights[numFlights].departTime, "14:30");
    strcpy(flights[numFlights].arriveTime, "16:45");
    flights[numFlights].availableSeats = 15;
    flights[numFlights].ticketPrice = 3099.0;
    strcpy(flights[numFlights].flightStatus, "On Time");
    numFlights++;

    int choice;
    do
    {
        printf("\n======================================================\nMenu:\n");
        printf("1. Display Available Flights\n");
        printf("2. Make Reservation\n");
        printf("3. Login as Admin\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("======================================================\n\n");

        switch (choice)
        {
        case 1:
            displayFlights();
            break;
        case 2:
            makeReservation();
            break;
        case 3:
            adminDuty();
            break;
        case 0:
            printf("Thank you!...\n");
            break;
        default:
            printf("Invalid choice, try again.\n");
        }
    } while (choice != 0);
}