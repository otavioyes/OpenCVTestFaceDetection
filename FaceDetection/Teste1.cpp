#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>

#include <iostream>
#include <vector>

int main() {
    cv::Mat frame;
    cv::VideoCapture cap(0); // ABRE A CAMERA PADRÃO -> (0) 

    if (!cap.isOpened()) {
        std::cerr << "Erro ao abrir a câmera" << std::endl;
        return -1;
    }

    // Carrega o classificador Haar Cascade
    cv::CascadeClassifier detecFace;
    if (!detecFace.load("haarcascade_frontalface_default.xml")) {
        std::cerr << "Erro ao carregar o classificador de faces" << std::endl;
        return -1;
    }

    while (true) {
        cap >> frame; // Lê um frame da câmera

        // Verifica se o frame foi capturado com sucesso 
        if (frame.empty()) {
            std::cerr << "Erro ao capturar frame" << std::endl;
            break;
        }

        std::vector<cv::Rect> faces;
        detecFace.detectMultiScale(frame, faces, 1.3, 5);

        std::cout << faces.size() << '\n';

        for (size_t i = 0; i < faces.size(); i++) {
            cv::rectangle(frame, faces[i], cv::Scalar(50, 50, 255), 3);
            cv::rectangle(frame, cv::Point(0,0), cv::Point(690, 70), 
                cv::Scalar(50, 50, 255), cv::FILLED);

            cv::putText(frame, std::to_string(faces.size()) + " Rosto encontrado", cv::Point(10, 40),
                cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(0, 0, 0), 1);
        }

        cv::imshow("Video", frame);
        if (cv::waitKey(20) == 27) { // Pressione Esc para sair
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}