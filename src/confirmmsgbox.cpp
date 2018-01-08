#include "confirmmsgbox.h"

#include <QLabel>
#include <QFont>
#include <QFontMetrics>

ConfirmMsgBox::ConfirmMsgBox( QWidget *parent ,QString title , QString text )
{

    QString titleStr;
    QString tip;

    titleStr =  title;

    tip = tr( text.toStdString().data() );

    //setIcon( QIcon(":Resources/images/logo_24.svg") );

    QIcon appico = QIcon::fromTheme("deepin-download");

    if( ! appico.isNull() ){

        setIcon( appico );
    }else{

        setIcon( QIcon(":Resources/images/logo_24.svg") );
    }

    setTitle( titleStr );

    QLabel* label = new QLabel(this);

    QFont font;
    font.setPixelSize(12);
    label->setFont(font);

    QFontMetrics fm(font);
    QString elidedTipStr = fm.elidedText(tip,Qt::ElideRight,240);
    //elidedTipStr += "?";
    label->setText(elidedTipStr);

    addContent(label);
    addButton(tr("Cancel"), false);
    addButton(tr("Empty"), true, DDialog::ButtonWarning);

}
