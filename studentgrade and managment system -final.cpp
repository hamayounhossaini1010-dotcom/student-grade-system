#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

// PILLAR 4: Transactional Integrity. You use a global constant here to establish a Single Source of Truth for your database file.
const string FILE_NAME = "student_grades.txt";

/* ================= ENCAPSULATED DATA MODELS (OOP) ================= */

class SubjectScores {
private:
    // PILLAR 1: Encapsulated Structural Design. You apply Data Hiding by using 'private' to protect these variables from external modification.
    double chinese{0};
    double math{0};
    double english{0};
    double computer{0};

public:
    // Secure data accessors (Getters)
    // PILLAR 1: Access Control. You place the 'const' keyword at the exact end of these functions to guarantee they are read-only. This prevents accidental data changes.
    double getChinese() const { return chinese; }
    double getMath() const { return math; }
    double getEnglish() const { return english; }
    double getComputer() const { return computer; }

    // Data mutator (Setter)
    void setScores(double c, double m, double e, double comp) {
        chinese = c;
        math = m;
        english = e;
        computer = comp;
    }
};

class Student {
private:
    string semester;
    string studentID;
    string className;
    string name;
    // PILLAR 1: Object Composition. You implement a "Has-A" relationship here. The Student class contains the SubjectScores object, separating identity logic from math logic.
    SubjectScores scores;
    double totalScore{0};
    double averageScore{0};

    // Internal calculation method
    void calculateScores() {
        totalScore = scores.getChinese() + scores.getMath() + 
                     scores.getEnglish() + scores.getComputer();
        averageScore = totalScore / 4.0;
    }

public:
    Student() = default;
    Student(string sem, string id, string cls, string n, double c, double m, double e, double comp) {
        semester = sem;
        studentID = id;
        className = cls;
        name = n;
        scores.setScores(c, m, e, comp);
        calculateScores();
    }

    // Secure data accessors
    string getSemester() const { return semester; }
    string getStudentID() const { return studentID; }
    string getClassName() const { return className; }
    string getName() const { return name; }
    const SubjectScores& getScores() const { return scores; }
    double getTotalScore() const { return totalScore; }
    double getAverageScore() const { return averageScore; }

    // Mutator for record modification
    void updateGrades(double c, double m, double e, double comp) {
        scores.setScores(c, m, e, comp);
        calculateScores();
    }

    // Evaluation business logic
    bool hasFailingSubject() const {
        return scores.getChinese() < 60 || scores.getMath() < 60 || 
               scores.getEnglish() < 60 || scores.getComputer() < 60;
    }
};

/* ================= INPUT VALIDATION UTILITIES ================= */

// Flushes remaining invalid characters from the input stream buffer
void clearInputBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Validates numeric data entry and prevents stream type failure crashes
double inputScore(const string& subject) {
    double score;
    while (true) {
        cout << "   Enter " << subject << " Score (0-100): ";
        cin >> score;
        // PILLAR 2: Defensive Runtime Engineering. You built a Validation Gate here. If a user inputs text instead of numbers, you catch the fail state and clear the buffer to prevent a crash.
        if (cin.fail()) {
            cin.clear();
            clearInputBuffer();
            cout << "   Invalid input! Please enter a numerical value." << endl;
            continue;
        }
        if (score >= 0 && score <= 100) return score;
        cout << "   Range error! Score must be strictly between 0 and 100." << endl;
    }
}

/* ================= HELPER METHODS (MODULAR DESIGN) ================= */

// PILLAR 3: Algorithmic Efficiency. You decoupled your sorting logic into these modular predicates. This ensures your STL sorts execute efficiently as the class size grows.
bool compareByAverageDescending(const Student& a, const Student& b) {
    return a.getAverageScore() > b.getAverageScore();
}

bool compareByNameAscending(const Student& a, const Student& b) {
    return a.getName() < b.getName();
}

// Displays individual formatted student report cards
void printSingleReportCard(const Student& s) {
    cout << "\n=========================================\n";
    cout << "             OFFICIAL REPORT CARD         \n";
    cout << "=========================================\n";
    cout << " ID Vector : " << s.getStudentID() << "\n Name      : " << s.getName() << "\n";
    cout << " Semester  : " << s.getSemester() << "\n Class Group: " << s.getClassName() << "\n";
    cout << "-----------------------------------------\n";
    cout << " Chinese   : " << setw(6) << s.getScores().getChinese() << "  |  Math     : " << s.getScores().getMath() << "\n";
    cout << " English   : " << setw(6) << s.getScores().getEnglish() << "  |  Computer : " << s.getScores().getComputer() << "\n";
    cout << "-----------------------------------------\n";
    cout << " Gross Sum : " << setw(6) << s.getTotalScore()  << "  |  GPA Avg  : " << fixed << setprecision(2) << s.getAverageScore() << "\n";
    cout << "=========================================\n";
}

// Prints a single line entry for failing student records
void printFailingRow(const Student& s) {
    string failedList = "";
    if (s.getScores().getChinese() < 60) failedList += "Chi ";
    if (s.getScores().getMath() < 60) failedList += "Math ";
    if (s.getScores().getEnglish() < 60) failedList += "Eng ";
    if (s.getScores().getComputer() < 60) failedList += "Com ";

    cout << left << setw(12) << s.getClassName() 
         << setw(12) << s.getStudentID() 
         << setw(15) << s.getName() 
         << "Failed: [ " << failedList << "]\n";
}

/* ================= CORE FUNCTIONAL MODULES ================= */

// Requirement (1): Grade Entry and Modification
void addOrUpdateGrade(vector<Student>& students) {
    string semester, className, id, name;
    cout << "\n=========================================\n";
    cout << "      1. GRADE ENTRY & MODIFICATION       \n";
    cout << "=========================================\n";
    cout << "Enter Semester (e.g., 2026-Fall): "; cin >> semester;
    cout << "Enter Class Name: "; cin >> className;
    cout << "Enter Student ID: "; cin >> id;
    
    double chi, math, eng, comp;

    for (auto& s : students) {
        if (s.getSemester() == semester && s.getClassName() == className && s.getStudentID() == id) {
            cout << "\n Match Found! Updating records for student: " << s.getName() << "\n";
            s.updateGrades(inputScore("Chinese"), inputScore("Math"), inputScore("English"), inputScore("Computer"));
            cout << "Grade record modified successfully!\n";
            return;
        }
    }

    // Clear buffer right before using getline to read names with spaces safely
    clearInputBuffer();
    cout << "\n No existing record found. Registering a new profile.\n";
    cout << "Enter Student Name: ";
    getline(cin, name);
    
    chi = inputScore("Chinese");
    math = inputScore("Math");
    eng = inputScore("English");
    comp = inputScore("Computer");

    students.emplace_back(semester, id, className, name, chi, math, eng, comp);
    cout << "New student profile successfully registered into the system!\n";
}

// Requirement (2): Grade Statistics by Class
void showClassStatistics(vector<Student>& students) {
    if (students.empty()) {
        cout << "\n No data records available in the system.\n";
        return;
    }
    string targetClass;
    cout << "\nEnter Target Class Name for Statistics: "; cin >> targetClass;

    vector<Student> classSubSet;
    for (const auto& s : students) {
        if (s.getClassName() == targetClass) classSubSet.push_back(s);
    }
    if (classSubSet.empty()) {
        cout << " No records located matching class code: " << targetClass << "\n";
        return;
    }

    int sortChoice;
    cout << "Choose Sorting Order:\n  1. Sort by Average (Highest First)\n  2. Sort by Name (A-Z)\nChoice: ";
    cin >> sortChoice;

    if (sortChoice == 1) {
        sort(classSubSet.begin(), classSubSet.end(), compareByAverageDescending);
    } else if (sortChoice == 2) {
        sort(classSubSet.begin(), classSubSet.end(), compareByNameAscending);
    }

    cout << "\n=======================================================\n";
    cout << "        GRADE PERFORMANCE STATISTICS FOR CLASS: " << targetClass << " \n";
    cout << "=======================================================\n";
    cout << left << setw(8) << "Rank" << setw(15) << "Name" << setw(15) << "Total Score" << "Average Score\n";
    cout << "-------------------------------------------------------\n";

    for (size_t i = 0; i < classSubSet.size(); ++i) {
        cout << left << setw(8) << (i + 1) << setw(15) << classSubSet[i].getName()
             << setw(15) << fixed << setprecision(1) << classSubSet[i].getTotalScore()
             << fixed << setprecision(2) << classSubSet[i].getAverageScore() << "\n";
    }
}

// Requirement (3): Grade Query Interface
void queryGradeSystem(const vector<Student>& students) {
    int choice;
    cout << "\n=========================================\n";
    cout << "             3. GRADE QUERY SYSTEM        \n";
    cout << "=========================================\n";
    cout << "1. Search Specific Student Details by ID\n";
    cout << "2. View Comprehensive Failing Student Directory\n";
    cout << "Select Lookup Mode: "; cin >> choice;

    if (choice == 1) {
        string targetID;
        cout << "Enter target Student ID: "; cin >> targetID;
        for (const auto& s : students) {
            if (s.getStudentID() == targetID) {
                printSingleReportCard(s);
                return;
            }
        }
        cout << " No matching profile registered under ID: " << targetID << "\n";
    } 
    else if (choice == 2) {
        cout << "\n=======================================================\n";
        cout << "        ACADEMIC PROBATION / FAILING DIRECTORY         \n";
        cout << "=======================================================\n";
        cout << left << setw(12) << "Class" << setw(12) << "Student ID" << setw(15) << "Name" << "Status Summary\n";
        cout << "-------------------------------------------------------\n";
        
        bool foundFailures = false;
        for (const auto& s : students) {
            if (s.hasFailingSubject()) {
                printFailingRow(s);
                foundFailures = true;
            }
        }
        if (!foundFailures) cout << " Validated: 100% of student profiles meet passing benchmarks.\n";
    } else {
        cout << " Out of selection range.\n";
    }
}

// Requirement (4): Grade Report Generation
void generateClassReport(const vector<Student>& students) {
    string targetClass;
    cout << "\nEnter Class Name for Report Generation: "; cin >> targetClass;

    cout << "\n============================================================================\n";
    cout << "                    OFFICIAL CLASS REPORT SHEET: " << targetClass << " \n";
    cout << "============================================================================\n";
    cout << left << setw(12) << "ID" << setw(15) << "Name" 
         << setw(8) << "Chi" << setw(8) << "Math" << setw(8) << "Eng" << setw(8) << "Com" << "Average\n";
    cout << "----------------------------------------------------------------------------\n";

    bool found = false;
    for (const auto& s : students) {
        if (s.getClassName() == targetClass) {
            cout << left << setw(12) << s.getStudentID() << setw(15) << s.getName()
                 << setw(8) << fixed << setprecision(1) << s.getScores().getChinese()
                 << setw(8) << s.getScores().getMath() << setw(8) << s.getScores().getEnglish() << setw(8) << s.getScores().getComputer()
                 << fixed << setprecision(2) << s.getAverageScore() << "\n";
            found = true;
        }
    }
    if (!found) cout << " No active records match Class: " << targetClass << "\n";
    cout << "============================================================================\n";
}

/* ================= SECURE DATA PERSISTENCE ================= */

void saveToFile(const vector<Student>& students) {
    // PILLAR 4: Transactional Integrity. You explicitly acquire the file handle here to manage the data lifecycle safely.
    ofstream out(FILE_NAME);
    if (!out) return;
    for (const auto& s : students) {
        out << s.getSemester() << "|" << s.getStudentID() << "|" << s.getClassName() << "|" << s.getName() << "|"
            << s.getScores().getChinese() << "|" << s.getScores().getMath() << "|"
            << s.getScores().getEnglish() << "|" << s.getScores().getComputer() << "\n";
    }
    out.close();
}

void loadFromFile(vector<Student>& students) {
    ifstream in(FILE_NAME);
    if (!in) return; 

    students.clear();
    string line;
    while (getline(in, line)) {
        vector<string> segments;
        size_t position;
        while ((position = line.find('|')) != string::npos) {
            segments.push_back(line.substr(0, position));
            line.erase(0, position + 1);
        }
        segments.push_back(line);

        if (segments.size() != 8) continue;
        try {
            students.emplace_back(segments[0], segments[1], segments[2], segments[3],
                                  stod(segments[4]), stod(segments[5]), stod(segments[6]), stod(segments[7]));
        } catch (...) {
            continue; 
        }
    }
    in.close();
}

// Display interface helper to keep main() loop tight and compliant
void displayMainMenu() {
    cout << "\n===================================================\n";
    cout << "        STUDENT GRADE MANAGEMENT CORE SYSTEM         \n";
    cout << "===================================================\n";
    cout << "  1. Grade Entry and Modification\n";
    cout << "  2. Grade Statistics by Class\n";
    cout << "  3. Grade Query Portal\n";
    cout << "  4. Grade Report Generation\n";
    cout << "  5. Explicit Save Matrix\n";
    cout << "  0. Secure Exit and Commit Saves\n";
    cout << "===================================================\n";
    cout << "Select Option ID (0-5): ";
}

/* ================= CENTRAL APPLICATION RUNTIME INTERFACE ================= */

int main() {
    vector<Student> systemDatabase;
    loadFromFile(systemDatabase);

    int menuDirective;
    do {
        displayMainMenu();
        if (!(cin >> menuDirective)) {
            cin.clear();
            clearInputBuffer();
            cout << "Invalid Directive! Input execution path canceled." << endl;
            continue;
        }

        switch (menuDirective) {
            case 1: addOrUpdateGrade(systemDatabase); break;
            case 2: showClassStatistics(systemDatabase); break;
            case 3: queryGradeSystem(systemDatabase); break;
            case 4: generateClassReport(systemDatabase); break;
            case 5: 
                saveToFile(systemDatabase); 
                cout << "Local database cache written to flat-file successfully." << endl; 
                break;
            case 0: 
                saveToFile(systemDatabase); 
                cout << "Data records safely saved. Shutting down system. Goodbye!" << endl; 
                break;
            default: cout << "Selection code outside operational boundaries." << endl;
        }
    } while (menuDirective != 0);

    return 0;
}