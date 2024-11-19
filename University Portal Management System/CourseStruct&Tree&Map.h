#include <iostream>
#include <vector>
#include "UserStruct&Class.cpp"
using namespace std;

struct CourseNode{
    string upperYear, semester;
    int lowerYear;
    vector<vector<string>> courses;
    
    CourseNode* left;
    CourseNode* right;

    CourseNode() : lowerYear(0), left(NULL), right(NULL) {}

    CourseNode(int lowerYear, string upperYear, string semester) : lowerYear(lowerYear), upperYear(upperYear),
    semester(semester) {}

    CourseNode(int lowerYear, string upperYear, string semester, vector<vector<string>> Courses) : 
    lowerYear(lowerYear), upperYear(upperYear),semester(semester), courses(Courses) {}

};

void buildCourseTree(CourseNode* root);
void registerUserCourses(CourseNode* root, User* user);