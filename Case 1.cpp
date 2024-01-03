#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

const int numQuestions = 20;
const int numStudents = 20;

int readFile(string[][numQuestions], string[], char[], char[]);
int compareAns(int, char[][numQuestions], char[], bool[]);
void printMissQuestion(int, char[][numQuestions], char[], bool[]);
void printReport(string[], string[], int[], char[]);

int main(){
	string name[numStudents], 				// Student name read from file
	       matricNumber[numStudents];			// Student ID read from file
	char studentAns[numStudents][numQuestions], 		// Student answer read from file
	     correctAns[numQuestions], 				// Correct answer read from file
	     grade[numStudents];				// Grade computed of each student
	bool correctedAns[numQuestions];			// Boolen that stores the correct or false of each question for a student
	int percentage[numStudents];				// Percentage computed of each student
	int studentNum,						// Number of students in the file
	    studentIndex = -1,					// Location of the student in an array
	    missNum;						// Number of missed question of a student

	studentNum = readFile(name, matricNumber, studentAns, correctAns);

	// Find percentage and grade
	for (int i = 0; i < numStudents; i++){
		missNum = compareAns(studentIndex, studentAns, correctAns, correctedAns);
		percentage[i] = (numQuestions - missNum) / static_cast<double>(QUES_NUM) * 100;
		if(percentage >= 80)
			grade[i] = 'A';
		else if(percentage >= 70)
			grade[i] = 'B';
		else if(percentage >= 60)
			grade[i] = 'C';
		else
			grade[i]  = 'F';
	}

	printReport(name, matricNumber, percentage, grade);

	// Get Matric Number and find student index
	do{
		cout << "Enter the student ID: ";
		cin >> studentID;
		for (int i = 0; i < studentNum; i++){
			if (matricNumber[i] == studentID){
				studentIndex = i;
				break;
			}
		}
		if (studentIndex == -1){
			cout << "The ID does not exist in the database\n";
		}
	}
	while(studentIndex == -1);

	// Print Report
	cout
	<< "EXAM RESULT\n"
	<< "Name: " << name[studentIndex] << endl
	<< "Student ID: " << matricNumber[studentIndex] << endl
	<< "Number of questions missed: " << compareAns(studentIndex, studentAns, correctAns, correctedAns) << endl
	<< printMissQuestion(studentIndex, studentAns, correctAns, correctedAns)
	<< "Percentage: " << percentage[studentIndex] << "%, GRED: " << grade[studentIndex];

	return 0;
}

void readFile(string name[], string matricNum[], char studentAns[][numQuestions], char correctAns[])
{
	ifstream inFile;
	inFile.open("StudentAnswer.dat");

	if (!inFile){
		cerr << "ERROR. File not found.\n";
		exit(1);
    	}

	for (int i = 0; i < numStudents; ++i)
	{
		inFile >> name[i] >> matricNum[i];
		
		for (int j = 0; j < numQuestions; ++j)
		    {
		    	inFile >> studentAns[i][j];
		    }
	}
	
	inFile.close();

	ifstream inFile2;
	inFile2.open("CorrectAns.txt");

    	if(!inFile2)
	{
	        cerr << "Error. File not found.\n";
	        exit(1);
	}

	for (int j = 0; j < numQuestions; ++j)
	{
		inFile2 >> correctAns[j];
	}

    	inFile2.close()
}
