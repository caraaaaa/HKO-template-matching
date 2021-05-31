//MatchTemplate_Demo_withimage_2
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/// Global Variables
Mat img; Mat templ; Mat result; Mat img_display;
const char* image_window = "Source Image";
//const char* result_window = "Result window";

int match_method = 4;
//int max_Trackbar = 5;

/// Function Headers
void MatchingMethod( int, void*, char** );

int main( int, char** argv )
{
  /// Load image and template
  Mat imgimg = imread( argv[1], 1 );
  templ = imread( "feature.jpg" , 1 );
  
  // subtract line
  Mat src2 = imread("converted.jpg",-1);
  Mat img_swap = ~imgimg;
  src2 = ~src2;
  img_swap = img_swap - src2;
  img_swap = ~img_swap;
  
  //crop
  Mat ROI(img_swap, Rect(15, 90, 650, 500));
  ROI.copyTo(img);
  Mat ROI2(imgimg, Rect(15, 90, 650, 500));
  ROI2.copyTo(img_display);

  /// Create windows
  namedWindow( image_window, WINDOW_AUTOSIZE );
  //namedWindow( result_window, WINDOW_AUTOSIZE );

  /// Create Trackbar
  //const char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
  //createTrackbar( trackbar_label, image_window, &match_method, max_Trackbar, MatchingMethod );

  MatchingMethod( 0, 0, argv );

  waitKey(0);
  return 0;
}

void MatchingMethod( int, void*, char** argv )
{
  /// Source image to display
  //Mat img_display;
  //img.copyTo( img_display );

  /// Create the result matrix
  int result_cols =  img.cols - templ.cols + 1;
  int result_rows = img.rows - templ.rows + 1;

  result.create( result_rows, result_cols, CV_32FC1 );

  /// Do the Matching and Normalize
  matchTemplate( img, templ, result, match_method );
  ///normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );

  /// Localizing the best match with minMaxLoc
  double minVal; double maxVal; Point minLoc; Point maxLoc;
  Point matchLoc;
  //minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
  //printf("-- minVal: %f \n", minVal );
  //printf("-- maxVal: %f \n", maxVal );

  /// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
  //if( match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED )
  //  { matchLoc = minLoc; }
  //else
  //  { matchLoc = maxLoc; }

  /// Show me what you got
  vector<Point> res;
  maxVal = 4200000.0;
  while (maxVal >= 3300000.0)
  {
    minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
    if (maxVal >= 3300000.0)
    {
      printf("-- maxVal: %f \n    ", maxVal );
      printf(argv[1]);    
      printf(" contain \n");
      rectangle( result, Point(maxLoc.x - templ.cols/2, maxLoc.y - templ.rows/2), Point( maxLoc.x + templ.cols/2 , maxLoc.y + templ.rows/2 ), Scalar::all(0), -1);
      res.push_back(maxLoc);
      //rectangle( result, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );
    }
  }
  //else
  //  printf("   not contain \n");
  
  for (int i = 0; i < res.size(); i++)
    rectangle(img_display, Point(res[i].x, res[i].y), Point(res[i].x + templ.cols, res[i].y + templ.rows), Scalar::all(0), 2, 8, 0 );

  imshow( image_window, img_display );
  ///imshow( result_window, result );

  return;
}