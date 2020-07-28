#include "mainwidget.h"
#include "ui_form.h"
#include "clientsocketadapter.h"
#include <QDateTime>
#include <QScrollBar>
#include <QLabel>
#include <QLayoutItem>
MainWidget::MainWidget(QWidget *parent, QString user_id, QString login) : QWidget(parent), login(login), user_id_from(user_id), m_pForm(new Ui::Form()),  m_pSock(new ClientSocketAdapter(this)) {

  m_pForm->setupUi(this);
  connect(m_pSock, SIGNAL(message(QString)), SLOT(on_message(QString)));
  connect(m_pForm->send, SIGNAL(clicked()), SLOT(on_send()));
  connect(m_pForm->message, SIGNAL(returnPressed()), SLOT(EnterPressed()));
  for(auto a : ClientSocketAdapter::getOldMsg(QDate::currentDate().toString(Qt::ISODate)) ){
         on_message(a);
    }
  for(auto a : ClientSocketAdapter::getAllChats() ){
      if(a.split(":")[0] != login){
          QLabel *l = new QLabel(a.split(":")[0]);
          l->setObjectName(a.split(":")[1]);
          l->installEventFilter(this);
          m_pForm->verticalLayout->addWidget(l);
      }
  }

}

void MainWidget::on_message(QString text) {
  m_pForm->messages->setHtml(m_pForm->messages->toHtml() + text + "<br>");
  m_pForm->messages->moveCursor(QTextCursor::End);
}

void MainWidget::on_send() {
    m_pSock->sendString(MainWidget::login + ": " + m_pForm->message->text());
    ClientSocketAdapter::sendMsgToDb(user_id_from, user_id_to, m_pForm->message->text() );
    m_pForm->message->clear();
}

void MainWidget::EnterPressed(){
   on_send();
}


bool MainWidget::eventFilter(QObject *watched, QEvent *event){
    if(event->type() == QEvent::MouseButtonPress){
        m_pForm->messages->clear();
        user_id_to = static_cast<QLabel*>(watched)->objectName();
        for(auto a : ClientSocketAdapter::getChatWithUser(user_id_from, user_id_to))
        {
               QList<QString> ms = a.split(":");
               if(ms[0] == user_id_to)
                   ms[0] = static_cast<QLabel*>(watched)->text();
               else
                   ms[0] = this->login;
               a = ms.join(":");
               on_message(ms[0] + ":" + ms[2]);
        }
    }
}


