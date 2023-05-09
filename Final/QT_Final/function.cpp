#include "Header.h"

void load_data(string& path, vector<Mat>& images) {
    vector<string> file_names;
    cv::glob(path, file_names);
    int s = file_names.size();
    images.resize(s);
    #pragma omp parallel for num_threads(omp_get_max_threads())
    for (int i = 0; i < s; ++i) {
        images[i] = imread(file_names[i]);
    }
}

void CurvatureFilter(Mat& images, int iteration)
{
    int width = images.cols;
    int height = images.rows;
    Mat mirimg;
    Vec3b img_ij, img_prev, img_next, img_left, img_rigt, img_leUp, img_riUp, img_leDn, img_riDn;
    double d, d1, d2, d3, d4, d5, d6, d7, d8;
    Mat emptyImage(height, width, CV_8UC3, Scalar(0, 0, 0));
    copyMakeBorder(images, mirimg, 2, 2, 2, 2, BORDER_REFLECT);

    for (int times = 0; times < iteration; times++)
    {
        for (int y = 2; y < images.rows + 2; y++)
        {
            for (int x = 2; x < images.cols + 2; x++)
            {
                img_ij = mirimg.at<Vec3b>(y, x);
                img_prev = mirimg.at<Vec3b>(y - 2, x);
                img_next = mirimg.at<Vec3b>(y + 2, x);
                img_left = mirimg.at<Vec3b>(y, x - 2);
                img_rigt = mirimg.at<Vec3b>(y, x + 2);
                img_leUp = mirimg.at<Vec3b>(y - 2, x - 2);
                img_riUp = mirimg.at<Vec3b>(y - 2, x + 2);
                img_leDn = mirimg.at<Vec3b>(y + 2, x - 2);
                img_riDn = mirimg.at<Vec3b>(y + 2, x + 2);
                for (int k = 0; k < 3; k++)
                {
                    d = 10000.0;
                    d1 = (img_prev.val[k] + img_next.val[k]) / 2.0 - img_ij.val[k];
                    d2 = (img_left.val[k] + img_rigt.val[k]) / 2.0 - img_ij.val[k];
                    d3 = (img_leUp.val[k] + img_riDn.val[k]) / 2.0 - img_ij.val[k];
                    d4 = (img_leDn.val[k] + img_riUp.val[k]) / 2.0 - img_ij.val[k];
                    d5 = (img_prev.val[k] + img_leUp.val[k] + img_left.val[k]) / 3.0 - img_ij.val[k];
                    d6 = (img_prev.val[k] + img_riUp.val[k] + img_rigt.val[k]) / 3.0 - img_ij.val[k];
                    d7 = (img_leDn.val[k] + img_left.val[k] + img_next.val[k]) / 3.0 - img_ij.val[k];
                    d8 = (img_rigt.val[k] + img_riDn.val[k] + img_next.val[k]) / 3.0 - img_ij.val[k];

                    if (abs(d2) <= abs(d1)) d = d2;
                    else d = d1;

                    if (abs(d3) <= abs(d)) d = d3;
                    if (abs(d4) <= abs(d)) d = d4;
                    if (abs(d5) <= abs(d)) d = d5;
                    if (abs(d6) <= abs(d)) d = d6;
                    if (abs(d7) <= abs(d)) d = d7;
                    if (abs(d8) <= abs(d)) d = d8;
                    img_ij.val[k] += d;
                    emptyImage.at<Vec3b>(y - 2, x - 2) = img_ij;
                }
            }
        }
        copyMakeBorder(emptyImage, mirimg, 2, 2, 2, 2, BORDER_REFLECT);
    }
    images = emptyImage;
}

void gamma_transformation(Mat scr, Mat& dst, double gamma)
{
    double c;
    double r_min, r_max;
    minMaxLoc(scr, &r_min, &r_max);
    c = 255 / pow(r_max, gamma);
    scr.convertTo(scr, CV_32F);
    pow(scr, gamma, dst);
    dst = c * dst;
    dst.convertTo(dst, CV_8UC3);
}

void contrast_evaluation(Mat& dst, Scalar mean)
{
    Scalar dst_mean;
    Scalar val;
    vector<Mat> channels;
    Mat hsv_image;
    val[0] = 300;
    val[1] = 300;
    val[2] = 300;
    int n = 0;
    while (!(abs(val[0]) < 10 || abs(val[1]) < 10 || abs(val[2]) < 10) && n < 15)
    {
        dst_mean = cv::mean(dst);
        val = mean - dst_mean;
        if (val[0] > 10 && val[1] > 10 && val[2] > 10)
            gamma_transformation(dst, dst, 0.8);
        else if (val[0] < -10 && val[1] < -10 && val[2] < -10)
            gamma_transformation(dst, dst, 1.2);
        n++;
    }
}

Scalar evaluate_mean(vector<Mat>& images)
{
    Scalar All_mean = 0;
    Scalar mean;
    
    for (int i = 0; i < images.size(); ++i)
    {
        mean = cv::mean(images[i]);
        All_mean += mean;
    }        
    return All_mean / (double)images.size();
}

void contrast(vector<Mat>& images)
{
    vector<Mat> hsv_channels;
    Mat hsv_image;
    Scalar All_mean = evaluate_mean(images);
    #pragma omp parallel for num_threads(omp_get_max_threads())
    for (int i = 0; i < images.size(); ++i)
    {
        contrast_evaluation(images[i], All_mean);
    }    
}

Scalar getMSSIM_CUDA_optimized(Mat& i1, Mat& i2, BufferMSSIM& b)
{
    const float C1 = 6.5025f, C2 = 58.5225f;
    /***************************** INITS **********************************/

    b.gI1.upload(i1);
    b.gI2.upload(i2);

    cuda::Stream stream;

    b.gI1.convertTo(b.t1, CV_32F, stream);
    b.gI2.convertTo(b.t2, CV_32F, stream);

    cuda::split(b.t1, b.vI1, stream);
    cuda::split(b.t2, b.vI2, stream);
    Scalar mssim;

    Ptr<cuda::Filter> gauss = cuda::createGaussianFilter(b.vI1[0].type(), -1, Size(11, 11), 1.5);

    for (int i = 0; i < b.gI1.channels(); ++i)
    {
        cuda::multiply(b.vI2[i], b.vI2[i], b.I2_2, 1, -1, stream);        // I2^2
        cuda::multiply(b.vI1[i], b.vI1[i], b.I1_2, 1, -1, stream);        // I1^2
        cuda::multiply(b.vI1[i], b.vI2[i], b.I1_I2, 1, -1, stream);       // I1 * I2

        gauss->apply(b.vI1[i], b.mu1, stream);
        gauss->apply(b.vI2[i], b.mu2, stream);

        cuda::multiply(b.mu1, b.mu1, b.mu1_2, 1, -1, stream);
        cuda::multiply(b.mu2, b.mu2, b.mu2_2, 1, -1, stream);
        cuda::multiply(b.mu1, b.mu2, b.mu1_mu2, 1, -1, stream);

        gauss->apply(b.I1_2, b.sigma1_2, stream);
        cuda::subtract(b.sigma1_2, b.mu1_2, b.sigma1_2, cuda::GpuMat(), -1, stream);
        //b.sigma1_2 -= b.mu1_2;  - This would result in an extra data transfer operation

        gauss->apply(b.I2_2, b.sigma2_2, stream);
        cuda::subtract(b.sigma2_2, b.mu2_2, b.sigma2_2, cuda::GpuMat(), -1, stream);
        //b.sigma2_2 -= b.mu2_2;

        gauss->apply(b.I1_I2, b.sigma12, stream);
        cuda::subtract(b.sigma12, b.mu1_mu2, b.sigma12, cuda::GpuMat(), -1, stream);
        //b.sigma12 -= b.mu1_mu2;

        //here too it would be an extra data transfer due to call of operator*(Scalar, Mat)
        cuda::multiply(b.mu1_mu2, 2, b.t1, 1, -1, stream); //b.t1 = 2 * b.mu1_mu2 + C1;
        cuda::add(b.t1, C1, b.t1, cuda::GpuMat(), -1, stream);
        cuda::multiply(b.sigma12, 2, b.t2, 1, -1, stream); //b.t2 = 2 * b.sigma12 + C2;
        cuda::add(b.t2, C2, b.t2, cuda::GpuMat(), -12, stream);

        cuda::multiply(b.t1, b.t2, b.t3, 1, -1, stream);     // t3 = ((2*mu1_mu2 + C1).*(2*sigma12 + C2))

        cuda::add(b.mu1_2, b.mu2_2, b.t1, cuda::GpuMat(), -1, stream);
        cuda::add(b.t1, C1, b.t1, cuda::GpuMat(), -1, stream);

        cuda::add(b.sigma1_2, b.sigma2_2, b.t2, cuda::GpuMat(), -1, stream);
        cuda::add(b.t2, C2, b.t2, cuda::GpuMat(), -1, stream);


        cuda::multiply(b.t1, b.t2, b.t1, 1, -1, stream);     // t1 =((mu1_2 + mu2_2 + C1).*(sigma1_2 + sigma2_2 + C2))
        cuda::divide(b.t3, b.t1, b.ssim_map, 1, -1, stream);      // ssim_map =  t3./t1;

        stream.waitForCompletion();

        Scalar s = cuda::sum(b.ssim_map, b.buf);
        mssim.val[i] = s.val[0] / (b.ssim_map.rows * b.ssim_map.cols);

    }
    return mssim;
}

Scalar getMSSIM(Mat& i1, Mat& i2)
{
    const double C1 = 6.5025, C2 = 58.5225;
    /***************************** INITS **********************************/
    int d = CV_32F;
    Mat I1, I2;
    i1.convertTo(I1, d);           // cannot calculate on one byte large values
    i2.convertTo(I2, d);
    Mat I2_2 = I2.mul(I2);        // I2^2
    Mat I1_2 = I1.mul(I1);        // I1^2
    Mat I1_I2 = I1.mul(I2);        // I1 * I2
    /*************************** END INITS **********************************/
    Mat mu1, mu2;   // PRELIMINARY COMPUTING
    GaussianBlur(I1, mu1, Size(11, 11), 1.5);
    GaussianBlur(I2, mu2, Size(11, 11), 1.5);
    Mat mu1_2 = mu1.mul(mu1);
    Mat mu2_2 = mu2.mul(mu2);
    Mat mu1_mu2 = mu1.mul(mu2);
    Mat sigma1_2, sigma2_2, sigma12;
    GaussianBlur(I1_2, sigma1_2, Size(11, 11), 1.5);
    sigma1_2 -= mu1_2;
    GaussianBlur(I2_2, sigma2_2, Size(11, 11), 1.5);
    sigma2_2 -= mu2_2;
    GaussianBlur(I1_I2, sigma12, Size(11, 11), 1.5);
    sigma12 -= mu1_mu2;
    Mat t1, t2, t3;
    t1 = 2 * mu1_mu2 + C1;
    t2 = 2 * sigma12 + C2;
    t3 = t1.mul(t2);              // t3 = ((2*mu1_mu2 + C1).*(2*sigma12 + C2))
    t1 = mu1_2 + mu2_2 + C1;
    t2 = sigma1_2 + sigma2_2 + C2;
    t1 = t1.mul(t2);               // t1 =((mu1_2 + mu2_2 + C1).*(sigma1_2 + sigma2_2 + C2))
    Mat ssim_map;
    divide(t3, t1, ssim_map);      // ssim_map =  t3./t1;
    Scalar mssim = mean(ssim_map); // mssim = average of ssim map
    return mssim;
}

void sort_frames_L2S(map<int, double> map, vector<int>& frame_sequence, int n_frames, int RATIO) {
    /*---------------------------Sort Map By Value---------------------------*/
    vector<int> keys;
    for (auto const& pair : map) {
        keys.push_back(pair.first);
    }
    sort(keys.begin(), keys.end(), [&map](int const& lhs, double const& rhs) {
        return map.at(lhs) > map.at(rhs);
        });
    /*---------------------------Sort Frames---------------------------*/
    int a, b;
    while (1) {
        if (frame_sequence.size() == n_frames)
            break;
        for (auto const& key : keys) {
            if (frame_sequence.size() == n_frames)
                break;
            a = key / RATIO;
            b = key % RATIO;
            if (frame_sequence.empty()) {
                frame_sequence.insert(frame_sequence.begin(), a);
                frame_sequence.push_back(b);
                keys.erase(remove(keys.begin(), keys.end(), key), keys.end());
                continue;
            }
            if (find(frame_sequence.begin(), frame_sequence.end(), a) != frame_sequence.end() && find(frame_sequence.begin(), frame_sequence.end(), b) != frame_sequence.end()) {
                keys.erase(remove(keys.begin(), keys.end(), key), keys.end());
                break;
            }
            if (frame_sequence.front() == a) {
                frame_sequence.insert(frame_sequence.begin(), b);
                keys.erase(remove(keys.begin(), keys.end(), key), keys.end());
                break;
            }
            else if (frame_sequence.front() == b) {
                frame_sequence.insert(frame_sequence.begin(), a);
                keys.erase(remove(keys.begin(), keys.end(), key), keys.end());
                break;
            }
            else if (frame_sequence.back() == a) {
                frame_sequence.push_back(b);
                keys.erase(remove(keys.begin(), keys.end(), key), keys.end());
                break;
            }
            else if (frame_sequence.back() == b) {
                frame_sequence.push_back(a);
                keys.erase(remove(keys.begin(), keys.end(), key), keys.end());
                break;
            }
        }
    }
}

void sort_frames_S2L(map<int, double> map, vector<int>& frame_sequence, int n_frames, int RATIO) {
    /*---------------------------Sort Map By Value---------------------------*/
    vector<int> keys;
    for (auto const& pair : map) {
        keys.push_back(pair.first);
    }
    sort(keys.begin(), keys.end(), [&map](int const& lhs, double const& rhs) {
        return map.at(lhs) < map.at(rhs);
        });
    /*---------------------------Sort Frames---------------------------*/
    int a, b;
    while (1) {
        if (frame_sequence.size() == n_frames)
            break;
        for (auto const& key : keys) {
            if (frame_sequence.size() == n_frames)
                break;
            a = key / RATIO;
            b = key % RATIO;
            if (frame_sequence.empty()) {
                frame_sequence.insert(frame_sequence.begin(), a);
                frame_sequence.push_back(b);
                keys.erase(remove(keys.begin(), keys.end(), key), keys.end());
                continue;
            }
            if (find(frame_sequence.begin(), frame_sequence.end(), a) != frame_sequence.end() && find(frame_sequence.begin(), frame_sequence.end(), b) != frame_sequence.end()) {
                keys.erase(remove(keys.begin(), keys.end(), key), keys.end());
                break;
            }
            if (frame_sequence.front() == a) {
                frame_sequence.insert(frame_sequence.begin(), b);
                keys.erase(remove(keys.begin(), keys.end(), key), keys.end());
                break;
            }
            else if (frame_sequence.front() == b) {
                frame_sequence.insert(frame_sequence.begin(), a);
                keys.erase(remove(keys.begin(), keys.end(), key), keys.end());
                break;
            }
            else if (frame_sequence.back() == a) {
                frame_sequence.push_back(b);
                keys.erase(remove(keys.begin(), keys.end(), key), keys.end());
                break;
            }
            else if (frame_sequence.back() == b) {
                frame_sequence.push_back(a);
                keys.erase(remove(keys.begin(), keys.end(), key), keys.end());
                break;
            }
        }
    }
}

void write_txt(string path, vector<int> frame_sequence) {
    ofstream out(path);
    for (int i : frame_sequence) {
        out << i << endl;
    }
    out.close();
}

void write_video(string path, vector<Mat> images_RGB, vector<int> frame_sequence, int fps) {
    int width = images_RGB[0].cols;
    int height = images_RGB[0].rows;
    VideoWriter writer(path, VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, Size(width, height));
    for (int i = 0; i < images_RGB.size(); i++) {
        writer.write(images_RGB[frame_sequence[i] - 1]);
    }
    writer.release();
}

double cal_SRCC(string& predict_path, string& truth_path) {
    string line;
    //read predict txt file
    vector<string> predict_vector;
    ifstream predict_file(predict_path);
    if (predict_file.is_open()) {
        while (getline(predict_file, line)) {
            predict_vector.push_back(line);
        }
        predict_file.close();
    }
    //read label txt file
    vector<string> label_vector;
    ifstream label_file(truth_path);
    if (label_file.is_open()) {
        while (getline(label_file, line)) {
            label_vector.push_back(line);
        }
        label_file.close();
    }
    if (predict_vector.size() != label_vector.size()) {
        return -1;
    }
    //calculate SRCC
    double diff = 0;
    for (int i = 0; i < predict_vector.size(); i++) {
        diff += pow(stod(predict_vector[i]) - stod(label_vector[i]), 2);
    }
    double n = predict_vector.size();

    return abs(1.0 - (6.0 * diff) / ((pow(n, 3) - n)));
}

double cal_SRCC_reverse(string& predict_path, string& truth_path) {
    string line;
    //read predict txt file
    vector<string> predict_vector;
    ifstream predict_file(predict_path);
    if (predict_file.is_open()) {
        while (getline(predict_file, line)) {
            predict_vector.push_back(line);
        }
        predict_file.close();
    }
    //read label txt file
    vector<string> label_vector;
    ifstream label_file(truth_path);
    if (label_file.is_open()) {
        while (getline(label_file, line)) {
            label_vector.push_back(line);
        }
        label_file.close();
    }
    if (predict_vector.size() != label_vector.size()) {
        return -1;
    }
    //inverse predict
    reverse(predict_vector.begin(), predict_vector.end());
    //calculate SRCC
    double diff = 0;
    for (int i = 0; i < predict_vector.size(); i++) {
        diff += pow(stod(predict_vector[i]) - stod(label_vector[i]), 2);
    }
    double n = predict_vector.size();

    return abs(1.0 - (6.0 * diff) / ((pow(n, 3) - n)));
}

double compute_MSE(Mat Mat1, Mat Mat2)
{
    Mat M1 = Mat1.clone();
    Mat M2 = Mat2.clone();
    Mat Diff;

    M1.convertTo(M1, CV_32F);
    M2.convertTo(M2, CV_32F);
    Diff.convertTo(Diff, CV_32F);

    absdiff(M1, M2, Diff);

    Diff = Diff.mul(Diff);
    Scalar S = sum(Diff);

    double sse;
    if (Diff.channels() == 3)
        sse = S.val[0] + S.val[1] + S.val[2];
    else
        sse = S.val[0];

    int nTotalElement = M2.channels() * M2.total();

    double mse = (sse / (double)nTotalElement);

    return mse;
}

double cal_MSE(vector<Mat> images_RGB, vector<int> frame_sequence, string Ground_Truth_path)
{
    string Ground_Truth_image_path = Ground_Truth_path + "/*.png";
    vector<Mat> Ground_Truth_image;
    load_data(Ground_Truth_image_path, Ground_Truth_image);
    double mse = 0;
    for (int i = 1; i < Ground_Truth_image.size(); i++)
    {
        mse += compute_MSE(images_RGB[frame_sequence[i] - 1], Ground_Truth_image[i]);
    }
    return mse / (double)Ground_Truth_image.size();
}

double cal_MSE_reverse(vector<Mat> images_RGB, vector<int> frame_sequence, string Ground_Truth_path)
{
    string Ground_Truth_image_path = Ground_Truth_path + "/*.png";
    vector<Mat> Ground_Truth_image;
    load_data(Ground_Truth_image_path, Ground_Truth_image);
    double mse = 0;
    for (int i = 1; i < Ground_Truth_image.size(); i++)
    {
        mse += compute_MSE(images_RGB[frame_sequence[Ground_Truth_image.size() - i - 1] - 1], Ground_Truth_image[i]);
    }
    return mse / (double)Ground_Truth_image.size();
}