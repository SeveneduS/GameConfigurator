#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void ReturnControl();

private slots:
    void on_pushButtonQUIT_clicked();

    void on_pushButtonOPTIONS_clicked();

    void on_pushButtonPLAY_clicked();

    void on_cbShowLog_toggled(bool checked);

private:
    Ui::MainWindow *ui;

    bool showLogWindow = false;

    void HoldButtons();
    void ReleaseButtons();

    inline void init_window_style();

};

#endif // MAINWINDOW_H
