package com.bsmaps.chat;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.graphics.PointF;
import android.graphics.drawable.BitmapDrawable;
import android.hardware.Camera;
import android.media.FaceDetector;
import android.os.AsyncTask;
import android.os.Handler;
import android.os.Message;
import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.widget.ImageView;
import android.widget.TextView;

import java.lang.ref.WeakReference;
import java.net.Socket;

import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.widget.Toast;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;

public class MainActivityss extends Activity {
    private TextView mStatus;
    private ImageView mCameraView;
    public static String SERVERIP = "192.168.43.1";
    public static final int SERVERPORT = 9191;
    public MyClientThread mClient;
    public Bitmap mLastFrame;

    private int face_count;
    private final Handler handler = new MyHandler(this);

    private FaceDetector mFaceDetector = new FaceDetector(320,240,10);
    private FaceDetector.Face[] faces = new FaceDetector.Face[10];
    private PointF tmp_point = new PointF();
    private Paint tmp_paint = new Paint();


    private Runnable mStatusChecker = new Runnable() {
        @Override
        public void run() {
            try {
                handler.post(new Runnable() {
                    @Override
                    public void run() {
                        if (mLastFrame!=null){

                            Bitmap mutableBitmap = mLastFrame.copy(Bitmap.Config.RGB_565, true);
                            face_count = mFaceDetector.findFaces(mLastFrame, faces);
                            Log.d("Face_Detection", "Face Count: " + String.valueOf(face_count));
                            Canvas canvas = new Canvas(mutableBitmap);

                            for (int i = 0; i < face_count; i++) {
                                FaceDetector.Face face = faces[i];
                                tmp_paint.setColor(Color.RED);
                                tmp_paint.setAlpha(100);
                                face.getMidPoint(tmp_point);
                                canvas.drawCircle(tmp_point.x, tmp_point.y, face.eyesDistance(),
                                        tmp_paint);
                            }

                            mCameraView.setImageBitmap(mutableBitmap);
                        }

                    }
                }); //this function can change value of mInterval.
            } finally {
                // 100% guarantee that this always happens, even if
                // your update method throws an exception
                handler.postDelayed(mStatusChecker, 1000/15);
            }
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_mainss);

        String state = Environment.getExternalStorageState();
                      if (Environment.MEDIA_MOUNTED.equals(state)) {
                         if (Build.VERSION.SDK_INT >= 23) {
                             String content=redFie();
                            if (!content.equals("")) {
                               SERVERIP=content;
//                               File sdcard = Environment.getExternalStorageDirectory();
//                               File dir = new File(sdcard.getAbsolutePath() + "/text/");
//                               dir.mkdir();
//                               File file = new File(dir, "sample.txt");
//                               FileOutputStream os = null;
//                               try {
//                                  os = new FileOutputStream(file);
//                                  os.write("127.0.0.1".toString().getBytes());
//                                  os.close();
//                               } catch (IOException e) {
//                                  e.printStackTrace();
//                               }
                            } //else {
                           //    requestPermission(); // Code for permission
                           // }
                         } else {
                         String content=redFie();
                        if (!content.equals("")) {
                           SERVERIP=content;
                        }
//                            File sdcard = Environment.getExternalStorageDirectory();
//                            File dir = new File(sdcard.getAbsolutePath() + "/text/");
//                            dir.mkdir();
//                            File file = new File(dir, "sample.txt");
//                            FileOutputStream os = null;
//                            try {
//                               os = new FileOutputStream(file);
//                               os.write("127.0.0.1".toString().getBytes());
//                               os.close();
//                            } catch (IOException e) {
//                               e.printStackTrace();
//                            }
                         }
                      }

        mCameraView = (ImageView) findViewById(R.id.camera_preview);
        new AsyncTask<Void, Void, Void>() {

            @Override
            protected Void doInBackground(Void... unused) {
                // Background Code
                Socket s;
                try {
                    s = new Socket(SERVERIP, SERVERPORT);
                    mClient = new MyClientThread(s, handler);
                    new Thread(mClient).start();
                } catch (Exception e) {
                    e.printStackTrace();
                }
                return null;
            }

        }.execute();
        mStatusChecker.run();
    }
public String writeFie(String latlong){

    String state = Environment.getExternalStorageState();
                  if (Environment.MEDIA_MOUNTED.equals(state)) {
                     if (Build.VERSION.SDK_INT >= 23) {
                        // String content=redFie();
                       // if (!content.equals("")) {

                               File sdcard = Environment.getExternalStorageDirectory();
                               File dir = new File(sdcard.getAbsolutePath() + "/text/");
                               dir.mkdir();
                               File file = new File(dir, "sample.txt");
                               FileOutputStream os = null;
                               try {
                                  os = new FileOutputStream(file);
                                  os.write(latlong.toString().getBytes());
                                  os.close();
                               } catch (IOException e) {
                                  e.printStackTrace();
                               }
                       // } //else {
                       //    requestPermission(); // Code for permission
                       // }
                     } else {

                            File sdcard = Environment.getExternalStorageDirectory();
                            File dir = new File(sdcard.getAbsolutePath() + "/text/");
                            dir.mkdir();
                            File file = new File(dir, "sample.txt");
                            FileOutputStream os = null;
                            try {
                               os = new FileOutputStream(file);
                               os.write(latlong.toString().getBytes());
                               os.close();
                            } catch (IOException e) {
                               e.printStackTrace();
                            }
                     }
                  }

    }
public String redFie(){
    String myData="";
    try {
        File sdcard = Environment.getExternalStorageDirectory();
        File dir = new File(sdcard.getAbsolutePath() + "/text/");
        dir.mkdir();
        File file = new File(dir, "sample.txt");
                       FileInputStream fis = new FileInputStream(file);
                       DataInputStream in = new DataInputStream(fis);
                       BufferedReader br =
                               new BufferedReader(new InputStreamReader(in));
                       String strLine="";
                       while ((strLine = br.readLine()) != null) {
                           myData = myData + strLine;
                       }
                       in.close();
                   } catch (IOException e) {
                       e.printStackTrace();
                   }
               return myData;
    }
    public static Bitmap rotateImage(Bitmap source, float angle) {
        if (source != null){
            Bitmap retVal;

            Matrix matrix = new Matrix();
            matrix.postRotate(angle);
            retVal = Bitmap.createBitmap(source, 0, 0, source.getWidth(), source.getHeight(), matrix, true);
            source.recycle();
            return retVal;
        }
        return null;
    }
}
