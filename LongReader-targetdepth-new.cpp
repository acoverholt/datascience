//Program to read CORSIKA .long files into an array.
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <stdlib.h>
using namespace std;

int main () {

	int energy=117;

	while (energy<=150) {


		cout << "Starting calculations for energy ";
		cout << energy;
		cout << "\n";

	  std::string directoryname;
	  std::string decimalname;
	  std::string depthname;
	  std::stringstream outdirectory;
	  std::stringstream outdecimal;
	  std::stringstream outdepth;
	  outdirectory << int((energy - (energy % 10))/10);
	  outdecimal << energy % 10;
	  directoryname=outdirectory.str();
	  decimalname=outdecimal.str();

double neutrons[3][11][107];
double temp=0;
double part2, part3, part4, part5, part6, part7, part8, part9, part10;
int showertotal;
int targetdepth=104;
int adjustedtargetdepth=0;
int i, j, k;
int size;

double totalneutrons=0;
double oldtotalneutrons=0;
double droppedneutrons=0;


	std:: string outname="C:/Users/ACOverholt/workspace/Long2MCNP/Debug/NeutronCut/Neutrons-" + directoryname + "p" + decimalname + ".txt";
  ofstream outfile (outname.c_str());

	int angle=1; //actual angle is *5 degrees
	int shower=1;
	int depth=1; //actual depth is *10 g/cm^3
	double column=0;

	string filename;

	while (angle<=9) {

		 j=1;
		 k=1;


		while (k<=2) {
				while (j<=106) {
					neutrons[k][angle][j]=0;
					j=j+1;
				}
			k=k+1;
			j=1;
		}

		cout << "Done setting zeroes \n";

		std::string theta;
		std:: stringstream out;
		out << angle*10-5;
		theta=out.str();

		if (angle==1) {
			filename= "C:/Users/ACOverholt/Documents/Astrobiophysics/CORSIKA DATA/" + directoryname + "point" + decimalname + "/DAT000005.long";
		} else filename="C:/Users/ACOverholt/Documents/Astrobiophysics/CORSIKA DATA/" + directoryname + "point" + decimalname + "/DAT0000" + theta + ".long";

		ifstream longtest (filename.c_str());
		ifstream longfile (filename.c_str());

		int totaldepth;
		   if (angle==1) {
		   totaldepth = 106;
		   }
		   if (angle==2) {
		   	totaldepth = 109;
		   }
		   if (angle==3) {
		   	totaldepth = 116;
		   }
		   if (angle==4) {
		   	totaldepth = 128;
		   }
		   if (angle==5) {
		   	totaldepth = 148;
		   }
		   if (angle==6) {
			totaldepth = 182;
		   }
		   if (angle==7) {
			   totaldepth = 245;
		   }
		   if (angle==8) {
			   totaldepth = 396;
		   }
		   if (angle==9) {
			   totaldepth = 1059;
		   }

		   size = 0;
		   string line;
		   while ( !longtest.eof() )   {
		   	   getline(longtest, line);
		   	   size++;
		   }

		   showertotal = size/(2*totaldepth+10);

		   cout << "Total number of showers: ";
		   cout << showertotal;
		   cout << "\n";

		   longfile.seekg(201, ios::beg);

	if (longfile.is_open()) {
		while (longfile.good()) {

			while (shower<=showertotal) {
		//			column=cos((angle*10-5)*(3.14159265/180));
						column=105/(totaldepth-0.1);

					totalneutrons=0;
					oldtotalneutrons=0;
					droppedneutrons=0;
					adjustedtargetdepth=targetdepth;

				while (depth<=targetdepth) {

							longfile.seekg(8, ios::cur);

							longfile >> temp;
							part2=temp;
							longfile >> temp;
							part3=temp;
							longfile >> temp;
							part4=temp;
							longfile >> temp;
							part5=temp;
							longfile >> temp;
							part6=temp;
							longfile >> temp;
							part7=temp;
							longfile >> temp;
							part8=temp;
							longfile >> temp;
							part9=temp;
							longfile >> temp;
							part10=temp;

					totalneutrons=part7+part3+part4+part5+part6-part8;

					droppedneutrons=oldtotalneutrons-totalneutrons;

					if (droppedneutrons>=0) {
					neutrons[1][angle][depth]=neutrons[1][angle][depth]+droppedneutrons/showertotal;
					}

					oldtotalneutrons=totalneutrons;
						
			//		column=column+cos((angle*10-5)*(3.14159265/180));
					column=column+105/(totaldepth-0.1);


					if (column>=(depth)) {
						neutrons[2][angle][depth]=neutrons[2][angle][depth]+totalneutrons/showertotal;
						depth=depth+1;
					} else adjustedtargetdepth=adjustedtargetdepth+1;

				}

				longfile.seekg(((totaldepth-adjustedtargetdepth)*115), ios::cur);
				longfile.seekg((totaldepth*116), ios::cur);
				longfile.seekg(752, ios::cur);

				longfile >> temp;
				if (temp!=10) {
					longfile.seekg(-39, ios::cur);
				}else longfile.seekg(-4, ios::cur);

				oldtotalneutrons=0;
				totalneutrons=0;
				depth=1;
				shower=shower+1;
	//			if (shower%(showertotal/100)==0) {
	//				cout << "|";
	//			}
	//			if (shower%(showertotal/2)==0) {
	//				cout << "\n";
	//			}
			}

		longfile.close();
		}
	} else cout << "Unable to open file";

	shower=1;
	cout << "\nCalculations for angle ";
	cout << angle;
	cout << " complete.\n";
	angle=angle+1;
	}


	cout << "Printing results to file\n";
	outfile << "Depth \t 5 \t 15 \t 25 \t 35 \t 45 \t 55 \t 65 \t 75 \t 85 \n";

	i=1;
	k=1;

	while (k<=targetdepth) {

		outfile << k*10;

			while (i<=9) {

					outfile << "\t";
					outfile << neutrons[1][i][k];
					i=i+1;
			}
			outfile << "\n";
			i=1;
			k=k+1;
	}

	outfile << "\n\nHigh Energy Neutrons\n\nDepth \t 5 \t 15 \t 25 \t 35 \t 45 \t 55 \t 65 \t 75 \t 85 \n";

	i=1;
	k=1;

	while (k<=targetdepth) {

		outfile << k*10;

			while (i<=9) {

					outfile << "\t";
					outfile << neutrons[2][i][k];
					i=i+1;
			}
			outfile << "\n";
			i=1;
			k=k+1;
	}
energy=energy+1;
	}
return 0;
}

