# Copyright (c) 2013-2016 The Bitcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

# Pattern rule to print variables, e.g. make print-top_srcdir
print-%: FORCE
	@echo '$*'='$($*)'

DIST_SUBDIRS = secp256k1 univalue

AM_LDFLAGS = $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS) $(GPROF_LDFLAGS) $(SANITIZER_LDFLAGS)
AM_CXXFLAGS = $(DEBUG_CXXFLAGS) $(HARDENED_CXXFLAGS) $(WARN_CXXFLAGS) $(NOWARN_CXXFLAGS) $(ERROR_CXXFLAGS) $(GPROF_CXXFLAGS) $(SANITIZER_CXXFLAGS)
AM_CPPFLAGS = $(DEBUG_CPPFLAGS) $(HARDENED_CPPFLAGS)
AM_LIBTOOLFLAGS = --preserve-dup-deps
PTHREAD_FLAGS = $(PTHREAD_CFLAGS) $(PTHREAD_LIBS)
EXTRA_LIBRARIES =

if EMBEDDED_UNIVALUE
LIBUNIVALUE = univalue/libunivalue.la

$(LIBUNIVALUE): $(wildcard univalue/lib/*) $(wildcard univalue/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)
else
LIBUNIVALUE = $(UNIVALUE_LIBS)
endif

FLOCOIN_INCLUDES=-I$(builddir) -I$(srcdir)/secp256k1/include $(BDB_CPPFLAGS) $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS)

FLOCOIN_INCLUDES += $(UNIVALUE_CFLAGS)

LIBFLOCOIN_SERVER=libflocoin_server.a
LIBFLOCOIN_COMMON=libflocoin_common.a
LIBFLOCOIN_CONSENSUS=libflocoin_consensus.a
LIBFLOCOIN_CLI=libflocoin_cli.a
LIBFLOCOIN_UTIL=libflocoin_util.a
LIBFLOCOIN_CRYPTO_BASE=crypto/libflocoin_crypto_base.a
LIBFLOCOINQT=qt/libflocoinqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la

if ENABLE_ZMQ
LIBFLOCOIN_ZMQ=libflocoin_zmq.a
endif
if BUILD_FLOCOIN_LIBS
LIBFLOCOINCONSENSUS=libflocoinconsensus.la
endif
if ENABLE_WALLET
LIBFLOCOIN_WALLET=libflocoin_wallet.a
LIBFLOCOIN_WALLET_TOOL=libflocoin_wallet_tool.a
endif

LIBFLOCOIN_CRYPTO= $(LIBFLOCOIN_CRYPTO_BASE)
if ENABLE_SSE41
LIBFLOCOIN_CRYPTO_SSE41 = crypto/libflocoin_crypto_sse41.a
LIBFLOCOIN_CRYPTO += $(LIBFLOCOIN_CRYPTO_SSE41)
endif
if ENABLE_AVX2
LIBFLOCOIN_CRYPTO_AVX2 = crypto/libflocoin_crypto_avx2.a
LIBFLOCOIN_CRYPTO += $(LIBFLOCOIN_CRYPTO_AVX2)
endif
if ENABLE_SHANI
LIBFLOCOIN_CRYPTO_SHANI = crypto/libflocoin_crypto_shani.a
LIBFLOCOIN_CRYPTO += $(LIBFLOCOIN_CRYPTO_SHANI)
endif

$(LIBSECP256K1): $(wildcard secp256k1/src/*.h) $(wildcard secp256k1/src/*.c) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES += \
  $(LIBFLOCOIN_CRYPTO) \
  $(LIBFLOCOIN_UTIL) \
  $(LIBFLOCOIN_COMMON) \
  $(LIBFLOCOIN_CONSENSUS) \
  $(LIBFLOCOIN_SERVER) \
  $(LIBFLOCOIN_CLI) \
  $(LIBFLOCOIN_IPC) \
  $(LIBFLOCOIN_WALLET) \
  $(LIBFLOCOIN_WALLET_TOOL) \
  $(LIBFLOCOIN_ZMQ)

lib_LTLIBRARIES = $(LIBFLOCOINCONSENSUS)

bin_PROGRAMS =
noinst_PROGRAMS =
TESTS =
BENCHMARKS =

if BUILD_FLOCOIND
  bin_PROGRAMS += flocoind
endif

if BUILD_FLOCOIN_NODE
  bin_PROGRAMS += flocoin-node
endif

if BUILD_FLOCOIN_CLI
  bin_PROGRAMS += flocoin-cli
endif

if BUILD_FLOCOIN_TX
  bin_PROGRAMS += flocoin-tx
endif

if ENABLE_WALLET
if BUILD_FLOCOIN_WALLET
  bin_PROGRAMS += flocoin-wallet
endif
endif

if BUILD_FLOCOIN_UTIL
  bin_PROGRAMS += flocoin-util
endif

.PHONY: FORCE check-symbols check-security
# flocoin core #
FLOCOIN_CORE_H = \
  addrdb.h \
  addrman.h \
  attributes.h \
  banman.h \
  base58.h \
  bech32.h \
  blockencodings.h \
  blockfilter.h \
  bloom.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkqueue.h \
  clientversion.h \
  coins.h \
  compat.h \
  compat/assumptions.h \
  compat/byteswap.h \
  compat/cpuid.h \
  compat/endian.h \
  compat/sanity.h \
  compressor.h \
  consensus/consensus.h \
  consensus/tx_check.h \
  consensus/tx_verify.h \
  core_io.h \
  core_memusage.h \
  cuckoocache.h \
  dbwrapper.h \
  deploymentinfo.h \
  deploymentstatus.h \
  external_signer.h \
  flatfile.h \
  fs.h \
  httprpc.h \
  httpserver.h \
  i2p.h \
  index/base.h \
  index/blockfilterindex.h \
  index/coinstatsindex.h \
  index/disktxpos.h \
  index/txindex.h \
  indirectmap.h \
  init.h \
  init/common.h \
  interfaces/chain.h \
  interfaces/echo.h \
  interfaces/handler.h \
  interfaces/init.h \
  interfaces/ipc.h \
  interfaces/node.h \
  interfaces/wallet.h \
  key.h \
  key_io.h \
  logging.h \
  logging/timer.h \
  mapport.h \
  memusage.h \
  merkleblock.h \
  miner.h \
  net.h \
  net_permissions.h \
  net_processing.h \
  net_types.h \
  netaddress.h \
  netbase.h \
  netmessagemaker.h \
  node/blockstorage.h \
  node/coin.h \
  node/coinstats.h \
  node/context.h \
  node/psbt.h \
  node/transaction.h \
  node/ui_interface.h \
  node/utxo_snapshot.h \
  noui.h \
  outputtype.h \
  policy/feerate.h \
  policy/fees.h \
  policy/packages.h \
  policy/policy.h \
  policy/rbf.h \
  policy/settings.h \
  pow.h \
  protocol.h \
  psbt.h \
  random.h \
  randomenv.h \
  reverse_iterator.h \
  rpc/blockchain.h \
  rpc/client.h \
  rpc/mining.h \
  rpc/net.h \
  rpc/protocol.h \
  rpc/rawtransaction_util.h \
  rpc/register.h \
  rpc/request.h \
  rpc/server.h \
  rpc/util.h \
  scheduler.h \
  script/descriptor.h \
  script/keyorigin.h \
  script/sigcache.h \
  script/sign.h \
  script/signingprovider.h \
  script/standard.h \
  shutdown.h \
  signet.h \
  streams.h \
  support/allocators/secure.h \
  support/allocators/zeroafterfree.h \
  support/cleanse.h \
  support/events.h \
  support/lockedpool.h \
  sync.h \
  threadinterrupt.h \
  threadsafety.h \
  timedata.h \
  torcontrol.h \
  txdb.h \
  txmempool.h \
  txorphanage.h \
  txrequest.h \
  undo.h \
  util/asmap.h \
  util/bip32.h \
  util/bytevectorhash.h \
  util/check.h \
  util/epochguard.h \
  util/error.h \
  util/fees.h \
  util/getuniquepath.h \
  util/golombrice.h \
  util/hash_type.h \
  util/hasher.h \
  util/macros.h \
  util/message.h \
  util/moneystr.h \
  util/rbf.h \
  util/readwritefile.h \
  util/serfloat.h \
  util/settings.h \
  util/sock.h \
  util/spanparsing.h \
  util/string.h \
  util/system.h \
  util/thread.h \
  util/threadnames.h \
  util/time.h \
  util/tokenpipe.h \
  util/trace.h \
  util/translation.h \
  util/ui_change_type.h \
  util/url.h \
  util/vector.h \
  validation.h \
  validationinterface.h \
  versionbits.h \
  wallet/bdb.h \
  wallet/coincontrol.h \
  wallet/coinselection.h \
  wallet/context.h \
  wallet/crypter.h \
  wallet/db.h \
  wallet/dump.h \
  wallet/external_signer_scriptpubkeyman.h \
  wallet/feebumper.h \
  wallet/fees.h \
  wallet/ismine.h \
  wallet/load.h \
  wallet/receive.h \
  wallet/rpcwallet.h \
  wallet/salvage.h \
  wallet/scriptpubkeyman.h \
  wallet/spend.h \
  wallet/sqlite.h \
  wallet/transaction.h \
  wallet/wallet.h \
  wallet/walletdb.h \
  wallet/wallettool.h \
  wallet/walletutil.h \
  walletinitinterface.h \
  warnings.h \
  zmq/zmqabstractnotifier.h \
  zmq/zmqnotificationinterface.h \
  zmq/zmqpublishnotifier.h \
  zmq/zmqrpc.h \
  zmq/zmqutil.h


obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh "$(abs_top_builddir)/src/obj/build.h" \
	  "$(abs_top_srcdir)"
libflocoin_util_a-clientversion.$(OBJEXT): obj/build.h

ipc/capnp/libflocoin_ipc_a-ipc.$(OBJEXT): $(libflocoin_ipc_mpgen_input:=.h)

# server: shared between flocoind and flocoin-qt
# Contains code accessing mempool and chain state that is meant to be separated
# from wallet and gui code (see node/README.md). Shared code should go in
# libflocoin_common or libflocoin_util libraries, instead.
libflocoin_server_a_CPPFLAGS = $(AM_CPPFLAGS) $(FLOCOIN_INCLUDES) $(MINIUPNPC_CPPFLAGS) $(NATPMP_CPPFLAGS) $(EVENT_CFLAGS) $(EVENT_PTHREADS_CFLAGS)
libflocoin_server_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libflocoin_server_a_SOURCES = \
  addrdb.cpp \
  addrman.cpp \
  banman.cpp \
  blockencodings.cpp \
  blockfilter.cpp \
  chain.cpp \
  consensus/tx_verify.cpp \
  dbwrapper.cpp \
  deploymentstatus.cpp \
  flatfile.cpp \
  httprpc.cpp \
  httpserver.cpp \
  i2p.cpp \
  index/base.cpp \
  index/blockfilterindex.cpp \
  index/coinstatsindex.cpp \
  index/txindex.cpp \
  init.cpp \
  mapport.cpp \
  miner.cpp \
  net.cpp \
  net_processing.cpp \
  node/blockstorage.cpp \
  node/coin.cpp \
  node/coinstats.cpp \
  node/context.cpp \
  node/interfaces.cpp \
  node/psbt.cpp \
  node/transaction.cpp \
  node/ui_interface.cpp \
  noui.cpp \
  policy/fees.cpp \
  policy/packages.cpp \
  policy/rbf.cpp \
  policy/settings.cpp \
  pow.cpp \
  rest.cpp \
  rpc/blockchain.cpp \
  rpc/mining.cpp \
  rpc/misc.cpp \
  rpc/net.cpp \
  rpc/rawtransaction.cpp \
  rpc/server.cpp \
  script/sigcache.cpp \
  shutdown.cpp \
  signet.cpp \
  timedata.cpp \
  torcontrol.cpp \
  txdb.cpp \
  txmempool.cpp \
  txorphanage.cpp \
  txrequest.cpp \
  validation.cpp \
  validationinterface.cpp \
  versionbits.cpp \
  $(FLOCOIN_CORE_H)

if ENABLE_WALLET
libflocoin_server_a_SOURCES += wallet/init.cpp
endif
if !ENABLE_WALLET
libflocoin_server_a_SOURCES += dummywallet.cpp
endif

if ENABLE_ZMQ
libflocoin_zmq_a_CPPFLAGS = $(AM_CPPFLAGS) $(FLOCOIN_INCLUDES) $(ZMQ_CFLAGS)
libflocoin_zmq_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libflocoin_zmq_a_SOURCES = \
  zmq/zmqabstractnotifier.cpp \
  zmq/zmqnotificationinterface.cpp \
  zmq/zmqpublishnotifier.cpp \
  zmq/zmqrpc.cpp \
  zmq/zmqutil.cpp
endif


# wallet: shared between flocoind and flocoin-qt, but only linked
# when wallet enabled
libflocoin_wallet_a_CPPFLAGS = $(AM_CPPFLAGS) $(FLOCOIN_INCLUDES) $(SQLITE_CFLAGS)
libflocoin_wallet_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libflocoin_wallet_a_SOURCES = \
  wallet/coincontrol.cpp \
  wallet/context.cpp \
  wallet/crypter.cpp \
  wallet/db.cpp \
  wallet/dump.cpp \
  wallet/external_signer_scriptpubkeyman.cpp \
  wallet/feebumper.cpp \
  wallet/fees.cpp \
  wallet/interfaces.cpp \
  wallet/load.cpp \
  wallet/receive.cpp \
  wallet/rpcdump.cpp \
  wallet/rpcwallet.cpp \
  wallet/scriptpubkeyman.cpp \
  wallet/spend.cpp \
  wallet/transaction.cpp \
  wallet/wallet.cpp \
  wallet/walletdb.cpp \
  wallet/walletutil.cpp \
  wallet/coinselection.cpp \
  $(FLOCOIN_CORE_H)

if USE_SQLITE
libflocoin_wallet_a_SOURCES += wallet/sqlite.cpp
endif
if USE_BDB
libflocoin_wallet_a_SOURCES += wallet/bdb.cpp wallet/salvage.cpp
endif

libflocoin_wallet_tool_a_CPPFLAGS = $(AM_CPPFLAGS) $(FLOCOIN_INCLUDES)
libflocoin_wallet_tool_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libflocoin_wallet_tool_a_SOURCES = \
  wallet/wallettool.cpp \
  $(FLOCOIN_CORE_H)

# crypto primitives library
crypto_libflocoin_crypto_base_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libflocoin_crypto_base_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libflocoin_crypto_base_a_SOURCES = \
  crypto/aes.cpp \
  crypto/aes.h \
  crypto/chacha_poly_aead.h \
  crypto/chacha_poly_aead.cpp \
  crypto/chacha20.h \
  crypto/chacha20.cpp \
  crypto/common.h \
  crypto/hkdf_sha256_32.cpp \
  crypto/hkdf_sha256_32.h \
  crypto/hmac_sha256.cpp \
  crypto/hmac_sha256.h \
  crypto/hmac_sha512.cpp \
  crypto/hmac_sha512.h \
  crypto/poly1305.h \
  crypto/poly1305.cpp \
  crypto/muhash.h \
  crypto/muhash.cpp \
  crypto/ripemd160.cpp \
  crypto/ripemd160.h \
  crypto/sha1.cpp \
  crypto/sha1.h \
  crypto/sha256.cpp \
  crypto/sha256.h \
  crypto/sha3.cpp \
  crypto/sha3.h \
  crypto/sha512.cpp \
  crypto/sha512.h \
  crypto/scrypt.cpp \
  crypto/scrypt-sse2.cpp \
  crypto/scrypt.h \
  crypto/siphash.cpp \
  crypto/siphash.h

if USE_ASM
crypto_libflocoin_crypto_base_a_SOURCES += crypto/sha256_sse4.cpp
endif

crypto_libflocoin_crypto_sse41_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libflocoin_crypto_sse41_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libflocoin_crypto_sse41_a_CXXFLAGS += $(SSE41_CXXFLAGS)
crypto_libflocoin_crypto_sse41_a_CPPFLAGS += -DENABLE_SSE41
crypto_libflocoin_crypto_sse41_a_SOURCES = crypto/sha256_sse41.cpp

crypto_libflocoin_crypto_avx2_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libflocoin_crypto_avx2_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libflocoin_crypto_avx2_a_CXXFLAGS += $(AVX2_CXXFLAGS)
crypto_libflocoin_crypto_avx2_a_CPPFLAGS += -DENABLE_AVX2
crypto_libflocoin_crypto_avx2_a_SOURCES = crypto/sha256_avx2.cpp

crypto_libflocoin_crypto_shani_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libflocoin_crypto_shani_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libflocoin_crypto_shani_a_CXXFLAGS += $(SHANI_CXXFLAGS)
crypto_libflocoin_crypto_shani_a_CPPFLAGS += -DENABLE_SHANI
crypto_libflocoin_crypto_shani_a_SOURCES = crypto/sha256_shani.cpp

# consensus: shared between all executables that validate any consensus rules.
libflocoin_consensus_a_CPPFLAGS = $(AM_CPPFLAGS) $(FLOCOIN_INCLUDES)
libflocoin_consensus_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libflocoin_consensus_a_SOURCES = \
  amount.h \
  arith_uint256.cpp \
  arith_uint256.h \
  consensus/merkle.cpp \
  consensus/merkle.h \
  consensus/params.h \
  consensus/tx_check.cpp \
  consensus/validation.h \
  hash.cpp \
  hash.h \
  prevector.h \
  primitives/block.cpp \
  primitives/block.h \
  primitives/transaction.cpp \
  primitives/transaction.h \
  pubkey.cpp \
  pubkey.h \
  script/flocoinconsensus.cpp \
  script/interpreter.cpp \
  script/interpreter.h \
  script/script.cpp \
  script/script.h \
  script/script_error.cpp \
  script/script_error.h \
  serialize.h \
  span.h \
  tinyformat.h \
  uint256.cpp \
  uint256.h \
  util/strencodings.cpp \
  util/strencodings.h \
  version.h

# common: shared between flocoind, and flocoin-qt and non-server tools
libflocoin_common_a_CPPFLAGS = $(AM_CPPFLAGS) $(FLOCOIN_INCLUDES)
libflocoin_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libflocoin_common_a_SOURCES = \
  base58.cpp \
  bech32.cpp \
  bloom.cpp \
  chainparams.cpp \
  coins.cpp \
  compressor.cpp \
  core_read.cpp \
  core_write.cpp \
  deploymentinfo.cpp \
  external_signer.cpp \
  init/common.cpp \
  key.cpp \
  key_io.cpp \
  merkleblock.cpp \
  netaddress.cpp \
  netbase.cpp \
  net_permissions.cpp \
  outputtype.cpp \
  policy/feerate.cpp \
  policy/policy.cpp \
  protocol.cpp \
  psbt.cpp \
  rpc/rawtransaction_util.cpp \
  rpc/external_signer.cpp \
  rpc/util.cpp \
  scheduler.cpp \
  script/descriptor.cpp \
  script/sign.cpp \
  script/signingprovider.cpp \
  script/standard.cpp \
  warnings.cpp \
  $(FLOCOIN_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libflocoin_util_a_CPPFLAGS = $(AM_CPPFLAGS) $(FLOCOIN_INCLUDES)
libflocoin_util_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libflocoin_util_a_SOURCES = \
  support/lockedpool.cpp \
  chainparamsbase.cpp \
  clientversion.cpp \
  compat/glibcxx_sanity.cpp \
  compat/strnlen.cpp \
  fs.cpp \
  interfaces/echo.cpp \
  interfaces/handler.cpp \
  interfaces/init.cpp \
  logging.cpp \
  random.cpp \
  randomenv.cpp \
  rpc/request.cpp \
  support/cleanse.cpp \
  sync.cpp \
  threadinterrupt.cpp \
  util/asmap.cpp \
  util/bip32.cpp \
  util/bytevectorhash.cpp \
  util/error.cpp \
  util/fees.cpp \
  util/getuniquepath.cpp \
  util/hasher.cpp \
  util/sock.cpp \
  util/system.cpp \
  util/message.cpp \
  util/moneystr.cpp \
  util/rbf.cpp \
  util/readwritefile.cpp \
  util/settings.cpp \
  util/thread.cpp \
  util/threadnames.cpp \
  util/serfloat.cpp \
  util/spanparsing.cpp \
  util/strencodings.cpp \
  util/string.cpp \
  util/time.cpp \
  util/tokenpipe.cpp \
  $(FLOCOIN_CORE_H)

if USE_LIBEVENT
libflocoin_util_a_SOURCES += util/url.cpp
endif

if GLIBC_BACK_COMPAT
libflocoin_util_a_SOURCES += compat/glibc_compat.cpp
AM_LDFLAGS += $(COMPAT_LDFLAGS)
endif

# cli: shared between flocoin-cli and flocoin-qt
libflocoin_cli_a_CPPFLAGS = $(AM_CPPFLAGS) $(FLOCOIN_INCLUDES)
libflocoin_cli_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libflocoin_cli_a_SOURCES = \
  compat/stdin.h \
  compat/stdin.cpp \
  rpc/client.cpp \
  $(FLOCOIN_CORE_H)

nodist_libflocoin_util_a_SOURCES = $(srcdir)/obj/build.h
#

# flocoind & flocoin-node binaries #
flocoin_daemon_sources = flocoind.cpp
flocoin_bin_cppflags = $(AM_CPPFLAGS) $(FLOCOIN_INCLUDES)
flocoin_bin_cxxflags = $(AM_CXXFLAGS) $(PIE_FLAGS)
flocoin_bin_ldflags = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS) $(PTHREAD_FLAGS)

if TARGET_WINDOWS
flocoin_daemon_sources += flocoind-res.rc
endif

flocoin_bin_ldadd = \
  $(LIBFLOCOIN_WALLET) \
  $(LIBFLOCOIN_COMMON) \
  $(LIBFLOCOIN_UTIL) \
  $(LIBUNIVALUE) \
  $(LIBFLOCOIN_ZMQ) \
  $(LIBFLOCOIN_CONSENSUS) \
  $(LIBFLOCOIN_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBLEVELDB_SSE42) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

flocoin_bin_ldadd += $(BOOST_LIBS) $(BDB_LIBS) $(MINIUPNPC_LIBS) $(NATPMP_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS) $(ZMQ_LIBS) $(SQLITE_LIBS)

flocoind_SOURCES = $(flocoin_daemon_sources) init/flocoind.cpp
flocoind_CPPFLAGS = $(flocoin_bin_cppflags)
flocoind_CXXFLAGS = $(flocoin_bin_cxxflags)
flocoind_LDFLAGS = $(flocoin_bin_ldflags)
flocoind_LDADD = $(LIBFLOCOIN_SERVER) $(flocoin_bin_ldadd)

flocoin_node_SOURCES = $(flocoin_daemon_sources) init/flocoin-node.cpp
flocoin_node_CPPFLAGS = $(flocoin_bin_cppflags)
flocoin_node_CXXFLAGS = $(flocoin_bin_cxxflags)
flocoin_node_LDFLAGS = $(flocoin_bin_ldflags)
flocoin_node_LDADD = $(LIBFLOCOIN_SERVER) $(flocoin_bin_ldadd) $(LIBFLOCOIN_IPC) $(LIBMULTIPROCESS_LIBS)

# flocoin-cli binary #
flocoin_cli_SOURCES = flocoin-cli.cpp
flocoin_cli_CPPFLAGS = $(AM_CPPFLAGS) $(FLOCOIN_INCLUDES) $(EVENT_CFLAGS)
flocoin_cli_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
flocoin_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS) $(PTHREAD_FLAGS)

if TARGET_WINDOWS
flocoin_cli_SOURCES += flocoin-cli-res.rc
endif

flocoin_cli_LDADD = \
  $(LIBFLOCOIN_CLI) \
  $(LIBUNIVALUE) \
  $(LIBFLOCOIN_UTIL) \
  $(LIBFLOCOIN_CRYPTO)

flocoin_cli_LDADD += $(BOOST_LIBS) $(EVENT_LIBS)
#

# flocoin-tx binary #
flocoin_tx_SOURCES = flocoin-tx.cpp
flocoin_tx_CPPFLAGS = $(AM_CPPFLAGS) $(FLOCOIN_INCLUDES)
flocoin_tx_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
flocoin_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS) $(PTHREAD_FLAGS)

if TARGET_WINDOWS
flocoin_tx_SOURCES += flocoin-tx-res.rc
endif

flocoin_tx_LDADD = \
  $(LIBUNIVALUE) \
  $(LIBFLOCOIN_COMMON) \
  $(LIBFLOCOIN_UTIL) \
  $(LIBFLOCOIN_CONSENSUS) \
  $(LIBFLOCOIN_CRYPTO) \
  $(LIBSECP256K1)

flocoin_tx_LDADD += $(BOOST_LIBS)
#

# flocoin-wallet binary #
flocoin_wallet_SOURCES = flocoin-wallet.cpp
flocoin_wallet_CPPFLAGS = $(flocoin_bin_cppflags)
flocoin_wallet_CXXFLAGS = $(flocoin_bin_cxxflags)
flocoin_wallet_LDFLAGS = $(flocoin_bin_ldflags)
flocoin_wallet_LDADD = $(LIBFLOCOIN_WALLET_TOOL) $(flocoin_bin_ldadd)

if TARGET_WINDOWS
flocoin_wallet_SOURCES += flocoin-wallet-res.rc
endif
#

# flocoin-util binary #
flocoin_util_SOURCES = flocoin-util.cpp
flocoin_util_CPPFLAGS = $(AM_CPPFLAGS) $(FLOCOIN_INCLUDES)
flocoin_util_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
flocoin_util_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS) $(PTHREAD_FLAGS)

if TARGET_WINDOWS
flocoin_util_SOURCES += flocoin-util-res.rc
endif

flocoin_util_LDADD = \
  $(LIBFLOCOIN_COMMON) \
  $(LIBFLOCOIN_UTIL) \
  $(LIBUNIVALUE) \
  $(LIBFLOCOIN_CONSENSUS) \
  $(LIBFLOCOIN_CRYPTO) \
  $(LIBSECP256K1)

flocoin_util_LDADD += $(BOOST_LIBS)
#

# flocoinconsensus library #
if BUILD_FLOCOIN_LIBS
include_HEADERS = script/flocoinconsensus.h
libflocoinconsensus_la_SOURCES = support/cleanse.cpp $(crypto_libflocoin_crypto_base_a_SOURCES) $(libflocoin_consensus_a_SOURCES)

if GLIBC_BACK_COMPAT
  libflocoinconsensus_la_SOURCES += compat/glibc_compat.cpp
endif

libflocoinconsensus_la_LDFLAGS = $(AM_LDFLAGS) -no-undefined $(RELDFLAGS)
libflocoinconsensus_la_LIBADD = $(LIBSECP256K1)
libflocoinconsensus_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(builddir)/obj -I$(srcdir)/secp256k1/include -DBUILD_FLOCOIN_INTERNAL
libflocoinconsensus_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)

endif
#

CTAES_DIST =  crypto/ctaes/bench.c
CTAES_DIST += crypto/ctaes/ctaes.c
CTAES_DIST += crypto/ctaes/ctaes.h
CTAES_DIST += crypto/ctaes/README.md
CTAES_DIST += crypto/ctaes/test.c

CLEANFILES = $(EXTRA_LIBRARIES)

CLEANFILES += *.gcda *.gcno
CLEANFILES += compat/*.gcda compat/*.gcno
CLEANFILES += consensus/*.gcda consensus/*.gcno
CLEANFILES += crc32c/src/*.gcda crc32c/src/*.gcno
CLEANFILES += crypto/*.gcda crypto/*.gcno
CLEANFILES += index/*.gcda index/*.gcno
CLEANFILES += interfaces/*.gcda interfaces/*.gcno
CLEANFILES += node/*.gcda node/*.gcno
CLEANFILES += policy/*.gcda policy/*.gcno
CLEANFILES += primitives/*.gcda primitives/*.gcno
CLEANFILES += rpc/*.gcda rpc/*.gcno
CLEANFILES += script/*.gcda script/*.gcno
CLEANFILES += support/*.gcda support/*.gcno
CLEANFILES += univalue/*.gcda univalue/*.gcno
CLEANFILES += util/*.gcda util/*.gcno
CLEANFILES += wallet/*.gcda wallet/*.gcno
CLEANFILES += wallet/test/*.gcda wallet/test/*.gcno
CLEANFILES += zmq/*.gcda zmq/*.gcno
CLEANFILES += obj/build.h

EXTRA_DIST = $(CTAES_DIST)


config/flocoin-config.h: config/stamp-h1
	@$(MAKE) -C $(top_builddir) $(subdir)/$(@)
config/stamp-h1: $(top_srcdir)/$(subdir)/config/flocoin-config.h.in $(top_builddir)/config.status
	$(AM_V_at)$(MAKE) -C $(top_builddir) $(subdir)/$(@)
$(top_srcdir)/$(subdir)/config/flocoin-config.h.in:  $(am__configure_deps)
	$(AM_V_at)$(MAKE) -C $(top_srcdir) $(subdir)/config/flocoin-config.h.in

clean-local:
	-$(MAKE) -C secp256k1 clean
	-$(MAKE) -C univalue clean
	-rm -f leveldb/*/*.gcda leveldb/*/*.gcno leveldb/helpers/memenv/*.gcda leveldb/helpers/memenv/*.gcno
	-rm -f config.h
	-rm -rf test/__pycache__

.rc.o:
	@test -f $(WINDRES)
	## FIXME: How to get the appropriate modulename_CPPFLAGS in here?
	$(AM_V_GEN) $(WINDRES) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(CPPFLAGS) -DWINDRES_PREPROC -i $< -o $@

check-symbols: $(bin_PROGRAMS)
if TARGET_DARWIN
	@echo "Checking macOS dynamic libraries..."
	$(AM_V_at) $(PYTHON) $(top_srcdir)/contrib/devtools/symbol-check.py $(bin_PROGRAMS)
endif

if TARGET_WINDOWS
	@echo "Checking Windows dynamic libraries..."
	$(AM_V_at) $(PYTHON) $(top_srcdir)/contrib/devtools/symbol-check.py $(bin_PROGRAMS)
endif

if TARGET_LINUX
	@echo "Checking glibc back compat..."
	$(AM_V_at) CPPFILT='$(CPPFILT)' $(PYTHON) $(top_srcdir)/contrib/devtools/symbol-check.py $(bin_PROGRAMS)
endif

check-security: $(bin_PROGRAMS)
if HARDEN
	@echo "Checking binary security..."
	$(AM_V_at) $(PYTHON) $(top_srcdir)/contrib/devtools/security-check.py $(bin_PROGRAMS)
endif

libflocoin_ipc_mpgen_input = \
  ipc/capnp/echo.capnp \
  ipc/capnp/init.capnp
EXTRA_DIST += $(libflocoin_ipc_mpgen_input)
%.capnp:

if BUILD_MULTIPROCESS
LIBFLOCOIN_IPC=libflocoin_ipc.a
libflocoin_ipc_a_SOURCES = \
  ipc/capnp/context.h \
  ipc/capnp/init-types.h \
  ipc/capnp/protocol.cpp \
  ipc/capnp/protocol.h \
  ipc/context.h \
  ipc/exception.h \
  ipc/interfaces.cpp \
  ipc/process.cpp \
  ipc/process.h \
  ipc/protocol.h
libflocoin_ipc_a_CPPFLAGS = $(AM_CPPFLAGS) $(FLOCOIN_INCLUDES)
libflocoin_ipc_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS) $(LIBMULTIPROCESS_CFLAGS)

include $(MPGEN_PREFIX)/include/mpgen.mk
libflocoin_ipc_mpgen_output = \
  $(libflocoin_ipc_mpgen_input:=.c++) \
  $(libflocoin_ipc_mpgen_input:=.h) \
  $(libflocoin_ipc_mpgen_input:=.proxy-client.c++) \
  $(libflocoin_ipc_mpgen_input:=.proxy-server.c++) \
  $(libflocoin_ipc_mpgen_input:=.proxy-types.c++) \
  $(libflocoin_ipc_mpgen_input:=.proxy-types.h) \
  $(libflocoin_ipc_mpgen_input:=.proxy.h)
nodist_libflocoin_ipc_a_SOURCES = $(libflocoin_ipc_mpgen_output)
CLEANFILES += $(libflocoin_ipc_mpgen_output)
endif

if EMBEDDED_LEVELDB
include Makefile.crc32c.include
include Makefile.leveldb.include
endif

include Makefile.test_util.include
include Makefile.test_fuzz.include

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_BENCH
include Makefile.bench.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
