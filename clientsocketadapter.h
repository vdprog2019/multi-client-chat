#ifndef CLIENTSOCKETADAPTER_H
# define CLIENTSOCKETADAPTER_H

# include "../common/socketadapter.h"

class ClientSocketAdapter : public SocketAdapter {
  Q_OBJECT
public:
  explicit ClientSocketAdapter(QObject *parent);
  static QString getDatabasePath();
  static void sendMsgToDb(QString user_id_from, QString user_id_to, QString msg);
  static QVector<QString> getOldMsg(QString dateFrom);
  static QVector<QString> getAllChats();
  static QVector<QString> getChatWithUser(QString user_id_from, QString user_id_to);
  static QString LogIn(QString login, QString pass);
  static bool RegistUser(QString login, QString pass);
};

#endif // CLIENTSOCKETADAPTER_H
