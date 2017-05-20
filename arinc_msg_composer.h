#ifndef ARINC_MSG_COMPOSER_H
#define ARINC_MSG_COMPOSER_H

#include <QWidget>
#include <socket.h>
#include <profile.h>


namespace Ui {
class ARINC_MSG_composer;
}

class ARINC_MSG_composer : public QWidget
{
    Q_OBJECT

public:
    explicit ARINC_MSG_composer(QWidget *parent = 0);
    ~ARINC_MSG_composer();


private slots:
    void sendClickedHandle();
    void fillParameters(Profile* profile);


private:
    Ui::ARINC_MSG_composer *ui;

    void setArincMsg(A825_MSG* msg);
};

#endif // ARINC_MSG_COMPOSER_H
