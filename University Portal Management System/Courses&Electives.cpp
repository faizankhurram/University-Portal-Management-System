#include <iostream>
#include <vector>
using namespace std;

//the order for template is
    //<<course code, course title>>
    //the order for distribution is
    //{{first year fall semester}, {first year spring semester}, {second year fall semester} and so on...}

vector<vector<vector<string>>> coursesOffered = {
    {{"CT-159", "Programming Fundamentals"}, {"CT-174", "Fundamentals of Information Tehcnology"}, {"EA-104", "Functional English"}, {"PH-122", "Applied Physics"}, {"ES-206", "Islamic Studies"}},
    {{"CS-251", "Logic Design and Switching Theory"}, {"CT-162", "Discrete Structures"}, {"CT-260", "Object Oriented Programming"}, {"MT-171", "Differential and Integral Calculus"}, {"ES-127", "Pakistan Studies"}},
    {{"CT-159", "Data Structure Algorithms and Applications"}, {"MT-227", "Differential Equations"}, {"EA-115", "Academic Reading and Writing"}, {"EA-219", "Professional Ethics"}, {"MT-331", "Probability and Statistics"}},
    {{"CS-252", "Computer Architecture and Organization"}, {"CT-261", "Database Management Systems"}, {"EA-218", "Business Communication"}, {"EC-209", "Financial and Cost Accounting"}, {"MT-272", "Linear Algebra and Geometry"}},
    {{"##-###", "Computer Science Elective 1"}, {"##-###", "Computer Science Elective 2"}, {"CT-365", "Software Engineering"}, {"CT-262", "Introduction to Artificial Intelligence"}, {"CT-363", "Design and Analysis of Algorithms"}, {"CT-364", "Theory of Automata and Formal Languages"}},
    {{"##-###", "Computer Science Elective 3"}, {"CT-376", "Computer Communication Networks"}, {"CT-353", "Operating Systems"}, {"CT-362", "Web Engineering"}, {"CT-367", "Theory of Programming Languages"}},
    {{"CT-499", "Final Year Project"}, {"MG-482", "Organizational Behavior"}, {"##-###", "Computer Science Elective 4"}, {"CT-486", "Network and Information Security"}, {"CT-407", "Human Computer Interaction"}},
    {{"CT-499", "Final Year Project"}, {"##-###", "Computer Science Elective 5"}, {"CS-428", "Parallel and Dstributed Computing"}, {"CT-465", "Compiler Design"}, {"MG-481", "Entrepreneurship"}}
};

vector<vector<string>> electives = {
    {"false", "CT-263", "Object Oriented Analysis and Design"},
    {"false", "CT-264", "Programming for Artificial Intelligence"},
    {"false", "CT-368", "Fundamentals of Data Science"},
    {"false", "CT-266", "Fundamentals of Cyber Security"},
    {"false", "CT-267", "Fundamentals of Game Development"},
    {"false", "MT-442", "Numerical Methods"},
    {"false", "CT-337", "Data Mining"},
    {"false", "CT-378", "Machine Learning"}
};