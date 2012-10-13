/*
 * by lovewilliam <lovewilliam@gmail.com>
 */

#include <QObject>
#include <QString>

class DataObject : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
	Q_PROPERTY(bool ticked READ isTicked WRITE setTicked NOTIFY tickChanged)

	public:
		DataObject(QObject* parent = 0);
		DataObject(QString _name ,bool _isTicked,QObject* parent = 0);

		void setName(QString);
		void setTicked(bool);
		QString getName();
		bool isTicked();

	signals:
		void nameChanged();
		void tickChanged(QString,bool);

	private:
		QString m_name;
		bool m_ticked;
};

