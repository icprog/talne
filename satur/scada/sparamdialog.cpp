#include "sparamdialog.h"
#include "ui_sparamdialog.h"
#include <iodev.h>
#include <QSettings>

#include <QDebug>


SParamDialog::SParamDialog(IoDev &src,QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::SParamDialog),
    s(src)
{
    m_ui->setupUi(this);

    foreach(QString tag,s.getTags().keys())
    {
        if(s.isScaleChange(tag))
            tag_name << tag;
    }

    foreach(QString str,tag_name)
    {
        m_ui->bx_Teg->addItem(s.getText()[str]);
    }

    connect(m_ui->bn_Ok,SIGNAL(clicked()),this,SLOT(myAccept()));
    connect(m_ui->bx_Teg,SIGNAL(currentIndexChanged(int)),this,SLOT(selectTeg(int)));

    connect(m_ui->sb_Fs,SIGNAL(valueChanged(QString)),this,SLOT(slotSet(QString)));
    connect(m_ui->sb_Zs,SIGNAL(valueChanged(QString)),this,SLOT(slotSet(QString)));
    connect(m_ui->sb_f,SIGNAL(valueChanged(QString)),this,SLOT(slotSet(QString)));
    //connect(m_ui->sb_m,SIGNAL(valueChanged(QString)),this,SLOT(slotSet(QString)));

    m_ui->bx_Teg->setCurrentIndex(0);
    selectTeg(0);

    QSettings set;
    m_ui->le_ioserv->setText(set.value("/ioserv/hostname","localhost").toString());

    m_ui->le_dbserv->setText(set.value("/db/hostname","localhost").toString());
    m_ui->le_dbname->setText(set.value("/db/dbname","test").toString());
    m_ui->le_username->setText(set.value("/db/username","scada").toString());
    m_ui->le_passwd->setText(set.value("/db/passwd","").toString());


}

SParamDialog::~SParamDialog()
{
    delete m_ui;
}

void SParamDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


void SParamDialog::myAccept()
{

    s.sendValue("Save",qint16(-1));
    s.sendValue("Run",qint16(0));

    QSettings set;
    set.setValue("/ioserv/hostname",m_ui->le_ioserv->text());

    set.setValue("/db/hostname",m_ui->le_dbserv->text());
    set.setValue("/db/dbname",m_ui->le_dbname->text());
    set.setValue("/db/username",m_ui->le_username->text());
    set.setValue("/db/passwd",m_ui->le_passwd->text());


    accept();
}



void SParamDialog::slotSet(QString v )
{
    if(sender()->objectName()=="sb_Zs")
        s.setScaleZero(tag_name[m_ui->bx_Teg->currentIndex()],v.toDouble());
    else if(sender()->objectName()=="sb_Fs")
        s.setScaleFull(tag_name[m_ui->bx_Teg->currentIndex()],v.toDouble());
    else if(sender()->objectName()=="sb_f")
        s.sendValue(QString("kf_%1").arg(tag_name[m_ui->bx_Teg->currentIndex()]),qint16(v.toInt()));

}

void SParamDialog::selectTeg(int v)
{
    m_ui->sb_Zs->setValue(s.scaleZero(tag_name[v]));
    m_ui->sb_Fs->setValue(s.scaleFull(tag_name[v]));
    m_ui->sb_f->setValue(s.getValue16(QString("kf_%1").arg(tag_name[v])));

    //m_ui->sb_m->setValue((double)s.getValue16(QString("m_%1").arg(tag_name[v]))/4000.0*(s.scaleFull(tag_name[v])-s.scaleZero(tag_name[v]))+s.scaleZero(tag_name[v]));
}



