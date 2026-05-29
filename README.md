# Student Grade Management System

A comprehensive C++ course design project for managing student grades with OOP principles, data validation, and persistent file storage.

## Table of Contents
- [Features](#features)
- [Architecture & Design Principles](#architecture--design-principles)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
- [Installation & Compilation](#installation--compilation)
- [Usage Guide](#usage-guide)
- [System Requirements](#system-requirements)

## Features

### Core Functionality
1. **Grade Entry & Modification** - Add new student records or update existing grades
2. **Grade Statistics by Class** - View class-wide statistics with sorting options (by average or name)
3. **Grade Query Portal** - Search individual student records or view failing students directory
4. **Grade Report Generation** - Generate comprehensive class reports with all subject scores
5. **Data Persistence** - Automatic file-based storage and loading of student records

### Subject Support
- Chinese
- Mathematics
- English
- Computer Science

## Architecture & Design Principles

This project demonstrates **4 core software engineering pillars**:

### PILLAR 1: Encapsulated Structural Design
- **Data Hiding**: Private member variables in `SubjectScores` and `Student` classes
- **Access Control**: Read-only getters with `const` keyword for data integrity
- **Object Composition**: Student class contains SubjectScores object (Has-A relationship)

### PILLAR 2: Defensive Runtime Engineering
- **Input Validation**: Comprehensive numeric validation with range checking (0-100)
- **Buffer Management**: Proper handling of input stream failures and buffer clearing
- **Error Prevention**: Prevents crashes from invalid data entry

### PILLAR 3: Algorithmic Efficiency
- **Modular Sorting**: Decoupled comparison predicates for STL sort operations
- **Vector Operations**: Efficient data structure usage for scalability
- **Optimized Searches**: Filtered subset operations before sorting

### PILLAR 4: Transactional Integrity
- **Single Source of Truth**: Global constant `FILE_NAME` for database file management
- **Safe File Operations**: Explicit file handle management with proper resource cleanup
- **Data Persistence**: Delimited text format (pipe-separated) for reliable storage

## Project Structure

```
student-grade-system/
├── README.md                 # Project documentation
├── main.cpp                  # Complete application source code
└── student_grades.txt        # Data persistence file (auto-generated)
```

## Getting Started

### Prerequisites
- C++ compiler (C++11 or later)
  - GCC/G++ (Linux/Mac)
  - MSVC (Windows)
  - Clang
- Standard C++ Library (iostream, fstream, string, vector, algorithm, iomanip, limits)

### Installation & Compilation

**Linux/Mac:**
```bash
# Clone the repository
git clone https://github.com/hamayounhossaini1010-dotcom/student-grade-system.git
cd student-grade-system

# Compile the program
g++ -std=c++11 main.cpp -o grade_system

# Run the program
./grade_system
```

**Windows (Command Prompt):**
```bash
# Clone the repository
git clone https://github.com/hamayounhossaini1010-dotcom/student-grade-system.git
cd student-grade-system

# Compile using MSVC
cl main.cpp

# Run the program
grade_system.exe
```

## Usage Guide

### Main Menu Options

```
===================================================
        STUDENT GRADE MANAGEMENT CORE SYSTEM         
===================================================
  1. Grade Entry and Modification
  2. Grade Statistics by Class
  3. Grade Query Portal
  4. Grade Report Generation
  5. Explicit Save Matrix
  0. Secure Exit and Commit Saves
===================================================
```

### Option 1: Grade Entry and Modification
- Enter semester (e.g., 2026-Fall)
- Enter class name
- Enter student ID
- If student exists: Update their grades
- If student is new: Register new profile and enter grades
- Score range validation: 0-100

**Example:**
```
Enter Semester: 2026-Spring
Enter Class Name: Class-A
Enter Student ID: STU001
Enter Chinese Score (0-100): 85
Enter Math Score (0-100): 92
Enter English Score (0-100): 78
Enter Computer Score (0-100): 88
```

### Option 2: Grade Statistics by Class
- View all students in a specific class
- Choose sorting method:
  - **1**: Sort by Average Score (Highest First)
  - **2**: Sort by Name (A-Z)
- Displays: Rank, Name, Total Score, Average Score

### Option 3: Grade Query Portal
#### Submode 1: Search Specific Student
- Enter Student ID
- View official report card with all details

#### Submode 2: Failing Student Directory
- View all students with at least one failing subject (<60)
- Lists failed subjects for each student
- Shows class, ID, name, and failed subjects

### Option 4: Grade Report Generation
- Enter class name
- Generate comprehensive report with columns:
  - Student ID
  - Name
  - Subject scores (Chinese, Math, English, Computer)
  - Average score

### Option 5: Explicit Save Matrix
- Manually save all data to file
- Useful for backup purposes

### Option 0: Secure Exit
- Automatically saves all data
- Closes the application gracefully

## Data Storage Format

Student data is stored in `student_grades.txt` using pipe-delimited format:

```
Semester|StudentID|ClassName|Name|Chinese|Math|English|Computer
2026-Spring|STU001|Class-A|John Doe|85|92|78|88
2026-Spring|STU002|Class-A|Jane Smith|95|87|92|90
```

## Key Classes & Methods

### SubjectScores Class
- Private members: chinese, math, english, computer
- Methods: Getters (const) and setters for all scores

### Student Class
- Private members: semester, studentID, className, name, scores, totalScore, averageScore
- Key methods:
  - `calculateScores()`: Computes total and average
  - `updateGrades()`: Modifies student scores
  - `hasFailingSubject()`: Checks for any score < 60

### Core Functions
- `addOrUpdateGrade()`: Handle new/existing student entries
- `showClassStatistics()`: Generate class-level reports
- `queryGradeSystem()`: Student search and failing directory
- `generateClassReport()`: Export full class data
- `saveToFile()`/`loadFromFile()`: File persistence

## Input Validation

The system validates all numeric inputs:
- **Type checking**: Rejects non-numeric characters
- **Range checking**: Enforces 0-100 score limits
- **Buffer management**: Clears input stream to prevent crashes
- **Stream recovery**: Handles and recovers from input failures

## Error Handling

- Empty database checks
- Missing student record handling
- File I/O error management
- Invalid menu selection feedback
- Data parsing error recovery

## Future Enhancements

- Database migration to SQL/JSON format
- User authentication system
- Grade weighting by subject
- GPA calculation system
- Export to PDF/Excel reports
- Web interface frontend

## Contributing

Contributions are welcome! Please feel free to:
1. Fork the repository
2. Create a feature branch
3. Submit pull requests with improvements

## License

This project is a course design assignment. Please consult your institution's policies regarding academic work usage and redistribution.

## Author

**Hamayoun Hossaini** - hamayounhossaini1010-dotcom

## Support

For issues or questions, please open an issue on the GitHub repository.

---

**Last Updated**: 2026-05-29
