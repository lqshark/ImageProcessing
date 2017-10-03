#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>

using namespace cv;

int main() {
Mat image;
image = imread("mandrill.jpg", CV_LOAD_IMAGE_UNCHANGED);
  for(int y = 0; y < image.rows; y++) {
    for (int x = 0; x < image.cols; x++) {
      /*
    if (image.at<uchar>(y,x) >= 128) {
      image.at<uchar>(y,x) = 255;
      }
    else {
      image.at<uchar>(y,x) = 0;
      }
      */
      }
    }
      threshold(image, image, 128, 255, THRESH_BINARY);
    namedWindow("Display window", CV_WINDOW_AUTOSIZE);
    imshow("Display window", image);
    waitKey(0);
    image.release();
    return 0;
}
