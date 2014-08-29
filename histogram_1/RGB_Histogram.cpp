/*
本程式進行的是萃取影像的個波段直方圖
透過此種方式可以將影像進行解析

 */

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>

int BlueHistogramData[256]={0};
int GreenHistogramData[256]={0};
int RedHistogramData[256]={0};
int GrayLevelHistogramData[256]={0};


int main()
{
    IplImage *Image1=cvLoadImage("markven_view.jpg",3);
    IplImage *BufferImage_1,*BufferImage_2;
    IplImage *BlueHistogramImage,*GreenHistogramImage,*RedHistogramImage;
    IplImage *GrayLevelHistogramImage;

    //建立通道buffer
    //降低畫面產生錯誤及雜訊
    //
    BufferImage_1=cvCreateImage(cvSize(256,250),IPL_DEPTH_8U,3);
    BufferImage_2=cvCreateImage(cvSize(256,250),IPL_DEPTH_8U,3);

    BlueHistogramImage=cvCreateImage(cvSize(512,250),IPL_DEPTH_8U,3);
    GreenHistogramImage=cvCreateImage(cvSize(512,250),IPL_DEPTH_8U,3);
    RedHistogramImage=cvCreateImage(cvSize(512,250),IPL_DEPTH_8U,3);
    GrayLevelHistogramImage=cvCreateImage(cvSize(512,250),IPL_DEPTH_8U,3);

    //IplImage->origin 可以決定影像的坐標起點是在左上（0）或是在左下（1）
    //但是在mac上面並不奏效
    //
    BlueHistogramImage->origin=0;
    GreenHistogramImage->origin=1;
    RedHistogramImage->origin=1;
    GrayLevelHistogramImage->origin=1;

    CvScalar Scalar1;
    int BlueColor,GreenColor,RedColor,GrayLevelColor;

    for(int i=0;i<Image1->height;i++)
    {
        for(int j=0;j<Image1->width;j++)
        {
            //cvSet2D(Image1,i,j,cvScalar(255,255,255));
            //cvSet2D(Image1,i,j,CV_RGB(255,255,255));
            Scalar1=cvGet2D(Image1,i,j);
            BlueColor=(int)Scalar1.val[0];
            GreenColor=(int)Scalar1.val[1];
            RedColor=(int)Scalar1.val[2];
            GrayLevelColor=(int) (0.299*RedColor+0.587*GreenColor+0.114*BlueColor);
            
            //printf("%i\t",BlueColor);
            
            BlueHistogramData[BlueColor]++;
            GreenHistogramData[GreenColor]++;
            RedHistogramData[RedColor]++;
            GrayLevelHistogramData[GrayLevelColor]++;

        }
    }

    printf("i\tRed\tGreen\tBlue\tGrayLevel\n");
    for(int i=0;i<256;i++)
    {

        printf("%d\t%d\t%d\t%d\t%d\t\n",i,RedHistogramData[i],GreenHistogramData[i],BlueHistogramData[i],GrayLevelHistogramData[i]);
    }
    
    //i*2的原因是因為希望線條線條中間有黑色分隔
    //影像計算的時候，坐標軸原點是在左上角
    //
    

    for(int i=1;i<256;i++)
    {
        cvLine(BlueHistogramImage,cvPoint(i*2,250-BlueHistogramData[i]/100),cvPoint(i*2,255),CV_RGB(0,128,255));
        cvLine(GreenHistogramImage,cvPoint(i*2,250-GreenHistogramData[i]/100),cvPoint(i*2,255),CV_RGB(0,255,0));
        cvLine(RedHistogramImage,cvPoint(i*2,250-RedHistogramData[i]/100),cvPoint(i*2,255),CV_RGB(255,0,0));
        cvLine(GrayLevelHistogramImage,cvPoint(i*2,250-GrayLevelHistogramData[i]/100),cvPoint(i*2,255),CV_RGB(128,128,128));

    }

    cvNamedWindow("waterfall",1);
    cvShowImage("waterfall",Image1);
    cvNamedWindow("Blue Histogram",1);
    cvShowImage("Blue Histogram",BlueHistogramImage);
    cvNamedWindow("Green Histogram",1);
    cvShowImage("Green Histogram",GreenHistogramImage);
    cvNamedWindow("Red Histogram",1);
    cvShowImage("Red Histogram",RedHistogramImage);
    cvNamedWindow("GrayLevel Histogram",1);
    cvShowImage("GrayLevel Histogram",GrayLevelHistogramImage);



    cvWaitKey(0);
}