#include <fstream>

using std::ifstream;
using std::ofstream;
using std::endl;

char* toString(bool b) {
	if (b) 
		return "YES";
	else 
		return "NO";
}

bool equals(double a, double b) {
	if (abs(a-b) < 10e-4)
		return true;
	return false;
}

bool contains(double *a, int n, double key) {
	for (int i=0; i<n; i++) {
		if (equals(a[i], key))
			return true;
	}
	return false;
}

int main() {
	ifstream in("input.txt");
	ofstream out("output.txt");
	int n;
	in >> n;
	double *a = new double[n];
	for (int i=0; i<n; i++)
		in >> a[i];
	double key;
	while (!in.eof()) {
		in >> key;
		out << toString(contains(a,n,key)) << endl;
	}
	delete[] a;
	in.close();
	out.close();
	return 0;
}