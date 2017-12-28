#include "gcmessagebox.h"
#include <QLabel>
#include <QFont>
#include <QFontMetrics>
#include <QIcon>
#include <Qt>

GCMessageBox::GCMessageBox(QWidget *parent ,QString title ,QString text ) :Dtk::Widget::DDialog(parent)
{

       QString titleStr;
       QString tip;

       titleStr =  title;

       tip = tr( text.toStdString().data() );

       setIcon( QIcon(":Resources/images/logo_24.svg") );
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
       addButton(tr("Confirm"), false);
       //addButton(tr("Delete"), true, DDialog::ButtonWarning);
}
