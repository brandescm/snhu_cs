#include <Python.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;
//test

void callProcedure(string proc);
//int callIntFunc(string proc, int param);
int callIntFunc(string proc, string param);
void ShowMenu();
void MenuHandler(int selection);
void CreateHistogram();
void ClearScreen();

string output_file = "frequency.dat";

int main()
{
	string selectionStr;
	int menuSelection;
	callProcedure("CreateDatFile");
	ClearScreen();

	while(true) {
		ShowMenu();
		getline(cin, selectionStr);
		ClearScreen();
		try {
			menuSelection = stoi(selectionStr);
			if (menuSelection == 4) {
				return 0;
			}
			MenuHandler(menuSelection);
		}
		catch(...) {
			MenuHandler(0);
		}

	}
}

/*
MenuHandler(): Handle menu selection options

input: int selection
return: None

*/
void MenuHandler(int selection) {
	string item;
	int result;
	switch (selection) {
	case 1:
		cout << "Printing List of Items and Quatity" << endl;
		callProcedure("PrintList");
		break;

	case 2:
		cout << "Enter Item to Display" << endl;
		getline(cin, item);
		result = callIntFunc("GetItem", item);
		if (result == 0) {
			cout << "Not a valid item." << endl;
			cout << endl;
		}
		else {
			cout << item << " was/were purchased " << result << " times today." << endl;
			cout << endl;
		}
		break;

	case 3:
		cout << "Displaying Histrogram......" << endl;
		cout << string('*', 30) << endl;
		CreateHistogram();
		break;

	default:
		cout << "Enter valid input!" << endl;
		cout << endl;
	}
}

void CreateHistogram() {
	string line;
	string name;
	int qty;
	ifstream fileIn(output_file);
	while (getline(fileIn, line)) {
		istringstream iss(line);
		iss >> name;
		iss >> qty;
		cout << name << " " << string(qty, '#') << endl;
	}
}
/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print to console
Return:
	None
*/
void callProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("list_functions");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print the item and quantity of today's sales to console.:
		Item	Qty
		Bread	6
Return:
	0 is returned for valid item
	1 is returned for invalid item
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
	pName = PyUnicode_FromString((char*)"list_functions");
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
ShowMenu(): Display base user option menu

input: None
return: None

*/
void ShowMenu() {
	cout << string('*', 30) << endl;
	cout << "1. Display List of Items with Quantity" << endl;
	cout << "2. Display Specific Item with Quantity" << endl;
	cout << "3. Display Histogram of All Items" << endl;
	cout << "4. Exit" << endl;
	cout << "Enter your selection as a number 1, 2 , 3, or 4" << endl;

}

/*
ClearScreen() : Clears screen of old data, Unix and Windows valid

input : None
return : None

*/
void ClearScreen() {
	system("cls");
	//cout << "\x1B[2J\x1B[H" << endl;
}
