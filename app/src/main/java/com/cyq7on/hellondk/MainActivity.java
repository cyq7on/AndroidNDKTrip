package com.cyq7on.hellondk;

import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import java.text.SimpleDateFormat;
import java.util.Date;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
            }
        });

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        StringBuilder stringBuilder = new StringBuilder(stringFromJNI() + "\n");

        HelloJNI helloJNI = new HelloJNI();
        stringBuilder.append("修改前 name 的值：" + helloJNI.getName() + "\n");
        Log.d("修改前 name 的值", helloJNI.getName());
        helloJNI.accessJavaField();
        stringBuilder.append("修改后 name 的值：" + helloJNI.getName() + "\n");
        Log.d("修改后 name 的值", helloJNI.getName());
        helloJNI.accessJavaMethod();
        stringBuilder.append("setName:" + helloJNI.getName() + "\n");
        HelloJNI.changeFlag();
        stringBuilder.append("changeFlag:" + HelloJNI.flag + "\n");
        helloJNI.accessJavaStaticField();
        stringBuilder.append("age:" + HelloJNI.age + "\n");
        stringBuilder.append("static setAge():" + HelloJNI.age + "\n");
        helloJNI.accessJavaStaticMethod();
        SimpleDateFormat sdf = new SimpleDateFormat();
        sdf.applyPattern("yyyy-MM-dd  HH:mm:ss:S") ;
        String date = sdf.format(new Date(helloJNI.accessJavaConstructorMethod()));
        stringBuilder.append("accessJavaConstructorMethod:" + date + "\n");
        // Java数组在C中排序
        int[] array = {1,60,20,10,4,90,23} ;
        helloJNI.arraySort(array);
        // 输出
        stringBuilder.append("sort:");
        for (int i = 0; i < array.length; i++) {
            stringBuilder.append(array[i] + ",");
        }
        stringBuilder.append("\n");
        //得到C中创建的数据
        array = helloJNI.getIntArray(7);
        stringBuilder.append("array from c:");
        for (int i = 0; i < array.length; i++) {
            stringBuilder.append(array[i] + "\t");
        }
        stringBuilder.append("\n");
        tv.setText(stringBuilder);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}
