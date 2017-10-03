#include <stdio.h>
#include <opencv/cv.h>        //you may need to
#include <opencv/highgui.h>   //adjust import locations
#include <opencv/cxcore.h>    //depending on your machine setup

using namespace cv;

int main() {

  int newval[3];

  Mat image;
  //image = imread("mandrill0.jpg", CV_LOAD_IMAGE_UNCHANGED);
  image = imread("mandrill0.jpg", CV_LOAD_IMAGE_UNCHANGED);
  newval[0] = image.at<cv::Vec3b>(0,0)[0];
  newval[1] = image.at<cv::Vec3b>(0,0)[1];
  newval[2] = image.at<cv::Vec3b>(0,0)[2];

for(int y = 0; y < image.rows; y++)
  for (int x = 0; x <image.cols; x++) {
    int temp = image.at<Vec3b>(y,x)[0];
    image.at<Vec3b>(y,x)[0] = image.at<Vec3b>(y,x)[2];
    image.at<Vec3b>(y,x)[2] = image.at<Vec3b>(y,x)[1];
    image.at<Vec3b>(y,x)[1] = temp;

  }
  printf (" Value = %d \n", newval[0]);
  printf (" Value = %d \n", newval[1]);
  printf (" Value = %d \n", newval[2]);
  namedWindow("Display window, CV_WINDOW_AUTOSIZE");
  imshow("DIsplay window", image);
  waitKey(0);
  image.release();
  return 0;
}


  /*
//  namedWindow("Display window, CV_WINDOW_AUTOSIZE");
//  imshow("DIsplay window", image);
int HistR[257] = {0};
    int HistG[257] = {0};
    int HistB[257] = {0};
    for (int i = 0; i < image.rows; i++)
        for (int j = 0; j < image.cols; j++)
        {
            Vec3b intensity = image.at<Vec3b>(Point(j, i));
            int Red = intensity.val[0];
            int Green = intensity.val[1];
            int Blue = intensity.val[2];
            HistR[Red] = HistR[Red]+1;
            HistB[Blue] = HistB[Blue]+1;
            HistG[Green] = HistG[Green]+1;
        }
    Mat HistPlotR (500, 256, CV_8UC3, Scalar(0, 0, 0));
    Mat HistPlotG (500, 256, CV_8UC3, Scalar(0, 0, 0));
    Mat HistPlotB (500, 256, CV_8UC3, Scalar(0, 0, 0));
    for (int i = 0; i < 256; i=i+2)
    {
        line(HistPlotR, Point(i, 500), Point(i, 500-HistR[i]), Scalar(0, 0, 255),1,8,0);
        line(HistPlotG, Point(i, 500), Point(i, 500-HistG[i]), Scalar(0, 255, 0),1,8,0);
        line(HistPlotB, Point(i, 500), Point(i, 500-HistB[i]), Scalar(255, 0, 0),1,8,0);
    }
    namedWindow("Red Histogram");
    namedWindow("Green Histogram");
    namedWindow("Blue Histogram");
    imshow("Red Histogram", HistPlotR);
    imshow("Green Histogram", HistPlotG);
    imshow("Blue Histogram", HistPlotB);
    waitKey(0);
    return 0;
  }
  */
/*
    Mat image2;
    image2 = imread("mandrillRGB.jpg", CV_LOAD_IMAGE_UNCHANGED);
  //  namedWindow("Display window, CV_WINDOW_AUTOSIZE");
  //  imshow("DIsplay window", image);
  int HistR[257] = {0};
      int HistG[257] = {0};
      int HistB[257] = {0};
      for (int i = 0; i < image2.rows; i++)
          for (int j = 0; j < image2.cols; j++)
          {
              Vec3b intensity = image2.at<Vec3b>(Point(j, i));
              int Red = intensity.val[0];
              int Green = intensity.val[1];
              int Blue = intensity.val[2];
              HistR[Red] = HistR[Red]+1;
              HistB[Blue] = HistB[Blue]+1;
              HistG[Green] = HistG[Green]+1;
          }
      Mat HistPlotR (500, 256, CV_8UC3, Scalar(0, 0, 0));
      Mat HistPlotG (500, 256, CV_8UC3, Scalar(0, 0, 0));
      Mat HistPlotB (500, 256, CV_8UC3, Scalar(0, 0, 0));
      for (int i = 0; i < 256; i=i+2)
      {
          line(HistPlotR, Point(i, 500), Point(i, 500-HistR[i]), Scalar(0, 0, 255),1,8,0);
          line(HistPlotG, Point(i, 500), Point(i, 500-HistG[i]), Scalar(0, 255, 0),1,8,0);
          line(HistPlotB, Point(i, 500), Point(i, 500-HistB[i]), Scalar(255, 0, 0),1,8,0);
      }
      namedWindow("Red Histogram2");
      namedWindow("Green Histogram2");
      namedWindow("Blue Histogram2");
      imshow("Red Histogram2", HistPlotR);
      imshow("Green Histogram2", HistPlotG);
      imshow("Blue Histogram2", HistPlotB);
      waitKey(0);
    return 0;
}
*/
