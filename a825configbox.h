#ifndef A825CONFIGBOX_H
#define A825CONFIGBOX_H

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class A825ConfigBox;
}

class A825ConfigBox : public QWidget
{
    Q_OBJECT

public:
    explicit A825ConfigBox(QWidget *parent = 0);
    ~A825ConfigBox();

private slots:
    void profileButtonClicked();
    void initializeButtonClicked();

private:
    Ui::A825ConfigBox *ui;

signals:
    void newProfileChoice(QString fileName);
};

#endif // A825CONFIGBOX_H
