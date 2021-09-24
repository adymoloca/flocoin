// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2020 The Bitcoin Core developers
// Copyright (c) Flo Developers 2013-2021
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>

#include <chainparamsseeds.h>
#include <consensus/merkle.h>
#include <deploymentinfo.h>
#include <hash.h> // for signet block challenge hash
#include <util/system.h>

#include <assert.h>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

static CBlock CreateGenesisBlock(const char* pszTimestamp, const std::string strFloData, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 2;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;
    txNew.strFloData = strFloData;


    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Slashdot - 17 June 2013 - Saudi Arabia Set To Ban WhatsApp, Skype";
    const std::string strFloData = "text:Florincoin genesis block";
    const CScript genesisOutputScript = CScript() << ParseHex("040184710fa689ad5023690c80f3a49c8f13f8d45b8c857fbcbc8bc4a8e4d3eb4b10f4d4604fa08dce601aaf0f470216fe1b51850b4acf21b179c45070ac7b03a9") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, strFloData, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network on which people trade goods and services.
 */
class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = CBaseChainParams::MAIN;
        consensus.signet_blocks = false;
        consensus.signet_challenge.clear();
        consensus.nSubsidyHalvingInterval = 800000;
        consensus.BIP16Exception = uint256S("");
        consensus.BIP34Height = 1679161;
        consensus.BIP34Hash = uint256S("490a10507efe42b89104408787088b7c43310cc230310201b5f57dac6f513b8b");
        consensus.BIP65Height = 1679161; // 490a10507efe42b89104408787088b7c43310cc230310201b5f57dac6f513b8b
        consensus.BIP66Height = 1679161; // 490a10507efe42b89104408787088b7c43310cc230310201b5f57dac6f513b8b
        consensus.CSVHeight = 2757888; // 490a10507efe42b89104408787088b7c43310cc230310201b5f57dac6f513b8b
        consensus.SegwitHeight = 2757888; // 490a10507efe42b89104408787088b7c43310cc230310201b5f57dac6f513b8b
        consensus.MinBIP9WarningHeight = 2765952; // segwit activation height + miner confirmation window
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 6048; // 75% of 8064
        consensus.nMinerConfirmationWindow = 8064; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = Consensus::BIP9Deployment::NEVER_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].min_activation_height = 0; // No activation delay

        // Deployment of Taproot (BIPs 340-342)
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].bit = 2;
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].nStartTime = 1619222400; // April 24th, 2021
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].nTimeout = 1628640000; // August 11th, 2021
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].min_activation_height = 709632; // Approximately November 12th, 2021

        consensus.nMinimumChainWork = uint256S("0x00000000000000000000000000000000000000000000000050b6f9f1c2494ad8"); // 3,000,000
        consensus.defaultAssumeValid = uint256S("0x5ad3a302e3b1c681f0177411384ea03ee595a80a530c23a61f22839fae948e7f"); // 3,000,000

        // Difficulty adjustments
        consensus.nPowTargetSpacing = 40; // 40s block time
        // V1
        consensus.nTargetTimespan_Version1 = 60 * 60;
        consensus.nInterval_Version1 = consensus.nTargetTimespan_Version1 / consensus.nPowTargetSpacing;
        consensus.nMaxAdjustUp_Version1 = 75;
        consensus.nMaxAdjustDown_Version1 = 300;
        consensus.nAveragingInterval_Version1 = consensus.nInterval_Version1;
        // V2
        consensus.nHeight_Difficulty_Version2 = 208440;
        consensus.nInterval_Version2 = 15;
        consensus.nMaxAdjustDown_Version2 = 300;
        consensus.nMaxAdjustUp_Version2 = 75;
        consensus.nAveragingInterval_Version2 = consensus.nInterval_Version2;
        // V3
        consensus.nHeight_Difficulty_Version3 = 426000;
        consensus.nInterval_Version3 = 1;
        consensus.nMaxAdjustDown_Version3 = 3;
        consensus.nMaxAdjustUp_Version3 = 2;
        consensus.nAveragingInterval_Version3 = 6;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xfd;
        pchMessageStart[1] = 0xc0;
        pchMessageStart[2] = 0xa5;
        pchMessageStart[3] = 0xf1;
        nDefaultPort = 7312;
        nPruneAfterHeight = 100000;
        nNlrLimit = 100; // 100 * ~40s = ~66 minutes
        m_assumed_blockchain_size = 840;
        m_assumed_chain_state_size = 24;

        genesis = CreateGenesisBlock(1371488396, 1000112548, 0x1e0ffff0, 1, 100 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x09c7781c9df90708e278c35d38ea5c9041d7ecfcdd1c56ba67274b7cff3e1cea"));
        assert(genesis.hashMerkleRoot == uint256S("0x730f0c8ddc5a592d5512566890e2a73e45feaa6748b24b849d1c29a7ab2b2300"));

        // Note that of those with the service bits flag, most only support a subset of possible options
        vSeeds.emplace_back("seed1.florincoin.org", false);
        vSeeds.emplace_back("node.oip.fun", false);
        vSeeds.emplace_back("flodns.oip.li", false);
        vSeeds.emplace_back("flodns.oip.fun", false);
        vSeeds.emplace_back("flodns.seednode.net", false);


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,35);  //F
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,8);   //4
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,94); //e or f
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,163); //R
        base58Prefixes[SECRET_KEY2] =    std::vector<unsigned char>(1,176); //T
        base58Prefixes[EXT_PUBLIC_KEY] = {0x01, 0x34, 0x40, 0x6b}; //Fpub, Fprv for mainnet
        base58Prefixes[EXT_SECRET_KEY] = {0x01, 0x34, 0x3c, 0x31};

        bech32_hrp = "fc";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + (sizeof(pnSeed6_main)/sizeof((pnSeed6_main)[0])));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        m_is_test_chain = false;
        m_is_mockable_chain = false;

        checkpointData = {
            {
                {      0, uint256S("0x09c7781c9df90708e278c35d38ea5c9041d7ecfcdd1c56ba67274b7cff3e1cea")},
                {   8002, uint256S("0x73bc3b16d99bbf797f396c9532f80c3b73bb21304280de2efbc5edcb75739234")},
                {  18001, uint256S("0x5a7a4821aa4fc7ee3dea2f8319e9fa4d991a8c6762e79cb624c64e4cf1031582")},
                {  38002, uint256S("0x4962437c6d0a450f44c1e40cd38ff220f8122af1517e1329f1abd07fb7791e40")},
                { 160002, uint256S("0x478d381c92298614c3a05fb934a4fffc4d3e5b573efbba9b3e8b2ce8d26a0f8f")},
                { 208001, uint256S("0x2bb3f8b2d5081aefa0af9f5d8de42bd73a5d89eebf78aa7421cd63dc40a56d4c")},
                { 270001, uint256S("0x74988a3179ae6bbc5986e63f71bafc855202502b07e4d9331015eee82df80860")},
                { 290036, uint256S("0x145994381e5e4f0e5674adc1ace9a03b670838792f6bd6b650c80466453c2da3")},
                { 344665, uint256S("0x40fe36d8dec357aa529b6b1d99b2989a37ed8c7b065a0e3345cd15a751b9c1ad")},
                { 400236, uint256S("0xf9a4b8e21d410539e45ff3f11c28dee8966de7edffc45fd02dd1a5f4e7d4ef38")},
                { 415000, uint256S("0x16ef8ab98a7300039a5755d5bdc00e31dada9d2f1c440ff7928f43c4ea41c0a8")},
                { 420937, uint256S("0x48a75e4687021ec0dda2031439de50b61933e197a4e1a1185d131cc2b59b8444")},
                { 425606, uint256S("0x62c8d811b1a49f6fdaffded704dc48b1c98d6f8dd736d8afb96c9b097774a85e")},
                { 508694, uint256S("0x65cde197e9118e5164c4dcdcdc6fcfaf8c0de605d569cefd56aa220e7739da6a")},
                { 696454, uint256S("0x8cfb75684405e22f8f69522ec11f1e5206758e37f25db13880548f69fe6f1976")},
                { 955000, uint256S("0xb5517a50aee6af59eb0ab4ee3262bcbaf3f6672b9301cdd3302e4bab491e7526")},
                {1505017, uint256S("0xd38b306850bb26a5c98400df747d4391bb4e359e95e20dc79b50063ed3c5bfa7")},
                {1678879, uint256S("0x1e874e2852e8dfb3553f0e6c02dcf70e9f5697effa31385d25a3c88fe26676fc")},
                {1678909, uint256S("0x4c5a1040e337a542e6717904c8346bd72151fc34c390dff7b5cf23dcedc5058a")},
                {1679162, uint256S("0xb32c64fb80a4196ff3e1be883db10629e1d7cd27c00ef0b5d1fe54af481fc10f")},
                {1796633, uint256S("0xc2da8b936a7f2c0de02aa0c6c45f3d971ebad78655255a945b0e60b62f27d445")},
                {2094558, uint256S("0x946616c88286f32bfac15868456d87a86f8611e1f9b56594b81e46831ce43f81")},
                {2532181, uint256S("0xcacd5149aaed1088ae1db997a741210b0525e941356104120f182f3159931c79")},
                {3000000, uint256S("0x5ad3a302e3b1c681f0177411384ea03ee595a80a530c23a61f22839fae948e7f")},
            }
        };

        m_assumeutxo_data = MapAssumeutxo{
         // TODO to be specified in a future patch.
        };

        chainTxData = ChainTxData{
            // Data from RPC: getchaintxstats 4096 00000000000000000008a89e854d57e5667df88f1cdef6fde2fbca1de5b639ad
            /* nTime    */ 1538389345,
            /* nTxCount */ 4563023,
            /* dTxRate  */ 0.03,
        };
    }
};

/**
 * Testnet (v3): public test network which is reset from time to time.
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = CBaseChainParams::TESTNET;
        consensus.signet_blocks = false;
        consensus.signet_challenge.clear();
        consensus.nSubsidyHalvingInterval = 800000;
        consensus.BIP16Exception = uint256S("");
        consensus.BIP34Height = 33600;
        consensus.BIP34Hash = uint256S("4ac31d938531317c065405a9b23478c8c99204ff17fc294cb09821e2c2b42e65");
        consensus.BIP65Height = 33600; // 4ac31d938531317c065405a9b23478c8c99204ff17fc294cb09821e2c2b42e65
        consensus.BIP66Height = 33600; // 4ac31d938531317c065405a9b23478c8c99204ff17fc294cb09821e2c2b42e65
        consensus.CSVHeight = 0; // 4ac31d938531317c065405a9b23478c8c99204ff17fc294cb09821e2c2b42e65
        consensus.SegwitHeight = 0; // 4ac31d938531317c065405a9b23478c8c99204ff17fc294cb09821e2c2b42e65
        consensus.MinBIP9WarningHeight = 34400; // segwit activation height + miner confirmation window
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetSpacing = 10 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 600; // 75% of 800
        consensus.nMinerConfirmationWindow = 800;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = Consensus::BIP9Deployment::NEVER_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].min_activation_height = 0; // No activation delay

        // Deployment of Taproot (BIPs 340-342)
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].bit = 2;
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].nStartTime = 1619222400; // April 24th, 2021
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].nTimeout = 1628640000; // August 11th, 2021
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].min_activation_height = 0; // No activation delay

        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000003dd47d3172"); // 230,000
        consensus.defaultAssumeValid = uint256S("0xc2e6451240a580c3bfa5ddbfad1b001f8655e7c51d5c32c123e16f69c2d2b539"); // 230,000

        // Difficulty adjustments
        consensus.nPowTargetSpacing = 40; // 40s block time
        // V1
        consensus.nTargetTimespan_Version1 = 60 * 60;
        consensus.nInterval_Version1 = consensus.nTargetTimespan_Version1 / consensus.nPowTargetSpacing;
        consensus.nMaxAdjustUp_Version1 = 75;
        consensus.nMaxAdjustDown_Version1 = 300;
        consensus.nAveragingInterval_Version1 = consensus.nInterval_Version1;
        // V2
        consensus.nHeight_Difficulty_Version2 = 50000;
        consensus.nInterval_Version2 = 15;
        consensus.nMaxAdjustDown_Version2 = 300;
        consensus.nMaxAdjustUp_Version2 = 75;
        consensus.nAveragingInterval_Version2 = consensus.nInterval_Version2;
        // V3
        consensus.nHeight_Difficulty_Version3 = 60000;
        consensus.nInterval_Version3 = 1;
        consensus.nMaxAdjustDown_Version3 = 3;
        consensus.nMaxAdjustUp_Version3 = 2;
        consensus.nAveragingInterval_Version3 = 6;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */

        pchMessageStart[0] = 0xfd;
        pchMessageStart[1] = 0xc0;
        pchMessageStart[2] = 0x5a;
        pchMessageStart[3] = 0xf2;
        nDefaultPort = 17312;
        nPruneAfterHeight = 100000;
        nNlrLimit = 50; // 50 * ~40s = ~33 minutes
        m_assumed_blockchain_size = 40;
        m_assumed_chain_state_size = 2;

        genesis = CreateGenesisBlock(1371387277, 1000580675, 0x1e0ffff0, 1, 100 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x9b7bc86236c34b5e3a39367c036b7fe8807a966c22a7a1f0da2a198a27e03731"));
        assert(genesis.hashMerkleRoot == uint256S("0x730f0c8ddc5a592d5512566890e2a73e45feaa6748b24b849d1c29a7ab2b2300"));

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.emplace_back("testnet.oip.fun", false);

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,115);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,198);
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,58);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[SECRET_KEY2] =    std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x01, 0x34, 0x40, 0xe2};  //Fput, Fprt for testnet
        base58Prefixes[EXT_SECRET_KEY] = {0x01, 0x34, 0x3c, 0x23};

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + (sizeof(pnSeed6_test)/sizeof((pnSeed6_test)[0])));

        bech32_hrp = "tf";

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        m_is_test_chain = true;
        m_is_mockable_chain = false;

        checkpointData = {
            {
                {2056, uint256S("0xd3334db071731beaa651f10624c2fea1a5e8c6f9e50f0e602f86262938374148")},
                {230000, uint256S("0xc2e6451240a580c3bfa5ddbfad1b001f8655e7c51d5c32c123e16f69c2d2b539")},
            }
        };

        m_assumeutxo_data = MapAssumeutxo{
            // TODO to be specified in a future patch.
        };

        chainTxData = ChainTxData{
            // Data from RPC: getchaintxstats 4096 0000000000004ae2f3896ca8ecd41c460a35bf6184e145d91558cece1c688a76
            /* nTime    */ 1538135261,
            /* nTxCount */ 265211,
            /* dTxRate  */ 0.01,
        };
    }
};

/**
 * Signet: test network with an additional consensus parameter (see BIP325).
 */
class SigNetParams : public CChainParams {
public:
    explicit SigNetParams(const ArgsManager& args) {
        std::vector<uint8_t> bin;
        vSeeds.clear();

        if (!args.IsArgSet("-signetchallenge")) {
            bin = ParseHex("512103ad5e0edad18cb1f0fc0d28a3d4f1f3e445640337489abb10404f2d1e086be430210359ef5021964fe22d6f8e05b2463c9540ce96883fe3b278760f048f5189f2e6c452ae");
            // vSeeds.emplace_back("178.128.221.177");
            // vSeeds.emplace_back("2a01:7c8:d005:390::5");
            // vSeeds.emplace_back("v7ajjeirttkbnt32wpy3c6w3emwnfr3fkla7hpxcfokr3ysd3kqtzmqd.onion:38333");

            consensus.nMinimumChainWork = uint256S("0x00000000000000000000000000000000000000000000000050b6f9f1c2494ad8");
            consensus.defaultAssumeValid = uint256S("0x5ad3a302e3b1c681f0177411384ea03ee595a80a530c23a61f22839fae948e7f"); // 47200
            m_assumed_blockchain_size = 1;
            m_assumed_chain_state_size = 0;
            chainTxData = ChainTxData{
                // Data from RPC: getchaintxstats 4096 000000187d4440e5bff91488b700a140441e089a8aaea707414982460edbfe54
                /* nTime    */ 1626696658,
                /* nTxCount */ 387761,
                /* dTxRate  */ 0.04035946932424404,
            };
        } else {
            const auto signet_challenge = args.GetArgs("-signetchallenge");
            if (signet_challenge.size() != 1) {
                throw std::runtime_error(strprintf("%s: -signetchallenge cannot be multiple values.", __func__));
            }
            bin = ParseHex(signet_challenge[0]);

            consensus.nMinimumChainWork = uint256{};
            consensus.defaultAssumeValid = uint256{};
            m_assumed_blockchain_size = 0;
            m_assumed_chain_state_size = 0;
            chainTxData = ChainTxData{
                0,
                0,
                0,
            };
            LogPrintf("Signet with challenge %s\n", signet_challenge[0]);
        }

        if (args.IsArgSet("-signetseednode")) {
            vSeeds = args.GetArgs("-signetseednode");
        }

        strNetworkID = CBaseChainParams::SIGNET;
        consensus.signet_blocks = true;
        consensus.signet_challenge.assign(bin.begin(), bin.end());
        consensus.nSubsidyHalvingInterval = 800000;
        consensus.BIP16Exception = uint256{};
        consensus.BIP34Height = 1;
        consensus.BIP34Hash = uint256{};
        consensus.BIP65Height = 1;
        consensus.BIP66Height = 1;
        consensus.CSVHeight = 1;
        consensus.SegwitHeight = 1;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 600; // 75% of 800
        consensus.nMinerConfirmationWindow = 800;
        consensus.MinBIP9WarningHeight = 0;
        consensus.powLimit = uint256S("00000377ae000000000000000000000000000000000000000000000000000000");
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = Consensus::BIP9Deployment::NEVER_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].min_activation_height = 0; // No activation delay

        // Activation of Taproot (BIPs 340-342)
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].bit = 2;
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].min_activation_height = 0; // No activation delay

        // message start is defined as the first 4 bytes of the sha256d of the block script
        CHashWriter h(SER_DISK, 0);
        h << consensus.signet_challenge;
        uint256 hash = h.GetHash();
        memcpy(pchMessageStart, hash.begin(), 4);

        nDefaultPort = 17512;
        nPruneAfterHeight = 1000;
        nNlrLimit = 100; // 100 * ~40s = ~66 minutes

        genesis = CreateGenesisBlock(1371488396, 1000112548, 0x1e0ffff0, 1, 100 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x09c7781c9df90708e278c35d38ea5c9041d7ecfcdd1c56ba67274b7cff3e1cea"));
        assert(genesis.hashMerkleRoot == uint256S("0x730f0c8ddc5a592d5512566890e2a73e45feaa6748b24b849d1c29a7ab2b2300"));

        vFixedSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,35);  //F
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,8);   //4
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,94); //e or f
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,163); //R
        base58Prefixes[SECRET_KEY2] =    std::vector<unsigned char>(1,176); //T
        base58Prefixes[EXT_PUBLIC_KEY] = {0x01, 0x34, 0x40, 0x6b}; //Fpub, Fprv for mainnet
        base58Prefixes[EXT_SECRET_KEY] = {0x01, 0x34, 0x3c, 0x31};

        bech32_hrp = "fb";

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        m_is_test_chain = true;
        m_is_mockable_chain = false;
    }
};

/**
 * Regression test: intended for private networks only. Has minimal difficulty to ensure that
 * blocks can be found instantly.
 */
class CRegTestParams : public CChainParams {
public:
    explicit CRegTestParams(const ArgsManager& args) {
        strNetworkID =  CBaseChainParams::REGTEST;
        consensus.signet_blocks = false;
        consensus.signet_challenge.clear();
        consensus.nSubsidyHalvingInterval = 150;
        consensus.BIP16Exception = uint256();
        consensus.BIP34Height = 100000000; // BIP34 has not activated on regtest (far in the future so block v1 are not rejected in tests)
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 1351; // BIP65 activated on regtest (Used in rpc activation tests)
        consensus.BIP66Height = 1251; // BIP66 activated on regtest (Used in rpc activation tests)
        consensus.CSVHeight = 0; // CSV activated on regtest (Used in rpc activation tests)
        consensus.SegwitHeight = 0; // SEGWIT is always activated on regtest unless overridden
        consensus.MinBIP9WarningHeight = 0;
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].min_activation_height = 0; // No activation delay

        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].bit = 2;
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].min_activation_height = 0; // No activation delay

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        // Difficulty adjustments
        consensus.nPowTargetSpacing = 40; // 40s block time
        // V1
        consensus.nTargetTimespan_Version1 = 60 * 60;
        consensus.nInterval_Version1 = consensus.nTargetTimespan_Version1 / consensus.nPowTargetSpacing;
        consensus.nMaxAdjustUp_Version1 = 75;
        consensus.nMaxAdjustDown_Version1 = 300;
        consensus.nAveragingInterval_Version1 = consensus.nInterval_Version1;
        // V2
        consensus.nHeight_Difficulty_Version2 = 208440;
        consensus.nInterval_Version2 = 15;
        consensus.nMaxAdjustDown_Version2 = 300;
        consensus.nMaxAdjustUp_Version2 = 75;
        consensus.nAveragingInterval_Version2 = consensus.nInterval_Version2;
        // V3
        consensus.nHeight_Difficulty_Version3 = 426000;
        consensus.nInterval_Version3 = 1;
        consensus.nMaxAdjustDown_Version3 = 3;
        consensus.nMaxAdjustUp_Version3 = 2;
        consensus.nAveragingInterval_Version3 = 6;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;
        nDefaultPort = 17412;
        nPruneAfterHeight = 1000;
        nNlrLimit = 10;
        m_assumed_blockchain_size = 0;
        m_assumed_chain_state_size = 0;

        UpdateActivationParametersFromArgs(args);

        genesis = CreateGenesisBlock(1371387277, 0, 0x207fffff, 1, 100 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0xec42fa26ca6dcb1103b59a1d24b161935ea4566f8d5736db8917d5b9a8dee0d7"));
        assert(genesis.hashMerkleRoot == uint256S("0x730f0c8ddc5a592d5512566890e2a73e45feaa6748b24b849d1c29a7ab2b2300"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();
        vSeeds.emplace_back("dummySeed.invalid.");

        fDefaultConsistencyChecks = true;
        fRequireStandard = true;
        m_is_test_chain = true;
        m_is_mockable_chain = true;

        // checkpointData = {
        //     {
        //         {0, uint256S("0f9188f13cb7b2c71f2a335e3a4fc328bf5beb436012afca590b1a11466e2206")},
        //     }
        // };

        m_assumeutxo_data = MapAssumeutxo{
            // {
            //     110,
            //     {AssumeutxoHash{uint256S("0x1ebbf5850204c0bdb15bf030f47c7fe91d45c44c712697e4509ba67adb01c618")}, 110},
            // },
            // {
            //     200,
            //     {AssumeutxoHash{uint256S("0x51c8d11d8b5c1de51543c579736e786aa2736206d1e11e627568029ce092cf62")}, 200},
            // },
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,115);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,198);
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,58);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[SECRET_KEY2] =    std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "fcrt";
    }

    /**
     * Allows modifying the Version Bits regtest parameters.
     */
    void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout, int min_activation_height)
    {
        consensus.vDeployments[d].nStartTime = nStartTime;
        consensus.vDeployments[d].nTimeout = nTimeout;
        consensus.vDeployments[d].min_activation_height = min_activation_height;
    }
    void UpdateActivationParametersFromArgs(const ArgsManager& args);
};

void CRegTestParams::UpdateActivationParametersFromArgs(const ArgsManager& args)
{
    if (args.IsArgSet("-segwitheight")) {
        int64_t height = args.GetArg("-segwitheight", consensus.SegwitHeight);
        if (height < 0 || height >= std::numeric_limits<int>::max()) {
            throw std::runtime_error(strprintf("Activation height %ld for segwit is out of valid range.", height));
        }
        consensus.SegwitHeight = static_cast<int>(height);
    }

    if (!args.IsArgSet("-vbparams")) return;

    for (const std::string& strDeployment : args.GetArgs("-vbparams")) {
        std::vector<std::string> vDeploymentParams;
        boost::split(vDeploymentParams, strDeployment, boost::is_any_of(":"));
        if (vDeploymentParams.size() < 3 || 4 < vDeploymentParams.size()) {
            throw std::runtime_error("Version bits parameters malformed, expecting deployment:start:end[:min_activation_height]");
        }
        int64_t nStartTime, nTimeout;
        int min_activation_height = 0;
        if (!ParseInt64(vDeploymentParams[1], &nStartTime)) {
            throw std::runtime_error(strprintf("Invalid nStartTime (%s)", vDeploymentParams[1]));
        }
        if (!ParseInt64(vDeploymentParams[2], &nTimeout)) {
            throw std::runtime_error(strprintf("Invalid nTimeout (%s)", vDeploymentParams[2]));
        }
        if (vDeploymentParams.size() >= 4 && !ParseInt32(vDeploymentParams[3], &min_activation_height)) {
            throw std::runtime_error(strprintf("Invalid min_activation_height (%s)", vDeploymentParams[3]));
        }
        bool found = false;
        for (int j=0; j < (int)Consensus::MAX_VERSION_BITS_DEPLOYMENTS; ++j) {
            if (vDeploymentParams[0] == VersionBitsDeploymentInfo[j].name) {
                UpdateVersionBitsParameters(Consensus::DeploymentPos(j), nStartTime, nTimeout, min_activation_height);
                found = true;
                LogPrintf("Setting version bits activation parameters for %s to start=%ld, timeout=%ld, min_activation_height=%d\n", vDeploymentParams[0], nStartTime, nTimeout, min_activation_height);
                break;
            }
        }
        if (!found) {
            throw std::runtime_error(strprintf("Invalid deployment (%s)", vDeploymentParams[0]));
        }
    }
}

static std::unique_ptr<const CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<const CChainParams> CreateChainParams(const ArgsManager& args, const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN) {
        return std::unique_ptr<CChainParams>(new CMainParams());
    } else if (chain == CBaseChainParams::TESTNET) {
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    } else if (chain == CBaseChainParams::SIGNET) {
        return std::unique_ptr<CChainParams>(new SigNetParams(args));
    } else if (chain == CBaseChainParams::REGTEST) {
        return std::unique_ptr<CChainParams>(new CRegTestParams(args));
    }
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(gArgs, network);
}
