#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

vector<Vec3f> circles;
int threshold_value = 0;
int threshold_type = 3;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

int p = 0;
Mat src, src_gray, dst;

/// Function headers
void proc_imagem(int, void*);
void imprime_circulo(int, void*);

int main()
{
	//Carrega imagem
	src = imread("olho5.jpg");

	//Blur para evitar ruídos
	medianBlur(src, src, 1);
	medianBlur(src, src, 1);
	cvtColor(src, src_gray, COLOR_BGR2GRAY);

	namedWindow("Qualquer tecla para update", WINDOW_AUTOSIZE);

	//Trackbar para mudar o valor máximo de Threshold


	createTrackbar("Valor: ",
		"Qualquer tecla para update", &threshold_value,
		max_value, proc_imagem);

	//Trackbar para mudar o tipo de Threshold

	createTrackbar("Tipo: ",
		"Qualquer tecla para update", &threshold_type,
		max_type, proc_imagem);

	// inicializa funcao
	proc_imagem(0, 0);

	cout << "Aperte uma tecla para atualizar a imagem";
	while (1) {
		
		imprime_circulo(0,0);
		waitKey(0);
	}
}

void proc_imagem(int, void*){
	
	Mat src_test;
	threshold(src_gray, dst, threshold_value, max_BINARY_value, threshold_type);
	GaussianBlur(dst, src_test, Size(9, 9), 0, 0);
	
	
}
void imprime_circulo(int, void*) {

	HoughCircles(dst, circles, HOUGH_GRADIENT, 1, dst.rows / 8, 100, 20, 0, 0);
	if (circles.size() == 0) exit(-1);
	for (size_t current_circle = 0; current_circle < circles.size(); ++current_circle) {
		Point center(round(circles[current_circle][0]), round(circles[current_circle][1]));
		int radius = round(circles[current_circle][2]);

		circle(dst, center, radius, Scalar(100, 100, 0), 2);
	}
	imshow("Teste", dst);
}