#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include "UserStruct&Class.h"
using namespace std;

void writeUserToFile(User* user, const string& filename) {
    ofstream file(filename, ios::binary | ios::app);
    if (file) {
        // Existing code for writing other fields
        size_t nameSize = user->name.size();
        file.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
        file.write(user->name.c_str(), nameSize);

        size_t usernameSize = user->username.size();
        file.write(reinterpret_cast<const char*>(&usernameSize), sizeof(usernameSize));
        file.write(user->username.c_str(), usernameSize);

        size_t passwordSize = user->password.size();
        file.write(reinterpret_cast<const char*>(&passwordSize), sizeof(passwordSize));
        file.write(user->password.c_str(), passwordSize);

        size_t emailSize = user->email.size();
        file.write(reinterpret_cast<const char*>(&emailSize), sizeof(emailSize));
        file.write(user->email.c_str(), emailSize);

        size_t techSize = user->technology.size();
        file.write(reinterpret_cast<const char*>(&techSize), sizeof(techSize));
        file.write(user->technology.c_str(), techSize);

        size_t semesterSize = user->semester.size();
        file.write(reinterpret_cast<const char*>(&semesterSize), sizeof(semesterSize));
        file.write(user->semester.c_str(), semesterSize);

        file.write(reinterpret_cast<const char*>(&user->year), sizeof(user->year));
        file.write(reinterpret_cast<const char*>(&user->registered), sizeof(user->registered));

        // Writing the courses vector
        size_t courseCount = user->courses.size();
        file.write(reinterpret_cast<const char*>(&courseCount), sizeof(courseCount));

        for (const auto& course : user->courses) {
            size_t courseSize = course.size();
            file.write(reinterpret_cast<const char*>(&courseSize), sizeof(courseSize));

            for (const auto& field : course) {
                size_t fieldSize = field.size();
                file.write(reinterpret_cast<const char*>(&fieldSize), sizeof(fieldSize));
                file.write(field.c_str(), fieldSize);
            }
        }
    } else {
        cerr << "Error opening file for writing." << endl;
    }
}

vector<User*> loadUsersFromFile(const string& filename) {
    ifstream file(filename, ios::binary);
    vector<User*> users;

    while (file) {
        User* user = new User();

        // Existing code for reading other fields
        size_t nameSize;
        file.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
        if (file.eof()) break;
        user->name.resize(nameSize);
        file.read(&user->name[0], nameSize);

        size_t usernameSize;
        file.read(reinterpret_cast<char*>(&usernameSize), sizeof(usernameSize));
        user->username.resize(usernameSize);
        file.read(&user->username[0], usernameSize);

        size_t passwordSize;
        file.read(reinterpret_cast<char*>(&passwordSize), sizeof(passwordSize));
        user->password.resize(passwordSize);
        file.read(&user->password[0], passwordSize);

        size_t emailSize;
        file.read(reinterpret_cast<char*>(&emailSize), sizeof(emailSize));
        user->email.resize(emailSize);
        file.read(&user->email[0], emailSize);

        size_t techSize;
        file.read(reinterpret_cast<char*>(&techSize), sizeof(techSize));
        user->technology.resize(techSize);
        file.read(&user->technology[0], techSize);

        size_t semesterSize;
        file.read(reinterpret_cast<char*>(&semesterSize), sizeof(semesterSize));
        user->semester.resize(semesterSize);
        file.read(&user->semester[0], semesterSize);

        file.read(reinterpret_cast<char*>(&user->year), sizeof(user->year));
        file.read(reinterpret_cast<char*>(&user->registered), sizeof(user->registered));

        // Reading the courses vector
        size_t courseCount;
        file.read(reinterpret_cast<char*>(&courseCount), sizeof(courseCount));

        user->courses.resize(courseCount);
        for (auto& course : user->courses) {
            size_t courseSize;
            file.read(reinterpret_cast<char*>(&courseSize), sizeof(courseSize));

            course.resize(courseSize);
            for (auto& field : course) {
                size_t fieldSize;
                file.read(reinterpret_cast<char*>(&fieldSize), sizeof(fieldSize));
                field.resize(fieldSize);
                file.read(&field[0], fieldSize);
            }
        }

        users.push_back(user);
    }

    return users;
}

void removeUserFromFile(User* user, const string& filename) {
    ifstream inputFile(filename, ios::binary);
    ofstream tempFile("temp.bin", ios::binary);

    if (!inputFile || !tempFile) {
        cerr << "Error opening file for removal." << endl;
        return;
    }

    inputFile.seekg(0, ios::beg);

    while (inputFile) {
        User tempUser;

        // Existing code to read other fields
        size_t nameSize;
        inputFile.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
        if (inputFile.eof()) break;
        tempUser.name.resize(nameSize);
        inputFile.read(&tempUser.name[0], nameSize);

        size_t usernameSize;
        inputFile.read(reinterpret_cast<char*>(&usernameSize), sizeof(usernameSize));
        tempUser.username.resize(usernameSize);
        inputFile.read(&tempUser.username[0], usernameSize);

        size_t passwordSize;
        inputFile.read(reinterpret_cast<char*>(&passwordSize), sizeof(passwordSize));
        tempUser.password.resize(passwordSize);
        inputFile.read(&tempUser.password[0], passwordSize);

        size_t emailSize;
        inputFile.read(reinterpret_cast<char*>(&emailSize), sizeof(emailSize));
        tempUser.email.resize(emailSize);
        inputFile.read(&tempUser.email[0], emailSize);

        size_t techSize;
        inputFile.read(reinterpret_cast<char*>(&techSize), sizeof(techSize));
        tempUser.technology.resize(techSize);
        inputFile.read(&tempUser.technology[0], techSize);

        size_t semesterSize;
        inputFile.read(reinterpret_cast<char*>(&semesterSize), sizeof(semesterSize));
        tempUser.semester.resize(semesterSize);
        inputFile.read(&tempUser.semester[0], semesterSize);

        inputFile.read(reinterpret_cast<char*>(&tempUser.year), sizeof(tempUser.year));
        inputFile.read(reinterpret_cast<char*>(&tempUser.registered), sizeof(tempUser.registered));

        // Read courses vector
        size_t courseCount;
        inputFile.read(reinterpret_cast<char*>(&courseCount), sizeof(courseCount));
        tempUser.courses.resize(courseCount);

        for (auto& course : tempUser.courses) {
            size_t courseSize;
            inputFile.read(reinterpret_cast<char*>(&courseSize), sizeof(courseSize));

            course.resize(courseSize);
            for (auto& field : course) {
                size_t fieldSize;
                inputFile.read(reinterpret_cast<char*>(&fieldSize), sizeof(fieldSize));
                field.resize(fieldSize);
                inputFile.read(&field[0], fieldSize);
            }
        }

        // Write to temp file if not the user to delete
        if (tempUser.username != user->username) {
            size_t nameSize = tempUser.name.size();
            tempFile.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
            tempFile.write(tempUser.name.c_str(), nameSize);

            size_t usernameSize = tempUser.username.size();
            tempFile.write(reinterpret_cast<const char*>(&usernameSize), sizeof(usernameSize));
            tempFile.write(tempUser.username.c_str(), usernameSize);

            size_t passwordSize = tempUser.password.size();
            tempFile.write(reinterpret_cast<const char*>(&passwordSize), sizeof(passwordSize));
            tempFile.write(tempUser.password.c_str(), passwordSize);

            size_t emailSize = tempUser.email.size();
            tempFile.write(reinterpret_cast<const char*>(&emailSize), sizeof(emailSize));
            tempFile.write(tempUser.email.c_str(), emailSize);

            size_t techSize = tempUser.technology.size();
            tempFile.write(reinterpret_cast<const char*>(&techSize), sizeof(techSize));
            tempFile.write(tempUser.technology.c_str(), techSize);

            size_t semesterSize = tempUser.semester.size();
            tempFile.write(reinterpret_cast<const char*>(&semesterSize), sizeof(semesterSize));
            tempFile.write(tempUser.semester.c_str(), semesterSize);

            tempFile.write(reinterpret_cast<const char*>(&tempUser.year), sizeof(tempUser.year));
            tempFile.write(reinterpret_cast<const char*>(&tempUser.registered), sizeof(tempUser.registered));

            // Write courses vector
            tempFile.write(reinterpret_cast<const char*>(&courseCount), sizeof(courseCount));
            for (const auto& course : tempUser.courses) {
                size_t courseSize = course.size();
                tempFile.write(reinterpret_cast<const char*>(&courseSize), sizeof(courseSize));
                for (const auto& field : course) {
                    size_t fieldSize = field.size();
                    tempFile.write(reinterpret_cast<const char*>(&fieldSize), sizeof(fieldSize));
                    tempFile.write(field.c_str(), fieldSize);
                }
            }
        }
    }

    inputFile.close();
    tempFile.close();

    remove(filename.c_str());
    rename("temp.bin", filename.c_str());
}

User* loginUser(CircularDoublyList &users){
    system("cls"); sleep(2);
    cout << "\t\t\t\t\t\t-------------------Login Page-------------------";
    string nameOrUsername;
    while(true){
        cout << "\nEnter your full name or username: ";
        getline(cin >> ws, nameOrUsername);
        User* user = users.searchUser(nameOrUsername);
        if(!user){
            cout << "\nThe user with this username or full name does not exist!" << endl;
        }
        else{
            string password = user -> password;
            while(true){
                string p;
                cout << "\nEnter your password: ";
                getline(cin >> ws, p);
                if(p == password){
                    cout << "\nPassword verified successfully!" << endl;
                    break;
                }
                else{
                    cout << "\nIncorrect password...";
                }
            }
            sleep(2); return user;
        }
    }
    return NULL;    //this line will never get executed
}

void signupUser(CircularDoublyList &users){
    system("cls"); sleep(2);
    cout << "\t\t\t\t\t\t-------------------Signup Page-------------------";
    users.addUser();
    system("cls"); sleep(1);
}
