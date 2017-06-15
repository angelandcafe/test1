// configure_test.cpp
// Added by Steve Orens on 10/29/2016.

#include <atf-c++.hpp>
#include <taxonomy/FSTaxonomy.h>

const std::string kEvaTaxonomyPath      = "/usr/local/eva/sdks/darwin/share";

fuse::Taxonomy::Device _createAppleTV3rdGen()
{
    fuse::Taxonomy::Device device;
    device.typeID = "eva.type.dmp";
    device.brandID = "eva.brand.apple";
    device.deviceID = "eva.device.dmp.apple.appletv3";
    device.name = "AppleTV3";
    device.friendlyName = "Apple TV";
    device.watermarkID = "appletv";
    device.protocol = 6;
    device.flags = 8;
    // TODO there is no cecVendorID field, yet
    // device.cecVendorID = "0010FA";
    device.powerOn = "device.command.menu.home";
    device.powerOff = "device.command.menu.home";
    device.cecControl = 1;
    return device;
}

fuse::Taxonomy::Device _createAppleTV4thGen()
{
    fuse::Taxonomy::Device device;
    device.typeID = "eva.type.dmp";
    device.brandID = "eva.brand.apple";
    device.deviceID = "eva.device.dmp.apple.appletv4";
    device.name = "AppleTV4";
    device.friendlyName = "Apple TV";
    device.watermarkID = "appletv";
    device.protocol = 2;
    device.flags = 8;
    device.powerOn = "device.command.menu.home";
    device.powerOff = "device.command.menu.home";
    device.cecControl = 1;
    return device;
}

fuse::Taxonomy::Device _createFireTV1stGen()
{
    fuse::Taxonomy::Device device;
    device.typeID = "eva.type.dmp";
    device.brandID = "eva.brand.amazon";
    device.deviceID = "eva.device.dmp.amazon.firetv";
    device.name = "Fire TV";
    device.friendlyName = "Fire TV";
    device.watermarkID = "firetv";
    device.protocol = 2;
    device.flags = 8;
    device.powerOn = "device.command.menu.home";
    device.powerOff = "device.command.menu.home";
    device.cecControl = 1;
    return device;
}

fuse::Taxonomy::Device _createPanasonicTV()
{
    fuse::Taxonomy::Device device;
    device.typeID = "eva.type.tv";
    device.brandID = "eva.brand.panasonic";
    device.deviceID = "eva.device.tv.panasonic.90902b";
    device.name = "90902b";
    device.protocol = 2;
    device.flags = 8;
    device.cecControl = 2;
    return device;
}

fuse::Taxonomy::Device _createSamsungTV()
{
    fuse::Taxonomy::Device device;
    device.typeID = "eva.type.tv";
    device.brandID = "eva.brand.samsung";
    device.deviceID = "eva.device.tv.samsung.aa5900430a";
    device.name = "AA5900430A";
    device.protocol = 2;
    device.flags = 8;
    device.powerOn = "device.command.power.toggle";
    device.powerOff = "device.command.power.toggle";
    device.cecControl = 2;
    return device;
}

fuse::Taxonomy::Device _createPlaystation4()
{
    fuse::Taxonomy::Device device;
    device.typeID = "eva.type.game_console";
    device.brandID = "eva.brand.sony";
    device.deviceID = "eva.device.game_console.sony.ps4";
    device.name = "Playstation 4";
    device.friendlyName = "PS4";
    device.watermarkID = "ps4";
    device.protocol = 4;
    device.flags = 10;
    device.spdInfoFrame = "8301196053434549000000005053340000000000000000000000000000";
    device.cecControl = 1;
    return device;
}

#pragma mark Configure Apple TV 3rd Gen

ATF_TEST_CASE_WITH_CLEANUP(configure_device_appletv3);

ATF_TEST_CASE_HEAD(configure_device_appletv3)
{
    set_md_var("ident", "configure_device_appletv3");
    set_md_var("descr", "Configure Apple TV 3rd Generation");
}

ATF_TEST_CASE_BODY(configure_device_appletv3)
{
    fuse::Taxonomy::Device device = _createAppleTV3rdGen();

    fuse::Device configuredDevice = fuse::Device::Null();
    // Initialize Taxonomy with the appropriate path
    fuse::Taxonomy::Initialize(kEvaTaxonomyPath, get_config_var("srcdir"));
    fuse::Taxonomy::sharedInstance()->configureDeviceFromTaxonomyDevice(device, configuredDevice);

    ATF_REQUIRE(configuredDevice.displayName == "Apple TV");
}

ATF_TEST_CASE_CLEANUP(configure_device_appletv3)
{
}

#pragma mark Configure Apple TV 4th Gen

ATF_TEST_CASE_WITH_CLEANUP(configure_device_appletv4);

ATF_TEST_CASE_HEAD(configure_device_appletv4)
{
    set_md_var("ident", "configure_device_appletv4");
    set_md_var("descr", "Configure Apple TV 4th Generation");
}

ATF_TEST_CASE_BODY(configure_device_appletv4)
{
    fuse::Taxonomy::Device device = _createAppleTV4thGen();

    fuse::Device configuredDevice = fuse::Device::Null();
    // Initialize Taxonomy with the appropriate path
    fuse::Taxonomy::Initialize(kEvaTaxonomyPath, get_config_var("srcdir"));
    fuse::Taxonomy::sharedInstance()->configureDeviceFromTaxonomyDevice(device, configuredDevice);

    ATF_REQUIRE(configuredDevice.displayName == "Apple TV");
}

ATF_TEST_CASE_CLEANUP(configure_device_appletv4)
{
}

#pragma mark Configure Playstation 4

ATF_TEST_CASE_WITH_CLEANUP(configure_device_ps4);

ATF_TEST_CASE_HEAD(configure_device_ps4)
{
    set_md_var("ident", "configure_device_ps4");
    set_md_var("descr", "Configure Playstation 4");
}

ATF_TEST_CASE_BODY(configure_device_ps4)
{
    fuse::Taxonomy::Device device = _createPlaystation4();

    fuse::Device configuredDevice = fuse::Device::Null();
    // Initialize Taxonomy with the appropriate path
    fuse::Taxonomy::Initialize(kEvaTaxonomyPath, get_config_var("srcdir"));
    fuse::Taxonomy::sharedInstance()->configureDeviceFromTaxonomyDevice(device, configuredDevice);

    ATF_REQUIRE(configuredDevice.displayName == "PS4");
}

ATF_TEST_CASE_CLEANUP(configure_device_ps4)
{
}

#pragma mark Configure Fire TV 1st Gen

ATF_TEST_CASE_WITH_CLEANUP(configure_device_firetv1);

ATF_TEST_CASE_HEAD(configure_device_firetv1)
{
    set_md_var("ident", "configure_device_firetv1");
    set_md_var("descr", "Configure Fire TV 1st Gen");
}

ATF_TEST_CASE_BODY(configure_device_firetv1)
{
    fuse::Taxonomy::Device device = _createFireTV1stGen();
    
    fuse::Device configuredDevice = fuse::Device::Null();
    // Initialize Taxonomy with the appropriate path
    fuse::Taxonomy::Initialize(kEvaTaxonomyPath, get_config_var("srcdir"));
    fuse::Taxonomy::sharedInstance()->configureDeviceFromTaxonomyDevice(device, configuredDevice);
    
    ATF_REQUIRE(configuredDevice.displayName == "Fire TV");
}

ATF_TEST_CASE_CLEANUP(configure_device_firetv1) {}

#pragma mark Configure Panasonic TV

ATF_TEST_CASE_WITH_CLEANUP(configure_device_panasonic);

ATF_TEST_CASE_HEAD(configure_device_panasonic)
{
    set_md_var("ident", "configure_device_panasonic");
    set_md_var("descr", "Configure Panasonic TV");
}

ATF_TEST_CASE_BODY(configure_device_panasonic)
{
    fuse::Taxonomy::Device device = _createPanasonicTV();
    
    fuse::Device configuredDevice = fuse::Device::Null();
    // Initialize Taxonomy with the appropriate path
    fuse::Taxonomy::Initialize(kEvaTaxonomyPath, get_config_var("srcdir"));
    fuse::Taxonomy::sharedInstance()->configureDeviceFromTaxonomyDevice(device, configuredDevice);
    
    ATF_REQUIRE(configuredDevice.displayName == "Panasonic TV");
}

ATF_TEST_CASE_CLEANUP(configure_device_panasonic) {}

#pragma mark Configure Samsung TV

ATF_TEST_CASE_WITH_CLEANUP(configure_device_samsung);

ATF_TEST_CASE_HEAD(configure_device_samsung)
{
    set_md_var("ident", "configure_device_samsung");
    set_md_var("descr", "Configure Samsung TV");
}

ATF_TEST_CASE_BODY(configure_device_samsung)
{
    fuse::Taxonomy::Device device = _createSamsungTV();
    
    fuse::Device configuredDevice = fuse::Device::Null();
    // Initialize Taxonomy with the appropriate path
    fuse::Taxonomy::Initialize(kEvaTaxonomyPath, get_config_var("srcdir"));
    fuse::Taxonomy::sharedInstance()->configureDeviceFromTaxonomyDevice(device, configuredDevice);
    
    ATF_REQUIRE(configuredDevice.displayName == "Samsung TV");
}

ATF_TEST_CASE_CLEANUP(configure_device_samsung) {}

#pragma mark Init Test Cases

ATF_INIT_TEST_CASES(all)
{
    ATF_ADD_TEST_CASE(all, configure_device_appletv3);
    ATF_ADD_TEST_CASE(all, configure_device_appletv4);
    ATF_ADD_TEST_CASE(all, configure_device_ps4);
    ATF_ADD_TEST_CASE(all, configure_device_firetv1);
    ATF_ADD_TEST_CASE(all, configure_device_panasonic);
    ATF_ADD_TEST_CASE(all, configure_device_samsung);
} 

