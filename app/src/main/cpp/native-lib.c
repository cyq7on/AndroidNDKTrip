#include <jni.h>
#include <stdlib.h>
#include <stdio.h>


JNIEXPORT jstring JNICALL Java_com_cyq7on_hellondk_MainActivity_stringFromJNI
        (JNIEnv *Env, jclass jclazz) {

    return (*Env)->NewStringUTF(Env, "Hello from C");
}

JNIEXPORT void JNICALL Java_com_cyq7on_hellondk_HelloJNI_accessJavaField
        (JNIEnv *env, jobject jobj) {

    // 得到jclass
    jclass jcls = (*env)->GetObjectClass(env, jobj);

    // 得到字段ID
    jfieldID jfID = (*env)->GetFieldID(env, jcls, "name", "Ljava/lang/String;");

    // 得到字段的值
    jstring jstr = (*env)->GetObjectField(env, jobj, jfID);

    // 将jstring类型转换成字符指针
    char* cstr = (*env)->GetStringUTFChars(env, jstr, JNI_FALSE);
    //printf("is vaule：%s\n", cstr);
    // 拼接字符
    char text[30] = "  xiaojiu and ";
    strcat(text, cstr);
    printf("modify value %s\n", text);

    // 将字符指针转换成jstring类型
    jstring new_str = (*env)->NewStringUTF(env, text);

    // 将jstring类型的变量 ， 设置到java 字段中
    (*env)->SetObjectField(env, jobj, jfID, new_str);
}
//changeFlag()方法是static的，所以此处第二个形参为jclass类型，而普通方法为jobject类型
JNIEXPORT void JNICALL Java_com_cyq7on_hellondk_HelloJNI_changeFlag
        (JNIEnv *env, jclass jcls) {


    // 得到字段ID
    jfieldID jfID = (*env)->GetStaticFieldID(env, jcls, "flag", "Ljava/lang/String;");

    // 得到字段的值
    jstring jstr = (*env)->GetStaticObjectField(env, jcls, jfID);

    // 将jstring类型转换成字符指针
    char* cstr = (*env)->GetStringUTFChars(env, jstr, JNI_FALSE);
    //printf("is vaule：%s\n", cstr);
    // 拼接字符
    char text[30] = " change by static native";
    strcat(cstr,text);
    // 将字符指针转换成jstring类型
    jstring new_str = (*env)->NewStringUTF(env, cstr);

    // 将jstring类型的变量 ， 设置到java 字段中
    (*env)->SetStaticObjectField(env, jcls, jfID, new_str);
}
JNIEXPORT void JNICALL Java_com_cyq7on_hellondk_HelloJNI_accessJavaStaticField
        (JNIEnv *env, jobject jobj) {

    jclass jcls = (*env)->GetObjectClass(env, jobj);
    jfieldID jstaticID = (*env)->GetStaticFieldID(env,jcls,"age","I");
    jint jage = (*env)->GetStaticIntField(env,jcls,jstaticID);
    jage += 23;
    (*env)->SetStaticIntField(env,jcls,jstaticID,jage);
}

JNIEXPORT void JNICALL Java_com_cyq7on_hellondk_HelloJNI_accessJavaMethod
        (JNIEnv *env, jobject jobj) {

    // 得到jclass
    jclass jcls = (*env)->GetObjectClass(env, jobj);

    // 得到方法ID
    jmethodID jmID = (*env)->GetMethodID(env, jcls, "setName", "(Ljava/lang/String;)V");

    jstring jname = (*env)->NewStringUTF(env,"cyq7on");
    // 调用方法
    (*env)->CallVoidMethod(env,jobj,jmID,jname);
}

JNIEXPORT void JNICALL Java_com_cyq7on_hellondk_HelloJNI_accessJavaStaticMethod
        (JNIEnv *env, jobject jobj) {

    // 得到jclass
    jclass jcls = (*env)->GetObjectClass(env, jobj);

    // 得到方法ID
    jmethodID jmID = (*env)->GetStaticMethodID(env, jcls, "setAge", "(I)V");

    jint jage = 46;
    // 调用方法
    (*env)->CallStaticVoidMethod(env,jcls,jmID,jage);
}
JNIEXPORT jlong JNICALL Java_com_cyq7on_hellondk_HelloJNI_accessJavaConstructorMethod
        (JNIEnv *env, jobject jobj) {

    // 得到jclass
    jclass dateCls = (*env)->FindClass(env, "java/util/Date");

    // 得到方法ID
    jmethodID dateConstructorID = (*env)->GetMethodID(env, dateCls, "<init>", "()V");
    jobject date = (*env)->NewObject(env,dateCls,dateConstructorID);
    jmethodID getTimeID = (*env)->GetMethodID(env, dateCls, "getTime", "()J");
    jlong time = (*env)->CallLongMethod(env,date,getTimeID);
    return time;
}

// sort
int compare(int* a, int* b) {

    return (*a) - (*b);
}


JNIEXPORT void JNICALL
Java_com_cyq7on_hellondk_HelloJNI_arraySort(JNIEnv *env, jobject instance, jintArray arr_) {
    jint *arr = (*env)->GetIntArrayElements(env, arr_, NULL);
    jsize arraySize = (*env)->GetArrayLength(env,arr_);
    qsort(arr,arraySize, sizeof(jint),compare);
    (*env)->ReleaseIntArrayElements(env, arr_, arr, 0);
}

JNIEXPORT jintArray JNICALL
Java_com_cyq7on_hellondk_HelloJNI_getIntArray(JNIEnv *env, jobject instance, jint len) {
    jintArray array = (*env)->NewIntArray(env,len);
    jint *arr = (*env)->GetIntArrayElements(env,array,NULL);
    for (int i = 0; i < len; ++i) {
        *(arr + i) = rand();
    }
    (*env)->ReleaseIntArrayElements(env,array,arr,0);
    return array;
}