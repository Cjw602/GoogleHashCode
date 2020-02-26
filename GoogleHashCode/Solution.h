#pragma once

#include "stdafx.h"

using namespace std;

class Library;

const static bool BOOKWEIGHTING = true;
const static bool SCANWEIGHTING = true;
const static bool SIGNUPWEIGHTING = true;




class Solution
{
private:
	//TOTALS
	int totalLibs;
	int totalBooks;
	int totalDays;

	int totalScore;
	int libsToSign;
	string fileName;

	int currentTime;
	pair<int, Library*> signUpBuffer;


	vector<Library*> libraryList;
	vector<Book*> booksList;
	vector<Library*> chosenLibraries;




public:

	//Constructor
	Solution(string file);
	~Solution();


	//Methods
	void constructData(string fileName);
	vector<int> getNextLineSplit(ifstream* fp);
	bool createNewLibFromData(ifstream* fp);

	Library* getNextLibrary();

	int calcScore(vector<double> weightings);
	void resolveSignUps(vector<double> weightings);
	void resolveScans();

	void resetData();
	void writeToFile();

	//hueristic Methods
	void recalculateLibWeightings(vector<double> weightings);
	double getLibBookTotal(Library* lib);
	int getMaxSignUp();
	int getMaxRate();
	int getTotalBookValue();




public:
    int getTotalLibs() const;
    void setTotalLibs(int totalLibs);

    int getTotalBooks() const;
    void setTotalBooks(int totalBooks);

    int getTotalDays() const;
    void setTotalDays(int totalDays);

    int getTotalScore() const;
    void setTotalScore(int totalScore);

    int getLibsToSign() const;
    void setLibsToSign(int libsToSign);

    int getCurrentTime() const;
    void setCurrentTime(int currentTime);

    pair<int,Library*> getSignUpBuffer() const;
    void setSignUpBuffer(pair<int,Library*> signUpBuffer);

    vector<Library*> getLibraryList() const;
    void setLibraryList(vector<Library*> libraryList);

    vector<Book*> getBooksList() const;
    void setBooksList(vector<Book*> booksList);

    vector<Library*> getChosenLibraries() const;
    void setChosenLibraries(vector<Library*> chosenLibraries);

};

