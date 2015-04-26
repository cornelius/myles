#include "model.h"

#include <QStandardPaths>
#include <QCoreApplication>
#include <QDir>
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

Model::Model(QWidget *parent)
    : m_parent(parent)
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

    m_localBucketsPath = QStandardPaths::locate(QStandardPaths::AppDataLocation, "buckets", QStandardPaths::LocateDirectory);

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

Bucket::List Model::buckets()
{
    if (m_buckets.isEmpty()) {
        foreach(QString bucketFile, bucketFiles()) {
            m_buckets.append(readBucket(bucketFile));
        }
    }
    return m_buckets;
}

Bucket Model::readBucket(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(m_parent, "Error reading bucket",
          QString("Unable to open bucket at '%1'").arg(path));
        return Bucket();
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    Bucket bucket;

    bucket.setTitle(doc.object()["title"].toString());
    bucket.setSize(doc.object()["data"].toArray().size());
    bucket.setId(doc.object()["bucket_id"].toString());

    return bucket;
}
