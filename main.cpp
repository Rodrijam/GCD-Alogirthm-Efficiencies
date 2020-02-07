// Authors : Samuel Smetzer and James Rodriguez
// Project 1
 
#include <iostream>
#include <cctype>
#include <string.h>
#include <sstream>
#include <limits>
#include <vector>
#include <math.h>
#include <algorithm> 
#include <cstdlib>

#include "gnuplot-iostream.h"

using namespace std;


void plotPoints(vector<boost::tuple<double, double>>, int, int, string, string);
int EUgcd(int, int);
int CIC(int,int);
int MSgcd(int, int);
vector<int> discPrimes(int);
int FibSeq(int);

float modCount = 0;
float CICmodcount = 0;
float SDcount = 0;

bool xele;

int main (){
    
	// Initial User Queries Begin
	
    bool testing;
    string choice = " ";
    
	cout << "Does your terminal have x11 support? (Y/N)";
    cin >> choice;
    
    if (choice.size() > 1 )
    {
        cout << "Response Invalid, '" << choice << "' is not an option" << endl;
        exit(0);
    }
    if (tolower(choice[0]) == 'y')
        xele = true;
    else if (tolower(choice[0]) == 'n')
        xele = false;
    else
    {
        cout << "Response Invalid, '" << choice << "' is not an option" << endl;
        exit(0);
    }	
	
	choice = " ";
	
    cout << "Would you like to enter Testing Mode (T) or Scatter Plot Mode (S)? ";
    cin >> choice;
    
    if (choice.size() > 1 )
    {
        cout << "Response Invalid, '" << choice << "' is not an option" << endl;
        exit(0);
    }
    if (tolower(choice[0]) == 't')
        testing = true;
    else if (tolower(choice[0]) == 's')
        testing = false;
    else
    {
        cout << "Response Invalid, '" << choice << "' is not an option" << endl;
        exit(0);
    }
    
	// User Queries End

	// Test Choice Begin
	
    if(testing){
        
        int task;
        
        cout << "Please choose a task:\n Task1[1] (Euclid's algorithm and Consecutive integer comparison)\n Task2[2] (Worst-case efficiency of Euclid's algorithm)\n Task3[3] (Middle-school procedure)" << endl;
        cin >> task;
        while (task != 1 and task != 2 and task !=3)
        {
            cout << "Response Invalid, please choose again." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please choose a task:\n Task1[1] (Euclid's algorithm and Consecutive integer comparison)\n Task2[2] (Worst-case efficiency of Euclid's algorithm)\n Task3[3] (Middle-school procedure)" << endl;
            cin >> task;
            
        }       
        
        cout << "Task chosen: Task " << task << endl;;
        
        if(task == 1) 								//Algorithm Comparison
        {
            int n;
            cout << "Please enter a value for 'n': ";
            cin >> n;
			modCount = 0;
			CICmodcount = 0;
			for (int j = 1; j < n+1 ; j++)
			{
				EUgcd(n, j);
				CIC(n, j);
			}

			float avgEU = modCount / n;
			float avgCIC = CICmodcount / n;

			cout << "Euclid’s Algorithm average-case efficiency: " << avgEU << endl;
			cout << "Consecutive Integer Checking Algorithm average-case efficiency: "  << avgCIC << endl;

		}
        if(task == 2)								//Worst-case Euclid’s Algorithm
        {
            int k;
            cout << "Please enter a value for 'k': ";
            cin >> k;
			double m = FibSeq(k+1);
			double n = FibSeq(k);
            cout << "GCD of (" << m << "," << n << ") is: " << EUgcd(m,n) << endl;
        }
        if(task == 3)								// Middle School Procedure
        {
            int n, m, o;
            cout << "Enter 2 integers: \nM: ";
            cin >> m;
            while (!cin)
            {
                cout << "Error, input is not a digit!" << endl;  
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "M: ";
                cin >> m;
                
            }
         
            cout << "N: ";
            cin >> n;
            while (!cin)
            {
                cout << "Error, input is not a digit!" << endl;  
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "N: ";
                cin >> n;
                
            }
            o = MSgcd(m,n);
            cout << "GCD(" << m << "," << n <<") of is: " << o << endl;
        }
		
		// Test Choice End
    }
    else
    {
		
		
		int n = 5;
		int f = 20;
		int maxSize = 50;
		

		vector<boost::tuple<double, double> > EUpoints;
		vector<boost::tuple<double, double> > CICpoints;
		vector<boost::tuple<double, double> > FIBpoints;
		vector<boost::tuple<double, double> > MSPpoints;

		float avgEU;
		float avgCIC;
		float avgFIB;
		float avgMSP;
		
		float maxEU = 0;
		float maxCIC = 0;
		float maxFIB = 0;
		float maxMSP = 0;
		
		
		//Point Generation
		for (int i = 1; i < 11; i++)
		{
			modCount = 0;
			CICmodcount = 0;
			SDcount = 0;
			n *= 2;
			for (int j = 1; j < n+1 ; j++)
			{
				EUgcd(n, j);
				CIC(n, j);
				MSgcd((rand() % maxSize) + 1,(rand() % maxSize) + 1); // gets the gcd of two random integers from 1 to maxSize
			}

			avgEU = modCount / n;
			avgCIC = CICmodcount / n;
			
			modCount = 0;
			for (int j = 1; j < n+1 ; j++)
			{
				EUgcd(FibSeq((i*2)+1), FibSeq(i*2));
			}
			avgFIB = modCount / n;			
			avgMSP = SDcount / n;
			
			EUpoints.push_back(boost::make_tuple(n,avgEU));
			CICpoints.push_back(boost::make_tuple(n,avgCIC));
			FIBpoints.push_back(boost::make_tuple(FibSeq(i*2),avgFIB));
			MSPpoints.push_back(boost::make_tuple(n,avgMSP));		
			
			// find max values
			if (avgEU > maxEU)
				maxEU = avgEU;
			if (avgCIC > maxCIC)
				maxCIC = avgCIC;
			if (avgFIB > maxFIB)
				maxFIB = avgFIB;
			if (avgMSP > maxMSP)
				maxMSP = avgMSP;
		}
		
		cout << "Generating plot for Euclid’s Algorithm... with n starting at 5" << endl;
		plotPoints(EUpoints, n, maxEU + 10, "euSP", "Euclid’s Algorithm");
		cout << "Scatterplot has been made in scatter_plots as euSP.png" << endl;

		cout << "Generating plot for Consecutive Integer Checking Algorithm... with n starting at 5" << endl;
		plotPoints(CICpoints, n, maxCIC + 10, "cicSP", "Consecutive Integer Checking Algorithm");
		cout << "Scatterplot has been made in scatter_plots as cicSP.png" << endl;

		cout << "Generating plot for Worst Case Euclid’s Algorithm... with the first n elements" << endl;
		plotPoints(FIBpoints, n, maxFIB + 10, "fibSP", "Worst Case Euclid’s Algorithm (Fibonacci Sequence)");
		cout << "Scatterplot has been made in scatter_plots as fibSP.png" << endl;
		
		cout << "Generating plot for Middle-School Procedure... with a range of maximum 50" << endl;
		plotPoints(MSPpoints, n, maxMSP + 10, "mspSP", "Middle-School Procedure");
		cout << "Scatterplot has been made in scatter_plots as mspSP.png" << endl;		
		
		

	}
}


void plotPoints(vector<boost::tuple<double, double>> allPoints, int x, int y, string name, string title)
{
		Gnuplot gp;
		if(!xele)
		{
			gp << "set term png\n";
			gp << "set out 'scatter_plots/" << name <<".png'\n";
		}

		gp << "set title '" << title << "'\n";
		gp << "set xrange [0:" << x + 10 << "]\nset yrange [0:" << y << "]\n";
		gp << "plot '-' with points notitle\n";
		gp.send1d(allPoints);	
		
		if(!xele)
			gp << "set out";
}

int EUgcd(int m, int n){
    
    if (n == 0)
        return m;
    modCount++;
    return EUgcd(n, m % n);
    
}

int CIC(int n, int m)
{
	int t = min(n, m);
	while(t > 0 )
	{
		CICmodcount ++;
		if(m % t == 0)
		{
			if(n % t == 0)
			{
				CICmodcount ++;
				return t;
			}
		}
		t = t-1;
	}
	return t;
}

int FibSeq(int k)
{		
	int prev = 0;
	int curr = 1;
	int temp;
	
	for(int i = 1; i < k; i++)
	{
		temp = prev;
		prev = curr;
		curr = prev + temp;
	}
	return curr;
}


int MSgcd(int m, int n){
    
    if (n > m)
    {
        int temp = m;
        m = n;
        n = temp;
    }

    vector<int> m_primelist = discPrimes(m);
    vector<int> n_primelist = discPrimes(n);
    
    int gcd_res = 1;
    
    for(int i = 0; i < m_primelist.size(); i++)
    {
        for(int j = 0; j < n_primelist.size(); j++)
        {
            if (m_primelist[i] == n_primelist[j])
            {
                gcd_res *= m_primelist[i];
                i++;
                j = 0;
            }
            
        }
    }
    
    
    return gcd_res;
}

vector<int> discPrimes(int k){
    vector<int> primeALLList;
    vector<int> primeFACList;
    bool pass = true;
    
    for (int i = 2; i < k+1; i++)
    {
        
        for (int j = 0; j < primeALLList.size(); j++)
        {
			SDcount++;
            if (i % primeALLList[j] == 0)
                pass = false;
        }
        
        if (pass)
        {
            primeALLList.push_back(i);
        }
        pass = true;
        
    }
    int i = 0;
    while (k > 1)
    {
		SDcount++;
        if (k % primeALLList[i] == 0)
        {
            k = k / primeALLList[i];
			SDcount++;
            primeFACList.push_back(primeALLList[i]);
        }
        else
            i++;
    }
    
    return primeFACList;
}
