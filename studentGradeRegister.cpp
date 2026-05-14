#include <fstream>
#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>

using namespace std;
const string lines = "--------------------------------------------------------------------------------------------";
const string dlines = "=============================================================================================";
string filename;
struct student {

    string names;
    int marks;
    string grades;

};

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear")
    #endif

}

void printStudentResults(const vector<student>& s){
    for (int i =0; i<s.size(); i++ ){
        cout << s[i].names<<endl;
        cout << s[i].marks<<endl;
        cout << s[i].grades<<endl;
        cout << "\n"<<endl;
    }
}

bool loadfile(vector<student>& s, const string filename){
    string name;
    int mark;
    string stringmark;
    string grade;
    student student;
    ifstream ifile(filename);
    if (!ifile.is_open()){
        cout << "error: file has failed to open";
        
        return true;
    }
    while(getline(ifile,name)){
        student.names = name;
        getline(ifile, stringmark);
        mark = stoi(stringmark);
        student.marks = mark;
        getline(ifile,grade);
        student.grades = grade;

        s.push_back(student);


    }
    ifile.close();
    return false;
}


bool writefile(vector<student>s, const string filename){

    ofstream ofile(filename);
    if(!ofile.is_open()){
        cout<<"error: file has failed to open";
        
        return true;
    }
    for (int i=0; i<s.size(); i++){
        ofile << s[i].names<<endl;
        ofile << s[i].marks<<endl;
        ofile << s[i].grades<<endl;
    }
    ofile.close();
    return false;
}

string  claculateGrade(const int& mark){
    string grade;
    if(mark >=82){
        grade = "A+";
    }
    else if(mark < 82 && mark >+75){
        grade ="A";
    }
    else if(mark<75 && mark>=68){
        grade = "B+";
    }
    else if(mark <68 && mark>=61){
        grade = "B";

    }
    else if(mark< 61 && mark >= 55){
        grade ="C+";

    }
    else if (mark <55 && mark >=48){
        grade = "c";

    }
    else if(mark< 48 && mark >=40){
        grade = "D";

    }
    else{
        grade = "F";
    }
    return grade;
}
int findStudent(const vector<student>& s){

    while(true){
        int index = 0;
        cout <<"enter student name: ";
        string name;
        getline(cin,name);
        for(char c: name){
            c = tolower(c);
        }
        for(int i= 0; i<s.size(); i++){
            string namelower = s[i].names;
            for(char& c: namelower){

                c= tolower(c);
            }
            if (name == namelower){
                return index;
            }
            index++;
        }
        cout << name << " "<< "has not been found\nPRESS Q TO QUIT AND ANY KEY TO REENTER NAME: ";
        string choice;
        getline(cin, choice);
        if (choice == "Q" || choice == "q") {
            return -1;
        }
        clearScreen();

    }
        
}
int viewIndividualResults(const vector<student>& s) {
    int index = findStudent(s);
    if(index != -1) {
        cout<<setw(6)<<"name: "<<setw(6)<<s[index].names<<endl;
        cout<<setw(6)<<"marks: "<<setw(6)<<s[index].marks<<endl;
        cout<<setw(6)<<"grade: "<<setw(6)<<s[index].grades<<endl;
    }
    return index;
}

void addStudent( vector<student>& s){
    student student;
    
    cout << "enter the name of the student: ";
    getline(cin, student.names);
    
    
    while (true){
        
        cout << "enter marks: ";
        if (!(cin >> student.marks) || cin.peek() != '\n'){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << " please enter a valid input"<<endl;
            continue;
        }
        cin.ignore();
         
        break;

    }

    
    student.grades =claculateGrade(student.marks);
    
    s.push_back(student);
}
void changeResults(vector<student>& s){
    int index = viewIndividualResults(s);
    if (index == -1){
        return;
    }

    while(true){
        int choice;
        while(true){
            cout<<"1: change student name\n 2:change student marks\n 3: exit\n CHOSE NUMBER: ";
                
            cin>>choice;
            if(cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                choice = 0;
            }
            else{
                cin.ignore();
            }
            if ((choice == 0) || (choice < 1 || choice >4)) {
                cout << "invalid entry"<<endl;
            }
            else{
                break;
            }
        }
        switch(choice){
            case 1: cout << "enter new name: ";
                    getline(cin, s[index].names);
                    break;
            case 2: cout<<"enter new marks: ";
                    cin>>s[index].marks;
                    cin.ignore();
                    s[index].grades = claculateGrade(s[index].marks);
                    break;
            case 3: return;
            default: "invalid entry";
         }     
    }
    
}

void deleteStudent(vector<student>& s){
    int index = viewIndividualResults(s);
    cout << "are you sure you wantto delete"<< " "<<s[index].names<<" "<< "fromthe file :";
    cout<<"y or n : ";
    string choice;
    getline(cin, choice);

    if (choice == "y"){
        s.erase(s.begin() + index);
        cout<<s[index].names<<" "<<"has been deleted successfully"<<endl;
    }
    return;

}



void makeDecision(){
    cout << lines<<endl;
    cout << "STUDENT GRADE TRACKER"<<endl;
    cout << dlines<<endl;
    cout << "1: VIEW RESULTS\n 2: CAHNGE RESULTS\n 3: ADD STUDENT RESULTS\n 4: DELETE STUDENT RESULTS\n 5: view individual results\n 6: TO EXIT AND SAVE FILE\n ENTER NUMBER: ";
    
}



int main(){
 
    vector<student> studentresults;
    bool running = true;
    while (running){
        cout<<"enter the name of the file in use: ";
        getline(cin, filename);
        running = loadfile(studentresults, filename);
        if (running == true) {
            cout << "press q to exit or anykey reenterfile: ";
            string choice;
            getline(cin, choice);

            if (choice == "q" || choice == "Q"){
                return 0;
            }

        }
    }
    int decision;
    bool exitfile = true;
    do {
        clearScreen();
        makeDecision();
        cin >> decision;
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), 'n');
            decision = 0;
        }
        cin.ignore();

        switch(decision){
            case 1: printStudentResults(studentresults);
                    system("pause");
                    break;
            case 2: changeResults(studentresults);
                    system("pause");
                    break;
            case 3:addStudent(studentresults);
                    system("pause");
                    break;
            case 4:break;
            case 5: viewIndividualResults(studentresults);
                    system("pause");
                     break;
            case 6: exitfile = false; break;
            defaute: cout << "invalid entry: please enter values in the options";
                    

        }
        
    }while(exitfile);

    running = true;
    while (running){
        cout<<"enter the name of the file in use: ";
        getline(cin, filename);
        running = writefile(studentresults, filename);
        if (running == true) {
            cout << "press q to exit or anykey reenterfile: ";
            string choice;
            getline(cin, choice);

            if (choice == "q" || choice == "Q"){
                return 0;
            }

        }
    }
    
    system("pause");

}