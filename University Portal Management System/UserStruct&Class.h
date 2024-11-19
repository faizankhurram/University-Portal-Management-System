#include <iostream>
#include <vector>
#include <fstream>
#include <unistd.h>
using namespace std;

struct User{
    string name, username, password, email, technology, semester;
    int year;
    bool registered;
    vector<vector<string>> courses;
    User* next;
    User* prev;
    
    User() : year(0), semester("NA"), registered(false), next(NULL), prev(NULL) {}
    User(string Name, string Username, string Password, string Email, string Technology){
        this -> name = Name; this -> username = Username; this -> password = Password; this -> email = Email; this -> technology = Technology;
        year = 0;
        semester = "NA";
        registered = false;
        next = NULL; prev = NULL;
    }
};

void writeUserToFile(User* user, const string& filename);

vector<User*> loadUsersFromFile(const string& filename);

void removeUserFromFile(User* user, const string& filename);

class CircularDoublyList{
private:
    User* head;
public:
    CircularDoublyList() : head(NULL) {}
    
    void addUser(void){
        string name, username, password, email, technology;
        int year = 0, semester = 0;
        
        cout << "\nEnter your full name: ";
        getline(cin >> ws, name);
        cout << "\nEnter your username for portal: ";
        getline(cin >> ws, username);
        User* temp = searchUser(username);
        if(temp){
            cout << "\nThe user with this username already exists!" << endl; sleep(2.5);
        }
        else{
            cout << "\nEnter your password: ";
            getline(cin >> ws, password);
            cout << "\nEnter your current active Email address: ";
            getline(cin >> ws, email);
            cout << "\nEnter the name of your department / technology: ";
            getline(cin >> ws, technology);
            User* newUser = new User(name, username, password, email, technology);
            
            writeUserToFile(newUser, "users.bin");
            
            if(head == NULL){
                head = newUser; head -> next = head; head -> prev = head;
            }
            else{
                User* curr = head;
                while(curr -> next != head){
                    curr = curr -> next;
                }
                curr -> next = newUser; newUser -> prev = curr; newUser -> next = head; head -> prev = newUser;
            }
        }
    }
    
    //overloading the above function
    void addUser(User* user){
        if(head == NULL){
            head = user; head -> next = head; head -> prev = head;
        }
        else{
            User* curr = head;
            while(curr -> next != head){
                curr = curr -> next;
            }
            curr -> next = user; user -> prev = curr; user -> next = head; head -> prev = user;
        }
    }
    
    User* searchUser(string tag){
        if(!head){
            return NULL;
        }
        User* curr = head;
        while(true){
            if(curr -> name == tag || curr -> username == tag){
                return curr;    //user with the given tag is found
            }
            if(curr -> next == head){
                break;
            }
            curr = curr -> next;
        }
        return NULL;    //user not found
    }
    
    void displayUser(User* user){
        if(user){
            cout << "\nName: " << user -> name << endl;
            cout << "\nPortal ID: " << user -> username << endl;
            cout << "\nTechnology: " << user -> technology << endl;
            cout << "\nSaved Email: " << user -> email << endl;
            (user -> year == 0) ? cout << "\nYear: Full registration incomplete!" << endl : cout << "\nYear: " << user -> year << endl;
            (user -> semester.length() == 0) ? cout << "\nSemester: Full registration incomplete!" << endl : cout << "\nSemester: " << user -> semester << endl;
        }
    }
    
    void searchUsersByTechnology(string tech){
        User* curr = head;
        while(true){
            if(curr -> technology == tech){
                this -> displayUser(curr);
            }
            if(curr -> next == head){
                break;
            }
            curr = curr -> next;
        }
    }

    void clear(void){
        if(!head){
            return;
        }
        User* curr = head;
        do{
            User* nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
        while (curr != head);
        head = NULL;
    }
};

User* loginUser(CircularDoublyList &users);

void signupUser(CircularDoublyList &users);
