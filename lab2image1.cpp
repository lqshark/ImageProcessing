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
  Mat temp_image = image;

// Pull red layer from 30 pixels to the left and 30 pixels above a
// given pixel, starting from the bottom-right pixel
  for (int y = image.rows - 1; y > 30; y--)
    for (int x = image.cols - 1; x > 30; x--) {
      image.at<cv::Vec3b>(y,x)[2] = image.at<cv::Vec3b>(y-30,x-30)[2];
    }


// Do the above for pixels in the strip above

  for (int y = 0; y <= 30; y++)
    for (int x = 0; x < image.cols; x++) {
      image.at<cv::Vec3b>(y,x)[2] = temp_image.at<cv::Vec3b>(y+image.rows-30,x)[2];
    }

for (int y = 0; y < image.rows; y++)
  for (int x = 0; x <= 30; x++) {
    image.at<cv::Vec3b>(y,x)[2] = temp_image.at<cv::Vec3b>(y,x+image.cols-30)[2];
  }



imshow("DIsplay window", image);
waitKey(0);
image.release();

return 0;
}
