#include <stdio.h>
#include <opencv/cv.h>        //you may need to
#include <opencv/highgui.h>   //adjust import locations
#include <opencv/cxcore.h>    //depending on your machine setup

using namespace cv;

int main() {

  int newval[3];

  Mat image;
  //image = imread("mandrill0.jpg", CV_LOAD_IMAGE_UNCHANGED);
  image = imread("mandrill1.jpg", CV_LOAD_IMAGE_UNCHANGED);
//  newval[0] = image.at<cv::Vec3b>(x,y)[0];
//  newval[1] = image.at<cv::Vec3b>(x,y)[1];
//  newval[2] = image.at<cv::Vec3b>(x,y)[2];

  for(int y = image.rows - 1; y > 30; y--)
    for (int x = image.cols - 1; x > 30; x--) {
      image.at<cv::Vec3b>(x,y)[2] = image.at<cv::Vec3b>(x-30,y-30)[2];
    }



//  printf (" Value = %d \n", newval[0]);
//  printf (" Value = %d \n", newval[1]);
//  printf (" Value = %d \n", newval[2]);


namedWindow("Display window, CV_WINDOW_AUTOSIZE");
imshow("DIsplay window", image);
waitKey(0);
image.release();

return 0;
}
