// header inclusion
#include <stdio.h>
#include <opencv/cv.h>        //you may need to
#include <opencv/highgui.h>   //adjust import locations
#include <opencv/cxcore.h>    //depending on your machine setup


using namespace cv;
/*
void GaussianBlur(
	cv::Mat &input,
	int size,
	cv::Mat &blurredOutput);
*/
void insertionSort(int window[])
{
    int temp, i , j;
    for(i = 0; i < 9; i++){
        temp = window[i];
        for(j = i-1; j >= 0 && temp < window[j]; j--){
            window[j+1] = window[j];
        }
        window[j+1] = temp;
    }
}

int main( int argc, char** argv )
{

 // LOADING THE IMAGE
 char* imageName = argv[1];

 Mat image;
 image = imread( "car2.png", 1 );

 //if( argc != 2 || !image.data )
 //{
   //printf( " No image data \n " );
   //return -1;
 //}

 // CONVERT COLOUR, BLUR AND SAVE
 Mat gray_image;
 cvtColor( image, gray_image, CV_BGR2GRAY );

 //Mat carBlurred;
 //GaussianBlur(gray_image,23,carBlurred);
 Mat dst;

       // Load an image
       //src = imread("book.png", CV_LOAD_IMAGE_GRAYSCALE);

       if( !gray_image.data )
       { return -1; }

       //create a sliding window of size 9
       int window[9];

         dst = gray_image.clone();
         for(int y = 0; y < gray_image.rows; y++)
             for(int x = 0; x < gray_image.cols; x++)
                 dst.at<uchar>(y,x) = 0.0;

         for(int y = 1; y < gray_image.rows - 1; y++){
             for(int x = 1; x < gray_image.cols - 1; x++){

                 // Pick up window element

                 window[0] = gray_image.at<uchar>(y - 1 ,x - 1);
                 window[1] = gray_image.at<uchar>(y, x - 1);
                 window[2] = gray_image.at<uchar>(y + 1, x - 1);
                 window[3] = gray_image.at<uchar>(y - 1, x);
                 window[4] = gray_image.at<uchar>(y, x);
                 window[5] = gray_image.at<uchar>(y + 1, x);
                 window[6] = gray_image.at<uchar>(y - 1, x + 1);
                 window[7] = gray_image.at<uchar>(y, x + 1);
                 window[8] = gray_image.at<uchar>(y + 1, x + 1);

                 // sort the window to find median
                 insertionSort(window);

                 // assign the median to centered element of the matrix
                 dst.at<uchar>(y,x) = window[4];
             }
         }

         namedWindow("final");
         imshow("final", dst);

         namedWindow("initial");
         imshow("initial", gray_image);

       waitKey();
 //imwrite( "blur.jpg", carBlurred );

 return 0;
}
/*
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
*/
