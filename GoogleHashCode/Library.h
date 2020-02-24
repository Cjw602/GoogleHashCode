#pragma once

#include "stdafx.h"

using namespace std;


class Book;

class Library
{
private:

	int ID;
	vector<Book*> books;
	int signUpTime;
	int scanRate;
	bool chosen;
	double weight;
	vector<Book*> localBookScans;

	

public:

	//constructors
	Library(int id, int sTime, int sRate, vector<Book*> collection);


	//Methods
	void addBook(Book* newBook);
	void markAsScanned(Book* scannedBook);
	Book* getNextBestBook();
	void reset();
	

	


public:
    int getID() const;
    void setID(int ID);

    vector<Book*> getBooks() const;
    void setBooks(vector<Book*> books);

    int getSignUpTime() const;
    void setSignUpTime(int signUpTime);

    int getScanRate() const;
    void setScanRate(int scanRate);

    bool getChosen() const;
    void setChosen(bool chosen);

    double getWeight() const;
    void setWeight(double weight);

    vector<Book*> getLocalBookScans() const;
    void setLocalBookScans(vector<Book*> localBookScans);

};

