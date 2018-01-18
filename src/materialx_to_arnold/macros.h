#ifndef MTLX_TO_A_MACROS_H
#define MTLX_TO_A_MACROS_H

// Macros for more verbose messages during debug (for use with Arnold facade)

#ifdef NDEBUG

#define MSG_INFO(AF, FORMAT, ...) AF.AiMsgInfo(FORMAT, ##__VA_ARGS__)
#define MSG_DEBUG(AF, FORMAT, ...) AF.AiMsgDebug(FORMAT, ##__VA_ARGS__)
#define MSG_WARNING(AF, FORMAT, ...) AF.AiMsgWarning(FORMAT, ##__VA_ARGS__)
#define MSG_ERROR(AF, FORMAT, ...) AF.AiMsgError(FORMAT, ##__VA_ARGS__)
#define MSG_FATAL(AF, FORMAT, ...) AF.AiMsgFatal(FORMAT, ##__VA_ARGS__)

#else

#define MSG_INFO(AF, FORMAT, ...) AF.AiMsgInfo(__FILE__, __LINE__,  \
    __FUNCTION__, FORMAT, ##__VA_ARGS__)
#define MSG_DEBUG(AF, FORMAT, ...) AF.AiMsgDebug(__FILE__, __LINE__,  \
    __FUNCTION__, FORMAT, ##__VA_ARGS__)
#define MSG_WARNING(AF, FORMAT, ...) AF.AiMsgWarning(__FILE__, __LINE__,  \
    __FUNCTION__, FORMAT, ##__VA_ARGS__)
#define MSG_ERROR(AF, FORMAT, ...) AF.AiMsgError(__FILE__, __LINE__,  \
    __FUNCTION__, FORMAT, ##__VA_ARGS__)
#define MSG_FATAL(AF, FORMAT, ...) AF.AiMsgFatal(__FILE__, __LINE__,  \
    __FUNCTION__, FORMAT, ##__VA_ARGS__)

#endif

#endif // MTLX_TO_A_MACROS_H
