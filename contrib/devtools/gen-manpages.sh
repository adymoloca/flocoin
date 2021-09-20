#!/usr/bin/env bash
# Copyright (c) 2016-2020 The Bitcoin Core developers
# Copyright (c) Flo Developers 2013-2021
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

export LC_ALL=C
TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
BUILDDIR=${BUILDDIR:-$TOPDIR}

BINDIR=${BINDIR:-$BUILDDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

FLOCOIND=${FLOCOIND:-$BINDIR/flocoind}
FLOCOINCLI=${FLOCOINCLI:-$BINDIR/flocoin-cli}
FLOCOINTX=${FLOCOINTX:-$BINDIR/flocoin-tx}
WALLET_TOOL=${WALLET_TOOL:-$BINDIR/flocoin-wallet}
FLOCOINUTIL=${FLOCOINQT:-$BINDIR/flocoin-util}
FLOCOINQT=${FLOCOINQT:-$BINDIR/qt/flocoin-qt}

[ ! -x $FLOCOIND ] && echo "$FLOCOIND not found or not executable." && exit 1

# Don't allow man pages to be generated for binaries built from a dirty tree
DIRTY=""
for cmd in $FLOCOIND $FLOCOINCLI $FLOCOINTX $WALLET_TOOL $FLOCOINUTIL $FLOCOINQT; do
  VERSION_OUTPUT=$($cmd --version)
  if [[ $VERSION_OUTPUT == *"dirty"* ]]; then
    DIRTY="${DIRTY}${cmd}\n"
  fi
done
if [ -n "$DIRTY" ]
then
  echo -e "WARNING: the following binaries were built from a dirty tree:\n"
  echo -e $DIRTY
  echo "man pages generated from dirty binaries should NOT be committed."
  echo "To properly generate man pages, please commit your changes to the above binaries, rebuild them, then run this script again."
fi

# The autodetected version git tag can screw up manpage output a little bit
read -r -a FLOVER <<< "$($FLOCOINCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }')"

# Create a footer file with copyright content.
# This gets autodetected fine for flocoind if --version-string is not set,
# but has different outcomes for flocoin-qt and flocoin-cli.
echo "[COPYRIGHT]" > footer.h2m
$FLOCOIND --version | sed -n '1!p' >> footer.h2m

for cmd in $FLOCOIND $FLOCOINCLI $FLOCOINTX $WALLET_TOOL $FLOCOINUTIL $FLOCOINQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${FLOVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${FLOVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
