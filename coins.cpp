// header inclusion
#include <stdio.h>
#include <opencv/cv.h>        //you may need to
#include <opencv/highgui.h>   //adjust import locations
#include <opencv/cxcore.h>    //depending on your machine setup

using namespace cv;

void GaussianBlur(
	cv::Mat &input,
	int size,
	cv::Mat &blurredOutput);

int main(){

  // read image
  Mat image;
  image = imread("coins1.png");

  //convert to grayscale
  Mat gray_image;
  cvtColor( image, gray_image, CV_BGR2GRAY );

  //Gaussian blur
  Mat coinBlurred;
  GaussianBlur(gray_image,23,coinBlurred);


  int cols = gray_image.cols;
  int rows = gray_image.rows;

  // Sobel operator in x direction
  int sobel_x[3][3] = {-1,0,1,-2,0,2,-1,0,1};
  // Sobel operator in y direction
  int sobel_y[3][3] = {-1,-2,-1,0,0,0,1,2,1};

  int radius = 1;

  // edges
  Mat _src;
  copyMakeBorder(gray_image, _src, radius, radius, radius, radius, BORDER_REFLECT101);

  // Create output matrix
  Mat gradient_x = gray_image.clone();
  Mat gradient_y = gray_image.clone();
  Mat gradient_f = gray_image.clone();

  int max=0;

  // Correlation loop in x direction

// Iterate on image
for (int r = radius; r < _src.rows - radius; ++r)
{
    for (int c = radius; c < _src.cols - radius; ++c)
    {
        int s = 0;

        // Iterate on kernel
        for (int i = -radius; i <= radius; ++i)
        {
            for (int j = -radius; j <= radius; ++j)
            {
                s += _src.at<uchar>(r + i, c + j) * sobel_x[i + radius][j + radius];
            }
        }
        gradient_x.at<uchar>(r - radius, c - radius) = s/30;
    }
}

Mat absGrad_x;
convertScaleAbs( gradient_x, absGrad_x );

// Conrrelation loop in y direction

// Iterate on image
for (int r = radius; r < _src.rows - radius; ++r)
{
    for (int c = radius; c < _src.cols - radius; ++c)
    {
        int s = 0;

        // Iterate on kernel
        for (int i = -radius; i <= radius; ++i)
        {
            for (int j = -radius; j <= radius; ++j)
            {
                s += _src.at<uchar>(r + i, c + j) * sobel_y[i + radius][j + radius];
            }
        }
        gradient_y.at<uchar>(r - radius, c - radius) = s/30;
    }
}

Mat absGrad_y;
convertScaleAbs( gradient_y, absGrad_y );


//Calculating gradient magnitude
for(int i=0; i<gradient_f.rows; i++)
{
    for(int j=0; j<gradient_f.cols; j++)
    {
        gradient_f.at<uchar>(i,j) = sqrt( pow(gradient_x.at<uchar>(i,j),2) + pow(gradient_y.at<uchar>(i,j),2) );

         if(gradient_f.at<uchar>(i,j) >240)
            gradient_f.at<uchar>(i,j) = 100;
        else
            gradient_f.at<uchar>(i,j) = 0;
    }
}


imshow("grad magnitude",gradient_f);
waitKey(0);
}

void GaussianBlur(cv::Mat &input, int size, cv::Mat &blurredOutput)
{
	// intialise the output using the input
	blurredOutput.create(input.size(), input.type());

	// create the Gaussian kernel in 1D
	cv::Mat kX = cv::getGaussianKernel(size, -1);
	cv::Mat kY = cv::getGaussianKernel(size, -1);

	// make it 2D multiply one by the transpose of the other
	cv::Mat kernel = kX * kY.t();

	//CREATING A DIFFERENT IMAGE kernel WILL BE NEEDED
	//TO PERFORM OPERATIONS OTHER THAN GUASSIAN BLUR!!!

	// we need to create a padded version of the input
	// or there will be border effects
	int kernelRadiusX = ( kernel.size[0] - 1 ) / 2;
	int kernelRadiusY = ( kernel.size[1] - 1 ) / 2;

	cv::Mat paddedInput;
	cv::copyMakeBorder( input, paddedInput,
		kernelRadiusX, kernelRadiusX, kernelRadiusY, kernelRadiusY,
		cv::BORDER_REPLICATE );

	// now we can do the convoltion
	for ( int i = 0; i < input.rows; i++ )
	{
		for( int j = 0; j < input.cols; j++ )
		{
			double sum = 0.0;
			for( int m = -kernelRadiusX; m <= kernelRadiusX; m++ )
			{
				for( int n = -kernelRadiusY; n <= kernelRadiusY; n++ )
				{
					// find the correct indices we are using
					int imagex = i + m + kernelRadiusX;
					int imagey = j + n + kernelRadiusY;
					int kernelx = m + kernelRadiusX;
					int kernely = n + kernelRadiusY;

					// get the values from the padded image and the kernel
					int imageval = ( int ) paddedInput.at<uchar>( imagex, imagey );
					double kernalval = kernel.at<double>( kernelx, kernely );

					// do the multiplication
					sum += imageval * kernalval;
				}
			}
			// set the output value as the sum of the convolution
			blurredOutput.at<uchar>(i, j) = (uchar) sum;
		}
	}
}
