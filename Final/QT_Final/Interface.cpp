#include "Interface.h"
#include "Header.h"

template <typename T>
inline int CalculateAndCompareHash(const Mat& a, const Mat& b)
{
    Mat hashA, hashB;
    Ptr<ImgHashBase> func;
    func = T::create();
    func->compute(a, hashA);
    func->compute(b, hashB);
    return (int)func->compare(hashA, hashB);
}

Interface::Interface(QWidget *parent)
    : QWidget(parent)
{
    /*-----------------------------------Initialize-----------------------------------*/
    dataSetPathLabel = new QLabel("DataSet Path:");
    dataSetPathLineEdit = new QLineEdit;
    dataSetPathLineEdit->setPlaceholderText("Dataset Path");
    browseDataSetPathButton = new QPushButton("Browse");
    connect(browseDataSetPathButton, SIGNAL(clicked()), this, SLOT(browseDataSetPath()));

    outputPathLabel = new QLabel("Output Path:");
    outputPathLineEdit = new QLineEdit;
    outputPathLineEdit->setPlaceholderText("Output Path");
    browseOutputPathButton = new QPushButton("Browse");
    connect(browseOutputPathButton, SIGNAL(clicked()), this, SLOT(browseOutputPath()));

    ground_truth_PathLabel = new QLabel("Ground Truth Path:");
    ground_truth_PathLineEdit = new QLineEdit;
    ground_truth_PathLineEdit->setPlaceholderText("Ground Truth Path");
    browse_ground_truth_PathButton = new QPushButton("Browse");
    connect(browse_ground_truth_PathButton, SIGNAL(clicked()), this, SLOT(browse_ground_truth_Path()));

    outputNameLabel = new QLabel("Output Name:");
    outputNameLineEdit = new QLineEdit;
    outputNameLineEdit->setPlaceholderText("Output Name");

    fpsLabel = new QLabel("FPS:");
    fpsLineEdit = new QLineEdit;
    fpsLineEdit->setPlaceholderText("30");

    filterIterationLabel = new QLabel("Filter Iteration:");
    filterIterationLineEdit = new QLineEdit;
    filterIterationLineEdit->setPlaceholderText("10");

    methodLabel = new QLabel("Choose a method to run program:");
    MSSIM_CheckBox = new QCheckBox("MSSIM", this);
    PHash_CheckBox = new QCheckBox("PHash", this);
    Contrast_CheckBox = new QCheckBox("Constrast Adjustment");
    connect(MSSIM_CheckBox, SIGNAL(stateChanged(int)), this, SLOT(slotCheckBoxMSSIMChanged(int)));
    connect(PHash_CheckBox, SIGNAL(stateChanged(int)), this, SLOT(slotCheckBoxPHashChanged(int)));

    runProgramButton = new QPushButton("Run Program");
    connect(runProgramButton, SIGNAL(clicked()), this, SLOT(runProgram()));

    commandOutput = new QTextEdit;
    commandOutput->setReadOnly(true);
    commandOutput->setFixedHeight(500);

    predict_txt_PathLabel = new QLabel("Predict txt File:");
    predict_txt_FileLineEdit = new QLineEdit;
    predict_txt_FileLineEdit->setPlaceholderText("Predict txt File");
    browse_predict_txt_PathButton = new QPushButton("Browse");
    connect(browse_predict_txt_PathButton, SIGNAL(clicked()), this, SLOT(browse_predict_txt_File()));

    answer_txt_PathLabel = new QLabel("Answer txt File:");
    answer_txt_FileLineEdit = new QLineEdit;
    answer_txt_FileLineEdit->setPlaceholderText("Answer txt File");
    browse_answer_txt_PathButton = new QPushButton("Browse");
    connect(browse_answer_txt_PathButton, SIGNAL(clicked()), this, SLOT(browse_answer_txt_File()));

    Cal_SRCC_Button = new QPushButton("Calculate SRCC");
    connect(Cal_SRCC_Button, SIGNAL(clicked()), this, SLOT(Cal_SRCC()));

    SRCC_Output = new QTextEdit;
    SRCC_Output->setReadOnly(true);
    /*-----------------------------------Add Widget-----------------------------------*/
    dataSetPathLayout = new QHBoxLayout;
    dataSetPathLayout->addWidget(dataSetPathLabel);
    dataSetPathLayout->addWidget(dataSetPathLineEdit);
    dataSetPathLayout->addWidget(browseDataSetPathButton);

    outputPathLayout = new QHBoxLayout;
    outputPathLayout->addWidget(outputPathLabel);
    outputPathLayout->addWidget(outputPathLineEdit);
    outputPathLayout->addWidget(browseOutputPathButton);

    ground_truth_Layout = new QHBoxLayout;
    ground_truth_Layout->addWidget(ground_truth_PathLabel);
    ground_truth_Layout->addWidget(ground_truth_PathLineEdit);
    ground_truth_Layout->addWidget(browse_ground_truth_PathButton);

    outputNameLayout = new QHBoxLayout;
    outputNameLayout->addWidget(outputNameLabel);
    outputNameLayout->addWidget(outputNameLineEdit);

    fpsLayout = new QHBoxLayout;
    fpsLayout->addWidget(fpsLabel);
    fpsLayout->addWidget(fpsLineEdit);

    filterIterationLayout = new QHBoxLayout;
    filterIterationLayout->addWidget(filterIterationLabel);
    filterIterationLayout->addWidget(filterIterationLineEdit);

    methodLayout = new QHBoxLayout;
    methodLayout->addWidget(methodLabel);
    methodLayout->addWidget(MSSIM_CheckBox);
    methodLayout->addWidget(PHash_CheckBox);
    methodLayout->addWidget(Contrast_CheckBox);

    predict_txt_Layout = new QHBoxLayout;
    predict_txt_Layout->addWidget(predict_txt_PathLabel);
    predict_txt_Layout->addWidget(predict_txt_FileLineEdit);
    predict_txt_Layout->addWidget(browse_predict_txt_PathButton);

    answer_txt_Layout = new QHBoxLayout;
    answer_txt_Layout->addWidget(answer_txt_PathLabel);
    answer_txt_Layout->addWidget(answer_txt_FileLineEdit);
    answer_txt_Layout->addWidget(browse_answer_txt_PathButton);

    //Main Layout
    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(dataSetPathLayout);
    mainLayout->addLayout(outputPathLayout);
    mainLayout->addLayout(ground_truth_Layout);
    mainLayout->addLayout(outputNameLayout);
    mainLayout->addLayout(fpsLayout);
    mainLayout->addLayout(filterIterationLayout);
    mainLayout->addLayout(methodLayout);
    mainLayout->addWidget(runProgramButton);
    mainLayout->addWidget(commandOutput);
    mainLayout->addLayout(predict_txt_Layout);
    mainLayout->addLayout(answer_txt_Layout);
    mainLayout->addWidget(Cal_SRCC_Button);
    mainLayout->addWidget(SRCC_Output);

    setLayout(mainLayout);
    setWindowTitle("ADIP Final Project Team 7");
}
/*-----------------------------------XXXXXXXXX-----------------------------------*/
Interface::~Interface()
{

}
/*-----------------------------------Functions-----------------------------------*/
void Interface::browseDataSetPath()
{
    QString dataSetPath = QFileDialog::getExistingDirectory(this, "Choose Path",
        QDir::currentPath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    dataSetPathLineEdit->setText(dataSetPath);
}

void Interface::browseOutputPath()
{
    QString outputPath = QFileDialog::getExistingDirectory(this, "Choose Path",
        QDir::currentPath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    outputPathLineEdit->setText(outputPath);
}

void Interface::slotCheckBoxMSSIMChanged(int state)
{
    if (state == Qt::Checked)
    {
        PHash_CheckBox->setCheckState(Qt::Unchecked);
    }
}

void Interface::slotCheckBoxPHashChanged(int state)
{
    if (state == Qt::Checked)
    {
        MSSIM_CheckBox->setCheckState(Qt::Unchecked);
    }
}

void Interface::runProgram()
{
    commandOutput->clear();
    QString dataSetPath = dataSetPathLineEdit->text();
    QString outputPath = outputPathLineEdit->text();
    QString outputName = outputNameLineEdit->text();
    QString ground_truth_path = ground_truth_PathLineEdit->text();
    int fps = fpsLineEdit->text().toInt();
    int filterIteration = filterIterationLineEdit->text().toInt();

    if (dataSetPath.isEmpty() || outputPath.isEmpty() || outputName.isEmpty() || fps == 0 || filterIteration == 0)
    {
        QMessageBox::warning(this, "Warning", "Please input valid parameters!");
        return;
    }

    if (!MSSIM_CheckBox->isChecked() && !PHash_CheckBox->isChecked())
    {
        QMessageBox::warning(this, "Warning", "Please select one method!");
        return;
    }
    /*------------------------------------------------------------------------------------------------------------------------------*/
    /*-------------------------------------------------------------main-------------------------------------------------------------*/
    /*------------------------------------------------------------------------------------------------------------------------------*/
    TickMeter total_time, load_images_time, curvature_filter_time, constrast_adjustment_time, grayscale_time,
        cuda_MSSIM_time, hash_time, sort_frames_time, write_txt_time, write_video_time;
    vector<Mat> images_RGB;
    const int RATIO = 100000;
    int key;
    double value;
    map<int, double> map;
    total_time.start();
    /*---------------------------Load Images---------------------------*/
    load_images_time.start();
    commandOutput->append("<Loading images...>");
    string img_folder_path = dataSetPath.toStdString() + "/*.png";
    load_data(img_folder_path, images_RGB);
    vector<Mat> images_gray(images_RGB.size());
    load_images_time.stop();
    commandOutput->append(QString::number(load_images_time.getTimeSec()) + " sec.\n");
    /*---------------------------Curvature Filter---------------------------*/
    if (filterIteration > 0)
    {
        curvature_filter_time.start();
        commandOutput->append("<Filtering images...>");
        #pragma omp parallel for num_threads(omp_get_max_threads())
        for (int i = 0; i < images_RGB.size(); i++)
        {
            CurvatureFilter(images_RGB[i], filterIteration);
        }
        curvature_filter_time.stop();
        commandOutput->append(QString::number(curvature_filter_time.getTimeSec()) + " sec.\n");
    }
    /*---------------------------Constrast Adjustment---------------------------*/
    if (Contrast_CheckBox->isChecked())
    {
        constrast_adjustment_time.start();
        commandOutput->append("<Constrast adjusting...>");
        contrast(images_RGB);
        constrast_adjustment_time.stop();
        commandOutput->append(QString::number(constrast_adjustment_time.getTimeSec()) + " sec.\n");
    }    
    /*---------------------------BGR2GRAY---------------------------*/
    grayscale_time.start();
    commandOutput->append("<Gray scaling...>");
    #pragma omp parallel for num_threads(omp_get_max_threads())
    for (int i = 0; i < images_RGB.size(); i++)
    {
        cvtColor(images_RGB[i], images_gray[i], COLOR_BGR2GRAY);
    }
    grayscale_time.stop();
    commandOutput->append(QString::number(grayscale_time.getTimeSec()) + " sec.\n");
    /*---------------------------------MSSIM CUDA Optimized---------------------------------*/
    if (MSSIM_CheckBox->isChecked())
    {
        cuda_MSSIM_time.start();
        commandOutput->append("<Caculating MSSIM...>");
        BufferMSSIM bufferMSSIM;
        for (int i = 0; i < images_gray.size() - 1; i++)
        {
            for (int j = i + 1; j < images_gray.size(); j++)
            {
                key = RATIO * (i + 1) + j + 1;
                value = getMSSIM_CUDA_optimized(images_gray[i], images_gray[j], bufferMSSIM).val[0];
                map.insert(pair<int, double>(key, value));
            }
        }
        cuda_MSSIM_time.stop();
        commandOutput->append(QString::number(cuda_MSSIM_time.getTimeSec()) + " sec.\n");
    }
    /*---------------------------Calculate And Compare Hash---------------------------*/
    if (PHash_CheckBox->isChecked())
    {
        hash_time.start();
        commandOutput->append("<Caculating And Compare Hash...>");

        for (int i = 0; i < images_gray.size() - 1; i++)
        {
            for (int j = i + 1; j < images_gray.size(); j++)
            {
                key = RATIO * (i + 1) + j + 1;
                value = CalculateAndCompareHash<PHash>(images_gray[i], images_gray[j]);
                map.insert(pair<int, double>(key, value));
            }
        }
        hash_time.stop();
        commandOutput->append(QString::number(hash_time.getTimeSec()) + " sec.\n");
    }
    /*---------------------------Sort Frames---------------------------*/
    sort_frames_time.start();
    commandOutput->append("<Sorting Frames...>");
    vector<int> frame_sequence;
    if (MSSIM_CheckBox->isChecked())
    {
        sort_frames_L2S(map, frame_sequence, images_gray.size(), RATIO);
    }
    if (PHash_CheckBox->isChecked())
    {
        sort_frames_S2L(map, frame_sequence, images_gray.size(), RATIO);
    }
    sort_frames_time.stop();
    commandOutput->append(QString::number(sort_frames_time.getTimeSec()) + " sec.\n");
    /*---------------------------Write txt File---------------------------*/
    write_txt_time.start();
    commandOutput->append("<Writing txt File...>");
    write_txt(outputPath.toStdString() + "/" + outputName.toStdString() + ".txt", frame_sequence);
    write_txt_time.stop();
    commandOutput->append(QString::number(write_txt_time.getTimeSec()) + " sec.\n");
    /*---------------------------Write Video---------------------------*/
    write_video_time.start();
    commandOutput->append("<Writing Video...>");
    write_video(outputPath.toStdString() + "/" + outputName.toStdString() + ".avi", images_RGB, frame_sequence, fps);
    write_video_time.stop();
    commandOutput->append(QString::number(write_video_time.getTimeSec()) + " sec.\n");
    /*---------------------------MSE---------------------------*/    
    double MSE = cal_MSE(images_RGB, frame_sequence, ground_truth_path.toStdString());
    double MSE_reverse = cal_MSE_reverse(images_RGB, frame_sequence, ground_truth_path.toStdString());
    commandOutput->append("MSE: " + QString::number(MSE));
    commandOutput->append("Reversed MSE: " + QString::number(MSE_reverse));
    /*---------------------------Time Stop---------------------------*/
    total_time.stop();
    commandOutput->append("\n<Total excution time: " + QString::number(total_time.getTimeSec()) + " sec.>");
}

void Interface::browse_predict_txt_File()
{
    QString predict_txt_File = QFileDialog::getOpenFileName(this, "Choose File",
        QDir::currentPath(), "Text Files (*.txt)");
    predict_txt_FileLineEdit->setText(predict_txt_File);
}

void Interface::browse_answer_txt_File()
{
    QString answer_txt_File = QFileDialog::getOpenFileName(this, "Choose File",
        QDir::currentPath(), "Text Files (*.txt)");
    answer_txt_FileLineEdit->setText(answer_txt_File);
}

void Interface::browse_ground_truth_Path()
{    
    QString ground_truth_path = QFileDialog::getExistingDirectory(this, "Choose Path",
        QDir::currentPath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ground_truth_PathLineEdit->setText(ground_truth_path);
}

void Interface::Cal_SRCC()
{
    SRCC_Output->clear();
    QString predict_txt_Path = predict_txt_FileLineEdit->text();
    QString answer_txt_Path = answer_txt_FileLineEdit->text();    

    if (answer_txt_Path.isEmpty() || predict_txt_Path.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please input valid parameters!");
        return;
    }

    string predict_path = predict_txt_Path.toStdString();
    string truth_path = answer_txt_Path.toStdString();
    double SRCC = cal_SRCC(predict_path, truth_path);
    double SRCC_reverse = cal_SRCC_reverse(predict_path, truth_path);
    SRCC_Output->append("SRCC: " + QString::number(SRCC));
    SRCC_Output->append("Reversed SRCC: " + QString::number(SRCC_reverse));
}