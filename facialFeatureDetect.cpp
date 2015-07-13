#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>
using namespace std;  
using namespace cv;  
  
CvHaarClassifierCascade *cascade_f;  
CvHaarClassifierCascade *cascade_e;  
CvHaarClassifierCascade *cascade_n;  
CvHaarClassifierCascade *cascade_m;  
CvMemStorage   *storage;  
  
#define NUM_OF_FEATURES 5  
  
CvPoint2D32f frontal_frame_features[NUM_OF_FEATURES];  
  
int detectFaces(IplImage *img, CvRect *face);  
int detectFaceFeatures(IplImage *img, CvRect *face);  
int tracking();  
  
static const double pi = 3.14159265358979323846;  
  
int main(int argc, char** argv)  
{  
    IplImage *img;  
 const char *file1 = "haarcascades/haarcascade_frontalface_alt.xml";  
    const char *file2 = "haarcascades/haarcascade_eye.xml";  
 const char *file3 = "haarcascades/haarcascade_mcs_nose.xml";  
 const char *file4 = "haarcascades/haarcascade_mcs_mouth.xml";  
  
 cascade_f = (CvHaarClassifierCascade*)cvLoad(file1, 0, 0, 0);  
    cascade_e = (CvHaarClassifierCascade*)cvLoad(file2, 0, 0, 0);  
    cascade_n = (CvHaarClassifierCascade*)cvLoad(file3, 0, 0, 0);  
    cascade_m = (CvHaarClassifierCascade*)cvLoad(file4, 0, 0, 0);  
  
    /* setup memory storage, needed by the object detector */  
    storage = cvCreateMemStorage(0);  
  
    /* load image */  
    img = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_COLOR);  
  
    assert(cascade_f && cascade_e && storage);  
  
 const char* name = "Features-Detection";  
    cvNamedWindow(name, 1);  
  
 Mat frame = img;  
 CvRect face;  
 if (detectFaces(img, &face)) {  
  if(detectFaceFeatures(img, &face)) {  
   cout << "Features detected" << endl;  
  }  
 }  
 cvShowImage(name, img);  
 cvWaitKey(0);  
    cvDestroyWindow(name);  
    cvReleaseImage(&img);  
    cvClearMemStorage(storage);  
  
    return 0;  
}  
  
int detectFaces(IplImage *img, CvRect *face) {  
    /* detect faces */  
 CvSeq *faces = cvHaarDetectObjects(  
            img, cascade_f, storage,  
            1.1, 2, CV_HAAR_DO_CANNY_PRUNING, cvSize( 50, 50 ) );  
  
 if (faces->total == 0) {  
  return 0;  
 }  
 CvRect* _face = (CvRect*)cvGetSeqElem(faces, 0);  
 face->x = _face->x;  
 face->y = _face->y;  
 face->width = _face->width;  
 face->height = _face->height;  
 return 1;  
}  
  
int detectFaceFeatures(IplImage *img, CvRect *face)  
{  
 int i;  
 bool hasEyes = false;  
 bool hasNose = false;  
 bool hasMouth = false;  
 cvRectangle(img,  
    cvPoint(face->x, face->y),  
    cvPoint(face->x + face->width, face->y + face->height),  
    CV_RGB(255, 0, 0), 1, 8, 0);  
  
    /* Set the Region of Interest*/  
 CvRect eyeROI = cvRect(face->x, face->y + (face->height/5.5), face->width, face->height/3.0);  
 CvRect noseROI = cvRect(face->x, face->y + (face->height/2.5), face->width, face->height/3.0);  
 CvRect mouthROI = cvRect(face->x, face->y + (face->height/1.5), face->width, face->height/2.5);  
  
 CvRect *r;  
    /* detect eyes */  
 cvSetImageROI(img, eyeROI);  
 CvSeq* eyes = cvHaarDetectObjects(  
           img, cascade_e, storage,  
           1.15, 3, 0, cvSize(25, 15));  
 cvResetImageROI(img);  
 /* detect nose */  
 cvSetImageROI(img, noseROI);  
 CvSeq* noses = cvHaarDetectObjects(  
           img, cascade_n, storage,  
           1.1, 3, 0, cvSize(25, 15));  
 cvResetImageROI(img);  
 /* detect Mouth */  
 cvSetImageROI(img, mouthROI);  
 CvSeq* mouths = cvHaarDetectObjects(  
            img, cascade_m, storage,  
            1.1, 3, 0, Size(30, 30));  
 cvResetImageROI(img);  
 /* draw a rectangle for each eye found */  
 for( i = 0; i < (eyes ? eyes->total : 0); i++ ) {  
  r = (CvRect*)cvGetSeqElem( eyes, i );  
  int x1 = r->x + eyeROI.x;  
  int y1 = r->y + eyeROI.y;  
  int x2 = x1 + r->width;  
  int y2 = y1 + r->height;  
  int xc = (x1 + x2)/2;  
  int yc = (y1 + y2)/2;  
  cvRectangle(img,  
     cvPoint(x1, y1),  
     cvPoint(x2, y2),  
     CV_RGB(255, 0, 0), 1, 8, 0);  
  cvCircle(img, cvPoint(xc, yc), 2, CV_RGB(255,0,0), 2, 8, 0);  
  float fX = xc;  
  float fY = yc;  
  frontal_frame_features[i] = cvPoint2D32f(fX,fY);  
  if (i==1) {  
   hasEyes = true;  
  }  
 }  
 /* draw a rectangle for each nose found */  
 for( i = 0; i < (noses ? noses->total : 0); i++ ) {  
  r = (CvRect*)cvGetSeqElem( noses, i );  
  int x1 = r->x + noseROI.x;  
  int y1 = r->y + noseROI.y;  
  int x2 = x1 + r->width;  
  int y2 = y1 + r->height;  
  int xc = (x1 + x2)/2;  
  int yc = (y1 + y2)/2;  
  cvRectangle(img,  
     cvPoint(x1, y1),  
     cvPoint(x2, y2),  
     CV_RGB(0, 255, 0), 1, 8, 0);  
  cvCircle(img, cvPoint(xc, yc), 2, CV_RGB(255,0,0), 2, 8, 0);  
  hasNose = true;  
  float fX = xc;  
  float fY = yc;  
  frontal_frame_features[2] = cvPoint2D32f(fX,fY);  
 }  
 /* draw a rectangle for each mouth found */  
 for( i = 0; i < (mouths ? mouths->total : 0); i++ ) {  
  int margin_left = 10;  
  int margin_right = 0;  
  r = (CvRect*)cvGetSeqElem( mouths, i );  
  int x1 = r->x + mouthROI.x;  
  int y1 = r->y + mouthROI.y;  
  int x2 = x1 + r->width;  
  int y2 = y1 + r->height;  
  int x1c = x1 + margin_left;  
  int y1c = (y1 + y2)/2;  
  int x2c = x2 - margin_right;  
  int y2c = (y1 + y2)/2 - 5;  
  cvRectangle(img,  
     cvPoint(x1, y1),  
     cvPoint(x2, y2),  
     CV_RGB(0, 0, 255), 1, 8, 0);  
  cvCircle(img, cvPoint(x1c, y1c), 2, CV_RGB(255,0,0), 2, 8, 0);  
  cvCircle(img, cvPoint(x2c, y2c), 2, CV_RGB(255,0,0), 2, 8, 0);  
  hasMouth = true;  
  frontal_frame_features[3] = cvPoint2D32f(x1c,y1c);  
  frontal_frame_features[4] = cvPoint2D32f(x2c,y2c);  
 }  
 return (hasEyes && hasNose && hasMouth)?1:0;  
} 
