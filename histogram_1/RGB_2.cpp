#include <iostream>  
#include <opencv/cv.h>  
#include "opencv/highgui.h"  
#include "opencv/cxcore.h"  
using namespace std;  
  
IplImage *DrawHistogram(CvHistogram*hist, float scaleX = 2, float scaleY = 4){  // 画直方图  
    float histMax = 0;  
    cvGetMinMaxHistValue(hist, 0 , &histMax, 0, 0);  // 取得直方图中的最值  
    IplImage *imgHist = cvCreateImage(cvSize(256 * scaleX, 64*scaleY), 8, 1);  
    cvZero(imgHist); //// 清空随机值  
    for(int i = 0; i < 255; i++)  
    {  
        float histValue = cvQueryHistValue_1D(hist, i); // 取得直方图中的i值  
        float nextValue = cvQueryHistValue_1D(hist, i+1);  
        int numPt = 5;  
        CvPoint pt[5];  
        pt[0] = cvPoint(i*scaleX, 64*scaleY);  
        pt[1] = cvPoint((i+1)*scaleX, 64*scaleY);  
        pt[2] = cvPoint((i+1)*scaleX, (1 -(nextValue/histMax))* 64 * scaleY);  
        pt[3] = cvPoint((i+1)*scaleX, (1 -(histValue/histMax))* 64 * scaleY);  
        pt[4] = cvPoint(i*scaleX, 64*scaleY);  
        cvFillConvexPoly(imgHist, pt, numPt, cvScalarAll(255));  
    }  
    return imgHist;  
  
  
}  
  
  
int main()  
{  
    IplImage *img = cvLoadImage("waterfall.jpg",1);  
    if(!img){  
        cout << "No data img" << endl;  
    }  
    int dims = 1;  
    int sizes = 256;  
    float range[] = {0,255};  
    float*ranges[]={range};  
    CvHistogram *hist = cvCreateHist(dims, &sizes, CV_HIST_ARRAY, ranges, 1);  
    cvClearHist(hist);          //清除直方图里面的随机值   
    IplImage *imgBlue = cvCreateImage(cvGetSize(img), 8, 1);  
    IplImage *imgGreen = cvCreateImage(cvGetSize(img), 8, 1);  
    IplImage *imgRed = cvCreateImage(cvGetSize(img), 8, 1);  
    cvSplit(img, imgBlue, imgGreen, imgRed, NULL);   //将多通道图像分解  
  
    cvCalcHist(&imgBlue, hist, 0, 0);    // 计算图像的直方图  
    IplImage *histBlue = DrawHistogram(hist);   // 将直方图中的数据画出来  
    cvClearHist(hist);  
  
    cvCalcHist(&imgGreen, hist, 0, 0);    
    IplImage *histGreen = DrawHistogram(hist);  
    cvClearHist(hist);  
    cvCalcHist(&imgRed, hist, 0, 0);  
    IplImage *histRed = DrawHistogram(hist);  
    cvClearHist(hist);  
  
    cvNamedWindow("show",0);  
    cvNamedWindow("B", 0);  
    cvNamedWindow("G", 0);  
    cvNamedWindow("R", 0);  
    cvShowImage("show",img);  
    cvShowImage("B",histBlue);  
    cvShowImage("G",histGreen);  
    cvShowImage("R", histRed);  
    cvWaitKey(0);  
    cvReleaseImage(&img);  
    cvDestroyWindow("show");  
    cvReleaseImage(&histBlue);  
    cvDestroyWindow("B");  
    cvReleaseImage(&histGreen);  
    cvDestroyWindow("G");  
    cvReleaseImage(&histRed);  
    cvDestroyWindow("R");  
    return 0;  
      
}  