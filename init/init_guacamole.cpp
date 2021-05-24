#include <stdlib.h>

#include <android-base/file.h>
#include <android-base/logging.h>
#include <android-base/properties.h>
#include <android-base/strings.h>

// #include "property_service.h" turned off because of missing chroma.h
#include "vendor_init.h"

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>
#include <sys/sysinfo.h>

using android::base::GetProperty;

// copied from build/tools/releasetools/ota_from_target_files.py
// but with "." at the end and empty entry
std::vector<std::string> ro_product_props_default_source_order = {
    "",
    "product.",
    "odm.",
    "vendor.",
    "system.",
};

// copied from build/tools/releasetools/ota_from_target_files.py
// but with "." at the end and empty entry
std::vector<std::string> ro_fingerprints_default_source_order = {
    "",
    "product.",
    "odm.",
    "vendor.",
    "system.",
    "bootimage.",
};

void property_set(char const prop[], char const value[])
{
    prop_info *pi;
    pi = (prop_info*) __system_property_find(prop);

    if (pi && strncmp(prop, "ro.", 3))
        __system_property_update(pi, value, strlen(value));
    else if(!pi)
        __system_property_add(prop, strlen(prop), value, strlen(value));
    else
        LOG(ERROR) << "Unable to set property '" << prop << "' from vendor_init: Read-only property was already set\n";
}

void property_override(char const prop[], char const value[], bool add = true)
{
    auto pi = (prop_info *) __system_property_find(prop);

    if (pi != nullptr) {
        __system_property_update(pi, value, strlen(value));
    } else if (add) {
        __system_property_add(prop, strlen(prop), value, strlen(value));
    }
}

void load_dalvikvm_properties()
{
  struct sysinfo sys;
  sysinfo(&sys);
  if (sys.totalram > 8192ull * 1024 * 1024) {
    // from - phone-xhdpi-12288-dalvik-heap.mk
    // configuration for devices with RAM > 8GB
  property_override("dalvik.vm.heapstartsize", "24m");
  property_override("dalvik.vm.heapgrowthlimit", "384m");
  property_override("dalvik.vm.heaptargetutilization", "0.42");
  property_override("dalvik.vm.heapmaxfree", "56m");
    }
  else if(sys.totalram > 6144ull * 1024 * 1024) {
    // from - phone-xhdpi-8192-dalvik-heap.mk
    // configuration for devices with RAM > 6GB
    property_override("dalvik.vm.heapstartsize", "24m");
    property_override("dalvik.vm.heapgrowthlimit", "256m");
    property_override("dalvik.vm.heaptargetutilization", "0.46");
    property_override("dalvik.vm.heapmaxfree", "48m");
    }
  else {
    // from - phone-xhdpi-6144-dalvik-heap.mk
    property_override("dalvik.vm.heapstartsize", "16m");
    property_override("dalvik.vm.heapgrowthlimit", "256m");
    property_override("dalvik.vm.heaptargetutilization", "0.5");
    property_override("dalvik.vm.heapmaxfree", "32m");
  }
  property_override("dalvik.vm.heapsize", "512m");
  property_override("dalvik.vm.heapminfree", "8m");
}

void vendor_load_properties()
{
    const auto set_ro_product_prop = [](const std::string &source,
            const std::string &prop, const std::string &value) {
        auto prop_name = "ro.product." + source + prop;
        property_override(prop_name.c_str(), value.c_str(), false);
    };

    const auto set_ro_fingerprint = [](const std::string &source,
            const std::string &value) {
        auto prop_name = "ro." + source + "build.fingerprint";
        property_override(prop_name.c_str(), value.c_str(), false);
    };

    int project_name = stoi(android::base::GetProperty("ro.boot.project_name", ""));
    int rf_version = stoi(android::base::GetProperty("ro.boot.rf_version", ""));
    if (project_name == 18821 ) {
        /* We are guacamole */
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "brand", "OnePlus");
            set_ro_product_prop(source, "device", "OnePlus7Pro");
            set_ro_product_prop(source, "manufacturer", "OnePlus");
        }
        property_override("ro.build.product", "OnePlus7Pro");
        property_override("ro.display.series", "OnePlus 7 Pro");
        if (rf_version == 4) {
            /* We are Europe */
            for (const auto &source : ro_product_props_default_source_order) {
                set_ro_product_prop(source, "model", "GM1913");
            }
            for (const auto &source : ro_fingerprints_default_source_order) {
                set_ro_fingerprint(source, "google/coral/coral:11/RQ2A.210505.002/7246365:user/release-keys");
            }
            for (const auto &source : ro_product_props_default_source_order) {
                set_ro_product_prop(source, "name", "OnePlus7Pro_EEA");
            }
        } else if (rf_version == 5) {
            /* We are global */
            for (const auto &source : ro_product_props_default_source_order) {
                set_ro_product_prop(source, "model", "GM1917");
            }
            for (const auto &source : ro_fingerprints_default_source_order) {
                set_ro_fingerprint(source, "google/coral/coral:11/RQ2A.210505.002/7246365:user/release-keys");
            }
            for (const auto &source : ro_product_props_default_source_order) {
                    set_ro_product_prop(source, "name", "OnePlus7Pro");
            }
        } else if (rf_version == 1) {
            /* We are China */
            for (const auto &source : ro_product_props_default_source_order) {
                set_ro_product_prop(source, "model", "GM1910");
            }
            for (const auto &source : ro_fingerprints_default_source_order) {
                set_ro_fingerprint(source, "google/coral/coral:11/RQ2A.210505.002/7246365:user/release-keys");
            }
            for (const auto &source : ro_product_props_default_source_order) {
                    set_ro_product_prop(source, "name", "OnePlus7Pro_CH");
            }
        } else if (rf_version == 3) {
            /* We are India */
            for (const auto &source : ro_product_props_default_source_order) {
                set_ro_product_prop(source, "model", "GM1911");
            }
            for (const auto &source : ro_fingerprints_default_source_order) {
                set_ro_fingerprint(source, "google/coral/coral:11/RQ2A.210505.002/7246365:user/release-keys");
            }
            for (const auto &source : ro_product_props_default_source_order) {
                    set_ro_product_prop(source, "name", "OnePlus7Pro");
            }
        } else {
        /* Default to global */
            for (const auto &source : ro_product_props_default_source_order) {
                set_ro_product_prop(source, "model", "GM1917");
            }
            for (const auto &source : ro_fingerprints_default_source_order) {
                set_ro_fingerprint(source, "google/coral/coral:11/RQ2A.210505.002/7246365:user/release-keys");
            }
            for (const auto &source : ro_product_props_default_source_order) {
                    set_ro_product_prop(source, "name", "OnePlus7Pro");
            }
        }
    }
    property_override("ro.boot.flash.locked", "1");
    property_override("ro.boot.selinux", "enforcing");
    property_override("ro.boot.vbmeta.device_state", "locked");
    property_override("ro.boot.verifiedbootstate", "green");
    property_override("ro.boot.veritymode", "enforcing");
    property_override("ro.boot.warranty_bit", "0");
    property_override("ro.build.release_type", "release");
    property_override("ro.build.tags", "release-keys");
    property_override("ro.build.type", "user");
    property_override("ro.secure", "1");
    property_override("ro.vendor.build.release_type", "release");
    property_override("ro.vendor.build.type", "user");
    property_override("ro.warranty_bit", "0");
    // dalvikvm props
    load_dalvikvm_properties();
}
