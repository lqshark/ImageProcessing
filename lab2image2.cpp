#include <stdio.h>
#include <opencv/cv.h>        //you may need to
#include <opencv/highgui.h>   //adjust import locations
#include <opencv/cxcore.h>    //depending on your machine setup
#include "opencv2/imgproc/imgproc.hpp"


using namespace cv;

int main() {

  Mat image;
  // image = imread("mandrillRGB.jpg", CV_LOAD_IMAGE_UNCHANGED);
  image = imread("mandrill2.jpg", CV_LOAD_IMAGE_UNCHANGED);

  // Invert the individual RGB colours by minusing the current
  // RGB values from 255
  for (int y = 0; y < image.rows; y++)
    for (int x = 0; x < image.cols; x++) {
      image.at<Vec3b>(y,x)[0] = 255 - image.at<Vec3b>(y,x)[0];
      image.at<Vec3b>(y,x)[1] = 255 - image.at<Vec3b>(y,x)[1];
      image.at<Vec3b>(y,x)[2] = 255 - image.at<Vec3b>(y,x)[2];
    }

  imshow("Display window", image);
  waitKey(0);
  image.release();

  return 0;
}
