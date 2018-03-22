#include <jni.h>
#include <string>
#include <android/log.h>

#define TAG "JNI_Test====>"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)

extern "C" {
JNIEXPORT jstring

JNICALL
Java_com_joe_jni_1test_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

JNIEXPORT void
JNICALL
Java_com_joe_jni_1test_MainActivity_setString(JNIEnv *env, jobject thiz, jstring string) {
    const char *c = env->GetStringUTFChars(string, NULL);
    int len = env->GetStringUTFLength(string);
    LOGI("set string [%s] from java, len: %d", c,len);
    env->ReleaseStringUTFChars(string, c);
}

JNIEXPORT jintArray
JNICALL
Java_com_joe_jni_1test_MainActivity_getIntArray(JNIEnv *env, jobject thiz) {
    jint size = 5;
    //create native array
    jintArray a = env->NewIntArray(size);
    if(a == NULL) {
        LOGE("new int array error, out of memory");
        return NULL;
    }

    jint b[size];
    for(int i=0; i<size; i++) {
        b[i] = i+2;
    }

    //set element region
    env->SetIntArrayRegion(a, 0, size, b);

    return a;
}

JNIEXPORT void
JNICALL
Java_com_joe_jni_1test_MainActivity_setFloatArray(JNIEnv *env, jobject thiz, jfloatArray array) {
    //get element pointer
    jfloat *a = env->GetFloatArrayElements(array, NULL);
    if(a == NULL) {
        LOGE("no available value");
        return;
    }

    LOGI("got float array=>");
    jint len = env->GetArrayLength(array);
    for(int i=0; i<len; i++) {
        LOGI("elem[%d]: %.5f", i, a[i]);
    }

    //get element region
    jint nsize = 5;
    jfloat native[nsize];
    if(nsize > len) nsize = len;
    env->GetFloatArrayRegion(array,0,nsize, native);
    for(int i=0; i<len; i++) {
        LOGI("elem[%d]: %.5f", i, native[i]);
    }

    env->ReleaseFloatArrayElements(array, a, 0);
}

JNIEXPORT void
JNICALL
Java_com_joe_jni_1test_MainActivity_setJavaVal(JNIEnv *env, jobject thiz) {
    //one way to get class is from object itself from java
    jclass cls = env->GetObjectClass(thiz);
    if(cls == NULL){
        LOGE("can not get class object");
        return;
    }

    //get field id for get or set the field value, even private field
    jfieldID intfd = env->GetFieldID(cls, "val", "I");
    if(intfd == 0) {
        LOGE("can not get int val field ID");
        return;
    }

    jfieldID strfd = env->GetStaticFieldID(cls, "str", "Ljava/lang/String;");
    if(strfd == 0) {
        LOGE("can not get float val field ID");
        return;
    }

    //get field val through field id
    jint val = env->GetIntField(thiz, intfd);
    LOGI("get orig java int val: %d", val);

    //set field val through filed id
    env->SetIntField(thiz, intfd, -1);
    jstring str = env->NewStringUTF("native test string");

    //static value do not need object, just need class, because they are shared to all objects
    env->SetStaticObjectField(cls, strfd, str);
}

JNIEXPORT void
JNICALL
Java_com_joe_jni_1test_MainActivity_callMainFunc(JNIEnv *env, jobject thiz) {
    jclass cls = env->GetObjectClass(thiz);
    if(cls == NULL){
        LOGE("can not get class object");
        return;
    }

    //get method id for calling
    jmethodID mid = env->GetMethodID(cls, "getFval", "()F");
    if(mid == 0) {
        LOGE("can not get method ID");
        return;
    }

    //call java method
    jfloat val = env->CallFloatMethod(thiz, mid);
    LOGI("get float value from java:%f",val);

}

JNIEXPORT void
JNICALL
Java_com_joe_jni_1test_MainActivity_callObjFunc(JNIEnv *env, jobject thiz) {
    //another way to get class
    jclass cls = env->FindClass("com/joe/jni_test/util");
    if(cls == NULL){
        LOGE("can not get class object com.joe.jni_test.util");
        return;
    }

    jmethodID constructid = env->GetMethodID(cls, "<init>", "(ILjava/lang/String;)V");
    if(constructid == 0) {
        LOGE("can not get construct method ID");
        return;
    }

    jmethodID infoid = env->GetMethodID(cls, "list_info", "()V");
    if(infoid == 0) {
        LOGE("can not get list out method ID");
        return;
    }

    //create one java object with construct function
    jstring name = env->NewStringUTF("native_jack");
    jobject util = env->NewObject(cls, constructid, 10, name);

    //call method
    env->CallVoidMethod(util, infoid);

}

}