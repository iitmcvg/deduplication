#include "../include/dhash.h"
#include <iostream>
using namespace cv;
using namespace std;

/*
 * Tests dHash by passing two images and checking if they are duplicates.
 *
 * Usage: <output file name> <first image file name> <second image file name>
*/
int main(int argc, char const *argv[])
{
	if (argc != 3) {
		cout << "Usage: " << argv[0] << " <image file name> <image file name>" << endl;
		return 1;
	}
	Mat img1 = imread(argv[1]), img2 = imread(argv[2]);
	ulng hash1 = dh_getHash(img1), hash2 = dh_getHash(img2);
	//cout << "Hash 1: " << hash1 << "\nHash 2: " << hash2 << endl;
	int dist = dh_HammingDistance(hash1, hash2);
	/*if (dist < DUPE_THRESHOLD) {
		cout << "Image 1: " << argv[1] << endl << "Image 2: " << argv[2] << endl;
		cout << "Hamming distance between hashes: " << dist << endl << endl;
		imshow("Image 1", img1);
		imshow("Image 2", img2);
		waitKey(0);
	}*/
	cout << dist << " " << DUPE_THRESHOLD;
	/*bool areDupes = dh_areDuplicates(imread(argv[1]), imread(argv[2]));
	cout << "Duplicates: " << ((areDupes) ? "yes" : "no") << endl;*/
	return 0;
}