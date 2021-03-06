*After branching off for a major version release of Flocoin Core, use this
template to create the initial release notes draft.*

*The release notes draft is a temporary file that can be added to by anyone. See
[/doc/developer-notes.md#release-notes](/doc/developer-notes.md#release-notes)
for the process.*

*Create the draft, named* "*version* Release Notes Draft"
*(e.g. "22.0 Release Notes Draft"), as a collaborative wiki in:*

https://github.com/flocoin-core/flocoin-devwiki/wiki/

*Before the final release, move the notes back to this git repository.*

*version* Release Notes Draft
===============================

Flocoin Core version *version* is now available from:

  <https://flocoincore.org/bin/flocoin-core-*version*/>

This release includes new features, various bug fixes and performance
improvements, as well as updated translations.

Please report bugs using the issue tracker at GitHub:

  <https://github.com/flocoin/flocoin/issues>

To receive security and update notifications, please subscribe to:

  <https://flocoincore.org/en/list/announcements/join/>

How to Upgrade
==============

If you are running an older version, shut it down. Wait until it has completely
shut down (which might take a few minutes in some cases), then run the
installer (on Windows) or just copy over `/Applications/Flocoin-Qt` (on Mac)
or `flocoind`/`flocoin-qt` (on Linux).

Upgrading directly from a version of Flocoin Core that has reached its EOL is
possible, but it might take some time if the data directory needs to be migrated. Old
wallet versions of Flocoin Core are generally supported.

Compatibility
==============

Flocoin Core is supported and extensively tested on operating systems
using the Linux kernel, macOS 10.14+, and Windows 7 and newer.  Flocoin
Core should also work on most other Unix-like systems but is not as
frequently tested on them.  It is not recommended to use Flocoin Core on
unsupported systems.

Notable changes
===============

P2P and network changes
-----------------------

Updated RPCs
------------

New RPCs
--------

Build System
------------

New settings
------------

Updated settings
----------------

Tools and Utilities
-------------------

- Update `-getinfo` to return data in a user-friendly format that also reduces vertical space. (#21832)

Wallet
------

GUI changes
-----------

Low-level changes
=================

RPC
---

- `getblockchaininfo` now returns a new `time` field, that provides the chain tip time. (#22407)

Tests
-----

Credits
=======

Thanks to everyone who directly contributed to this release:


As well as to everyone that helped with translations on
[Transifex](https://www.transifex.com/flocoin/flocoin/).
