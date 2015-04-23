#include "model.h"

#include <QStandardPaths>
#include <QCoreApplication>
#include <QDir>

Model::Model()
{
  initLocalBucketsPath();
}

QString Model::localBucketsPath()
{
    return m_localBucketsPath;
}

void Model::initLocalBucketsPath()
{
    QString org = QCoreApplication::organizationName();
    QString domain = QCoreApplication::organizationDomain();
    QString app = QCoreApplication::applicationName();

    QCoreApplication::setOrganizationName("");
    QCoreApplication::setOrganizationDomain("");
    QCoreApplication::setApplicationName("myer");

    m_localBucketsPath = QStandardPaths::locate(QStandardPaths::AppDataLocation,"buckets",QStandardPaths::LocateDirectory);

    QCoreApplication::setOrganizationName(org);
    QCoreApplication::setOrganizationDomain(domain);
    QCoreApplication::setApplicationName(app);
}

QStringList Model::bucketFiles()
{
    QStringList files;

    QDir dir(localBucketsPath());
    QStringList entries = dir.entryList(QStringList("*.json"));

    foreach(QString entry, entries) {
        files.append(localBucketsPath() + "/" + entry);
    }

    return files;
}
