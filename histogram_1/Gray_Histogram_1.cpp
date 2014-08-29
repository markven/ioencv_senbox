//方法2，直接使用opencv內的hist API
//#include <stdafx.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>

int HistogramBins = 256;//橫軸想切成幾個區塊
float GrayLevelRange[2]={0,255};
//每個區塊代表的範圍值，例[0~1]、[1~2]~
//如果Bin越小，每一個區塊所代表的範圍值就越大，
//例Bin=10，範圍設{0,100}，每一個區塊值是[0~10]、[10~20]~
float *HistogramRange[1]={&GrayLevelRange[0]};

int main()
{
    IplImage *Src = cvLoadImage("lena.jpg",0);

    CvHistogram *Hist = cvCreateHist(1, &HistogramBins, CV_HIST_ARRAY, HistogramRange, 1);
    //cvCreateHist(直方圖維度, 直方圖區塊數, 輸入參數, 每個維度的上下界)
    //uniform = 1時，表示直方圖是均勻的
    cvCalcHist(&Src,Hist);//將來源影像轉成直方圖
    float histMax = 0;  
    cvGetMinMaxHistValue(Hist, 0 , &histMax, 0, 0);  // 取得直方图中的最值

    IplImage *HistImg = cvCreateImage(cvSize(HistogramBins, 300),8,3);
    HistImg->origin=1;//mac 不管用，將值方圖以直觀方式顯示



    ///cvNormalizeHist(Hist,1);//正規化
    //normalize(&src,Hist,1);
   // cvEqualizeHist(Hist,Hist);
    

    for(int i = 0; i < HistogramBins; i++)
    {
        printf("index = %d , count = %.f \n", i, ((CvMatND *) Hist->bins)->data.fl[i]);
        //取得每一個區塊所代表的數量
        cvLine(HistImg, cvPoint(i,300), cvPoint(i,(1-(cvQueryHistValue_1D(Hist,i)/histMax))*300)
            , CV_RGB(128,128,128));
        //將直方圖以影像表示
    }

    printf("%f\n",histMax );

/*
    IplImage* r_Img=cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);    
    IplImage* g_Img=cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);    
    IplImage* b_Img=cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);  
    cvSplit(src, r_Img, g_Img, b_Img,NULL);
*/

    IplImage *image1 = cvLoadImage("lena.jpg",3);  
    IplImage *redImage = cvCreateImage(cvGetSize(image1),IPL_DEPTH_8U,1);  
    IplImage *greenImage = cvCreateImage(cvGetSize(image1),IPL_DEPTH_8U,1);  
    IplImage *blueImage = cvCreateImage(cvGetSize(image1),IPL_DEPTH_8U,1);  
  
    cvSplit(image1,redImage,greenImage,blueImage,NULL);  
    cvNamedWindow("hello",CV_WINDOW_AUTOSIZE);  
    cvShowImage("hello",image1);  
    cvWaitKey(0);  
    cvShowImage("hello",redImage);  
    cvWaitKey(0);  
    cvShowImage("hello",greenImage);  
    cvWaitKey(0);  
    cvShowImage("hello",blueImage);  
    cvWaitKey(0); 

    cvNamedWindow("Hist",1);
    cvNamedWindow("Riverbank",1);
    cvShowImage("Riverbank", Src);
    cvShowImage("Hist", HistImg);
 
    cvWaitKey(0);
}