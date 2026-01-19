#include "subfileconverter.h"
#include <QDirListing>
#include <QFile>
#include <QStringConverter>
#include <QTextCodec>
#include <QDebug>

SubFileConverter::SubFileConverter(QObject *parent)
    : QObject{parent}
{

}

void SubFileConverter::startConvertion(const QString &path)
{
    qDebug() << "SubFileConverter::startConvertion start" << path;
    using ItFlag = QDirListing::IteratorFlag;        
    for (const auto &dirEntry : QDirListing(path, ItFlag::FilesOnly)) {
        const QString fileName = dirEntry.fileName();
        if (!fileName.endsWith(".srt"))
            continue;

        convertFile(fileName);
    }

    emit finished();
}

void SubFileConverter::convertFile(const QString &fileName)
{
    QFile fileIn(fileName);

    if (!fileIn.open(QIODevice::ReadOnly| QIODevice::Text)) {
        qWarning() << "Could not open file:" << fileIn.errorString();
        return;
    }

    qDebug() << "SubFileConverter::convertFile" << fileName;

    QTextStream in(&fileIn);
    in.setEncoding(QStringConverter::Utf8);

    QString readText = in.readAll();
    if (!readText.contains("ž")) {
        // qDebug() << readText;
        fileIn.seek(0); // Go back to the beginning of the file
        // in.setEncoding(QStringEncoder::Latin1);
        // auto fromUtf16 = QStringEncoder(QStringEncoder::Utf8);
        // readText = fromUtf16(in.readAll());

        QByteArray bfileIna = fileIn.readAll();

        QTextCodec* codec = QTextCodec::codecForName("windows-1252");
        readText = codec->toUnicode(bfileIna);
    }

    fileIn.close();

    QString fileNameOut(fileName);
    // fileNameOut.append(".tmp");

    // Create a new file
    QFile fileOut(fileNameOut);
    if (!fileOut.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Could not create file:" << fileNameOut << fileOut.errorString();
        return;
    }

    QTextStream out(&fileOut);
    out.setEncoding(QStringConverter::Utf8);
    out << readText.replace("è", "č").replace("È", "Č");

    // optional, as QFile destructor will already do it:
    fileOut.close();
}
