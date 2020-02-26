// GoogleHashCode.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "stdafx.h"

using namespace std;

const static int passes = 100;
const static int samples = 20;
const static int microSamples = 3;
static double sigma = 1; // may be too big

static vector<double> weightings = vector<double>({ 0, 0, 0 });



int optimize(string file)
{
	int maxScore = 0;
	Solution* bestSolution = NULL;
	vector<double> weightings = vector<double>({ 0, 0, 0 });

	default_random_engine generator(static_cast <unsigned> (time(0)));
	normal_distribution<double> normalDist(1.0, sigma);
	double sigmaDecrement = sigma / ((double)passes + 1);

	//starting params
	weightings.at(0) = 0;
	weightings.at(1) = 0;
	weightings.at(2) = 0;
	
	vector<double> weightingsBuffer = vector<double>(weightings);
	vector<double> bestCurrentPassWeightingsBuffer = vector<double>(weightings);
	
	

	Solution* base = new Solution(file);
	
	//climbs
	for (int pass = 0; pass < passes; pass++)
	{

		cout << "\n------------ Pass " << pass << " ------------\n";
		cout << "Weightings: " << weightingsBuffer.at(0) << ", " << weightingsBuffer.at(1) << ", " << weightingsBuffer.at(2) << "\n";

		for (int sample = 0; sample < samples; sample++)
		{
			cout << "		------------ Sample " << sample<< " ------------\n";

			//best score for a given set of micro samples
			int localMaxScore = 0;
			Solution* currentSample = NULL;

			//calc some weighting normal on current
			if (BOOKWEIGHTING)
			{
				normalDist = normal_distribution<double>(weightingsBuffer.at(0), sigma);
				weightings.at(0) = normalDist(generator);
			}
			if (SCANWEIGHTING)
			{
				normalDist = normal_distribution<double>(weightingsBuffer.at(1), sigma);
				weightings.at(1) = normalDist(generator);
				
			}
			if (SIGNUPWEIGHTING)
			{
				normalDist = normal_distribution<double>(weightingsBuffer.at(2), sigma);
				weightings.at(2) = normalDist(generator);
			}

			cout << "		Weightings: " << weightings.at(0) << ", " << weightings.at(1) << ", " << weightings.at(2) << "\n";
			//run n micro samples and record the score
			for (int microSample = 0; microSample < microSamples; microSample++)
			{
				cout << "				------------ MicroSample " << microSample << " ------------\n";
				currentSample = new Solution(*base);
				int score = currentSample->calcScore(weightings);
				if (score > localMaxScore)
				{
					localMaxScore = score;

					if (!bestSolution == NULL)
					{
						delete bestSolution;
					}
					bestSolution = new Solution(*currentSample);
					if (localMaxScore > maxScore)
					{
						maxScore = localMaxScore;
						bestCurrentPassWeightingsBuffer = vector<double>(weightings);
						currentSample->writeToFile();
					}
				}
				currentSample->resetData();
				delete currentSample;
			}

			//if this sample beat the max score copy the weighting into best weightings


			cout << "		Finished Sample with SampleMax: " << localMaxScore << "\n";

		}


		weightingsBuffer = bestCurrentPassWeightingsBuffer;
		sigma *= 0.75;
		cout << "New Sigma: " << sigma << "\n";






	}

	for (Book* book : bestSolution->getBooksList())
	{
		delete book;
	}

	for (Library* lib : bestSolution->getLibraryList())
	{
		delete lib;
	}

	delete bestSolution;

	return maxScore;
}



int main()
{

	//ONLY RUN ONE AT A TIME

	//FILE A
	//cout << "Finished with Score: " << optimize( "..\\GoogleHashCode\\a_example.txt" ) << endl;

	//FILE B
	//cout << "Finished with Score: " << optimize( "..\\GoogleHashCode\\b_read_on.txt" ) << endl;

	//FILE C
	cout << "Finished with Score: " << optimize( "..\\GoogleHashCode\\c_incunabula.txt" ) << endl;

	//FILE D
	//cout << "Finished with Score: " << optimize( "..\\GoogleHashCode\\d_tough_choices.txt" ) << endl;

	//FILE E
	//cout << "Finished with Score: " << optimize( "..\\GoogleHashCode\\e_so_many_books.txt" ) << endl;

	//FILE F
	//cout << "Finished with Score: " << optimize( "..\\GoogleHashCode\\f_libraries_of_the_world.txt" ) << endl;


	

}






