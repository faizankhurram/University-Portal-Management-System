#include "Queue.cpp"
using namespace std;

bool attendance = false;

int main(void) {
    CircularDoublyList users;
    LinearQueue<string> queue(250);     //for safe work
    //the hashmap is coming from the file "CourseStruct&Tree&Map.cpp"
    CourseNode* root;
    buildCourseTree(root);

    while(true){
        //Booting up our up-to-date users database as-well-as our hashmap
        vector<User*> userVec = loadUsersFromFile("users.bin");
        for (auto &user : userVec) {
            userCourseMap[user] = user -> courses;
            users.addUser(user);
        }

        displayInitialMenu();
        int initialMenuChoice = 0;
        while(true){
            cout << "\nEnter your choice: ";
            cin >> initialMenuChoice;
            if(initialMenuChoice < 1 || initialMenuChoice > 2){
                cout << "\nInvalid option entered..."; initialMenuChoice = 0;
            }
            else{
                break;
            }
        }

        if(initialMenuChoice == 1){
            system("cls");
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t-------------------Loading Login Page-------------------";
            sleep(2.5);
            User* user = loginUser(users);
            while(true){
                system("cls");
                cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t-------------------Loading Main Page-------------------";
                sleep(2.5);
                displayMainMenu(user);
                int mainMenuChoice = 0;
                cout << "Enter your choice: ";
                cin >> mainMenuChoice;
                if(mainMenuChoice == 7){
                    //log out the user from the portal
                    system("cls");
                    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t-------------------Loading Logout Page-------------------";
                    sleep(2.5);
                    system("cls"); sleep(2);
                    cout << "\nLogging out user ID: " << user -> username << " ..."; sleep(3);
                    //removing the old copy of the user node from our binary file
                    removeUserFromFile(user, "users.bin");
                    //appending this newly updated user node with the modified data back to our binary file
                    writeUserToFile(user, "users.bin");
                    //in this way, when the same user logs in again, their most-recent information will be dynamically retrieved
                    return -1;
                }
                else if(mainMenuChoice == 1){
                    //undergraduate registration
                    system("cls");
                    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t-------------------Loading Course Registration Page-------------------";
                    sleep(2.5);
                    system("cls"); sleep(2);
                    if(user -> registered){
                        cout << "\nDear " << user -> name << ", you have already registered for your courses..." << endl; sleep(2);
                    }
                    else{
                        registerUserCourses(root, user);
                    }
                }
                else if(mainMenuChoice == 2){
                    //generate enrollment card
                    system("cls");
                    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t-------------------Loading Enrollment Card Page-------------------";
                    sleep(2.5);
                    system("cls"); sleep(2);
                    if(!user -> registered){
                        cout << "\nDear " << user -> name << ", your registration is incomplete..." << endl; sleep(3);
                    }
                    else{
                        generateEnrollmentCard(user);
                    }
                }
                else if(mainMenuChoice == 3){
                    //generate admit card
                    system("cls");
                    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t-------------------Loading Admit Card Status-------------------";
                    sleep(2.5);
                    system("cls"); sleep(2);
                    if(!user -> registered){
                        cout << "\nDear " << user -> name << ", your registration is incomplete..." << endl; sleep(2);
                    }
                    else{
                        if(!attendance){
                            cout << "\nDear " << user -> name << ", please submit your attendance first..." << endl; sleep(2);
                        }
                        else{
                            bool canGetAdmitCard = finalizeAttendance(queue);
                            if(canGetAdmitCard){
                                cout << "\nDear " << user -> name << ", based on your attendance evaluation,";
                                cout << " your Admit Card is unlocked and can be retrieved from the department office...";
                                cout << endl; sleep(6);
                            }
                            else{
                                cout << "\nYour Admit Card is locked due to shortage of attendance..." << endl; sleep(5);
                            }
                        }
                    }
                }
                else if(mainMenuChoice == 4){
                    //generate progressive transcript
                    system("cls");
                    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t-------------------Generating Progressive Transcript-------------------";
                    sleep(2.5);
                    system("cls"); sleep(2);
                    if(!user -> registered){
                        cout << "\nDear " << user -> name << ", your registration is incomplete..." << endl; sleep(2);
                    }
                    else{
                        generateProgressiveTranscript(user);
                    }
                }
                else if(mainMenuChoice == 5){
                    //attendance
                    system("cls");
                    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t-------------------Loading Attendance Page-------------------";
                    sleep(2.5);
                    system("cls"); sleep(2);
                    if(!user -> registered){
                        cout << "\nDear " << user -> name << ", your registration is incomplete..." << endl; sleep(2);
                    }
                    else{
                        int choice = 0;
                        cout << "\nPlease select any one of the following two options: ";
                        cout << "\n\n1. Enter your attendance records\n2. View recently attended classes" << endl; sleep(2);
                        while(true){
                            cout << "\nEnter your choice: ";
                            cin >> choice;
                            if(choice < 1 || choice > 2){
                                cout << "\nInvalid choice entered..."; choice = 0;
                            }
                            else{
                                break;
                            }
                        }
                        if(choice == 1){
                            if(!attendance){
                                attendance = true;
                                getUserAttendance(queue, user);
                            }
                            else{
                                system("cls"); sleep(2);
                                cout << "\nDear " << user -> name << ", you have already submitted your attendance for this session..." << endl;
                                sleep(3);
                            }
                        }
                        else{
                            mostRecentAttendedClasses(queue);
                        }
                    }

                }
                else if(mainMenuChoice == 6){
                    //searching
                    system("cls");
                    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t-------------------Loading Search Page-------------------";
                    sleep(2.5);
                    system("cls"); sleep(2);
                    int searchChoice = 0;
                    cout << "\nWould you like to search for: \n\n1. Any specific student\n2. Students department wise";
                    while(true){
                        cout << "\n\nEnter your choice: ";
                        cin >> searchChoice;
                        if(searchChoice < 1 || searchChoice > 2){
                            cout << "\nInvalid choice..."; searchChoice = 0;
                        }
                        else{
                            break;
                        }
                    }
                    string tag;
                    if(searchChoice == 1){
                        sleep(2.5); system("cls");
                        cout << "\nEnter the username or full name: ";
                        getline(cin >> ws, tag);
                        system("cls");
                        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t-------------------Searching For User-------------------";
                        sleep(2.5); system("cls");
                        User* userFromSearch = users.searchUser(tag);
                        if(!userFromSearch){
                            cout << "\nThe required user does not exist!" << endl; sleep(2);
                        }
                        else{
                            users.displayUser(userFromSearch); sleep(5);
                        }
                    }
                    else{
                        sleep(2.5); system("cls");
                        cout << "\nEnter the department to search for all the students: ";
                        getline(cin >> ws, tag);
                        system("cls");
                        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t-------------------Searching this Department-------------------";
                        sleep(2.5); system("cls");
                        users.searchUsersByTechnology(tag); sleep(5);
                    }
                }
                else{
                    cout << "\nInvalid option selected..."; sleep(2);
                }
            }
        }
        else{
            system("cls");
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t-------------------Loading Signup Page-------------------";
            sleep(2.5);
            signupUser(users);
        }
    }
    return 0;
}
