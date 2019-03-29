#ifndef QTHREADWITHMSGBOX_H
#define QTHREADWITHMSGBOX_H

#include <QThread>
#include <QSemaphore>
#include <QObject>
#include <QMessageBox>

class QThreadWithMsgBox : public QThread
{
   Q_OBJECT
protected:
   int m_btnres;
   int information(QWidget * parent, const QString &title, const QString &text, QMessageBox::StandardButtons buttons = QMessageBox::Ok, QMessageBox::StandardButtons defaultButton = QMessageBox::NoButton)
   {
       emit information_sig(parent, title, text, buttons, defaultButton);
       return m_btnres;
   }

   void run(void) Q_DECL_OVERRIDE {
      information(0,tr("test dialog"),tr("a information from thread."));
   }
public:
   QThreadWithMsgBox(QObject * parent = 0)
      :QThread(parent), m_btnres(QMessageBox::NoButton) {
      qRegisterMetaType<QMessageBox::StandardButtons>("QMessageBox::StandardButtons");
      connect(this, SIGNAL(information_sig(QWidget *, const QString, const QString, QMessageBox::StandardButtons, QMessageBox::StandardButtons)), SLOT(on_information(QWidget *, const QString , const QString, QMessageBox::StandardButtons , QMessageBox::StandardButtons )), Qt::BlockingQueuedConnection);
   }
signals:
    void information_sig(QWidget * parent, const QString &title, const QString &text, QMessageBox::StandardButtons buttons, QMessageBox::StandardButtons defaultButton);

private slots:
    void on_information(QWidget * parent, const QString &title, const QString &text, QMessageBox::StandardButtons buttons, QMessageBox::StandardButtons defaultButton) {
        m_btnres = QMessageBox::information(parent, title, text, buttons, defaultButton);
    }
};

#endif // QTHREADWITHMSGBOX_H
