#ifndef SOAPOPERACARD_H
#define SOAPOPERACARD_H

#include <QFrame>

namespace Ui {
class SoapOperaCard;
}

class SoapOperaCard : public QFrame
{
    Q_OBJECT

public:
    explicit SoapOperaCard(QWidget *parent = nullptr);
    ~SoapOperaCard();

private:
    Ui::SoapOperaCard *ui;
};

#endif // SOAPOPERACARD_H
