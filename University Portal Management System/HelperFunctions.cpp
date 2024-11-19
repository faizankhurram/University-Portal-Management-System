#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <unordered_map>
#include "CourseStruct&Tree&Map.cpp"
using namespace std;

void displayInitialMenu(void){
    system("cls");
    cout << "\t\t\t\t\t\t-------------------Online University Portal-------------------" << endl;
    cout << "\n\nWelcome, user! Please choose any one of the following two options..."; sleep(2);
    cout << "\n\n1. Login\n2. Signup" << endl << endl; sleep(2.5);
}

void displayMainMenu(User* user){
    system("cls");
    cout << "\t\t\t\t\t\t-------------------Portal Main Menu---------------------" << endl;
    cout << "\n\n\t\t\t\t\t\t-------------------User ID: " << user -> username << "-------------------";
    cout << "\n\t\t\t\t\t\t-------------------Registration: ";
    (user -> registered) ? cout << "COMPLETE" : cout << "INCOMPLETE";
    cout << "---------------";
    cout << "\n\n\nPlease select any option of your preference from the below menu list..."; sleep(3); cout << endl;
    cout << "\n1. Undergraduate Registration\n2. Generate Enrollment Card\n3. Generate Admit Card";
    cout << "\n4. Generate Progressive Transcript (Randomized)\n5. Attendance\n6. Search for a Student";
    cout << "\n7. Logout from Portal";
    cout << "\n\nP.S. Remember to log out otherwise your data will not be saved further!" << endl << endl;
    sleep(4);
}

void generateEnrollmentCard(User* user){
    cout << "\t\t\t\t\t\t-------------------Enrollment Card Page-------------------" << endl << endl;
    cout << "\nName: " << user -> name << "\n\nPortal ID: " << user -> username;
    cout << "\n\nAcademic Year: " << user -> year << "\n\nSemester: " << user -> semester;
    cout << endl << endl;
    displaySelectedCourses(user);
    sleep(10);
}

void displayProgressiveTranscript(unordered_map<string, float> coursesGPA){
    for(auto &pair : coursesGPA){
        cout << "\nCourse Name: " << pair.first << "\nObtained GPA: " << pair.second << endl << endl;
    }
}

void merge(vector<pair<string, float>> &courses, int left, int mid, int right, bool ascending){
    vector<pair<string, float>> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while(i <= mid && j <= right){
        if((ascending && courses[i].second <= courses[j].second) ||
            (!ascending && courses[i].second > courses[j].second)){
            temp[k++] = courses[i++];
        }
        else{
            temp[k++] = courses[j++];
        }
    }

    while (i <= mid) temp[k++] = courses[i++];
    while (j <= right) temp[k++] = courses[j++];

    for(i = left, k = 0; i <= right; ++i, ++k){
        courses[i] = temp[k];
    }
}

void mergeSort(vector<pair<string, float>> &courses, int left, int right, bool ascending){
    if(left >= right){
        return;
    }
    int mid = (left + right) / 2;
    mergeSort(courses, left, mid, ascending);
    mergeSort(courses, mid + 1, right, ascending);
    merge(courses, left, mid, right, ascending);
}

void displaySortedProgressiveTranscript(unordered_map<string, float> &coursesGPA, bool ascending){
    vector<pair<string, float>> courses(coursesGPA.begin(), coursesGPA.end());
    mergeSort(courses, 0, courses.size() - 1, ascending);

    cout << "\nSorted Transcript:\n";
    for (auto &pair : courses){
        cout << "\nCourse Name: " << pair.first << "\nObtained GPA: " << pair.second << endl << endl;
    }
}

void generateProgressiveTranscript(User* user){
    unordered_map<string, float> coursesGPA;
    for(auto &course : userCourseMap[user]){
        float randomGPA = 2.0 + static_cast<float>(rand() % 201) / 100.0;
        coursesGPA[course[1]] = randomGPA;
    }
    //the GPA for each course has now been randomly generated
    //now we can move on to displaying the result of the transcript generation to the user
    sleep(2);
    cout << "\nDear " << user -> name << ", your transcript has been generated. Would you like to: ";
    cout << "\n\n1. View it by default\n2. View it sorted" << endl; sleep(2);
    int firstChoice = 0;
    while(true){
        cout << "\nEnter your choice: ";
        cin >> firstChoice;
        if(firstChoice < 1 || firstChoice > 2){
            cout << "\nInvalid choice entered..." << endl; firstChoice = 0;
        }
        else{
            break;
        }
    }

    if(firstChoice == 1){
        system("cls"); sleep(2); displayProgressiveTranscript(coursesGPA); sleep(10);
    }
    else{
        system("cls"); sleep(2);
        cout << "\nWould you like to view your transcript sorted in either: ";
        cout << "\n\n1. Ascending Order\n2. Descending Order" << endl; sleep(2);
        int secondChoice = 0;
        while(true){
            cout << "\nEnter your choice: ";
            cin >> secondChoice;
            if(secondChoice < 1 || secondChoice > 2){
                cout << "\nInvalid choice entered..." << endl; secondChoice = 0;
            }
            else{
                break;
            }
        }
        if(secondChoice == 1){
            //this will present the result in ascending order GPA wise
            system("cls"); sleep(2);
            displaySortedProgressiveTranscript(coursesGPA, true);
        }
        else{
            //this will present the result in descending order GPA wise
            system("cls"); sleep(2);
            displaySortedProgressiveTranscript(coursesGPA, false);
        }
        sleep(10);
    }
}