#include <stdio.h>
#include <opencv/cv.h>        //you may need to
#include <opencv/highgui.h>   //adjust import locations
#include <opencv/cxcore.h>    //depending on your machine setup
#include "opencv2/imgproc/imgproc.hpp"


using namespace cv;

int main() {

  Mat image;
  // image = imread("mandrillRGB.jpg", CV_LOAD_IMAGE_UNCHANGED);
  image = imread("mandrill3.jpg", CV_LOAD_IMAGE_UNCHANGED);


  cvtColor(image, image, CV_HSV2BGR);

  imshow("Display window", image);
  waitKey(0);
  image.release();

  return 0;
}
