// GoogleHashCode.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "stdafx.h"

using namespace std;

const static int passes = 10;
const static int samples = 5;
const static int microSamples = 1;
static double sigma = 1; // may be too big

static vector<double> weightings = vector<double>({ 1, 1, 1 });



int optimize(string file)
{
	int maxScore = 0;
	Solution* bestSolution = NULL;
	vector<double> weightings = vector<double>({ 1, 1, 1 });

	default_random_engine generator(static_cast <unsigned> (time(0)));
	normal_distribution<double> normalDist(1.0, sigma);
	double sigmaDecrement = sigma / ((double)passes + 1);

	//starting params
	weightings.at(0) = 0.5;
	weightings.at(1) = 0.5;
	weightings.at(2) = 0.5;
	
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
					bestSolution = new Solution(*currentSample);
					if (localMaxScore > maxScore)
					{
						maxScore = localMaxScore;
						bestCurrentPassWeightingsBuffer = vector<double>(weightings);
						currentSample->writeToFile();
					}
				}
				currentSample->resetData();
			}

			//if this sample beat the max score copy the weighting into best weightings


			cout << "		Finished Sample with SampleMax: " << localMaxScore << "\n";

		}


		weightingsBuffer = bestCurrentPassWeightingsBuffer;
		sigma -= sigmaDecrement;
		cout << "New Sigma: " << sigma << "\n";






	}

	delete bestSolution;
	
	return maxScore;
}



int main()
{
	//Solution* sol1 = new Solution("C:\\Users\\44749\\Downloads\\a_example .txt");
	//Solution* sol1 = new Solution("C:\\Users\\44749\\Downloads\\b_read_on.txt");
	//Solution* sol1 = new Solution("C:\\Users\\44749\\Downloads\\c_incunabula.txt");
	//Solution* sol1 = new Solution("C:\\Users\\44749\\Downloads\\d_tough_choices.txt");
	//Solution* sol1 = new Solution("C:\\Users\\44749\\Downloads\\e_so_many_books.txt");
	//Solution* sol1 = new Solution("C:\\Users\\44749\\Downloads\\f_libraries_of_the_world.txt");
	//int score = sol1->calcScore(1,1,1);



	//Solution* bestSolution = optimize("C:\\Users\\44749\\Downloads\\a_example .txt");


	//cout << "Finished with Score: " << optimize("C:\\Users\\44749\\Downloads\\b_read_on.txt") << endl;
	cout << "Finished with Score: " << optimize("C:\\Users\\44749\\Downloads\\e_so_many_books.txt") << endl;


	//Solution* bestSolution = optimize("C:\\Users\\44749\\Downloads\\f_libraries_of_the_world.txt");
	//Solution* bestSolution = optimize("C:\\Users\\44749\\Downloads\\e_so_many_books.txt");


	//bestSolution->writeToFile();

}






