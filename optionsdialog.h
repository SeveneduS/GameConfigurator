#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>
#include <QTextStream>
#include <QVector>

namespace Ui {
class OptionsDialog;
}

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog(QWidget *parent = 0);
    ~OptionsDialog();


    void ReturnControl();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_pushButton_AdvSettings_pressed();

    void on_comboBoxARatio_currentIndexChanged(int index);

private:
    Ui::OptionsDialog *ui_options;

    bool customSettings;

    int  settingLOD;

    void SwitchScreenRatios(int index_);
    void SetResolutionsList(int index_);
    void HoldControl();
    void ReleaseControl();
    void SavePresets();
    void LoadPresets();
    void SetUI_Items(QVector<QString> * sParams_);
    void SetAA(int idx_);
    void SetAF(int idx_);
    void SetAR(int idx_);
    void SetLD(int idx_);
    void SetCM(int idx_);
    void SetWB(int idx_);
    void SetWM(int idx_);
    void SetSR(int s_width, int s_height);
};

#endif // OPTIONSDIALOG_H
