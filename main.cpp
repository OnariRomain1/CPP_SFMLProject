#include <iostream>

using namespace std;
struct Person{
    int id;
    string name;
    string email;
};

class 
PersonManager{
public:
    void displayPerson(const Person& person){
        cout << "ID: " << person.id << std::endl;
        cout << "Name: " << person.name << std::endl;
        cout << "Email: " << person.email << std::endl;
    }
};

int main(){
    Person person1;
    person1.id = 1;
    person1.name = "John Doe";
    person1.email = "john.doe@example.com";

    PersonManager manager;
    manager.displayPerson(person1);
    cout << "Press Enter to exit..." << std::endl;
    string input;
    getline(std::cin, input);
    return 0;
}