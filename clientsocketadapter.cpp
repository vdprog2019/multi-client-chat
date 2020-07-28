#include "clientsocketadapter.h"
#include <QVector>
#include <QTcpSocket>
#include <QDataStream>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateTime>

ClientSocketAdapter::ClientSocketAdapter(QObject *parent)
  : SocketAdapter(parent) {
  m_ptcpSocket->connectToHost("localhost", 1024);
}

QString ClientSocketAdapter::getDatabasePath(){
    return "/Users/kenny/Desktop/chat/database.db";
}

void ClientSocketAdapter::sendMsgToDb(QString user_id_from, QString user_id_to, QString msg){
     QSqlDatabase m_db;
     if (QSqlDatabase::contains())
     {
        m_db = QSqlDatabase::database(QLatin1String(QSqlDatabase::defaultConnection), false);
     }
     else{
        m_db = QSqlDatabase::addDatabase("QSQLITE");
        m_db.setDatabaseName(getDatabasePath());
     }
     if (!m_db.open())
     {
        qDebug() << "Error: connection with database failed";
     }
     else
     {

         QSqlQuery query;
         query.prepare("INSERT INTO messages (user_id_from, user_id_to, sms) VALUES(" + user_id_from + ", " + user_id_to + ", :sms)");
         query.bindValue(":sms", msg);
         query.exec();
         query.clear();
         m_db.close();
     }

}
QVector<QString> ClientSocketAdapter::getAllChats(){
    QSqlDatabase m_db;
    QVector<QString> v;
    if (QSqlDatabase::contains())
    {
       m_db = QSqlDatabase::database(QLatin1String(QSqlDatabase::defaultConnection), false);
    }
    else{
       m_db = QSqlDatabase::addDatabase("QSQLITE");
       m_db.setDatabaseName(getDatabasePath());
    }
    if (!m_db.open())
    {
       qDebug() << "Error: connection with database failed";
    }
    else
    {
        QSqlQuery query;
        query.prepare("SELECT user.login, user.id FROM user;");
        query.exec();

        while (query.next())
        {
            if(!query.isNull(0) && !query.isNull(1))
                v.append(query.value(0).toString() + ":" + query.value(1).toString() );
        }
        query.clear();
        m_db.close();
    }

    return  v;
}
QVector<QString> ClientSocketAdapter::getChatWithUser(QString user_id_from, QString user_id_to){
    QSqlDatabase m_db;
    QVector<QString> v;


    if (QSqlDatabase::contains())
    {
       m_db = QSqlDatabase::database(QLatin1String(QSqlDatabase::defaultConnection), false);
    }
    else{
       m_db = QSqlDatabase::addDatabase("QSQLITE");
       m_db.setDatabaseName(getDatabasePath());
    }
    if (!m_db.open())
    {
       qDebug() << "Error: connection with database failed";
    }
    else
    {
        QSqlQuery query;
        query.prepare("SELECT DISTINCT [messages].user_id_from, [messages].user_id_to, [messages].sms "
                      "FROM [messages] JOIN [user] "
                      "ON [messages].user_id_from == [user].id "
                      "WHERE [messages].user_id_from = :user_to AND [messages].user_id_to = :user_from "
                      "OR [messages].user_id_from = :user_from AND [messages].user_id_to = :user_to");
        query.bindValue(":user_from", user_id_from);
        query.bindValue(":user_to", user_id_to);
        query.exec();
        while (query.next())
        {
            if(!query.isNull(0) && !query.isNull(1)  ){
                v.append(query.value(0).toString() + ":" + query.value(1).toString() + ":" + query.value(2).toString());
            }
        }
        query.clear();
        m_db.close();
    }

    return  v;
}
QVector<QString> ClientSocketAdapter::getOldMsg(QString dateFrom){
    //тут получаем сообщения с старых переписок
    QSqlDatabase m_db;
    QVector<QString> v;
    if (QSqlDatabase::contains())
    {
       m_db = QSqlDatabase::database(QLatin1String(QSqlDatabase::defaultConnection), false);
    }
    else{
       m_db = QSqlDatabase::addDatabase("QSQLITE");
       m_db.setDatabaseName(getDatabasePath());
    }
    if (!m_db.open())
    {
       qDebug() << "Error: connection with database failed";
    }
    else
    {
        QSqlQuery query;
        query.prepare("SELECT user.login, messages.sms FROM messages INNER JOIN user ON user.id = messages.user_id WHERE msg_time < ':smsDate';");
        query.bindValue(":smsDate", dateFrom);
        query.exec();
        while (query.next())
        {
            if(!query.isNull(1) && !query.isNull(0) )
                v.append(query.value(0).toString() + ":" + query.value(1).toString());
        }
        query.clear();
        m_db.close();
    }

    return  v;
}
QString ClientSocketAdapter::LogIn(QString login, QString pass){
    QSqlDatabase m_db;
    if (QSqlDatabase::contains())
    {
       m_db = QSqlDatabase::database(QLatin1String(QSqlDatabase::defaultConnection), false);
    }
    else{
       m_db = QSqlDatabase::addDatabase("QSQLITE");
       m_db.setDatabaseName(getDatabasePath());
    }
    if (!m_db.open())
    {
       qDebug() << "Error: connection with database failed";
    }else{
      QString name = "";
      QSqlQuery query("SELECT id FROM user WHERE login = '" + login + "' AND password='" + pass + "';" );
      while (query.next())
      {
          name = query.value(0).toString();
      }
      query.clear();
      m_db.close();
      return  name;
    }
    return "";
}


bool ClientSocketAdapter::RegistUser(QString login, QString pass){
    QSqlDatabase m_db;
    if (QSqlDatabase::contains())
    {
       m_db = QSqlDatabase::database(QLatin1String(QSqlDatabase::defaultConnection), false);
    }
    else{
       m_db = QSqlDatabase::addDatabase("QSQLITE");
       m_db.setDatabaseName(getDatabasePath());
    }
    if (!m_db.open())
    {
       qDebug() << "Error: connection with database failed";
    }else{
      QString name = "";
      QSqlQuery query;
      query.prepare("INSERT INTO [user](login, password) VALUES (:l, :p);");
      query.bindValue(":l", login);
      query.bindValue(":p", pass);
      qDebug() << login;
      query.exec();
      query.clear();
      m_db.close();
      return  true;
    }
    return false;
}



