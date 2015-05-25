#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

Mat img,imgHSV,imgThresholded;

int LowH = 0;
int HighH = 179;

int LowS = 0; 
int HighS = 255;

int LowV = 0;
int HighV = 255;

void callback(int , void*){	
	inRange(imgHSV, Scalar(LowH, LowS, LowV), Scalar(HighH, HighS, HighV), imgThresholded); //Threshold the image
      
	//opening (removes small objects from the foreground)
	erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
	dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 

	//closing (removes small holes from the foreground)
	dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
	erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

	imshow("THRESHOLD", imgThresholded); //show the thresholded image
}

int main( int argc, char** argv ) {
    //VideoCapture cap(0); //capture the video from webcam
    VideoCapture cap("line_pool.mp4"); //path of the video 

    if ( !cap.isOpened() )  // if not success, exit program
    {
         cout << "Cannot get the stream" << endl;
         return -1;
    }

	namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
	namedWindow("ORIGINAL",CV_WINDOW_AUTOSIZE);
	namedWindow("THRESHOLD",CV_WINDOW_AUTOSIZE);
	
	createTrackbar("LowH", "Control", &LowH, 179,callback); //Hue (0 - 179)
	createTrackbar("HighH", "Control", &HighH, 179,callback);

	createTrackbar("LowS", "Control", &LowS, 255,callback); //Saturation (0 - 255)
	createTrackbar("HighS", "Control", &HighS, 255,callback);

	createTrackbar("LowV", "Control", &LowV, 255,callback);//Value (0 - 255)
	createTrackbar("HighV", "Control", &HighV, 255,callback); 

    while (true)
    {
        bool bSuccess = cap.read(img); // read a new frame from video

        if (!bSuccess) //if not success, break loop
        {
             cout << "Cannot read a frame from video stream" << endl;
             break;
        }
        
        imshow("ORIGINAL",img);

        char key=cvWaitKey(30);
		if((key)==32 || key==27){
			break;
		}
	}

	cvtColor(img, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
	
	char key=cvWaitKey(0);
	if((key) == 27){
		destroyAllWindows();
	}
	
	cout<<"HUE:- "<<LowH<<"-"<<HighH<<"  "<<"SATURATION:- "<<LowS<<"-"<<HighS<<"  "<<"VALUES:- "<<LowV<<"-"<<HighV<<endl;

	return 0;
}

