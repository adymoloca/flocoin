// Copyright (c) 2020 The Bitcoin Core developers
// Copyright (c) Flo Developers 2013-2021
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <deploymentstatus.h>

#include <consensus/params.h>
#include <versionbits.h>

VersionBitsCache g_versionbitscache;

/* Basic sanity checking for DeploymentPos enums and
 * ValidDeployment check */

static_assert(ValidDeployment(Consensus::DEPLOYMENT_TESTDUMMY), "sanity check of DeploymentPos failed (TESTDUMMY not valid)");
static_assert(!ValidDeployment(Consensus::MAX_VERSION_BITS_DEPLOYMENTS), "sanity check of DeploymentPos failed (MAX value considered valid)");
static_assert(!ValidDeployment(static_cast<Consensus::DeploymentPos>(Consensus::DEPLOYMENT_TESTDUMMY)), "sanity check of DeploymentPos failed (overlaps with DeploymentPos)");
