#pragma once


#include "stdafx.h"

class Book
{
private: 
	int ID;
	int bookScore;
	bool chosen;



public :
	
	Book(int Id, int score);






public:
    int getID() const;
    void setID(int ID);

    int getBookScore() const;
    void setBookScore(int bookScore);

    bool getChosen() const;
    void setChosen(bool chosen);

};

