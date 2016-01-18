#ifndef DHASH_H
#define DHASH_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;

typedef unsigned long long ulng;

const Size HASH_IMAGE_SIZE = Size(9, 8);    // arbitrary choice
const int HASH_LENGTH = (HASH_IMAGE_SIZE.width - 1) * HASH_IMAGE_SIZE.height;
const int DUPE_THRESHOLD = 10;              // empirically determined

ulng dh_getHash(Mat img)
{
    ulng hash = 0;
    cvtColor(img, img, CV_BGR2GRAY, 1);
    resize(img, img, HASH_IMAGE_SIZE);
    for (int i = 0; i < HASH_IMAGE_SIZE.width - 1; i++) 
        for (int j = 0; j < HASH_IMAGE_SIZE.height; j++) {
            hash = (hash << 1);
            if(img.at<uchar>(i, j + 1) > img.at<uchar>(i, j)) ++hash;
        }
    return hash;
}

int dh_HammingDistance(ulng hash1, ulng hash2) { return __builtin_popcountll(hash1 ^ hash2); }

// convenience method to quickly check if two images are duplicates.
bool dh_areDuplicates(Mat img1, Mat img2) {
    ulng hash1 = dh_getHash(img1), hash2 = dh_getHash(img2);
    return (dh_HammingDistance(hash1, hash2) < DUPE_THRESHOLD);
}

#endif