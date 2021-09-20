Flocoin Core
=============

Setup
---------------------
Flocoin Core is the original Flocoin client and it builds the backbone of the network. It downloads and, by default, stores the entire history of Flocoin transactions, which requires a few hundred gigabytes of disk space. Depending on the speed of your computer and network connection, the synchronization process can take anywhere from a few hours to a day or more.

To download Flocoin Core, visit [flocoincore.org](https://flocoincore.org/en/download/).

Running
---------------------
The following are some helpful notes on how to run Flocoin Core on your native platform.

### Unix

Unpack the files into a directory and run:

- `bin/flocoin-qt` (GUI) or
- `bin/flocoind` (headless)

### Windows

Unpack the files into a directory, and then run flocoin-qt.exe.

### macOS

Drag Flocoin Core to your applications folder, and then run Flocoin Core.

### Need Help?

* See the documentation at the [Flocoin Wiki](https://en.flocoin.it/wiki/Main_Page)
for help and more information.
* Ask for help on [Flocoin StackExchange](https://flocoin.stackexchange.com).
* Ask for help on #flocoin on Libera Chat. If you don't have an IRC client, you can use [web.libera.chat](https://web.libera.chat/#flocoin).
* Ask for help on the [FlocoinTalk](https://flocointalk.org/) forums, in the [Technical Support board](https://flocointalk.org/index.php?board=4.0).

Building
---------------------
The following are developer notes on how to build Flocoin Core on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [Dependencies](dependencies.md)
- [macOS Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
- [Windows Build Notes](build-windows.md)
- [FreeBSD Build Notes](build-freebsd.md)
- [OpenBSD Build Notes](build-openbsd.md)
- [NetBSD Build Notes](build-netbsd.md)
- [Android Build Notes](build-android.md)
- [Gitian Building Guide (External Link)](https://github.com/flocoin-core/docs/blob/master/gitian-building.md)

Development
---------------------
The Flocoin repo's [root README](/README.md) contains relevant information on the development process and automated testing.

- [Developer Notes](developer-notes.md)
- [Productivity Notes](productivity.md)
- [Release Notes](release-notes.md)
- [Release Process](release-process.md)
- [Source Code Documentation (External Link)](https://doxygen.flocoincore.org/)
- [Translation Process](translation_process.md)
- [Translation Strings Policy](translation_strings_policy.md)
- [JSON-RPC Interface](JSON-RPC-interface.md)
- [Unauthenticated REST Interface](REST-interface.md)
- [Shared Libraries](shared-libraries.md)
- [BIPS](bips.md)
- [Dnsseed Policy](dnsseed-policy.md)
- [Benchmarking](benchmarking.md)

### Resources
* Discuss on the [FlocoinTalk](https://flocointalk.org/) forums, in the [Development & Technical Discussion board](https://flocointalk.org/index.php?board=6.0).
* Discuss project-specific development on #flocoin-core-dev on Libera Chat. If you don't have an IRC client, you can use [web.libera.chat](https://web.libera.chat/#flocoin-core-dev).

### Miscellaneous
- [Assets Attribution](assets-attribution.md)
- [flocoin.conf Configuration File](flocoin-conf.md)
- [Files](files.md)
- [Fuzz-testing](fuzzing.md)
- [I2P Support](i2p.md)
- [Init Scripts (systemd/upstart/openrc)](init.md)
- [PSBT support](psbt.md)
- [Reduce Memory](reduce-memory.md)
- [Reduce Traffic](reduce-traffic.md)
- [Tor Support](tor.md)
- [ZMQ](zmq.md)

License
---------------------
Distributed under the [MIT software license](/COPYING).
