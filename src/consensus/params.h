// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2020 The Bitcoin Core developers
// Copyright (c) Flo Developers 2013-2021
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef FLOCOIN_CONSENSUS_PARAMS_H
#define FLOCOIN_CONSENSUS_PARAMS_H

#include <uint256.h>
#include <limits>

namespace Consensus {

/**
 * A buried deployment is one where the height of the activation has been hardcoded into
 * the client implementation long after the consensus change has activated. See BIP 90.
 */
enum BuriedDeployment : int16_t {
    // buried deployments get negative values to avoid overlap with DeploymentPos
    DEPLOYMENT_HEIGHTINCB = std::numeric_limits<int16_t>::min(),
    DEPLOYMENT_CLTV,
    DEPLOYMENT_DERSIG,
    DEPLOYMENT_CSV,
    DEPLOYMENT_SEGWIT,
};
constexpr bool ValidDeployment(BuriedDeployment dep) { return dep <= DEPLOYMENT_SEGWIT; }

enum DeploymentPos : uint16_t {
    DEPLOYMENT_TESTDUMMY,
    DEPLOYMENT_TAPROOT, // Deployment of Schnorr/Taproot (BIPs 340-342)
    // NOTE: Also add new deployments to VersionBitsDeploymentInfo in deploymentinfo.cpp
    MAX_VERSION_BITS_DEPLOYMENTS
};
constexpr bool ValidDeployment(DeploymentPos dep) { return dep < MAX_VERSION_BITS_DEPLOYMENTS; }

/**
 * Struct for each individual consensus rule change using BIP9.
 */
struct BIP9Deployment {
    /** Bit position to select the particular bit in nVersion. */
    int bit;
    /** Start MedianTime for version bits miner confirmation. Can be a date in the past */
    int64_t nStartTime;
    /** Timeout/expiry MedianTime for the deployment attempt. */
    int64_t nTimeout;
    /** If lock in occurs, delay activation until at least this block
     *  height.  Note that activation will only occur on a retarget
     *  boundary.
     */
    int min_activation_height{0};

    /** Constant for nTimeout very far in the future. */
    static constexpr int64_t NO_TIMEOUT = std::numeric_limits<int64_t>::max();

    /** Special value for nStartTime indicating that the deployment is always active.
     *  This is useful for testing, as it means tests don't need to deal with the activation
     *  process (which takes at least 3 BIP9 intervals). Only tests that specifically test the
     *  behaviour during activation cannot use this. */
    static constexpr int64_t ALWAYS_ACTIVE = -1;

    /** Special value for nStartTime indicating that the deployment is never active.
     *  This is useful for integrating the code changes for a new feature
     *  prior to deploying it on some or all networks. */
    static constexpr int64_t NEVER_ACTIVE = -2;
};

/**
 * Parameters that influence chain consensus.
 */
struct Params {
    uint256 hashGenesisBlock;
    int nSubsidyHalvingInterval;
    /* Block hash that is excepted from BIP16 enforcement */
    uint256 BIP16Exception;
    /** Block height and hash at which BIP34 becomes active */
    int BIP34Height;
    uint256 BIP34Hash;
    /** Block height at which BIP65 becomes active */
    int BIP65Height;
    /** Block height at which BIP66 becomes active */
    int BIP66Height;
    /** Block height at which CSV (BIP68, BIP112 and BIP113) becomes active */
    int CSVHeight;
    /** Block height at which Segwit (BIP141, BIP143 and BIP147) becomes active.
     * Note that segwit v0 script rules are enforced on all blocks except the
     * BIP 16 exception blocks. */
    int SegwitHeight;
    /** Don't warn about unknown BIP 9 activations below this height.
     * This prevents us from warning about the CSV and segwit activations. */
    int MinBIP9WarningHeight;
    /**
     * Minimum blocks including miner confirmation of the total of 2016 blocks in a retargeting period,
     * (nPowTargetTimespan / nPowTargetSpacing) which is also used for BIP9 deployments.
     * Examples: 1916 for 95%, 1512 for testchains.
     */
    uint32_t nRuleChangeActivationThreshold;
    uint32_t nMinerConfirmationWindow;
    BIP9Deployment vDeployments[MAX_VERSION_BITS_DEPLOYMENTS];
    /** Proof of work parameters */
    uint256 powLimit;
    bool fPowAllowMinDifficultyBlocks;
    bool fPowNoRetargeting;
    int64_t nPowTargetSpacing;
    /** The best chain should have at least this much work */
    uint256 nMinimumChainWork;
    /** By default assume that the signatures in ancestors of this block are valid */
    uint256 defaultAssumeValid;

    // FLO: Difficulty adjustment forks.
    int64_t TargetTimespan(int height) const {
        // V1
        if (height < nHeight_Difficulty_Version2)
            return nTargetTimespan_Version1;
        // V2
        if (height < nHeight_Difficulty_Version3)
            return nAveragingInterval_Version2 * nPowTargetSpacing;
        // V3
        return nAveragingInterval_Version3 * nPowTargetSpacing;
    }

    int64_t DifficultyAdjustmentInterval(int height) const {
        // V1
        if (height < nHeight_Difficulty_Version2)
            return nInterval_Version1;
        // V2
        if (height < nHeight_Difficulty_Version3)
            return nInterval_Version2;
        // V3
        return nInterval_Version3;
    }

    int64_t MaxActualTimespan(int height) const {
        const int64_t averagingTargetTimespan = AveragingInterval(height) * nPowTargetSpacing;
        // V1
        if (height < nHeight_Difficulty_Version2)
            return averagingTargetTimespan * (100 + nMaxAdjustDown_Version1) / 100;
        // V2
        if (height < nHeight_Difficulty_Version3)
            return averagingTargetTimespan * (100 + nMaxAdjustDown_Version2) / 100;
        // V3
        return averagingTargetTimespan * (100 + nMaxAdjustDown_Version3) / 100;
    }

    int64_t MinActualTimespan(int height) const {
        const int64_t averagingTargetTimespan = AveragingInterval(height) * nPowTargetSpacing;
        // V1
        if (height < nHeight_Difficulty_Version2)
            return averagingTargetTimespan * (100 - nMaxAdjustUp_Version1) / 100;
        // V2
        if (height < nHeight_Difficulty_Version3)
            return averagingTargetTimespan * (100 - nMaxAdjustUp_Version2) / 100;
        // V3
        return averagingTargetTimespan * (100 - nMaxAdjustUp_Version3) / 100;
    }

    int64_t AveragingInterval(int height) const {
        // V1
        if (height < nHeight_Difficulty_Version2)
            return nAveragingInterval_Version1;
        // V2
        if (height < nHeight_Difficulty_Version3)
            return nAveragingInterval_Version2;
        // V3
        return nAveragingInterval_Version3;
    }

    // V1
    int64_t nTargetTimespan_Version1;
    int64_t nInterval_Version1;
    int64_t nMaxAdjustUp_Version1;
    int64_t nMaxAdjustDown_Version1;
    int64_t nAveragingInterval_Version1;

    // V2
    int64_t nHeight_Difficulty_Version2;
    int64_t nInterval_Version2;
    int64_t nMaxAdjustDown_Version2;
    int64_t nMaxAdjustUp_Version2;
    int64_t nAveragingInterval_Version2;

    // V3
    int64_t nHeight_Difficulty_Version3;
    int64_t nInterval_Version3;
    int64_t nMaxAdjustDown_Version3;
    int64_t nMaxAdjustUp_Version3;
    int64_t nAveragingInterval_Version3;

    /**
     * If true, witness commitments contain a payload equal to a Flocoin Script solution
     * to the signet challenge. See BIP325.
     */
    bool signet_blocks{false};
    std::vector<uint8_t> signet_challenge;

    int DeploymentHeight(BuriedDeployment dep) const
    {
        switch (dep) {
        case DEPLOYMENT_HEIGHTINCB:
            return BIP34Height;
        case DEPLOYMENT_CLTV:
            return BIP65Height;
        case DEPLOYMENT_DERSIG:
            return BIP66Height;
        case DEPLOYMENT_CSV:
            return CSVHeight;
        case DEPLOYMENT_SEGWIT:
            return SegwitHeight;
        } // no default case, so the compiler can warn about missing cases
        return std::numeric_limits<int>::max();
    }
};

} // namespace Consensus

#endif // FLOCOIN_CONSENSUS_PARAMS_H
