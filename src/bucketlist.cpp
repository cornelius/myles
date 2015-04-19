#include "bucketlist.h"

#include "bucketlistitem.h"

#include <QBoxLayout>
#include <QFrame>
#include <QLabel>
#include <QDebug>
#include <QStandardPaths>
#include <QCoreApplication>
#include <QDir>

BucketList::BucketList(QWidget *parent) : QWidget(parent)
{
    m_topLayout = new QVBoxLayout(this);

    QLabel *label = new QLabel("Buckets");
    m_topLayout->addWidget(label);

    readBuckets();

    QFrame *dummyBucket = new QFrame();
    dummyBucket->setFrameStyle(QFrame::Box | QFrame::Raised);

    m_topLayout->addWidget(dummyBucket, 1);
}

void BucketList::readBuckets()
{
    QDir dir(localBucketsPath());
    QStringList entries = dir.entryList(QStringList("*.json"));

    foreach(QString entry, entries) {
        BucketListItem *item = new BucketListItem;
        m_topLayout->addWidget(item);

        item->readBucket(localBucketsPath() + "/" + entry);
    }
}

QString BucketList::localBucketsPath()
{
    QString org = QCoreApplication::organizationName();
    QString domain = QCoreApplication::organizationDomain();
    QString app = QCoreApplication::applicationName();

    QCoreApplication::setOrganizationName("");
    QCoreApplication::setOrganizationDomain("");
    QCoreApplication::setApplicationName("myer");

    QString path = QStandardPaths::locate(QStandardPaths::AppDataLocation,"buckets",QStandardPaths::LocateDirectory);

    QCoreApplication::setOrganizationName(org);
    QCoreApplication::setOrganizationDomain(domain);
    QCoreApplication::setApplicationName(app);

    return path;
}
