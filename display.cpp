#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>

using namespace cv;

int main() {
Mat image;
image = imread("myimage.jpg", CV_LOAD_IMAGE_UNCHANGED);
namedWindow("Display window", CV_WINDOW_AUTOSIZE);
imshow("Display window", image);
waitKey(0);
image.release();
return 0;
}
