#
# Copyright (C) 2019 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

# Inherit from those products. Most specific first.
$(call inherit-product, $(SRC_TARGET_DIR)/product/core_64_bit.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)

# Inherit from guacamole device
$(call inherit-product, device/oneplus/guacamole/device.mk)

# Inherit some common AICP stuff.
$(call inherit-product, vendor/aicp/config/common_full_phone.mk)

TARGET_INCLUDE_WIFI_EXT := true

# Device identifier. This must come after all inclusions.
PRODUCT_NAME := aicp_guacamole
PRODUCT_DEVICE := guacamole
PRODUCT_BRAND := OnePlus
PRODUCT_MODEL := GM1917
PRODUCT_MANUFACTURER := OnePlus

TARGET_VENDOR_PRODUCT_NAME := OnePlus7Pro
TARGET_VENDOR_DEVICE_NAME := OnePlus7Pro

PRODUCT_AAPT_CONFIG := xxxhdpi
PRODUCT_AAPT_PREF_CONFIG := xxxhdpi
PRODUCT_CHARACTERISTICS := nosdcard

# Build info
BUILD_FINGERPRINT := "google/coral/coral:11/RP1A.201005.004/6782484:user/release-keys"
#BUILD_FINGERPRINT := "OnePlus/OnePlus7Pro/OnePlus7Pro:10/QKQ1.190716.003/2007030000:user/release-keys"

PRODUCT_BUILD_PROP_OVERRIDES += \
    PRIVATE_BUILD_DESC="OnePlus7Pro-user 10 QKQ1.190716.003 2007030000 release-keys"

PRODUCT_BUILD_PROP_OVERRIDES += \
    PRODUCT_DEVICE=OnePlus7Pro \
    PRODUCT_NAME=OnePlus7Pro

# AICP Device Maintainers
PRODUCT_BUILD_PROP_OVERRIDES += \
    DEVICE_MAINTAINERS="Julian Veit (Claymore1297), Ralf Luther (wartomato)"

PRODUCT_GMS_CLIENTID_BASE := android-oneplus

# Boot animation screen size
TARGET_SCREEN_HEIGHT := 3120
TARGET_SCREEN_WIDTH := 1440
TARGET_BOOTANIMATION_HALF_RES := true
