package com.bsmaps.chat;

import android.graphics.Bitmap;
import android.os.Handler;
import android.os.Message;

import java.lang.ref.WeakReference;

/**
 * Created by Alvin on 2016-05-20.
 */
class MyHandler extends Handler {
    private final WeakReference<MainActivityss> mActivity;

    public MyHandler(MainActivityss activity) {
        mActivity = new WeakReference<MainActivityss>(activity);
    }

    @Override
    public void handleMessage(Message msg) {
        MainActivityss activity = mActivity.get();
        if (activity != null) {
            try {
                activity.mLastFrame = (Bitmap) msg.obj;
            } catch (Exception e) {
                e.printStackTrace();
            }
            super.handleMessage(msg);
        }
    }
}
