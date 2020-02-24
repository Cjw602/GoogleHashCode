#include "Library.h"

Library::Library(int id, int sTime, int sRate, vector<Book*> collection)
{
	ID = id;
	books = collection;
	signUpTime = sTime;
	scanRate = sRate;
	chosen = false;
	weight = 0;
}

void Library::addBook(Book* newBook)
{
	books.push_back(newBook);
}

void Library::markAsScanned(Book* scannedBook)
{
    localBookScans.push_back(scannedBook);

}

Book* Library::getNextBestBook()
{
    int max = 0;
    Book* bestBook = NULL;
    for (Book* book : books)
    {
        if (!book->getChosen())
        {
            if (book->getBookScore() > max)
            {
                max = book->getBookScore();
                bestBook = book;
            }
        }
    }

    if (max == 0)
    {
        return NULL;
    }
    else
    {
        return bestBook;
    }

}

void Library::reset()
{
    chosen = false;
    localBookScans.clear();
}



int Library::getID() const
{
    return ID;
}

void Library::setID(int ID)
{
    this->ID = ID;
}

vector<Book*> Library::getBooks() const
{
    return books;
}

void Library::setBooks(vector<Book*> books)
{
    this->books = books;
}

int Library::getSignUpTime() const
{
    return signUpTime;
}

void Library::setSignUpTime(int signUpTime)
{
    this->signUpTime = signUpTime;
}

int Library::getScanRate() const
{
    return scanRate;
}

void Library::setScanRate(int scanRate)
{
    this->scanRate = scanRate;
}

bool Library::getChosen() const
{
    return chosen;
}

void Library::setChosen(bool chosen)
{
    this->chosen = chosen;
}

double Library::getWeight() const
{
    return weight;
}

void Library::setWeight(double weight)
{
    this->weight = weight;
}

vector<Book*> Library::getLocalBookScans() const
{
    return localBookScans;
}

void Library::setLocalBookScans(vector<Book*> localBookScans)
{
    this->localBookScans = localBookScans;
}

