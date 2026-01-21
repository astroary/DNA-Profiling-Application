//  *************************
//
//  Project 1 - DNA Profiling
//  Author - Aryansingh Chauhan
//  CS 251 - Spring 22 - Prof Pat Troy
//  Milestone 6 - For my creative component, I have taken an
//  input "run commands.txt".
//  When a user types this command, the code reads a file called
//  'commands.txt'.
//  This txt file contains a list of commands that are automatically
//  executed. User does not need to type in different commands like
//  search, process, load_db small.txt or load_dna 1.txt.
//  The input "run commands.txt" does all the work
//  by reading the file the commands.txt.
//  I have added the commands.txt file with my main.cpp
//  *************************
#include <iostream>
#include <fstream>
#include "ourvector.h"

using namespace std;

struct gene {
    ourvector<char> genes;
};

struct person {
    string name;
    ourvector<int> numbers;
};

void displayDb(ourvector <gene> &allGenes,
ourvector <person>& allPersons) {
// this function displays the content of the database.
// Parameter allGenes - all the genes from database.
// Parameter allPersons - contains all names of people
// from input files.

    if (allGenes.size() == 0) {
        cout << "No database loaded." << endl;
    } else {
        cout << "Database loaded: " << endl;
        for (int i = 0; i < allPersons.size(); i++) {
            cout << allPersons[i].name << " ";
            for (int j = 0; j < allPersons[i].numbers.size(); j++) {
                cout << allPersons[i].numbers[j] << " ";
            }
            cout << "\n";
        }
    }
}

void displayDna(gene &loadedSequence) {
// this function will output if there are any loaded
// sequences of the dna.
// parameter loadedSequence - contains all the gene sequences
// like AATG.
    if (loadedSequence.genes.size() == 0) {
        cout << endl << "No DNA loaded." << endl;
    } else {
        cout << endl << "DNA loaded: " << endl;
        for (int j = 0; j < loadedSequence.genes.size(); j++) {
            cout << loadedSequence.genes[j];
        }
        cout << "\n";
    }
}

void displayProcess(ourvector<int>& noOcc,
ourvector <gene>& allGenes) {
// this function will output the STR count if a DNA is processed.
// Parameter noOcc - contains the number of times a DNA string
// is consecutively after one other.
// Parameter allGenes - contains all the genes from
// input file.
    if (noOcc.size() == 0) {
        cout << endl << "No DNA has been processed.";
    } else {
        cout << endl << "DNA processed, STR counts: " << endl;
        for (int i = 0; i < noOcc.size(); i++) {
            // gene gene = allGenes[i];
            for (int j = 0; j < allGenes[i].genes.size(); j++) {
                cout << allGenes[i].genes[j];
            }
            cout << ": " << noOcc[i] << endl;
        }
    }
}

void display(ourvector <gene>& allGenes,
ourvector <person>& allPersons,
gene& loadedSequence,
ourvector<int>& noOcc) {
// function executed when user types in 'display'
    displayDb(allGenes, allPersons);
    displayDna(loadedSequence);
    displayProcess(noOcc, allGenes);
}

void loadDbGenes(ifstream &f, ourvector <gene> &allGenes) {
// this function will load all the genes from an input file
// the first parameter will read an input file.
// Parameter allGenes - contains all the genes from
// input file.
    string line1;
    f >> line1;  // reads first line
    // process first row
    int i = 0;
    while (line1[i] != ',')  // skip first element
        i++;
    i++;
    while (i < line1.length()) {
        gene gene;
        while (i < line1.length() && (line1[i] != ',')) {
            gene.genes.push_back(line1[i]);
            i++;
        }
        allGenes.push_back(gene);
        i++;
    }
}

void loadDbPersons(ifstream &f, ourvector <person> &allPersons) {
// this function will load the name of the person from
// input file, e.g -'Bob'
// the first parameter will read an input file.
// Parameter allPersons - contains all names of people
// from input files.
    string line;
    while (f >> line) {
        person person;
        // ourvector<int> numbers;
        int i = 0;
        string name;
        while (line[i] != ',') {  // skip first element
            name.push_back(line[i]);
            i++;
        }
        i++;
        person.name = name;
        while (i < line.length()) {
            int actualNumber = 0;
            while (i < line.length() && (line[i] != ',')) {
                actualNumber = actualNumber * 10 + line[i] - '0';
                i++;
            }
            person.numbers.push_back(actualNumber);
            i++;
        }
        // person.numbers = numbers;
        allPersons.push_back(person);
    }
}

void load(string filename, ourvector <gene> &allGenes,
ourvector <person> &allPersons) {
// function that loads the database.
// the first parameter will read an input file.
// Parameter allGenes - contains all the genes from
// input file.
// Parameter allPersons - contains all names of people
// from input files.
    ifstream f(filename);
    if (!f.is_open()) {  // to check if valid file is present
        cout << endl << "Error: unable to open '" << filename << "'";
        return;
    }
    if (allGenes.size() != 0){
        allGenes.clear();
    }
    if (allPersons.size() != 0){
        allPersons.clear();
    }

    loadDbGenes(f, allGenes);
    loadDbPersons(f, allPersons);
}

void loadDna(string filename, gene &loadedSequence) {
// this function is used to load the dna strands
// the first parameter will read an input file.
// Parameter loadedSequence - contains all the gene sequences
// like AATG.
    ifstream f(filename);  // reads file input
    string dna;
    cout << "Loading DNA...";
    if (!f.is_open()) {  // if no filename of input exists
        cout << endl << "Error: unable to open '" << filename << "'";
    } else {
        f >> dna;
        if (loadedSequence.genes.size() != 0){
          loadedSequence.genes.clear();
        }
        for (int i = 0; i < dna.length(); i++) {
            loadedSequence.genes.push_back(dna[i]);
        }
        // loadedSequence = dnaSequence;
    }
}

void processDna(gene& loadedSequence, ourvector<int> &noOcc,
ourvector <gene> &allGenes) {
// funtion that loads dna after command 'process' is read.
// Parameter loadedSequence - contains all the gene sequences
// like AATG.
// Parameter noOcc - contains the number of times a DNA string
// is consecutively after one other.
// Parameter allGenes - contains all the genes from
// input file.
    int ok;  // works as a flag
    for (int i = 0; i < allGenes.size(); i++) {
        int lmax = 0;
        int lc = 0;
        gene gene = allGenes[i];
        int size = allGenes[i].genes.size();
        for (int startIndex = 0; startIndex <= size; startIndex++) {
            int idx = startIndex;
            while (idx <= loadedSequence.genes.size() - size) {
                ok = 1;
                for (int k = 0; k < size; k++) {
                    if (loadedSequence.genes[idx + k] != gene.genes[k]) {
                        ok = 0;
                    }
                }
                if (ok == 1) {
                    lc++;
                    idx = idx + size;
                } else {
                    if (lmax < lc) {
                        lmax = lc;
                    }
                    lc = 0;
                    idx = idx + size;
                }
            }
        }
        noOcc.push_back(lmax);
    }
}

void process(gene &loadedSequence,
ourvector<int> &noOcc, ourvector <gene> &allGenes) {
// function used when command1 taken is 'process'.
// Parameter loadedSequence - contains all the gene sequences
// like AATG.
// Parameter noOcc - contains the number of times a DNA string
// is consecutively after one other.
// Parameter allGenes - contains all the genes from
// input file.
    if (allGenes.size() == 0) {
        cout << "No database loaded.";
    } else {
        if (loadedSequence.genes.size() == 0) {
            cout << "No DNA loaded.";
        } else {
            cout << "Processing DNA...";
            processDna(loadedSequence, noOcc, allGenes);
        }
    }
}

void searchDb(ourvector <person>& allPersons, ourvector<int> &noOcc) {
// function that will search if the DNA matches to some person
// when command1 entered is 'search'.
// Parameter allPersons - vector containing all names of people
// from input files.
// Parameter noOcc - contains the number of times a DNA string
// is consecutively after one other.
    string result = "";
    for (int i = 0; i < allPersons.size(); i++) {
        person person = allPersons[i];
        string name = person.name;
        int ok = 1;
        for (int j = 0; j < person.numbers.size(); j++) {
            if (person.numbers[j] != noOcc[j]) {
                ok = 0;
            }
        }
        if (ok == 1) {
            result = name;
        }
    }
    if (result == "") {
        cout << "Not found in database.";
    } else {
        cout << "Found in database! DNA matches: " << result;
    }
}

void search(ourvector <gene>& allGenes,
ourvector <person> &allPersons,
ourvector<int> &noOcc, gene& loadedSequence) {
// function when command1 entered is 'search'
// the first parameter is an ourvector that stores all gene types.
// the second parameter is an ourvector that stores names of
// all people.
// Parameter noOcc - contains the number of times a DNA string
// is consecutively after one other.
// Parameter loadedSequence - contains all the gene sequences
// like AATG.
    if (allGenes.size() == 0) {
        cout << "No database loaded.";
    } else {
        if (loadedSequence.genes.size() == 0) {
            cout << "No DNA loaded.";
        } else {
            if (noOcc.size() == 0) {
                cout << endl << "No DNA processed.";
            } else {
                cout << "Searching database..." << endl;
                searchDb(allPersons, noOcc);
            }
        }
    }
}

void commandsFromFile(string filename,
ourvector <gene>  & allGenes,
ourvector <person>& allPersons,
gene& loadedSequence,
ourvector<int>& noOcc) {
// function for creative component, will only work if
// command1 == run.
// Parameter 1 - is the name of the file
// Parameter allGenes - contains all the genes from
// input file.
// Parameter allPersons - vector containing all names of people
// from input files.
// Parameter loadedSequence - contains all the gene sequences
// like AATG.
// Parameter noOcc - contains the number of times a DNA string
// is consecutively after one other.
  ifstream f(filename);
  if (!f.is_open()) {  // to check if valid file is present
        cout << endl << "Error: unable to open '" << filename << "'";
        return;
    }
  string command1;
  string command2;
  while (f >> command1) {
        cout << "\nEnter command or # to exit: ";
        if (command1 == "#") {
            exit(0);
        } else {
            if (command1 == "display") {
                display(allGenes, allPersons, loadedSequence, noOcc);
            } else {
                if (command1 == "load_db") {
                    f >> command2;
                    cout << "Loading database...";
                    load(command2, allGenes, allPersons);
                } else {
                    if (command1 == "load_dna") {
                        f >> command2;
                        loadDna(command2, loadedSequence);
                    } else {
                        if (command1 == "process") {
                            process(loadedSequence, noOcc, allGenes);
                        } else {
                            if (command1 == "search") {
                                search(allGenes,
                                allPersons, noOcc,
                                loadedSequence);
                            }
                          }
                        }
                    }
                }
            }
        }
}

int main() {
    ourvector <gene> allGenes;
    // ourvector that stores all the genes
    ourvector <person> allPersons;
    // ourvector that stores name of people from files
    gene loadedSequence;
    // store loaded sequence of DNA
    ourvector<int> noOcc;
    // ourvector that stores the max  #occurances for one kind of gene 
    string command1;
    string command2;
    cout << "Welcome to the DNA Profiling Application.";
    while (true) {
        cout << "\nEnter command or # to exit: ";
        cin >> command1;
        if (command1 == "#") {
            return 0;
        } else {
            if (command1 == "display") {
                display(allGenes, allPersons, loadedSequence, noOcc);
            } else {
                if (command1 == "load_db") {
                    cin >> command2;
                    cout << "Loading database...";
                    load(command2, allGenes, allPersons);
                } else {
                    if (command1 == "load_dna") {
                        cin >> command2;
                        loadDna(command2, loadedSequence);
                    } else {
                        if (command1 == "process") {
                            process(loadedSequence, noOcc, allGenes);
                        } else {
                            if (command1 == "search") {
                                search(allGenes,
                                allPersons, noOcc,
                                loadedSequence);
                            }
                            else{
                              if (command1 == "run"){
                                  cin >> command2;
                                  commandsFromFile(command2, allGenes,
                                  allPersons,
                                  loadedSequence,
                                  noOcc);
                              }
                            }
                        }
                    }
                }
            }
        }
    }
}
// end of int main()
