//! @file
//!
//! Copyright (c) Memfault, Inc.
//! See License.txt for details
//!
//! API for Memfault OTA Session Metrics

#pragma once

void ota_session_metrics_start(void);
void ota_session_metrics_end(int ota_error_code);
