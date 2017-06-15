// command_center_test.cpp
//
// *NOTE* 
// IF YOU ADD TESTS THAT USE FORK() TO VALIDATE AGAINST STDOUT / STDERR
// YOU *MUST* PERFORM ALL SETUP IN THE FORKED PROCESS, OR THE TEST WILL FAIL
//
// (specifically Taxonomy::Initialize() must be called in the forked process)
//

#include <atf-c++.hpp>
#include <unistd.h>
#include <dispatch/dispatch.h>
#include <commandcenter/FSCommandDispatcher.h>
#include <commandcenter/FSDummyCommand.h>
#include <commandcenter/FSIRCommand.h>
#include <commandcenter/FSCECCommand.h>
#include <commandcenter/FSHTTPCommand.h>
#include <commandcenter/FSMeshCommand.h>

using namespace fuse;
using namespace fuse::CommandCenter;


const std::string kEvaTaxonomyPath = "/usr/local/eva/sdks/darwin/share";

fuse::Device createTestDevice( const char* const suffix = "" )
{
    auto testDevice = fuse::Device::Null();
    std::string testID("TEST_DEVICE");
    testID += suffix;
    testDevice.ID = testID;
    ATF_REQUIRE(testDevice.ID == testID);
    return testDevice;
}

ATF_TEST_CASE(create_ir_command);

ATF_TEST_CASE_HEAD(create_ir_command)
{
    set_md_var("ident", "create_ir_command");
    set_md_var("descr", "Create an empty IRCommand object");
}

ATF_TEST_CASE_BODY(create_ir_command)
{
    std::unique_ptr<Command> command = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaIRCommand, fuse::Device::Null());
    ATF_REQUIRE(command != nullptr);
#pragma clang diagnostic ignored "-Wpotentially-evaluated-expression"
    ATF_REQUIRE(typeid(*command.get()) == typeid(IRCommand));
    ATF_REQUIRE(typeid(command.get()) == typeid(Command*));
    auto dummyCommand = std::unique_ptr<Command>(new DummyCommand(std::move(command), "Dummy IR: "));
    ATF_REQUIRE(dummyCommand != nullptr);
    ATF_REQUIRE(command == nullptr);
}


ATF_TEST_CASE(create_cec_command);

ATF_TEST_CASE_HEAD(create_cec_command)
{
    set_md_var("ident", "create_cec_command");
    set_md_var("descr", "Create an empty CECCommand object");
}

ATF_TEST_CASE_BODY(create_cec_command)
{
    std::unique_ptr<Command> command = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaCECCommand, fuse::Device::Null());
    ATF_REQUIRE(command != nullptr);
#pragma clang diagnostic ignored "-Wpotentially-evaluated-expression"
    ATF_REQUIRE(typeid(*command.get()) == typeid(CECCommand));
    ATF_REQUIRE(typeid(command.get()) == typeid(Command*));
    auto dummyCommand = std::unique_ptr<Command>(new DummyCommand(std::move(command), "Dummy CEC: "));
    ATF_REQUIRE(dummyCommand != nullptr);
    ATF_REQUIRE(command == nullptr);
}


ATF_TEST_CASE(create_mesh_command);

ATF_TEST_CASE_HEAD(create_mesh_command)
{
    set_md_var("ident", "create_mesh_command");
    set_md_var("descr", "Create an empty MeshCommand object");
}

ATF_TEST_CASE_BODY(create_mesh_command)
{
    std::unique_ptr<Command> command = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaMeshCommand, fuse::Device::Null());
    ATF_REQUIRE(command != nullptr);
#pragma clang diagnostic ignored "-Wpotentially-evaluated-expression"
    ATF_REQUIRE(typeid(*command.get()) == typeid(MeshCommand));
    ATF_REQUIRE(typeid(command.get()) == typeid(Command*));
    auto dummyCommand = std::unique_ptr<Command>(new DummyCommand(std::move(command), "Dummy Mesh: "));
    ATF_REQUIRE(dummyCommand != nullptr);
    ATF_REQUIRE(command == nullptr);
}


ATF_TEST_CASE(create_http_command);

ATF_TEST_CASE_HEAD(create_http_command)
{
    set_md_var("ident", "create_http_command");
    set_md_var("descr", "Create an empty HTTPCommand object");
}

ATF_TEST_CASE_BODY(create_http_command)
{
    std::unique_ptr<Command> command = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaHTTPCommand, fuse::Device::Null());
    ATF_REQUIRE(command != nullptr);
#pragma clang diagnostic ignored "-Wpotentially-evaluated-expression"
    ATF_REQUIRE(typeid(*command.get()) == typeid(HTTPCommand));
    ATF_REQUIRE(typeid(command.get()) == typeid(Command*));
    auto dummyCommand = std::unique_ptr<Command>(new DummyCommand(std::move(command), "Dummy HTTP: "));
    ATF_REQUIRE(dummyCommand != nullptr);
    ATF_REQUIRE(command == nullptr);
}


ATF_TEST_CASE(command_queue);

ATF_TEST_CASE_HEAD(command_queue)
{
    set_md_var("ident", "command_queue");
    set_md_var("descr", "CommandQueue operations test");
}

ATF_TEST_CASE_BODY(command_queue)
{
    // test push
    std::unique_ptr<Command> command1 = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaIRCommand, fuse::Device::Null());
    ATF_REQUIRE(command1 != nullptr);
    auto dummyCommand1 = std::unique_ptr<Command>(new DummyCommand(std::move(command1), "Dummy1: "));
    ATF_REQUIRE(dummyCommand1 != nullptr);
    ATF_REQUIRE(command1 == nullptr);

    std::unique_ptr<Command> command2 = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaCECCommand, fuse::Device::Null());
    ATF_REQUIRE(command2 != nullptr);
    auto dummyCommand2 = std::unique_ptr<Command>(new DummyCommand(std::move(command2), "Dummy2: "));
    ATF_REQUIRE(dummyCommand2 != nullptr);
    ATF_REQUIRE(command2 == nullptr);

    std::unique_ptr<Command> command3 = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaHTTPCommand, fuse::Device::Null());
    ATF_REQUIRE(command3 != nullptr);
    auto dummyCommand3 = std::unique_ptr<Command>(new DummyCommand(std::move(command3), "Dummy3: "));
    ATF_REQUIRE(dummyCommand3 != nullptr);
    ATF_REQUIRE(command3 == nullptr);

    std::unique_ptr<Command> command4 = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaMeshCommand, fuse::Device::Null());
    ATF_REQUIRE(command4 != nullptr);
    auto dummyCommand4 = std::unique_ptr<Command>(new DummyCommand(std::move(command4), "Dummy4: "));
    ATF_REQUIRE(dummyCommand4 != nullptr);
    ATF_REQUIRE(command4 == nullptr);

    CommandQueue commandQueue(3);
    ATF_REQUIRE(commandQueue.push(std::move(dummyCommand1)));
    ATF_REQUIRE(!commandQueue.empty());
    ATF_REQUIRE(commandQueue.size() == 1);
    ATF_REQUIRE(commandQueue.push(std::move(dummyCommand2)));
    ATF_REQUIRE(commandQueue.size() == 2);
    ATF_REQUIRE(!commandQueue.empty());
    ATF_REQUIRE(commandQueue.push(std::move(dummyCommand3)));
    ATF_REQUIRE(commandQueue.size() == 3);
    ATF_REQUIRE(!commandQueue.empty());
    ATF_REQUIRE(!commandQueue.push(std::move(dummyCommand4)));
    ATF_REQUIRE(commandQueue.size() == 3);
    ATF_REQUIRE(!commandQueue.empty());

    // test pop
    auto dummyCommand = commandQueue.pop();
    ATF_REQUIRE(dummyCommand != nullptr);
    ATF_REQUIRE(dummyCommand->description().substr(0, 6) == "Dummy1");

    dummyCommand = commandQueue.pop();
    ATF_REQUIRE(dummyCommand != nullptr);
    ATF_REQUIRE(dummyCommand->description().substr(0, 6) == "Dummy2");

    dummyCommand = commandQueue.pop();
    ATF_REQUIRE(dummyCommand != nullptr);
    ATF_REQUIRE(dummyCommand->description().substr(0, 6) == "Dummy3");

    ATF_REQUIRE(commandQueue.empty());
    ATF_REQUIRE(commandQueue.size() == 0);

    // test clear(device)
    auto testDevice = createTestDevice();

    command1 = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaIRCommand, fuse::Device::Null());
    ATF_REQUIRE(command1 != nullptr);
    dummyCommand1 = std::unique_ptr<Command>(new DummyCommand(std::move(command1), "Dummy1: "));
    ATF_REQUIRE(dummyCommand1 != nullptr);
    ATF_REQUIRE(command1 == nullptr);

    command2 = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaCECCommand, testDevice);
    ATF_REQUIRE(command2 != nullptr);
    dummyCommand2 = std::unique_ptr<Command>(new DummyCommand(std::move(command2), "Dummy2: "));
    ATF_REQUIRE(testDevice.ID == dummyCommand2->deviceId());
    ATF_REQUIRE(dummyCommand2 != nullptr);
    ATF_REQUIRE(command2 == nullptr);

    command3 = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaHTTPCommand, fuse::Device::Null());
    ATF_REQUIRE(command3 != nullptr);
    dummyCommand3 = std::unique_ptr<Command>(new DummyCommand(std::move(command3), "Dummy3: "));
    ATF_REQUIRE(dummyCommand3 != nullptr);
    ATF_REQUIRE(command3 == nullptr);

    ATF_REQUIRE(commandQueue.push(std::move(dummyCommand1)));
    ATF_REQUIRE(commandQueue.push(std::move(dummyCommand2)));
    ATF_REQUIRE(commandQueue.push(std::move(dummyCommand3)));

    ATF_REQUIRE(commandQueue.size() == 3);
    commandQueue.clear(testDevice.ID);
    ATF_REQUIRE(commandQueue.size() == 2);

    dummyCommand = commandQueue.pop();
    ATF_REQUIRE(dummyCommand != nullptr);
    ATF_REQUIRE(dummyCommand->description().substr(0, 6) == "Dummy1");

    dummyCommand = commandQueue.pop();
    ATF_REQUIRE(dummyCommand != nullptr);
    ATF_REQUIRE(dummyCommand->description().substr(0, 6) == "Dummy3");


    // test clear()
    command1 = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaIRCommand, fuse::Device::Null());
    ATF_REQUIRE(command1 != nullptr);
    dummyCommand1 = std::unique_ptr<Command>(new DummyCommand(std::move(command1), "Dummy1: "));
    ATF_REQUIRE(dummyCommand1 != nullptr);
    ATF_REQUIRE(command1 == nullptr);

    command2 = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaCECCommand, testDevice);
    ATF_REQUIRE(command2 != nullptr);
    dummyCommand2 = std::unique_ptr<Command>(new DummyCommand(std::move(command2), "Dummy2: "));
    ATF_REQUIRE(dummyCommand2 != nullptr);
    ATF_REQUIRE(command2 == nullptr);

    command3 = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaMeshCommand, fuse::Device::Null());
    ATF_REQUIRE(command3 != nullptr);
    dummyCommand3 = std::unique_ptr<Command>(new DummyCommand(std::move(command3), "Dummy3: "));
    ATF_REQUIRE(dummyCommand3 != nullptr);
    ATF_REQUIRE(command3 == nullptr);

    ATF_REQUIRE(commandQueue.push(std::move(dummyCommand1)));
    ATF_REQUIRE(commandQueue.push(std::move(dummyCommand2)));
    ATF_REQUIRE(commandQueue.push(std::move(dummyCommand3)));

    ATF_REQUIRE(commandQueue.size() == 3);

    commandQueue.clear();
    ATF_REQUIRE(commandQueue.empty());
    ATF_REQUIRE(commandQueue.size() == 0);

    // expect SIGABRT: require pop on an empty queue to runtime_assert
    expect_signal(6, "passed");
    dummyCommand = commandQueue.pop();
}


ATF_TEST_CASE(broadcast_processor);

ATF_TEST_CASE_HEAD(broadcast_processor)
{
    set_md_var("ident", "broadcast_processor");
    set_md_var("descr", "Queue a Command on the BroadcastCommandProcessor");
}

ATF_TEST_CASE_BODY(broadcast_processor)
{
    BroadcastCommandProcessor broadcast("IR", 3);

    // attach some dummy devices
    auto device = createTestDevice();
    broadcast.attachDevice(device.ID);
    auto device2 = createTestDevice("2");
    broadcast.attachDevice(device2.ID);

    // create and queue a command
    std::unique_ptr<Command> command = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaIRCommand, device);
    ATF_REQUIRE(command != nullptr);
#pragma clang diagnostic ignored "-Wpotentially-evaluated-expression"
    ATF_REQUIRE(typeid(*command.get()) == typeid(IRCommand));
    ATF_REQUIRE(typeid(command.get()) == typeid(Command*));
    auto dummyCommand = std::unique_ptr<Command>(new DummyCommand(std::move(command), "Dummy IR: "));
    ATF_REQUIRE(dummyCommand != nullptr);
    ATF_REQUIRE(command == nullptr);

    // queue
    ATF_REQUIRE(broadcast.queue(std::move(dummyCommand)));
    const pid_t control = fork();
    ATF_REQUIRE(control != -1);
    if (control == 0) {
        const pid_t pid = atf::utils::fork();
        if (pid == 0) {
            broadcast.processAll(^(bool success){ ATF_REQUIRE(success); });
            exit(1);
        }
        atf::utils::wait(pid, 1, "save:junk", "Dummy IR: Dummy Eva Command (IR)\n");
        exit(0);
    }
    else {
        int status;
        ATF_REQUIRE(waitpid(control, &status, 0) != -1);
        ATF_REQUIRE(WIFEXITED(status));
        ATF_REQUIRE_EQ(0, WEXITSTATUS(status));
    }

    // clear(device)
    command = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaIRCommand, device);
#pragma clang diagnostic ignored "-Wpotentially-evaluated-expression"
    dummyCommand = std::unique_ptr<Command>(new DummyCommand(std::move(command), "Dummy IR: "));
    ATF_REQUIRE(broadcast.queue(std::move(dummyCommand)));

    auto command2 = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaIRCommand, device2);
#pragma clang diagnostic ignored "-Wpotentially-evaluated-expression"
    auto dummyCommand2 = std::unique_ptr<Command>(new DummyCommand(std::move(command2), "Dummy IR: "));
    ATF_REQUIRE(broadcast.queue(std::move(dummyCommand2)));

    broadcast.clear(device.ID);
    // verify that process(device) now does nothing (no commands left for that device):
    const pid_t control2 = fork();
    ATF_REQUIRE(control2 != -1);
    if (control2 == 0) {
        const pid_t pid = atf::utils::fork();
        if (pid == 0) {
            broadcast.process(device, ^(bool success){ ATF_REQUIRE(success); });
            exit(1);
        }
        atf::utils::wait(pid, 1, "", "");
        exit(0);
    }
    else {
        int status;
        ATF_REQUIRE(waitpid(control2, &status, 0) != -1);
        ATF_REQUIRE(WIFEXITED(status));
        ATF_REQUIRE_EQ(0, WEXITSTATUS(status));
    }

    // verify that dummyCommand2 is still in the queue
    const pid_t control3 = fork();
    ATF_REQUIRE(control3 != -1);
    if (control3 == 0) {
        const pid_t pid = atf::utils::fork();
        if (pid == 0) {
            broadcast.processAll(^(bool success){ ATF_REQUIRE(success); });
            exit(1);
        }
        atf::utils::wait(pid, 1, "save:junk", "Dummy IR: Dummy Eva Command (IR)\n");
        exit(0);
    }
    else {
        int status;
        ATF_REQUIRE(waitpid(control3, &status, 0) != -1);
        ATF_REQUIRE(WIFEXITED(status));
        ATF_REQUIRE_EQ(0, WEXITSTATUS(status));
    }

    // clearAll()
    auto command3 = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaIRCommand, device);
#pragma clang diagnostic ignored "-Wpotentially-evaluated-expression"
    auto dummyCommand3 = std::unique_ptr<Command>(new DummyCommand(std::move(command3), "Dummy IR: "));
    ATF_REQUIRE(broadcast.queue(std::move(dummyCommand3)));

    broadcast.clearAll();

    // verify that process(device) now does nothing (no commands left)
    const pid_t control4 = fork();
    ATF_REQUIRE(control4 != -1);
    if (control4 == 0) {
        const pid_t pid = atf::utils::fork();
        if (pid == 0) {
            broadcast.processAll(^(bool success){ ATF_REQUIRE(success); });
            exit(1);
        }
        atf::utils::wait(pid, 1, "", "");
        exit(0);
    }
    else {
        int status;
        ATF_REQUIRE(waitpid(control4, &status, 0) != -1);
        ATF_REQUIRE(WIFEXITED(status));
        ATF_REQUIRE_EQ(0, WEXITSTATUS(status));
    }

    // detach the device
    broadcast.detachDevice(device.ID);

    // ensure that ops requiring device now throw
    command = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaIRCommand, fuse::Device::Null());
#pragma clang diagnostic ignored "-Wpotentially-evaluated-expression"
    dummyCommand = std::unique_ptr<Command>(new DummyCommand(std::move(command), "Dummy IR: "));
    ATF_REQUIRE(!broadcast.queue(std::move(dummyCommand)));
}


ATF_TEST_CASE(unicast_processor);

ATF_TEST_CASE_HEAD(unicast_processor)
{
    set_md_var("ident", "unicast_processor");
    set_md_var("descr", "Queue a Command on the UnicastCommandProcessor");
}

ATF_TEST_CASE_BODY(unicast_processor)
{
    UnicastCommandProcessor unicast("CEC", 3);

    // attach some dummy devices
    auto device = createTestDevice();
    unicast.attachDevice(device.ID);
    auto device2 = createTestDevice("2");
    unicast.attachDevice(device2.ID);

    // create and queue a command
    std::unique_ptr<Command> command = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaCECCommand, device);
    ATF_REQUIRE(command != nullptr);
#pragma clang diagnostic ignored "-Wpotentially-evaluated-expression"
    ATF_REQUIRE(typeid(*command.get()) == typeid(CECCommand));
    ATF_REQUIRE(typeid(command.get()) == typeid(Command*));
    auto dummyCommand = std::unique_ptr<Command>(new DummyCommand(std::move(command), "Dummy CEC: "));
    ATF_REQUIRE(dummyCommand != nullptr);
    ATF_REQUIRE(command == nullptr);

    // queue
    ATF_REQUIRE(unicast.queue(std::move(dummyCommand)));
    const pid_t control = fork();
    ATF_REQUIRE(control != -1);
    if (control == 0) {
        const pid_t pid = atf::utils::fork();
        if (pid == 0) {
            unicast.processAll(^(bool success){ ATF_REQUIRE(success); });
            exit(1);
        }
        atf::utils::wait(pid, 1, "save:junk", "Dummy CEC: Dummy Eva Command (CEC)\n");
        exit(0);
    }
    else {
        int status;
        ATF_REQUIRE(waitpid(control, &status, 0) != -1);
        ATF_REQUIRE(WIFEXITED(status));
        ATF_REQUIRE_EQ(0, WEXITSTATUS(status));
    }

    // clear(device)
    command = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaCECCommand, device);
#pragma clang diagnostic ignored "-Wpotentially-evaluated-expression"
    dummyCommand = std::unique_ptr<Command>(new DummyCommand(std::move(command), "Dummy CEC: "));
    ATF_REQUIRE(unicast.queue(std::move(dummyCommand)));

    auto command2 = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaCECCommand, device2);
#pragma clang diagnostic ignored "-Wpotentially-evaluated-expression"
    auto dummyCommand2 = std::unique_ptr<Command>(new DummyCommand(std::move(command2), "Dummy CEC: "));
    ATF_REQUIRE(unicast.queue(std::move(dummyCommand2)));

    unicast.clear(device.ID);
    // verify that process(device) now does nothing (no commands left for that device):
    const pid_t control2 = fork();
    ATF_REQUIRE(control2 != -1);
    if (control2 == 0) {
        const pid_t pid = atf::utils::fork();
        if (pid == 0) {
            unicast.process(device, ^(bool success){ ATF_REQUIRE(success); });
            exit(1);
        }
        atf::utils::wait(pid, 1, "", "");
        exit(0);
    }
    else {
        int status;
        ATF_REQUIRE(waitpid(control2, &status, 0) != -1);
        ATF_REQUIRE(WIFEXITED(status));
        ATF_REQUIRE_EQ(0, WEXITSTATUS(status));
    }

    // verify that dummyCommand2 is still in the queue
    const pid_t control3 = fork();
    ATF_REQUIRE(control3 != -1);
    if (control3 == 0) {
        const pid_t pid = atf::utils::fork();
        if (pid == 0) {
            unicast.processAll(^(bool success){ ATF_REQUIRE(success); });
            exit(1);
        }
        atf::utils::wait(pid, 1, "save:junk", "Dummy CEC: Dummy Eva Command (CEC)\n");
        exit(0);
    }
    else {
        int status;
        ATF_REQUIRE(waitpid(control3, &status, 0) != -1);
        ATF_REQUIRE(WIFEXITED(status));
        ATF_REQUIRE_EQ(0, WEXITSTATUS(status));
    }

    // clearAll()
    auto command3 = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaCECCommand, device);
#pragma clang diagnostic ignored "-Wpotentially-evaluated-expression"
    auto dummyCommand3 = std::unique_ptr<Command>(new DummyCommand(std::move(command3), "Dummy CEC: "));
    ATF_REQUIRE(unicast.queue(std::move(dummyCommand3)));

    unicast.clearAll();

    // verify that process(device) now does nothing (no commands left)
    const pid_t control4 = fork();
    ATF_REQUIRE(control4 != -1);
    if (control4 == 0) {
        const pid_t pid = atf::utils::fork();
        if (pid == 0) {
            unicast.processAll(^(bool success){ ATF_REQUIRE(success); });
            exit(1);
        }
        atf::utils::wait(pid, 1, "", "");
        exit(0);
    }
    else {
        int status;
        ATF_REQUIRE(waitpid(control4, &status, 0) != -1);
        ATF_REQUIRE(WIFEXITED(status));
        ATF_REQUIRE_EQ(0, WEXITSTATUS(status));
    }

    // detach the device
    unicast.detachDevice(device.ID);

    // ensure that ops requiring device now throw
    command = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaCECCommand, fuse::Device::Null());
#pragma clang diagnostic ignored "-Wpotentially-evaluated-expression"
    dummyCommand = std::unique_ptr<Command>(new DummyCommand(std::move(command), "Dummy CEC: "));
    ATF_REQUIRE(!unicast.queue(std::move(dummyCommand)));
}

ATF_TEST_CASE(queue_command_dispatcher);

ATF_TEST_CASE_HEAD(queue_command_dispatcher)
{
    set_md_var("ident", "queue_command_dispatcher");
    set_md_var("descr", "Queue a Command onto CommandDispatcher");
}

ATF_TEST_CASE_BODY(queue_command_dispatcher)
{
    fuse::Taxonomy::Initialize(kEvaTaxonomyPath, get_config_var("srcdir"));
    auto device = createTestDevice();
    CommandDispatcher::sharedInstance()->attachDevice(device);

    std::unique_ptr<Command> command = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaIRCommand, device);
    ATF_REQUIRE(command != nullptr);
    auto dummyCommand = std::unique_ptr<Command>(new DummyCommand(std::move(command), "Dummy: "));
    ATF_REQUIRE(dummyCommand != nullptr);
    ATF_REQUIRE(command == nullptr);

    dispatch_semaphore_t sema = dispatch_semaphore_create(0);

    // queue
    __block bool queueSucceeded = false;
    CommandDispatcher::sharedInstance()->queue(std::move(dummyCommand), ^(bool success){ queueSucceeded = true; dispatch_semaphore_signal(sema); });

    // wait for completion block to finish
    dispatch_semaphore_wait(sema, DISPATCH_TIME_FOREVER);
    dispatch_release(sema);

    ATF_REQUIRE(queueSucceeded);
}


ATF_TEST_CASE(exec_ir_command);

ATF_TEST_CASE_HEAD(exec_ir_command)
{
    set_md_var("ident", "exec_ir_command");
    set_md_var("descr", "Execute an empty IRCommand object");
}

ATF_TEST_CASE_BODY(exec_ir_command)
{
    const pid_t control = fork();
    ATF_REQUIRE(control != -1);
    if (control == 0) {
        const pid_t pid = atf::utils::fork();
        if (pid == 0) {
            fuse::Taxonomy::Initialize(kEvaTaxonomyPath, get_config_var("srcdir"));
            auto device = createTestDevice();
            CommandDispatcher::sharedInstance()->attachDevice(device);

            std::unique_ptr<Command> command = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaIRCommand, device);
#pragma clang diagnostic ignored "-Wpotentially-evaluated-expression"
            auto dummyCommand = std::unique_ptr<Command>(new DummyCommand(std::move(command), "Dummy IR: "));

            CommandDispatcher::sharedInstance()->queue(std::move(dummyCommand), ^(bool success) { ATF_REQUIRE(success); });
            usleep(100);    // crappy way to wait for background task
            exit(1);
        }
        atf::utils::wait(pid, 1, "save:junk", "Dummy IR: Dummy Eva Command (IR)\n");
        exit(0);
    }
    else {
        int status;
        ATF_REQUIRE(waitpid(control, &status, 0) != -1);
        ATF_REQUIRE(WIFEXITED(status));
        ATF_REQUIRE_EQ(0, WEXITSTATUS(status));
    }
}


ATF_TEST_CASE(exec_cec_command);

ATF_TEST_CASE_HEAD(exec_cec_command)
{
    set_md_var("ident", "exec_cec_command");
    set_md_var("descr", "Execute an empty CECCommand object");
}

ATF_TEST_CASE_BODY(exec_cec_command)
{
    const pid_t control = fork();
    ATF_REQUIRE(control != -1);
    if (control == 0) {
        const pid_t pid = atf::utils::fork();
        if (pid == 0) {
            fuse::Taxonomy::Initialize(kEvaTaxonomyPath, get_config_var("srcdir"));
            auto device = createTestDevice();
            CommandDispatcher::sharedInstance()->attachDevice(device);

            std::unique_ptr<Command> command = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaCECCommand, device);
#pragma clang diagnostic ignored "-Wpotentially-evaluated-expression"
            auto dummyCommand = std::unique_ptr<Command>(new DummyCommand(std::move(command), "Dummy CEC: "));

            CommandDispatcher::sharedInstance()->queue(std::move(dummyCommand), ^(bool success) { ATF_REQUIRE(success); });
            usleep(100);    // crappy way to wait for background task
            exit(1);
        }
        atf::utils::wait(pid, 1, "save:junk", "Dummy CEC: Dummy Eva Command (CEC)\n");
        exit(0);
    }
    else {
        int status;
        ATF_REQUIRE(waitpid(control, &status, 0) != -1);
        ATF_REQUIRE(WIFEXITED(status));
        ATF_REQUIRE_EQ(0, WEXITSTATUS(status));
    }
}


ATF_TEST_CASE(exec_http_command);

ATF_TEST_CASE_HEAD(exec_http_command)
{
    set_md_var("ident", "exec_http_command");
    set_md_var("descr", "Execute an empty HTTPCommand object");
}

ATF_TEST_CASE_BODY(exec_http_command)
{
    const pid_t control = fork();
    ATF_REQUIRE(control != -1);
    if (control == 0) {
        const pid_t pid = atf::utils::fork();
        if (pid == 0) {
            fuse::Taxonomy::Initialize(kEvaTaxonomyPath, get_config_var("srcdir"));
            auto device = createTestDevice();
            CommandDispatcher::sharedInstance()->attachDevice(device);

            std::unique_ptr<Command> command = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaHTTPCommand, device);
#pragma clang diagnostic ignored "-Wpotentially-evaluated-expression"
            auto dummyCommand = std::unique_ptr<Command>(new DummyCommand(std::move(command), "Dummy HTTP: "));

            CommandDispatcher::sharedInstance()->queue(std::move(dummyCommand), ^(bool success) { ATF_REQUIRE(success); });
            usleep(100);    // crappy way to wait for background task
            exit(1);
        }
        atf::utils::wait(pid, 1, "save:junk", "Dummy HTTP: Dummy Eva Command (HTTP)\n");
        exit(0);
    }
    else {
        int status;
        ATF_REQUIRE(waitpid(control, &status, 0) != -1);
        ATF_REQUIRE(WIFEXITED(status));
        ATF_REQUIRE_EQ(0, WEXITSTATUS(status));
    }
}


ATF_TEST_CASE(exec_mesh_command);

ATF_TEST_CASE_HEAD(exec_mesh_command)
{
    set_md_var("ident", "exec_mesh_command");
    set_md_var("descr", "Execute an empty MeshCommand object");
}

ATF_TEST_CASE_BODY(exec_mesh_command)
{
    const pid_t control = fork();
    ATF_REQUIRE(control != -1);
    if (control == 0) {
        const pid_t pid = atf::utils::fork();
        if (pid == 0) {
            fuse::Taxonomy::Initialize(kEvaTaxonomyPath, get_config_var("srcdir"));
            auto device = createTestDevice();
            CommandDispatcher::sharedInstance()->attachDevice(device);

            std::unique_ptr<Command> command = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaMeshCommand, device);
#pragma clang diagnostic ignored "-Wpotentially-evaluated-expression"
            auto dummyCommand = std::unique_ptr<Command>(new DummyCommand(std::move(command), "Dummy Mesh: "));

            CommandDispatcher::sharedInstance()->queue(std::move(dummyCommand), ^(bool success) { ATF_REQUIRE(success); });
            usleep(100);    // crappy way to wait for background task
            exit(1);
        }
        atf::utils::wait(pid, 1, "save:junk", "Dummy Mesh: Dummy Eva Command (Mesh)\n");
        exit(0);
    }
    else {
        int status;
        ATF_REQUIRE(waitpid(control, &status, 0) != -1);
        ATF_REQUIRE(WIFEXITED(status));
        ATF_REQUIRE_EQ(0, WEXITSTATUS(status));
    }
}


ATF_TEST_CASE(broadcast_continuous);

ATF_TEST_CASE_HEAD(broadcast_continuous)
{
    set_md_var("ident", "broadcast_continuous");
    set_md_var("descr", "Test continuouus & discrete commands on the broadcast processor");
}

ATF_TEST_CASE_BODY(broadcast_continuous)
{
    // queue/process 5 commands:
    // - 1 continuous on device 1 - should execute
    // - 2 continuous on device 1 - should *not* execute
    // - 3 discrete on device 2 - should execute (should *not* cancel continuous mode on device 1)
    // - 4 continuous on device 1 - should *not* execute
    // - 5 discrete on device 1 - should execute (should cancel continuous mode on device 1)
    // - 6 continuous on device 1 - should execute

    const pid_t control = fork();
    ATF_REQUIRE(control != -1);
    if (control == 0) {
        const pid_t pid = atf::utils::fork();
        if (pid == 0) {
            fuse::Taxonomy::Initialize(kEvaTaxonomyPath, get_config_var("srcdir"));

            auto device1 = createTestDevice();
            auto device2 = createTestDevice("2");
            CommandDispatcher::sharedInstance()->attachDevice(device1);
            CommandDispatcher::sharedInstance()->attachDevice(device2);

            std::unique_ptr<Command> command1 = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaIRCommand, device1, Command::Type::Continuous);
            std::unique_ptr<Command> command2 = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaIRCommand, device1, Command::Type::Continuous);
            std::unique_ptr<Command> command3 = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaIRCommand, device2, Command::Type::Discrete);
            std::unique_ptr<Command> command4 = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaIRCommand, device1, Command::Type::Continuous);
            std::unique_ptr<Command> command5 = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaIRCommand, device1, Command::Type::Discrete);
            std::unique_ptr<Command> command6 = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaIRCommand, device1, Command::Type::Continuous);
#pragma clang diagnostic ignored "-Wpotentially-evaluated-expression"
            auto cmd1 = std::unique_ptr<Command>(new DummyCommand(std::move(command1), "Dummy IR 1 (YES): "));
            auto cmd2 = std::unique_ptr<Command>(new DummyCommand(std::move(command2), "Dummy IR 2 (NO): "));
            auto cmd3 = std::unique_ptr<Command>(new DummyCommand(std::move(command3), "Dummy IR 3 (YES): "));
            auto cmd4 = std::unique_ptr<Command>(new DummyCommand(std::move(command4), "Dummy IR 4 (NO): "));
            auto cmd5 = std::unique_ptr<Command>(new DummyCommand(std::move(command5), "Dummy IR 5 (YES): "));
            auto cmd6 = std::unique_ptr<Command>(new DummyCommand(std::move(command6), "Dummy IR 6 (YES): "));

            CommandDispatcher::sharedInstance()->queue(std::move(cmd1), ^(bool success) { ATF_REQUIRE(success); });
            usleep(100);    // lousy way to sync...
            CommandDispatcher::sharedInstance()->queue(std::move(cmd2), ^(bool success) { ATF_REQUIRE(success); });
            usleep(100);
            CommandDispatcher::sharedInstance()->queue(std::move(cmd3), ^(bool success) { ATF_REQUIRE(success); });
            usleep(100);
            CommandDispatcher::sharedInstance()->queue(std::move(cmd4), ^(bool success) { ATF_REQUIRE(success); });
            usleep(100);
            CommandDispatcher::sharedInstance()->queue(std::move(cmd5), ^(bool success) { ATF_REQUIRE(success); });
            usleep(100);
            CommandDispatcher::sharedInstance()->queue(std::move(cmd6), ^(bool success) { ATF_REQUIRE(success); });
            exit(1);
        }
        std::string waitStr("Dummy IR 1 (YES): Dummy Eva Command (IR)\n"\
"Dummy IR 3 (YES): Dummy Eva Command (IR)\n"\
"Dummy IR 5 (YES): Dummy Eva Command (IR)\n"\
"Dummy IR 6 (YES): Dummy Eva Command (IR)\n");
        atf::utils::wait(pid, 1, "save:junk", waitStr);
        exit(0);
    }
    else {
        int status;
        ATF_REQUIRE(waitpid(control, &status, 0) != -1);
        ATF_REQUIRE(WIFEXITED(status));
        ATF_REQUIRE_EQ(0, WEXITSTATUS(status));
    }
}


ATF_TEST_CASE(unicast_continuous);

ATF_TEST_CASE_HEAD(unicast_continuous)
{
    set_md_var("ident", "unicast_continuous");
    set_md_var("descr", "Test continuouus & discrete commands on the unicast processor");
}

ATF_TEST_CASE_BODY(unicast_continuous)
{
    // queue/process 5 commands:
    // - 1 continuous on device 1 - should execute
    // - 2 continuous on device 1 - should *not* execute
    // - 3 discrete on device 2 - should execute (should *not* cancel continuous mode on device 1)
    // - 4 continuous on device 1 - should *not* execute
    // - 5 discrete on device 1 - should execute (should cancel continuous mode on device 1)
    // - 6 continuous on device 1 - should execute

    const pid_t control = fork();
    ATF_REQUIRE(control != -1);
    if (control == 0) {
        const pid_t pid = atf::utils::fork();
        if (pid == 0) {
            fuse::Taxonomy::Initialize(kEvaTaxonomyPath, get_config_var("srcdir"));

            auto device1 = createTestDevice();
            auto device2 = createTestDevice("2");
            CommandDispatcher::sharedInstance()->attachDevice(device1);
            CommandDispatcher::sharedInstance()->attachDevice(device2);

            std::unique_ptr<Command> command1 = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaCECCommand, device1, Command::Type::Continuous);
            std::unique_ptr<Command> command2 = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaCECCommand, device1, Command::Type::Continuous);
            std::unique_ptr<Command> command3 = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaCECCommand, device2, Command::Type::Discrete);
            std::unique_ptr<Command> command4 = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaCECCommand, device1, Command::Type::Continuous);
            std::unique_ptr<Command> command5 = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaCECCommand, device1, Command::Type::Discrete);
            std::unique_ptr<Command> command6 = CommandDispatcher::sharedInstance()->createCommand(CommandId::dummyEvaCECCommand, device1, Command::Type::Continuous);
#pragma clang diagnostic ignored "-Wpotentially-evaluated-expression"
            auto cmd1 = std::unique_ptr<Command>(new DummyCommand(std::move(command1), "Dummy CEC 1 (YES): "));
            auto cmd2 = std::unique_ptr<Command>(new DummyCommand(std::move(command2), "Dummy CEC 2 (NO): "));
            auto cmd3 = std::unique_ptr<Command>(new DummyCommand(std::move(command3), "Dummy CEC 3 (YES): "));
            auto cmd4 = std::unique_ptr<Command>(new DummyCommand(std::move(command4), "Dummy CEC 4 (NO): "));
            auto cmd5 = std::unique_ptr<Command>(new DummyCommand(std::move(command5), "Dummy CEC 5 (YES): "));
            auto cmd6 = std::unique_ptr<Command>(new DummyCommand(std::move(command6), "Dummy CEC 6 (YES): "));

            CommandDispatcher::sharedInstance()->queue(std::move(cmd1), ^(bool success) { ATF_REQUIRE(success); });
            usleep(100);    // lousy way to sync...
            CommandDispatcher::sharedInstance()->queue(std::move(cmd2), ^(bool success) { ATF_REQUIRE(success); });
            usleep(100);
            CommandDispatcher::sharedInstance()->queue(std::move(cmd3), ^(bool success) { ATF_REQUIRE(success); });
            usleep(100);
            CommandDispatcher::sharedInstance()->queue(std::move(cmd4), ^(bool success) { ATF_REQUIRE(success); });
            usleep(100);
            CommandDispatcher::sharedInstance()->queue(std::move(cmd5), ^(bool success) { ATF_REQUIRE(success); });
            usleep(100);
            CommandDispatcher::sharedInstance()->queue(std::move(cmd6), ^(bool success) { ATF_REQUIRE(success); });
            exit(1);
        }
        std::string waitStr("Dummy CEC 1 (YES): Dummy Eva Command (CEC)\n"\
"Dummy CEC 3 (YES): Dummy Eva Command (CEC)\n"\
"Dummy CEC 5 (YES): Dummy Eva Command (CEC)\n"\
"Dummy CEC 6 (YES): Dummy Eva Command (CEC)\n");
        atf::utils::wait(pid, 1, "save:junk", waitStr);
        exit(0);
    }
    else {
        int status;
        ATF_REQUIRE(waitpid(control, &status, 0) != -1);
        ATF_REQUIRE(WIFEXITED(status));
        ATF_REQUIRE_EQ(0, WEXITSTATUS(status));
    }
}


ATF_INIT_TEST_CASES(all)
{
    ATF_ADD_TEST_CASE(all, create_ir_command);
    ATF_ADD_TEST_CASE(all, create_cec_command);
    ATF_ADD_TEST_CASE(all, create_mesh_command);
    ATF_ADD_TEST_CASE(all, create_http_command);
    ATF_ADD_TEST_CASE(all, command_queue);
    ATF_ADD_TEST_CASE(all, broadcast_processor);
    ATF_ADD_TEST_CASE(all, unicast_processor);
    ATF_ADD_TEST_CASE(all, queue_command_dispatcher);
    ATF_ADD_TEST_CASE(all, exec_ir_command);
    ATF_ADD_TEST_CASE(all, exec_cec_command);
    ATF_ADD_TEST_CASE(all, exec_http_command);
    ATF_ADD_TEST_CASE(all, exec_mesh_command);
    ATF_ADD_TEST_CASE(all, broadcast_continuous);
    ATF_ADD_TEST_CASE(all, unicast_continuous);
}
