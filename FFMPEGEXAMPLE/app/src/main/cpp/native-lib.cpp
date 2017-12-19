#include <jni.h>
#include <string>
#include <android/log.h>
extern "C" {
#include "libavformat/avformat.h"
#include "ffmpeg.h"
}

#define LOGE(FORMAT, ...) __android_log_print(ANDROID_LOG_ERROR, "ffmpeg", FORMAT, ##__VA_ARGS__);
#define LOGD(FORMAT, ...) __android_log_print(ANDROID_LOG_INFO, "ffmpeg", FORMAT, ##__VA_ARGS__);

extern "C"
JNIEXPORT jstring JNICALL
Java_test_yves_com_ffmpegexample_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
//    av_register_all();
    LOGE("test ffmpeg build");
    return env->NewStringUTF(hello.c_str());
}

int run(int argc, char **argv);

extern "C"
JNIEXPORT jint JNICALL
Java_test_yves_com_ffmpegexample_MainActivity_ffmpegrun(JNIEnv *env, jclass obj, jobjectArray commands) {
    int argc = env->GetArrayLength(commands);
    char *argv[argc];
    int i;
    for (i = 0; i < argc; i++) {
        jstring js = (jstring) (*env).GetObjectArrayElement(commands, i);
        argv[i] = (char*) (*env).GetStringUTFChars(js, 0);
        LOGE("test ffmpeg run, argv[%d] = %s", i, argv[i]);
    }
//    LOGD("----------begin---------");
    return run(argc, argv);
}

//Output FFmpeg's av_log()
void custom_log(void *ptr, int level, const char* fmt, va_list vl){

    //To TXT file

    FILE *fp=fopen("/storage/emulated/0/av_log.txt","a+");
    if(fp){
        vfprintf(fp,fmt,vl);
        fflush(fp);
        fclose(fp);
    }
}

extern "C"
JNIEXPORT jint JNICALL
Java_test_yves_com_ffmpegexample_MainActivity_ffmpegcore(JNIEnv * env, jobject thiz, jint cmdnum, jobjectArray cmdline)
{

    //FFmpeg av_log() callback
//    av_log_set_callback(custom_log);

    int argc=cmdnum;
    char** argv=(char**)malloc(sizeof(char*)*argc);

    int i=0;
    for(i=0;i<argc;i++)
    {
        jstring string = (jstring)(*env).GetObjectArrayElement(cmdline, i);
        const char* tmp = (*env).GetStringUTFChars(string,0);
        argv[i]=(char*)malloc(sizeof(char)*1024);
        strcpy(argv[i],tmp);
        LOGE("test ffmpeg run, argv[%d] = %s", i, argv[i]);
    }

    run(argc,argv);

    for(i=0;i<argc;i++){
        free(argv[i]);
    }
    free(argv);
    return 0;

}
