/****************************************************************************
 *
 * Copyright (c) 2014 - 2016 Samsung Electronics Co., Ltd. All rights reserved
 *
 ****************************************************************************/
#include "dev.h"
#include "sap.h"
#include "sap_test.h"
#include "hip.h"
#include "debug_scsc.h"

#define SUPPORTED_VERSION       13
#define SUPPORTED_OLD_VERSION   0

static int sap_test_version_supported(u16 version);
static int sap_test_rx_handler(struct slsi_dev *sdev, struct max_buff *mbuf);

static struct sap_api sap_test = {
	.sap_class = SAP_TST,
	.sap_version_supported = sap_test_version_supported,
	.sap_handler = sap_test_rx_handler,
	.sap_versions = {SUPPORTED_VERSION, SUPPORTED_OLD_VERSION},
};

static int sap_test_version_supported(u16 version)
{
	unsigned int major = SAP_MAJOR(version);
	unsigned int minor = SAP_MINOR(version);

	UNUSED(minor);				//in case of debug off - else we will get an unused warning
	u8 i = 0;

	SLSI_INFO_NODEV("Reported version: %d.%d\n", major, minor);

	for (i = 0; i < SAP_MAX_VER; i++)
		if (sap_test.sap_versions[i] == major) {
			return 0;
		}

	pr_err("%s: Version %d.%d Not supported\n", __func__, major, minor);

	return -EINVAL;
}

static int sap_test_rx_handler(struct slsi_dev *sdev, struct max_buff *mbuf)
{
	pr_err("%s: TEST SAP not implemented\n", __func__);
	return -EOPNOTSUPP;
}

int sap_test_init(void)
{
	SLSI_INFO_NODEV("Registering SAP\n");
	slsi_hip_sap_register(&sap_test);
	return 0;
}

int sap_test_deinit(void)
{
	SLSI_INFO_NODEV("Unregistering SAP\n");
	slsi_hip_sap_unregister(&sap_test);
	return 0;
}
