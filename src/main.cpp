#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
/*
Onari Romain 8/4/26


*/
using namespace std;
 std::random_device rd;
// 2. Initialize the standard 32-bit Mersenne Twister engine with the seed
std::mt19937 gen(rd());

struct User{
    int id;
    string name;
    string email;
    string password;


};

class 
UserManager{
public:

    User user;

    UserManager()
       : user({0, "", "", ""}){

       }      
    

    UserManager(const User& user)
        : user(user) {
    }
    

    void updateName(string name){
        user.name = name;
    }

    void updateEmail(string email){
        user.email = email;
    }

    void updatePassword(string password){
        user.password = password;
    }

    void updateId(int id){
        user.id = id;
    }

  
    void toString(){
        cout << "ID: " << user.id << std::endl;
        cout << "Name: " << user.name << std::endl;
        cout << "Email: " << user.email << std::endl;
        cout << "Password: " << user.password << std::endl;
    }

    int GenerateId(){
       
        // 3. Define the desired distribution range [inclusive, inclusive]
        std::uniform_int_distribution<int> distrib(1, 100); 

        return distrib(gen);
    }
    User createUser(string name, string email, string password){
        User user;
        user.id = GenerateId();
        user.name = name;
        user.email = email;
        user.password = password;
        return user;
    }
    void UpdateCurrentUser(User& updatedUser){
        user = updatedUser;

    }
};

void display(UserManager& userManager){
    string name, email, password;
    
    cout << "Enter your name: ";
    cin >> name;
    cout << "Enter your email: ";
    cin >> email;
    cout << "Enter your password: ";
    cin >> password;
    cout << "creating user....";
    
    User user = userManager.createUser(name, email, password);
    userManager.UpdateCurrentUser(user);
}
int main(){


   
    UserManager userManager;
    display(userManager);
    string confirmation;

    cout << "Is this information correct? (y/n): \n";
    cin >> confirmation;
    if(confirmation == "y"){
       cout << "User information confirmed." << std::endl;
    }else{
        display(userManager);
    }
    return 0;
   


}
