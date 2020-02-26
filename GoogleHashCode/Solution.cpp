#include "Solution.h"

using namespace std;




//static vector<double> weightings; //= vector<double>({ 1, 1, 1 });



Solution::Solution(string file)
{

    constructData(file);

    fileName = file;
    currentTime = 0;
    signUpBuffer = pair<int, Library*>(0, NULL);
    totalScore = 0;
    libsToSign = totalLibs;
    srand(static_cast <unsigned> (time(0)));

    

    



}

Solution::~Solution()
{

}

void Solution::constructData(string fileName)
{
    vector<int> lineData;
    ifstream* myFile = new ifstream();
    myFile->open(fileName);

    lineData = getNextLineSplit(myFile);

    totalBooks = lineData.at(0);
    totalLibs = lineData.at(1);
    totalDays = lineData.at(2);

    lineData = getNextLineSplit(myFile);
    for (int bookValue : lineData)
    {
        booksList.push_back(new Book(booksList.size(), bookValue));
        cout << "New Book Created!\n";
    }

    cout << "";

    while (createNewLibFromData(myFile))
    {
        cout << "New Library Created!\n";
    }


    
}

vector<int> Solution::getNextLineSplit(ifstream* fp)
{
    string myText;
    stringstream ss;
    string buf;
    vector<int> tokens;

    //GetTotals
    getline(*fp, myText);
    ss.str(myText);

    while (ss >> buf)
        tokens.push_back(stoi(buf));

    return tokens;

}

bool Solution::createNewLibFromData(ifstream* fp)
{
    vector<int> libData = getNextLineSplit(fp);
    vector<int> libBookData = getNextLineSplit(fp);

    if (libData.size() > 0)
    {

        Library* newLib = new Library(libraryList.size(), libData.at(1), libData.at(2), vector<Book*>());
        for (int bookIndex : libBookData)
        {
            newLib->addBook(booksList.at(bookIndex));
        }

        libraryList.push_back(newLib);
        return true;

    }
    else
    {
        return false;
    }

}

Library* Solution::getNextLibrary()
{
    vector<Library*> availableLibs;
    double totalCumlativeWeighting = 0;
    
    for (Library* lib : libraryList)
    {
        if (!lib->getChosen())
        {
            availableLibs.push_back(lib);
            totalCumlativeWeighting += lib->getWeight();
        }

    }

    if (availableLibs.size() > 0)
    {
        double weightMarker = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / totalCumlativeWeighting));
        double cumlativeMarker = 0;

        for (Library* lib : availableLibs)
        {
            cumlativeMarker += lib->getWeight();
            if (cumlativeMarker > weightMarker)
            {
                return lib;
            }
        }
    }


    return NULL;
}

int Solution::calcScore(vector<double> weightings)
{
    //Calculates Score
	recalculateLibWeightings(weightings);
    while (currentTime < totalDays)
    {
        //cout << "                               ------------ Day " << currentTime << " ------------\n";
        resolveSignUps(weightings);
        resolveScans();



        currentTime++;

    }

    //cout << "Finished with Score: " << totalScore << "\n";


    return totalScore;

}

void Solution::resolveSignUps(vector<double> weightings)
{
    //deal with sign ups and sign up decrement
    if (signUpBuffer.first == 0)
    {
		recalculateLibWeightings(weightings);
        if (libsToSign >= 0)
        {
            Library* nextLibToSign = getNextLibrary();
            if (!signUpBuffer.second == NULL)
            {
                chosenLibraries.push_back(signUpBuffer.second);
                //cout << "Signed up Lib[" << signUpBuffer.second->getID() << "]\n";
            }

            if (!nextLibToSign == NULL)
            {

                signUpBuffer.second = nextLibToSign;
                signUpBuffer.first = nextLibToSign->getSignUpTime();
                nextLibToSign->setChosen(true);
                libsToSign--;
            }
        }
    }

    signUpBuffer.first--;

}

void Solution::resolveScans()
{
    //this is bad oop
    for (Library* scannedLib : chosenLibraries)
    {
        for (int scan = 0; scan < scannedLib->getScanRate(); scan++)
        {
            Book* nextBook = scannedLib->getNextBestBook();
            if (!nextBook == NULL)
            {
                totalScore += nextBook->getBookScore();

                nextBook->setChosen(true);
                scannedLib->markAsScanned(nextBook);

                //cout << "Lib[" << scannedLib->getID() << "] scanned Book[" << nextBook->getID() << "]\n";

            }



        }


    }




}

void Solution::resetData()
{
    for (Book* book : booksList)
    {
        book->setChosen(false);
    }

    for (Library* lib : libraryList)
    {
        lib->reset();
    }
    
}

void Solution::writeToFile()
{
    
    ofstream outputfile;
    outputfile.open(fileName.insert(fileName.size() - 4, "_solution"));
    int libsCounted = totalLibs - libsToSign - 1;

    for (Library* lib : chosenLibraries)
    {
        vector<Book*> libBooks = lib->getLocalBookScans();
        if (!(libBooks.size() > 0))
        {
            libsCounted--;
            cout << "///////LIB DISCARDED///////////////\n";
        }
    }

    outputfile << libsCounted << std::endl;
    for (Library* lib : chosenLibraries)
    {
        vector<Book*> libBooks = lib->getLocalBookScans();
        if (libBooks.size() > 0)
        {
            outputfile << lib->getID() << " " << libBooks.size() << std::endl;
            for (int bookIndex = 0; bookIndex < libBooks.size(); bookIndex++)
            {
                outputfile << libBooks.at(bookIndex)->getID();
                if (bookIndex == (libBooks.size()-1))
                {
                    outputfile << std::endl;
                }
                else
                {
                    outputfile << " ";
                }
            }

        }
        else
        {
            cout << "BLEEP WARNING BLEEP";
        }

    }

    outputfile.close();
    cout << "                       Write Complete Score: " << totalScore << "\n";
    



    

}


int Solution::getTotalBookValue()
{
    int total = 0;

    for (Library* lib : libraryList)
    {
        if (!lib->getChosen())
        {
            for (Book* book : lib->getBooks())
            {
                if (!book->getChosen())
                {
                    total += book->getBookScore();
                }
            }
        }
    }

    return total;
}



int Solution::getMaxRate()
{
    int max = 0;

    for (Library* lib : libraryList)
    {
        if (!lib->getChosen())
        {
            if (lib->getScanRate() > max)
            {
                max = lib->getScanRate();
            }
        }
    }

    return max;
}

int Solution::getMaxSignUp()
{
    int max = 0;

    for (Library* lib : libraryList)
    {
        if (!lib->getChosen())
        {
            if (lib->getSignUpTime() > max)
            {
                max = lib->getSignUpTime();
            }
        }
    }

    return max;
}

double Solution::getLibBookTotal(Library* lib)
{
    int libTotal = 0;
    for (Book* book : lib->getBooks())
    {
        if (!book->getChosen())
        {
            libTotal += book->getBookScore();
        }

    }

    return libTotal;
}

void Solution::recalculateLibWeightings(vector<double> weightings)
{
    int weightsUsed = 0;
    
    if (BOOKWEIGHTING)
    {
        weightsUsed += 1;
    }
    if (SCANWEIGHTING)
    {
        weightsUsed += 1;
    }
    if (SIGNUPWEIGHTING)
    {
        weightsUsed += 1;
    }

    int totalBV = getTotalBookValue();
    int maxRate = getMaxRate();
    int maxSign = getMaxSignUp();


    for (Library* lib : libraryList)
    {
        if (!lib->getChosen())
        {

            double totalHueristic = 0;
            if (BOOKWEIGHTING)
            {
                double tempVal = 0;
                tempVal = (double)getLibBookTotal(lib) / totalBV;
                totalHueristic += tempVal * weightings.at(0);
            }
            if (SCANWEIGHTING)
            {
                double tempVal = 0;
                tempVal = (double)lib->getScanRate() / maxRate;
                totalHueristic += tempVal * weightings.at(1);
            }
            if (SIGNUPWEIGHTING)
            {
                double tempVal = 0;
                tempVal = (double)lib->getSignUpTime() / maxSign;
                tempVal = 1 - tempVal;
                totalHueristic += tempVal * weightings.at(2);
            }

            totalHueristic = totalHueristic / weightsUsed;

            //change this choose algo
            totalHueristic = powl(totalHueristic, 8);
            
            
            lib->setWeight(totalHueristic);
        }

    }




}






int Solution::getTotalLibs() const
{
    return totalLibs;
}

void Solution::setTotalLibs(int totalLibs)
{
    this->totalLibs = totalLibs;
}

int Solution::getTotalBooks() const
{
    return totalBooks;
}

void Solution::setTotalBooks(int totalBooks)
{
    this->totalBooks = totalBooks;
}

int Solution::getTotalDays() const
{
    return totalDays;
}

void Solution::setTotalDays(int totalDays)
{
    this->totalDays = totalDays;
}

int Solution::getTotalScore() const
{
    return totalScore;
}

void Solution::setTotalScore(int totalScore)
{
    this->totalScore = totalScore;
}

int Solution::getLibsToSign() const
{
    return libsToSign;
}

void Solution::setLibsToSign(int libsToSign)
{
    this->libsToSign = libsToSign;
}

int Solution::getCurrentTime() const
{
    return currentTime;
}

void Solution::setCurrentTime(int currentTime)
{
    this->currentTime = currentTime;
}

pair<int,Library*> Solution::getSignUpBuffer() const
{
    return signUpBuffer;
}

void Solution::setSignUpBuffer(pair<int,Library*> signUpBuffer)
{
    this->signUpBuffer = signUpBuffer;
}

vector<Library*> Solution::getLibraryList() const
{
    return libraryList;
}

void Solution::setLibraryList(vector<Library*> libraryList)
{
    this->libraryList = libraryList;
}

vector<Book*> Solution::getBooksList() const
{
    return booksList;
}

void Solution::setBooksList(vector<Book*> booksList)
{
    this->booksList = booksList;
}

vector<Library*> Solution::getChosenLibraries() const
{
    return chosenLibraries;
}

void Solution::setChosenLibraries(vector<Library*> chosenLibraries)
{
    this->chosenLibraries = chosenLibraries;
}

