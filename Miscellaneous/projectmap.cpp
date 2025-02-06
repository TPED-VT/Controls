//#include <wiringPi.h>
#include <iostream>
//#include <opencv2/opencv.hpp> 

// using namespace cv;
using namespace std; 

int SwitchProjectMap(void) {

int choice = 0; 
string filename; 

// if (checkStage1(ride)) {
//     choice = 1; 
// } else if (CheckStage2(ride)) {
//     choice = 2; 
// } else if (CheckStage3(ride)) {
//     choice = 3; 
// } else if (CheckStage4(ride)) {
//     choice = 4; 
// } else {
//     break;
// }

// ASSUMING THAT THE CHECKSTAGE IS A BOOLEAN EXPRESSION AND RETURNS TRUE OR FALSE 

switch(choice) {
    case 1 :  
    filename = "Smoke.mp4";
    break;

    case 2 :
    filename = "SmokeBIG.mp4";
    break;

    case 3 :
    filename = "Fire.mp4";
    break; 

    case 4 :
    filename = "FireSmokeWhosh.mp4";
    break;

    default:
    break;
    
}

// REC MOCK CODE:

// VideoCapture cap(filename);
// if (if !cap.isOpened() ) // isOpened() returns true if capturing has been initilaized. 
// {

    // cout << "Cannot open the video file. \n"


// }

// double fps = cap.get(CV_CAP_PROP_FPS); // get the frames per seconds of the video
    // The function get is used to derive a property from the element.

// CV_CAP_POS_MSEC : Current Video Capture timestamp.
// CV_CAP_PROP_POS_FRAMES : Index of the next frame. 

// namedWindow(filename, CV_WINDOW_AUTOSIZE); // create a window called "MyVideo"
    // first argument: name of the window. 
    // second argument: flag - types:
        // WINDOW_NORMAL : The user can resize the window
        // WINDOW_AUTOSIZE : The window size is automatically adjusted to fit the displayed image() ), and you cannot change the window size manually. 

    // WINDOW_OPENGL : The window will be created with OpenGL support. 

// while(1) 
//{

    // Mat frame; 
        // Mat object is a basic image container. frame is an object of Mat.

    // if (!cap.read(frame)) // if not success, break loop 
      // read() decodes and captures the next frame. 
    //{

        // cout <<"\n Cannot read the video file. \n";
        // break;
    //}

    //if(waitKey(30) == 27) // Wait for 'esc' key press to exit 
 // {
    // break;
 // }


//}




// GEEKS FOR GEEK CODE:


// VideoCapture cap("Smoke.mp4");
    // cap is the object video capture that tries to capture Smoke.mp4
// if (if !cap.isOpened() ) // isOpened() returns true if capturing has been initilaized. 
// {

    // cout << "Cannot open the video file. \n"


// }

// double fps = cap.get(CV_CAP_PROP_FPS); // get the frames per seconds of the video
    // The function get is used to derive a property from the element.

// CV_CAP_POS_MSEC : Current Video Capture timestamp.
// CV_CAP_PROP_POS_FRAMES : Index of the next frame. 

// namedWindow("FireName", CV_WINDOW_AUTOSIZE); // create a window called "MyVideo"
    // first argument: name of the window. 
    // second argument: flag - types:
        // WINDOW_NORMAL : The user can resize the window
        // WINDOW_AUTOSIZE : The window size is automatically adjusted to fit the displayed image() ), and you cannot change the window size manually. 

    // WINDOW_OPENGL : The window will be created with OpenGL support. 

// while(1) 
//{

    // Mat frame; 
        // Mat object is a basic image container. frame is an object of Mat.

    // if (!cap.read(frame)) // if not success, break loop 
      // read() decodes and captures the next frame. 
    //{

        // cout <<"\n Cannot read the video file. \n";
        // break;
    //}

    //if(waitKey(30) == 27) // Wait for 'esc' key press to exit 
 // {
    // break;
 // }


//}

return 0; 
}