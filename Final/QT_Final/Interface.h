//#include <QtWidgets/QMainWindow>
#include "ui_Interface.h"

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>
#include <QLabel>
#include <QMessageBox>
#include <QTextEdit>
#include <QCheckBox>

class Interface : public QWidget
{
    Q_OBJECT

public:
    Interface(QWidget *parent = nullptr);
    ~Interface();

private slots:
    void browseDataSetPath();
    void browseOutputPath();
    void slotCheckBoxMSSIMChanged(int state);
    void slotCheckBoxPHashChanged(int state);
    void runProgram();
    void browse_predict_txt_File();
    void browse_answer_txt_File();
    void browse_ground_truth_Path();
    void Cal_SRCC();

private:
    QLabel* dataSetPathLabel;
    QLineEdit* dataSetPathLineEdit;
    QPushButton* browseDataSetPathButton;

    QLabel* outputPathLabel;
    QLineEdit* outputPathLineEdit;
    QPushButton* browseOutputPathButton;

    QLabel* outputNameLabel;
    QLineEdit* outputNameLineEdit;

    QLabel* fpsLabel;
    QLineEdit* fpsLineEdit;

    QLabel* filterIterationLabel;
    QLineEdit* filterIterationLineEdit;

    QLabel* methodLabel;
    QCheckBox* MSSIM_CheckBox;
    QCheckBox* PHash_CheckBox;
    QCheckBox* Contrast_CheckBox;

    QPushButton* runProgramButton;

    QLabel* predict_txt_PathLabel;
    QLineEdit* predict_txt_FileLineEdit;
    QPushButton* browse_predict_txt_PathButton;

    QLabel* answer_txt_PathLabel;
    QLineEdit* answer_txt_FileLineEdit;
    QPushButton* browse_answer_txt_PathButton;

    QLabel* ground_truth_PathLabel;
    QLineEdit* ground_truth_PathLineEdit;
    QPushButton* browse_ground_truth_PathButton;
    
    QPushButton* Cal_SRCC_Button;

    // Layout
    QHBoxLayout* dataSetPathLayout;
    QHBoxLayout* outputPathLayout;
    QHBoxLayout* outputNameLayout;
    QHBoxLayout* fpsLayout;
    QHBoxLayout* filterIterationLayout;
    QHBoxLayout* methodLayout;

    QTextEdit* commandOutput;

    QHBoxLayout* predict_txt_Layout;
    QHBoxLayout* answer_txt_Layout;
    QHBoxLayout* ground_truth_Layout;

    QTextEdit* SRCC_Output;

    QVBoxLayout* mainLayout;
};