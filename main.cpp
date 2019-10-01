/*
 KeLynne Lee
 UTILIZE STL LIST CONTAINERS AND ITERATORS
 TO CREATE AIRPORT FILE
 */
#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iterator>
#include <algorithm>
#include <vector>
#include <list>
#include <iomanip>
#include <string.h>
#include <stdlib.h>
#include <curses.h>

using namespace std;

list<string> split(const string& s, const string& delim);
bool compare(string, string);
void displayNations(list<string> &list);
void searchBy(list<string> &list);
void searchFOR(list<string> &list);
void deletePORT(list<string> &list);


list<string> nation;//stores nation; for sorted display and sortBY Alpha
list<string> details;//stores "port name - city - nation - code"
list<string>::iterator it;//iterator for all details
list<string>::iterator aCode;//iterator to validate Port Code

int main()
{
    string fileLine;
    ifstream inputFile;
    inputFile.open("airports.dat");
    if (!inputFile)
    {
        cout << "File Access Error!";
        return 0;
    }
    cout << "Reading File ..." << endl;
    while (!inputFile.eof())
    {
        list<string> line = split(fileLine, ",");
        getline(inputFile, fileLine);
        
        it = line.begin();
        
        aCode = line.begin();
        
        if (line.size() >= 3)
        {
            advance(aCode, 4);
            
            if ((*aCode).size() == 3) {
                //store port name
                advance(it, 1);
                details.push_back(*it);
                
                // store city
                advance(it, 1);
                details.push_back(*it);
                
                //store nation
                advance(it, 1);
                nation.push_back(*it);
                details.push_back(*it);
                
                //store code
                advance(it, 1);
                details.push_back(*it);
            }
        }
    }
    
    string menu_options = "\nMenu Options: \n \t\t\t 1) Display List \n"
    "\n \t\t\t 2) Search Records \n"
    "\n \t\t\t 3) Delete a Record \n"
    "\n \t\t\t X) Exit\n";
    
    cout << "\nVALUES LOADED" << endl;
    system("CLS");
    
    cout << "\t\t\t WELCOME TO THE AIRPORT RECORD PROGRAM" << endl;
    cout << menu_options;
    nation.sort();
    nation.unique(compare);
    
    cout << "SELECT: ";
    char a;
    cin >> a;
    
    do
    {
        if (a == '1') {
            cout << "DISPLAYING SORTED NATION LIST: " << endl;
            displayNations(nation);
        }
        
        else if (a == '2') {
            searchBy(nation);
            searchFOR(details);
        }
        
        else if (a == '3') {
            deletePORT(details);
            cout << "\nRECORD DELETED!!!" << endl;
        }
        
        
        cout << menu_options;
        cout << "SELECT: ";
        cin >> a;
        
        
        
    } while (a != 'x');
    
    cout << "GOODBYE" << endl;
    return 0;
}

//function to store data file in linked list
list<string> split(const string& s, const string& delim)
{
    const bool keep_empty = true;
    list<string> result;
    
    if (delim.empty())
    {
        result.push_back(s);
        return result;
    }
    
    string::const_iterator substart = s.begin(), subend;
    
    while (true)
    {
        subend = search(substart, s.end(), delim.begin(), delim.end());
        string temp(substart, subend);
        if (keep_empty || !temp.empty())
        {
            result.push_back(temp);
        }
        if (subend == s.end())
        {
            break;
        }
        substart = subend + delim.size();
    }
    
    return result;
}

//function to compare strings
bool compare(string a, string b)
{
    return((string)a == (string)b);
}

//function displays list of strings through iteration
void displayNations(list<string> &list) {
    for (it = list.begin(); it != list.end(); it++) {
        cout << " " << *it << endl;
    }
    cout << " ";
}

//searches list for strings with matching first character
void searchBy(list<string> &list) {
    //clear screen
    printf("\033[2J\033[1;1H");
    cout << "\nSEARCH FOR A NATION BY FIRST LETTER; USE UPPERCASE " << endl;
    cout << "SELECT: ";
    
    char choice;
    cin >> choice;
    cout << endl;
    
    for (it = list.begin(); it != list.end(); it++) {
        if (!(*it).empty() && (*it)[0] == choice)
        {
            cout << *it << endl;
            
        }
    }
}

//searches list for specific string using compare function, displays through iteration
void searchFOR(list<string> &list) {
    cout << " \nSELECT A NATION TO VIEW AIRPORT CODES FOR; case sensitive" << endl;
    cout << "SELECT: ";
    string name;
    cin >> name;
    cout << endl;
    cout << "NATION \tCITY \tPORT-NAME \tPORT-CODE" << endl;
    cout << endl;
    
    for (it = list.begin(); it != list.end(); it++) {
        if (compare(name, *it)) {
            //display country
            cout << *it << " ";
            
            //display city
            cout << "\t";
            auto ax = prev(it, 1);
            cout << *ax << " ";
            
            //display airport name
            cout << "\t";
            auto bx = prev(it, 2);
            cout << *bx << " ";
            
            //display airport code
            cout << "\t";
            auto cx = next(it, 1);
            cout << *cx << " ";
            cout << endl;
        }
    }
}

//search list for specific record, match user entry, delete the entire line if matched
void deletePORT(list<string> &list) {
    cout << "\nTO DELETE AN AIRPORT, ENTER THE PORT CODE" << endl;
    cout << "SELECT: ";
    string code;
    cin >> code;
    
    for (it = list.begin(); it != list.end(); it++)
    {
        if (compare(code, *it))
        {
            cout << "Searching for " << *it << " to delete..." << endl;
            
            it = details.erase(it);
            auto dx = prev(it, 3);
            dx = details.erase(dx);
            auto ex = prev(it, 2);
            ex = details.erase(ex);
            auto fx = prev(it, 1);
            fx = details.erase(fx);
            
            break;
        }
    }
    //clear screen
    printf("\033[2J\033[1;1H");
}

