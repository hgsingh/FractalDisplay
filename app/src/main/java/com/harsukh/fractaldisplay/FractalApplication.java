package com.harsukh.fractaldisplay;

import android.app.Application;

/**
 * Created by harsukh on 5/28/17.
 */

public class FractalApplication extends Application {
    @Override
    public void onCreate() {
        super.onCreate();
        System.loadLibrary("native-lib");
    }
}
