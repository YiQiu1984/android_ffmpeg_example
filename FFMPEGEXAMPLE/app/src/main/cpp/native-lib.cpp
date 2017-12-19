#include <jni.h>
#include <string>
#include <android/log.h>
extern "C" {
#include "libavformat/avformat.h"
#include "ffmpeg.h"
}

#include "logger.h"

extern "C"
JNIEXPORT jstring JNICALL
Java_test_yves_com_ffmpegexample_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    LOGD("test ffmpeg build");
    return env->NewStringUTF(hello.c_str());
}

int run(int argc, char **argv);

extern "C"
JNIEXPORT jint JNICALL
Java_test_yves_com_ffmpegexample_MainActivity_ffmpegrun(JNIEnv * env, jobject thiz, jint cmdnum, jobjectArray cmdline)
{
    int argc = cmdnum;
    char** argv = (char**) malloc( sizeof(char*)*argc );

    int i = 0;
    for(i = 0; i < argc ;i++)
    {
        jstring string = (jstring)(*env).GetObjectArrayElement(cmdline, i);
        const char* tmp = (*env).GetStringUTFChars(string, 0);
        argv[i]=(char*)malloc(sizeof(char) * 1024);
        strcpy(argv[i],tmp);
        LOGD("test ffmpeg run, argv[%d] = %s", i, argv[i]);
    }

    run(argc, argv);

    for(i = 0; i < argc; i++){
        free(argv[i]);
    }
    free(argv);
    return 0;

}
