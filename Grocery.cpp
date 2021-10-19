/**
* Brennan Reed
* This project is a grocery list tracker that creates a list of items purchased,
* how often they're purchased, and creates a visual for said information for each
* day for the grocery store - all utilizing c++ and python code
* 10/17/21
**/
#include "Grocery.h"

using namespace std;

char sent = 'a';

/*
* function calls a function from python code to execute
* requires string parameter of Python function name, such as fullLIst
* returns nothing, but displays Python results pertinent to said function
*/
void callProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
* function calls Python function to execute
* requires a pair of string parameters, one function name and one corresponding
* variable to be used in the python function (such as singleItem, itemName)
* returns key value pair from dictionary created in python, so effectively string and int
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
* function is the same as last except for with string and int params for overloading
* requires one string (Python function name) and one int parameter
* returns int result of function
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

/**
* function tests first character for str or int
* input validation for itemName that is needed to feed to python function
* parameters required are string str and int n
* returns true if string is valid (does not start with number) or false if
* invalid (contains characters besides a-z (upper and lower) and -)
**/
bool isValid(string str, int n) {

	// If first character is invalid
	if (!((str[0] >= 'a' && str[0] <= 'z')
		|| (str[0] >= 'A' && str[0] <= 'Z')
		|| str[0] == '_'))
		return false;

	// Traverse the string for the rest of the characters
	for (int i = 1; i < str.length(); i++) {
		if (!((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| str[i] == '_'))
			return false;
	}

	// String is a valid identifier
	return true;
}

/**
* function that opens .dat file written by a python function
* no parameters required
* returns string and int as the item and a histogram based on int value
**/
int openDat() {

	std::ifstream myFile("frequency.dat");
	std::string line;

	// contains input validation and loop that adds asterisk for the value
	// of the int (i.e. 8 asterisks printed for a value of 8)
	while (std::getline(myFile, line)) {
		std::stringstream iss(line);
		string a;
		int b;
		if (!(iss >> a >> b)) {
			break;
		}
		else {
			int i = 0;
			cout << a;
			cout << " ";
			for (i = 0; i < b; ++i) {
				cout << "*";
			}
			cout << endl;
		}
	}
}

/**
* Contains options menu
* No parameters required
* displays options users can select from, returns nothing
**/
void displayMenu() {
	cout << "1: List of All Items Purchased and Quantities of Each" << endl;
	cout << "2: Search for Specific Item Purchase Quantities" << endl;
	cout << "3: Graphic for All Items Purchased/Quantities" << endl;
	cout << "4: Exit" << endl;
	cout << "Enter your selection as a number 1, 2, 3, or 4." << endl;
}

/**
* Contains loop and switch that allow user to use options from menu
* No parameters required
* calls functions that send code to python for calculations, which print results
**/
void useMenu() {
	string itemName;
	int n = itemName.length();
	int userInput = 0;
	int i;

	// loop that repeats unless 4 selected to quit
	// contains switch statement matching three options users have
	do {
		// initial input from user and prompted for after each loop
		cin >> userInput;
		switch (userInput) {
		case 1:
			callProcedure("fullList");	
			cout << endl;
			displayMenu();
			break;

		case 2:
			// additional user input needed which is itemName
			// which gets sent to function in Python
			cout << "Enter the item: " << endl;
			cin >> itemName;
			if (isValid(itemName, n)) {
				cout << "Number of " << itemName << " purchased: ";
				cout << callIntFunc("singleItem", itemName) << endl;
				cout << endl;
			}
			
			// input validation if itemName has numbers/invalid characters
			else {
				cout << "Invalid input - please enter an item name.  Make a new selection." << endl;
				cout << endl;
			}
			displayMenu();
			break;
		
			// calls function for histogram
		case 3:
			callProcedure("itemGraph");	
			cout << endl;
			cout << "******* Items Purchased Histogram *******" << endl;
			openDat();	// calls function that opens .dat file and outputs the data appropriately
			cout << endl;
			displayMenu();
			break;

			// Displays quit message for user to validate that they selected 4 aka exit
		case 4:
			cout << "Thanks for using our product! Goodbye." << endl;
			sent = 'q';
			break;

			// default case contains text explaining error to user for invalid input and restarts loop
		default:
			cout << "Invalid selection - please enter 1, 2, 3, or 4" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
	} while (userInput != 4);
}

/**
* main function to run do while loop for program
* no parameters needed
* calls menus which have other functions in those as needed
* returns nothing
**/
int main() {
	do {
		displayMenu();
		useMenu();
	} while (sent != 'q');
}
