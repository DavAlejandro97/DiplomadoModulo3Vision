/*
 * main.cpp
 *
 *  Created on: 20/07/2019
 *      Author: davidsilva
 */
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>

using namespace std;
using namespace cv;
int xmin, ymin, xmax, ymax, red, green, blue, Rn, Gn, Bn;


cv::Mat image, Mex1, Mex2, res;
std::vector<cv::Mat> channels;
std::vector<cv::Mat> rgbChannels(3);
cv::Mat g, copia, fin_image;

void onMouse(int event, int x, int y, int, void *param);
void onMouse_roi(int event, int x, int y, int, void *param);

int main(int argc, char ** argv) {

	image = cv::imread("OpenCV_Screenshot.jpg");
	Mex1 = cv::imread("mex1.jpg");
	Mex2 = cv::imread("mex2.jpg");
	int opcion = atoi(argv[1]);

	switch(opcion){
		case 2:
			cout<< "Se ha elegido Ejercicio 2"<<endl;
			cv::namedWindow("Imagen",1);
			cv::setMouseCallback("Imagen", onMouse, &image);
			cv::imshow("Imagen", image);
			cv::waitKey(0);
			break;

		case 3:
			cout<< "Se ha elegido Ejercicio 3"<<endl;
			image.copyTo(copia);
			cv::namedWindow("Imagen original",1);
			cv::imshow("Imagen original", image);
			//cv::waitKey(0);
			cv::namedWindow("Copia",1);
			cv::imshow("Copia", copia);
			cv::waitKey(0);
			break;

		case 4:
			cout<<"Se ha elegido Ejercicio 4"<<endl;
			cv::split(image, rgbChannels);
			cv::namedWindow("Original",1);
			cv::imshow("Original", image);

			g = cv::Mat::zeros(cv::Size(image.cols, image.rows), CV_8UC1);

			channels.push_back(g);
			channels.push_back(g);
			channels.push_back(rgbChannels[2]);

			cv::merge(channels, fin_image);
			cv::imshow("red", fin_image);

			channels = std::vector<cv::Mat>();
			channels.push_back(g);
			channels.push_back(rgbChannels[1]);
			channels.push_back(g);


			cv::merge(channels, fin_image);
			cv::imshow("green", fin_image);

			channels = std::vector<cv::Mat>();
			channels.push_back(rgbChannels[0]);
			channels.push_back(g);
			channels.push_back(g);


			cv::merge(channels, fin_image);
			cv::imshow("blue", fin_image);

			cv::waitKey(0);
			break;

		case 5:
			cout<<"Se ha elegido Ejercicio 5"<<endl;
			cv::namedWindow("Imagen",1);
			cv::setMouseCallback("Imagen", onMouse_roi, &image);
			cv::imshow("Imagen", image);
			cv::waitKey(0);
			break;

		case 6:
			cout<<"Se ha elegido Ejercicio 6"<<endl;
			cv::namedWindow("Img1",1);
			cv::imshow("Img1", Mex1);
			cv::namedWindow("Img2",1);
			cv::imshow("Img2", Mex2);

			cv::bitwise_and(Mex1,Mex2,res);   	  	cv::imshow("AND",res);
			cv::bitwise_or(Mex1,Mex2,res);    	  	cv::imshow("OR",res);
			cv::bitwise_xor(Mex1,Mex2,res);     	cv::imshow("XOR",res);
			cv::bitwise_not(Mex1,res);     			cv::imshow("NOT - Catedral",res);
			cv::bitwise_not(Mex2,res);     			cv::imshow("NOT - Bellas artes",res);
			cv::waitKey(0);
			break;

		case 7:
			cout<<"Se ha elegido Ejercicio 7"<<endl;
			cv::cvtColor(image, res, CV_BGR2GRAY);
			cv::imshow("Original", image);
			cv::imshow("Gray", res);
			cv::cvtColor(image, res, CV_BGR2HSV);
			cv::imshow("HSV", res);
			cv::waitKey(0);

			break;

		case 8:
			cout<<"Se ha elegido Ejercicio 8"<<endl;
			fin_image = cv::Mat::zeros(cv::Size(image.cols, image.rows), image.type());
			for(int i = 0; i<image.cols; i++){
				for(int j = 0; j<image.rows; j++){
					blue = (int)image.at<cv::Vec3b>(j,i)[0];
					green = (int)image.at<cv::Vec3b>(j,i)[1];
					red = (int)image.at<cv::Vec3b>(j,i)[2];
					if ((red + green + blue) == 0){
						Rn = 0;		Gn = 0;		Bn = 0;
					} else {
						Rn = (int) 255 * red / (red + green + blue);
						Gn = (int) 255 * green / (red + green + blue);
						Bn = (int) 255 * blue / (red + green + blue);
					}
					fin_image.at<cv::Vec3b>(j,i)[2] = Rn;
					fin_image.at<cv::Vec3b>(j,i)[1] = Gn;
					fin_image.at<cv::Vec3b>(j,i)[0] = Bn;
				}
			}

			cv::namedWindow("Original",1);
			cv::imshow("Original", image);
			cv::namedWindow("Normalizada",1);
			cv::imshow("Normalizada", fin_image);
			cv::waitKey(0);
			break;

		default:
			break;


	}

	return 0;

}


void onMouse(int event, int x, int y, int, void *param){
	if (event == CV_EVENT_LBUTTONDOWN){
		cout<< "El clic izquierdo del mouse fue presionado en la posición: " << x <<  ", " <<y<< "" << endl;
		image.at<cv::Vec3b>(y,x);
		cout<< "Rojo: " <<(int)image.at<cv::Vec3b>(y,x)[2]<<endl;
		cout<< "Verde: " <<(int)image.at<cv::Vec3b>(y,x)[1]<<endl;
		cout<< "Azul: " <<(int)image.at<cv::Vec3b>(y,x)[0]<<endl;
	}
}


void onMouse_roi(int event, int x, int y, int, void *param){
	bool cropping= false;
	cv::Mat* imagePtr = (cv::Mat*) param;
	cv::Mat image = *imagePtr;

	if(event == CV_EVENT_LBUTTONDOWN){
		xmin = x;
		ymin = y;
		xmax = x;
		ymax = y;

		cropping = true;
	} else if(event == CV_EVENT_MOUSEMOVE && cropping){
		xmax = x;
		ymax = y;
	} else if(event == CV_EVENT_LBUTTONUP){
		xmax = x;
		ymax = y;
		cropping = false;
		cv::rectangle(image, cv::Point(xmin, ymin), cv::Point(xmax, ymax), cv::Scalar(0,255,0), 2);
		cv::Rect rect(xmin, ymin, xmax - xmin, ymax - ymin);
		cv::Mat roi = image(rect);

		cv::imshow("Imagen", image);
		cv::imshow("Roi", roi);
		cv::waitKey(0);
	}
}



