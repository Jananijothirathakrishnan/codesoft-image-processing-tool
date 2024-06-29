#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
void displayImage(const Mat& image, const string& windowName);
Mat applyFilter(const Mat& image, const string& filter);
Mat adjustBrightnessContrast(const Mat& image, double alpha, int beta);
Mat cropImage(const Mat& image, Rect cropRegion);
Mat resizeImage(const Mat& image, int width, int height);

int main() {
    string imagePath;
    cout << "Enter the path to the image: ";
    cin >> imagePath;

    // Load image
    Mat image = imread(imagePath);
    if (image.empty()) {
        cout << "Could not load image!" << endl;
        return -1;
    }

    displayImage(image, "Original Image");

    while (true) {
        cout << "\nChoose an option:\n";
        cout << "1. Apply filter (grayscale, blur, sharpen)\n";
        cout << "2. Adjust brightness/contrast\n";
        cout << "3. Crop image\n";
        cout << "4. Resize image\n";
        cout << "5. Save image\n";
        cout << "6. Exit\n";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string filter;
                cout << "Enter filter type (grayscale, blur, sharpen): ";
                cin >> filter;
                image = applyFilter(image, filter);
                displayImage(image, "Filtered Image");
                break;
            }
            case 2: {
                double alpha;
                int beta;
                cout << "Enter alpha (contrast) [1.0-3.0]: ";
                cin >> alpha;
                cout << "Enter beta (brightness) [0-100]: ";
                cin >> beta;
                image = adjustBrightnessContrast(image, alpha, beta);
                displayImage(image, "Brightness/Contrast Adjusted Image");
                break;
            }
            case 3: {
                int x, y, width, height;
                cout << "Enter crop region x y width height: ";
                cin >> x >> y >> width >> height;
                image = cropImage(image, Rect(x, y, width, height));
                displayImage(image, "Cropped Image");
                break;
            }
            case 4: {
                int width, height;
                cout << "Enter new width and height: ";
                cin >> width >> height;
                image = resizeImage(image, width, height);
                displayImage(image, "Resized Image");
                break;
            }
            case 5: {
                string savePath;
                cout << "Enter the path to save the image: ";
                cin >> savePath;
                imwrite(savePath, image);
                cout << "Image saved successfully!" << endl;
                break;
            }
            case 6:
                return 0;
            default:
                cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}

void displayImage(const Mat& image, const string& windowName) {
    namedWindow(windowName, WINDOW_AUTOSIZE);
    imshow(windowName, image);
    waitKey(0);
}

Mat applyFilter(const Mat& image, const string& filter) {
    Mat result;
    if (filter == "grayscale") {
        cvtColor(image, result, COLOR_BGR2GRAY);
    } else if (filter == "blur") {
        GaussianBlur(image, result, Size(15, 15), 0);
    } else if (filter == "sharpen") {
        Mat kernel = (Mat_<float>(3, 3) <<
                       0, -1,  0,
                      -1,  5, -1,
                       0, -1,  0);
        filter2D(image, result, image.depth(), kernel);
    } else {
        cout << "Invalid filter type!" << endl;
        result = image;
    }
    return result;
}

Mat adjustBrightnessContrast(const Mat& image, double alpha, int beta) {
    Mat result = Mat::zeros(image.size(), image.type());
    for (int y = 0; y < image.rows; y++) {
        for (int x = 0; x < image.cols; x++) {
            for (int c = 0; c < image.channels(); c++) {
                result.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alpha * image.at<Vec3b>(y, x)[c] + beta);
            }
        }
    }
    return result;
}

Mat cropImage(const Mat& image, Rect cropRegion) {
    return image(cropRegion);
}

Mat resizeImage(const Mat& image, int width, int height) {
    Mat result;
    resize(image, result, Size(width, height));
    return result;
}
```

### How to Compile and Run
1. **Install OpenCV**: Ensure OpenCV is installed on your system. Follow the instructions on the [OpenCV installation guide](https://opencv.org/releases/).

2. **Compile the Code**:
   ```sh
   g++ -o image_processing_tool image_processing_tool.cpp `pkg-config --cflags --libs opencv4`
   ```

3. **Run the Application**:
   ```sh
   ./image_processing_tool
