#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <cstdio>
#include <pHash.h>
#include <pHash-config.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;

void split_line(string line, string& fname, string& hash) {
	fname.clear();
	hash.clear();
	bool foundMark = false;
	for (char c: line)
		if (foundMark) hash.push_back(c);
		else if (c != '#') fname.push_back(c);
		else foundMark = true;
}

int compare_dHashes(int* hash1, int* hash2)
{
	int count = 0;
	for(int i = 0; i < 64; i++)
		if(hash1[i] != hash2[i]) count++;
	return count;
}

int main(int argc, char const *argv[])
{
	// Format: ./a.out p <file1> <file2> OR
	//         ./a.out d <file1> <file2>
	ifstream infile1(argv[2], ifstream::in);
	ifstream infile2;
	string line1, line2, fname1, fname2, hash1, hash2;
	int compare_result, count = 0;
	if (infile1.is_open()) {
		while (getline(infile1, line1)) {
			split_line(line1, fname1, hash1);
			infile2.open(argv[3], ifstream::in);
			while (getline(infile2, line2)) {
				split_line(line2, fname2, hash2);
				if (fname1 != fname2) {
					if (!strcasecmp(argv[1], "p")) {
						ulong64 hashref1 = stoul(hash1, nullptr, 0),
								hashref2 = stoul(hash2, nullptr, 0);
						compare_result = ph_hamming_distance(hashref1, hashref2);
					}
					else if (!strcasecmp(argv[1], "d")) {
						int hashref1[100], hashref2[100];
						for (int i = 0; i < 64; ++i) {
							hashref1[i] = hash1[i] - '0';
							hashref2[i] = hash2[i] - '0';
						}
						compare_result = compare_dHashes(hashref1, hashref2);
					}
					if (compare_result < 10) {
						cout << fname1 << " " << fname2 << " : " << compare_result << endl;
						++count;
						// imshow(fname1, imread(fname1));
						// imshow(fname2, imread(fname2));
						// waitKey(0);
					}
				}
			}
			infile2.close();
		}
		infile1.close();
		cout << "Total of " << count << " dupes found." << endl;
	}
	return 0;
}