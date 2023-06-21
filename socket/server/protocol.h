#ifndef PROTOCOL_H
#define PROTOCOL_H
enum MSGTYPE{
    LOGIN_REQUEST,
    LOGIN_SUCCESS,
    LOGIN_FAILED_ACCOUNT_OR_PASSWD,
    LOGIN_FAILED_NOT_REGIST,
    REGIST_REQUEST,
    REGIST_SUCCESS,
    REGIST_CODE_NOT_RIGHT
};
#endif // PROTOCOL_H