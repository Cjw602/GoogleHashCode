#include "Book.h"

Book::Book(int Id, int score)
{
	ID = Id;
	bookScore = score;
	chosen = false;
}
int Book::getID() const
{
    return ID;
}

void Book::setID(int ID)
{
    this->ID = ID;
}

int Book::getBookScore() const
{
    return bookScore;
}

void Book::setBookScore(int bookScore)
{
    this->bookScore = bookScore;
}

bool Book::getChosen() const
{
    return chosen;
}

void Book::setChosen(bool chosen)
{
    this->chosen = chosen;
}

