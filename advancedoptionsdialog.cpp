#include "QtGui"

#include "advancedoptionsdialog.h"
#include "ui_advancedoptionsdialog.h"

#include "optionsdialog.h"

AdvancedOptionsDialog::AdvancedOptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui_advance_options(new Ui::AdvancedOptionsDialog)
{
    ui_advance_options->setupUi(this);
}

AdvancedOptionsDialog::~AdvancedOptionsDialog()
{
    delete ui_advance_options;
}

void AdvancedOptionsDialog::HideMe()
{
    OptionsDialog * m_options = qobject_cast<OptionsDialog *>(parent());
    m_options->ReturnControl();
    this->hide();
}

void AdvancedOptionsDialog::on_buttonBox_rejected()
{
    HideMe();
}

void AdvancedOptionsDialog::on_buttonBox_accepted()
{
    /**
     * ToDo:
     *  Save settings into the configuration file
     * */
    HideMe();
}
