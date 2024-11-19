#include <cstdlib>
#include <unistd.h>
#include <map>
#include "CourseStruct&Tree&Map.h"
#include "Courses&Electives.cpp"

map<User*, vector<vector<string>>> userCourseMap;

//method to display all the courses selected by the user
void displaySelectedCourses(User* user){
    cout << "\nDear " << user -> name << ", you have selected the following courses: " << endl; sleep(2);
    for(auto &course : userCourseMap[user]){
        cout << "\nCourse Code: " << course[0] << "\tCourse Title: " << course[1] << endl;
    }
}

void buildCourseTree(CourseNode* root){
    CourseNode* upperYearOne = new CourseNode(0, "Junior", "0");
    CourseNode* upperYearTwo = new CourseNode(0, "Senior", "0");
    CourseNode* lowerYearOne = new CourseNode(1, "Junior", "0");
    CourseNode* lowerYearTwo = new CourseNode(2, "Junior", "0");
    CourseNode* lowerYearThree = new CourseNode(3, "Senior", "0");
    CourseNode* lowerYearFour = new CourseNode(4, "Senior", "0");
    
    //the following are all the leaf nodes of the hierarchy
    CourseNode* firstFall = new CourseNode(1, "Junior", "Fall", coursesOffered[0]);
    CourseNode* firstSpring = new CourseNode(1, "Junior", "Spring", coursesOffered[1]);
    CourseNode* secondFall = new CourseNode(2, "Junior", "Fall", coursesOffered[2]);
    CourseNode* secondSpring = new CourseNode(2, "Junior", "Spring", coursesOffered[3]);
    CourseNode* thirdFall = new CourseNode(3, "Senior", "Fall", coursesOffered[4]);
    CourseNode* thirdSpring = new CourseNode(3, "Senior", "Spring", coursesOffered[5]);
    CourseNode* fourthFall = new CourseNode(4, "Senior", "Fall", coursesOffered[6]);
    CourseNode* fourthSpring = new CourseNode(4, "Senior", "Spring", coursesOffered[7]);

    root -> left = upperYearOne; upperYearOne -> left = lowerYearOne; lowerYearOne -> left = firstFall;
    lowerYearOne -> right = firstSpring; upperYearOne -> right = lowerYearTwo; lowerYearTwo -> left = secondFall;
    lowerYearTwo -> right = secondSpring;
    firstFall -> left = NULL; firstFall -> right = NULL; firstSpring -> left = NULL; firstSpring -> right = NULL;
    secondFall -> left = NULL; secondFall -> right = NULL; secondSpring -> left = NULL; secondSpring -> right = NULL;

    root -> right = upperYearTwo; upperYearTwo -> left = lowerYearThree; lowerYearThree -> left = thirdFall;
    lowerYearThree -> right = thirdSpring; upperYearTwo -> right = lowerYearFour; lowerYearFour -> left = fourthFall;
    lowerYearFour -> right = fourthSpring;
    thirdFall -> left = NULL; thirdFall -> right = NULL; thirdSpring -> left = NULL; thirdSpring -> right = NULL;
    fourthFall -> left = NULL; fourthFall -> right = NULL; fourthSpring -> left = NULL; fourthSpring -> right = NULL;

    //the entire binary tree hierarchy has been constructed
}

vector<string> getElectiveCourse(vector<vector<string>> &electives){
    system("cls"); sleep(2);
    int i = 0;
    for(auto &elective : electives){
        cout << i << ". Course Code: " << elective[1] << "\tCourse Title: " << elective[2] << endl;
        i++;
    }
    int choice;
    while(true){
        cout << "\nEnter the number for the elective that you want to choose: ";
        cin >> choice;
        if((choice >= 1 && choice <= 8) && electives[choice][0] == "false"){
            electives[choice][0] = "true";
            cout << "\nSuccessfully selected course: " << electives[choice][2] << endl; sleep(2.5);
            return {electives[choice][1], electives[choice][2]};
        }
        else if(choice < 1 || choice > 7){
            cout << "\nInvalid choice entered..." << endl; choice = 0;
        }
        else{
            //this can only mean that the required course has already been selected
            cout << "\nYou have already selected this elective course..."; sleep(2.5); choice = 0;
        }
    }
    return {};  //this line wont get executed
}

void registerUserCourses(CourseNode* root, User* user){
    cout << "\t\t\t\t\t\t-------------------Course Registration Page-------------------" << endl;
    string semester, upperYear;
    int lowerYear = 0;
    vector<vector<string>> coursesSelected;
    while(true){
        cout << "\nEnter your upper year (Junior for Years 1-2 and Senior for Years 3-4): ";
        getline(cin >> ws, upperYear);
        if(upperYear == "Junior" || upperYear == "Senior"){
            break;
        }
        else{
            cout << "\nInvalid year entered..."; upperYear = "";
        }
    }
    (upperYear == "Junior") ? root = root -> left : root = root -> right;
    while(true){
        cout << "\nEnter your lower year (1 for First Year, 2 for Second Year and so forth): ";
        cin >> lowerYear;
        if((upperYear == "Junior" && lowerYear >= 1 && lowerYear <= 2) || (upperYear == "Senior" && lowerYear >= 3 && lowerYear <= 4)){
            user -> year = lowerYear;
            break;
        }
        else{
            cout << "\nInvalid lower year entered...";
            lowerYear = 0;
        }
    }
    (lowerYear == 1 || lowerYear == 3) ? root = root -> left : root = root -> right;
    while(true){
        cout << "\nEnter your semester (Fall or Spring): ";
        getline(cin >> ws, semester);
        if(semester == "Fall" || semester == "Spring"){
            user -> semester = semester;
            break;
        }
        else{
            cout << "\nInvalid semester entered..."; semester = "";
        }
    }
    (semester == "Fall") ? root = root -> left : root = root -> right;
    for(auto &course : root -> courses){
        if(course[0] == "##-###"){
            coursesSelected.push_back(getElectiveCourse(electives));
        }
        else{
            coursesSelected.push_back(course);
        }
    }
    //at this point, we have now gathered our users selected courses in user coursesSelected vector
    //we can now assign our user's courses vector to this
    user -> courses = coursesSelected; user -> registered = true;
    userCourseMap[user] = coursesSelected;
    //now we can just show the user the courses that they have selected
    //for this, we can use a helper function
    system("cls"); sleep(2); displaySelectedCourses(user); sleep(10);
}
