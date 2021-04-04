#
# Copyright (C) 2018-2019 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#
$(call inherit-product, $(SRC_TARGET_DIR)/product/product_launched_with_p.mk)
$(call inherit-product, device/oneplus/sm8150-common/common.mk)

# Get non-open-source specific aspects
$(call inherit-product, vendor/oneplus/guacamole/guacamole-vendor.mk)

# Overlays
DEVICE_PACKAGE_OVERLAYS += \
    $(LOCAL_PATH)/overlay \
    $(LOCAL_PATH)/overlay-aicp

#PRODUCT_ENFORCE_RRO_EXCLUDED_OVERLAYS += \
#    $(LOCAL_PATH)/overlay/frameworks/base/packages/SystemUI

# Vendor properties
-include $(LOCAL_PATH)/vendor_props.mk

# Init
PRODUCT_PACKAGES += \
    libinit_guacamole

# Audio
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/audio/mixer_paths_pahu.xml:$(TARGET_COPY_OUT_VENDOR)/etc/mixer_paths_pahu.xml \
    $(LOCAL_PATH)/audio/mixer_paths_tavil.xml:$(TARGET_COPY_OUT_VENDOR)/etc/mixer_paths_tavil.xml

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/audio/media_codecs_dolby_audio.xml:$(TARGET_COPY_OUT_ODM)/etc/media_codecs_dolby_audio.xml \
    $(LOCAL_PATH)/audio/dolby/dax_default.xml:$(TARGET_COPY_OUT_ODM)/etc/dolby/dax_default.xml

# Camera
PRODUCT_PACKAGES += \
    OnePlusCameraHelper

# Device init scripts
PRODUCT_PACKAGES += \
    fstab.qcom \
    init.aicp-sm8150.rc

# OPFeature
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/odm_feature_list:$(TARGET_COPY_OUT_ODM)/etc/odm_feature_list

# Soong namespaces
PRODUCT_SOONG_NAMESPACES += \
    $(LOCAL_PATH)
