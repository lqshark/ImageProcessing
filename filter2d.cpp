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

int main( int argc, char** argv )
{

 // LOADING THE IMAGE
 char* imageName = argv[1];

 Mat image;
 image = imread( "car1.png", 1 );

 Mat image_f;
 image.convertTo(image_f, CV_32F);


 // CONVERT COLOUR, BLUR AND SAVE
 Mat gray_image;
 cvtColor( image_f, gray_image, CV_BGR2GRAY );

 for(int y = 0; y < gray_image.rows; y++)
   for (int x = 0; x <gray_image.cols; x++) {
 		gray_image.at<float>(y,x) = 2*(gray_image.at<float>(y,x));
 	}

Mat carBlurred;
GaussianBlur(gray_image,23,carBlurred);

for(int y = 0; y < gray_image.rows; y++)
	for (int x = 0; x <gray_image.cols; x++) {
	 gray_image.at<float>(y,x) = ((gray_image.at<float>(y,x)) - carBlurred.at<float>(y,x));
 }

	for(int y = 0; y < gray_image.rows; y++) {
		for (int x = 0; x < gray_image.cols; x++) {
		if (gray_image.at<float>(y,x) > 255) {
			gray_image.at<float>(y,x) = 255;
			}
		else if (gray_image.at<float>(y,x) < 0) {
			gray_image.at<float>(y,x) = 0;
			}
			}
		}
Mat image_end;
gray_image.convertTo(image_end, CV_8U);



//Mat carBlurred;
 //GaussianBlur(image,23,carBlurred);

 //imwrite( "blur.jpg", carBlurred );
 namedWindow("Display window, CV_WINDOW_AUTOSIZE");
 imshow("DIsplay window", image_end);
 waitKey(0);
 image.release();
 return 0;
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

       // SET KERNEL VALUES
	for( int m = -kernelRadiusX; m <= kernelRadiusX; m++ ) {
	  for( int n = -kernelRadiusY; n <= kernelRadiusY; n++ )
           kernel.at<double>(m+ kernelRadiusX, n+ kernelRadiusY) = (double) 1.0/(size*size);

       }

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
