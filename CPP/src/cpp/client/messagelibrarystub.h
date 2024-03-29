/**
 * This file is generated by jsonrpcstub, DO NOT CHANGE IT MANUALLY!
 */

#ifndef JSONRPC_CPP_STUB_MESSAGELIBRARYSTUB_H_
#define JSONRPC_CPP_STUB_MESSAGELIBRARYSTUB_H_

#include <jsonrpccpp/client.h>

class messagelibrarystub : public jsonrpc::Client
{
    public:
        messagelibrarystub(jsonrpc::IClientConnector &conn, jsonrpc::clientVersion_t type = jsonrpc::JSONRPC_CLIENT_V2) : jsonrpc::Client(conn, type) {}

        Json::Value getMessageFromHeaders(const std::string& param1) throw (jsonrpc::JsonRpcException)
        {
            Json::Value p;
            p.append(param1);
            Json::Value result = this->CallMethod("getMessageFromHeaders",p);
            if (result.isArray())
                return result;
            else
                throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
        }
        Json::Value getMessage(const std::string& param1, const std::string& param2) throw (jsonrpc::JsonRpcException)
        {
            Json::Value p;
            p.append(param1);
            p.append(param2);
            Json::Value result = this->CallMethod("getMessage",p);
            if (result.isObject())
                return result;
            else
                throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
        }
        bool deleteMessage(const std::string& param1, const std::string& param2) throw (jsonrpc::JsonRpcException)
        {
            Json::Value p;
            p.append(param1);
            p.append(param2);
            Json::Value result = this->CallMethod("deleteMessage",p);
            if (result.isBool())
                return result.asBool();
            else
                throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
        }
        bool initGroupFromJsonFile() throw (jsonrpc::JsonRpcException)
        {
            Json::Value p;
            p = Json::nullValue;
            Json::Value result = this->CallMethod("initGroupFromJsonFile",p);
            if (result.isBool())
                return result.asBool();
            else
                throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
        }
        bool sendClearText(const std::string& param1, const std::string& param2, const std::string& param3, const std::string& param4, const std::string& param5, const std::string& param6, const std::string& param7, const std::string& param8, const std::string& param9) throw (jsonrpc::JsonRpcException)
        {
            Json::Value p;
            p.append(param1);
            p.append(param2);
            p.append(param3);
            p.append(param4);
            p.append(param5);
            p.append(param6);
            p.append(param7);
            p.append(param8);
            p.append(param9);
            Json::Value result = this->CallMethod("sendClearText",p);
            if (result.isBool())
                return result.asBool();
            else
                throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
        }
};

#endif //JSONRPC_CPP_STUB_MESSAGELIBRARYSTUB_H_
