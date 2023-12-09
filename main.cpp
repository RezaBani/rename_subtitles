#include <QCoreApplication>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include <QList>
#include <QStringList>
#include <QTextStream>
#include <iostream>
#include <QDebug>

const QStringList movieExtensions {"mkv", "mp4", "avi", "m4v"};
const QStringList subtitleExtensions {"srt", "vtt", "ass", "idx"};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QStringList movieNameList {};
    QStringList subtitleNameList {};
    QStringList subtitleExtList {};
    QString path {};
    qInfo() << "Please enter the movie/tv-series folder:";
    QTextStream qtin(stdin);
    path = qtin.readLine();
    path.replace('\\','/');
    QDir movieDir(path);

    qInfo() << "Please enter the subtitles folder:";
    path = qtin.readLine();
    path.replace('\\','/');
    QDir subtitleDir(path);

    foreach (QFileInfo fi, movieDir.entryInfoList(QDir::Files)) {
        foreach(QString ext,movieExtensions){
            if (fi.suffix() == ext){
                movieNameList.append(fi.completeBaseName());
                break;
            }
        }
    }

    foreach (QFileInfo fi, subtitleDir.entryInfoList(QDir::Files)) {
        foreach(QString ext,subtitleExtensions){
            if (fi.suffix() == ext){
                subtitleNameList.append(fi.fileName());
                subtitleExtList.append(fi.suffix());
                break;
            }
        }
    }
    QDir::setCurrent(path);
    size_t i = 0;
    qInfo() << "Changes Preview:";
    foreach (QString name, subtitleNameList) {
        qInfo() << name << " --> " << movieNameList.at(i) + "." + subtitleExtList.at(i);
        i++;
    }
    qInfo() << "Are you agree?(y/n)";
    QString choice;
    choice = qtin.readLine().toLower();
    i = 0;
    if(choice == "y" || choice == "yes"){
        foreach (QString name, subtitleNameList) {
            QFile::rename(name, movieNameList.at(i) + "." + subtitleExtList.at(i));
            i++;
        }
        qInfo() << "Subtitle Names changed";
    } else {
        qInfo() << "Nothing changed";
    }

    return a.exec();
}
