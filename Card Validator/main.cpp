#include <iostream>
#include <cstring>

using namespace std;

string citire_card() {
    string card_input;
    cout << "Introduceti datele cardului:";
    getline(cin, card_input);
    return card_input;
}

bool date_corecte(string card_input) {
    int lenght = card_input.length();
    if (lenght < 16 || lenght > 19)
        return false;
    for (int i = 0; i < lenght; i++) {
        if (i == 4 || i == 9 || i == 14)
            continue;
        if (card_input[i] < '0' || card_input[i] > '9')
            return false;
    }
    return true;
}

bool identificare(string card_input) {
    int lenght = card_input.length();
    switch (lenght - 3) {
        case 16:
            if (card_input[0] == '5' && strchr(to_string(card_input[0]).c_str(), '12345')) {
                cout << "MasterCard\n";
                return true;
            }
            if (card_input[0] == '4') {
                cout << "Visa\n";
                return true;
            }
            if (strncmp(card_input.c_str(), "6011", 4) == 0) {
                cout << "Discover\n";
                return true;
            }
            if (card_input[0] == '3') {
                cout << "JCB\n";
                return true;
            }
            break;
        case 15:
            if (strncmp(card_input.c_str(), "34", 2) == 0 || strncmp(card_input.c_str(), "37", 2) == 0) {
                cout << "American Express\n";
                return true;
            }
            if (strncmp(card_input.c_str(), "2123", 4) == 0 || strncmp(card_input.c_str(), "1800", 4) == 0) {
                cout << "JCB\n";
                return true;
            }
            break;
        case 14:
            if (strncmp(card_input.c_str(), "36", 2) == 0 || strncmp(card_input.c_str(), "38", 4) == 0 ||
                (strncmp(card_input.c_str(), "30", 2) == 0) && strchr(to_string(card_input[2]).c_str(), '12345')) {
                cout << "Diners Club and Carte Blanche\n";
                return true;
            }
            break;
        case 13:
            if (card_input[0] == '4') {
                cout << "Visa\n";
                return true;
            }
            break;
        default:
            return false;
    }
}

int *conversie(string card_input, int &length) {
    int size_input = card_input.length();
    int *card = new int[size_input - 3];
    for (int i = 0; i < size_input; i++)
        if (i != 4 && i != 9 && i != 14)
            card[length++] = card_input[i] - '0';
    return card;
}

bool integritate(int *card_id, int lenght) {
    int sum = 0, aux;
    for (int i = 0; i < lenght; i++) {
        if (i % 2 == 0) {
            aux = card_id[i] * 2;
            if (aux >= 10)
                aux = aux % 10 + aux / 10;
            sum += aux;
        } else sum += card_id[i];
    }
    if (sum % 10 == 0)
        return true;
    else
        return false;
}

int main() {
    string card_input;
    for (;;) {
        card_input = citire_card();
        if (date_corecte(card_input) && identificare(card_input))
            break;
        cout << "Format gresit!\n";
    }
    int lenght = 0;
    int *card_id = conversie(card_input, lenght);
    if (integritate(card_id, lenght))
        cout << "Cardul este valid!";
    else
        cout << "Cardul nu este valid!";
    return 0;
}
