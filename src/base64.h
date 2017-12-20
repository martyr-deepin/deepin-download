#ifndef BASE64_H
#define BASE64_H

#include <QString>

class Base64
{
public:    
    static QString encode(const QByteArray & binaryData) throw();
    static QByteArray decode(const QString & base64String) throw(int);
};

#endif // BASE64_H
