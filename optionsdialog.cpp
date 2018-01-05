#include <QtGui>
#include <QFile>
#include <QException>
#include <QScopedPointer>

#include "optionsdialog.h"
#include "ui_optionsdialog.h"

#include "mainwindow.h"
#include "advancedoptionsdialog.h"

OptionsDialog::OptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui_options(new Ui::OptionsDialog)
{
    ui_options->setupUi(this);

    /** removing unneeded buttons from the title bar */
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

    ui_options->comboBoxARatio->addItems({ "16:9 Widescreen",
                                           "16:10 Widescreen" });

    ui_options->comboBoxAA->addItems({  "NONE",
                                        "FXAA",
                                        "Temporal AA" });


    ui_options->comboBoxAFiltering->addItems({ "OFF (Best performance)",
                                               "2x Smaples",
                                               "4x Smaples",
                                               "8x Smaples",
                                               "16x Smaples" });

    this->LoadPresets();
//    SwitchScreenRatios(ui_options->comboBoxVResolution->currentIndex());
}

OptionsDialog::~OptionsDialog()
{
    delete ui_options;
}

void OptionsDialog::SwitchScreenRatios(int index_ = 0)
{
    SetResolutionsList(index_);
}

void OptionsDialog::SetResolutionsList(int index_ = 0)
{
    ui_options->comboBoxVResolution->clear();

    settingLOD = 0;//Default initialization

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();

    QString strFirstParam = QString::number( width ) +
                            "x" +
                            QString::number( height) +
                            " (Current Desktop)";

    switch (index_){
        case 1:
            ui_options->comboBoxVResolution->addItems({ strFirstParam,
                                                        "1280×800 WXGA",
                                                        "1440×900 WXGA+",
                                                        "1680×1050 WSXGA+",
                                                        "1920×1200 WUXGA",
                                                        "2560×1600 WQXGA" });
            break;
        default://16:9
            ui_options->comboBoxVResolution->addItems({ strFirstParam,
                                                        "1280x720 HD",
                                                        "1366x768",
                                                        "1600x900 HD+",
                                                        "1920x1080 Full HD",
                                                        "2048x1152",
                                                        "2560x1440 QHD",
                                                        "2880x1620",
                                                        "3200x1800 QHD+",
                                                        "3840x2160 4K UHD",
                                                        "4096x2304 Full 4K UHD",
                                                        "5120x2880 5K UHD",
                                                        "7680x4320 8K UHD",
                                                        "8192x4608 Full 8K UHD" });
            break;
    }

}

void OptionsDialog::on_buttonBox_accepted()
{
    HoldControl();

    SavePresets();

    /**
     * @brief m_window - parent MainWindow
     */
    MainWindow * m_window = qobject_cast<MainWindow *>(parent());
    m_window->ReturnControl();
    this->hide();
}

void OptionsDialog::on_buttonBox_rejected()
{
    MainWindow * m_window = qobject_cast<MainWindow *>(parent());
    m_window->ReturnControl();
    this->hide();
}

void OptionsDialog::on_pushButton_AdvSettings_pressed()
{
    HoldControl();

    QScopedPointer<AdvancedOptionsDialog> oDialog(new AdvancedOptionsDialog(this));

    oDialog->showNormal();
    oDialog->exec();
}

void OptionsDialog::HoldControl(){
    ui_options->buttonBox->setEnabled(false);
    ui_options->checkBox_IsWindowed->setEnabled(false);
    ui_options->checkBox_WindowBorderStyle->setEnabled(false);
    ui_options->comboBoxAA->setEnabled(false);
    ui_options->comboBoxAFiltering->setEnabled(false);
    ui_options->comboBoxARatio->setEnabled(false);
    ui_options->comboBoxVResolution->setEnabled(false);
    ui_options->pushButtonVLow->setEnabled(false);
    ui_options->pushButtonVMed->setEnabled(false);
    ui_options->pushButton_VHigh->setEnabled(false);
    ui_options->pushButton_VEpic->setEnabled(false);
    ui_options->pushButton_VideoReset->setEnabled(false);
    //uncomment if implement advanced options
    //ui_options->pushButton_AdvSettings->setEnabled(false);
}

void OptionsDialog::ReleaseControl(){
    ui_options->buttonBox->setEnabled(true);
    ui_options->checkBox_IsWindowed->setEnabled(true);
    ui_options->checkBox_WindowBorderStyle->setEnabled(true);
    ui_options->comboBoxAA->setEnabled(true);
    ui_options->comboBoxAFiltering->setEnabled(true);
    ui_options->comboBoxARatio->setEnabled(true);
    ui_options->comboBoxVResolution->setEnabled(true);
    ui_options->pushButtonVLow->setEnabled(true);
    ui_options->pushButtonVMed->setEnabled(true);
    ui_options->pushButton_VHigh->setEnabled(true);
    ui_options->pushButton_VEpic->setEnabled(true);
    ui_options->pushButton_VideoReset->setEnabled(true);
    //uncomment if implement advanced options
    //ui_options->pushButton_AdvSettings->setEnabled(true);
}

/** call it from child dialog */
void OptionsDialog::ReturnControl(){
    ReleaseControl();
}

void OptionsDialog::SavePresets(){
    HoldControl();

    QString s_sRatio_ID,
            s_sAA_ID,
            s_sWidth,
            s_sHeight,
            s_sAF_ID,
            s_sLODLevel,
            s_sWM_ID,
            s_sWB_ID,
            s_isCustom;

    QString filename = QCoreApplication::applicationDirPath() +
                                        "/config/launcher.cfg";

    QFile file_out(filename);
    file_out.open( QIODevice::WriteOnly);

    QTextStream out(&file_out);

    try{
        if(file_out.exists()){
            QFile::remove(filename);
        }

        if(file_out.isOpen()){

            s_sRatio_ID  = QString::number(ui_options->comboBoxARatio->currentIndex());
            s_sAA_ID     = QString::number(ui_options->comboBoxAA->currentIndex()    );

            s_sWidth     = QString::number(ui_options->comboBoxARatio->currentIndex());
            s_sHeight    = QString::number(ui_options->comboBoxARatio->currentIndex());

            s_sAF_ID     = QString::number(ui_options->comboBoxAFiltering->currentIndex());
            s_sLODLevel  = QString::number(this->settingLOD);
            s_sWM_ID     = QString::number(ui_options->checkBox_IsWindowed ? 1 : 0);
            s_sWB_ID     = QString::number(ui_options->checkBox_WindowBorderStyle ? 1 : 0);
            s_isCustom   = QString::number(this->customSettings ? 1 : 0);

            out << "v_screen_ratio \""    << s_sRatio_ID << "\"" << endl;
            out << "v_aa \""              << s_sAA_ID    << "\"" << endl;
            out << "v_screen_width \""    << s_sWidth    << "\"" << endl;
            out << "v_screen_height \""   << s_sHeight   << "\"" << endl;
            out << "v_aniso_filtering \"" << s_sAF_ID    << "\"" << endl;
            out << "v_lod \""             << s_sLODLevel << "\"" << endl;
            out << "is_windowed \""       << s_sWM_ID    << "\"" << endl;
            out << "is_borderless \""     << s_sWB_ID    << "\"" << endl;
            out << "is_custom \""         << s_isCustom  << "\"" << endl;
        }
    }catch(QException ex){
        throw ex;
    }

    file_out.close();

    ReleaseControl();
}

void OptionsDialog::SetAA(int idx_){
    ui_options->comboBoxAA->setCurrentIndex(idx_);
}

void OptionsDialog::SetAF(int idx_){
    ui_options->comboBoxAFiltering->setCurrentIndex(idx_);
}

void OptionsDialog::SetAR(int idx_){
    ui_options->comboBoxARatio->setCurrentIndex(idx_);
}

void OptionsDialog::SetLD(int idx_){
    this->settingLOD = idx_;
}

void OptionsDialog::SetCM(int idx_){
    this->customSettings = static_cast<bool>(idx_);
}

void OptionsDialog::SetWB(int idx_){
    ui_options->checkBox_WindowBorderStyle->setChecked(static_cast<bool>(idx_));
}

void OptionsDialog::SetWM(int idx_){
    ui_options->checkBox_IsWindowed->setChecked(static_cast<bool>(idx_));
}

void OptionsDialog::SetSR(int s_width, int s_height){
    QString _strPreviousParam = QString::number( s_width ) +
                                "x" +
                                QString::number( s_height) +
                                " (Previous Settings)";

    ui_options->comboBoxVResolution->addItem(_strPreviousParam, 0);
//    SwitchScreenRatios(ui_options->comboBoxVResolution->currentIndex());

}

void OptionsDialog::SetUI_Items(QVector<QString> * sParams_){
    QVector<int> iParamsTemp;

    for(auto &sTemp : *sParams_){
        int start = sTemp.indexOf("\"", 0,     Qt::CaseInsensitive);
        int end   = sTemp.indexOf("\"", ++start, Qt::CaseInsensitive);

        QString str = sTemp.mid(start, end - start);

        iParamsTemp.append(str.toInt());
    }

    SwitchScreenRatios(iParamsTemp.at(0));

    SetAA(iParamsTemp.at(1));

    SetSR(iParamsTemp.at(2), iParamsTemp.at(3));

    SetAF(iParamsTemp.at(4));

    SetLD(iParamsTemp.at(5));

    SetWM(iParamsTemp.at(6));

    SetWB(iParamsTemp.at(7));

    SetCM(iParamsTemp.at(8));

    sParams_->clear();
    iParamsTemp.clear();
}

void OptionsDialog::LoadPresets(){
    QVector<QString> sParams;

    QString filename = QCoreApplication::applicationDirPath() +
                                        "/config/launcher.cfg";

    QFile file(filename);

    if(!file.open(QIODevice::ReadOnly)) {
        QString default_filename = QCoreApplication::applicationDirPath() +
                                            "/config/default_launcher.cfg";

        QFile default_cfg_file(default_filename);

        if ( default_cfg_file.open(QIODevice::ReadOnly) )
        {
            QFile file_out(filename);
            file_out.open( QIODevice::WriteOnly);

            QTextStream in(&default_cfg_file);
            QTextStream out(&file_out);

            if(file_out.isOpen()){
                while (!in.atEnd())
                {
                    QString line = in.readLine();

                    out << line <<endl;
                }
            }

            file_out.close();
            default_cfg_file.close();
        }

        file.open(QIODevice::ReadOnly);
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        sParams.push_back(line);
    }

    file.close();

    SetUI_Items(&sParams);
}

void OptionsDialog::on_comboBoxARatio_currentIndexChanged(int index)
{
    SwitchScreenRatios(index);
}
