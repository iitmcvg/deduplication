#ifndef DHASH_H
#define DHASH_H

#include <string>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;

const Size HASH_IMAGE_SIZE = Size(9, 8);    // arbitrary choice
const int HASH_LENGTH = (HASH_IMAGE_SIZE.width - 1) * HASH_IMAGE_SIZE.height;
const int DUPE_THRESHOLD = 10;              // empirically determined

string dh_getHash(Mat img)
{
    string hash = "";
    cvtColor(img, img, CV_BGR2GRAY, 1);
    resize(img, img, HASH_IMAGE_SIZE);
    for (int i = 0; i < HASH_IMAGE_SIZE.width - 1; i++) 
        for (int j = 0; j < HASH_IMAGE_SIZE.height; j++)
            if(img.at<uchar>(i, j + 1) > img.at<uchar>(i, j)) hash.push_back('1');
            else hash.push_back('0');
    return hash;
}

// currently no error detection/handling is being done.
int dh_HammingDistance(string hash1, string hash2) {
    int distance = 0;
    for (int i = 0; i < HASH_LENGTH; ++i)
        distance += (hash1[i] != hash2[i]);
    return distance;
}

// convenience method to quickly check if two images are duplicates.
bool dh_areDuplicates(Mat img1, Mat img2) {
    string hash1 = dh_getHash(img1), hash2 = dh_getHash(img2);
    return (dh_HammingDistance(hash1, hash2) < DUPE_THRESHOLD);
}

#endif