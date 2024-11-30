#include <iostream>
#include <fstream>
using namespace std;

struct MobilePhone {
    double weight;
    bool is_broken;
    double price;
};

int main() {
    int phone_count;
    cin >> phone_count;
    if (phone_count == 0) {
        cout << "{\n";
        cout << "\t\"MobilePhones\": []\n";
        cout << "}\n";
        return 0;
    } else if (phone_count < 0) {
        cout << "Вводить отрицательные числа запрещается. Negative number are not allowed.\n"; 
        return 0;
    }
    MobilePhone * phone_arr = new MobilePhone[phone_count];
    for (int i = 0; i < phone_count; ++i) {
        cin >> phone_arr[i].weight;
        cin >> phone_arr[i].is_broken;
        cin >> phone_arr[i].price;
    }
    cout << "{\n";
    cout << "\t\"MobilePhones\": [\n";
    for (int i = 0; i < phone_count; ++i){
        cout << "\t\t{\n";
        cout << "\t\t\t\"id\": " << i << ",\n";
        cout << "\t\t\t\"weight\": " << phone_arr[i].weight << ",\n";
        cout << "\t\t\t\"is_broken\": " << (phone_arr[i].is_broken == 1 ? "true" : "false") << ",\n";
        cout << "\t\t\t\"price\": " << phone_arr[i].price << "\n";
        if (i != phone_count - 1) {
            cout << "\t\t},\n";
        } else {
            cout << "\t\t}\n";
        }
    }
    cout << "\t]\n";
    cout << "}\n";
    return 0;
}