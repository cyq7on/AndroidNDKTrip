package com.cyq7on.hellondk;

/**
 * Created by cyq7on on 2016/12/7.
 */

public class HelloJNI {
    // 使用C语言修改java字段
    private String name = "zeno" ;
    public static int age;
    public static String flag = "flag";

    // C语言修改java String 类型字段本地方法
    public native void accessJavaField() ;
    public static native void changeFlag() ;
    public native void accessJavaStaticField() ;

    public native void accessJavaMethod() ;
    public native void accessJavaStaticMethod() ;
    public native long accessJavaConstructorMethod() ;
    public native void arraySort(int[] arr) ;
    public native int[] getIntArray(int len) ;

    //供c调用
    private void setName(String name) {
        this.name = name;
    }
    private static void setAge(int age) {
        HelloJNI.age = age;
    }

    public String getName() {
        return name;
    }
}
