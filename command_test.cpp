// command_test.cpp
// Added by Steve Orens on 01/12/2017.

#include <atf-c++.hpp>
#include <taxonomy/FSTaxonomy.h>

std::string _internalCreateTestData(std::string deviceID, std::string commandID, std::string evaCommandID, int data, int cec)
{
    std::stringstream stream;
    stream << "{\"_type\": 1, \"cec\": ";
    stream << cec;
    stream << ", \"commandID\": \"";
    stream << commandID;
    stream << "\", \"data\": ";
    stream << data;
    stream << ", \"deviceID\": \"";
    stream << deviceID;
    stream << "\", \"evaCommandID\": \"";
    stream << evaCommandID;
    stream << "\", \"groupID\": \"eva.command.group.123\", \
        \"groupName\": \"\", \"iconID\": \"enter\", \"irLength\": 10, \"irValue\": \"0A0B0C0D0E0F10111213\", \
        \"longName\": \"Enter\", \"mapped\": false, \"name\": \"Enter\", \"primaryKey\": 14, \"protocol\": 0, \
        \"timestamp\": 74748282}";

    return stream.str();
}

fuse::Taxonomy::Command _internalCreateTestCommand(std::string deviceID, std::string commandID, std::string evaCommandID, int data, int cec)
{
    fuse::Taxonomy::Command command = fuse::Taxonomy::Command::CreateEvaCommand();
    command.deviceID = deviceID;
    command.commandID = commandID;
    command.evaCommandID = evaCommandID;
    command.data = data;
    command.cec = cec;

    return command;
}

ATF_TEST_CASE(command_construct_null);

ATF_TEST_CASE_HEAD(command_construct_null)
{
    set_md_var("ident", "command_construct_null");
    set_md_var("descr", "Create an empty Command object");
}

ATF_TEST_CASE_BODY(command_construct_null)
{
    fuse::Taxonomy::Command command = fuse::Taxonomy::Command::Null();
    ATF_REQUIRE(command._type == fuse::Taxonomy::RecordType::Null);
    ATF_REQUIRE(command.isValid() == false);
    ATF_REQUIRE(command.isEva() == false);
    ATF_REQUIRE(command.isUser() == false);
}

ATF_TEST_CASE(command_construct_eva_command);

ATF_TEST_CASE_HEAD(command_construct_eva_command)
{
    set_md_var("ident", "command_construct_eva_command");
    set_md_var("descr", "Create an EVA (read-only) Command object");
}

ATF_TEST_CASE_BODY(command_construct_eva_command)
{
    fuse::Taxonomy::Command command = fuse::Taxonomy::Command::CreateEvaCommand();
    ATF_REQUIRE(command._type == fuse::Taxonomy::RecordType::Eva);
    ATF_REQUIRE(command.isValid() == true);
    ATF_REQUIRE(command.isEva() == true);
    ATF_REQUIRE(command.isUser() == false);
}

ATF_TEST_CASE(command_construct_user_command);

ATF_TEST_CASE_HEAD(command_construct_user_command)
{
    set_md_var("ident", "command_construct_user_command");
    set_md_var("descr", "Create an User (red-write) Command object");
}

ATF_TEST_CASE_BODY(command_construct_user_command)
{
    fuse::Taxonomy::Command command = fuse::Taxonomy::Command::CreateUserCommand();
    ATF_REQUIRE(command._type == fuse::Taxonomy::RecordType::User);
    ATF_REQUIRE(command.isValid() == true);
    ATF_REQUIRE(command.isEva() == false);
    ATF_REQUIRE(command.isUser() == true);
}

ATF_TEST_CASE(command_to_json);

ATF_TEST_CASE_HEAD(command_to_json)
{
    set_md_var("ident", "command_to_json");
    set_md_var("descr", "Taxonomy::Command to_json");
}

ATF_TEST_CASE_BODY(command_to_json)
{
    fuse::Taxonomy::Command command = fuse::Taxonomy::Command::Null();
    command.deviceID = "deviceID";
    command.commandID = "commandID";
    command.name = "name";
    command.longName = "longName";
    command.groupID = "groupID";
    command.iconID = "iconID";
    command.groupName = "groupName";
    command.evaCommandID = "evaCommandID";
    command.data = 1;
    command.cec = 2;
    command.protocol = 3;
    command.mapped = true;
    int size = 512;
    for (int i = 0; i < size; i++) {
        int t = i;
        if (t > 255)
            t -= 255;
        command.irValue[i] = t;
    }
    command.irLength = size;
    command.timestamp = DBL_MAX;
    command._type = fuse::Taxonomy::RecordType::Eva;
    command.primaryKey = 10;
    auto json = command.toJson();
    
    ATF_REQUIRE(json["deviceID"].string_value() == "deviceID");
    ATF_REQUIRE(json["commandID"].string_value() == "commandID");
    ATF_REQUIRE(json["name"].string_value() == "name");
    ATF_REQUIRE(json["longName"].string_value() == "longName");
    ATF_REQUIRE(json["groupID"].string_value() == "groupID");
    ATF_REQUIRE(json["iconID"].string_value() == "iconID");
    ATF_REQUIRE(json["groupName"].string_value() == "groupName");
    ATF_REQUIRE(json["evaCommandID"].string_value() == "evaCommandID");
    ATF_REQUIRE(json["data"].int_value() == 1);
    ATF_REQUIRE(json["cec"].int_value() == 2);
    ATF_REQUIRE(json["protocol"].int_value() == 3);
    ATF_REQUIRE(json["mapped"].bool_value() == true);
    ATF_REQUIRE(json["irValue"].string_value() == Jetpack::Foundation::Data::Hex(reinterpret_cast<const char*>(command.irValue), command.irLength));
    ATF_REQUIRE(json["irLength"].int_value() == size);
    ATF_REQUIRE(json["timestamp"].number_value() == DBL_MAX);
    ATF_REQUIRE(json["_type"].int_value() == (int)fuse::Taxonomy::RecordType::Eva);
    ATF_REQUIRE(json["primaryKey"].int_value() == 10);
}

ATF_TEST_CASE(command_from_json);

ATF_TEST_CASE_HEAD(command_from_json)
{
    set_md_var("ident", "command_from_json");
    set_md_var("descr", "Taxonomy::Command from_json");
}

ATF_TEST_CASE_BODY(command_from_json)
{
    std::string jsonString = _internalCreateTestData("bar", "device.command.channel.enter", "foo", 0, 43);

    std::string error;
    json11::Json jsonObject = json11::Json::parse(jsonString, error);
    ATF_REQUIRE(error.empty());
    fuse::Taxonomy::Command command(jsonObject);
    ATF_REQUIRE(command.isValid() == true);
    ATF_REQUIRE(command.cec == 43);
    ATF_REQUIRE(command.commandID == "device.command.channel.enter");
    ATF_REQUIRE(command.data == 0);
    ATF_REQUIRE(command.deviceID == "bar");
    ATF_REQUIRE(command.evaCommandID == "foo");
    ATF_REQUIRE(command.groupID == "eva.command.group.123");
    ATF_REQUIRE(command.iconID == "enter");
    ATF_REQUIRE(command.irLength == 10);
    ATF_REQUIRE(command.irValue[0] == 10);
    ATF_REQUIRE(command.irValue[1] == 11);
    ATF_REQUIRE(command.irValue[2] == 12);
    ATF_REQUIRE(command.irValue[3] == 13);
    ATF_REQUIRE(command.irValue[4] == 14);
    ATF_REQUIRE(command.irValue[5] == 15);
    ATF_REQUIRE(command.irValue[6] == 16);
    ATF_REQUIRE(command.irValue[7] == 17);
    ATF_REQUIRE(command.irValue[8] == 18);
    ATF_REQUIRE(command.irValue[9] == 19);
    ATF_REQUIRE(command.name == "Enter");
    ATF_REQUIRE(command.longName == "Enter");
    ATF_REQUIRE(command.timestamp == 74748282);
}

ATF_TEST_CASE(command_commandlist_to_json);

ATF_TEST_CASE_HEAD(command_commandlist_to_json)
{
    set_md_var("ident", "command_commandlist_to_json");
    set_md_var("descr", "Taxonomy::Command CommandList to_json");
}

ATF_TEST_CASE_BODY(command_commandlist_to_json)
{
    fuse::Taxonomy::Command command1 = _internalCreateTestCommand("device1", "command1", "evaCommand1", 1, 1);
    fuse::Taxonomy::Command command2 = _internalCreateTestCommand("device2", "command2", "evaCommand2", 2, 2);
    fuse::Taxonomy::Command command3 = _internalCreateTestCommand("device3", "command3", "evaCommand3", 3, 3);
    fuse::Taxonomy::Command command4 = _internalCreateTestCommand("device4", "command4", "evaCommand4", 4, 4);

    std::vector<fuse::Taxonomy::Command> commands;
    commands.push_back(command1);
    commands.push_back(command2);
    commands.push_back(command3);
    commands.push_back(command4);

    auto json = fuse::Taxonomy::Command::ExportListToJson(commands);

    ATF_REQUIRE(json[0]["deviceID"].string_value() == "device1");
    ATF_REQUIRE(json[0]["commandID"].string_value() == "command1");
    ATF_REQUIRE(json[0]["evaCommandID"].string_value() == "evaCommand1");
    ATF_REQUIRE(json[0]["data"].int_value() == 1);
    ATF_REQUIRE(json[0]["cec"].int_value() == 1);
    ATF_REQUIRE(json[1]["deviceID"].string_value() == "device2");
    ATF_REQUIRE(json[1]["commandID"].string_value() == "command2");
    ATF_REQUIRE(json[1]["evaCommandID"].string_value() == "evaCommand2");
    ATF_REQUIRE(json[1]["data"].int_value() == 2);
    ATF_REQUIRE(json[1]["cec"].int_value() == 2);
    ATF_REQUIRE(json[2]["deviceID"].string_value() == "device3");
    ATF_REQUIRE(json[2]["commandID"].string_value() == "command3");
    ATF_REQUIRE(json[2]["evaCommandID"].string_value() == "evaCommand3");
    ATF_REQUIRE(json[2]["data"].int_value() == 3);
    ATF_REQUIRE(json[2]["cec"].int_value() == 3);
    ATF_REQUIRE(json[3]["deviceID"].string_value() == "device4");
    ATF_REQUIRE(json[3]["commandID"].string_value() == "command4");
    ATF_REQUIRE(json[3]["evaCommandID"].string_value() == "evaCommand4");
    ATF_REQUIRE(json[3]["data"].int_value() == 4);
    ATF_REQUIRE(json[3]["cec"].int_value() == 4);
}

ATF_TEST_CASE(command_commandmap_to_json);

ATF_TEST_CASE_HEAD(command_commandmap_to_json)
{
    set_md_var("ident", "command_commandmap_to_json");
    set_md_var("descr", "Taxonomy::Command CommandMap to_json");
}

ATF_TEST_CASE_BODY(command_commandmap_to_json)
{
    fuse::Taxonomy::Command command1 = _internalCreateTestCommand("device1", "command1", "evaCommand1", 1, 1);
    fuse::Taxonomy::Command command2 = _internalCreateTestCommand("device2", "command2", "evaCommand2", 2, 2);
    fuse::Taxonomy::Command command3 = _internalCreateTestCommand("device3", "command3", "evaCommand3", 3, 3);
    fuse::Taxonomy::Command command4 = _internalCreateTestCommand("device4", "command4", "evaCommand4", 4, 4);

    std::map<std::string, fuse::Taxonomy::Command> commands;
    commands.insert(std::pair<std::string, fuse::Taxonomy::Command>(command1.deviceID, command1));
    commands.insert(std::pair<std::string, fuse::Taxonomy::Command>(command2.deviceID, command2));
    commands.insert(std::pair<std::string, fuse::Taxonomy::Command>(command3.deviceID, command3));
    commands.insert(std::pair<std::string, fuse::Taxonomy::Command>(command4.deviceID, command4));

    auto json = fuse::Taxonomy::Command::ExportMapToJson(commands);

    ATF_REQUIRE(json["device1"]["deviceID"].string_value() == "device1");
    ATF_REQUIRE(json["device1"]["commandID"].string_value() == "command1");
    ATF_REQUIRE(json["device1"]["evaCommandID"].string_value() == "evaCommand1");
    ATF_REQUIRE(json["device1"]["data"].int_value() == 1);
    ATF_REQUIRE(json["device1"]["cec"].int_value() == 1);
    ATF_REQUIRE(json["device2"]["deviceID"].string_value() == "device2");
    ATF_REQUIRE(json["device2"]["commandID"].string_value() == "command2");
    ATF_REQUIRE(json["device2"]["evaCommandID"].string_value() == "evaCommand2");
    ATF_REQUIRE(json["device2"]["data"].int_value() == 2);
    ATF_REQUIRE(json["device2"]["cec"].int_value() == 2);
    ATF_REQUIRE(json["device3"]["deviceID"].string_value() == "device3");
    ATF_REQUIRE(json["device3"]["commandID"].string_value() == "command3");
    ATF_REQUIRE(json["device3"]["evaCommandID"].string_value() == "evaCommand3");
    ATF_REQUIRE(json["device3"]["data"].int_value() == 3);
    ATF_REQUIRE(json["device3"]["cec"].int_value() == 3);
    ATF_REQUIRE(json["device4"]["deviceID"].string_value() == "device4");
    ATF_REQUIRE(json["device4"]["commandID"].string_value() == "command4");
    ATF_REQUIRE(json["device4"]["evaCommandID"].string_value() == "evaCommand4");
    ATF_REQUIRE(json["device4"]["data"].int_value() == 4);
    ATF_REQUIRE(json["device4"]["cec"].int_value() == 4);

    std::string jsonString;
    json["device4"].dump(jsonString);

    std::string error;
    json11::Json jsonObject = json11::Json::parse(jsonString, error);
    ATF_REQUIRE(error.empty());
    fuse::Taxonomy::Command command(jsonObject);
    ATF_REQUIRE(command.isValid() == true);
    ATF_REQUIRE(command.deviceID == "device4");
    ATF_REQUIRE(command.commandID == "command4");
    ATF_REQUIRE(command.evaCommandID == "evaCommand4");
    ATF_REQUIRE(command.data == 4);
    ATF_REQUIRE(command.cec == 4);
}

ATF_TEST_CASE(command_commandlistmap_to_json);

ATF_TEST_CASE_HEAD(command_commandlistmap_to_json)
{
    set_md_var("ident", "command_commandlistmap_to_json");
    set_md_var("descr", "Taxonomy::Command CommandListMap to_json");
}

ATF_TEST_CASE_BODY(command_commandlistmap_to_json)
{
    std::vector<fuse::Taxonomy::Command> commands1;
    std::vector<fuse::Taxonomy::Command> commands2;
    std::vector<fuse::Taxonomy::Command> commands3;
    std::vector<fuse::Taxonomy::Command> commands4;

    fuse::Taxonomy::Command device1Command1 = _internalCreateTestCommand("device1", "command1", "evaCommand1", 1, 1);
    fuse::Taxonomy::Command device1Command2 = _internalCreateTestCommand("device1", "command2", "evaCommand2", 2, 2);
    fuse::Taxonomy::Command device1Command3 = _internalCreateTestCommand("device1", "command3", "evaCommand3", 3, 3);
    fuse::Taxonomy::Command device1Command4 = _internalCreateTestCommand("device1", "command4", "evaCommand4", 4, 4);

    commands1.push_back(device1Command1);
    commands1.push_back(device1Command2);
    commands1.push_back(device1Command3);
    commands1.push_back(device1Command4);

    fuse::Taxonomy::Command device2Command1 = _internalCreateTestCommand("device2", "command5", "evaCommand5", 5, 5);
    fuse::Taxonomy::Command device2Command2 = _internalCreateTestCommand("device2", "command6", "evaCommand6", 6, 6);
    fuse::Taxonomy::Command device2Command3 = _internalCreateTestCommand("device2", "command7", "evaCommand7", 7, 7);
    fuse::Taxonomy::Command device2Command4 = _internalCreateTestCommand("device2", "command8", "evaCommand8", 8, 8);

    commands2.push_back(device2Command1);
    commands2.push_back(device2Command2);
    commands2.push_back(device2Command3);
    commands2.push_back(device2Command4);

    fuse::Taxonomy::Command device3Command1 = _internalCreateTestCommand("device3", "command9", "evaCommand9", 9, 9);
    fuse::Taxonomy::Command device3Command2 = _internalCreateTestCommand("device3", "command10", "evaCommand10", 10, 10);
    fuse::Taxonomy::Command device3Command3 = _internalCreateTestCommand("device3", "command11", "evaCommand11", 11, 11);
    fuse::Taxonomy::Command device3Command4 = _internalCreateTestCommand("device3", "command12", "evaCommand12", 12, 12);

    commands3.push_back(device3Command1);
    commands3.push_back(device3Command2);
    commands3.push_back(device3Command3);
    commands3.push_back(device3Command4);

    fuse::Taxonomy::Command device4Command1 = _internalCreateTestCommand("device4", "command13", "evaCommand13", 13, 13);
    fuse::Taxonomy::Command device4Command2 = _internalCreateTestCommand("device4", "command14", "evaCommand14", 14, 14);
    fuse::Taxonomy::Command device4Command3 = _internalCreateTestCommand("device4", "command15", "evaCommand15", 15, 15);
    fuse::Taxonomy::Command device4Command4 = _internalCreateTestCommand("device4", "command16", "evaCommand16", 16, 16);

    commands4.push_back(device4Command1);
    commands4.push_back(device4Command2);
    commands4.push_back(device4Command3);
    commands4.push_back(device4Command4);

    std::map<std::string, std::vector<fuse::Taxonomy::Command>> listMap;
    listMap.insert(std::pair<std::string, std::vector<fuse::Taxonomy::Command>>("device1", commands1));
    listMap.insert(std::pair<std::string, std::vector<fuse::Taxonomy::Command>>("device2", commands2));
    listMap.insert(std::pair<std::string, std::vector<fuse::Taxonomy::Command>>("device3", commands3));
    listMap.insert(std::pair<std::string, std::vector<fuse::Taxonomy::Command>>("device4", commands4));

    auto json = fuse::Taxonomy::Command::ExportListMapToJson(listMap);

    ATF_REQUIRE(json["device1"][0]["deviceID"].string_value() == "device1");
    ATF_REQUIRE(json["device1"][0]["commandID"].string_value() == "command1");
    ATF_REQUIRE(json["device1"][0]["evaCommandID"].string_value() == "evaCommand1");
    ATF_REQUIRE(json["device1"][0]["data"].int_value() == 1);
    ATF_REQUIRE(json["device1"][0]["cec"].int_value() == 1);
    ATF_REQUIRE(json["device2"][1]["deviceID"].string_value() == "device2");
    ATF_REQUIRE(json["device2"][1]["commandID"].string_value() == "command6");
    ATF_REQUIRE(json["device2"][1]["evaCommandID"].string_value() == "evaCommand6");
    ATF_REQUIRE(json["device2"][1]["data"].int_value() == 6);
    ATF_REQUIRE(json["device2"][1]["cec"].int_value() == 6);
    ATF_REQUIRE(json["device3"][2]["deviceID"].string_value() == "device3");
    ATF_REQUIRE(json["device3"][2]["commandID"].string_value() == "command11");
    ATF_REQUIRE(json["device3"][2]["evaCommandID"].string_value() == "evaCommand11");
    ATF_REQUIRE(json["device3"][2]["data"].int_value() == 11);
    ATF_REQUIRE(json["device3"][2]["cec"].int_value() == 11);
    ATF_REQUIRE(json["device4"][3]["deviceID"].string_value() == "device4");
    ATF_REQUIRE(json["device4"][3]["commandID"].string_value() == "command16");
    ATF_REQUIRE(json["device4"][3]["evaCommandID"].string_value() == "evaCommand16");
    ATF_REQUIRE(json["device4"][3]["data"].int_value() == 16);
    ATF_REQUIRE(json["device4"][3]["cec"].int_value() == 16);

    std::string jsonString;
    json["device3"][0].dump(jsonString);

    std::string error;
    json11::Json jsonObject = json11::Json::parse(jsonString, error);
    ATF_REQUIRE(error.empty());
    fuse::Taxonomy::Command command(jsonObject);
    ATF_REQUIRE(command.isValid() == true);
    ATF_REQUIRE(command.deviceID == "device3");
    ATF_REQUIRE(command.commandID == "command9");
    ATF_REQUIRE(command.evaCommandID == "evaCommand9");
    ATF_REQUIRE(command.data == 9);
    ATF_REQUIRE(command.cec == 9);
}

#pragma mark Init Test Cases

ATF_INIT_TEST_CASES(all)
{
    ATF_ADD_TEST_CASE(all, command_construct_null);
    ATF_ADD_TEST_CASE(all, command_construct_eva_command);
    ATF_ADD_TEST_CASE(all, command_construct_user_command);
    ATF_ADD_TEST_CASE(all, command_to_json);
    ATF_ADD_TEST_CASE(all, command_from_json);
    ATF_ADD_TEST_CASE(all, command_commandlist_to_json);
    ATF_ADD_TEST_CASE(all, command_commandmap_to_json);
    ATF_ADD_TEST_CASE(all, command_commandlistmap_to_json);
} 

