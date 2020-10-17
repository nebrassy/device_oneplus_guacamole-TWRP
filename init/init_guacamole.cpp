#include <stdlib.h>

#include <android-base/file.h>
#include <android-base/logging.h>
#include <android-base/properties.h>
#include <android-base/strings.h>

#include "property_service.h"
#include "vendor_init.h"

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

using android::base::GetProperty;
using android::init::property_set;

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

void property_override(char const prop[], char const value[], bool add = true)
{
    auto pi = (prop_info *) __system_property_find(prop);

    if (pi != nullptr) {
        __system_property_update(pi, value, strlen(value));
    } else if (add) {
        __system_property_add(prop, strlen(prop), value, strlen(value));
    }
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
            set_ro_product_prop(source, "manufacturer", "OPD");
        }
        property_override("ro.build.product", "OnePlus7Pro");
        property_override("ro.display.series", "OnePlus 7 Pro");
        if (rf_version == 4) {
            /* We are Europe */
            for (const auto &source : ro_product_props_default_source_order) {
                set_ro_product_prop(source, "model", "GM1913");
            }
            for (const auto &source : ro_fingerprints_default_source_order) {
                set_ro_fingerprint(source, "google/coral/coral:11/RP1A.201005.004/6782484:user/release-keys");
            }
            for (const auto &source : ro_product_props_default_source_order) {
                set_ro_product_prop(source, "name", "OnePlus7Pro_EEA");
            }
            property_override("ro.build.description", "OnePlus7Pro-user 10 QKQ1.190716.003 2007030000 release-keys");
        } else if (rf_version == 5) {
            /* We are global */
            for (const auto &source : ro_product_props_default_source_order) {
                set_ro_product_prop(source, "model", "GM1917");
            }
            for (const auto &source : ro_fingerprints_default_source_order) {
                set_ro_fingerprint(source, "google/coral/coral:11/RP1A.201005.004/6782484:user/release-keys");
            }
            for (const auto &source : ro_product_props_default_source_order) {
                    set_ro_product_prop(source, "name", "OnePlus7Pro");
            }
            property_override("ro.build.description", "OnePlus7Pro-user 10 QKQ1.190716.003 2007030000 release-keys");
        } else if (rf_version == 1) {
            /* We are China */
            for (const auto &source : ro_product_props_default_source_order) {
                set_ro_product_prop(source, "model", "GM1910");
            }
            for (const auto &source : ro_fingerprints_default_source_order) {
                set_ro_fingerprint(source, "google/coral/coral:11/RP1A.201005.004/6782484:user/release-keys");
            }
            for (const auto &source : ro_product_props_default_source_order) {
                    set_ro_product_prop(source, "name", "OnePlus7Pro_CH");
            }
            property_override("ro.build.description", "OnePlus7Pro-user 10 QKQ1.190716.003 2007030000 release-keys");
        } else if (rf_version == 3) {
            /* We are India */
            for (const auto &source : ro_product_props_default_source_order) {
                set_ro_product_prop(source, "model", "GM1911");
            }
            for (const auto &source : ro_fingerprints_default_source_order) {
                set_ro_fingerprint(source, "google/coral/coral:11/RP1A.201005.004/6782484:user/release-keys");
            }
            for (const auto &source : ro_product_props_default_source_order) {
                    set_ro_product_prop(source, "name", "OnePlus7Pro");
            }
            property_override("ro.build.description", "OnePlus7Pro-user 10 QKQ1.190716.003 2007030000 release-keys");
        } else {
        /* Default to global */
            for (const auto &source : ro_product_props_default_source_order) {
                set_ro_product_prop(source, "model", "GM1917");
            }
            for (const auto &source : ro_fingerprints_default_source_order) {
                set_ro_fingerprint(source, "google/coral/coral:11/RP1A.201005.004/6782484:user/release-keys");
            }
            for (const auto &source : ro_product_props_default_source_order) {
                    set_ro_product_prop(source, "name", "OnePlus7Pro");
            }
            property_override("ro.build.description", "OnePlus7Pro-user 10 QKQ1.190716.003 2007030000 release-keys");
        }
    }
    property_override("ro.build.type", "user");
    property_override("ro.vendor.build.type", "user");
    property_override("ro.boot.verifiedbootstate", "green");
}
