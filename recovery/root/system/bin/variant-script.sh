#!/system/bin/sh
# This script is needed to automatically set device props.

load_op7pro()
{
    resetprop "ro.product.model" $1
    resetprop "ro.product.name" "OnePlus7Pro"
    resetprop "ro.build.product" "OnePlus7Pro"
    resetprop "ro.product.device" "OnePlus7Pro"
    resetprop "ro.vendor.product.device" "OnePlus7Pro"
    resetprop "ro.display.series" "OnePlus 7 Pro"
}

load_op7pro5g()
{
    resetprop "ro.product.model" $1
    resetprop "ro.product.name" "OnePlus7ProNR"
    resetprop "ro.build.product" "OnePlus7ProNR"
    resetprop "ro.product.device" "OnePlus7ProNR"
    resetprop "ro.vendor.product.device" "OnePlus7ProNR"
    resetprop "ro.display.series" "OnePlus 7 Pro 5G"
}

load_op7()
{
    resetprop "ro.product.model" $1
    resetprop "ro.product.name" "OnePlus7"
    resetprop "ro.build.product" "OnePlus7"
    resetprop "ro.product.device" "OnePlus7"
    resetprop "ro.vendor.product.device" "OnePlus7"
    resetprop "ro.display.series" "OnePlus 7"
}

variant=$(getprop ro.boot.project_name)
rfversion=$(getprop ro.boot.rf_version)

echo $variant
echo $rfversion

case $variant in
    "18821")
        case $rfversion in
            "1")
            #China
                load_op7pro "GM1910"
                ;;
            "3")
            #India
                load_op7pro "GM1911"
                ;;
            "4")
            #Europe
                load_op7pro "GM1913"
                ;;
            "5")
            #Global
                load_op7pro "GM1917"
                ;;
            *)
                load_op7pro "GM1917"
                ;;
        esac
        ;;
    "18831")
    #T-Mobile
        load_op7pro "GM1915"
        ;;
    "18825")
    #5g USA
        case $rfversion in
            "5")
            #Sprint
                load_op7pro5g "GM1925"
                ;;
            *)
                load_op7pro5g "GM1925"
                ;;
        esac
        ;;
    "18827")
    #5g europe
        load_op7pro5g "GM1920"
        ;;
    "18857")
        case $rfversion in
            "1")
            #China
                load_op7 "GM1900"
                ;;
            "3")
            #India
                load_op7 "GM1901"
                ;;
            "4")
            #Europe
                load_op7 "GM1903"
                ;;
            "5")
            #Global
                load_op7 "GM1907"
                ;;
            *)
                load_op7 "GM1907"
                ;;
        esac
        ;;
    *)
        load_op7pro "GM1917"
        ;;
esac

exit 0
