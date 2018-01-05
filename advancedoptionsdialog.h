#ifndef ADVANCEDOPTIONSDIALOG_H
#define ADVANCEDOPTIONSDIALOG_H

#include <QDialog>

namespace Ui {
class AdvancedOptionsDialog;
}

class AdvancedOptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AdvancedOptionsDialog(QWidget *parent = 0);
    ~AdvancedOptionsDialog();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::AdvancedOptionsDialog *ui_advance_options;

    void SavePresets();
    void LoadPresets();

    void HideMe();
};

#endif // ADVANCEDOPTIONSDIALOG_H
