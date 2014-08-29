/*
Ver1
這是綜合版本，把畫圖的地方獨立出來，並且有做正規化。
by Mark Ven 20140829
 */

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include <istream>

using namespace std;
using namespace cv;

static void help()
{
    cout << "\nHistogram_ver1\n"
    "You choose a image and the algorithm it.\n"
    "u can get R, G, B, Gray of histogram\n"
    "\n"
    "Usage: \n"
    "$ ./main [image_name]\n";    
}

IplImage *DrawHistogram(CvHistogram *Hist, int Color = 0, float scaleX = 2, float scaleY = 4){  // 畫直方圖  
    
    float HistMax = 0;  
    float HistMin = 0;
    cvGetMinMaxHistValue(Hist, &HistMin, &HistMax, 0, 0);  // 取得直方圖中的最極值  
    
    IplImage *imgHist = cvCreateImage(cvSize(256 * scaleX, 64*scaleY), 8, 3);  
    cvZero(imgHist); //// 清空随機值  
	

    for(int i = 0; i < 255; i++)  
    {  
        float histValue = cvQueryHistValue_1D(Hist, i); // 取得直方圖i中的值  
        float nextValue = cvQueryHistValue_1D(Hist, i+1);  

        int numPt = 5;  
        CvPoint pt[5];

        CvScalar drawColor;  

        if (Color == 1){
        	drawColor = CV_RGB(255,0,0);
        }
        else if (Color == 2){
        	drawColor = CV_RGB(0,255,0);
        }
        else if (Color == 3){
        	drawColor = CV_RGB(0,30,255);
        }
        else if (Color == 0){
        	drawColor = cvScalarAll(128);
        }
        
        pt[0] = cvPoint(i*scaleX, 64*scaleY);  
        pt[1] = cvPoint((i+1)*scaleX, 64*scaleY);  
        pt[2] = cvPoint((i+1)*scaleX, (1 -(nextValue/HistMax))* 64 * scaleY);  
        pt[3] = cvPoint((i+1)*scaleX, (1 -(histValue/HistMax))* 64 * scaleY);  
        pt[4] = cvPoint((i+1)*scaleX, 64*scaleY);  
        cvFillConvexPoly(imgHist, pt, numPt, drawColor);  
    }  
    return imgHist;  
  
} 

int main(int argc,const char** argv){

	help();

	if(argv[1]==NULL){  
        cout << "No data img\n" << endl;
        cout<<"please keyin image name \n";  
        return -1;
    }


    IplImage *img = cvLoadImage(argv[1],3);  

    int dims = 1;  
    int sizes = 256;  
    float range[] = {0,255};  
    float*ranges[]={range};  
    CvHistogram *Hist = cvCreateHist(dims, &sizes, CV_HIST_ARRAY, ranges, 1);  
    cvClearHist(Hist);          //清除直方圖的noise   
    
    IplImage *imgGray = cvLoadImage(argv[1],0);
    IplImage *imgBlue = cvCreateImage(cvGetSize(img), 8, 1);  
    IplImage *imgGreen = cvCreateImage(cvGetSize(img), 8, 1);  
    IplImage *imgRed = cvCreateImage(cvGetSize(img), 8, 1);  
    cvSplit(img, imgBlue, imgGreen, imgRed, NULL);   //ＲＧＢ分離 

	cvCalcHist(&imgGray, Hist, 0, 0);    // 計算直方圖 
    IplImage *histGray = DrawHistogram(Hist,0);   // 把直方圖畫出來  
    cvClearHist(Hist);  

    cvCalcHist(&imgBlue, Hist, 0, 0);    // 計算直方圖  
    IplImage *histBlue = DrawHistogram(Hist,3);   // 把直方圖畫出來  
    cvClearHist(Hist);  
  
    cvCalcHist(&imgGreen, Hist, 0, 0);    
    IplImage *histGreen = DrawHistogram(Hist,2);  
    cvClearHist(Hist);

    cvCalcHist(&imgRed, Hist, 0, 0);  
    IplImage *histRed = DrawHistogram(Hist,1);  
    cvClearHist(Hist);  
  
    cvNamedWindow("show",0);  
    cvNamedWindow("B_hist", 0);  
    cvNamedWindow("G_hist", 0);  
    cvNamedWindow("R_hist", 0);
    cvNamedWindow("Gray_hist", 0);   
    cvShowImage("show",img);  
    cvShowImage("B_hist",histBlue);  
    cvShowImage("G_hist",histGreen);  
    cvShowImage("R_hist", histRed);
    cvShowImage("Gray_hist", histGray);   

    cvNamedWindow("B", 0);  
    cvNamedWindow("G", 0);  
    cvNamedWindow("R", 0);
    cvNamedWindow("Gray", 0); 

    cvShowImage("B",imgBlue);  
    cvShowImage("G",imgGreen);  
    cvShowImage("R",imgRed);
    cvShowImage("Gray",imgGray);
    cvWaitKey(0);  
    
    cvReleaseImage(&img);  
    cvDestroyWindow("show");  
    cvReleaseImage(&histBlue);  
    cvDestroyWindow("B_hist");  
    cvReleaseImage(&histGreen);  
    cvDestroyWindow("G_hist");  
    cvReleaseImage(&histRed);  
    cvDestroyWindow("R_hist");
    cvReleaseImage(&histGray);  
    cvDestroyWindow("Gray_hist");    
    return 0;  

}

