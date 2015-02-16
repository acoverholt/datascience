//Program to read CORSIKA .long files into an array.
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <stdlib.h>
using namespace std;

int main () {
double neutrons[12][10][105];
double finalneutrons[12][105];
double longtemp;
double mcnptemp;
double hightemp;
int energy=100;
int depth=10;
int thermdepth;

while (energy<=150) {

	int i=1;
	int j=1;
	int k=1;
	while (k<=104) {
		while (j<=9) {
				while (i<=11) {
					neutrons[i][j][k]=0;
					finalneutrons[i][k]=0;
					i=i+1;
				}
				j=j+1;
				i=1;
			}
		k=k+1;
		j=1;
	}



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

  string inname="C:/Users/ACOverholt/workspace/Long2MCNP/Debug/NeutronCut/Neutrons-" + directoryname + "p" + decimalname + ".txt";
  ifstream longfile (inname.c_str());

	string outname="Spectrum-" + directoryname + "p" + decimalname + ".txt";
	ofstream outfile (outname.c_str());

	string dummystring;
	getline(longfile, dummystring);

while (depth<=104) {

	  outdepth << depth;
	  depthname=outdepth.str();
	  string mcnpname="C:/Users/ACOverholt/workspace/Long2MCNP/Debug/ThermalCut/Thermal-" + depthname + ".txt";

  ifstream mcnpfile (mcnpname.c_str());

	j=1;
	i=1;

		longfile >> longtemp;

		while (j<=9) {

			longfile >> longtemp;

			thermdepth=1;

			while (thermdepth<=104) {

			int skipline=(thermdepth-1)*9;
			mcnpfile.seekg(ios::beg);
			while (skipline>0) {
				getline(mcnpfile, dummystring);
				skipline=skipline-1;
			}
			skipline=(j-1);
			while (skipline>0) {
							getline(mcnpfile, dummystring);
							skipline=skipline-1;
						}

			while (i<=10) {

				mcnpfile >> mcnptemp;

					neutrons[i][j][thermdepth]=longtemp*mcnptemp+neutrons[i][j][thermdepth];
				i=i+1;
			}
/*				int location;
				location=longfile.tellg();

				skipline=109;
				while (skipline>=0) {
						getline(longfile, dummystring);
						skipline=skipline-1;
										}

				int tabbed=0;
					hightemp=0;
				while (tabbed<=j) {
					longfile >> hightemp;
					tabbed=tabbed+1;
				}

				neutrons[i][j][depth]=hightemp;

				longfile.seekg(ios::beg);
				longfile.seekg(location);
*/
				thermdepth=thermdepth+1;
				i=1;
			}

			j=j+1;
			i=1;
		}

		j=1;
depth=depth+1;
}

depth=1;

while (depth<=104) {
	while (i<=11) {
		while (j<=9) {
			finalneutrons[i][depth]=finalneutrons[i][depth]+(cos((j*5-5)*(3.14159265/180))-cos((j*5+5)*(3.14159265/180)))*neutrons[i][j][depth];
			j=j+1;
		}
		i=i+1;
		j=1;
	}
	i=1;
	depth=depth+1;
}

i=1;
depth=10;
outfile << "Depth \t 5 \t 15 \t 25 \t 35 \t 45 \t 55 \t 65 \t 75 \t 85 \n";
while (depth<=104) {
	outfile << depth << "\t";
			while (i<=11) {

				outfile << finalneutrons[i][depth] << "\t";

				i=i+1;
			}
			outfile << "\n";
			i=1;
depth=depth+1;
}

depth=10;

cout << "Energy ";
cout << energy;
cout << " completed.\n";
energy=energy+1;
}
return 0;
}

