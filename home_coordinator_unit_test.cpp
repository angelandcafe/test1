// home_coordinator_unit_test.cpp
// Added by Andrew Baron on 2017.02.21

#include <atf-c++.hpp>
#include <home/PRHomeCoordinator.h>

ATF_TEST_CASE(construct_and_destruct);

ATF_TEST_CASE_HEAD(construct_and_destruct)
{
    set_md_var("ident", "construct_and_destruct");
    set_md_var("descr", "Create and destroy a HomeCoordinator instance.");
}

ATF_TEST_CASE_BODY(construct_and_destruct)
{
// TODO: Uncomment when Unit Tests for Presto are supported
//    eva::HomeCoordinatorRef homeCoordinator = eva::HomeCoordinator::Create();
//    ATF_REQUIRE(homeCoordinator != nullptr);
//    homeCoordinator = nullptr;
//    ATF_REQUIRE(homeCoordinator == nullptr);
}

#pragma mark Init Test Cases

ATF_INIT_TEST_CASES(all)
{
    ATF_ADD_TEST_CASE(all, construct_and_destruct);
}
