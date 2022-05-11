#pragma once
#include "tasks/Task.h"
#include <QNetworkReply>
#include <QString>
#include <QBuffer>
#include <memory>
#include <array>

class PasteUpload : public Task
{
    Q_OBJECT
public:
    enum PasteType : unsigned int {
        // 0x0.st
        NullPointer,
        // hastebin.com
        Hastebin,
        // paste.gg
        PasteGG,
        // mclo.gs
        Mclogs,
        // Helpful to get the range of valid values on the enum for input sanitisation:
        First = NullPointer,
        Last = Mclogs
    };

    struct PasteTypeInfo {
        const QString name;
        const QString defaultBase;
        const QString endpointPath;
    };

    static std::array<PasteTypeInfo, 4> PasteTypes;

    PasteUpload(QWidget *window, QString text, QString url, PasteType pasteType);
    virtual ~PasteUpload();

    QString pasteLink()
    {
        return m_pasteLink;
    }
protected:
    virtual void executeTask();

private:
    QWidget *m_window;
    QString m_pasteLink;
    QString m_baseUrl;
    QString m_uploadUrl;
    PasteType m_pasteType;
    QByteArray m_text;
    std::shared_ptr<QNetworkReply> m_reply;
public
slots:
    void downloadError(QNetworkReply::NetworkError);
    void downloadFinished();
};
