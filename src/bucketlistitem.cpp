#include "bucketlistitem.h"

#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <QDebug>

BucketListItem::BucketListItem()
{
    QBoxLayout *topLayout = new QVBoxLayout(this);

    m_title = new QLabel;
    topLayout->addWidget(m_title);

    m_details = new QLabel;
    topLayout->addWidget(m_details);

    QPushButton *button = new QPushButton("Show graph");
    topLayout->addWidget(button);
    connect(button, SIGNAL(clicked()), SLOT(slotShowGraph()));
}

void BucketListItem::slotShowGraph()
{
    emit showGraph(m_bucketId);
}

void BucketListItem::readBucket(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Error reading bucket",
          QString("Unable to open bucket at '%1'").arg(path));
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    QString title = doc.object()["title"].toString();
    m_title->setText(title);

    QJsonArray items = doc.object()["data"].toArray();

    m_bucketId = doc.object()["bucket_id"].toString();

    m_details->setText(QString("%1 items\nId: %2").arg(items.size()).arg(m_bucketId));
}
