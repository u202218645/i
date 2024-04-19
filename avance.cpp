#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // Para system("cls") en Windows y system("clear") en Unix

using namespace std;

// Definición de las clases y estructuras

// Estructura de un nodo para la lista enlazada simple
template<typename T>
struct ListNode {
    T data;
    ListNode* next;
    ListNode(T data) : data(data), next(nullptr) {}
};

// Lista enlazada simple
template<typename T>
class LinkedList {
private:
    ListNode<T>* head;
    int size;

public:
    LinkedList() : head(nullptr), size(0) {}

    ~LinkedList() {
        ListNode<T>* current = head;
        while (current != nullptr) {
            ListNode<T>* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }

    void push_back(T data) {
        ListNode<T>* newNode = new ListNode<T>(data);
        if (head == nullptr) {
            head = newNode;
        } else {
            ListNode<T>* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
    }

    int getSize() const {
        return size;
    }
};

// Estructura de un nodo para la lista enlazada doble
template<typename T>
struct DoublyListNode {
    T data;
    DoublyListNode* prev;
    DoublyListNode* next;
    DoublyListNode(T data) : data(data), prev(nullptr), next(nullptr) {}
};

// Lista enlazada doble
template<typename T>
class DoublyLinkedList {
private:
    DoublyListNode<T>* head;
    DoublyListNode<T>* tail;
    int size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoublyLinkedList() {
        DoublyListNode<T>* current = head;
        while (current != nullptr) {
            DoublyListNode<T>* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
    }

    void push_back(T data) {
        DoublyListNode<T>* newNode = new DoublyListNode<T>(data);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    int getSize() const {
        return size;
    }
};

// Pila (implementada utilizando un vector)
template<typename T>
class Stack {
private:
    vector<T> data;

public:
    Stack() {}

    void push(T element) {
        data.push_back(element);
    }

    void pop() {
        if (!data.empty()) {
            data.pop_back();
        }
    }

    T top() const {
        if (!data.empty()) {
            return data.back();
        }
        throw logic_error("Stack is empty");
    }

    bool empty() const {
        return data.empty();
    }

    int size() const {
        return data.size();
    }
};

// Funciones lambda
void showInvalidOptionMessage() {
    cout << "Opción inválida. Por favor, ingrese un número válido.\n";
    cout << "Presione Enter para continuar...";
    cin.ignore();
    cin.get();
}

auto clearScreen = []() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
};

auto confirmReservation = [](const Hotel& hotel) {
    if (hotel.getHabitacionesDisponibles() > 0) {
        cout << "Se ha realizado la reserva de una habitación en " << hotel.getNombre() << " correctamente.\n";
    } else {
        cout << "Lo siento, no hay habitaciones disponibles en este momento.\n";
    }
};

auto confirmCancellation = [](const Hotel& hotel) {
    cout << "Se ha cancelado la reserva de una habitación en " << hotel.getNombre() << " correctamente.\n";
};

auto showAvailability = [](const Hotel& hotel) {
    cout << "Disponibilidad de habitaciones en " << hotel.getNombre() << ":\n";
    cout << "---------------------------------------------\n";
    cout << "Habitaciones disponibles: " << hotel.getHabitacionesDisponibles() << endl;
    cout << "---------------------------------------------\n";
    cout << "Presione Enter para volver al menú principal...";
    cin.ignore();
    cin.get();
};

auto makeReservation = [](Hotel& hotel) {
    confirmReservation(hotel);
    hotel.reservarHabitacion();
};

auto cancelReservation = [](Hotel& hotel) {
    confirmCancellation(hotel);
    hotel.liberarHabitacion();
};

int main() {
    Hotel hotel("Hotel Ejemplo", 10); // Crear un hotel con 10 habitaciones

    bool exit = false;
    while (!exit) {
        clearScreen();
        cout << "Bienvenido al Sistema de Gestión de Reservas de Hotel\n";
        cout << "----------------------------------------------------\n";
        cout << "1. Ver disponibilidad de habitaciones\n";
        cout << "2. Hacer una reserva\n";
        cout << "3. Cancelar una reserva\n";
        cout << "4. Salir\n";
        cout << "----------------------------------------------------\n";
        cout << "Ingrese el número de la opción deseada: ";

        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                showAvailability(hotel);
                break;
            case 2:
                makeReservation(hotel);
                break;
            case 3:
                cancelReservation(hotel);
                break;
            case 4:
                exit = true;
                clearScreen();
                cout << "Gracias por utilizar el Sistema de Gestión de Reservas de Hotel. ¡Hasta luego!\n";
                break;
            default:
                showInvalidOptionMessage();
                break;
        }
    }

    return 0;
}
