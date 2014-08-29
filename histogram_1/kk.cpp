//方法2，直接使用opencv內的hist API
//#include <stdafx.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include <iostream>  

int HistogramBins = 256;//橫軸想切成幾個區塊
float GrayLevelRange[2]={0,255};
//每個區塊代表的範圍值，例[0~1]、[1~2]~
//如果Bin越小，每一個區塊所代表的範圍值就越大，
//例Bin=10，範圍設{0,100}，每一個區塊值是[0~10]、[10~20]~
float *HistogramRange[1]={&GrayLevelRange[0]};

int main()
{
    IplImage *src = cvLoadImage("lena.jpg",0);
    IplImage *HistImg = cvCreateImage(cvSize(HistogramBins, 300),8,3);
    HistImg->origin=1;//將值方圖以直觀方式顯示
    CvHistogram *Hist = cvCreateHist(1, &HistogramBins, CV_HIST_ARRAY, HistogramRange, 1);
    //cvCreateHist(直方圖維度, 直方圖區塊數, 輸入參數, 每個維度的上下界)
    //uniform = 1時，表示直方圖是均勻的
    cvCalcHist(&src,Hist);//將來源影像轉成直方圖

    for(int i = 0; i < HistogramBins; i++)
    {
        printf("index = %d , count = %.f ", i, ((CvMatND *) Hist->bins)->data.fl[i]);
        //取得每一個區塊所代表的數量
        cvLine(HistImg, cvPoint(i,0), cvPoint(i,(int)(cvQueryHistValue_1D(Hist,i)/10))
            , CV_RGB(0,0,0));
        //將直方圖以影像表示
    }
    cvNamedWindow("Hist",1);
    cvNamedWindow("Riverbank",1);
    cvShowImage("Riverbank", src);
    cvShowImage("Hist", HistImg);
    cvWaitKey(0);
}