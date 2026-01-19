#ifndef SUBFILECONVERTER_H
#define SUBFILECONVERTER_H

#include <QObject>

class SubFileConverter : public QObject
{
    Q_OBJECT
public:
    explicit SubFileConverter(QObject *parent = nullptr);
    ~SubFileConverter() = default;

    void startConvertion(const QString &path);

signals:
    void finished();

private:
    void convertFile(const QString &fileName);
};

#endif // SUBFILECONVERTER_H
