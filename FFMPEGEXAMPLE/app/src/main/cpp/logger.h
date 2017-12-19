//
// Created by Qiuyi on 2017/12/18.
//

#ifndef MYANDROIDTEXT_LOGGER_H
#define MYANDROIDTEXT_LOGGER_H

#include <android/log.h>

#define LOGE(FORMAT, ...) __android_log_print(ANDROID_LOG_ERROR, "ffmpeg", FORMAT, ##__VA_ARGS__);
#define LOGD(FORMAT, ...) __android_log_print(ANDROID_LOG_INFO, "ffmpeg", FORMAT, ##__VA_ARGS__);

#endif //MYANDROIDTEXT_LOGGER_H
