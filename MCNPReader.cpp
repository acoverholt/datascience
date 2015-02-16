//Program to read mctal files and pull out ground level neutrons
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <stdlib.h>
using namespace std;

int main () {

	int targetdepth=10;

while (targetdepth<=104) {
	string outname;
	std::string tardepth;
	std:: stringstream out3;
	out3 << targetdepth;
	tardepth=out3.str();

	outname="C:/Users/ACOverholt/workspace/Long2MCNP/Debug/ThermalCut/Thermal-"+tardepth+".txt";


  ofstream outfile (outname.c_str());

	int angle=0; //actual angle is *10 degrees
	int depth=9;
	int energy=1;
	double temp;
	   int position1;
	   string line1;
	   int skipline;
		string line;

	string filename;
	
	 outfile << "0\t0\t0\t0\t0\t0\t0\t0\t0\t0\n";
	 outfile << "0\t0\t0\t0\t0\t0\t0\t0\t0\t0\n";
	 outfile << "0\t0\t0\t0\t0\t0\t0\t0\t0\t0\n";
	 outfile << "0\t0\t0\t0\t0\t0\t0\t0\t0\t0\n";
	 outfile << "0\t0\t0\t0\t0\t0\t0\t0\t0\t0\n";
	 outfile << "0\t0\t0\t0\t0\t0\t0\t0\t0\t0\n";
	 outfile << "0\t0\t0\t0\t0\t0\t0\t0\t0\t0\n";
	 outfile << "0\t0\t0\t0\t0\t0\t0\t0\t0\t0\n";

	while (depth<=104) {

	while (angle<=8) {

		std::string theta;
		std:: stringstream out1;
		out1 << angle*10;
		theta=out1.str();
		
		std::string surface;
		std:: stringstream out2;
		out2 << 109-depth;
		surface=out2.str();

		filename="C:/Users/ACOverholt/Documents/Astrobiophysics/Neutron Thermalization/100kruns/sur" + surface + "/mctal_" + theta;

		ifstream mctalfile (filename.c_str());


		   getline(mctalfile, line1);
		   position1=line1.find("tally   21");

		   while ( position1 == string::npos )   {
			   getline(mctalfile, line1);
			   position1=line1.find("tally   21");
		   }

			skipline=0;

			while (skipline <=(23+(targetdepth*10)/4-(targetdepth*10)%4)) {
				getline(mctalfile, line);
				skipline=skipline+1;
			}

		   mctalfile.seekg(21*(targetdepth*10)%4, ios::cur);

//		outfile << "Surface = ";
//		outfile << surface;
//		outfile << "\tAngle = ";
//		outfile << theta;
//		outfile << "\t";

	if (mctalfile.is_open()) {
		if (mctalfile.good()) {
		
		while (energy<=10) {
			mctalfile >> temp;
			outfile << temp;
			outfile << "\t";
			mctalfile.seekg(7, ios::cur);
			energy=energy+1;
		}
		outfile << "\n";
		energy=1;
		mctalfile.close();
		}
		} else outfile << "ERROR!\n";
	angle=angle+1;
	}
angle=0;

depth=depth+1;
}
	cout << "Depth ";
	cout << targetdepth;
	cout << " completed.\n";
	targetdepth=targetdepth+1;
}

return 0;
}

