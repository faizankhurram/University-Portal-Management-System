#include "Queue.h"

void getUserAttendance(LinearQueue<string> &queue, User* user){
    system("cls"); sleep(2);
    for(auto &course : userCourseMap[user]){
        int attendance = 0;
        while(true){
            cout << "\nEnter the attended classes for course: " << course[1] << ": ";
            cin >> attendance;
            if(attendance < 0 || attendance > 40){
                cout << "\nInvalid attendance entered..."; attendance = 0;
            }
            else{
                break;
            }
        }
        while(attendance > 0){
            //this will fill up the queue correctly
            queue.push(course[1]); attendance--;
        }
    }
    sleep(2);
    //at this point, the attendance will be successfully filled up for all the courses in our queue
    //and the queue will get modified
}

void mostRecentAttendedClasses(LinearQueue<string> queue){
    system("cls"); sleep(2);
    int k = 0;
    cout << "\nEnter the number of most recent classes that you want to look up for: ";
    cin >> k;
    if(queue.size() < k){
        cout << "\nYou have not attended enough classes yet..." << endl; sleep(2);
    }
    else{
        while(!queue.isEmpty() && queue.size() > k){
            queue.pop();
        }
        //now we have the correct amount of classes
        map<string, int> classes;
        while(!queue.isEmpty()){
            classes[queue.front()]++; queue.pop();
        }
        cout << "\n\nYou have attended the following " << k << " classes recently: " << endl;
        for(auto &pair : classes){
            cout << "\n" << pair.first << ": " << pair.second << endl;
        }
        sleep(6);
    }
}

bool finalizeAttendance(LinearQueue<string> queue){
    //since we are assuming that every course will have a maximum of 40 classes
    //the student must have attended atleast 28 classes for each course
    //and in total, must have atleast 75% attendance combined
    map<string, int> classes;
    while(!queue.isEmpty()){
        classes[queue.front()]++; queue.pop();
    }
    
    vector<string> uneligibleCourses;

    int curr = 0, total = 0;
    for(auto &pair : classes){
        if(pair.second < 28){
            //not eligibile to give exam for this particular course
            uneligibleCourses.push_back(pair.first);
        }
        curr += pair.second; total += 40;
    }
    if(uneligibleCourses.size() >= 1){
        cout << "\nUnfortunately, you are unelgibile to appear in the exams for the following courses: " << endl;
        for(auto &course : uneligibleCourses){
            cout << "-" << course << endl;
        }
    }
    sleep(5);
    //now, we need to check if the total number of classes constitute an average attendance of atleast 75%
    int overall = (static_cast<double>(curr) / total) * 100;
    if(overall < 75){
        return false;
    }
    //if all this passes, the student is eligible to sit in the exam
    return true;
}