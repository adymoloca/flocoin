// Copyright (c) 2012-2020 The Bitcoin Core developers
// Copyright (c) Flo Developers 2013-2021
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <key.h>

#include <key_io.h>
#include <streams.h>
#include <test/util/setup_common.h>
#include <uint256.h>
#include <util/strencodings.h>
#include <util/string.h>
#include <util/system.h>

#include <string>
#include <vector>

#include <boost/test/unit_test.hpp>

static const std::string strSecret1 = "6UYrXhVrgjhHP9bjyc1HPVbKbkdLtrSLYTLZ9eJRpKUQeMTzuXt";
static const std::string strSecret2 = "6UbQ5c5u9ZSVSS7DdecXaHKSbU88NbBenepqn5Gd36cNTNAAZnx";
static const std::string strSecret1C = "RAbbcVkNJPSoJkxLgqWFLHCV6PZQosCqFqFJu9dvXrXyMmjB9Dr6";
static const std::string strSecret2C = "RAnpsKrdAnBWXFpSkm1owu2Py8iTYHt1nVxAHwqx4Fm7h2SkaSQd";
static const std::string addr1 = "FGnu49xmR6MDgZ5biBASB73A9jzn5G2Chz";
static const std::string addr2 = "FSwZQFY39grFLSfS57L2FQhX2XgJMhpuRQ";
static const std::string addr1C = "FTJAqaCyPdx9z3uSNNZz2r1D98gEJ4QpzU";
static const std::string addr2C = "FAS6sPR2dLvXKZBrDk7rmafKvW6YnoD9Vc";

static const std::string strAddressBad = "LWegHWHB5rmaF5rgWYt1YN3StapRdnGabc";


BOOST_FIXTURE_TEST_SUITE(key_tests, BasicTestingSetup)

BOOST_AUTO_TEST_CASE(key_test1)
{
    CKey key1  = DecodeSecret(strSecret1);
    BOOST_CHECK(key1.IsValid() && !key1.IsCompressed());
    CKey key2  = DecodeSecret(strSecret2);
    BOOST_CHECK(key2.IsValid() && !key2.IsCompressed());
    CKey key1C = DecodeSecret(strSecret1C);
    BOOST_CHECK(key1C.IsValid() && key1C.IsCompressed());
    CKey key2C = DecodeSecret(strSecret2C);
    BOOST_CHECK(key2C.IsValid() && key2C.IsCompressed());
    CKey bad_key = DecodeSecret(strAddressBad);
    BOOST_CHECK(!bad_key.IsValid());

    CPubKey pubkey1  = key1. GetPubKey();
    CPubKey pubkey2  = key2. GetPubKey();
    CPubKey pubkey1C = key1C.GetPubKey();
    CPubKey pubkey2C = key2C.GetPubKey();

#ifdef GENERATE_FLO_DATA
    std::cout << "static const CFlocoinAddress addr1 (\"" << pubkey1.ToString() << "\");\n";
    std::cout << "static const CFlocoinAddress addr2 (\"" << pubkey2.ToString() << "\");\n";
    std::cout << "static const CFlocoinAddress addr1C(\"" << pubkey1C.ToString() << "\");\n";
    std::cout << "static const CFlocoinAddress addr2C(\"" << pubkey2C.ToString() << "\");\n";
#endif

    BOOST_CHECK(key1.VerifyPubKey(pubkey1));
    BOOST_CHECK(!key1.VerifyPubKey(pubkey1C));
    BOOST_CHECK(!key1.VerifyPubKey(pubkey2));
    BOOST_CHECK(!key1.VerifyPubKey(pubkey2C));

    BOOST_CHECK(!key1C.VerifyPubKey(pubkey1));
    BOOST_CHECK(key1C.VerifyPubKey(pubkey1C));
    BOOST_CHECK(!key1C.VerifyPubKey(pubkey2));
    BOOST_CHECK(!key1C.VerifyPubKey(pubkey2C));

    BOOST_CHECK(!key2.VerifyPubKey(pubkey1));
    BOOST_CHECK(!key2.VerifyPubKey(pubkey1C));
    BOOST_CHECK(key2.VerifyPubKey(pubkey2));
    BOOST_CHECK(!key2.VerifyPubKey(pubkey2C));

    BOOST_CHECK(!key2C.VerifyPubKey(pubkey1));
    BOOST_CHECK(!key2C.VerifyPubKey(pubkey1C));
    BOOST_CHECK(!key2C.VerifyPubKey(pubkey2));
    BOOST_CHECK(key2C.VerifyPubKey(pubkey2C));

    BOOST_CHECK(DecodeDestination(addr1)  == CTxDestination(PKHash(pubkey1)));
    BOOST_CHECK(DecodeDestination(addr2)  == CTxDestination(PKHash(pubkey2)));
    BOOST_CHECK(DecodeDestination(addr1C) == CTxDestination(PKHash(pubkey1C)));
    BOOST_CHECK(DecodeDestination(addr2C) == CTxDestination(PKHash(pubkey2C)));

    for (int n=0; n<16; n++)
    {
        std::string strMsg = strprintf("Very secret message %i: 11", n);
        uint256 hashMsg = Hash(strMsg);

        // normal signatures

        std::vector<unsigned char> sign1, sign2, sign1C, sign2C;

        BOOST_CHECK(key1.Sign (hashMsg, sign1));
        BOOST_CHECK(key2.Sign (hashMsg, sign2));
        BOOST_CHECK(key1C.Sign(hashMsg, sign1C));
        BOOST_CHECK(key2C.Sign(hashMsg, sign2C));

        BOOST_CHECK( pubkey1.Verify(hashMsg, sign1));
        BOOST_CHECK(!pubkey1.Verify(hashMsg, sign2));
        BOOST_CHECK( pubkey1.Verify(hashMsg, sign1C));
        BOOST_CHECK(!pubkey1.Verify(hashMsg, sign2C));

        BOOST_CHECK(!pubkey2.Verify(hashMsg, sign1));
        BOOST_CHECK( pubkey2.Verify(hashMsg, sign2));
        BOOST_CHECK(!pubkey2.Verify(hashMsg, sign1C));
        BOOST_CHECK( pubkey2.Verify(hashMsg, sign2C));

        BOOST_CHECK( pubkey1C.Verify(hashMsg, sign1));
        BOOST_CHECK(!pubkey1C.Verify(hashMsg, sign2));
        BOOST_CHECK( pubkey1C.Verify(hashMsg, sign1C));
        BOOST_CHECK(!pubkey1C.Verify(hashMsg, sign2C));

        BOOST_CHECK(!pubkey2C.Verify(hashMsg, sign1));
        BOOST_CHECK( pubkey2C.Verify(hashMsg, sign2));
        BOOST_CHECK(!pubkey2C.Verify(hashMsg, sign1C));
        BOOST_CHECK( pubkey2C.Verify(hashMsg, sign2C));

        // compact signatures (with key recovery)

        std::vector<unsigned char> csign1, csign2, csign1C, csign2C;

        BOOST_CHECK(key1.SignCompact (hashMsg, csign1));
        BOOST_CHECK(key2.SignCompact (hashMsg, csign2));
        BOOST_CHECK(key1C.SignCompact(hashMsg, csign1C));
        BOOST_CHECK(key2C.SignCompact(hashMsg, csign2C));

        CPubKey rkey1, rkey2, rkey1C, rkey2C;

        BOOST_CHECK(rkey1.RecoverCompact (hashMsg, csign1));
        BOOST_CHECK(rkey2.RecoverCompact (hashMsg, csign2));
        BOOST_CHECK(rkey1C.RecoverCompact(hashMsg, csign1C));
        BOOST_CHECK(rkey2C.RecoverCompact(hashMsg, csign2C));

        BOOST_CHECK(rkey1  == pubkey1);
        BOOST_CHECK(rkey2  == pubkey2);
        BOOST_CHECK(rkey1C == pubkey1C);
        BOOST_CHECK(rkey2C == pubkey2C);
    }

    // test deterministic signing
    std::vector<unsigned char> detsig, detsigc;
    std::string strMsg = "Very deterministic message";
    uint256 hashMsg = Hash(strMsg.begin(), strMsg.end());
    BOOST_CHECK(key1.Sign(hashMsg, detsig));
    BOOST_CHECK(key1C.Sign(hashMsg, detsigc));
    BOOST_CHECK(detsig == detsigc);
    BOOST_CHECK(detsig == ParseHex("30450221008eb06cff5d3e674ec8cd6ff8178a5537af23339bcf646407fb3f4d59ff9b51560220267cca388c801f470890eb636f24eed2b432776789944435eb0b32bdf26dcf9a"));
#ifdef GENERATE_FLO_DATA
    std::cout << "detsig == ParseHex(\"";
    for (std::vector<unsigned char>::const_iterator i = detsig.begin(); i != detsig.end(); ++i)
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(*i);
    std::cout << ")\n";
#endif
    BOOST_CHECK(key2.Sign(hashMsg, detsig));
    BOOST_CHECK(key2C.Sign(hashMsg, detsigc));
    BOOST_CHECK(detsig == detsigc);
    BOOST_CHECK(detsig == ParseHex("3045022100b0208c440f805a57c654491518f6a7c699abd1767bfa738fc676fc5cb430395302206bb4ad99d6a0f952814f33816d4211ce36d7a5c116255927cf9b6b8d4779c276"));
#ifdef GENERATE_FLO_DATA
    std::cout << "detsig == ParseHex(\"";
    for (std::vector<unsigned char>::const_iterator i = detsig.begin(); i != detsig.end(); ++i)
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(*i);
    std::cout << ")\n";
#endif
    BOOST_CHECK(key1.SignCompact(hashMsg, detsig));
    BOOST_CHECK(key1C.SignCompact(hashMsg, detsigc));
    BOOST_CHECK(detsig == ParseHex("1b8eb06cff5d3e674ec8cd6ff8178a5537af23339bcf646407fb3f4d59ff9b5156267cca388c801f470890eb636f24eed2b432776789944435eb0b32bdf26dcf9a"));
#ifdef GENERATE_FLO_DATA
    std::cout << "detsig == ParseHex(\"";
    for (std::vector<unsigned char>::const_iterator i = detsig.begin(); i != detsig.end(); ++i)
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(*i);
    std::cout << ")\n";
#endif
    BOOST_CHECK(detsigc == ParseHex("1f8eb06cff5d3e674ec8cd6ff8178a5537af23339bcf646407fb3f4d59ff9b5156267cca388c801f470890eb636f24eed2b432776789944435eb0b32bdf26dcf9a"));
#ifdef GENERATE_FLO_DATA
    std::cout << "detsigc == ParseHex(\"";
    for (std::vector<unsigned char>::const_iterator i = detsigc.begin(); i != detsigc.end(); ++i)
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(*i);
    std::cout << ")\n";
#endif
    BOOST_CHECK(key2.SignCompact(hashMsg, detsig));
    BOOST_CHECK(key2C.SignCompact(hashMsg, detsigc));
    BOOST_CHECK(detsig == ParseHex("1cb0208c440f805a57c654491518f6a7c699abd1767bfa738fc676fc5cb43039536bb4ad99d6a0f952814f33816d4211ce36d7a5c116255927cf9b6b8d4779c276"));
#ifdef GENERATE_FLO_DATA
    std::cout << "detsig == ParseHex(\"";
    for (std::vector<unsigned char>::const_iterator i = detsig.begin(); i != detsig.end(); ++i)
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(*i);
    std::cout << ")\n";
#endif
    BOOST_CHECK(detsigc == ParseHex("20b0208c440f805a57c654491518f6a7c699abd1767bfa738fc676fc5cb43039536bb4ad99d6a0f952814f33816d4211ce36d7a5c116255927cf9b6b8d4779c276"));
#ifdef GENERATE_FLO_DATA
    std::cout << "detsigc == ParseHex(\"";
    for (std::vector<unsigned char>::const_iterator i = detsigc.begin(); i != detsigc.end(); ++i)
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(*i);
    std::cout << ")\n";
#endif
}

BOOST_AUTO_TEST_CASE(key_signature_tests)
{
    // When entropy is specified, we should see at least one high R signature within 20 signatures
    CKey key = DecodeSecret(strSecret1);
    std::string msg = "A message to be signed";
    uint256 msg_hash = Hash(msg);
    std::vector<unsigned char> sig;
    bool found = false;

    for (int i = 1; i <=20; ++i) {
        sig.clear();
        BOOST_CHECK(key.Sign(msg_hash, sig, false, i));
        found = sig[3] == 0x21 && sig[4] == 0x00;
        if (found) {
            break;
        }
    }
    BOOST_CHECK(found);

    // When entropy is not specified, we should always see low R signatures that are less than or equal to 70 bytes in 256 tries
    // The low R signatures should always have the value of their "length of R" byte less than or equal to 32
    // We should see at least one signature that is less than 70 bytes.
    bool found_small = false;
    bool found_big = false;
    bool bad_sign = false;
    for (int i = 0; i < 256; ++i) {
        sig.clear();
        std::string msg = "A message to be signed" + ToString(i);
        msg_hash = Hash(msg);
        if (!key.Sign(msg_hash, sig)) {
            bad_sign = true;
            break;
        }
        // sig.size() > 70 implies sig[3] > 32, because S is always low.
        // But check both conditions anyway, just in case this implication is broken for some reason
        if (sig[3] > 32 || sig.size() > 70) {
            found_big = true;
            break;
        }
        found_small |= sig.size() < 70;
    }
    BOOST_CHECK(!bad_sign);
    BOOST_CHECK(!found_big);
    BOOST_CHECK(found_small);
}

BOOST_AUTO_TEST_CASE(key_key_negation)
{
    // create a dummy hash for signature comparison
    unsigned char rnd[8];
    std::string str = "Bitcoin key verification\n";
    GetRandBytes(rnd, sizeof(rnd));
    uint256 hash;
    CHash256().Write(MakeUCharSpan(str)).Write(rnd).Finalize(hash);

    // import the static test key
    CKey key = DecodeSecret(strSecret1C);

    // create a signature
    std::vector<unsigned char> vch_sig;
    std::vector<unsigned char> vch_sig_cmp;
    key.Sign(hash, vch_sig);

    // negate the key twice
    BOOST_CHECK(key.GetPubKey().data()[0] == 0x03);
    key.Negate();
    // after the first negation, the signature must be different
    key.Sign(hash, vch_sig_cmp);
    BOOST_CHECK(vch_sig_cmp != vch_sig);
    BOOST_CHECK(key.GetPubKey().data()[0] == 0x02);
    key.Negate();
    // after the second negation, we should have the original key and thus the
    // same signature
    key.Sign(hash, vch_sig_cmp);
    BOOST_CHECK(vch_sig_cmp == vch_sig);
    BOOST_CHECK(key.GetPubKey().data()[0] == 0x03);
}

static CPubKey UnserializePubkey(const std::vector<uint8_t>& data)
{
    CDataStream stream{SER_NETWORK, INIT_PROTO_VERSION};
    stream << data;
    CPubKey pubkey;
    stream >> pubkey;
    return pubkey;
}

static unsigned int GetLen(unsigned char chHeader)
{
    if (chHeader == 2 || chHeader == 3)
        return CPubKey::COMPRESSED_SIZE;
    if (chHeader == 4 || chHeader == 6 || chHeader == 7)
        return CPubKey::SIZE;
    return 0;
}

static void CmpSerializationPubkey(const CPubKey& pubkey)
{
    CDataStream stream{SER_NETWORK, INIT_PROTO_VERSION};
    stream << pubkey;
    CPubKey pubkey2;
    stream >> pubkey2;
    BOOST_CHECK(pubkey == pubkey2);
}

BOOST_AUTO_TEST_CASE(pubkey_unserialize)
{
    for (uint8_t i = 2; i <= 7; ++i) {
        CPubKey key = UnserializePubkey({0x02});
        BOOST_CHECK(!key.IsValid());
        CmpSerializationPubkey(key);
        key = UnserializePubkey(std::vector<uint8_t>(GetLen(i), i));
        CmpSerializationPubkey(key);
        if (i == 5) {
            BOOST_CHECK(!key.IsValid());
        } else {
            BOOST_CHECK(key.IsValid());
        }
    }
}

BOOST_AUTO_TEST_SUITE_END()
