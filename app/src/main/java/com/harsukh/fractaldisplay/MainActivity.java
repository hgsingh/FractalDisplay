package com.harsukh.fractaldisplay;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.FrameLayout;
import android.widget.SeekBar;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = MainActivity.class.getSimpleName();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        final CustomJNIView customJNIView = new CustomJNIView(this);
        FrameLayout frameLayout = (FrameLayout) findViewById(R.id.jni_container);
        frameLayout.addView(customJNIView);
        SeekBar seekBar = (SeekBar) findViewById(R.id.seeking);
        seekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {

            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                Log.i(TAG, "Seekbar progress changed to " + progress);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
                Log.i(TAG, "Seekbar scrolling started");
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                customJNIView.loadFromSeekbar(seekBar.getProgress());
            }
        });
    }
}
