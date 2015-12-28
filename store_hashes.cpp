#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <pHash.h>
#include <pHash-config.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;

void compute_dHash(Mat img, int *hash)
{
	int k = 0;
	cvtColor(img,img,CV_BGR2GRAY,1);
	Size size(9,8);
	resize(img,img,size);
	for(int i = 0 ; i < 8 ; i++) {
		for(int j = 0 ; j < 8 ; j++ , k++) {
			if(img.at<uchar>(i,j+1) > img.at<uchar>(i,j)) 
				hash[k] = 1;
			else 
				hash[k] = 0;
		}
	}
}

int main(int argc, char const *argv[])
{
	// Format: ./a.out p <image> <file> OR ./a.out d <image> <file>
	ofstream outfile(argv[3], ofstream::app);
	if (!strcasecmp(argv[1], "d")) {
		int dHash[100];
		Mat image = imread(argv[2]);
		compute_dHash(image, dHash);
		outfile << argv[2] << "#";
		for (int d:dHash) outfile << d;
		outfile << endl;
	}
	else if (!strcasecmp(argv[1], "p")) {
		ulong64 hash_ref;
		int pHash = ph_dct_imagehash(argv[2], hash_ref);
		outfile << argv[2] << "#" << hash_ref << endl;
	}
	outfile.close();
	return 0;
}