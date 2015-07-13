#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>
 
using namespace std;
using namespace cv;
//function declaration
Mat DetectFace(Mat frame);

//global variables
CascadeClassifier face_cascade; 
int filenumber; // Number of file to be saved
string filename;

int main(int argc, char** argv  )
{
    Mat image,faceis,edge;
     if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }

    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);  
     if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    namedWindow( "window1", 1 );
    imshow( "window1", image );
 
    // Load Face cascade (.xml file)

    String face_cascade_name = "haarcascades/haarcascade_frontalface_alt.xml";
//    face_cascade.load( "haarcascade_frontalface_alt.xml" );
     if( !face_cascade.load( face_cascade_name ) ){
	printf("--(!)Error loading\n");
	return -1;
     }
	    // Detect faces
	faceis=DetectFace(image);
	Canny( faceis, edge, 50, 150, 3);
	Mat new_image = Mat::zeros( edge.size(), edge.type() );
	Mat sub_image = Mat::ones( edge.size(), edge.type() )*225;
	subtract(sub_image, edge, new_image);
	imshow("edges" , edge);
	imshow("inverted" , new_image);
	Mat photu= new_image;
	Vec3b pixel;
	pixel[0]= 148;
	pixel[1]= 242;
	pixel[2]= 169;
        int	row = new_image.rows, column=new_image.cols;
	for(int i=0 ; i < row;i++)
		for(int j=0 ; j < row;j++)
		{	Vec3b xx =image.at<Vec3b>(i, j);
			if( xx[0] > 250 | xx[1] >250)
				image.at<Vec3b>(i, j)=pixel;
		}
	imshow("coloured" , new_image);
    waitKey(0);                   
    return 0;
}
Mat DetectFace(Mat frame)
{
    std::vector<Rect> faces;
    Mat frame_gray;
    Mat crop;
    Mat res;
    Mat gray;
    string text;
    stringstream sstm;

    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

// Detect faces
    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

//    face_cascade.detectMultiScale(image, faces, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_SCALE_IMAGE, Size(30,30));
    cv::Rect roi_b;
    cv::Rect roi_c;
	printf("faces.size() : %d \n",faces.size());

    size_t ic = 0; // ic is index of current element
    int ac = 0; // ac is area of current element

    size_t ib = 0; // ib is index of biggest element
    int ab = 0; // ab is area of biggest element

    for (ic = 0; ic < faces.size(); ic++) // Iterate through all current elements (detected faces)

    {
        roi_c.x = faces[ic].x;
        roi_c.y = faces[ic].y;
        roi_c.width = (faces[ic].width);
        roi_c.height = (faces[ic].height);

        ac = roi_c.width * roi_c.height; // Get the area of current element (detected face)

        roi_b.x = faces[ib].x;
        roi_b.y = faces[ib].y;
        roi_b.width = (faces[ib].width);
        roi_b.height = (faces[ib].height);

        ab = roi_b.width * roi_b.height; // Get the area of biggest element, at beginning it is same as "current" element

        if (ac > ab)
        {
            ib = ic;
            roi_b.x = faces[ib].x;
            roi_b.y = faces[ib].y;
            roi_b.width = (faces[ib].width);
            roi_b.height = (faces[ib].height);
        }

        crop = frame(roi_b);
        resize(crop, res, Size(128, 128), 0, 0, INTER_LINEAR); // This will be needed later while saving images
        cvtColor(crop, gray, CV_BGR2GRAY); // Convert cropped image to Grayscale

        // Form a filename
        filename = "xyz";
        stringstream ssfn;
        ssfn << filenumber << ".jpg";
        filename = ssfn.str();
        filenumber++;

        imwrite(filename, gray);

        Point pt1(faces[ic].x, faces[ic].y); // Display detected faces on main window - live stream from camera
        Point pt2((faces[ic].x + faces[ic].height), (faces[ic].y + faces[ic].width));
        rectangle(frame, pt1, pt2, Scalar(0, 255, 0), 2, 8, 0);
    }

// Show image
    sstm << "Crop area size: " << roi_b.width << "x" << roi_b.height << " Filename: " << filename;
    text = sstm.str();

    putText(frame, text, cvPoint(30, 30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 255), 1, CV_AA);
    imshow("original", frame);

    if (!crop.empty())
    {
        imshow("detected", crop);
	return crop;
    }
    else
    {
        destroyWindow("detected");
	printf("Oops we could't able to detect your face :(\n");
	exit(0);
    }

}
