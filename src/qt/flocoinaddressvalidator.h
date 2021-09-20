// Copyright (c) 2011-2020 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef FLOCOIN_QT_FLOCOINADDRESSVALIDATOR_H
#define FLOCOIN_QT_FLOCOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class FlocoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit FlocoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

/** Flocoin address widget validator, checks for a valid flocoin address.
 */
class FlocoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit FlocoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

#endif // FLOCOIN_QT_FLOCOINADDRESSVALIDATOR_H
