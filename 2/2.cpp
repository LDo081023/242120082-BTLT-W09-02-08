#include <iostream>
#include <fstream>
using namespace std;


struct Monomial {
    int deg;
    float coef;
};


void readPolynomialsFromFile(const char* name) {
    ifstream File(name, ios::binary);
    if (!File) {
        cout << "Open failed: " << name << endl;
        return;
    }
    int numTerms;
    //reinterpret_cast<char*>(&numTerms) is a type cast that converts the address of numTerms(*int) to a char (GG)
    //reinterpret_cast<char*>(&numTerms) converts the address of numTerms(*int) to a *char (GG)
    while (File.read(reinterpret_cast<char*>(&numTerms), sizeof(numTerms))) {
        Monomial* terms = new Monomial[numTerms];

        for (int i = 0; i < numTerms; i++) {
            File.read(reinterpret_cast<char*>(&terms[i].deg), sizeof(int));
            File.read(reinterpret_cast<char*>(&terms[i].coef), sizeof(float));
        }

        int maxDegree = -1;
        for (int i = 0; i < numTerms; i++) {
            if (terms[i].deg >= maxDegree) {
                maxDegree = terms[i].deg;
            }
        }
        cout << "Max Degree: " << maxDegree << endl;
        for (int i = 0; i < numTerms; i++) {
            cout << "Degree: " << terms[i].deg << ", coefficient: " << terms[i].coef << endl;
        }

        delete[] terms;
    }
    File.close();
}
void writeLargestDegreePolynomialsToFile(const char* name) {
    ifstream File("POLY.BIN", ios::binary);
    if (!File) {
		cout << "Can't open the file to read." << endl;
        return;
    }
    ofstream outFile(name, ios::binary);
    if (!outFile) {
        cout << "Can't open the output file." << endl;
        return;
    }
	int lastDegree = -1;
    int maxDegree = -1;
    int numTerms;
    while (File.read(reinterpret_cast<char*>(&numTerms), sizeof(numTerms))) {
        Monomial* terms = new Monomial[numTerms];

        for (int i = 0; i < numTerms; i++) {
            File.read(reinterpret_cast<char*>(&terms[i].deg), sizeof(int));
            File.read(reinterpret_cast<char*>(&terms[i].coef), sizeof(float));
        }

        int maxDegree = -1;
        for (int i = 0; i < numTerms; i++) {
            if (terms[i].deg >= maxDegree) {
                maxDegree = terms[i].deg;
            }
        }
        lastDegree = maxDegree;
    }
    for (int i = 0; i <= numTerms; i++) {
		outFile << lastDegree;
    }
    for (int i = 0; i <= numTerms; i++) {
        File >> lastDegree;
    }
    File.close();
    outFile.close();
}
int main() {
    readPolynomialsFromFile("POLY.BIN");
	writeLargestDegreePolynomialsToFile("POLY2.BIN");
    return 0;
}




